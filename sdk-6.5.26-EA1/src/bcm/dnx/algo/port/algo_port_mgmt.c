/** \file algo_port_mgmt.c
 *
 *  PORT manager, Port utilities, and Port verifiers.
 *
 *  Algo port managment:
 *  * MGMT APIs
 *    - Used to configure algo port module
 *    - located in algo_port_mgmt.h (source code algo_port_mgmt.c)
 *  * Utility APIs
 *    - Provide utilities functions which will make the BCM module cleaner and simpler
 *    - located in algo_port_utils.h (source code algo_port_utils.c
 *  * Verify APIs
 *    - Provide a set of APIs which verify port attributes
 *    - These verifiers used to verify algo port functions input.
 *    - These verifiers can be used out side of the module, if requried.
 *    - located in algo_port_verify.h (source code algo_port_verify.c)
 *  * SOC APIs
 *    - Provide set of functions to set / restore  and remove soc info data
 *    - Only the port related members will be configured by this module (other modules should not set those memebers directly)
 *    - The relevant members are: 'port to block access', 'port names' and 'port bitmaps'
 *    - located in algo_port_soc.c (all the functions are module internals)
 *  * Module internal definitions - algo_port_internal.h
 *  * Data bases - use sw state mechanism - XML file is algo_port.xml
 *
 *  No need to include each sub module seperately.
 *  Including: 'algo_port_mgmt.h' will includes all the sub modules
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

/*
 * Include files.
 * {
 */

#include <soc/sand/shrextend/shrextend_debug.h>
#include <shared/utilex/utilex_bitstream.h>

#include <soc/memory.h>
#include <soc/feature.h>
#include <soc/types.h>
#include <soc/register.h>
#include <soc/dnxc/drv_dnxc_utils.h>

#include <soc/dnxc/swstate/dnxc_sw_state_utils.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/dnx_algo_port_access.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_device.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_fabric.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_nif.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_port.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_ingr_reassembly.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_max_egr_queuing.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_egr_queuing.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_egr_queuing_v1.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_sch.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_headers.h>
#include <soc/dnx/dnx_visibility.h>
#include <soc/portmod/portmod.h>

#include <bcm/types.h>

#include <bcm_int/dnx/algo/port/algo_port_mgmt.h>
#include <bcm_int/dnx/algo/port/algo_port_soc.h>
#include <bcm_int/dnx/algo/flexe_general/algo_flexe_general.h>
#include <bcm_int/dnx/algo/algo_gpm.h>
#include <bcm_int/dnx/algo/lane_map/algo_lane_map.h>
#include <bcm_int/dnx/cmn/dnxcmn.h>
#include "algo_port_internal.h"

/*
 * }
 */
/*
 * Defines.
 * {
 */
/** Maximum number of first header size profiles after injected header*/
#define DNX_PORT_MAX_FIRST_HEADER_SIZE_AFTER_INJECTED_PROFILES 1
/*
 * }
 */
/*
 * Macros
 * {
 */

/*
 * }
 */

/*
 * Local functions (documentation in function implementation)
 * {
 */

static shr_error_e dnx_algo_port_common_add(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t core,
    dnx_algo_port_common_add_t * info,
    dnx_algo_port_db_2d_handle_t interface_id);

static shr_error_e dnx_algo_port_tm_add(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t core,
    dnx_algo_port_tm_add_t * info,
    dnx_algo_port_db_2d_handle_t tm_interface_id);

static shr_error_e dnx_algo_port_sch_add(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t core,
    dnx_algo_port_tm_add_t * info,
    dnx_algo_port_db_2d_handle_t tm_interface_id);
/*
 * }
 */

/*
 * Module Init / Deinit
 * {
 */
/**
 * \brief - set default values for element in logical DB.
 */
static shr_error_e
dnx_algo_port_db_logical_init(
    int unit,
    bcm_port_t logical_port)
{
    dnx_algo_port_db_logical_t logical_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&logical_db, 0, sizeof(dnx_algo_port_db_logical_t));
    logical_db.fabric_handle = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.ilkn_handle = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.nif_handle = DNX_ALGO_PORT_HANDLE_INVALID;

    logical_db.pp_dsp_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.pp_dsp_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;

    logical_db.in_tm_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.in_tm_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;

    logical_db.pp_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.pp_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;

    logical_db.tm_interface_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.tm_interface_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.interface_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.interface_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.sch_if_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.sch_if_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.sch_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.sch_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.flexe_phy_handle = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.flexe_mac_handle = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.flexe_sar_handle = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.flexe_client_handle = DNX_ALGO_PORT_HANDLE_INVALID;
    logical_db.ptc = DNX_ALGO_PORT_HANDLE_INVALID;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.set(unit, logical_port, &logical_db));

exit:
    SHR_FUNC_EXIT;
}
/**
 * \brief - set default values for element in fabric DB.
 *          This function is not called during init since the current default is 0.
 *          In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_fabric_init(
    int unit,
    int fabric_handle)
{
    dnx_algo_port_db_fabric_t fabric_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&fabric_db, 0, sizeof(dnx_algo_port_db_fabric_t));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.set(unit, fabric_handle, &fabric_db));

exit:
    SHR_FUNC_EXIT;
}
/**
 * \brief - set default values for element in nif DB.
 *  This function is not called during init since the current default is 0.
 *  In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_nif_init(
    int unit,
    int nif_handle)
{
    int rmc_index;
    dnx_algo_port_db_nif_t nif_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&nif_db, 0, sizeof(dnx_algo_port_db_nif_t));
    nif_db.master_logical_port = DNX_ALGO_PORT_INVALID;
    for (rmc_index = 0; rmc_index < BCM_PORT_MAX_NOF_PRIORITY_GROUPS; ++rmc_index)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_rmc_info_t_init(unit, &nif_db.logical_fifos[rmc_index]));
    }
    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.set(unit, nif_handle, &nif_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in flexe client DB.
 *  This function is not called during init since the current default is 0.
 *  In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_flexe_client_init(
    int unit,
    int flexe_handle)
{
    dnx_algo_port_db_flexe_client_t flexe_client_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&flexe_client_db, 0, sizeof(dnx_algo_port_db_flexe_client_t));
    flexe_client_db.bas_period = bcmPortFlexeOamBasePeriod32K;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.set(unit, flexe_handle, &flexe_client_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in flexe mac DB.
 *  This function is not called during init since the current default is 0.
 *  In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_flexe_mac_init(
    int unit,
    int flexe_handle)
{
    int rmc_index;
    dnx_algo_port_db_flexe_mac_t flexe_mac_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&flexe_mac_db, 0, sizeof(dnx_algo_port_db_flexe_mac_t));
    for (rmc_index = 0; rmc_index < dnx_data_nif.mac_client.priority_groups_nof_get(unit); ++rmc_index)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_rmc_info_t_init(unit, &flexe_mac_db.logical_fifos[rmc_index]));
    }
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.set(unit, flexe_handle, &flexe_mac_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in flexe sar DB.
 *  This function is not called during init since the current default is 0.
 *  In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_flexe_sar_init(
    int unit,
    int flexe_handle)
{
    dnx_algo_port_db_flexe_sar_t flexe_sar_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&flexe_sar_db, 0, sizeof(dnx_algo_port_db_flexe_sar_t));
    flexe_sar_db.virtual_flexe_channel = -1;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.set(unit, flexe_handle, &flexe_sar_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in flexe phy DB.
 *  This function is not called during init since the current default is 0.
 *  In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_flexe_phy_init(
    int unit,
    int flexe_handle)
{
    dnx_algo_port_db_flexe_phy_t flexe_phy_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&flexe_phy_db, 0, sizeof(dnx_algo_port_db_flexe_phy_t));
    flexe_phy_db.core_port = DNX_ALGO_PORT_INVALID;
    flexe_phy_db.channel = DNX_ALGO_PORT_INVALID;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.phy.set(unit, flexe_handle, &flexe_phy_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in ilkn DB.
 *          This function is not called during init since the current default is 0.
 *          In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_ilkn_init(
    int unit,
    int ilkn_handle)
{
    dnx_algo_port_db_ilkn_t ilkn_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&ilkn_db, 0, sizeof(dnx_algo_port_db_ilkn_t));
    ilkn_db.master_logical_port = DNX_ALGO_PORT_INVALID;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.set(unit, ilkn_handle, &ilkn_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in tm interface DB.
 *          This function is not called during init since the current default is 0.
 *          In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_tm_interface_init(
    int unit,
    dnx_algo_port_db_2d_handle_t tm_interface_handle)
{
    dnx_algo_port_db_tm_interface_t tm_interface_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&tm_interface_db, 0, sizeof(dnx_algo_port_db_tm_interface_t));
    tm_interface_db.master_logical_port = DNX_ALGO_PORT_INVALID;
    tm_interface_db.rcy_mirror_logical_port = DNX_ALGO_PORT_INVALID;
    tm_interface_db.egr_if = DNX_ALGO_PORT_EGR_IF_INVALID;
    tm_interface_db.ch_egr_if = DNX_ALGO_PORT_EGR_IF_INVALID;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.
                    tm_interface.set(unit, tm_interface_handle.h0, tm_interface_handle.h1, &tm_interface_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in port_to_profile DB.
 *          This function is not called during init since the current default is 0.
 *          In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_prd_port_to_profile_map_interface_init(
    int unit,
    int interface_handle)
{
    dnx_algo_prd_info_t interface_db;
    int nif_interface_id, core;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_nif_interface_id_get(unit, interface_handle, 0, &core, &nif_interface_id));

    sal_memset(&interface_db, 0, sizeof(dnx_algo_prd_info_t));
    interface_db.port_to_profile_map = DNX_ALGO_PORT_INVALID;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.prd.set(unit, core, nif_interface_id, &interface_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for all elements in port_to_profile DB.
 *          This function will be called at dnx_algo_port_init and default for every interface will be DNX_ALGO_PORT_INVALID.
 *          Default value will be changed when PRD is configured for the interface and profile maping is initialized.
 */
static shr_error_e
dnx_algo_port_db_prd_port_to_profile_map_init_all_interfaces(
    int unit)
{
    dnx_algo_prd_info_t interface_db;
    int nif_interface_id, core;
    SHR_FUNC_INIT_VARS(unit);

    for (core = 0; core < dnx_data_device.general.nof_cores_get(unit); core++)
    {
        for (nif_interface_id = 0; nif_interface_id < dnx_data_nif.global.nof_nif_interfaces_per_core_get(unit);
             ++nif_interface_id)
        {
            sal_memset(&interface_db, 0, sizeof(dnx_algo_prd_info_t));
            interface_db.port_to_profile_map = DNX_ALGO_PORT_INVALID;
            SHR_IF_ERR_EXIT(dnx_algo_port_db.prd.set(unit, core, nif_interface_id, &interface_db));
        }
    }

exit:
    SHR_FUNC_EXIT;
}
/**
 * \brief - set default values for element in interface DB.
 *          This function is called during init from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_interface_init(
    int unit,
    dnx_algo_port_db_2d_handle_t interface_handle)
{
    dnx_algo_port_db_interface_t interface_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&interface_db, 0, sizeof(dnx_algo_port_db_interface_t));
    interface_db.master_logical_port = DNX_ALGO_PORT_INVALID;
    interface_db.tm_interface_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
    interface_db.tm_interface_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.set(unit, interface_handle.h0, interface_handle.h1, &interface_db));

exit:
    SHR_FUNC_EXIT;
}
/**
 * \brief - set default values for element in scheduler DB.
 *          This function is not called during init since the current default is 0.
 *          In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_sch_if_init(
    int unit,
    dnx_algo_port_db_2d_handle_t interface_handle)
{
    dnx_algo_port_db_sch_if_t sch_if_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&sch_if_db, 0, sizeof(dnx_algo_port_db_sch_if_t));
    sch_if_db.master_logical_port = DNX_ALGO_PORT_INVALID;
    sch_if_db.sch_if = -1;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.set(unit, interface_handle.h0, interface_handle.h1, &sch_if_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in out tm DB.
 *          This function is not called during init since the current default is 0.
 *          In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_out_tm_init(
    int unit,
    dnx_algo_port_db_2d_handle_t out_tm_handle)
{
    dnx_algo_port_db_out_tm_t out_tm_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&out_tm_db, 0, sizeof(dnx_algo_port_db_out_tm_t));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.set(unit, out_tm_handle.h0, out_tm_handle.h1, &out_tm_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in IN TM DB.
 *          This function is not called during init since the current default is 0.
 *          In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_in_tm_init(
    int unit,
    dnx_algo_port_db_2d_handle_t in_tm_handle)
{
    dnx_algo_port_db_in_tm_t in_tm;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&in_tm, 0, sizeof(dnx_algo_port_db_in_tm_t));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.set(unit, in_tm_handle.h0, in_tm_handle.h1, &in_tm));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in PP-DSP DB.
 *          This function is not called during init since the current default is 0.
 *          In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_pp_dsp_init(
    int unit,
    dnx_algo_port_db_2d_handle_t pp_dsp_handle)
{
    dnx_algo_port_db_pp_dsp_t pp_dsp_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&pp_dsp_db, 0, sizeof(dnx_algo_port_db_pp_dsp_t));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.set(unit, pp_dsp_handle.h0, pp_dsp_handle.h1, &pp_dsp_db));

    pp_dsp_db.out_tm_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
    pp_dsp_db.out_tm_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in pp DB.
 *          This function is not called during init since the current default is 0.
 *          In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_pp_init(
    int unit,
    dnx_algo_port_db_2d_handle_t pp_handle)
{
    dnx_algo_port_db_pp_t pp_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&pp_db, 0, sizeof(dnx_algo_port_db_pp_t));
    pp_db.header_type_in = BCM_SWITCH_PORT_HEADER_TYPE_ETH;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.set(unit, pp_handle.h0, pp_handle.h1, &pp_db));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_alloc.free_single(unit, pp_handle.h0, pp_handle.h1, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set default values for element in scheduler DB.
 *          This function is not called during init since the current default is 0.
 *          In a case the default should be changed to be different from 0, call this function from dnx_algo_port_init()
 */
static shr_error_e
dnx_algo_port_db_sch_init(
    int unit,
    dnx_algo_port_db_2d_handle_t sch_handle)
{
    dnx_algo_port_db_sch_t sch_db;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&sch_db, 0, sizeof(dnx_algo_port_db_sch_t));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.set(unit, sch_handle.h0, sch_handle.h1, &sch_db));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Initialize PRT ETH, PTCH1 and PTCH2 template managers
 *
 * \param [in] unit - Relevant unit
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_algo_port_db_first_header_size_init_templates(
    int unit)
{
    dnx_algo_template_create_data_t first_header_size_profile_data;
    dnx_algo_skip_first_header_info_t port_first_header_size_data;
    uint32 nof_references;
    SHR_FUNC_INIT_VARS(unit);

    /** Calculate nof_references */
    nof_references = dnx_data_port.general.nof_ptc_get(unit) * dnx_data_device.general.nof_cores_get(unit);

    sal_memset(&port_first_header_size_data, 0, sizeof(dnx_algo_skip_first_header_info_t));

    /** Create template for ETH, PTCH1 and PTCH2 ports */
    sal_memset(&first_header_size_profile_data, 0, sizeof(dnx_algo_template_create_data_t));
    first_header_size_profile_data.flags = DNX_ALGO_TEMPLATE_CREATE_USE_DEFAULT_PROFILE;
    first_header_size_profile_data.first_profile = DBAL_ENUM_FVAL_PORT_TERMINATION_PTC_PROFILE_UD1;
    /** Using additional profile as dummy profile*/
    first_header_size_profile_data.nof_profiles = DNX_ALGO_PORT_MAX_FIRST_HEADER_SIZE_PROFILES + 1;
    first_header_size_profile_data.max_references = nof_references;
    first_header_size_profile_data.default_profile = DNX_ALGO_PORT_FIRST_HEADER_SIZE_DEFAULT_PROFILE;
    first_header_size_profile_data.data_size = sizeof(dnx_algo_skip_first_header_info_t);
    first_header_size_profile_data.default_data = &port_first_header_size_data;
    sal_strncpy(first_header_size_profile_data.name, DNX_ALGO_PORT_FIRST_HEADER_SIZE_PROFILE,
                DNX_ALGO_TEMPLATE_MNGR_MAX_NAME_LENGTH - 1);

    SHR_IF_ERR_EXIT(dnx_algo_port_db.
                    skip_first_user_defined_header_size_profile_data.create(unit, &first_header_size_profile_data,
                                                                            NULL));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_init(
    int unit)
{
    bcm_port_t logical_port;
    int nof_fabric_links, nof_clients;
    int nof_nif_phys;
    int nof_pp_ports, nof_hrs;
    int nof_out_tm_ports, nof_pp_dsp, nof_in_tm_ports;
    int nof_cores;
    int nof_ilkn_if;
    int phy;
    dnx_algo_port_db_2d_handle_t if_id;
    int channel;
    bcm_core_t core_id;
    dnx_algo_res_create_data_t create_data;
    int nof_interfaces_handle0, nof_interfaces_handle1;
    SHR_FUNC_INIT_VARS(unit);

    if (sw_state_is_warm_boot(unit))
    {
       /** restore soc info data */
        SHR_IF_ERR_EXIT(dnx_algo_port_soc_info_restore(unit));
    }
    else
    {
        /*
         * Create SW State instance
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.init(unit));

        /*
         * Allocate SW STATE DBs
         */
        {
            /** Create portmod_mac_soft_reset_cb lock */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.general.portmod_mac_soft_reset_cb_lock.create(unit));

            /*
             *  pp alloc init
             */
            sal_memset(&create_data, 0, sizeof(create_data));
            create_data.first_element = 0;
            create_data.nof_elements = dnx_data_port.general.nof_pp_ports_get(unit);
            sal_strncpy(create_data.name, "PP_PORT_ALLOC", DNX_ALGO_RES_MNGR_MAX_NAME_LENGTH - 1);
            SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_alloc.alloc(unit, dnx_data_device.general.nof_cores_get(unit)));
            for (core_id = 0; core_id < dnx_data_device.general.nof_cores_get(unit); core_id++)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_alloc.create(unit, core_id, &create_data, NULL));
            }

            if (dnx_data_headers.
                system_headers.feature_get(unit, dnx_data_headers_system_headers_system_headers_ibch1_supported))
            {
                /*
                 *  PTC init
                 */
                sal_memset(&create_data, 0, sizeof(create_data));
                create_data.first_element = 0;
                create_data.nof_elements = dnx_data_port.general.nof_ptc_get(unit);
                sal_strncpy(create_data.name, "PTC_ALLOC", DNX_ALGO_RES_MNGR_MAX_NAME_LENGTH - 1);
                SHR_IF_ERR_EXIT(dnx_algo_port_db.ptc_alloc.alloc(unit, dnx_data_device.general.nof_cores_get(unit)));
                for (core_id = 0; core_id < dnx_data_device.general.nof_cores_get(unit); core_id++)
                {
                    SHR_IF_ERR_EXIT(dnx_algo_port_db.ptc_alloc.create(unit, core_id, &create_data, NULL));
                }
            }

            /*
             *  fabric init
             *  allocate db for each fabric link
             */
            nof_fabric_links = dnx_data_fabric.links.nof_links_get(unit);
            SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.alloc(unit, nof_fabric_links));

            /*
             * nif init
             * allocate db for each nif phy
             * allocate entries for fabric phys for ILKN over fabric
             */
            nof_nif_phys = dnx_data_nif.phys.nof_phys_get(unit) + dnx_data_fabric.links.nof_links_get(unit);
            SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.alloc(unit, nof_nif_phys));

            /*
             * ILKN init
             * allocate db for each ILKN id
             */
            if (dnx_data_nif.ilkn.feature_get(unit, dnx_data_nif_ilkn_is_supported))
            {
                nof_ilkn_if = dnx_data_nif.ilkn.ilkn_unit_nof_get(unit) * dnx_data_nif.ilkn.ilkn_unit_if_nof_get(unit);
                SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.alloc(unit, nof_ilkn_if));
            }

            /*
             *  out tm ports init
             *  allocate db for each core x out tm port
             */
            nof_cores = dnx_data_device.general.nof_cores_get(unit);
            nof_out_tm_ports = dnx_data_port.general.nof_out_tm_ports_get(unit);
            SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.alloc(unit, nof_cores, nof_out_tm_ports));

            /*
             *  pp dsp init
             *  allocate db for each core x PP-DSP
             */
            nof_cores = dnx_data_device.general.nof_cores_get(unit);
            nof_pp_dsp = dnx_data_port.general.nof_pp_dsp_get(unit);
            SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.alloc(unit, nof_cores, nof_pp_dsp));

            /*
             *  IN TM DB init
             *  allocate db for each core x in tm port
             */
            nof_cores = dnx_data_device.general.nof_cores_get(unit);
            nof_in_tm_ports = dnx_data_port.general.nof_in_tm_ports_get(unit);
            SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.alloc(unit, nof_cores, nof_in_tm_ports));

            /*
             *  counter port map init
             *  allocate db for counter port map
             */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.counter_port_map.alloc(unit, dnx_data_nif.prd.nof_prd_counters_get(unit)));

            if (dnx_data_nif.ofr.feature_get(unit, dnx_data_nif_ofr_is_supported))
            {
                /*
                 *  counter port map init
                 *  allocate db for counter port map
                 */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.rx_fifo_counter_port_map.alloc(unit));

                /*
                 *  counter port map init
                 *  allocate db for counter port map
                 */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.tx_fifo_counter_port_map.alloc(unit));
                /*
                 *  pp ports init
                 *  allocate db for each core x pp port
                 */
            }

            nof_cores = dnx_data_device.general.nof_cores_get(unit);
            nof_pp_ports = dnx_data_port.general.nof_pp_ports_get(unit);
            SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.alloc(unit, nof_cores, nof_pp_ports));
            /*
             *  sch init
             *  allocate db for each core x HR
             */
            nof_cores = dnx_data_device.general.nof_cores_get(unit);
            nof_hrs = dnx_data_sch.flow.nof_hr_get(unit);
            SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.alloc(unit, nof_cores, nof_hrs));
            /*
             *  sch IF init
             *  allocate sch interface for each nif phy, special tm interfaces.
             */
            nof_interfaces_handle0 = DNX_ALGO_PORT_TYPE_NOF;
            nof_interfaces_handle1 = 0;
            nof_interfaces_handle1 =
                UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_NIF_ETH_SIZE(unit));
            if (dnx_data_nif.ilkn.feature_get(unit, dnx_data_nif_ilkn_is_supported))
            {
                nof_interfaces_handle1 =
                    UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_NIF_ILKN_SIZE(unit));
            }
            nof_interfaces_handle1 =
                UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_ERP_SIZE(unit));
            nof_interfaces_handle1 =
                UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_RCY_MIRROR_SIZE(unit));
            nof_interfaces_handle1 =
                UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_OLP_SIZE(unit));
            nof_interfaces_handle1 =
                UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_OAMP_SIZE(unit));
            nof_interfaces_handle1 =
                UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_SAT_SIZE(unit));
            nof_interfaces_handle1 =
                UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_EVENTOR_SIZE(unit));
            nof_interfaces_handle1 =
                UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_RCY_SIZE(unit));

            if (dnx_data_nif.framer.feature_get(unit, dnx_data_nif_framer_is_supported))
            {
                nof_interfaces_handle1 =
                    UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_FLEXE_CLIENT_SIZE(unit));
                nof_interfaces_handle1 =
                    UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_FLEXE_SAR_SIZE(unit));
                nof_interfaces_handle1 =
                    UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_FLEXE_MAC_SIZE(unit));
            }
            nof_interfaces_handle1 =
                UTILEX_MAX(nof_interfaces_handle1, DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_CRPS_SIZE(unit));

            SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.alloc(unit, nof_interfaces_handle0, nof_interfaces_handle1));

            /*
             * tm interface init
             * allocate tm interface for each nif phy, special tm interfaces.
             */

            SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.alloc(unit, nof_interfaces_handle0, nof_interfaces_handle1));

            /*
             * Interface init
             * allocate tm interface for each nif phy, special tm interfaces.
             */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.alloc(unit, nof_interfaces_handle0, nof_interfaces_handle1));

            /*
             *  flexe client init
             *  allocate db for each flexe client
             */
            if (dnx_data_nif.framer.feature_get(unit, dnx_data_nif_framer_is_supported))
            {
                nof_clients = dnx_data_nif.mac_client.nof_clients_get(unit);
                SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.alloc(unit, nof_clients));

                nof_clients = dnx_data_nif.flexe.nof_clients_get(unit);
                SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.alloc(unit, nof_clients));

                nof_clients = dnx_data_nif.sar_client.nof_clients_get(unit);
                SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.alloc(unit, nof_clients));

                nof_nif_phys = dnx_data_nif.phys.nof_phys_get(unit);
                SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.phy.alloc(unit, nof_nif_phys));
            }

        }

        /*
         * Set default values for DBs
         */
        /** logicals init - set handles to -1 */
        for (logical_port = 0; logical_port < SOC_MAX_NUM_PORTS; logical_port++)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db_logical_init(unit, logical_port));
        }
        /** NIF init - init the NIF info DB */
        for (phy = 0; phy < nof_nif_phys; ++phy)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db_nif_init(unit, phy));
            if (dnx_data_nif.framer.feature_get(unit, dnx_data_nif_framer_is_supported))
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db_flexe_phy_init(unit, phy));
            }
        }
        if (dnx_data_nif.framer.feature_get(unit, dnx_data_nif_framer_is_supported))
        {
            /** FlexE client db init */
            nof_clients = dnx_data_nif.flexe.nof_clients_get(unit);
            for (channel = 0; channel < nof_clients; ++channel)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db_flexe_client_init(unit, channel));
            }
            /** FlexE mac db init */
            nof_clients = dnx_data_nif.mac_client.nof_clients_get(unit);
            for (channel = 0; channel < nof_clients; ++channel)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db_flexe_mac_init(unit, channel));
            }
            /** FlexE sar db init */
            nof_clients = dnx_data_nif.sar_client.nof_clients_get(unit);
            for (channel = 0; channel < nof_clients; ++channel)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db_flexe_sar_init(unit, channel));
            }
        }

        /** Interface init - init the NIF info DB */
        for (if_id.h0 = 0; if_id.h0 < nof_interfaces_handle0; ++if_id.h0)
        {
            for (if_id.h1 = 0; if_id.h1 < nof_interfaces_handle1; ++if_id.h1)
            {

                SHR_IF_ERR_EXIT(dnx_algo_port_db_interface_init(unit, if_id));
                SHR_IF_ERR_EXIT(dnx_algo_port_db_tm_interface_init(unit, if_id));
                SHR_IF_ERR_EXIT(dnx_algo_port_db_sch_if_init(unit, if_id));
            }
        }
        /** PRD Port to Profile Map init - init the port profile info DB */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.prd.alloc(unit));
        /** Set all entries to the default values of DNX_ALGO_PORT_INVALID*/
        SHR_IF_ERR_EXIT(dnx_algo_port_db_prd_port_to_profile_map_init_all_interfaces(unit));

        /*
         * Init SOC INFO
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_soc_info_init(unit));
        /** Create default template managers for ETH, PTCH1 and PTCH2 ports */
        SHR_IF_ERR_EXIT(dnx_algo_port_db_first_header_size_init_templates(unit));

    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * }
 */

/*
 * Add / Remove Port
 * {
 */
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_pp_port_allocate(
    int unit,
    uint32 flags,
    bcm_core_t core,
    bcm_trunk_t lag_id,
    uint32 *pp_port)
{
    dnx_algo_port_db_2d_handle_t pp_handle;
    uint32 supported_flags;
    uint32 res_mngr_flags = 0;
    SHR_FUNC_INIT_VARS(unit);
    pp_handle.h0 = core;
    pp_handle.h1 = DNX_ALGO_PORT_INVALID;

    /*
     * Verify
     */
    /** verify flags */
    supported_flags = DNX_ALGO_PORT_PP_PORT_ALLOCATE_F_LAG | DNX_ALGO_PORT_PP_PORT_ALLOCATE_F_WITH_ID;
    SHR_IF_ERR_EXIT_WITH_LOG(utilex_bitstream_mask_verify(&flags, &supported_flags, 1),
                             "pp port allocate does not support the requested flags 0x%x %s%s.\n", flags, EMPTY, EMPTY);
    /*
     * verify core
     */
    DNXCMN_CORE_VALIDATE(unit, core, 0);

    /** Find new free pp port */
    if (flags & DNX_ALGO_PORT_PP_PORT_ALLOCATE_F_WITH_ID)
    {
        res_mngr_flags = DNX_ALGO_RES_ALLOCATE_WITH_ID;
    }
    SHR_IF_ERR_EXIT_WITH_LOG(dnx_algo_port_db.
                             pp_alloc.allocate_single(unit, core, res_mngr_flags, NULL, (int *) pp_port),
                             "Free PP port not found in core %d\n%s%s", core, EMPTY, EMPTY);
    pp_handle.h1 = *pp_port;

    /*
     * allocate the port
     */
    /** mark as valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.ref_count.set(unit, pp_handle.h0, pp_handle.h1, 1));
    /** Set pp port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.pp_port.set(unit, pp_handle.h0, pp_handle.h1, *pp_port));
    /** Set core */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.core.set(unit, pp_handle.h0, pp_handle.h1, core));
    /** mark LLVP profile as invalid */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.ingress_llvp_profile_valid.set(unit, pp_handle.h0, pp_handle.h1, 0));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.egress_llvp_profile_valid.set(unit, pp_handle.h0, pp_handle.h1, 0));

    if (flags & DNX_ALGO_PORT_PP_PORT_ALLOCATE_F_LAG)
    {
        /** Set lag pp port */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.is_lag.set(unit, pp_handle.h0, pp_handle.h1, 1));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.lag_id.set(unit, pp_handle.h0, pp_handle.h1, lag_id));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_pp_port_free(
    int unit,
    bcm_core_t core,
    uint32 pp_port)
{
    dnx_algo_port_db_2d_handle_t pp_handle, other_pp_handle;
    bcm_port_t logical_port;
    SHR_FUNC_INIT_VARS(unit);

    /** create handle */
    pp_handle.h0 = core;
    pp_handle.h1 = pp_port;

    /*
     * Verify
     */
    /** verify pp port valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_pp_port_valid_verify(unit, core, pp_port));

    /** Make sure that there are no logical ports with the same handle */
    for (logical_port = 0; logical_port < SOC_MAX_NUM_PORTS; logical_port++)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.get(unit, logical_port, &other_pp_handle));

        /** Stop when found a free port */
        if (DNX_ALGO_PORT_2D_HANDLE_EQ(pp_handle, other_pp_handle))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "pp port used by logical port %d\n", logical_port);
        }
    }

   /** free resource */
    SHR_IF_ERR_EXIT(dnx_algo_port_db_pp_init(unit, pp_handle));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Add new NIF port
 * Relevant for both ethrnet port and interlaken ports.
 * (Configure NIF and ILKN data bases only)
 * \par DIRECT_INPUT:
 *   \param [in] unit - Relevant unit.
 *   \param [in] logical_port - required logical port.
 *   \param [in] nif_handle - nif DB handle
 *   \param [in] port_info - see dnx_algo_port_info_s
 *   \param [in] interface_offset - interface offset #
 *   \param [in] phys - bitmap of phy ports
 *   \param [in] phy_offset - offset for phys bitmap (used for ILKN over fabric)
 *   \param [in] ilkn_lanes - for ILKN only. bitmap of ILKN lanes (bits 0-23)
 *   \param [in] is_ilkn_over_fabric - for ILKN only. specify whether ILKN is over fabric.
 *   \param [in] is_elk - for ILKN only. specify whether ILKN it is elk interface.
 *   \param [in] is_flr_fw_support - for ETH only. specify whether Serdes FW supports FLR.
 *   \param [in] ext_txpi_enable - for ETH only. specify whether ext TXPI mode is enabled.
 *   \param [in] framer_channel - for ETH only. specify whether the framer channel.
 *
 * \par INDIRECT INPUT:
 *   * dnx data
 *   * internal algo port data base
 * \par DIRECT OUTPUT:
 *   see shr_error_e
 * \par INDIRECT OUTPUT
 *   * internal algo port data base
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_algo_port_nif_internal_add(
    int unit,
    bcm_port_t logical_port,
    int nif_handle,
    dnx_algo_port_info_s port_info,
    int interface_offset,
    bcm_pbmp_t phys,
    int phy_offset,
    bcm_pbmp_t ilkn_lanes,
    int is_ilkn_over_fabric,
    int is_elk,
    int is_flr_fw_support,
    int ext_txpi_enable,
    int framer_channel)
{
    int valid_nif_port;
    int phy;
    int first_phy;
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** set logical port as valid and set interface */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.set(unit, logical_port, DNX_ALGO_PORT_STATE_ADDED));

    /** set port type */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.set(unit, logical_port, port_info));

    /** Assign logical port to nif */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.set(unit, logical_port, nif_handle));

    /** Assign logical port to ilkn-id (just for ilkn of course) */
    if (DNX_ALGO_PORT_TYPE_IS_NIF_ILKN(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(ELK, L1)))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ilkn_handle.set(unit, logical_port, interface_offset));
    }

    /** set interface offset */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_offset.set(unit, logical_port, interface_offset));
    /*
     * If nif_handle_port is allocated -
     * assume that it's channelized interface with already configured NIF
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.valid.get(unit, nif_handle, &valid_nif_port));
    if (!valid_nif_port) /** i.e. master port */
    {
        /** set phys bitmap */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.phys.set(unit, nif_handle, phys));
        /** set first phy */
        _SHR_PBMP_FIRST(phys, first_phy);
        SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.first_phy.set(unit, nif_handle, first_phy));

        if (DNX_ALGO_PORT_TYPE_IS_NIF_ILKN(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(ELK, L1)))
        {
            /** set ILKN lanes **/
            SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.lanes.set(unit, interface_offset, ilkn_lanes));

            /** set ILKN over fabric indication **/
            SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.is_over_fabric.set(unit, interface_offset, is_ilkn_over_fabric));

            /** ILKN master and valid */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.valid.set(unit, interface_offset, 1));
            SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.master_logical_port.set(unit, interface_offset, logical_port));
            SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.is_elk.set(unit, interface_offset, is_elk));
        }
        if (DNX_ALGO_PORT_TYPE_IS_NIF_ETH(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(L1, MGMT))
            || DNX_ALGO_PORT_TYPE_IS_FLEXE_PHY(unit, port_info))
        {
            /** Set FLR Firmware satus **/
            SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.flr_fw_support.set(unit, nif_handle, is_flr_fw_support));
            /** Set TXPI mode */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.ext_txpi_enable.set(unit, nif_handle, ext_txpi_enable));
        }
        /*
         * set valid and master logical port for all phys
         * Relevant fields for non master phys are: valid, master_logical_port.
         */
        BCM_PBMP_ITER(phys, phy)
        {
            /** set as valid */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.valid.set(unit, phy + phy_offset, 1));

            /** set master port */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.master_logical_port.set(unit, phy + phy_offset, logical_port));
        }
    }
    /*
     * For L1 ETH port using Framer, need to init the FlexE PHY DB.
     */
    if (DNX_ALGO_PORT_TYPE_IS_FRAMER_PHY(unit, port_info))
    {
        flexe_handle = nif_handle;
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_phy_handle.set(unit, logical_port, flexe_handle));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.phy.valid.set(unit, flexe_handle, 1));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.phy.master_logical_port.set(unit, flexe_handle, logical_port));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.phy.channel.set(unit, flexe_handle, framer_channel));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_phy_active_get(
    int unit,
    int logical_phy,
    int *is_active)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.valid.get(unit, logical_phy, is_active));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_add(
    int unit,
    bcm_port_t logical_port,
    dnx_algo_port_if_add_t * info)
{
    int first_phy_port;
    int phy_offset = 0;
    dnx_algo_port_db_2d_handle_t interface_id;
    int is_master_port;
    dnx_algo_port_info_s port_info;
    dnx_algo_port_info_indicator_t indicator;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** verify logical port is free */
    SHR_IF_ERR_EXIT(dnx_algo_port_free_verify(unit, logical_port));

    /** add verify  */
    sal_memset(&indicator, 0, sizeof(dnx_algo_port_info_indicator_t));
    indicator.is_elk = info->ilkn_info.is_elk_if;
    indicator.is_stif = info->eth_info.is_stif;
    indicator.is_stif_data = info->eth_info.is_stif_data;
    indicator.is_flexe_phy = info->eth_info.is_flexe_phy;
    indicator.is_mgmt = info->eth_info.is_mgmt;
    indicator.is_cross_connect = info->is_cross_connect;

    SHR_IF_ERR_EXIT(dnx_algo_port_interface_to_port_info_get(unit, info->interface, &indicator, &port_info));

    SHR_IF_ERR_EXIT(dnx_algo_port_nif_add_verify(unit, logical_port, port_info, info));

    _SHR_PBMP_FIRST(info->phys, first_phy_port);

    if (DNX_ALGO_PORT_TYPE_IS_NIF_ILKN(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(ELK, L1)))
    {
        if (info->ilkn_info.is_ilkn_over_fabric)
        {
            phy_offset = dnx_data_port.general.fabric_phys_offset_get(unit);
            /** Add fabric links offset for NIF DB handle */
            first_phy_port += phy_offset;
        }
    }

    /** Verify channels just for TM ports */
    if (DNX_ALGO_PORT_TYPE_IS_ING_TM(unit, port_info))
    {
        /** in tm port Verify */
        SHR_IF_ERR_EXIT(dnx_algo_port_in_tm_port_free_verify(unit, port_info, info->core, info->tm_info.in_tm_port));

    }
    if (DNX_ALGO_PORT_TYPE_IS_PP_DSP(unit, port_info))
    {
        /** PP DSP Verify */
        SHR_IF_ERR_EXIT(dnx_algo_port_pp_dsp_free_verify(unit, port_info, info->core, info->tm_info.pp_dsp));

    }

    /*
     * channel is used for non NIF FLEXE interface only
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db_interface_id_get
                    (unit, port_info, info->core, info->interface_offset, &info->phys, -1,
                     &interface_id.h0, &interface_id.h1));

    /** Common Info Verify */
    SHR_IF_ERR_EXIT(dnx_algo_port_common_add_verify
                    (unit, logical_port, port_info, interface_id.h0, interface_id.h1, &info->common_info));

    if (DNX_ALGO_PORT_TYPE_IS_EGR_TM(unit, port_info))
    {
        /** out tm port Verify */
        SHR_IF_ERR_EXIT(dnx_algo_port_out_tm_add_verify(unit, port_info, info->core, info->tm_info.out_tm_port,
                                                        &info->tm_info, interface_id.h0, interface_id.h1));

    }

    if (DNX_ALGO_PORT_TYPE_IS_TM(unit, port_info))
    {
        /** TM Info Verify */
        SHR_IF_ERR_EXIT(dnx_algo_port_tm_add_verify
                        (unit, logical_port, port_info, interface_id.h0, interface_id.h1, &info->tm_info));
    }

    /** channel verify */
    if (info->common_info.is_channelized)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_channel_free_verify(unit, logical_port, interface_id,
                                                          info->common_info.out_channel, TRUE));
        SHR_IF_ERR_EXIT(dnx_algo_port_channel_free_verify(unit, logical_port, interface_id,
                                                          info->common_info.in_channel, FALSE));
    }

    /*
     * Add to data base
     */

    /** NIF PORT*/
    SHR_IF_ERR_EXIT(dnx_algo_port_nif_internal_add
                    (unit, logical_port, first_phy_port, port_info, info->interface_offset, info->phys,
                     phy_offset, info->ilkn_info.ilkn_lanes, info->ilkn_info.is_ilkn_over_fabric,
                     info->ilkn_info.is_elk_if, info->eth_info.is_flr_fw_support,
                     info->eth_info.ext_txpi_enable, info->eth_info.framer_channel));

    /** Add general interface DataBase */
    SHR_IF_ERR_EXIT(dnx_algo_port_common_add(unit, logical_port, info->core, &info->common_info, interface_id));

    if (DNX_ALGO_PORT_TYPE_IS_TM(unit, port_info))
    {
        /** TM PORT */
        SHR_IF_ERR_EXIT(dnx_algo_port_tm_add(unit, logical_port, info->core, &info->tm_info, interface_id));
    }

    if (DNX_ALGO_PORT_TYPE_IS_E2E_SCH(unit, port_info))
    {
        /** TM PORT */
        SHR_IF_ERR_EXIT(dnx_algo_port_sch_add(unit, logical_port, info->core, &info->tm_info, interface_id));
    }

    /*
     * Set SOC INFO.
     * Until TDM mode will be set assume the port is not TDM.
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_is_master_get(unit, logical_port, 0, &is_master_port));
    SHR_IF_ERR_EXIT(dnx_algo_port_soc_info_add
                    (unit, logical_port, is_master_port, port_info, info->phys, info->common_info.tdm_mode));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Add new TM port
 *   Relevant for any port type which has tm port (nif, cpu, ..)
 *
 * \param [in] unit - Relevant unit.
 * \param [in] logical_port - logical port.
 * \param [in] core - core ID.
 * \param [in] info - Switch port info.
 * \param [in] interface_id - See macros DNX_ALGO_PORT_TM_INTERFACE_*
 *
 * \return
 *   If zero (_SHR_E_NONE), then no error was encountered.
 *   Otherwise, see shr_error_e
 * \remark
 *   * INDIRECT INPUT:
 *   * * dnx data
 *   * * internal algo port data base
 *   * INDIRECT OUTPUT
 *   * * internal algo port data base
 * \see
 *   * None
 */
static shr_error_e
dnx_algo_port_common_add(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t core,
    dnx_algo_port_common_add_t * info,
    dnx_algo_port_db_2d_handle_t interface_id)
{
    int valid_interface;
    dnx_algo_port_info_s master_port_info, port_info;

    SHR_FUNC_INIT_VARS(unit);

    /** Assign logical port to general interface database */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.set(unit, logical_port, &interface_id));

    /** Set channel_id */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.in_channel.set(unit, logical_port, info->in_channel));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.out_channel.set(unit, logical_port, info->out_channel));

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    /*
     * If interface_id is allocated -
     * assume that it's channelized interface with already configured interface
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.valid.get(unit, interface_id.h0, interface_id.h1, &valid_interface));
    if (!valid_interface) /** i.e. master port */
    {
        /** set as valid */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.valid.set(unit, interface_id.h0, interface_id.h1, 1));
        /** Set interface core */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.core.set(unit, interface_id.h0, interface_id.h1, core));
        /** set master logical port */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        master_logical_port.set(unit, interface_id.h0, interface_id.h1, logical_port));

        /** Set is channelized */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        is_channelized.set(unit, interface_id.h0, interface_id.h1, info->is_channelized));
        /** Set is ingress interleave */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.is_ingress_interleave.set
                        (unit, interface_id.h0, interface_id.h1, info->is_ingress_interleave));

        /** TDM interface mode */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        tdm_mode.set(unit, interface_id.h0, interface_id.h1, info->if_tdm_mode));
        /** set tdm master port to be invalid */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        master_tdm_logical_port.set(unit, interface_id.h0, interface_id.h1, DNX_ALGO_PORT_INVALID));
        /** set non-tdm master port to be this port - assuming it's non tdm port for now */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        master_non_tdm_logical_port.set(unit, interface_id.h0, interface_id.h1, logical_port));

    }
    else
    {
        int if_master_port;

        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        master_logical_port.get(unit, interface_id.h0, interface_id.h1, &if_master_port));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, if_master_port, &master_port_info));

        /*
         * Set master_logical_port, when adding first L2 port
         */
        if (!DNX_ALGO_PORT_TYPE_IS_L1(unit, port_info) && DNX_ALGO_PORT_TYPE_IS_L1(unit, master_port_info))
        {
            /** set non-tdm master port to be this port - assuming it's non tdm port for now */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                            master_non_tdm_logical_port.set(unit, interface_id.h0, interface_id.h1, logical_port));
        }
    }

    /*
     * Configure TDM mode
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_tdm_set(unit, logical_port, info->tdm_mode));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  Free ptc when remove port.
 *  In case of mirror port, free only if it is the last one, since all mirror-ports has the same ptc
 */
static shr_error_e
dnx_algo_port_ptc_free(
    int unit,
    bcm_core_t core,
    bcm_port_t logical_port,
    int free_skip)
{
    int ptc;
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_headers.
        system_headers.feature_get(unit, dnx_data_headers_system_headers_system_headers_ibch1_supported))
    {
        /** Release PTC port Data Base */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ptc.get(unit, logical_port, &ptc));
        if ((ptc != DNX_ALGO_PORT_HANDLE_INVALID) && (free_skip == FALSE))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.ptc_alloc.free_single(unit, core, ptc, NULL));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  check if pp_port and ptc allocation (or deallocation) can be skipped, due to prev mirror port that already configured.
 */
static shr_error_e
algo_port_mgmt_pp_mirror_rcy_allocation_handle_skip(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t core,
    dnx_algo_port_info_s port_info,
    int *alloc_skip,
    bcm_port_t * reference_port)
{
    bcm_pbmp_t all_rcy_mirror_ports;
    int rcy_mirror_port_i;
    SHR_FUNC_INIT_VARS(unit);

    *alloc_skip = FALSE;

    if (dnx_data_headers.
        system_headers.feature_get(unit, dnx_data_headers_system_headers_system_headers_ibch1_supported))
    {
        /** all mirror rcy has same PTC and same pp_port. allocate new just in the first port. */
        if (DNX_ALGO_PORT_TYPE_IS_RCY_MIRROR(unit, port_info))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_logicals_get
                            (unit, core, DNX_ALGO_PORT_LOGICALS_TYPE_RCY_MIRROR, 0, &all_rcy_mirror_ports));
            /** if rcy-mirror port already exist, don't alloc and get its value back */
            BCM_PBMP_ITER(all_rcy_mirror_ports, rcy_mirror_port_i)
            {
                if (rcy_mirror_port_i != logical_port)
                {
                    *alloc_skip = TRUE;
                    /** use the first port found to be the pp_port reference port */
                    *reference_port = rcy_mirror_port_i;
                    break;
                }
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  alloc ptc when adding port.
 *  In case of mirror port, alloc only if it is the first port, since all mirror-ports has the same ptc.
 */
static shr_error_e
dnx_algo_port_ptc_alloc(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t core,
    int alloc_skip,
    bcm_port_t master_logical_port)
{
    int ptc;
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_headers.
        system_headers.feature_get(unit, dnx_data_headers_system_headers_system_headers_ibch1_supported))
    {
        if (alloc_skip == FALSE)
        {
            /** allocate PTC */
            SHR_IF_ERR_EXIT_WITH_LOG(dnx_algo_port_db.ptc_alloc.allocate_single(unit, core, 0, NULL, &ptc),
                                     "Free PTC not found in core %d\n%s%s", core, EMPTY, EMPTY);

        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ptc.get(unit, master_logical_port, &ptc));
        }
        /** set PTC in database */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ptc.set(unit, logical_port, ptc));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Add new TM port
 *   Relevant for any port type which has tm port (nif, cpu, ..)
 *
 * \param [in] unit - Relevant unit.
 * \param [in] logical_port - logical port.
 * \param [in] core - core ID.
 * \param [in] info - Switch port info.
 * \param [in] interface_id - See macros DNX_ALGO_PORT_TM_INTERFACE_*
 *
 * \return
 *   If zero (_SHR_E_NONE), then no error was encountered.
 *   Otherwise, see shr_error_e
 * \remark
 *   * INDIRECT INPUT:
 *   * * dnx data
 *   * * internal algo port data base
 *   * INDIRECT OUTPUT
 *   * * internal algo port data base
 * \see
 *   * None
 */
static shr_error_e
dnx_algo_port_tm_add(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t core,
    dnx_algo_port_tm_add_t * info,
    dnx_algo_port_db_2d_handle_t interface_id)
{
    int valid_tm_interface;
    uint32 pp_port = DNX_ALGO_PORT_TYPE_INVALID;
    dnx_algo_port_db_2d_handle_t out_tm_handle, pp_handle;
    dnx_algo_port_db_2d_handle_t pp_dsp_handle, in_tm_handle;
    dnx_algo_port_info_s port_info;
    int out_tm_port_valid = 0, in_tm_port_valid = 0;
    bcm_port_t master_logical_port;
    int pp_port_valid;
    int i;
    int mirror_pp_alloc_skip = FALSE;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    /** Assign logical port to tm interface */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.tm_interface_handle.set(unit, logical_port, &interface_id));

    /*
     * Configure IN TM port
     */
    if (DNX_ALGO_PORT_TYPE_IS_ING_TM(unit, port_info))
    {
        /** Assign logical port to in tm port DB */
        in_tm_handle.h0 = core;
        in_tm_handle.h1 = info->in_tm_port;
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.in_tm_handle.set(unit, logical_port, &in_tm_handle));

        SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.ref_count.get(unit, in_tm_handle.h0, in_tm_handle.h1,
                                                             &in_tm_port_valid));
        for (i = 0; i < info->in_tm_port_nof; i++)
        {
            if (!in_tm_port_valid)
            {
                /** mark as valid */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.ref_count.set(unit, in_tm_handle.h0, in_tm_handle.h1 + i, 1));
                /** Set IN TM port */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.in_tm_port.set(unit, in_tm_handle.h0, in_tm_handle.h1 + i,
                                                                      info->in_tm_port));
                /** Set core */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.core.set(unit, in_tm_handle.h0, in_tm_handle.h1 + i, core));
                /** Set number of IN TM ports */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.in_tm_port_nof.set(unit, in_tm_handle.h0, in_tm_handle.h1 + i,
                                                                          info->in_tm_port_nof));
                /** set master port (of IN TM DB!)*/
                SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.master_logical_port.set(unit, in_tm_handle.h0,
                                                                               in_tm_handle.h1 + i, logical_port));
            }
            else
            {
                /** increment reference  count */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.ref_count.inc(unit, in_tm_handle.h0, in_tm_handle.h1 + i, 1));
            }
        }

    }

    /*
     * Configure OUT TM port
     */

    if (DNX_ALGO_PORT_TYPE_IS_PP_DSP(unit, port_info))
    {
        /** Assign logical port to PP-DSP */
        pp_dsp_handle.h0 = core;
        pp_dsp_handle.h1 = info->pp_dsp;
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_dsp_handle.set(unit, logical_port, &pp_dsp_handle));

        /** mark as valid */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.valid.set(unit, pp_dsp_handle.h0, pp_dsp_handle.h1, 1));
        /** Set pp dsp */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.pp_dsp.set(unit, pp_dsp_handle.h0, pp_dsp_handle.h1, info->pp_dsp));
        /** Set core */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.core.set(unit, pp_dsp_handle.h0, pp_dsp_handle.h1, core));
        /** set master port (of pp dsp port!)*/
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.master_logical_port.set(unit, pp_dsp_handle.h0, pp_dsp_handle.h1,
                                                                           logical_port));
        /** Egress queuing port only */
        if (DNX_ALGO_PORT_TYPE_IS_EGR_TM(unit, port_info))
        {
            /** Assign logical port to out tm port */
            out_tm_handle.h0 = core;
            out_tm_handle.h1 = info->out_tm_port;
            SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.out_tm_handle.set(unit, pp_dsp_handle.h0, pp_dsp_handle.h1,
                                                                         &out_tm_handle));

            SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.ref_count.get(unit, out_tm_handle.h0, out_tm_handle.h1,
                                                                  &out_tm_port_valid));
            if (!out_tm_port_valid)
            {
                /** mark as valid */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.ref_count.set(unit, out_tm_handle.h0, out_tm_handle.h1, 1));
                /** Set out tm port */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.out_tm_port.set(unit, out_tm_handle.h0, out_tm_handle.h1,
                                                                        info->out_tm_port));
                /** Set core */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.core.set(unit, out_tm_handle.h0, out_tm_handle.h1, core));
                /** set master port (of out tm port!)*/
                SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.master_logical_port.set(unit,
                                                                                out_tm_handle.h0, out_tm_handle.h1,
                                                                                logical_port));

                /** Set base_q_pair */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.base_q_pair.set(unit, out_tm_handle.h0, out_tm_handle.h1,
                                                                        info->base_q_pair));
                /** Set number of port priorities */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.priorities.set(unit, out_tm_handle.h0, out_tm_handle.h1,
                                                                       info->num_priorities));
                SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.is_mc.set(unit, out_tm_handle.h0, out_tm_handle.h1,
                                                                  info->is_mc));
            }
            else
            {
                /** increment reference  count */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.ref_count.inc(unit, out_tm_handle.h0, out_tm_handle.h1, 1));
            }
        }

    }

    /*
     * If tm_interface_id is allocated -
     * assume that it's channelized interface with already configured interface
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                    valid.get(unit, interface_id.h0, interface_id.h1, &valid_tm_interface));
    if (!valid_tm_interface) /** i.e. master port */
    {
        dnx_algo_port_db_2d_handle_t logical_interface_id;

        /** set as valid */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.valid.set(unit, interface_id.h0, interface_id.h1, 1));
        /** Set is egress interleave */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.is_egress_interleave.set
                        (unit, interface_id.h0, interface_id.h1, info->is_egress_interleave));
        /** Set egress interface */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                        egr_if.set(unit, interface_id.h0, interface_id.h1, info->egress_interface));
        /** Set channelized egress interface */
        if (dnx_data_egr_queuing_v1.egress_interfaces.feature_get(unit,
                                                                  dnx_data_egr_queuing_v1_egress_interfaces_channelized_interface_mapping))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                            ch_egr_if.set(unit, interface_id.h0, interface_id.h1, info->channelized_egress_interface));
        }

        /** set master logical port */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                        master_logical_port.set(unit, interface_id.h0, interface_id.h1, logical_port));

        /** point to this TM interface from (general) interface */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &logical_interface_id));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        tm_interface_handle.set(unit, logical_interface_id.h0, logical_interface_id.h1, &interface_id));

    }
    else
    {
        int if_master_port;
        dnx_algo_port_info_s master_port_info;
        SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                        master_logical_port.get(unit, interface_id.h0, interface_id.h1, &if_master_port));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, if_master_port, &master_port_info));

        /*
         * Set master_logical_port, is_egress_interleave and egr_if when adding first L2 port
         */
        if (!DNX_ALGO_PORT_TYPE_IS_L1(unit, port_info) && DNX_ALGO_PORT_TYPE_IS_L1(unit, master_port_info))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                            master_logical_port.set(unit, interface_id.h0, interface_id.h1, logical_port));

            SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                            is_egress_interleave.set(unit, interface_id.h0, interface_id.h1,
                                                     info->is_egress_interleave));
            SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                            egr_if.set(unit, interface_id.h0, interface_id.h1, info->egress_interface));

            /** Set channelized egress interface */
            if (dnx_data_egr_queuing_v1.egress_interfaces.feature_get(unit,
                                                                      dnx_data_egr_queuing_v1_egress_interfaces_channelized_interface_mapping))
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.ch_egr_if.set(unit, interface_id.h0, interface_id.h1,
                                                                            info->channelized_egress_interface));
            }
        }
    }

    /*
     * Configure PP port
     */
    if (DNX_ALGO_PORT_TYPE_IS_PP(unit, port_info, 0 /* not in lag */ ))
    {
        /*
         * This code assumes that any PP port is also TM port.
         * This assumption is correct with the current code..
         * If this assumption is ever violated, the code below should be adjusted
         */
        /** it is not allowed to have 2 ports with the same PP DSP */
        pp_port_valid = in_tm_port_valid && !DNX_ALGO_PORT_TYPE_IS_PP_DSP(unit, port_info);

        /** alloc only single pp port and ptc for mirror-rcy ports. check if alloc can be skipped */
        if (dnx_data_headers.
            system_headers.feature_get(unit, dnx_data_headers_system_headers_system_headers_ibch1_supported))
        {
            SHR_IF_ERR_EXIT(algo_port_mgmt_pp_mirror_rcy_allocation_handle_skip
                            (unit, logical_port, core, port_info, &mirror_pp_alloc_skip, &master_logical_port));
            pp_port_valid = pp_port_valid | mirror_pp_alloc_skip;
        }

        if (!pp_port_valid)
        {
            /*
             * Allocate new pp port
             */
            SHR_IF_ERR_EXIT(dnx_algo_port_pp_port_allocate(unit, 0, core, 0, &pp_port));
            pp_handle.h0 = core;
            pp_handle.h1 = pp_port;

            /** set master port (of pp port!)*/
            SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.master_logical_port.set(unit, pp_handle.h0, pp_handle.h1,
                                                                        logical_port));
        }
        else
        {
            if (mirror_pp_alloc_skip == TRUE)
            {
                /** nothing to do - master  port already updated */
            }
            else if (in_tm_port_valid)
            {
                /** get master port (from IN TM DB) */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.master_logical_port.get(unit, in_tm_handle.h0, in_tm_handle.h1,
                                                                               &master_logical_port));
            }
            else
            {
                /** PP DSP valid */
                /** get master port (from PP DSP DB) */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.master_logical_port.get(unit, pp_dsp_handle.h0,
                                                                                   pp_dsp_handle.h1,
                                                                                   &master_logical_port));
            }
            /** Get the handle from master PP port */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.get(unit, master_logical_port, &pp_handle));

            /** increment reference count in PP DB */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.ref_count.inc(unit, pp_handle.h0, pp_handle.h1, 1));

        }

        /** Assign logical port to pp port */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.set(unit, logical_port, &pp_handle));

        SHR_IF_ERR_EXIT(dnx_algo_port_ptc_alloc(unit, logical_port, core, mirror_pp_alloc_skip, master_logical_port));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Add new sch port
 *   Relevant for any port type which has sch database (nif, cpu, ..)
 *
 * \param [in] unit - Relevant unit.
 * \param [in] logical_port - logical port.
 * \param [in] core - core ID.
 * \param [in] info - Switch port info.
 * \param [in] interface_id - See macros DNX_ALGO_PORT_TM_INTERFACE_*
 *
 * \return
 *   If zero (_SHR_E_NONE), then no error was encountered.
 *   Otherwise, see shr_error_e
 * \remark
 *   * INDIRECT INPUT:
 *   * * dnx data
 *   * * internal algo port data base
 *   * INDIRECT OUTPUT
 *   * * internal algo port data base
 * \see
 *   * None
 */
static shr_error_e
dnx_algo_port_sch_add(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t core,
    dnx_algo_port_tm_add_t * info,
    dnx_algo_port_db_2d_handle_t interface_id)
{
    int valid_sch_interface;
    dnx_algo_port_db_2d_handle_t sch_handle;
    int i;
    int ref_count = 0;

    SHR_FUNC_INIT_VARS(unit);

    /** Assign logical port to sch */
    sch_handle.h0 = core;
    sch_handle.h1 = info->base_hr;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_handle.set(unit, logical_port, &sch_handle));

    /** Assign logical port to sch interface */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_if_handle.set(unit, logical_port, &interface_id));

    /*
     * Configure SCH
     */

    /** Configure SCH info for all port's HRs */
    for (i = 0; i < info->sch_priorities; i++)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.ref_count.get(unit, sch_handle.h0, sch_handle.h1 + i, &ref_count));

        if (ref_count == 0)
        {
            /** mark as valid */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.ref_count.set(unit, sch_handle.h0, sch_handle.h1 + i, 1));
            /** Set base_hr */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.base_hr.set(unit, sch_handle.h0, sch_handle.h1 + i, info->base_hr));
            /** Set number of sch priorities */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.sch_priorities.set(unit, sch_handle.h0, sch_handle.h1 + i,
                                                                    info->sch_priorities));
            /** set master port */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.master_logical_port.set(unit, sch_handle.h0, sch_handle.h1 + i,
                                                                         logical_port));
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.ref_count.inc(unit, sch_handle.h0, sch_handle.h1 + i, 1));

        }
    }

    /** Configure SCH interface info */

    /*
     * If sch_interface is valid -
     * assume that it's channelized interface with already configured interface
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.
                    valid.get(unit, interface_id.h0, interface_id.h1, &valid_sch_interface));
    if (!valid_sch_interface) /** i.e. master port */
    {
        /** set as valid */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.valid.set(unit, interface_id.h0, interface_id.h1, TRUE));
        /** Set priority propagation */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.
                        priority_propagation_enable.set(unit, interface_id.h0, interface_id.h1,
                                                        info->sch_priority_propagation_enable));
        /** set master logical port */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.
                        master_logical_port.set(unit, interface_id.h0, interface_id.h1, logical_port));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_port_flexe_add(
    int unit,
    bcm_port_t logical_port,
    int flexe_index)
{
    dnx_algo_port_info_s port_info;
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);

    flexe_handle = flexe_index;

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FLEXE_CLIENT(unit, port_info))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_client_handle.set(unit, logical_port, flexe_handle));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.client_index.set(unit, flexe_handle, flexe_index));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.master_logical_port.set(unit, flexe_handle, logical_port));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.valid.set(unit, flexe_handle, 1));
    }
    else if (DNX_ALGO_PORT_TYPE_IS_FRAMER_MAC(unit, port_info, TRUE, TRUE))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_mac_handle.set(unit, logical_port, flexe_handle));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.client_index.set(unit, flexe_handle, flexe_index));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.master_logical_port.set(unit, flexe_handle, logical_port));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.valid.set(unit, flexe_handle, 1));
    }
    else if (DNX_ALGO_PORT_TYPE_IS_FRAMER_SAR(unit, port_info, TRUE))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_sar_handle.set(unit, logical_port, flexe_handle));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.client_index.set(unit, flexe_handle, flexe_index));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.master_logical_port.set(unit, flexe_handle, logical_port));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.valid.set(unit, flexe_handle, 1));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.virtual_flexe_channel.set(unit, flexe_handle, flexe_index));
    }

    /*
     * Set channel on logical DB
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.in_channel.set(unit, logical_port, flexe_index));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.out_channel.set(unit, logical_port, flexe_index));

exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h
 */
shr_error_e
dnx_algo_port_db_interface_id_get(
    int unit,
    dnx_algo_port_info_s port_info,
    bcm_core_t core,
    int interface_offset,
    bcm_pbmp_t * phys,
    int flexe_client_channel,
    int *if_id_h0,
    int *if_id_h1)
{
    SHR_FUNC_INIT_VARS(unit);

    if (DNX_ALGO_PORT_TYPE_IS_NIF(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(ELK, STIF, L1, FLEXE, MGMT)))
    {
        if (DNX_ALGO_PORT_TYPE_IS_NIF_ILKN(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(ELK, L1)))
        {
            *if_id_h0 = DNX_ALGO_PORT_TYPE_NIF_ILKN;
            *if_id_h1 = interface_offset;
        }
        else
        {
            *if_id_h0 = DNX_ALGO_PORT_TYPE_NIF_ETH;
            _SHR_PBMP_FIRST(*phys, *if_id_h1);
        }
    }
    else
    {
        /*
         * Get interface id and port type
         */
        *if_id_h0 = port_info.port_type;
        switch (port_info.port_type)
        {
            case DNX_ALGO_PORT_TYPE_CPU:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_CPU(unit, core);
                break;
            }
            case DNX_ALGO_PORT_TYPE_RCY:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_RCY(unit, core, interface_offset);
                break;
            }
            case DNX_ALGO_PORT_TYPE_RCY_MIRROR:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_RCY_MIRROR(unit, core);
                break;
            }
            case DNX_ALGO_PORT_TYPE_ERP:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_ERP(unit, core);
                break;
            }
            case DNX_ALGO_PORT_TYPE_OLP:
            {
                if (interface_offset == -1)
                {
                    /** set interface offset to 0 when the device has only a single OLP interface */
                    interface_offset = 0;
                }
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_OLP(unit, core, interface_offset);
                break;
            }
            case DNX_ALGO_PORT_TYPE_OAMP:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_OAMP(unit, core);
                break;
            }
            case DNX_ALGO_PORT_TYPE_SAT:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_SAT(unit, core);
                break;
            }
            case DNX_ALGO_PORT_TYPE_EVENTOR:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_EVENTOR(unit, core);
                break;
            }
            case DNX_ALGO_PORT_TYPE_FLEXE_CLIENT:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_FLEXE_CLIENT(unit, flexe_client_channel);
                break;
            }
            case DNX_ALGO_PORT_TYPE_FRAMER_MAC:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_FLEXE_MAC(unit, flexe_client_channel);
                break;
            }
            case DNX_ALGO_PORT_TYPE_FRAMER_SAR:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_FLEXE_SAR(unit, flexe_client_channel);
                break;
            }

            case DNX_ALGO_PORT_TYPE_SCH_ONLY:
            {
                int base_interface, index, valid;

                *if_id_h1 = -1;

                base_interface = DNX_ALGO_PORT_INTERFACE_HANDLE1_BASE_FOR_SCH_ONLY(unit, core);
                for (index = 0; index < dnx_data_sch.interface.nof_sch_interfaces_get(unit); index++)
                {
                    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.
                                    valid.get(unit, DNX_ALGO_PORT_TYPE_SCH_ONLY, base_interface + index, &valid));
                    if (!valid)
                    {
                        *if_id_h1 = base_interface + index;
                        break;
                    }

                }

                if (*if_id_h1 == -1)
                {
                    SHR_ERR_EXIT(_SHR_E_RESOURCE, "Cannot allocate SCH ONLY interface id\n");

                }
                break;
            }
            case DNX_ALGO_PORT_TYPE_CRPS:
            {
                *if_id_h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_CRPS(unit, core);
                break;
            }
            case DNX_ALGO_PORT_TYPE_OTN_PHY:
            {
                _SHR_PBMP_FIRST(*phys, *if_id_h1);
                break;
            }
            default:
            {
                SHR_ERR_EXIT(_SHR_E_INTERNAL, "Unsupported interface type for port\n");
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - input verification for special interface adding
 *
 */
static shr_error_e
dnx_algo_port_special_interface_add_verify(
    int unit,
    bcm_port_t logical_port,
    dnx_algo_port_special_interface_add_t * info)
{
    bcm_core_t core;
    dnx_algo_port_db_2d_handle_t cpu_interface_id, rcy_interface_id;
    int interface_offset;
    dnx_algo_port_db_2d_handle_t interface_id;
    dnx_algo_port_info_s port_info;
    dnx_algo_port_info_indicator_t indicator;

    SHR_FUNC_INIT_VARS(unit);
    /*
     * Get tm interface id and port type
     */
    sal_memset(&indicator, 0, sizeof(dnx_algo_port_info_indicator_t));
    indicator.is_flexe_mac = info->framer_info.is_flexe_mac;
    indicator.is_flexe_sar = info->framer_info.is_flexe_sar;
    indicator.is_otn_sar = info->framer_info.is_otn_sar;
    indicator.is_cross_connect = info->framer_info.is_cross_connet;
    indicator.is_stat_only = info->framer_info.is_stat_only;
    SHR_IF_ERR_EXIT(dnx_algo_port_interface_to_port_info_get(unit, info->interface, &indicator, &port_info));

    SHR_IF_ERR_EXIT(dnx_algo_port_db_interface_id_get
                    (unit, port_info, info->core, info->interface_offset, NULL, info->framer_info.client_channel,
                     &interface_id.h0, &interface_id.h1));

    /*
     * Verify
     */
    /** Verify logical port is free */
    SHR_IF_ERR_EXIT(dnx_algo_port_free_verify(unit, logical_port));
    /** Core verify*/
    DNXCMN_CORE_VALIDATE(unit, info->core, 0);

    /** Common Info Verify */
    SHR_IF_ERR_EXIT(dnx_algo_port_common_add_verify
                    (unit, logical_port, port_info, interface_id.h0, interface_id.h1, &info->common_info));

    if (DNX_ALGO_PORT_TYPE_IS_ING_TM(unit, port_info))
    {
        /** IN TM port Verify */
        SHR_IF_ERR_EXIT(dnx_algo_port_in_tm_port_free_verify(unit, port_info, info->core, info->tm_info.in_tm_port));

    }
    if (DNX_ALGO_PORT_TYPE_IS_PP_DSP(unit, port_info))
    {
        /** PP DSP Verify */
        SHR_IF_ERR_EXIT(dnx_algo_port_pp_dsp_free_verify(unit, port_info, info->core, info->tm_info.pp_dsp));

    }
    if (DNX_ALGO_PORT_TYPE_IS_EGR_TM(unit, port_info))
    {
        /** out tm port Verify */
        SHR_IF_ERR_EXIT(dnx_algo_port_out_tm_add_verify(unit, port_info, info->core, info->tm_info.out_tm_port,
                                                        &info->tm_info, interface_id.h0, interface_id.h1));
    }

    if (DNX_ALGO_PORT_TYPE_IS_TM(unit, port_info))
    {
        /** Verify interface offset */
        SHR_IF_ERR_EXIT(dnx_algo_port_special_interface_offset_verify(unit, port_info, info->interface_offset));

        /** TM Info Verify */
        SHR_IF_ERR_EXIT(dnx_algo_port_tm_add_verify
                        (unit, logical_port, port_info, interface_id.h0, interface_id.h1, &info->tm_info));
    }
    /** Verify channel */
    if (info->common_info.is_channelized)
    {
        if (DNX_ALGO_PORT_TYPE_IS_CPU(unit, port_info))
        {
            /** special check for cpu - make sure that the channel is not used on all cores */
            DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core)
            {
                cpu_interface_id.h0 = interface_id.h0;
                cpu_interface_id.h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_CPU(unit, core);
                SHR_IF_ERR_EXIT(dnx_algo_port_channel_free_verify
                                (unit, logical_port, cpu_interface_id, info->common_info.out_channel, TRUE));
                SHR_IF_ERR_EXIT(dnx_algo_port_channel_free_verify
                                (unit, logical_port, cpu_interface_id, info->common_info.in_channel, FALSE));
            }
        }
        else if (DNX_ALGO_PORT_TYPE_IS_RCY(unit, port_info))
        {
            /** special check for recycle - make sure that the channel is not used on all interface offsets */
            for (interface_offset = 0;
                 interface_offset < dnx_data_egr_queuing.params.nof_egr_rcy_interfaces_get(unit); interface_offset++)
            {
                rcy_interface_id.h0 = interface_id.h0;
                rcy_interface_id.h1 = DNX_ALGO_PORT_INTERFACE_HANDLE1_FOR_RCY(unit, info->core, interface_offset);
                SHR_IF_ERR_EXIT_WITH_LOG(dnx_algo_port_channel_free_verify
                                         (unit, logical_port, rcy_interface_id, info->common_info.in_channel, FALSE),
                                         "Port %d in channel %d is already used by one of the RCY interfaces. (RCY interfaces shared the channel ids).\n%s",
                                         logical_port, info->common_info.in_channel, EMPTY);
                SHR_IF_ERR_EXIT_WITH_LOG(dnx_algo_port_channel_free_verify
                                         (unit, logical_port, rcy_interface_id, info->common_info.out_channel, TRUE),
                                         "Port %d out channel %d is already used by one of the RCY interfaces. (RCY interfaces shared the channel ids).\n%s",
                                         logical_port, info->common_info.out_channel, EMPTY);
            }
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_channel_free_verify(unit, logical_port, interface_id,
                                                              info->common_info.out_channel, TRUE));
            SHR_IF_ERR_EXIT(dnx_algo_port_channel_free_verify(unit, logical_port, interface_id,
                                                              info->common_info.in_channel, FALSE));
        }
    }
    if (DNX_ALGO_PORT_TYPE_IS_E2E_SCH(unit, port_info))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_sch_add_verify(unit, logical_port, port_info, info->core, interface_id,
                                                     &info->tm_info));
    }

    if (DNX_ALGO_PORT_TYPE_IS_MC(unit, port_info))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_mc_add_verify(unit, logical_port, port_info, &info->common_info));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_special_interface_add(
    int unit,
    bcm_port_t logical_port,
    dnx_algo_port_special_interface_add_t * info)
{
    dnx_algo_port_db_2d_handle_t interface_id;
    dnx_algo_port_info_s port_info;
    bcm_pbmp_t dummy_pbmp;
    int is_master_port;
    dnx_algo_port_info_indicator_t indicator;

    SHR_FUNC_INIT_VARS(unit);

    /** Verify */
    SHR_INVOKE_VERIFY_DNXC(dnx_algo_port_special_interface_add_verify(unit, logical_port, info));

    sal_memset(&indicator, 0, sizeof(dnx_algo_port_info_indicator_t));
    indicator.is_flexe_mac = info->framer_info.is_flexe_mac;
    indicator.is_flexe_sar = info->framer_info.is_flexe_sar;
    indicator.is_otn_sar = info->framer_info.is_otn_sar;
    indicator.is_cross_connect = info->framer_info.is_cross_connet;
    indicator.is_stat_only = info->framer_info.is_stat_only;
    indicator.is_mc = info->tm_info.is_mc;
    /*
     * Get interface id and port type
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_interface_to_port_info_get(unit, info->interface, &indicator, &port_info));
    SHR_IF_ERR_EXIT(dnx_algo_port_db_interface_id_get
                    (unit, port_info, info->core, info->interface_offset, NULL, info->framer_info.client_channel,
                     &interface_id.h0, &interface_id.h1));

    /*
     * Add to data base
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.set(unit, logical_port, DNX_ALGO_PORT_STATE_ADDED));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.set(unit, logical_port, port_info));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_offset.set(unit, logical_port, info->interface_offset));

    /** Add general interface Data Base */
    SHR_IF_ERR_EXIT(dnx_algo_port_common_add(unit, logical_port, info->core, &info->common_info, interface_id));

    /** add tm info */
    if (DNX_ALGO_PORT_TYPE_IS_TM(unit, port_info))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_tm_add(unit, logical_port, info->core, &info->tm_info, interface_id));
    }

    /** add sch info */
    if (DNX_ALGO_PORT_TYPE_IS_E2E_SCH(unit, port_info))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_sch_add(unit, logical_port, info->core, &info->tm_info, interface_id));
    }

    if (DNX_ALGO_PORT_TYPE_IS_FRAMER_CLIENT(unit, port_info))
    {
        /** FLEXE */
        SHR_IF_ERR_EXIT(dnx_algo_port_flexe_add(unit, logical_port, info->framer_info.client_channel));
    }

    /*
     *  Set SOC INFO
     */
    BCM_PBMP_CLEAR(dummy_pbmp);
    SHR_IF_ERR_EXIT(dnx_algo_port_is_master_get(unit, logical_port, 0, &is_master_port));
    SHR_IF_ERR_EXIT(dnx_algo_port_soc_info_add
                    (unit, logical_port, is_master_port, port_info, dummy_pbmp, info->common_info.tdm_mode));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_sch_only_add(
    int unit,
    bcm_port_t logical_port,
    dnx_algo_port_tm_add_t * tm_info)
{
    dnx_algo_port_db_2d_handle_t interface_handle;
    dnx_algo_port_info_s port_info;
    bcm_core_t core;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Get parameters from the DB
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

    /** Get core */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.core.get(unit, interface_handle.h0, interface_handle.h1, &core));

    /*
     * Update port info in the data base
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));
    port_info.is_sch = 1;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.set(unit, logical_port, port_info));

    /** add sch info */
    if (DNX_ALGO_PORT_TYPE_IS_E2E_SCH(unit, port_info))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_sch_add(unit, logical_port, core, tm_info, interface_handle));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_interface_and_channel_to_logical_get(
    int unit,
    int core_id,
    dnx_algo_port_info_s port_info,
    int channel_id,
    int is_out_channel,
    bcm_port_t * logical_port)
{
    dnx_algo_port_info_s port_info_i;
    bcm_port_t logical_port_i;
    bcm_pbmp_t logical_ports;
    int channel_i;
    bcm_core_t core_i;
    SHR_FUNC_INIT_VARS(unit);

    *logical_port = DNX_ALGO_PORT_INVALID;

    /*
     * iterate over valid logical ports bitmap and compare channel and type
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_logicals_get(unit, BCM_CORE_ALL, DNX_ALGO_PORT_LOGICALS_TYPE_VALID, 0,
                                               &logical_ports));
    BCM_PBMP_ITER(logical_ports, logical_port_i)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, logical_port_i, &port_info_i));
        if (port_info_i.port_type == port_info.port_type)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_core_get(unit, logical_port_i, &core_i));
            if (is_out_channel)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_out_channel_get(unit, logical_port_i, &channel_i));
            }
            else
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_in_channel_get(unit, logical_port_i, &channel_i));
            }
            if ((core_id == core_i) && (channel_id == channel_i))
            {
                *logical_port = logical_port_i;
                break;
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_fabric_phy_active_get(
    int unit,
    int fabric_phy,
    int *is_active)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.valid.get(unit, fabric_phy, is_active));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_fabric_add(
    int unit,
    bcm_port_t logical_port,
    dnx_algo_port_fabric_add_t * info)
{
    bcm_pbmp_t dummy_pbmp;
    dnx_algo_port_info_s port_info_fabric;
    dnx_algo_port_info_indicator_t indicator;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is free */
    SHR_IF_ERR_EXIT(dnx_algo_port_free_verify(unit, logical_port));

    /** Verify that fabric link id is supported by device*/
    /** TBD SHR_IF_ERR_EXIT(dnx_algo_port_fabric_link_supported_verify(unit, info->interface, info->interface_offset)); */

    /*
     * Add to data base
     */
    /** Logical DB - port type and interface type*/
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.set(unit, logical_port, DNX_ALGO_PORT_STATE_ADDED));
    sal_memset(&indicator, 0, sizeof(dnx_algo_port_info_indicator_t));
    SHR_IF_ERR_EXIT(dnx_algo_port_interface_to_port_info_get(unit, BCM_PORT_IF_SFI, &indicator, &port_info_fabric));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.set(unit, logical_port, port_info_fabric));

    /** Fabric data base (handle, mark as valid and link id */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.set(unit, logical_port, info->link_id));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.valid.set(unit, info->link_id, 1));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.link.set(unit, info->link_id, info->link_id));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.master_logical_port.set(unit, info->link_id, logical_port));

    /*
     *  Set SOC INFO
     */
    BCM_PBMP_CLEAR(dummy_pbmp);
    /** Set logical_port in bitmap, even though we currently don't use it */
    BCM_PBMP_PORT_ADD(dummy_pbmp, logical_port);
    SHR_IF_ERR_EXIT(dnx_algo_port_soc_info_add
                    (unit, logical_port, 1, port_info_fabric, dummy_pbmp, DNX_ALGO_PORT_TDM_MODE_NONE));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - update sch DBs when removing port (or SCH from the port)
 */
static shr_error_e
dnx_algo_port_remove_update_sch_db(
    int unit,
    bcm_port_t logical_port)
{
    dnx_algo_port_db_2d_handle_t sch_handle, sch_handle_i;
    dnx_algo_port_db_2d_handle_t sch_if_handle;
    bcm_port_t next_master_port = DNX_ALGO_PORT_INVALID, current_master_port;

    SHR_FUNC_INIT_VARS(unit);

    /** Release SCH Data Base */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_handle.get(unit, logical_port, &sch_handle));
    if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(sch_handle))
    {
        int i, sch_priorities;
        int ref_count;
        bcm_port_t sch_master_logical_port, logical_port_i;
        bcm_pbmp_t logical_port_channels;

        SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.sch_priorities.get(unit, sch_handle.h0, sch_handle.h1, &sch_priorities));

        SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.ref_count.get(unit, sch_handle.h0, sch_handle.h1, &ref_count));

        if (ref_count == 1)
        {
            for (i = 0; i < sch_priorities; i++)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db_sch_init(unit, sch_handle));
                sch_handle.h1++;
            }
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.master_logical_port.get(unit, sch_handle.h0, sch_handle.h1,
                                                                         &sch_master_logical_port));
            if (logical_port == sch_master_logical_port)
            {
                /*
                 * master port is about to be removed
                 * need to find a new master port
                 */

                /** get channels ports bitmap */
                SHR_IF_ERR_EXIT(dnx_algo_port_channels_get
                                (unit, logical_port, DNX_ALGO_PORT_CHANNELS_F_NON_L1_ONLY, &logical_port_channels));

                BCM_PBMP_ITER(logical_port_channels, logical_port_i)
                {
                    /** filter master port */
                    if (logical_port_i == sch_master_logical_port)
                    {
                        continue;
                    }
                    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_handle.get(unit, logical_port_i, &sch_handle_i));
                    if (DNX_ALGO_PORT_2D_HANDLE_EQ(sch_handle_i, sch_handle))
                    {
                        /** new master found */
                        sch_master_logical_port = logical_port_i;
                        break;
                    }
                }
            }

            for (i = 0; i < sch_priorities; i++)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.ref_count.dec(unit, sch_handle.h0, sch_handle.h1, 1));
                SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.master_logical_port.set(unit, sch_handle.h0, sch_handle.h1,
                                                                             sch_master_logical_port));
                sch_handle.h1++;
            }
        }
    }

    /** Scheduler interface Data Base */
    /** SCH master might be different than master port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_if_handle.get(unit, logical_port, &sch_if_handle));
    if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(sch_if_handle))
    {

        SHR_IF_ERR_EXIT(dnx_algo_port_master_get(unit, logical_port, DNX_ALGO_PORT_MASTER_F_SCH, &current_master_port));
        if (logical_port == current_master_port)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_master_get(unit, logical_port,
                                                     DNX_ALGO_PORT_MASTER_F_NEXT | DNX_ALGO_PORT_MASTER_F_SCH,
                                                     &next_master_port));
            if (next_master_port == DNX_ALGO_PORT_INVALID)
            {
                /** Release scheduler interface Data Base */
                SHR_IF_ERR_EXIT(dnx_algo_port_db_sch_if_init(unit, sch_if_handle));
            }
            else
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.master_logical_port.set(unit, sch_if_handle.h0,
                                                                                       sch_if_handle.h1,
                                                                                       next_master_port));
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_remove(
    int unit,
    bcm_port_t logical_port)
{
    dnx_algo_port_state_e state;
    dnx_algo_port_info_s port_info;
    int is_tm_master_port = 0;
    int is_intf_master_port = 0;
    int nif_handle;
    int ilkn_handle;
    int fabric_handle;
    int flexe_handle;
    dnx_algo_port_db_2d_handle_t pp_handle;
    dnx_algo_port_db_2d_handle_t out_tm_handle, in_tm_handle, pp_dsp_handle;
    dnx_algo_port_db_2d_handle_t tm_interface_handle, interface_handle;
    bcm_port_t next_tm_master_port = DNX_ALGO_PORT_INVALID;
    bcm_port_t next_intf_master_port = DNX_ALGO_PORT_INVALID;
    bcm_pbmp_t phy_ports;
    int is_lag;
    int phy;
    int framer_channel;
    int out_tm_ref_count, in_tm_ref_count;
    bcm_port_t logical_port_i;
    bcm_port_t out_tm_master_logical_port, new_out_tm_master_logical_port = -1;
    bcm_port_t in_tm_master_logical_port, new_in_tm_master_logical_port = -1;
    bcm_pbmp_t logical_port_channels;
    dnx_algo_port_db_2d_handle_t out_tm_handle_i, in_tm_handle_i, pp_dsp_handle_i;
    bcm_port_t pp_master_logical_port, new_pp_master_logical_port;
    int pp_ref_count;
    bcm_core_t core;
    int mirror_pp_free_skip = FALSE;
    int nof_channels;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Get port state
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.get(unit, logical_port, &state));
    /*
     * If port is valid (i.e. removing existing port)
     * Remove non-logical data base in case it's the master port
     */
    if (state != DNX_ALGO_PORT_STATE_INVALID)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));
        /*
         * if it is tm port
         * first set tdm mode to be invalid, which will update tdm and non-tdm master ports
         */
        if (DNX_ALGO_PORT_TYPE_IS_TM(unit, port_info))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_tdm_set(unit, logical_port, DNX_ALGO_PORT_TDM_MODE_INVALID));
            SHR_IF_ERR_EXIT(dnx_algo_port_is_master_get
                            (unit, logical_port, DNX_ALGO_PORT_MASTER_F_TM, &is_tm_master_port));
        }
        /*
         * if it is OTN port
         * Recycle the OTN logical lane resources.
         */
        if (DNX_ALGO_PORT_TYPE_IS_OTN_PHY(unit, port_info))
        {
            SHR_IF_ERR_EXIT(dnx_algo_lane_map_otn_logical_lane_free(unit, logical_port));
        }
        /*
         * Get current interface master port
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_is_master_get(unit, logical_port, 0, &is_intf_master_port));

        if (is_intf_master_port)
        {
            /*
             * If we remove port that is currently the master port. We need to find the next master.
             */
            SHR_IF_ERR_EXIT(dnx_algo_port_master_get
                            (unit, logical_port, DNX_ALGO_PORT_MASTER_F_NEXT, &next_intf_master_port));
        }
        else
        {
            /*
             *  In case the current logical_port that will be removed is not Master port,
             *  we will set "next_master_port" to be same as the current master port.
             *  Current master port should not be changed.
             */
            SHR_IF_ERR_EXIT(dnx_algo_port_master_get(unit, logical_port, 0, &next_intf_master_port));
        }

        /*
         * Remove port from SOC INFO
         */
        BCM_PBMP_CLEAR(phy_ports);
        if (DNX_ALGO_PORT_TYPE_IS_NIF(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(ELK, STIF, L1, FLEXE, MGMT, OTN_PHY)))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_nif_phys_get(unit, logical_port, 0, &phy_ports));
        }
        SHR_IF_ERR_EXIT(dnx_algo_port_soc_info_remove(unit, logical_port, port_info, next_intf_master_port, phy_ports));

        /*
         * Remove the port from 'e' bitmap
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_soc_info_port_remove(unit, ETHER_PTYPE, logical_port));

        /*
         * Remove the prd port profile mapping
         */
        if (DNX_ALGO_PORT_TYPE_IS_NIF(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(ELK, STIF, L1, MGMT))
            || DNX_ALGO_PORT_TYPE_IS_FRAMER_MAC(unit, port_info, TRUE, FALSE))
        {
            /*
             * PRD profile mapping is per NIF interface. Profile for the interface will be cleared only
             * When lats port in the interface is removed.
             */
            SHR_IF_ERR_EXIT(dnx_algo_port_channels_nof_get(unit, logical_port, &nof_channels));
            if (nof_channels < 2)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db_prd_port_to_profile_map_interface_init(unit, logical_port));
            }
        }
        /*
         * Release data base which are one per logical ports
         */
        /** Fabric Data Base */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));
        if (fabric_handle != DNX_ALGO_PORT_HANDLE_INVALID)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db_fabric_init(unit, fabric_handle));
        }

        /** PP DSP Data Base */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_dsp_handle.get(unit, logical_port, &pp_dsp_handle));

        if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(pp_dsp_handle))
        {
            /** OUT TM Data Base */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.out_tm_handle.get(unit, pp_dsp_handle.h0, pp_dsp_handle.h1,
                                                                         &out_tm_handle));
            if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(out_tm_handle))
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.ref_count.get(unit, out_tm_handle.h0, out_tm_handle.h1,
                                                                      &out_tm_ref_count));
                if (out_tm_ref_count <= 1)
                {
                    /** last port pointing to this OUT TM DB -  release OUT TM port Data Base */
                    SHR_IF_ERR_EXIT(dnx_algo_port_db_out_tm_init(unit, out_tm_handle));
                }
                else
                {
                    /** decrement OUT TM DB reference count */
                    SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.ref_count.dec(unit, out_tm_handle.h0, out_tm_handle.h1, 1));

                    SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.master_logical_port.get(unit,
                                                                                    out_tm_handle.h0, out_tm_handle.h1,
                                                                                    &out_tm_master_logical_port));
                    if (logical_port == out_tm_master_logical_port)
                    {
                        /*
                         * master port is about to be removed
                         * need to find a new master port
                         */

                        /** get channels ports bitmap */
                        SHR_IF_ERR_EXIT(dnx_algo_port_channels_get(unit, logical_port,
                                                                   DNX_ALGO_PORT_CHANNELS_F_NON_L1_ONLY,
                                                                   &logical_port_channels));

                        BCM_PBMP_ITER(logical_port_channels, logical_port_i)
                        {
                            /** filter master port */
                            if (logical_port_i == out_tm_master_logical_port)
                            {
                                continue;
                            }
                            SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_dsp_handle.get(unit, logical_port_i,
                                                                                       &pp_dsp_handle_i));
                            SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.out_tm_handle.get(unit, pp_dsp_handle_i.h0,
                                                                                         pp_dsp_handle_i.h1,
                                                                                         &out_tm_handle_i));
                            if (DNX_ALGO_PORT_2D_HANDLE_EQ(out_tm_handle_i, out_tm_handle))
                            {
                                /** new master found - set it to DB */
                                new_out_tm_master_logical_port = logical_port_i;
                                SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.master_logical_port.set(unit,
                                                                                                out_tm_handle.h0,
                                                                                                out_tm_handle.h1,
                                                                                                new_out_tm_master_logical_port));
                                break;
                            }
                        }
                    }
                }
            }

            SHR_IF_ERR_EXIT(dnx_algo_port_db_pp_dsp_init(unit, pp_dsp_handle));
        }

       /** IN TM Data Base */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.in_tm_handle.get(unit, logical_port, &in_tm_handle));
        if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(in_tm_handle))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.ref_count.get(unit, in_tm_handle.h0, in_tm_handle.h1,
                                                                 &in_tm_ref_count));
            if (in_tm_ref_count <= 1)
            {
                /** last port pointing to this IN TM DB -  release IN TM Data Base */
                SHR_IF_ERR_EXIT(dnx_algo_port_db_in_tm_init(unit, in_tm_handle));
            }
            else
            {
                /** decrement IN TM DB reference count */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.ref_count.dec(unit, in_tm_handle.h0, in_tm_handle.h1, 1));

                SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.master_logical_port.get(unit, in_tm_handle.h0, in_tm_handle.h1,
                                                                               &in_tm_master_logical_port));
                if (logical_port == in_tm_master_logical_port)
                {
                    /*
                     * master port is about to be removed
                     * need to find a new master port
                     */

                    /** get channels ports bitmap */
                    SHR_IF_ERR_EXIT(dnx_algo_port_channels_get
                                    (unit, logical_port, DNX_ALGO_PORT_CHANNELS_F_NON_L1_ONLY, &logical_port_channels));

                    BCM_PBMP_ITER(logical_port_channels, logical_port_i)
                    {
                        /** filter master port */
                        if (logical_port_i == in_tm_master_logical_port)
                        {
                            continue;
                        }
                        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.in_tm_handle.get(unit, logical_port_i,
                                                                                  &in_tm_handle_i));
                        if (DNX_ALGO_PORT_2D_HANDLE_EQ(in_tm_handle_i, in_tm_handle))
                        {
                            /** new master found - set it to DB */
                            new_in_tm_master_logical_port = logical_port_i;
                            SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.master_logical_port.set(unit,
                                                                                           in_tm_handle.h0,
                                                                                           in_tm_handle.h1,
                                                                                           new_in_tm_master_logical_port));
                            break;
                        }
                    }
                }
            }
        }

        /** Release PP port Data Base */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.get(unit, logical_port, &pp_handle));
        if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(pp_handle))
        {
            /** free pp port and ptc for mirror-rcy ports only if is the last port. check if free can be skipped */
            if (dnx_data_headers.
                system_headers.feature_get(unit, dnx_data_headers_system_headers_system_headers_ibch1_supported))
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_core_get(unit, logical_port, &core));
                SHR_IF_ERR_EXIT(algo_port_mgmt_pp_mirror_rcy_allocation_handle_skip
                                (unit, logical_port, core, port_info, &mirror_pp_free_skip,
                                 &new_pp_master_logical_port));
                SHR_IF_ERR_EXIT(dnx_algo_port_ptc_free(unit, core, logical_port, mirror_pp_free_skip));
            }

            /** release just in case pp ported wasn't allocated for LAG */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.is_lag.get(unit, pp_handle.h0, pp_handle.h1, &is_lag));
            if (!is_lag)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.ref_count.get(unit, pp_handle.h0, pp_handle.h1, &pp_ref_count));
                if (pp_ref_count <= 1)
                {
                    /** last port pointing to this PP DB -  release PP port Data Base */
                    SHR_IF_ERR_EXIT(dnx_algo_port_db_pp_init(unit, pp_handle));
                }
                else
                {
                    /** decrement PP DB reference count */
                    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.ref_count.dec(unit, pp_handle.h0, pp_handle.h1, 1));

                    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.master_logical_port.get(unit, pp_handle.h0, pp_handle.h1,
                                                                                &pp_master_logical_port));
                    if (logical_port == pp_master_logical_port)
                    {
                        if (mirror_pp_free_skip == FALSE)
                        {
                            /*
                             * master port is about to be removed.
                             * new master port is set according to TM master port,
                             * as we assume TM master port and PP master port are always equal
                             */
                            new_pp_master_logical_port = DNX_ALGO_PORT_IS_2D_HANDLE_VALID(in_tm_handle) ?
                                new_in_tm_master_logical_port : new_out_tm_master_logical_port;
                        }

                        /** new master found - set it to DB */
                        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.master_logical_port.set(unit, pp_handle.h0, pp_handle.h1,
                                                                                    new_pp_master_logical_port));
                    }
                }
            }
        }

        /** free the channel in allocation manager */
        if (DNX_ALGO_PORT_TYPE_IS_FRAMER_CLIENT(unit, port_info)
            || DNX_ALGO_PORT_USE_FLEXE_CLIENT_CHANNEL(unit, port_info)
            || DNX_ALGO_PORT_TYPE_IS_FRAMER_MGMT(unit, port_info))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_flexe_channel_get(unit, logical_port, &framer_channel));

            if (DNX_ALGO_PORT_TYPE_IS_FRAMER_MGMT(unit, port_info))
            {
                SHR_IF_ERR_EXIT(dnx_algo_framer_mgmt_channel_db_init(unit, framer_channel));
            }
            else
            {
                /*
                 * Dont need to free client channel for OAM and PTP channel.
                 */
                if (!DNX_ALGO_FLEXE_MAC_CHANNEL_IS_PTP_OR_OAM(unit, framer_channel))
                {
                    SHR_IF_ERR_EXIT(dnx_algo_flexe_client_channel_free(unit, port_info, framer_channel));
                }
            }
        }
        /** Flexe client Data Base */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_client_handle.get(unit, logical_port, &flexe_handle));
        if (flexe_handle != DNX_ALGO_PORT_HANDLE_INVALID)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db_flexe_client_init(unit, flexe_handle));
        }

        /** Flexe MAC Data Base */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_mac_handle.get(unit, logical_port, &flexe_handle));
        if (flexe_handle != DNX_ALGO_PORT_HANDLE_INVALID)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db_flexe_mac_init(unit, flexe_handle));
        }

        /** Flexe SAR Data Base */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_sar_handle.get(unit, logical_port, &flexe_handle));
        if (flexe_handle != DNX_ALGO_PORT_HANDLE_INVALID)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db_flexe_sar_init(unit, flexe_handle));
        }

        /** Flexe phy Data Base */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_phy_handle.get(unit, logical_port, &flexe_handle));
        if (flexe_handle != DNX_ALGO_PORT_HANDLE_INVALID)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db_flexe_phy_init(unit, flexe_handle));
        }
        /*
         * For data bases which might be relevant more then one logical port.
         * Release it only it there is no other master port.
         * If it master port and there are additional ports - just reset the pointers to the new master port
         */
        if (is_tm_master_port || is_intf_master_port)
        {
            /** get next interface master */
            if (is_intf_master_port)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_master_get
                                (unit, logical_port, DNX_ALGO_PORT_MASTER_F_NEXT, &next_intf_master_port));
            }
            /** get next tm master */
            if (is_tm_master_port)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_master_get
                                (unit, logical_port, DNX_ALGO_PORT_MASTER_F_NEXT | DNX_ALGO_PORT_MASTER_F_TM,
                                 &next_tm_master_port));
            }

            SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
            if (nif_handle != DNX_ALGO_PORT_HANDLE_INVALID)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.phys.get(unit, nif_handle, &phy_ports));
            }

            /** if no next tm master - release all tm interface data bases */
            if (next_tm_master_port == DNX_ALGO_PORT_INVALID)
            {
                /** Release TM interface Data Base */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.
                                tm_interface_handle.get(unit, logical_port, &tm_interface_handle));
                if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(tm_interface_handle))
                {
                    SHR_IF_ERR_EXIT(dnx_algo_port_db_tm_interface_init(unit, tm_interface_handle));
                }
            }
            else
            {
                /** Update next TM interface master port */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.
                                tm_interface_handle.get(unit, logical_port, &tm_interface_handle));
                if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(tm_interface_handle))
                {
                    SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                                    master_logical_port.set(unit, tm_interface_handle.h0, tm_interface_handle.h1,
                                                            next_tm_master_port));
                }
            }
            /** if no next interface master - release all interface data bases */
            if (next_intf_master_port == DNX_ALGO_PORT_INVALID)
            {
                /** Release NIF Data Base - all related phys */
                BCM_PBMP_ITER(phy_ports, phy)
                {
                    SHR_IF_ERR_EXIT(dnx_algo_port_db_nif_init(unit, phy));
                }

                /** Release ILKN Data Base */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ilkn_handle.get(unit, logical_port, &ilkn_handle));
                if (ilkn_handle != DNX_ALGO_PORT_HANDLE_INVALID)
                {
                    SHR_IF_ERR_EXIT(dnx_algo_port_db_ilkn_init(unit, ilkn_handle));
                }
                /** Release interface Data Base */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
                if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(interface_handle))
                {
                    SHR_IF_ERR_EXIT(dnx_algo_port_db_interface_init(unit, interface_handle));
                }
            }
            else
            {
                /** Update next interface master port */
                /** NIF Data Base */
                BCM_PBMP_ITER(phy_ports, phy)
                {
                    /** set master port */
                    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.master_logical_port.set(unit, phy, next_intf_master_port));
                }

                /** ILKN Data Base */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ilkn_handle.get(unit, logical_port, &ilkn_handle));
                if (ilkn_handle != DNX_ALGO_PORT_HANDLE_INVALID)
                {
                    SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.
                                    master_logical_port.set(unit, ilkn_handle, next_intf_master_port));
                }

                /** Interface Data Base */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
                if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(interface_handle))
                {
                    SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                                    master_logical_port.set(unit, interface_handle.h0, interface_handle.h1,
                                                            next_intf_master_port));
                }

            }
        }

        /** Release SCH DBs */
        SHR_IF_ERR_EXIT(dnx_algo_port_remove_update_sch_db(unit, logical_port));
    }

    /*
     * Init logical DB
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db_logical_init(unit, logical_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_remove_sch_only(
    int unit,
    bcm_port_t logical_port)
{
    dnx_algo_port_state_e state;
    dnx_algo_port_db_logical_t logical_db;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Get port state
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.get(unit, logical_port, &state));

    /*
     * If port is valid
     */
    if (state != DNX_ALGO_PORT_STATE_INVALID)
    {
        /** Release SCH DBs */
        SHR_IF_ERR_EXIT(dnx_algo_port_remove_update_sch_db(unit, logical_port));

        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.get(unit, logical_port, &logical_db));

        logical_db.sch_if_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
        logical_db.sch_if_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;
        logical_db.sch_handle.h0 = DNX_ALGO_PORT_HANDLE_INVALID;
        logical_db.sch_handle.h1 = DNX_ALGO_PORT_HANDLE_INVALID;

        /** mark the port as non SCH */
        logical_db.info.is_sch = 0;

        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.set(unit, logical_port, &logical_db));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_remove_process_start(
    int unit,
    bcm_port_t logical_port)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Mark as port under remove process
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.set(unit, logical_port, DNX_ALGO_PORT_STATE_REMOVED));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_removed_port_get(
    int unit,
    bcm_port_t * logical_port)
{
    dnx_algo_port_state_e state;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Iterate over all ports and return the first port in removed state.
     * (Assuming just one port is in this state)
     */
    for ((*logical_port) = 0; (*logical_port) < SOC_MAX_NUM_PORTS; (*logical_port)++)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.get(unit, *logical_port, &state));
        if (state == DNX_ALGO_PORT_STATE_REMOVED)
        {
            break;
        }
    }

    /** if not found throw an error */
    if (*logical_port == SOC_MAX_NUM_PORTS)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "removed port wasn't found");
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_added_port_get(
    int unit,
    bcm_port_t * logical_port)
{
    dnx_algo_port_state_e state;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Iterate over all ports and return the first port in added state.
     * (Assuming just one port is in this state)
     */
    for ((*logical_port) = 0; (*logical_port) < SOC_MAX_NUM_PORTS; (*logical_port)++)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.get(unit, *logical_port, &state));
        if (state == DNX_ALGO_PORT_STATE_ADDED)
        {
            break;
        }
    }

    /** if not found throw an error */
    if (*logical_port == SOC_MAX_NUM_PORTS)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "added port wasn't found");
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_add_process_done(
    int unit,
    bcm_port_t logical_port)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify (i.e. make sure the port is not free)
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Mark as valid port - added process completed
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.set(unit, logical_port, DNX_ALGO_PORT_STATE_VALID));

exit:
    SHR_FUNC_EXIT;
}
/*
 * }
 */

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_out_tm_port_get(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t * core,
    uint32 *out_tm_port)
{
    dnx_algo_port_db_2d_handle_t out_tm_handle, pp_dsp_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to PP DSP DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_dsp_handle.get(unit, logical_port, &pp_dsp_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(pp_dsp_handle);

    /** Get handle to TM DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.out_tm_handle.get(unit, pp_dsp_handle.h0, pp_dsp_handle.h1,
                                                                 &out_tm_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(out_tm_handle);

    /** Get core and tm_port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.core.get(unit, out_tm_handle.h0, out_tm_handle.h1, core));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.out_tm_port.get(unit, out_tm_handle.h0, out_tm_handle.h1, out_tm_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_out_tm_port_ref_count_get(
    int unit,
    bcm_core_t core,
    int out_tm_port,
    int *ref_count)
{
    dnx_algo_port_db_2d_handle_t out_tm_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Get valid */
    out_tm_handle.h0 = core;
    out_tm_handle.h1 = out_tm_port;
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(out_tm_handle);

    SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.ref_count.get(unit, out_tm_handle.h0, out_tm_handle.h1, ref_count));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_base_hr_ref_count_get(
    int unit,
    bcm_core_t core,
    int base_hr,
    int *ref_count)
{
    dnx_algo_port_db_2d_handle_t sch_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Get valid */
    sch_handle.h0 = core;
    sch_handle.h1 = base_hr;
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(sch_handle);
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.ref_count.get(unit, sch_handle.h0, sch_handle.h1, ref_count));

exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_pp_dsp_get(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t * core,
    uint32 *pp_dsp)
{
    dnx_algo_port_db_2d_handle_t pp_dsp_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to TM DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_dsp_handle.get(unit, logical_port, &pp_dsp_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(pp_dsp_handle);

    /** Get core and PP DSP */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.core.get(unit, pp_dsp_handle.h0, pp_dsp_handle.h1, core));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.pp_dsp.get(unit, pp_dsp_handle.h0, pp_dsp_handle.h1, pp_dsp));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_in_tm_port_get(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t * core,
    uint32 *in_tm_port)
{
    dnx_algo_port_db_2d_handle_t in_tm_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to TM DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.in_tm_handle.get(unit, logical_port, &in_tm_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(in_tm_handle);

    /** Get core and in tm port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.core.get(unit, in_tm_handle.h0, in_tm_handle.h1, core));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.in_tm_port.get(unit, in_tm_handle.h0, in_tm_handle.h1, in_tm_port));

exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_core_get(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t * core)
{
    dnx_algo_port_db_2d_handle_t interface_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to interface DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

    /** Get core */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.core.get(unit, interface_handle.h0, interface_handle.h1, core));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_in_lag(
    int unit,
    bcm_port_t logical_port,
    int *port_in_lag)
{
    dnx_algo_port_db_2d_handle_t pp_handle;
    SHR_FUNC_INIT_VARS(unit);

    *port_in_lag = 0;

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to PP DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.get(unit, logical_port, &pp_handle));
    if (DNX_ALGO_PORT_IS_2D_HANDLE_VALID(pp_handle))
    {
        /** set port_in_lag if port is part of a lag */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.is_lag.get(unit, pp_handle.h0, pp_handle.h1, port_in_lag));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_lag_id_get(
    int unit,
    bcm_port_t logical_port,
    bcm_trunk_t * lag_id)
{
    dnx_algo_port_db_2d_handle_t pp_handle;
    int port_in_lag;
    SHR_FUNC_INIT_VARS(unit);

    /** set to invalid */
    *lag_id = BCM_TRUNK_INVALID;

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** check if port in lag */
    SHR_IF_ERR_EXIT(dnx_algo_port_in_lag(unit, logical_port, &port_in_lag));

    /** set lag_id if port is part of a lag */
    if (port_in_lag)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.get(unit, logical_port, &pp_handle));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.lag_id.get(unit, pp_handle.h0, pp_handle.h1, lag_id));
    }

exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_header_type_in_set(
    int unit,
    bcm_port_t logical_port,
    int header_type)
{
    dnx_algo_port_db_2d_handle_t pp_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.get(unit, logical_port, &pp_handle));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.header_type_in.set(unit, pp_handle.h0, pp_handle.h1, header_type));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_header_type_in_get(
    int unit,
    bcm_port_t logical_port,
    int *header_type)
{
    dnx_algo_port_db_2d_handle_t pp_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.get(unit, logical_port, &pp_handle));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.header_type_in.get(unit, pp_handle.h0, pp_handle.h1, header_type));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_header_type_out_set(
    int unit,
    bcm_port_t logical_port,
    int header_type)
{
    dnx_algo_port_db_2d_handle_t pp_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.get(unit, logical_port, &pp_handle));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.header_type_out.set(unit, pp_handle.h0, pp_handle.h1, header_type));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_header_type_out_get(
    int unit,
    bcm_port_t logical_port,
    int *header_type)
{
    dnx_algo_port_db_2d_handle_t pp_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.get(unit, logical_port, &pp_handle));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.header_type_out.get(unit, pp_handle.h0, pp_handle.h1, header_type));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_pp_port_get(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t * core,
    uint32 *pp_port)
{
    dnx_algo_port_db_2d_handle_t pp_handle;
    int is_lag;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to PP DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.get(unit, logical_port, &pp_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(pp_handle);

    /** Don't allow getting pp port for LAG member */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.is_lag.get(unit, pp_handle.h0, pp_handle.h1, &is_lag));
    if (is_lag)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "getting pp port for a LAG member %d is not allowed.\n"
                     "Use LAG gport to get the required pp port\n", logical_port);
    }

    /** Get core and pp_port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.core.get(unit, pp_handle.h0, pp_handle.h1, core));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.pp_port.get(unit, pp_handle.h0, pp_handle.h1, pp_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_pp_port_modify(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t core,
    uint32 pp_port)
{
    dnx_algo_port_db_2d_handle_t pp_handle;
    bcm_core_t tm_core;
    int is_lag;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));
    /** Verify pp port */
    SHR_IF_ERR_EXIT(dnx_algo_port_pp_port_valid_verify(unit, core, pp_port));
    /** Verify that tm core equals to pp core */
    SHR_IF_ERR_EXIT(dnx_algo_port_core_get(unit, logical_port, &tm_core));
    if (tm_core != core)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "logical port %d core must not changed dynamically\n", core);
    }

    /*
     * Set handle to PP DB
     */
    pp_handle.h0 = core;
    pp_handle.h1 = pp_port;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_handle.set(unit, logical_port, &pp_handle));
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.is_lag.get(unit, pp_handle.h0, pp_handle.h1, &is_lag));
    if (!is_lag)
    {
        /** set master port (of pp port!) if not in lag */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.master_logical_port.set(unit, pp_handle.h0, pp_handle.h1, logical_port));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_fabric_link_get(
    int unit,
    bcm_port_t logical_port,
    int *fabric_link)
{
    int fabric_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to FABRIC DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(fabric_handle);

    /** Get fabric link */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.link.get(unit, fabric_handle, fabric_link));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_prbs_mode_set(
    int unit,
    bcm_port_t logical_port,
    portmod_prbs_mode_t prbs_mode)
{
    int fabric_handle = 0;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to FABRIC DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));

    /*
     * For non Fabric ports, prbs mode is always portmodPrbsModePhy.
     * For Fabric ports, prbs mode can be either portmodPrbsModePhy or portmodPrbsModeMac.
     */
    if (fabric_handle == DNX_ALGO_PORT_HANDLE_INVALID)
    {
        /** Verify prbs mode */
        SHR_VAL_VERIFY(prbs_mode, portmodPrbsModePhy, _SHR_E_PARAM, "PRBS mode must be PHY for this port");
    }
    else
    {
        /** Verify prbs mode */
        SHR_RANGE_VERIFY(prbs_mode, portmodPrbsModePhy, portmodPrbsModeMac, _SHR_E_PARAM,
                         "prbs mode %d is not supported", prbs_mode);

        /** Set PRBS mode */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.prbs_mode.set(unit, fabric_handle, prbs_mode));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_prbs_mode_get(
    int unit,
    bcm_port_t logical_port,
    portmod_prbs_mode_t * prbs_mode)
{
    int fabric_handle = 0;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to FABRIC DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));

    /*
     * For non Fabric ports, prbs mode is always portmodPrbsModePhy.
     * For Fabric ports, prbs mode can be either portmodPrbsModePhy or portmodPrbsModeMac.
     */
    if (fabric_handle == DNX_ALGO_PORT_HANDLE_INVALID)
    {
        *prbs_mode = portmodPrbsModePhy;
    }
    else
    {
        /** Get PRBS mode */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.prbs_mode.get(unit, fabric_handle, (int *) prbs_mode));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_in_tm_to_logical_get(
    int unit,
    bcm_core_t core,
    uint32 in_tm_port,
    bcm_port_t * logical_port)
{

    SHR_FUNC_INIT_VARS(unit);

    /** Verify tm port valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_in_tm_port_valid_verify(unit, core, in_tm_port));

    /** Get logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.in_tm.master_logical_port.get(unit, core, in_tm_port, logical_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_pp_dsp_to_logical_get(
    int unit,
    bcm_core_t core,
    uint32 pp_dsp,
    bcm_port_t * logical_port)
{

    SHR_FUNC_INIT_VARS(unit);

    /** Verify tm port valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_pp_dsp_valid_verify(unit, core, pp_dsp));

    /** Get logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.master_logical_port.get(unit, core, pp_dsp, logical_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_pp_to_logical_get(
    int unit,
    bcm_core_t core,
    uint32 pp_port,
    bcm_port_t * logical_port)
{

    SHR_FUNC_INIT_VARS(unit);

    /** Verify pp port valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_pp_port_valid_verify(unit, core, pp_port));

    /** Get logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.master_logical_port.get(unit, core, pp_port, logical_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_hr_to_logical_get(
    int unit,
    bcm_core_t core,
    uint32 hr_id,
    bcm_port_t * logical_port)
{

    SHR_FUNC_INIT_VARS(unit);

    /** Verify tm port valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_hr_valid_verify(unit, core, hr_id));

    /** Get logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.master_logical_port.get(unit, core, hr_id, logical_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_hr_is_valid_get(
    int unit,
    bcm_core_t core,
    uint32 hr_id,
    int *is_valid)
{

    SHR_FUNC_INIT_VARS(unit);

    /** Verify tm port valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_hr_param_verify(unit, core, hr_id));

    /** Get is_valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.ref_count.get(unit, core, hr_id, is_valid));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_fabric_link_to_logical_get(
    int unit,
    int fabric_link,
    bcm_port_t * logical_port)
{

    SHR_FUNC_INIT_VARS(unit);

    /** Verify fabric link valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_fabric_link_valid_verify(unit, fabric_link));

    /** Get logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.master_logical_port.get(unit, fabric_link, logical_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_pp_to_gport_get(
    int unit,
    bcm_core_t core,
    uint32 pp_port,
    bcm_gport_t * gport)
{

    int is_lag = 0;
    bcm_trunk_t lag_id;
    bcm_port_t logical_port;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify pp port valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_pp_port_valid_verify(unit, core, pp_port));

    /** Check if PP port was allocated for LAG */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.is_lag.get(unit, core, pp_port, &is_lag));
    if (is_lag)
    {
        /** Get LAG ID*/
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.lag_id.get(unit, core, pp_port, &lag_id));
        BCM_GPORT_TRUNK_SET(*gport, lag_id);
    }
    else
    {
        /** Get logical port */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.pp.master_logical_port.get(unit, core, pp_port, &logical_port));
        *gport = logical_port;
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * }
 */

/*
 * Set / Get  APIs
 * {
 */
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_is_master_get(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    int *is_master_port)
{
    bcm_port_t master_port;
    SHR_FUNC_INIT_VARS(unit);

    /** get master port */
    SHR_IF_ERR_EXIT(dnx_algo_port_master_get(unit, logical_port, flags, &master_port));

    /** return true iff master port is logical port */
    *is_master_port = (logical_port == master_port);

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * is interface can be configured as channelized
 */
static shr_error_e
dnx_algo_port_is_channelized_supported(
    int unit,
    bcm_port_t logical_port,
    int *is_channelized_supported)
{

    dnx_algo_port_info_s port_info;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * get port type - different behavior per port type
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));
    *is_channelized_supported = port_info.is_channelized;

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_master_get(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    bcm_port_t * master_logical_port)
{
    dnx_algo_port_db_2d_handle_t tm_interface_handle, interface_handle;
    uint32 supported_flags;
    bcm_port_t logical_port_i;
    int is_channelized_supported;
    bcm_port_t cur_master_logical_port;
    bcm_pbmp_t logical_port_channels;
    dnx_algo_port_info_s port_info;

    SHR_FUNC_INIT_VARS(unit);

    /** Init default */
    *master_logical_port = DNX_ALGO_PORT_INVALID;

    /*
     * Verify
     */
    /** Verify that the required flags are supported */
    supported_flags = DNX_ALGO_PORT_MASTER_F_MASK;
    SHR_IF_ERR_EXIT_WITH_LOG(utilex_bitstream_mask_verify(&flags, &supported_flags, 1),
                             "get master flags does not support the requested flags 0x%x %s%s.\n", flags, EMPTY, EMPTY);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    SHR_IF_ERR_EXIT(dnx_algo_port_is_channelized_supported(unit, logical_port, &is_channelized_supported));
    if (!is_channelized_supported)
    {

        if (flags & DNX_ALGO_PORT_MASTER_F_NEXT)
        { /** no next master*/
            *master_logical_port = DNX_ALGO_PORT_INVALID;
        }
        else
        { /** the logical port is the master port */
            *master_logical_port = logical_port;
        }
    }
    else
    {
        /** get current master port */
        /** Get handle to tm interface */

        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
        DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

        /** iterate the port to find the requested port */
        if (flags & DNX_ALGO_PORT_MASTER_F_NEXT)
        {
            if (flags & DNX_ALGO_PORT_MASTER_F_TDM_BYPASS)
            {
                /*
                 * TDM-bypass master port
                 */
                /** get channels ports bitmap */
                SHR_IF_ERR_EXIT(dnx_algo_port_channels_get(unit, logical_port, DNX_ALGO_PORT_CHANNELS_F_TDM_BYPASS_ONLY,
                                                           &logical_port_channels));
                /** get current master port */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                                master_tdm_logical_port.get(unit, interface_handle.h0, interface_handle.h1,
                                                            &cur_master_logical_port));
                BCM_PBMP_ITER(logical_port_channels, logical_port_i)
                {
                    /** filter master port */
                    if (logical_port_i == cur_master_logical_port)
                    {
                        continue;
                    }
                    *master_logical_port = logical_port_i;
                    break;
                }
            }
            else if (flags & DNX_ALGO_PORT_MASTER_F_NON_TDM_BYPASS)
            {
                /*
                 * NON TDM-bypass master port
                 */
                /** get channels ports bitmap */
                SHR_IF_ERR_EXIT(dnx_algo_port_channels_get
                                (unit, logical_port, DNX_ALGO_PORT_CHANNELS_F_NON_TDM_BYPASS_ONLY,
                                 &logical_port_channels));
                /** get current master port */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                                master_non_tdm_logical_port.get(unit, interface_handle.h0, interface_handle.h1,
                                                                &cur_master_logical_port));
                BCM_PBMP_ITER(logical_port_channels, logical_port_i)
                {
                    /** filter master port */
                    if (logical_port_i == cur_master_logical_port)
                    {
                        continue;
                    }
                    *master_logical_port = logical_port_i;
                    break;
                }
            }
            else if (flags & DNX_ALGO_PORT_MASTER_F_SCH)
            {
                /*
                 * SCH master port
                 */

                /** Get handle to tm interface */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_if_handle.get(unit, logical_port, &interface_handle));
                DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

                /** get channels ports bitmap -- it might include non SCH ports */
                SHR_IF_ERR_EXIT(dnx_algo_port_channels_get
                                (unit, logical_port, DNX_ALGO_PORT_CHANNELS_F_NON_L1_ONLY, &logical_port_channels));

                /** get current SCH master port */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.
                                master_logical_port.get(unit, interface_handle.h0, interface_handle.h1,
                                                        &cur_master_logical_port));
                BCM_PBMP_ITER(logical_port_channels, logical_port_i)
                {
                    /** filter master port */
                    if (logical_port_i == cur_master_logical_port)
                    {
                        continue;
                    }

                    /** skip non SCH ports */
                    SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, logical_port_i, &port_info));
                    if (!DNX_ALGO_PORT_TYPE_IS_E2E_SCH(unit, port_info))
                    {
                        continue;
                    }

                    *master_logical_port = logical_port_i;
                    break;
                }
            }
            else if (flags & DNX_ALGO_PORT_MASTER_F_TM)
            {
                /** Get handle to tm interface */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.tm_interface_handle.get(unit, interface_handle.h0,
                                                                                   interface_handle.h1,
                                                                                   &tm_interface_handle));
                DNX_ALGO_PORT_2D_HANDLE_VERIFY(tm_interface_handle);
                SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                                master_logical_port.get(unit, tm_interface_handle.h0, tm_interface_handle.h1,
                                                        &cur_master_logical_port));
                /** get channels ports bitmap */
                SHR_IF_ERR_EXIT(dnx_algo_port_channels_get
                                (unit, logical_port, DNX_ALGO_PORT_CHANNELS_F_NON_L1_ONLY, &logical_port_channels));
                BCM_PBMP_ITER(logical_port_channels, logical_port_i)
                {
                    /** filter master port */
                    if (logical_port_i == cur_master_logical_port)
                    {
                        continue;
                    }
                    *master_logical_port = logical_port_i;
                    break;
                }
            }
            else
            {
                /*
                 * Interface master port
                 */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                                master_logical_port.get(unit, interface_handle.h0, interface_handle.h1,
                                                        &cur_master_logical_port));
                /** get channels ports bitmap */
                SHR_IF_ERR_EXIT(dnx_algo_port_channels_get(unit, logical_port, 0, &logical_port_channels));
                BCM_PBMP_ITER(logical_port_channels, logical_port_i)
                {
                    /** filter master port */
                    if (logical_port_i == cur_master_logical_port)
                    {
                        continue;
                    }
                    *master_logical_port = logical_port_i;
                    break;
                }
            }
        }
        else
        {   /** current master port */

            /** read master, tdm-bypass master, non-tdm-bypass master */
            if (flags & DNX_ALGO_PORT_MASTER_F_TDM_BYPASS)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                                master_tdm_logical_port.get(unit, interface_handle.h0, interface_handle.h1,
                                                            master_logical_port));
            }
            else if (flags & DNX_ALGO_PORT_MASTER_F_NON_TDM_BYPASS)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                                master_non_tdm_logical_port.get(unit, interface_handle.h0, interface_handle.h1,
                                                                master_logical_port));
            }
            else if (flags & DNX_ALGO_PORT_MASTER_F_SCH)
            {
                /*
                 * SCH master port
                 */

                /** Get handle to tm interface */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_if_handle.get(unit, logical_port, &interface_handle));
                DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

                /** get current SCH master port */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.
                                master_logical_port.get(unit, interface_handle.h0, interface_handle.h1,
                                                        master_logical_port));
            }
            else if (flags & DNX_ALGO_PORT_MASTER_F_TM)
            {
                /** Get handle to tm interface */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.tm_interface_handle.get(unit, interface_handle.h0,
                                                                                   interface_handle.h1,
                                                                                   &tm_interface_handle));
                DNX_ALGO_PORT_2D_HANDLE_VERIFY(tm_interface_handle);
                SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                                master_logical_port.get(unit, tm_interface_handle.h0, tm_interface_handle.h1,
                                                        master_logical_port));
            }
            else
            {
                /** Get interface master port */
                SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                                master_logical_port.get(unit, interface_handle.h0, interface_handle.h1,
                                                        master_logical_port));
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_to_ilkn_master_get(
    int unit,
    bcm_port_t logical_port,
    int *master_port)
{
    int ilkn_handle;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ilkn_handle.get(unit, logical_port, &ilkn_handle));

    SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.master_logical_port.get(unit, ilkn_handle, master_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_tm_inteface_to_master_get(
    int unit,
    int if_id_h0,
    int if_id_h1,
    int *master_port)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.master_logical_port.get(unit, if_id_h0, if_id_h1, master_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_info_get(
    int unit,
    bcm_port_t logical_port,
    dnx_algo_port_info_s * port_info)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port exist */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, port_info));

exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_interface_offset_get(
    int unit,
    bcm_port_t logical_port,
    int *interface_offset)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port exist */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_offset.get(unit, logical_port, interface_offset));

exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_interface_offset_logical_get(
    int unit,
    dnx_algo_port_type_e port_type,
    int interface_offset,
    bcm_gport_t * gport)
{
    bcm_port_t valid_port;
    bcm_pbmp_t valid_ports;
    int interface_offset_i;
    dnx_algo_port_info_s port_info_i;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Iter over all valid ports
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_logicals_get(unit, BCM_CORE_ALL, DNX_ALGO_PORT_LOGICALS_TYPE_VALID, 0, &valid_ports));
    BCM_PBMP_ITER(valid_ports, valid_port)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, valid_port, &port_info_i));
        if (port_info_i.port_type != port_type)
        {
            continue;
        }

        SHR_IF_ERR_EXIT(dnx_algo_port_interface_offset_get(unit, valid_port, &interface_offset_i));

        if (interface_offset_i != interface_offset)
        {
            continue;
        }

        BCM_GPORT_LOCAL_SET(*gport, valid_port);
        /** If port is found go directly to "exit" and skip NOT_FOUND error */
        SHR_EXIT();
    }

    /** If we reach this point it means that Port and COSQ were not found */
    SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "Logical port for interface offset %d not found.", interface_offset);
exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_in_channel_get(
    int unit,
    bcm_port_t logical_port,
    int *in_channel_id)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    *in_channel_id = 0;

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.in_channel.get(unit, logical_port, in_channel_id));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_out_channel_get(
    int unit,
    bcm_port_t logical_port,
    int *out_channel_id)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    *out_channel_id = 0;

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.out_channel.get(unit, logical_port, out_channel_id));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_flexe_channel_get(
    int unit,
    bcm_port_t logical_port,
    int *channel_id)
{
    int flexe_handle;
    dnx_algo_port_info_s port_info;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    *channel_id = 0;

    /** Get port type */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FLEXE_CLIENT(unit, port_info))
    {
        /*
         * Get Bus A channel
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_client_handle.get(unit, logical_port, &flexe_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.client_index.get(unit, flexe_handle, channel_id));
    }
    else if (DNX_ALGO_PORT_TYPE_IS_FRAMER_MAC(unit, port_info, TRUE, TRUE))
    {
        /*
         * Get BusB channel
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_mac_handle.get(unit, logical_port, &flexe_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.client_index.get(unit, flexe_handle, channel_id));
    }
    else if (DNX_ALGO_PORT_TYPE_IS_FRAMER_SAR(unit, port_info, TRUE))
    {
        /*
         * Get BusC channel
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_sar_handle.get(unit, logical_port, &flexe_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.client_index.get(unit, flexe_handle, channel_id));
    }
    else if (DNX_ALGO_PORT_TYPE_IS_FRAMER_MGMT(unit, port_info)
             || DNX_ALGO_PORT_TYPE_IS_NIF_ETH_L1(unit, port_info, TRUE))
    {
        /*
         * Get framer ETH channel
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_phy_handle.get(unit, logical_port, &flexe_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.phy.channel.get(unit, flexe_handle, channel_id));
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Port %d is expected to be of flexe type.\n", logical_port);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * See .h file
 */
shr_error_e
dnx_algo_port_sar_channel_logical_get(
    int unit,
    int channel_id,
    bcm_port_t * logical_port)
{
    bcm_pbmp_t port_bm;
    bcm_port_t logical_port_i = 0;
    dnx_algo_port_info_s port_info;
    int channel_id_temp = 0;
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_logicals_get(unit, BCM_CORE_ALL, DNX_ALGO_PORT_LOGICALS_TYPE_VALID, 0, &port_bm));

    /*
     * Set initial value for the port
     */
    *logical_port = BCM_PORT_INVALID;
    BCM_PBMP_ITER(port_bm, logical_port_i)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port_i, &port_info));
        if (DNX_ALGO_PORT_TYPE_IS_FRAMER_SAR(unit, port_info, TRUE))
        {
            /*
             * Get BusC channel
             */
            SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_sar_handle.get(unit, logical_port_i, &flexe_handle));
            DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);
            SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.client_index.get(unit, flexe_handle, &channel_id_temp));

            /*
             * If the channel is matching the requested one, return the logical port
             */
            if (channel_id_temp == channel_id)
            {
                *logical_port = logical_port_i;
                break;
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_app_flags_set(
    int unit,
    bcm_port_t logical_port,
    uint32 app_flags)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Set data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.port_app_flags.set(unit, logical_port, app_flags));
exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_app_flags_get(
    int unit,
    bcm_port_t logical_port,
    uint32 *app_flags)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    *app_flags = 0;

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.port_app_flags.get(unit, logical_port, app_flags));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_base_q_pair_get(
    int unit,
    bcm_port_t logical_port,
    int *base_q_pair)
{
    dnx_algo_port_db_2d_handle_t out_tm_handle, pp_dsp_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to PP DSP DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_dsp_handle.get(unit, logical_port, &pp_dsp_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(pp_dsp_handle);

    /** Get handle to TM DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.out_tm_handle.get(unit, pp_dsp_handle.h0, pp_dsp_handle.h1,
                                                                 &out_tm_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(out_tm_handle);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.base_q_pair.get(unit, out_tm_handle.h0, out_tm_handle.h1, base_q_pair));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_out_tm_to_logical_get(
    int unit,
    bcm_core_t core,
    uint32 out_tm_port,
    bcm_port_t * logical_port)
{
    dnx_algo_port_db_2d_handle_t out_tm_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    out_tm_handle.h0 = core;
    out_tm_handle.h1 = out_tm_port;

    DNX_ALGO_PORT_2D_HANDLE_VERIFY(out_tm_handle);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.master_logical_port.get(unit, out_tm_handle.h0, out_tm_handle.h1,
                                                                    logical_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_q_pair_port_cosq_get(
    int unit,
    int q_pair,
    bcm_core_t core,
    bcm_port_t * logical_port,
    bcm_cos_queue_t * cosq)
{
    bcm_port_t port;
    bcm_pbmp_t port_bm;
    int num_priorities, base_q_pair;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_logicals_get(unit, core, DNX_ALGO_PORT_LOGICALS_TYPE_TM_EGR_QUEUING, 0, &port_bm));
    BCM_PBMP_ITER(port_bm, port)
    {
        /*
         * Get the Q-pair
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_base_q_pair_get(unit, port, &base_q_pair));
        /*
         * Get number of priorities for current port
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_priorities_nof_get(unit, port, &num_priorities));
        /*
         * If q_pair is in the range of Q-pairs for this port, return the information and break the loop
         */
        if ((q_pair >= base_q_pair) && (q_pair < (base_q_pair + num_priorities)))
        {
            *logical_port = port;
            *cosq = q_pair - base_q_pair;
            /** If Port and COSQ are found go directly to "exit" and skip NOT_FOUND error */
            SHR_EXIT();
        }
    }
    /** If we reach this point it means that Port and COSQ were not found */
    SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "Port and COSQ for specified Q-pair not found.");
exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_base_hr_get(
    int unit,
    bcm_port_t logical_port,
    int *base_hr)
{
    dnx_algo_port_db_2d_handle_t sch_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to tm port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_handle.get(unit, logical_port, &sch_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(sch_handle);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.base_hr.get(unit, sch_handle.h0, sch_handle.h1, base_hr));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_priorities_nof_get(
    int unit,
    bcm_port_t logical_port,
    int *num_priorities)
{
    dnx_algo_port_db_2d_handle_t out_tm_handle, pp_dsp_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to PP DSP DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_dsp_handle.get(unit, logical_port, &pp_dsp_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(pp_dsp_handle);

    /** Get handle to TM DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.out_tm_handle.get(unit, pp_dsp_handle.h0, pp_dsp_handle.h1,
                                                                 &out_tm_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(out_tm_handle);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.priorities.get(unit, out_tm_handle.h0, out_tm_handle.h1, num_priorities));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_is_mc_get(
    int unit,
    bcm_port_t logical_port,
    int *is_mc)
{
    dnx_algo_port_db_2d_handle_t out_tm_handle, pp_dsp_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to PP DSP DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.pp_dsp_handle.get(unit, logical_port, &pp_dsp_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(pp_dsp_handle);

    /** Get handle to TM DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.pp_dsp_db.out_tm_handle.get(unit, pp_dsp_handle.h0, pp_dsp_handle.h1,
                                                                 &out_tm_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(out_tm_handle);

    /** Get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.out_tm.is_mc.get(unit, out_tm_handle.h0, out_tm_handle.h1, is_mc));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_sch_priorities_nof_get(
    int unit,
    bcm_port_t logical_port,
    int *num_priorities)
{
    dnx_algo_port_db_2d_handle_t sch_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to tm port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_handle.get(unit, logical_port, &sch_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(sch_handle);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch.sch_priorities.get(unit, sch_handle.h0, sch_handle.h1, num_priorities));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_is_channelized_get(
    int unit,
    bcm_port_t logical_port,
    int *is_channelized)
{
    dnx_algo_port_db_2d_handle_t interface_handle;
    int is_channelized_supported;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    SHR_IF_ERR_EXIT(dnx_algo_port_is_channelized_supported(unit, logical_port, &is_channelized_supported));
    if (is_channelized_supported)
    {
        /** Get handle to tm interface */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
        DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

        /*
         * Get data
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        is_channelized.get(unit, interface_handle.h0, interface_handle.h1, is_channelized));
    }
    else
    {
        *is_channelized = FALSE;
    }
exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_is_egress_interleave_get(
    int unit,
    bcm_port_t logical_port,
    int *is_egress_interleave)
{
    dnx_algo_port_db_2d_handle_t tm_interface_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to tm interface */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.tm_interface_handle.get(unit, logical_port, &tm_interface_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(tm_interface_handle);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.is_egress_interleave.get
                    (unit, tm_interface_handle.h0, tm_interface_handle.h1, is_egress_interleave));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_is_ingress_interleave_get(
    int unit,
    bcm_port_t logical_port,
    int *is_ingress_interleave)
{
    dnx_algo_port_db_2d_handle_t interface_handle;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to tm interface */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.is_ingress_interleave.get
                    (unit, interface_handle.h0, interface_handle.h1, is_ingress_interleave));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_sch_priority_propagation_enable_get(
    int unit,
    bcm_port_t logical_port,
    int *sch_priority_propagation_enable)
{
    dnx_algo_port_db_2d_handle_t sch_interface_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to tm interface */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_if_handle.get(unit, logical_port, &sch_interface_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(sch_interface_handle);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.
                    priority_propagation_enable.get(unit, sch_interface_handle.h0, sch_interface_handle.h1,
                                                    sch_priority_propagation_enable));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_fec_type_get(
    int unit,
    bcm_port_t logical_port,
    bcm_port_phy_fec_t * fec_type)
{
    int fec_type_int, fabric_handle;
    dnx_algo_port_info_s port_info;
    dnx_algo_port_db_2d_handle_t interface_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify logical port is valid 
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get port type 
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FABRIC(unit, port_info))
    {
        /*
         * Get handle to fabric link 
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(fabric_handle);

        /*
         * Get data
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.fec_type.get(unit, fabric_handle, &fec_type_int));
    }
    else
    {

        /*
         * Get handle to interface 
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
        DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

        /*
         * Get the data
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        fec_type.get(unit, interface_handle.h0, interface_handle.h1, &fec_type_int));

    }
    *fec_type = (bcm_port_phy_fec_t) fec_type_int;

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_fec_type_set(
    int unit,
    bcm_port_t logical_port,
    bcm_port_phy_fec_t fec_type)
{
    int fabric_handle;
    dnx_algo_port_info_s port_info;
    dnx_algo_port_db_2d_handle_t interface_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify logical port is valid 
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get port type 
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FABRIC(unit, port_info))
    {
        /*
         * Get handle to fabric link 
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(fabric_handle);

        /*
         * Set data
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.fec_type.set(unit, fabric_handle, (int) fec_type));
    }
    else
    {

        /*
         * Get handle to interface 
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
        DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

        /*
         * Set the data
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        fec_type.set(unit, interface_handle.h0, interface_handle.h1, (int) fec_type));

    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_speed_set(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    int speed)
{
    dnx_algo_port_db_2d_handle_t interface_handle;
    dnx_algo_port_info_s port_info;
    int fabric_handle;
    dnx_algo_port_tdm_mode_e tdm_mode;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get port type */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FABRIC(unit, port_info))
    {
        /** Get handle to fabric link */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(fabric_handle);

        /*
         * Set data
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.speed.set(unit, fabric_handle, speed));
    }
    else
    {

        /** Get handle to tm interface */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
        DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

        /*
         * Return error if neither RX nor TX flag is not set.
         */
        if (!DNX_ALGO_PORT_SPEED_RX_GET(flags) && !DNX_ALGO_PORT_SPEED_TX_GET(flags))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Please specify the speed is for Rx or Tx for port %d.\n", logical_port);
        }
        /*
         * Set data for Rx and Tx separately. The Rx and Tx speed may be
         * asymmetric for FlexE MAC and SAR client
         */
        if (DNX_ALGO_PORT_SPEED_RX_GET(flags))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                            rx_speed.set(unit, interface_handle.h0, interface_handle.h1, speed));
        }
        if (DNX_ALGO_PORT_SPEED_TX_GET(flags))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                            tx_speed.set(unit, interface_handle.h0, interface_handle.h1, speed));
        }
    }

    /** update SOC_INFO with new port's speed */
    tdm_mode = DNX_ALGO_PORT_TDM_MODE_NONE;
    SHR_IF_ERR_EXIT(dnx_algo_port_tdm_get(unit, logical_port, &tdm_mode));

    SHR_IF_ERR_EXIT(dnx_algo_port_soc_info_port_bitmaps_set(unit, logical_port, port_info, tdm_mode));

exit:
    SHR_FUNC_EXIT;
}

/*
 * internal implementation of speed_get
 */
static shr_error_e
dnx_algo_port_speed_get_impl(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    int *speed)
{
    dnx_algo_port_db_2d_handle_t interface_handle;
    dnx_algo_port_info_s port_info;
    int rx_speed, tx_speed;
    int fabric_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get port type */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FABRIC(unit, port_info))
    {
        /** Get handle to fabric link */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(fabric_handle);

        /*
         * Set data
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.speed.get(unit, fabric_handle, speed));

    }
    else
    {

        /** Get handle to tm interface */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
        DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

        /*
         * Get data for Rx and Tx separately. If the Rx/Tx speed are asymmetric and both RX/TX flags are set,
         * return error directly.
         */
        if (DNX_ALGO_PORT_SPEED_RX_GET(flags) && !DNX_ALGO_PORT_SPEED_TX_GET(flags))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                            rx_speed.get(unit, interface_handle.h0, interface_handle.h1, speed));
        }
        else if (DNX_ALGO_PORT_SPEED_TX_GET(flags) && !DNX_ALGO_PORT_SPEED_RX_GET(flags))
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                            tx_speed.get(unit, interface_handle.h0, interface_handle.h1, speed));
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                            rx_speed.get(unit, interface_handle.h0, interface_handle.h1, &rx_speed));
            SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                            tx_speed.get(unit, interface_handle.h0, interface_handle.h1, &tx_speed));
            if (rx_speed != tx_speed)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Rx speed and Tx speed are asymmetric for port %d, please specify the Rx or Tx flag.\n",
                             logical_port);
            }
            *speed = rx_speed;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_has_speed(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    int *has_speed)
{
    int speed;

    SHR_FUNC_INIT_VARS(unit);
    /*
     * Get speed
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_speed_get_impl(unit, logical_port, flags, &speed));

    *has_speed = (speed != 0);

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_speed_get(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    int *speed)
{
    uint32 supported_flags;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify that the required flags are supported */
    supported_flags =
        DNX_ALGO_PORT_SPEED_F_MBPS | DNX_ALGO_PORT_SPEED_F_KBPS | DNX_ALGO_PORT_SPEED_F_RX | DNX_ALGO_PORT_SPEED_F_TX;
    SHR_IF_ERR_EXIT_WITH_LOG(utilex_bitstream_mask_verify(&flags, &supported_flags, 1),
                             "get speed flags does not support the requested flags 0x%x %s%s.\n", flags, EMPTY, EMPTY);
    /*
     * Get speed
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_speed_get_impl(unit, logical_port, flags, speed));

    if (*speed == 0)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "speed wasn't set for port %d.\n", logical_port);
    }

    if (flags & DNX_ALGO_PORT_SPEED_F_KBPS)
    {
        *speed = *speed * 1000;
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_phys_get(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    bcm_pbmp_t * phys)
{
    int nif_handle;
    uint32 supported_flags;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));
    /** verify flags */
    supported_flags = 0;
    SHR_IF_ERR_EXIT_WITH_LOG(utilex_bitstream_mask_verify(&flags, &supported_flags, 1),
                             "function flags does not support the requested flags 0x%x %s%s.\n", flags, EMPTY, EMPTY);

    /*
     * Get data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.phys.get(unit, nif_handle, phys));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_first_phy_get(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    int *first_phy_port)
{
    int nif_handle;
    uint32 supported_flags;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));
    /** verify flags */
    supported_flags = 0;
    SHR_IF_ERR_EXIT_WITH_LOG(utilex_bitstream_mask_verify(&flags, &supported_flags, 1),
                             "function flags does not support the requested flags 0x%x %s%s.\n", flags, EMPTY, EMPTY);

    /*
     * Get data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.first_phy.get(unit, nif_handle, first_phy_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_ilkn_lanes_get(
    int unit,
    bcm_port_t logical_port,
    bcm_pbmp_t * ilkn_lanes)
{
    int ilkn_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ilkn_handle.get(unit, logical_port, &ilkn_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(ilkn_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.lanes.get(unit, ilkn_handle, ilkn_lanes));

exit:
    SHR_FUNC_EXIT;

}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_ilkn_nof_segments_get(
    int unit,
    bcm_port_t logical_port,
    int *nof_segments)
{
    int ilkn_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ilkn_handle.get(unit, logical_port, &ilkn_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(ilkn_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.nof_segments.get(unit, ilkn_handle, nof_segments));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_ilkn_nof_segments_set(
    int unit,
    bcm_port_t logical_port,
    int nof_segments)
{
    int ilkn_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ilkn_handle.get(unit, logical_port, &ilkn_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(ilkn_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.nof_segments.set(unit, ilkn_handle, nof_segments));

exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_ilkn_is_over_fabric_get(
    int unit,
    bcm_port_t logical_port,
    int *is_over_fabric)
{
    int ilkn_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ilkn_handle.get(unit, logical_port, &ilkn_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(ilkn_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.is_over_fabric.get(unit, ilkn_handle, is_over_fabric));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_ilkn_priority_get(
    int unit,
    bcm_port_t logical_port,
    bcm_port_nif_scheduler_t * priority)
{
    int ilkn_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ilkn_handle.get(unit, logical_port, &ilkn_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(ilkn_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.priority.get(unit, ilkn_handle, priority));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_ilkn_priority_set(
    int unit,
    bcm_port_t logical_port,
    bcm_port_nif_scheduler_t priority)
{
    int ilkn_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ilkn_handle.get(unit, logical_port, &ilkn_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(ilkn_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.ilkn.priority.set(unit, ilkn_handle, priority));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_ilkn_phy_pms_get(
    int unit,
    bcm_port_t logical_port,
    int is_over_fabric,
    int phy,
    int *pm_id,
    int *phy_offset_in_pm)
{
    int table_iter;
    int tmp_pm_id = 0, tmp_phy_offset_in_pm = 0;
    bcm_pbmp_t ilkn_phys;
    uint8 phy_found = FALSE;
    const dnxc_data_table_info_t *ilkn_pms_table_info;
    const dnx_data_nif_ilkn_nif_pms_t *ilkn_pm_info;
    const dnx_data_nif_ilkn_fabric_pms_t *ilkn_fabric_pm_info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_nif_phys_get(unit, logical_port, 0, &ilkn_phys));
    if (!BCM_PBMP_MEMBER(ilkn_phys, phy))
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Ilkn phy id isn't belong to the port.\n");
    }

    ilkn_pms_table_info =
        (is_over_fabric) ? dnx_data_nif.ilkn.fabric_pms_info_get(unit) : dnx_data_nif.ilkn.nif_pms_info_get(unit);

    for (table_iter = 0; table_iter < ilkn_pms_table_info->key_size[0]; table_iter++)
    {
        if (is_over_fabric)
        {
            ilkn_fabric_pm_info = dnx_data_nif.ilkn.fabric_pms_get(unit, table_iter);
            /*
             * If device lane is in range, take range info
             */
            if ((phy >= ilkn_fabric_pm_info->first_phy)
                && (phy < ilkn_fabric_pm_info->first_phy + ilkn_fabric_pm_info->nof_phys))
            {
                tmp_pm_id = table_iter;
                tmp_phy_offset_in_pm = phy - ilkn_fabric_pm_info->first_phy;
                phy_found = TRUE;
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {
            ilkn_pm_info = dnx_data_nif.ilkn.nif_pms_get(unit, table_iter);
            /*
             * If device lane is in range, take range info
             */
            if ((phy >= ilkn_pm_info->first_phy) && (phy < ilkn_pm_info->first_phy + ilkn_pm_info->nof_phys))
            {
                tmp_pm_id = table_iter;
                tmp_phy_offset_in_pm = phy - ilkn_pm_info->first_phy;
                phy_found = TRUE;
                break;
            }
            else
            {
                continue;
            }
        }
    }

    if (!phy_found)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Ilkn phy id can't be found.\n");
    }
    else
    {
        *pm_id = tmp_pm_id;
        *phy_offset_in_pm = tmp_phy_offset_in_pm;
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_ilkn_core_aggregated_pms_get(
    int unit,
    bcm_port_t logical_port,
    int is_over_fabric,
    int *nof_aggregated_pms,
    portmod_pm_identifier_t * controlled_pms)
{
    int i, max_nof_pms, phy, table_iter, tmp_pm_id = 0, next_free = 0, phy_offset = 0;
    int pm_arr[DNX_DATA_MAX_NIF_ILKN_PMS_NOF];
    uint32 pm_first_phy = 0;
    portmod_dispatch_type_t pm_type = portmodDispatchTypeCount;
    bcm_pbmp_t ilkn_phys;
    uint8 pm_found = FALSE, phy_found = FALSE;
    const dnxc_data_table_info_t *ilkn_pms_table_info;
    const dnx_data_nif_ilkn_nif_pms_t *ilkn_pm_info;
    const dnx_data_nif_ilkn_fabric_pms_t *ilkn_fabric_pm_info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_nif_phys_get(unit, logical_port, 0, &ilkn_phys));
    ilkn_pms_table_info =
        (is_over_fabric) ? dnx_data_nif.ilkn.fabric_pms_info_get(unit) : dnx_data_nif.ilkn.nif_pms_info_get(unit);
    max_nof_pms = dnx_data_nif.ilkn.pms_nof_get(unit);
    *nof_aggregated_pms = 0;

    for (i = 0; i < DNX_DATA_MAX_NIF_ILKN_PMS_NOF; i++)
    {
        pm_arr[i] = -1;
    }

    BCM_PBMP_ITER(ilkn_phys, phy)
    {
        for (table_iter = 0; table_iter < ilkn_pms_table_info->key_size[0]; table_iter++)
        {
            if (is_over_fabric)
            {
                ilkn_fabric_pm_info = dnx_data_nif.ilkn.fabric_pms_get(unit, table_iter);

                phy_offset = dnx_data_port.general.fabric_phys_offset_get(unit);

                /*
                 * If device lane is in range, take range info
                 */
                if ((phy >= ilkn_fabric_pm_info->first_phy)
                    && (phy < ilkn_fabric_pm_info->first_phy + ilkn_fabric_pm_info->nof_phys))
                {
                    tmp_pm_id = table_iter;
                    pm_first_phy = ilkn_fabric_pm_info->first_phy;
                    pm_type = ilkn_fabric_pm_info->dispatch_type;
                    phy_found = TRUE;
                    break;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                ilkn_pm_info = dnx_data_nif.ilkn.nif_pms_get(unit, table_iter);

                phy_offset = 0;

                /*
                 * If device lane is in range, take range info
                 */
                if ((phy >= ilkn_pm_info->first_phy) && (phy < ilkn_pm_info->first_phy + ilkn_pm_info->nof_phys))
                {
                    tmp_pm_id = table_iter;
                    pm_first_phy = ilkn_pm_info->first_phy;
                    pm_type = ilkn_pm_info->dispatch_type;
                    phy_found = TRUE;
                    break;
                }
                else
                {
                    continue;
                }
            }

        }

        pm_found = FALSE;
        for (i = 0; i < max_nof_pms; i++)
        {
            if (pm_arr[i] == tmp_pm_id)
            {
                pm_found = TRUE;
                break;
            }
        }

        if (!pm_found)
        {
            controlled_pms[*nof_aggregated_pms].phy = pm_first_phy + phy_offset;
            controlled_pms[*nof_aggregated_pms].type = pm_type;
            pm_arr[next_free++] = tmp_pm_id;
            (*nof_aggregated_pms)++;
        }

        if (!phy_found)
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Ilkn phy id can't be found.\n");
        }
    }

exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_latch_down_get(
    int unit,
    bcm_port_t logical_port,
    int *is_latch_down)
{
    int nif_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.latch_down.get(unit, nif_handle, is_latch_down));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_latch_down_set(
    int unit,
    bcm_port_t logical_port,
    int is_latch_down)
{
    int nif_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Set data
     */
    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

    /** set data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.latch_down.set(unit, nif_handle, is_latch_down));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_loopback_original_link_training_get(
    int unit,
    bcm_port_t logical_port,
    int *link_training_enable)
{
    int fabric_handle;
    int nif_handle;
    dnx_algo_port_info_s port_info;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FABRIC(unit, port_info))
    {
        /*
         * Get data
         */
        /** get fabric handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(fabric_handle);

        /** get data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.
                        loopback_original_link_training.get(unit, fabric_handle, link_training_enable));
    }
    else
    {
        /*
         * Get data
         */
        /** get nif handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

        /** get data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.
                        loopback_original_link_training.get(unit, nif_handle, link_training_enable));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_loopback_original_link_training_set(
    int unit,
    bcm_port_t logical_port,
    int link_training_enable)
{
    int fabric_handle;
    int nif_handle;
    dnx_algo_port_info_s port_info;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FABRIC(unit, port_info))
    {
        /*
         * Set data
         */
        /** get fabric handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(fabric_handle);

        /** set data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.
                        loopback_original_link_training.set(unit, fabric_handle, link_training_enable));
    }
    else
    {
        /*
         * Set data
         */
        /** get nif handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

        /** set data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.
                        loopback_original_link_training.set(unit, nif_handle, link_training_enable));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_loopback_original_phy_lane_config_get(
    int unit,
    bcm_port_t logical_port,
    int *phy_lane_config)
{
    int fabric_handle;
    int nif_handle;
    dnx_algo_port_info_s port_info;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FABRIC(unit, port_info))
    {
        /*
         * Get data
         */
        /** get fabric handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(fabric_handle);

        /** get data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.
                        loopback_original_phy_lane_config.get(unit, fabric_handle, phy_lane_config));
    }
    else
    {
        /*
         * Get data
         */
        /** get nif handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

        /** get data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.loopback_original_phy_lane_config.get(unit, nif_handle, phy_lane_config));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_loopback_original_phy_lane_config_set(
    int unit,
    bcm_port_t logical_port,
    int phy_lane_config)
{
    int fabric_handle;
    int nif_handle;
    dnx_algo_port_info_s port_info;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FABRIC(unit, port_info))
    {
        /*
         * Set data
         */
        /** get fabric handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.fabric_handle.get(unit, logical_port, &fabric_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(fabric_handle);

        /** set data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.fabric.
                        loopback_original_phy_lane_config.set(unit, fabric_handle, phy_lane_config));
    }
    else
    {
        /*
         * Set data
         */
        /** get nif handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

        /** set data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.loopback_original_phy_lane_config.set(unit, nif_handle, phy_lane_config));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_phy_to_logical_get(
    int unit,
    int phy,
    int is_over_fabric,
    uint32 flags,
    bcm_port_t * logical_port)
{
    uint32 supported_flags;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    if (is_over_fabric)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_fabric_phy_verify(unit, phy));
        phy += dnx_data_port.general.fabric_phys_offset_get(unit);
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_nif_phy_verify(unit, phy));
    }

    /** verify flags */
    supported_flags = 0;
    SHR_IF_ERR_EXIT_WITH_LOG(utilex_bitstream_mask_verify(&flags, &supported_flags, 1),
                             "function flags does not support the requested flags 0x%x %s%s.\n", flags, EMPTY, EMPTY);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.master_logical_port.get(unit, phy, logical_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_logical_fifo_get(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    int logical_fifo_index,
    dnx_algo_port_rmc_info_t * logical_fifo_info)
{
    int nif_handle, flexe_handle;
    uint32 supported_flags;
    dnx_algo_port_info_s port_info;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));
    /** verify flags */
    supported_flags = 0;
    SHR_IF_ERR_EXIT_WITH_LOG(utilex_bitstream_mask_verify(&flags, &supported_flags, 1),
                             "function flags does not support the requested flags 0x%x %s%s.\n", flags, EMPTY, EMPTY);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FRAMER_MAC(unit, port_info, TRUE, FALSE))
    {
        /** get flexe client handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_mac_handle.get(unit, logical_port, &flexe_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

        /** get data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.
                        logical_fifos.get(unit, flexe_handle, logical_fifo_index, logical_fifo_info));
    }
    else
    {
        /** get nif handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

        /** get data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.
                        logical_fifos.get(unit, nif_handle, logical_fifo_index, logical_fifo_info));
    }
exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_logical_fifo_set(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    int logical_fifo_index,
    dnx_algo_port_rmc_info_t * logical_fifo_info)
{
    int nif_handle, flexe_handle;
    uint32 supported_flags;
    dnx_algo_port_info_s port_info;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));
    /** verify flags */
    supported_flags = 0;
    SHR_IF_ERR_EXIT_WITH_LOG(utilex_bitstream_mask_verify(&flags, &supported_flags, 1),
                             "function flags does not support the requested flags 0x%x %s%s.\n", flags, EMPTY, EMPTY);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.info.get(unit, logical_port, &port_info));

    if (DNX_ALGO_PORT_TYPE_IS_FRAMER_MAC(unit, port_info, TRUE, TRUE))
    {
        /** get flexe client handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_mac_handle.get(unit, logical_port, &flexe_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

        /** get data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.
                        logical_fifos.set(unit, flexe_handle, logical_fifo_index, *logical_fifo_info));
    }
    else
    {
        /** get nif handle */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
        DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

        /** get data */
        SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.
                        logical_fifos.set(unit, nif_handle, logical_fifo_index, *logical_fifo_info));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_port_rmc_info_t_init(
    int unit,
    dnx_algo_port_rmc_info_t * rmc_info)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * initialize rmc info to invalid values
     */
    sal_memset(rmc_info, 0, sizeof(dnx_algo_port_rmc_info_t));
    rmc_info->rmc_id = -1;
    rmc_info->sch_priority = bcmPortNifSchedulerLow;
    rmc_info->prd_priority = -1;

    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_logical_fifo_pbmp_get(
    int unit,
    bcm_port_t logical_port,
    uint32 flags,
    bcm_pbmp_t * logical_fifo_pbmp)
{
    int ii, nof_priority_groups;
    dnx_algo_port_rmc_info_t rmc;
    SHR_FUNC_INIT_VARS(unit);

    _SHR_PBMP_CLEAR(*logical_fifo_pbmp);

    nof_priority_groups = dnx_data_nif.eth.priority_groups_nof_get(unit);
    /*
     * iterate over all logical fifos of the port
     */
    for (ii = 0; ii < nof_priority_groups; ++ii)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_nif_logical_fifo_get(unit, logical_port, 0, ii, &rmc));
        if (rmc.rmc_id != DNX_ALGO_PORT_INVALID)
        {
            /*
             * add each logical fifo id to bitmap
             */
            _SHR_PBMP_PORT_ADD(*logical_fifo_pbmp, rmc.rmc_id);
        }
    }
exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_interface_to_port_info_get(
    int unit,
    bcm_port_if_t interface_type,
    dnx_algo_port_info_indicator_t * indicator,
    dnx_algo_port_info_s * port_info)
{
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(port_info, 0, sizeof(dnx_algo_port_info_s));

    switch (interface_type)
    {
        case BCM_PORT_IF_NULL:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_INVALID;
            break;
        }
        case BCM_PORT_IF_SFI:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_FABRIC;
            port_info->is_fabric = 1;
            port_info->is_imb = 1;
            break;
        }
        case BCM_PORT_IF_RCY:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_RCY;
            port_info->is_ing_tm = 1;
            port_info->is_egr_tm = 1;
            port_info->is_pp_dsp = 1;
            port_info->is_sch = 1;
            port_info->is_channelized = 1;
            port_info->is_ing_pp = 1;
            port_info->is_egr_pp = 1;
            if (indicator->is_mc)
            {
                port_info->is_mc = 1;
            }
            break;
        }
        case BCM_PORT_IF_RCY_MIRROR:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_RCY_MIRROR;
            port_info->is_ing_tm = 1;
            port_info->is_ing_pp = 1;
            port_info->is_channelized = 1;
            break;
        }
        case BCM_PORT_IF_CPU:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_CPU;
            port_info->is_ing_tm = 1;
            port_info->is_egr_tm = 1;
            port_info->is_pp_dsp = 1;
            port_info->is_sch = 1;
            port_info->is_channelized = 1;
            port_info->is_ing_pp = 1;
            port_info->is_egr_pp = 1;
            break;
        }
        case BCM_PORT_IF_ERP:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_ERP;
            port_info->is_pp_dsp = 1;
            port_info->is_sch = 1;
            break;
        }
        case BCM_PORT_IF_SCH:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_SCH_ONLY;
            port_info->is_sch = 1;
            break;
        }
        case BCM_PORT_IF_OLP:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_OLP;
            port_info->is_ing_tm = 1;
            port_info->is_egr_tm = 1;
            port_info->is_pp_dsp = 1;
            port_info->is_sch = 1;
            port_info->is_channelized = 1;
            port_info->is_ing_pp = 1;
            port_info->is_egr_pp = 1;
            break;
        }
        case BCM_PORT_IF_OAMP:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_OAMP;
            port_info->is_ing_tm = 1;
            port_info->is_egr_tm = 1;
            port_info->is_pp_dsp = 1;
            port_info->is_sch = 1;
            port_info->is_channelized = 1;
            port_info->is_ing_pp = 1;
            port_info->is_egr_pp = 1;
            break;
        }
        case BCM_PORT_IF_EVENTOR:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_EVENTOR;
            port_info->is_ing_tm = 1;
            port_info->is_egr_tm = 1;
            port_info->is_pp_dsp = 1;
            port_info->is_sch = 1;
            port_info->is_channelized = 1;
            port_info->is_ing_pp = 1;
            port_info->is_egr_pp = 1;
            break;
        }
        case BCM_PORT_IF_SAT:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_SAT;
            port_info->is_ing_tm = 1;
            port_info->is_egr_tm = 1;
            port_info->is_pp_dsp = 1;
            port_info->is_sch = 1;
            port_info->is_channelized = 1;
            port_info->is_ing_pp = 1;
            port_info->is_egr_pp = 1;
            break;
        }
        case BCM_PORT_IF_ILKN:
        {
            if (indicator->is_cross_connect)
            {
                port_info->port_type = DNX_ALGO_PORT_TYPE_NIF_ILKN;
                port_info->is_nif = 1;
                port_info->is_nif_ilkn = 1;
                port_info->is_imb = 1;
                port_info->is_l1 = 1;
                port_info->is_channelized = 1;
            }
            else if (indicator->is_elk)
            {
                port_info->port_type = DNX_ALGO_PORT_TYPE_NIF_ILKN;
                port_info->is_nif = 1;
                port_info->is_nif_ilkn = 1;
                port_info->is_elk = 1;
                port_info->is_imb = 1;
            }
            else
            {
                port_info->port_type = DNX_ALGO_PORT_TYPE_NIF_ILKN;
                port_info->is_nif = 1;
                port_info->is_nif_ilkn = 1;
                port_info->is_imb = 1;
                port_info->is_ing_tm = 1;
                port_info->is_egr_tm = 1;
                port_info->is_pp_dsp = 1;
                port_info->is_sch = 1;
                port_info->is_channelized = 1;
                port_info->is_ing_pp = 1;
                port_info->is_egr_pp = 1;
            }
            break;
        }
        case BCM_PORT_IF_XFI:
        case BCM_PORT_IF_XLAUI:
        case BCM_PORT_IF_XLAUI2:
        case BCM_PORT_IF_CAUI:
        case BCM_PORT_IF_NIF_ETH:
        {

            if (indicator->is_flexe_phy)
            {
                port_info->port_type = DNX_ALGO_PORT_TYPE_FLEXE_PHY;
                port_info->is_nif = 1;
                port_info->is_nif_eth = 1;
                port_info->is_imb = 1;
                port_info->is_flexe_phy = 1;
                port_info->is_framer_phy = 1;
            }
            else if (indicator->is_cross_connect)
            {
                port_info->port_type = DNX_ALGO_PORT_TYPE_NIF_ETH;
                port_info->is_nif = 1;
                port_info->is_nif_eth = 1;
                port_info->is_imb = 1;
                port_info->is_l1 = 1;
                port_info->is_channelized = 1;

                if (dnx_data_nif.framer.feature_get(unit, dnx_data_nif_framer_l1_eth_supported))
                {
                    port_info->is_framer_phy = 1;
                }
            }
            else if (indicator->is_framer_mgmt)
            {
                port_info->port_type = DNX_ALGO_PORT_TYPE_NIF_ETH;
                port_info->is_nif = 1;
                port_info->is_nif_eth = 1;
                port_info->is_imb = 1;
                port_info->is_framer_phy = 1;
                port_info->is_framer_mgmt = 1;
            }
            else if (indicator->is_stif)
            {
                port_info->port_type = DNX_ALGO_PORT_TYPE_NIF_ETH;
                port_info->is_nif = 1;
                port_info->is_nif_eth = 1;
                port_info->is_imb = 1;
                port_info->is_stif = 1;

                /** mark STIF port as data as well (only ingress path) */
                if (indicator->is_stif_data)
                {
                    port_info->is_ing_pp = 1;
                    port_info->is_ing_tm = 1;
                }
            }
            else
            {
                port_info->port_type = DNX_ALGO_PORT_TYPE_NIF_ETH;
                port_info->is_nif = 1;
                port_info->is_nif_eth = 1;
                port_info->is_imb = 1;
                port_info->is_ing_tm = 1;
                port_info->is_egr_tm = 1;
                port_info->is_pp_dsp = 1;
                port_info->is_sch = 1;
                port_info->is_channelized = 1;
                port_info->is_ing_pp = 1;
                port_info->is_egr_pp = 1;
                if (indicator->is_mgmt)
                {
                    port_info->is_mgmt = 1;
                }
            }

            break;
        }
        case BCM_PORT_IF_FLEXE_CLIENT:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_FLEXE_CLIENT;
            port_info->is_imb = 1;
            port_info->is_flexe_client = 1;
            port_info->is_framer_client = 1;
            break;
        }
        case BCM_PORT_IF_VIRTUAL_FLEXE_CLIENT:
        {
            port_info->is_framer_client = 1;
            port_info->is_imb = 1;

            if (indicator->is_flexe_mac)
            {
                port_info->port_type = DNX_ALGO_PORT_TYPE_FRAMER_MAC;

                if (indicator->is_cross_connect)
                {
                    port_info->is_l1 = 1;
                }
                else if (indicator->is_stat_only)
                {
                    port_info->port_type = DNX_ALGO_PORT_TYPE_FRAMER_MAC;
                    port_info->is_imb = 1;
                    port_info->is_stat_only = 1;
                }
                else
                {
                    port_info->is_ing_tm = 1;
                    port_info->is_egr_tm = 1;
                    port_info->is_pp_dsp = 1;
                    port_info->is_sch = 1;
                    port_info->is_ing_pp = 1;
                    port_info->is_egr_pp = 1;

                    if (indicator->is_framer_mgmt)
                    {
                        port_info->is_framer_mgmt = 1;
                    }
                }
            }
            else if (indicator->is_flexe_sar || indicator->is_otn_sar)
            {
                port_info->port_type = DNX_ALGO_PORT_TYPE_FRAMER_SAR;

                if (dnx_data_nif.sar_client.feature_get(unit, dnx_data_nif_sar_client_is_tdm_port))
                {
                    port_info->is_ing_tm = 1;
                    port_info->is_egr_tm = 1;
                    port_info->is_pp_dsp = 1;
                    port_info->is_ing_pp = 1;
                    port_info->is_egr_pp = 1;
                }
                if (indicator->is_otn_sar)
                {
                    port_info->is_otn_sar = 1;
                }
            }
            break;
        }
        case BCM_PORT_IF_CRPS:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_CRPS;
            port_info->is_ing_tm = 1;
            port_info->is_ing_pp = 1;
            break;
        }
        case BCM_PORT_IF_OTN:
        {
            port_info->port_type = DNX_ALGO_PORT_TYPE_OTN_PHY;
            port_info->is_nif = 1;
            port_info->is_imb = 1;
            /*
             * port_info->is_framer_phy = 1;
             */
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported interface type (%d).\n", interface_type);
            break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_to_interface_type_get(
    int unit,
    dnx_algo_port_info_s port_info,
    dnx_algo_port_info_indicator_t * indicator,
    bcm_port_if_t * interface_type)
{
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(indicator, 0, sizeof(dnx_algo_port_info_indicator_t));
    switch (port_info.port_type)
    {
        case DNX_ALGO_PORT_TYPE_INVALID:
        {
            *interface_type = BCM_PORT_IF_NULL;
            break;
        }
        case DNX_ALGO_PORT_TYPE_FABRIC:
        {
            *interface_type = BCM_PORT_IF_SFI;
            break;
        }
        case DNX_ALGO_PORT_TYPE_RCY:
        {
            *interface_type = BCM_PORT_IF_RCY;
            if (DNX_ALGO_PORT_TYPE_IS_MC(unit, port_info))
            {
                indicator->is_mc = 1;
            }
            break;
        }
        case DNX_ALGO_PORT_TYPE_RCY_MIRROR:
        {
            *interface_type = BCM_PORT_IF_RCY_MIRROR;
            break;
        }
        case DNX_ALGO_PORT_TYPE_CPU:
        {
            *interface_type = BCM_PORT_IF_CPU;
            break;
        }
        case DNX_ALGO_PORT_TYPE_ERP:
        {
            *interface_type = BCM_PORT_IF_ERP;
            break;
        }
        case DNX_ALGO_PORT_TYPE_OLP:
        {
            *interface_type = BCM_PORT_IF_OLP;
            break;
        }
        case DNX_ALGO_PORT_TYPE_OAMP:
        {
            *interface_type = BCM_PORT_IF_OAMP;
            break;
        }
        case DNX_ALGO_PORT_TYPE_EVENTOR:
        {
            *interface_type = BCM_PORT_IF_EVENTOR;
            break;
        }
        case DNX_ALGO_PORT_TYPE_SAT:
        {
            *interface_type = BCM_PORT_IF_SAT;
            break;
        }
        case DNX_ALGO_PORT_TYPE_NIF_ILKN:
        {
            *interface_type = BCM_PORT_IF_ILKN;
            break;
        }
        case DNX_ALGO_PORT_TYPE_NIF_ETH:
        {
            *interface_type = BCM_PORT_IF_NIF_ETH;
            break;
        }
        case DNX_ALGO_PORT_TYPE_FLEXE_PHY:
        {
            *interface_type = BCM_PORT_IF_NIF_ETH;
            indicator->is_flexe_phy = 1;
            break;
        }
        case DNX_ALGO_PORT_TYPE_FRAMER_MAC:
        {
            *interface_type = BCM_PORT_IF_VIRTUAL_FLEXE_CLIENT;
            indicator->is_flexe_mac = 1;
            break;
        }
        case DNX_ALGO_PORT_TYPE_FRAMER_SAR:
        {
            *interface_type = BCM_PORT_IF_VIRTUAL_FLEXE_CLIENT;
            break;
        }
        case DNX_ALGO_PORT_TYPE_FLEXE_CLIENT:
        {
            *interface_type = BCM_PORT_IF_FLEXE_CLIENT;
            break;
        }
        case DNX_ALGO_PORT_TYPE_SCH_ONLY:
        {
            *interface_type = BCM_PORT_IF_SCH;
            break;
        }
        case DNX_ALGO_PORT_TYPE_CRPS:
        {
            *interface_type = BCM_PORT_IF_CRPS;
            break;
        }
        case DNX_ALGO_PORT_TYPE_OTN_PHY:
        {
            *interface_type = BCM_PORT_IF_OTN;
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Unsupported port type (%d).\n", port_info.port_type);
            break;
        }
    }

    if (DNX_ALGO_PORT_TYPE_IS_NIF_ILKN_ELK(unit, port_info))
    {
        indicator->is_elk = 1;
    }
    if (DNX_ALGO_PORT_TYPE_IS_NIF_ETH_STIF(unit, port_info))
    {
        indicator->is_stif = 1;

        /** some STIF ports support data on ingress path */
        if (DNX_ALGO_PORT_TYPE_IS_ING_TM(unit, port_info))
        {
            indicator->is_stif_data = 1;
        }
    }

    if (DNX_ALGO_PORT_TYPE_IS_NIF_ETH_MGMT(unit, port_info))
    {
        indicator->is_mgmt = 1;
    }

    if (DNX_ALGO_PORT_TYPE_IS_L1(unit, port_info))
    {
        indicator->is_cross_connect = 1;
    }

    if (DNX_ALGO_PORT_TYPE_IS_FRAMER_MAC_STAT(unit, port_info))
    {
        indicator->is_stat_only = 1;
    }

    if (DNX_ALGO_PORT_TYPE_IS_FRAMER_MGMT(unit, port_info))
    {
        indicator->is_framer_mgmt = 1;
    }
    if (DNX_ALGO_PORT_TYPE_IS_FRAMER_SAR(unit, port_info, TRUE))
    {
        if (DNX_ALGO_PORT_TYPE_IS_OTN_SAR(unit, port_info))
        {
            indicator->is_otn_sar = 1;
        }
        else
        {
            indicator->is_flexe_sar = 1;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_legacy_interface_to_nof_lanes_get(
    int unit,
    bcm_port_if_t interface_type,
    int *nof_lanes)
{
    SHR_FUNC_INIT_VARS(unit);

    switch (interface_type)
    {
        case BCM_PORT_IF_XFI:
        {
            *nof_lanes = 1;
            break;
        }
        case BCM_PORT_IF_XLAUI:
        case BCM_PORT_IF_CAUI:
        {
            *nof_lanes = 4;
            break;
        }
        case BCM_PORT_IF_XLAUI2:
        {
            *nof_lanes = 2;
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported interface type (%d).\n", interface_type);
            break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_egr_if_unset(
    int unit,
    bcm_port_t logical_port)
{
    dnx_algo_port_db_2d_handle_t tm_if_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to TM IF DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.tm_interface_handle.get(unit, logical_port, &tm_if_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(tm_if_handle);

    /*
     * Set Data to default
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                    egr_if.set(unit, tm_if_handle.h0, tm_if_handle.h1, DNX_ALGO_PORT_EGR_IF_INVALID));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See algo_port_mgmt.h file
 */
shr_error_e
dnx_algo_port_egr_if_get(
    int unit,
    bcm_port_t logical_port,
    int *if_id)
{
    dnx_algo_port_db_2d_handle_t tm_if_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to TM IF DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.tm_interface_handle.get(unit, logical_port, &tm_if_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(tm_if_handle);

    /*
     * Get Data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.egr_if.get(unit, tm_if_handle.h0, tm_if_handle.h1, if_id));

exit:
    SHR_FUNC_EXIT;
}

/** See algo_port_mgmt.h file */
shr_error_e
dnx_algo_port_ch_egr_if_get(
    int unit,
    bcm_port_t logical_port,
    int *ch_if_id)
{
    dnx_algo_port_db_2d_handle_t tm_if_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to TM IF DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.tm_interface_handle.get(unit, logical_port, &tm_if_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(tm_if_handle);

    /** Get Data */
    if (dnx_data_egr_queuing_v1.
        egress_interfaces.feature_get(unit, dnx_data_egr_queuing_v1_egress_interfaces_channelized_interface_mapping))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.ch_egr_if.get(unit, tm_if_handle.h0, tm_if_handle.h1, ch_if_id));
    }
    else
    {
        *ch_if_id = DNX_ALGO_PORT_EGR_IF_INVALID;
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_sch_if_set(
    int unit,
    bcm_port_t logical_port,
    int if_id)
{
    dnx_algo_port_db_2d_handle_t sch_if_handle;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Verify interface id */
    SHR_IF_ERR_EXIT(dnx_algo_port_sch_if_id_verify(unit, if_id));

    /** Get handle to SCH IF DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_if_handle.get(unit, logical_port, &sch_if_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(sch_if_handle);

    /*
     * Set Data
     */
    /** set scheduler interface id */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.sch_if.set(unit, sch_if_handle.h0, sch_if_handle.h1, if_id));

exit:
    SHR_FUNC_EXIT;

}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_sch_if_get(
    int unit,
    bcm_port_t logical_port,
    int *if_id)
{
    dnx_algo_port_db_2d_handle_t sch_if_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to SCH IF DB */ ;
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.sch_if_handle.get(unit, logical_port, &sch_if_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(sch_if_handle);

    /*
     * Get Data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.sch_interface.sch_if.get(unit, sch_if_handle.h0, sch_if_handle.h1, if_id));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_tdm_set(
    int unit,
    bcm_port_t logical_port,
    dnx_algo_port_tdm_mode_e tdm_mode)
{
    dnx_algo_port_db_2d_handle_t interface_handle;
    bcm_port_t master_tdm_logical_port, master_non_tdm_logical_port;
    bcm_port_t next_tdm_master_port, next_non_tdm_master_port;
    dnx_algo_port_state_e state;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Verify TDM mode */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.get(unit, logical_port, &state));
    if (state != DNX_ALGO_PORT_STATE_REMOVED)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_tdm_mode_supported_verify(unit, tdm_mode));
    }

    /** Get handle to TM interface DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

    /*
     * Set Data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.tdm_mode.set(unit, logical_port, tdm_mode));

    /*
     * Update tdm master port
     */
    /** get tdm master port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                    master_tdm_logical_port.get(unit, interface_handle.h0, interface_handle.h1,
                                                &master_tdm_logical_port));
    /** if first tdm port added - define as master tdm port */
    if (master_tdm_logical_port == DNX_ALGO_PORT_INVALID && tdm_mode == DNX_ALGO_PORT_TDM_MODE_BYPASS)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.master_tdm_logical_port.set(unit, interface_handle.h0,
                                                                               interface_handle.h1, logical_port));
    }

    /** if master tdm port removed / changed - define as master tdm port */
    if (master_tdm_logical_port == logical_port && tdm_mode != DNX_ALGO_PORT_TDM_MODE_BYPASS)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_master_get
                        (unit, logical_port, DNX_ALGO_PORT_MASTER_F_NEXT | DNX_ALGO_PORT_MASTER_F_TDM_BYPASS,
                         &next_tdm_master_port));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        master_tdm_logical_port.set(unit, interface_handle.h0, interface_handle.h1,
                                                    next_tdm_master_port));
    }

    /*
     * Update Non TDM master port
     */
     /** get non tdm master port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                    master_non_tdm_logical_port.get(unit, interface_handle.h0, interface_handle.h1,
                                                    &master_non_tdm_logical_port));
    /** if first non-tdm port added - define next one as master non-tdm port */
    if (master_non_tdm_logical_port == DNX_ALGO_PORT_INVALID && tdm_mode != DNX_ALGO_PORT_TDM_MODE_BYPASS)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.master_non_tdm_logical_port.set(unit, interface_handle.h0,
                                                                                   interface_handle.h1, logical_port));
    }

    /** if master non-tdm port removed / changed - define next one as master non-tdm port */
    if (master_non_tdm_logical_port == logical_port
        && (tdm_mode == DNX_ALGO_PORT_TDM_MODE_BYPASS || tdm_mode == DNX_ALGO_PORT_TDM_MODE_INVALID))
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_master_get
                        (unit, logical_port, DNX_ALGO_PORT_MASTER_F_NEXT | DNX_ALGO_PORT_MASTER_F_NON_TDM_BYPASS,
                         &next_non_tdm_master_port));
        SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                        master_non_tdm_logical_port.set(unit, interface_handle.h0, interface_handle.h1,
                                                        next_non_tdm_master_port));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_tdm_get(
    int unit,
    bcm_port_t logical_port,
    dnx_algo_port_tdm_mode_e * tdm_mode)
{
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get Data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.tdm_mode.get(unit, logical_port, tdm_mode));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_if_tdm_mode_get(
    int unit,
    bcm_port_t logical_port,
    dnx_algo_port_if_tdm_mode_e * if_tdm_mode)
{
    dnx_algo_port_db_2d_handle_t interface_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to tm interface */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.interface_handle.get(unit, logical_port, &interface_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(interface_handle);

    /*
     * Get data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.interface.
                    tdm_mode.get(unit, interface_handle.h0, interface_handle.h1, if_tdm_mode));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_flexe_client_index_to_port_get(
    int unit,
    dnx_algo_port_type_e port_type,
    int client_index,
    bcm_port_t * logical_port)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_flexe_client_index_valid_verify(unit, port_type, client_index));

    flexe_handle = client_index;
    if (port_type == DNX_ALGO_PORT_TYPE_FLEXE_CLIENT)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.master_logical_port.get(unit, flexe_handle, logical_port));
    }
    else if (port_type == DNX_ALGO_PORT_TYPE_FRAMER_MAC)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.master_logical_port.get(unit, flexe_handle, logical_port));
    }
    else if (port_type == DNX_ALGO_PORT_TYPE_FRAMER_SAR)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.master_logical_port.get(unit, flexe_handle, logical_port));
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Unexpected port type\n");
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_flexe_client_is_bypass_get(
    int unit,
    bcm_port_t logical_port,
    int *is_bypass)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get flexe client handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_client_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.is_bypass.get(unit, flexe_handle, is_bypass));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_flexe_client_is_bypass_set(
    int unit,
    bcm_port_t logical_port,
    int is_bypass)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get flexe client handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_client_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.is_bypass.set(unit, flexe_handle, is_bypass));

exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_flexe_client_bas_period_get(
    int unit,
    bcm_port_t logical_port,
    bcm_port_flexe_oam_base_period_t * period)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get flexe client handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_client_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.bas_period.get(unit, flexe_handle, period));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_flexe_client_bas_period_set(
    int unit,
    bcm_port_t logical_port,
    bcm_port_flexe_oam_base_period_t period)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get flexe client handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_client_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.client.bas_period.set(unit, flexe_handle, period));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_flexe_sar_virtual_flexe_channel_get(
    int unit,
    bcm_port_t logical_port,
    int *channel)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get flexe client handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_sar_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.virtual_flexe_channel.get(unit, flexe_handle, channel));
exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_flexe_sar_is_eth_get(
    int unit,
    bcm_port_t logical_port,
    int is_rx,
    int *is_eth)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get flexe client handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_sar_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

    /** get data */
    if (is_rx)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.rx_is_eth.get(unit, flexe_handle, is_eth));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.tx_is_eth.get(unit, flexe_handle, is_eth));
    }
exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_flexe_sar_is_eth_set(
    int unit,
    bcm_port_t logical_port,
    int is_rx,
    int is_eth)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get flexe client handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_sar_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

    /** configure data */
    if (is_rx)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.rx_is_eth.set(unit, flexe_handle, is_eth));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.tx_is_eth.set(unit, flexe_handle, is_eth));
    }
exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_sar_channel_to_logical_get(
    int unit,
    int client_channel,
    bcm_port_t * logical_port)
{
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    if (client_channel < 0 || client_channel >= dnx_data_nif.sar_client.nof_clients_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "SAR channel ID is out of range.\n");
    }
    /** Get logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.sar.master_logical_port.get(unit, client_channel, logical_port));
exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_framer_mac_channel_to_logical_get(
    int unit,
    int client_channel,
    bcm_port_t * logical_port)
{
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    if (client_channel < 0 || client_channel >= dnx_data_nif.mac_client.nof_clients_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Framer MAC channel ID is out of range.\n");
    }
    /** Get logical port */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.master_logical_port.get(unit, client_channel, logical_port));
exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_framer_mac_loopback_enable_get(
    int unit,
    bcm_port_t logical_port,
    int *loopback_enable)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /*
     * Get BusB loopback status
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_mac_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.loopback_enable.get(unit, flexe_handle, loopback_enable));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_framer_mac_loopback_enable_set(
    int unit,
    bcm_port_t logical_port,
    int loopback_enable)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));
    /*
     * Set BusB loopback status
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_mac_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.mac.loopback_enable.set(unit, flexe_handle, loopback_enable));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_port_flexe_core_port_get(
    int unit,
    bcm_port_t logical_port,
    int *core_port)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get flexe phy handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_phy_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.phy.core_port.get(unit, flexe_handle, core_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_flexe_core_port_set(
    int unit,
    bcm_port_t logical_port,
    int core_port)
{
    int flexe_handle;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get flexe phy handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.flexe_phy_handle.get(unit, logical_port, &flexe_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(flexe_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.flexe.phy.core_port.set(unit, flexe_handle, core_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
void
dnx_algo_port_db_skip_first_ud_header_size_print_cb(
    int unit,
    const void *data)
{
#ifdef DNX_SW_STATE_DIAGNOSTIC
    dnx_algo_skip_first_header_info_t *first_header_size = (dnx_algo_skip_first_header_info_t *) data;
#endif
    SW_STATE_PRETTY_PRINT_INIT_VARIABLES();
    SW_STATE_PRETTY_PRINT_ADD_LINE(SW_STATE_PRETTY_PRINT_TYPE_UINT32, "first header size",
                                   first_header_size->first_header_size_to_skip, NULL, NULL);
    SW_STATE_PRETTY_PRINT_ADD_LINE(SW_STATE_PRETTY_PRINT_TYPE_UINT32, "first header size",
                                   first_header_size->port_type, NULL, NULL);
    SW_STATE_PRETTY_PRINT_ADD_LINE(SW_STATE_PRETTY_PRINT_TYPE_UINT32, "first header size",
                                   first_header_size->is_before, NULL, NULL);
    SW_STATE_PRETTY_PRINT_ADD_LINE(SW_STATE_PRETTY_PRINT_TYPE_UINT32, "first header size",
                                   first_header_size->is_after, NULL, NULL);
    SW_STATE_PRETTY_PRINT_FINISH();
    return;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_counter_sets_get(
    int unit,
    bcm_port_t logical_port,
    int *nof_types,
    dnx_algo_port_mib_counter_set_type_e counter_set_types[DNX_ALGO_PORT_COUNTER_SETS_MAX])
{
    dnx_algo_port_info_s port_info;
    dnx_algo_port_ethu_access_info_t ethu_info;
    int ilkn_over_fabric_port;

    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get port type */
    SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, logical_port, &port_info));

    *nof_types = 0;

    /** mark port as fabric */
    if (DNX_ALGO_PORT_TYPE_IS_FABRIC(unit, port_info))
    {
        /** verify array size to avoid memory corruption */
        SHR_MAX_VERIFY(*nof_types, (DNX_ALGO_PORT_COUNTER_SETS_MAX - 1), _SHR_E_INTERNAL,
                       "Port=%d counter_set_types array size=%d is too small, required=%d",
                       logical_port, DNX_ALGO_PORT_COUNTER_SETS_MAX, *nof_types);

        counter_set_types[*nof_types] = DNX_ALGO_PORT_MIB_COUNTER_SET_TYPE_FABRIC;
        (*nof_types)++;
    }

    /** mark port as NIF */
    if (DNX_ALGO_PORT_TYPE_IS_NIF(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(ELK, STIF, L1, FLEXE, MGMT, OTN_PHY)))
    {
        /** verify array size to avoid memory corruption */
        SHR_MAX_VERIFY(*nof_types, (DNX_ALGO_PORT_COUNTER_SETS_MAX - 1), _SHR_E_INTERNAL,
                       "Port=%d counter_set_types array size=%d is too small, required=%d",
                       logical_port, DNX_ALGO_PORT_COUNTER_SETS_MAX, *nof_types);

        counter_set_types[*nof_types] = DNX_ALGO_PORT_MIB_COUNTER_SET_TYPE_NIF;
        (*nof_types)++;
    }

    /** mark port as ILKN */
    if (DNX_ALGO_PORT_TYPE_IS_NIF_ILKN(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(ELK, L1)))
    {
        /** verify array size to avoid memory corruption */
        SHR_MAX_VERIFY(*nof_types, (DNX_ALGO_PORT_COUNTER_SETS_MAX - 1), _SHR_E_INTERNAL,
                       "Port=%d counter_set_types array size=%d is too small, required=%d",
                       logical_port, DNX_ALGO_PORT_COUNTER_SETS_MAX, *nof_types);

        counter_set_types[*nof_types] = DNX_ALGO_PORT_MIB_COUNTER_SET_TYPE_ILKN;
        (*nof_types)++;

        /** mark port as ILKN over fabric */
        SHR_IF_ERR_EXIT(dnx_algo_port_nif_ilkn_is_over_fabric_get(unit, logical_port, &ilkn_over_fabric_port));
        if (ilkn_over_fabric_port)
        {
            /** verify array size to avoid memory corruption */
            SHR_MAX_VERIFY(*nof_types, (DNX_ALGO_PORT_COUNTER_SETS_MAX - 1), _SHR_E_INTERNAL,
                           "Port=%d counter_set_types array size=%d is too small, required=%d",
                           logical_port, DNX_ALGO_PORT_COUNTER_SETS_MAX, *nof_types);

            counter_set_types[*nof_types] = DNX_ALGO_PORT_MIB_COUNTER_SET_TYPE_ILKN_OVER_FABRIC;
            (*nof_types)++;
        }
    }

    /** mark port as NIF_ETH */
    if (DNX_ALGO_PORT_TYPE_IS_NIF_ETH(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(STIF, L1, MGMT)))
    {
        /** verify array size to avoid memory corruption */
        SHR_MAX_VERIFY(*nof_types, (DNX_ALGO_PORT_COUNTER_SETS_MAX - 1), _SHR_E_INTERNAL,
                       "Port=%d counter_set_types array size=%d is too small, required=%d",
                       logical_port, DNX_ALGO_PORT_COUNTER_SETS_MAX, *nof_types);

        counter_set_types[*nof_types] = DNX_ALGO_PORT_MIB_COUNTER_SET_TYPE_NIF_ETH;
        (*nof_types)++;

        /** mark port PM type (CDU/CLU)) */
        SHR_IF_ERR_EXIT(dnx_algo_port_ethu_access_info_get(unit, logical_port, &ethu_info));

        /** verify array size to avoid memory corruption */
        SHR_MAX_VERIFY(*nof_types, (DNX_ALGO_PORT_COUNTER_SETS_MAX - 1), _SHR_E_INTERNAL,
                       "Port=%d counter_set_types array size=%d is too small, required=%d",
                       logical_port, DNX_ALGO_PORT_COUNTER_SETS_MAX, *nof_types);

        counter_set_types[*nof_types] = dnx_data_port.imb.imb_type_info_get(unit, ethu_info.imb_type)->mib_type;
        (*nof_types)++;
    }

    /** mark port as flexe mac */
    if (DNX_ALGO_PORT_TYPE_IS_FRAMER_MAC(unit, port_info, 1, 1))
    {
        /** verify array size to avoid memory corruption */
        SHR_MAX_VERIFY(*nof_types, (DNX_ALGO_PORT_COUNTER_SETS_MAX - 1), _SHR_E_INTERNAL,
                       "Port=%d counter_set_types array size=%d is too small, required=%d",
                       logical_port, DNX_ALGO_PORT_COUNTER_SETS_MAX, *nof_types);

        counter_set_types[*nof_types] = DNX_ALGO_PORT_MIB_COUNTER_SET_TYPE_FLEX_MAC;
        (*nof_types)++;
    }
    /** mark port as cpu */
    if (DNX_ALGO_PORT_TYPE_IS_CPU(unit, port_info))
    {
        /** verify array size to avoid memory corruption */
        SHR_MAX_VERIFY(*nof_types, (DNX_ALGO_PORT_COUNTER_SETS_MAX - 1), _SHR_E_INTERNAL,
                       "Port=%d counter_set_types array size=%d is too small, required=%d",
                       logical_port, DNX_ALGO_PORT_COUNTER_SETS_MAX, *nof_types);

        counter_set_types[*nof_types] = DNX_ALGO_PORT_MIB_COUNTER_SET_TYPE_CPU;
        (*nof_types)++;
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_is_valid_get(
    int unit,
    bcm_port_t logical_port,
    int *is_valid)
{
    dnx_algo_port_state_e state;

    SHR_FUNC_INIT_VARS(unit);

    *is_valid = FALSE;

    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.state.get(unit, logical_port, &state));
    if (state != DNX_ALGO_PORT_STATE_INVALID)
    {
        *is_valid = TRUE;
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_ptc_get(
    int unit,
    bcm_port_t logical_port,
    bcm_core_t * core,
    int *ptc)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_headers.
        system_headers.feature_get(unit, dnx_data_headers_system_headers_system_headers_ibch1_supported))
    {
        /** Verify logical port */
        SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

        SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.ptc.get(unit, logical_port, ptc));
        DNX_ALGO_PORT_HANDLE_VERIFY(*ptc);

        SHR_IF_ERR_EXIT(dnx_algo_port_core_get(unit, logical_port, core));
    }
exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_flr_fw_support_get(
    int unit,
    bcm_port_t logical_port,
    int *is_supported)
{
    int nif_handle;

    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.flr_fw_support.get(unit, nif_handle, is_supported));

exit:
    SHR_FUNC_EXIT;
}
/*
 * See .h file
 */
shr_error_e
dnx_algo_port_nif_ext_txpi_enable_get(
    int unit,
    bcm_port_t logical_port,
    int *enable)
{
    int nif_handle;

    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** get nif handle */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.nif_handle.get(unit, logical_port, &nif_handle));
    DNX_ALGO_PORT_HANDLE_VERIFY(nif_handle);

    /** get data */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.nif.ext_txpi_enable.get(unit, nif_handle, enable));

exit:
    SHR_FUNC_EXIT;
}
/*
 * See algo_port_mgmt.h file
 */
shr_error_e
dnx_algo_port_forward_to_rcy_mirror_port_get(
    int unit,
    bcm_port_t logical_port,
    bcm_port_t * rcy_mirror_port)
{
    dnx_algo_port_db_2d_handle_t tm_if_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to TM IF DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.tm_interface_handle.get(unit, logical_port, &tm_if_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(tm_if_handle);

    /*
     * Get Data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.rcy_mirror_logical_port.get(unit, tm_if_handle.h0, tm_if_handle.h1,
                                                                              rcy_mirror_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See algo_port_mgmt.h file
 */
shr_error_e
dnx_algo_port_forward_to_rcy_mirror_port_set(
    int unit,
    bcm_port_t logical_port,
    bcm_port_t rcy_mirror_port)
{
    dnx_algo_port_db_2d_handle_t tm_if_handle;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify
     */
    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, logical_port));

    /** Get handle to TM IF DB */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.logical.tm_interface_handle.get(unit, logical_port, &tm_if_handle));
    DNX_ALGO_PORT_2D_HANDLE_VERIFY(tm_if_handle);

    /*
     * Set Data
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_db.tm_interface.
                    rcy_mirror_logical_port.set(unit, tm_if_handle.h0, tm_if_handle.h1, rcy_mirror_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See algo_port_mgmt.h file
 */
shr_error_e
dnx_algo_port_forward_port_get(
    int unit,
    bcm_port_t logical_port,
    bcm_port_t * forward_port)
{
    bcm_pbmp_t master_tm_ports;
    bcm_port_t port_i, rcy_mirror_port_i;
    bcm_core_t core;

    SHR_FUNC_INIT_VARS(unit);

    *forward_port = DNX_ALGO_PORT_INVALID;

    /** Get all egress tm master ports */
    SHR_IF_ERR_EXIT(dnx_algo_port_core_get(unit, logical_port, &core));
    SHR_IF_ERR_EXIT(dnx_algo_port_logicals_get
                    (unit, core, DNX_ALGO_PORT_LOGICALS_TYPE_TM_EGR_QUEUING,
                     DNX_ALGO_PORT_LOGICALS_F_MASTER_ONLY, &master_tm_ports));
    /** search for the mapped forward port */
    BCM_PBMP_ITER(master_tm_ports, port_i)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_forward_to_rcy_mirror_port_get(unit, port_i, &rcy_mirror_port_i));
        if (logical_port == rcy_mirror_port_i)
        {
            *forward_port = port_i;
            break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - returns logical port if fabric gport is provided
 */

shr_error_e
dnx_algo_port_fabric_logical_port_get(
    int unit,
    bcm_port_t fabric_gport,
    bcm_port_t * logical_port)
{
    int link = 0;
    SHR_FUNC_INIT_VARS(unit);

    if (!BCM_GPORT_IS_LOCAL_FABRIC(fabric_gport))
    {
        SHR_ERR_EXIT(_SHR_E_PORT,
                     "Invalid gport provided %d. API works only with fabric gport as input. Please use BCM_GPORT_LOCAL_FABRIC_SET.",
                     fabric_gport);
    }

    /**
     * IN FAP case fmac_lane and link are practically the same
     */
    link = BCM_GPORT_LOCAL_FABRIC_GET(fabric_gport);
    if (link > dnx_data_fabric.links.nof_links_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PORT, "Invalid link encoded %d.", link);
    }

    *logical_port = link + dnx_data_port.general.fabric_port_base_get(unit);

    /**
     * Above calculation is hardcoded but we still are not sure if the link is probed
     */
    SHR_INVOKE_VERIFY_DNXC(dnx_algo_port_valid_verify(unit, *logical_port));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_algo_port_otn_phy_resource_validate(
    int unit,
    bcm_port_resource_t * resource)
{
    bcm_pbmp_t phys, phy_lanes, phy_lanes_fold;
    soc_dnxc_lane_map_db_map_t lane2serdes;
    int nof_phys, nof_lanes, nof_logical_lanes;
    int first, base_phy_in_pm;
    int first_phy = -1, first_phy_fold = -1, last_phy = -1;
    const int supported_lane_number[] = { 1, 2, 4, 8 };
    int nof_cdu_phys_in_pm;
    dnx_algo_lane_map_type_e type;
    int i, rv, start, end;

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(resource, _SHR_E_MEMORY, "Should not be a NULL pointer!\n");

    BCM_PBMP_CLEAR(phys);
    BCM_PBMP_CLEAR(phy_lanes);
    BCM_PBMP_CLEAR(phy_lanes_fold);

    /** Verify the front panel lane number */
    SHR_IF_ERR_EXIT(dnx_algo_port_nif_phys_get(unit, resource->port, 0, &phys));
    if (BCM_PBMP_IS_NULL(phys))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The phys associated to port %d should not be NULL bitmap.\n", resource->port);
    }
    /** Verify the lane2serdes mapping */
    nof_phys = 0;
    BCM_PBMP_ITER(phys, i)
    {
        type = DNX_ALGO_LANE_MAP_NIF_SIDE;
        SHR_IF_ERR_EXIT(dnx_algo_lane_map_lane_id_to_serdes_map_get(unit, type, i, &lane2serdes));
        SHR_VAL_VERIFY(lane2serdes.rx_id, lane2serdes.tx_id, _SHR_E_CONFIG,
                       "The tx_id and rx_id of serdes should be the same in OTN PHY interface.\n");
        BCM_PBMP_PORT_ADD(phy_lanes, lane2serdes.rx_id);
        nof_phys++;
    }

    /** Verify the number of physical lanes */
    for (i = 0; i < COUNTOF(supported_lane_number); i++)
    {
        if (nof_phys == supported_lane_number[i])
        {
            break;
        }
    }
    SHR_MAX_VERIFY(i, COUNTOF(supported_lane_number) - 1, _SHR_E_PARAM, "Invalid number of lanses(%d).\n", nof_phys);

    /** Verify the physical lanes */
    BCM_PBMP_ITER(phy_lanes, i)
    {
        if (first_phy == -1)
        {
            first_phy = i;
        }
        last_phy = i;
    }
    SHR_RANGE_VERIFY(first_phy, 0, dnx_data_nif.eth.total_nof_cdu_lanes_in_device_get(unit) - 1, _SHR_E_PARAM,
                     "The first phy %d is out of range [%d:0].\n", first_phy,
                     dnx_data_nif.eth.total_nof_cdu_lanes_in_device_get(unit) - 1);
    SHR_RANGE_VERIFY(last_phy, 0, dnx_data_nif.eth.total_nof_cdu_lanes_in_device_get(unit) - 1, _SHR_E_PARAM,
                     "The last phy %d is out of range [%d:0].\n", last_phy,
                     dnx_data_nif.eth.total_nof_cdu_lanes_in_device_get(unit) - 1);
    nof_cdu_phys_in_pm = dnx_data_nif.eth.nof_cdu_lanes_in_pm_get(unit);
    base_phy_in_pm = first_phy / nof_cdu_phys_in_pm * nof_cdu_phys_in_pm;
    SHR_BITCOUNT_RANGE(phy_lanes.pbits, nof_lanes, base_phy_in_pm, base_phy_in_pm + nof_cdu_phys_in_pm);
    SHR_VAL_VERIFY(nof_lanes, nof_phys, _SHR_E_CONFIG,
                   "The phy lanes for each logical port should be within a PM core.\n");

    if (DNXC_PORT_PHY_SPEED_IS_PAM4(resource->speed))
    {
        if (nof_phys == 1 || nof_phys == nof_cdu_phys_in_pm)
        {
            SHR_VAL_VERIFY(first_phy % nof_phys, 0, _SHR_E_PARAM,
                           "The first phy should be multiple of number of lanes.\n");
            SHR_BITCOUNT_RANGE(phy_lanes.pbits, nof_lanes, first_phy, nof_phys);
            SHR_VAL_VERIFY(nof_lanes, nof_phys, _SHR_E_CONFIG,
                           "The phy lanes should be consecutive in a OTN PHY interface.\n");
        }
        else
        {
            BCM_PBMP_ITER(phy_lanes, i)
            {
                BCM_PBMP_PORT_ADD(phy_lanes_fold, i % (nof_cdu_phys_in_pm / 2) + base_phy_in_pm);
            }
            BCM_PBMP_ITER(phy_lanes_fold, i)
            {
                first_phy_fold = i;
                break;
            }
            SHR_RANGE_VERIFY(first_phy_fold, 0, dnx_data_nif.eth.total_nof_cdu_lanes_in_device_get(unit) - 1,
                             _SHR_E_PARAM, "The first phy %d is out of range [%d:0].\n", first_phy_fold,
                             dnx_data_nif.eth.total_nof_cdu_lanes_in_device_get(unit) - 1);
            SHR_VAL_VERIFY(first_phy_fold % nof_phys, 0, _SHR_E_PARAM,
                           "The first phy should be multiple of number of lanes.\n");
            SHR_BITCOUNT_RANGE(phy_lanes_fold.pbits, nof_lanes, first_phy_fold, nof_phys);
            SHR_VAL_VERIFY(nof_lanes, nof_phys, _SHR_E_CONFIG,
                           "The phy lanes should be consecutive in a OTN PHY interface.\n");
        }
    }
    else
    {
        SHR_VAL_VERIFY(first_phy % nof_phys, 0, _SHR_E_PARAM, "The first phy should be multiple of number of lanes.\n");
        SHR_BITCOUNT_RANGE(phy_lanes.pbits, nof_lanes, first_phy, nof_phys);
        SHR_VAL_VERIFY(nof_lanes, nof_phys, _SHR_E_CONFIG,
                       "The phy lanes should be consecutive in a OTN PHY interface.\n");
    }

    /** Verify the framer logical lanes */
    nof_logical_lanes = DNXC_PORT_PHY_SPEED_IS_PAM4(resource->speed) ? nof_lanes * 2 : nof_lanes;
    if (resource->logical_otn_lane == BCM_PORT_RESOURCE_DEFAULT_REQUEST)
    {
        start = 0;
        end = dnx_data_nif.otn.nof_lanes_get(unit) - 1;
        rv = dnx_algo_lane_map_otn_logical_lane_find(unit, resource->port, first_phy, nof_logical_lanes, start, end,
                                                     &first);
        if (rv == _SHR_E_NOT_FOUND)
        {
            SHR_ERR_EXIT(_SHR_E_RESOURCE, "There are no free logical otn lane resource.\n");
        }
        else
        {
            SHR_IF_ERR_EXIT(rv);
        }
        SHR_RANGE_VERIFY(first, start, end, _SHR_E_PARAM, "There are no free logical otn lane resource.\n");
    }
    else
    {
        start = resource->logical_otn_lane;
        end = resource->logical_otn_lane + nof_logical_lanes - 1;
        rv = dnx_algo_lane_map_otn_logical_lane_find(unit, resource->port, first_phy, nof_logical_lanes, start, end,
                                                     &first);
        if (rv == _SHR_E_NOT_FOUND)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "The specified logical otn lane is invalid.\n");
        }
        else
        {
            SHR_IF_ERR_EXIT(rv);
        }
        SHR_RANGE_VERIFY(first, start, end, _SHR_E_PARAM, "There are no free logical otn lane resource.\n");
        SHR_VAL_VERIFY(resource->logical_otn_lane, first, _SHR_E_PARAM, "The specified logical otn lane is invalid.\n");
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * }
 */

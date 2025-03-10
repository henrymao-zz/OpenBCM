
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_SWSTATEDNX_GENERAL

#include <soc/dnx/swstate/auto_generated/access/dnx_bier_db_access.h>
#include <soc/dnx/swstate/auto_generated/diagnostic/dnx_bier_db_diagnostic.h>
#include <soc/dnx/swstate/auto_generated/layout/dnx_bier_db_layout.h>





int
dnx_bier_db_is_init(int unit, uint8 *is_init)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB,
        SW_STATE_FUNC_IS_INIT,
        DNXC_SW_STATE_NO_FLAGS);

    *is_init = (NULL != ((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID]));
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_IS_INIT_LOGGING,
        BSL_LS_SWSTATEDNX_ISINIT,
        DNX_SW_STATE_DNX_BIER_DB,
        ((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID]),
        "dnx_bier_db[%d]",
        unit);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_bier_db_init(int unit)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB,
        SW_STATE_FUNC_INIT,
        DNXC_SW_STATE_NO_FLAGS);

    DNX_SW_STATE_MODULE_INIT(
        unit,
        DNX_SW_STATE_DNX_BIER_DB,
        DNXC_SW_STATE_IMPLEMENTATION_WB,
        dnx_bier_db_t,
        DNX_SW_STATE_DNX_BIER_DB_NOF_PARAMS,
        DNXC_SW_STATE_AUTO_GENERATED_ALLOCATION,
        "dnx_bier_db_init",
        DNX_SW_STATE_DIAG_ALLOC,
        dnx_bier_db_init_layout_structure);

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_INIT_LOGGING,
        BSL_LS_SWSTATEDNX_INIT,
        DNX_SW_STATE_DNX_BIER_DB,
        ((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID]),
        "dnx_bier_db[%d]",
        unit);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_BIER_DB,
        dnx_bier_db_info,
        DNX_BIER_DB_INFO,
        DNX_SW_STATE_DIAG_ALLOC,
        ((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID]));

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_bier_db_set_size_set(int unit, uint32 set_size_idx_0, int set_size)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        set_size_idx_0,
        DNX_DATA_MAX_MULTICAST_PARAMS_NOF_MCDB_ENTRIES);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        ((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID])->set_size[set_size_idx_0],
        set_size,
        int,
        0,
        "dnx_bier_db_set_size_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        &set_size,
        "dnx_bier_db[%d]->set_size[%d]",
        unit, set_size_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        dnx_bier_db_info,
        DNX_BIER_DB_SET_SIZE_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_bier_db_set_size_get(int unit, uint32 set_size_idx_0, int *set_size)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        set_size_idx_0,
        DNX_DATA_MAX_MULTICAST_PARAMS_NOF_MCDB_ENTRIES);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        set_size);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        DNX_SW_STATE_DIAG_READ);

    *set_size = ((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID])->set_size[set_size_idx_0];
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        &((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID])->set_size[set_size_idx_0],
        "dnx_bier_db[%d]->set_size[%d]",
        unit, set_size_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__SET_SIZE,
        dnx_bier_db_info,
        DNX_BIER_DB_SET_SIZE_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_bier_db_ingress_active_set(int unit, uint32 active_idx_0, uint32 active)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        active_idx_0,
        DNX_DATA_MAX_MULTICAST_PARAMS_NOF_MCDB_ENTRIES);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        ((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID])->ingress.active[active_idx_0],
        active,
        uint32,
        0,
        "dnx_bier_db_ingress_active_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        &active,
        "dnx_bier_db[%d]->ingress.active[%d]",
        unit, active_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        dnx_bier_db_info,
        DNX_BIER_DB_INGRESS_ACTIVE_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_bier_db_ingress_active_get(int unit, uint32 active_idx_0, uint32 *active)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        active_idx_0,
        DNX_DATA_MAX_MULTICAST_PARAMS_NOF_MCDB_ENTRIES);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        active);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        DNX_SW_STATE_DIAG_READ);

    *active = ((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID])->ingress.active[active_idx_0];
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        &((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID])->ingress.active[active_idx_0],
        "dnx_bier_db[%d]->ingress.active[%d]",
        unit, active_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__INGRESS__ACTIVE,
        dnx_bier_db_info,
        DNX_BIER_DB_INGRESS_ACTIVE_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_bier_db_egress_active_set(int unit, uint32 active_idx_0, uint32 active)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        active_idx_0,
        DNX_DATA_MAX_MULTICAST_PARAMS_NOF_MCDB_ENTRIES);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        ((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID])->egress.active[active_idx_0],
        active,
        uint32,
        0,
        "dnx_bier_db_egress_active_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        &active,
        "dnx_bier_db[%d]->egress.active[%d]",
        unit, active_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        dnx_bier_db_info,
        DNX_BIER_DB_EGRESS_ACTIVE_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_bier_db_egress_active_get(int unit, uint32 active_idx_0, uint32 *active)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        active_idx_0,
        DNX_DATA_MAX_MULTICAST_PARAMS_NOF_MCDB_ENTRIES);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        active);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        DNX_SW_STATE_DIAG_READ);

    *active = ((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID])->egress.active[active_idx_0];
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        &((dnx_bier_db_t*)sw_state_roots_array[unit][DNX_BIER_DB_MODULE_ID])->egress.active[active_idx_0],
        "dnx_bier_db[%d]->egress.active[%d]",
        unit, active_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_BIER_DB__EGRESS__ACTIVE,
        dnx_bier_db_info,
        DNX_BIER_DB_EGRESS_ACTIVE_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}





dnx_bier_db_cbs dnx_bier_db = 	{
	
	dnx_bier_db_is_init,
	dnx_bier_db_init,
		{
		
		dnx_bier_db_set_size_set,
		dnx_bier_db_set_size_get}
	,
		{
		
			{
			
			dnx_bier_db_ingress_active_set,
			dnx_bier_db_ingress_active_get}
		}
	,
		{
		
			{
			
			dnx_bier_db_egress_active_set,
			dnx_bier_db_egress_active_get}
		}
	}
;
#undef BSL_LOG_MODULE

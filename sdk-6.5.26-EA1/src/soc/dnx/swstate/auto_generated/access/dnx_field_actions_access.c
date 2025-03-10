
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_SWSTATEDNX_GENERAL

#include <soc/dnx/swstate/auto_generated/access/dnx_field_actions_access.h>
#include <soc/dnx/swstate/auto_generated/diagnostic/dnx_field_actions_diagnostic.h>
#include <soc/dnx/swstate/auto_generated/layout/dnx_field_actions_layout.h>





int
dnx_field_action_sw_db_is_init(int unit, uint8 *is_init)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB,
        SW_STATE_FUNC_IS_INIT,
        DNXC_SW_STATE_NO_FLAGS);

    *is_init = (NULL != ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]));
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_IS_INIT_LOGGING,
        BSL_LS_SWSTATEDNX_ISINIT,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]),
        "dnx_field_action_sw_db[%d]",
        unit);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_init(int unit)
{
    DNX_SW_STATE_DEFAULT_VALUE_DEFS;
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB,
        SW_STATE_FUNC_INIT,
        DNXC_SW_STATE_NO_FLAGS);

    DNX_SW_STATE_MODULE_INIT(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB,
        DNXC_SW_STATE_IMPLEMENTATION_WB,
        dnx_field_action_sw_db_t,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB_NOF_PARAMS,
        DNXC_SW_STATE_AUTO_GENERATED_ALLOCATION,
        "dnx_field_action_sw_db_init",
        DNX_SW_STATE_DIAG_ALLOC,
        dnx_field_actions_init_layout_structure);

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_INIT_LOGGING,
        BSL_LS_SWSTATEDNX_INIT,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]),
        "dnx_field_action_sw_db[%d]",
        unit);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO,
        DNX_SW_STATE_DIAG_ALLOC,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]));

    DNX_SW_STATE_DEFAULT_VALUE_LOOP(def_val_idx[1], DNX_DATA_MAX_FIELD_ACTION_USER_NOF)

    DNX_SW_STATE_DEFAULT_VALUE_ASSIGN(
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[def_val_idx[1]].field_id,
        DBAL_FIELD_EMPTY);

    DNX_SW_STATE_DEFAULT_VALUE_LOOP(def_val_idx[1], DNX_DATA_MAX_FIELD_ACTION_USER_NOF)

    DNX_SW_STATE_DEFAULT_VALUE_ASSIGN(
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[def_val_idx[1]].bcm_id,
        bcmFieldActionCount);

    DNX_SW_STATE_DEFAULT_VALUE_LOOP(def_val_idx[1], DNX_DATA_MAX_FIELD_ACTION_USER_NOF)

    DNX_SW_STATE_DEFAULT_VALUE_ASSIGN(
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[def_val_idx[1]].base_dnx_action,
        DNX_FIELD_ACTION_INVALID);

    DNX_SW_STATE_DEFAULT_VALUE_LOOP(def_val_idx[1], DNX_DATA_MAX_FIELD_ACTION_PREDEFINED_NOF)

    DNX_SW_STATE_DEFAULT_VALUE_ASSIGN(
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->predefined[def_val_idx[1]].field_id,
        DBAL_FIELD_EMPTY);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_set(int unit, uint32 info_idx_0, CONST dnx_field_user_action_info_t *info)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_MEMCPY(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0],
        info,
        dnx_field_user_action_info_t,
        0,
        "dnx_field_action_sw_db_info_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        info,
        "dnx_field_action_sw_db[%d]->info[%d]",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_get(int unit, uint32 info_idx_0, dnx_field_user_action_info_t *info)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        DNX_SW_STATE_DIAG_READ);

    *info = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0];
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0],
        "dnx_field_action_sw_db[%d]->info[%d]",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_field_id_set(int unit, uint32 info_idx_0, dbal_fields_e field_id)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].field_id,
        field_id,
        dbal_fields_e,
        0,
        "dnx_field_action_sw_db_info_field_id_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        &field_id,
        "dnx_field_action_sw_db[%d]->info[%d].field_id",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_FIELD_ID_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_field_id_get(int unit, uint32 info_idx_0, dbal_fields_e *field_id)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        field_id);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        DNX_SW_STATE_DIAG_READ);

    *field_id = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].field_id;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].field_id,
        "dnx_field_action_sw_db[%d]->info[%d].field_id",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FIELD_ID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_FIELD_ID_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_flags_set(int unit, uint32 info_idx_0, dnx_field_action_flags_e flags)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].flags,
        flags,
        dnx_field_action_flags_e,
        0,
        "dnx_field_action_sw_db_info_flags_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        &flags,
        "dnx_field_action_sw_db[%d]->info[%d].flags",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_FLAGS_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_flags_get(int unit, uint32 info_idx_0, dnx_field_action_flags_e *flags)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        flags);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        DNX_SW_STATE_DIAG_READ);

    *flags = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].flags;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].flags,
        "dnx_field_action_sw_db[%d]->info[%d].flags",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__FLAGS,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_FLAGS_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_bcm_id_set(int unit, uint32 info_idx_0, int bcm_id)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].bcm_id,
        bcm_id,
        int,
        0,
        "dnx_field_action_sw_db_info_bcm_id_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        &bcm_id,
        "dnx_field_action_sw_db[%d]->info[%d].bcm_id",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_BCM_ID_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_bcm_id_get(int unit, uint32 info_idx_0, int *bcm_id)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        bcm_id);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        DNX_SW_STATE_DIAG_READ);

    *bcm_id = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].bcm_id;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].bcm_id,
        "dnx_field_action_sw_db[%d]->info[%d].bcm_id",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BCM_ID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_BCM_ID_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_valid_set(int unit, uint32 info_idx_0, uint32 valid)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].valid,
        valid,
        uint32,
        0,
        "dnx_field_action_sw_db_info_valid_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        &valid,
        "dnx_field_action_sw_db[%d]->info[%d].valid",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_VALID_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_valid_get(int unit, uint32 info_idx_0, uint32 *valid)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        valid);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        DNX_SW_STATE_DIAG_READ);

    *valid = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].valid;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].valid,
        "dnx_field_action_sw_db[%d]->info[%d].valid",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__VALID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_VALID_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_size_set(int unit, uint32 info_idx_0, uint32 size)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].size,
        size,
        uint32,
        0,
        "dnx_field_action_sw_db_info_size_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        &size,
        "dnx_field_action_sw_db[%d]->info[%d].size",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_SIZE_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_size_get(int unit, uint32 info_idx_0, uint32 *size)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        size);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        DNX_SW_STATE_DIAG_READ);

    *size = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].size;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].size,
        "dnx_field_action_sw_db[%d]->info[%d].size",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__SIZE,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_SIZE_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_prefix_set(int unit, uint32 info_idx_0, uint32 prefix)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].prefix,
        prefix,
        uint32,
        0,
        "dnx_field_action_sw_db_info_prefix_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        &prefix,
        "dnx_field_action_sw_db[%d]->info[%d].prefix",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_PREFIX_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_prefix_get(int unit, uint32 info_idx_0, uint32 *prefix)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        prefix);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        DNX_SW_STATE_DIAG_READ);

    *prefix = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].prefix;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].prefix,
        "dnx_field_action_sw_db[%d]->info[%d].prefix",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_PREFIX_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_ref_count_set(int unit, uint32 info_idx_0, uint32 ref_count)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].ref_count,
        ref_count,
        uint32,
        0,
        "dnx_field_action_sw_db_info_ref_count_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        &ref_count,
        "dnx_field_action_sw_db[%d]->info[%d].ref_count",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_REF_COUNT_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_ref_count_get(int unit, uint32 info_idx_0, uint32 *ref_count)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        ref_count);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        DNX_SW_STATE_DIAG_READ);

    *ref_count = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].ref_count;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].ref_count,
        "dnx_field_action_sw_db[%d]->info[%d].ref_count",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__REF_COUNT,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_REF_COUNT_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_base_dnx_action_set(int unit, uint32 info_idx_0, dnx_field_action_t base_dnx_action)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].base_dnx_action,
        base_dnx_action,
        dnx_field_action_t,
        0,
        "dnx_field_action_sw_db_info_base_dnx_action_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        &base_dnx_action,
        "dnx_field_action_sw_db[%d]->info[%d].base_dnx_action",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_BASE_DNX_ACTION_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_base_dnx_action_get(int unit, uint32 info_idx_0, dnx_field_action_t *base_dnx_action)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        base_dnx_action);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        DNX_SW_STATE_DIAG_READ);

    *base_dnx_action = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].base_dnx_action;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].base_dnx_action,
        "dnx_field_action_sw_db[%d]->info[%d].base_dnx_action",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__BASE_DNX_ACTION,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_BASE_DNX_ACTION_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_prefix_size_set(int unit, uint32 info_idx_0, uint8 prefix_size)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].prefix_size,
        prefix_size,
        uint8,
        0,
        "dnx_field_action_sw_db_info_prefix_size_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        &prefix_size,
        "dnx_field_action_sw_db[%d]->info[%d].prefix_size",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_PREFIX_SIZE_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_info_prefix_size_get(int unit, uint32 info_idx_0, uint8 *prefix_size)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        info_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_USER_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        prefix_size);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        DNX_SW_STATE_DIAG_READ);

    *prefix_size = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].prefix_size;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->info[info_idx_0].prefix_size,
        "dnx_field_action_sw_db[%d]->info[%d].prefix_size",
        unit, info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__INFO__PREFIX_SIZE,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_INFO_PREFIX_SIZE_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_alloc(int unit)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO,
        SW_STATE_FUNC_ALLOC,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO,
        DNX_SW_STATE_DIAG_ALLOC);

    DNX_SW_STATE_ALLOC(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        dnx_field_fem_state_t,
        dnx_data_field.stage.stage_info_get(unit,DNX_FIELD_STAGE_IPMF1)->nof_fem_id,
        DNXC_SW_STATE_DNX_DATA_ALLOC | DNXC_SW_STATE_AUTO_GENERATED_ALLOCATION,
        "dnx_field_action_sw_db_fem_info_alloc");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_ALLOC_LOGGING,
        BSL_LS_SWSTATEDNX_ALLOC,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        "dnx_field_action_sw_db[%d]->fem_info",
        unit,
        dnx_data_field.stage.stage_info_get(unit,DNX_FIELD_STAGE_IPMF1)->nof_fem_id * sizeof(dnx_field_fem_state_t) / sizeof(*((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info));

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_INFO,
        DNX_SW_STATE_DIAG_ALLOC,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_is_allocated(int unit, uint8 *is_allocated)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO,
        SW_STATE_FUNC_IS_ALLOCATED,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO,
        is_allocated);

    DNX_SW_STATE_IS_ALLOC(
        unit,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        is_allocated,
        DNXC_SW_STATE_NONE,
        "dnx_field_action_sw_db_fem_info_alloc");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_IS_ALLOC_LOGGING,
        BSL_LS_SWSTATEDNX_ISALLOC,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        "dnx_field_action_sw_db[%d]->fem_info",
        unit);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_alloc(int unit, uint32 fem_info_idx_0)
{
    DNX_SW_STATE_DEFAULT_VALUE_DEFS;
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        SW_STATE_FUNC_ALLOC,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        DNX_SW_STATE_DIAG_ALLOC);

    DNX_SW_STATE_ALLOC(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        dnx_field_fg_id_info_t,
        dnx_data_field.stage.stage_info_get(unit,DNX_FIELD_STAGE_IPMF1)->nof_fem_programs,
        DNXC_SW_STATE_DNX_DATA_ALLOC | DNXC_SW_STATE_AUTO_GENERATED_ALLOCATION,
        "dnx_field_action_sw_db_fem_info_fg_id_info_alloc");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_ALLOC_LOGGING,
        BSL_LS_SWSTATEDNX_ALLOC,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info",
        unit, fem_info_idx_0,
        dnx_data_field.stage.stage_info_get(unit,DNX_FIELD_STAGE_IPMF1)->nof_fem_programs * sizeof(dnx_field_fg_id_info_t) / sizeof(*((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info));

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_INFO,
        DNX_SW_STATE_DIAG_ALLOC,
        NULL);

    DNX_SW_STATE_DEFAULT_VALUE_LOOP(def_val_idx[0], dnx_data_field.stage.stage_info_get(unit,DNX_FIELD_STAGE_IPMF1)->nof_fem_programs)

    DNX_SW_STATE_DEFAULT_VALUE_ASSIGN(
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[def_val_idx[0]].second_fg_id,
        DNX_FIELD_GROUP_INVALID);

    DNX_SW_STATE_DEFAULT_VALUE_LOOP(def_val_idx[0], dnx_data_field.stage.stage_info_get(unit,DNX_FIELD_STAGE_IPMF1)->nof_fem_programs)

    DNX_SW_STATE_DEFAULT_VALUE_ASSIGN(
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[def_val_idx[0]].fg_id,
        DNX_FIELD_GROUP_INVALID);

    DNX_SW_STATE_DEFAULT_VALUE_LOOP(def_val_idx[0], dnx_data_field.stage.stage_info_get(unit,DNX_FIELD_STAGE_IPMF1)->nof_fem_programs)

    DNX_SW_STATE_DEFAULT_VALUE_ASSIGN(
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[def_val_idx[0]].ignore_actions,
        DNX_FIELD_IGNORE_ALL_ACTIONS);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_is_allocated(int unit, uint32 fem_info_idx_0, uint8 *is_allocated)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        SW_STATE_FUNC_IS_ALLOCATED,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        is_allocated);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_IS_ALLOC(
        unit,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        is_allocated,
        DNXC_SW_STATE_NONE,
        "dnx_field_action_sw_db_fem_info_fg_id_info_alloc");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_IS_ALLOC_LOGGING,
        BSL_LS_SWSTATEDNX_ISALLOC,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info",
        unit, fem_info_idx_0);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_set(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, uint32 fem_encoded_actions_idx_0, dnx_field_action_t fem_encoded_actions)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions,
        fem_encoded_actions_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions[fem_encoded_actions_idx_0],
        fem_encoded_actions,
        dnx_field_action_t,
        0,
        "dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        &fem_encoded_actions,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].fem_encoded_actions[%d]",
        unit, fem_info_idx_0, fg_id_info_idx_0, fem_encoded_actions_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_FEM_ENCODED_ACTIONS_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_get(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, uint32 fem_encoded_actions_idx_0, dnx_field_action_t *fem_encoded_actions)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        fem_encoded_actions);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions,
        fem_encoded_actions_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        DNX_SW_STATE_DIAG_READ);

    *fem_encoded_actions = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions[fem_encoded_actions_idx_0];
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions[fem_encoded_actions_idx_0],
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].fem_encoded_actions[%d]",
        unit, fem_info_idx_0, fg_id_info_idx_0, fem_encoded_actions_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_FEM_ENCODED_ACTIONS_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_alloc(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0)
{
    DNX_SW_STATE_DEFAULT_VALUE_DEFS;
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        SW_STATE_FUNC_ALLOC,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        DNX_SW_STATE_DIAG_ALLOC);

    DNX_SW_STATE_ALLOC(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions,
        dnx_field_action_t,
        dnx_data_field.stage.stage_info_get(unit,DNX_FIELD_STAGE_IPMF1)->nof_fem_map_index,
        DNXC_SW_STATE_DNX_DATA_ALLOC | DNXC_SW_STATE_AUTO_GENERATED_ALLOCATION,
        "dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_alloc");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_ALLOC_LOGGING,
        BSL_LS_SWSTATEDNX_ALLOC,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].fem_encoded_actions",
        unit, fem_info_idx_0, fg_id_info_idx_0,
        dnx_data_field.stage.stage_info_get(unit,DNX_FIELD_STAGE_IPMF1)->nof_fem_map_index * sizeof(dnx_field_action_t) / sizeof(*((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions));

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_FEM_ENCODED_ACTIONS_INFO,
        DNX_SW_STATE_DIAG_ALLOC,
        NULL);

    DNX_SW_STATE_DEFAULT_VALUE_LOOP(def_val_idx[0], dnx_data_field.stage.stage_info_get(unit,DNX_FIELD_STAGE_IPMF1)->nof_fem_map_index)

    DNX_SW_STATE_DEFAULT_VALUE_ASSIGN(
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions[def_val_idx[0]],
        DNX_FIELD_ACTION_INVALID);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_is_allocated(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, uint8 *is_allocated)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        SW_STATE_FUNC_IS_ALLOCATED,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        is_allocated);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_IS_ALLOC(
        unit,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions,
        is_allocated,
        DNXC_SW_STATE_NONE,
        "dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_alloc");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_IS_ALLOC_LOGGING,
        BSL_LS_SWSTATEDNX_ISALLOC,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FEM_ENCODED_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fem_encoded_actions,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].fem_encoded_actions",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_second_fg_id_set(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, dnx_field_group_t second_fg_id)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].second_fg_id,
        second_fg_id,
        dnx_field_group_t,
        0,
        "dnx_field_action_sw_db_fem_info_fg_id_info_second_fg_id_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        &second_fg_id,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].second_fg_id",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_SECOND_FG_ID_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_second_fg_id_get(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, dnx_field_group_t *second_fg_id)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        second_fg_id);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        DNX_SW_STATE_DIAG_READ);

    *second_fg_id = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].second_fg_id;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].second_fg_id,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].second_fg_id",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__SECOND_FG_ID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_SECOND_FG_ID_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_fg_id_set(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, dnx_field_group_t fg_id)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fg_id,
        fg_id,
        dnx_field_group_t,
        0,
        "dnx_field_action_sw_db_fem_info_fg_id_info_fg_id_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        &fg_id,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].fg_id",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_FG_ID_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_fg_id_get(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, dnx_field_group_t *fg_id)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        fg_id);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        DNX_SW_STATE_DIAG_READ);

    *fg_id = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fg_id;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].fg_id,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].fg_id",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__FG_ID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_FG_ID_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_input_offset_set(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, uint8 input_offset)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].input_offset,
        input_offset,
        uint8,
        0,
        "dnx_field_action_sw_db_fem_info_fg_id_info_input_offset_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        &input_offset,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].input_offset",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_INPUT_OFFSET_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_input_offset_get(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, uint8 *input_offset)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        input_offset);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        DNX_SW_STATE_DIAG_READ);

    *input_offset = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].input_offset;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].input_offset,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].input_offset",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_OFFSET,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_INPUT_OFFSET_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_input_size_set(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, uint8 input_size)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].input_size,
        input_size,
        uint8,
        0,
        "dnx_field_action_sw_db_fem_info_fg_id_info_input_size_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        &input_size,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].input_size",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_INPUT_SIZE_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_input_size_get(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, uint8 *input_size)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        input_size);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        DNX_SW_STATE_DIAG_READ);

    *input_size = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].input_size;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].input_size,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].input_size",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__INPUT_SIZE,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_INPUT_SIZE_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_ignore_actions_set(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, uint8 ignore_actions)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].ignore_actions,
        ignore_actions,
        uint8,
        0,
        "dnx_field_action_sw_db_fem_info_fg_id_info_ignore_actions_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        &ignore_actions,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].ignore_actions",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_IGNORE_ACTIONS_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_fem_info_fg_id_info_ignore_actions_get(int unit, uint32 fem_info_idx_0, uint32 fg_id_info_idx_0, uint8 *ignore_actions)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info,
        fem_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        ignore_actions);

    DNX_SW_STATE_OOB_DYNAMIC_ARRAY_CHECK(
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info,
        fg_id_info_idx_0);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        DNX_SW_STATE_DIAG_READ);

    *ignore_actions = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].ignore_actions;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->fem_info[fem_info_idx_0].fg_id_info[fg_id_info_idx_0].ignore_actions,
        "dnx_field_action_sw_db[%d]->fem_info[%d].fg_id_info[%d].ignore_actions",
        unit, fem_info_idx_0, fg_id_info_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__FEM_INFO__FG_ID_INFO__IGNORE_ACTIONS,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_FEM_INFO_FG_ID_INFO_IGNORE_ACTIONS_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_predefined_set(int unit, uint32 predefined_idx_0, CONST dnx_field_predefined_action_info_t *predefined)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        predefined_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_PREDEFINED_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_MEMCPY(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->predefined[predefined_idx_0],
        predefined,
        dnx_field_predefined_action_info_t,
        0,
        "dnx_field_action_sw_db_predefined_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        predefined,
        "dnx_field_action_sw_db[%d]->predefined[%d]",
        unit, predefined_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_PREDEFINED_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_predefined_get(int unit, uint32 predefined_idx_0, dnx_field_predefined_action_info_t *predefined)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        predefined_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_PREDEFINED_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        predefined);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        DNX_SW_STATE_DIAG_READ);

    *predefined = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->predefined[predefined_idx_0];
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->predefined[predefined_idx_0],
        "dnx_field_action_sw_db[%d]->predefined[%d]",
        unit, predefined_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_PREDEFINED_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_predefined_field_id_set(int unit, uint32 predefined_idx_0, dbal_fields_e field_id)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        SW_STATE_FUNC_SET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        predefined_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_PREDEFINED_NOF);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        DNX_SW_STATE_DIAG_MODIFY);

    DNX_SW_STATE_SET(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->predefined[predefined_idx_0].field_id,
        field_id,
        dbal_fields_e,
        0,
        "dnx_field_action_sw_db_predefined_field_id_set");

    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_SET_LOGGING,
        BSL_LS_SWSTATEDNX_SET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        &field_id,
        "dnx_field_action_sw_db[%d]->predefined[%d].field_id",
        unit, predefined_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_PREDEFINED_FIELD_ID_INFO,
        DNX_SW_STATE_DIAG_MODIFY,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




int
dnx_field_action_sw_db_predefined_field_id_get(int unit, uint32 predefined_idx_0, dbal_fields_e *field_id)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    VERIFY_FUNCTION_CALL_ALLOWED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        SW_STATE_FUNC_GET,
        DNXC_SW_STATE_NO_FLAGS);

    VERIFY_MODULE_IS_INITIALIZED(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID]);

    DNX_SW_STATE_OOB_STATIC_ARRAY_CHECK(
        predefined_idx_0,
        DNX_DATA_MAX_FIELD_ACTION_PREDEFINED_NOF);

    DNX_SW_STATE_PTR_NULL_CHECK(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        field_id);

    DNX_SW_STATE_DIAG_INFO_PRE(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        DNX_SW_STATE_DIAG_READ);

    *field_id = ((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->predefined[predefined_idx_0].field_id;
    DNX_SW_STATE_LOG(
        unit,
        DNX_SW_STATE_GET_LOGGING,
        BSL_LS_SWSTATEDNX_GET,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        &((dnx_field_action_sw_db_t*)sw_state_roots_array[unit][DNX_FIELD_ACTIONS_MODULE_ID])->predefined[predefined_idx_0].field_id,
        "dnx_field_action_sw_db[%d]->predefined[%d].field_id",
        unit, predefined_idx_0);

    DNX_SW_STATE_DIAG_INFO_POST(
        unit,
        DNX_SW_STATE_DNX_FIELD_ACTION_SW_DB__PREDEFINED__FIELD_ID,
        dnx_field_action_sw_db_info,
        DNX_FIELD_ACTION_SW_DB_PREDEFINED_FIELD_ID_INFO,
        DNX_SW_STATE_DIAG_READ,
        NULL);

    DNXC_SW_STATE_FUNC_RETURN;
}




const char *
dnx_field_action_flags_e_get_name(dnx_field_action_flags_e value)
{
    DNX_SW_STATE_ENUM_COMPARE_AND_GET_NAME("DNX_FIELD_ACTION_FLAG_WITH_ID", value, DNX_FIELD_ACTION_FLAG_WITH_ID);

    DNX_SW_STATE_ENUM_COMPARE_AND_GET_NAME("DNX_FIELD_ACTION_FLAG_NOF", value, DNX_FIELD_ACTION_FLAG_NOF);

    return NULL;
}




const char *
dnx_field_fem_bit_format_e_get_name(dnx_field_fem_bit_format_e value)
{
    DNX_SW_STATE_ENUM_COMPARE_AND_GET_NAME("DNX_FIELD_FEM_BIT_FORMAT_INVALID", value, DNX_FIELD_FEM_BIT_FORMAT_INVALID);

    DNX_SW_STATE_ENUM_COMPARE_AND_GET_NAME("DNX_FIELD_FEM_BIT_FORMAT_FIRST", value, DNX_FIELD_FEM_BIT_FORMAT_FIRST);

    DNX_SW_STATE_ENUM_COMPARE_AND_GET_NAME("DNX_FIELD_FEM_BIT_FORMAT_FROM_KEY_SELECT", value, DNX_FIELD_FEM_BIT_FORMAT_FROM_KEY_SELECT);

    DNX_SW_STATE_ENUM_COMPARE_AND_GET_NAME("DNX_FIELD_FEM_BIT_FORMAT_FROM_MAP_DATA", value, DNX_FIELD_FEM_BIT_FORMAT_FROM_MAP_DATA);

    DNX_SW_STATE_ENUM_COMPARE_AND_GET_NAME("DNX_FIELD_FEM_BIT_FORMAT_FROM_THIS_FIELD", value, DNX_FIELD_FEM_BIT_FORMAT_FROM_THIS_FIELD);

    DNX_SW_STATE_ENUM_COMPARE_AND_GET_NAME("DNX_FIELD_FEM_BIT_FORMAT_NUM", value, DNX_FIELD_FEM_BIT_FORMAT_NUM);

    return NULL;
}





dnx_field_action_sw_db_cbs dnx_field_action_sw_db = 	{
	
	dnx_field_action_sw_db_is_init,
	dnx_field_action_sw_db_init,
		{
		
		dnx_field_action_sw_db_info_set,
		dnx_field_action_sw_db_info_get,
			{
			
			dnx_field_action_sw_db_info_field_id_set,
			dnx_field_action_sw_db_info_field_id_get}
		,
			{
			
			dnx_field_action_sw_db_info_flags_set,
			dnx_field_action_sw_db_info_flags_get}
		,
			{
			
			dnx_field_action_sw_db_info_bcm_id_set,
			dnx_field_action_sw_db_info_bcm_id_get}
		,
			{
			
			dnx_field_action_sw_db_info_valid_set,
			dnx_field_action_sw_db_info_valid_get}
		,
			{
			
			dnx_field_action_sw_db_info_size_set,
			dnx_field_action_sw_db_info_size_get}
		,
			{
			
			dnx_field_action_sw_db_info_prefix_set,
			dnx_field_action_sw_db_info_prefix_get}
		,
			{
			
			dnx_field_action_sw_db_info_ref_count_set,
			dnx_field_action_sw_db_info_ref_count_get}
		,
			{
			
			dnx_field_action_sw_db_info_base_dnx_action_set,
			dnx_field_action_sw_db_info_base_dnx_action_get}
		,
			{
			
			dnx_field_action_sw_db_info_prefix_size_set,
			dnx_field_action_sw_db_info_prefix_size_get}
		}
	,
		{
		
		dnx_field_action_sw_db_fem_info_alloc,
		dnx_field_action_sw_db_fem_info_is_allocated,
			{
			
			dnx_field_action_sw_db_fem_info_fg_id_info_alloc,
			dnx_field_action_sw_db_fem_info_fg_id_info_is_allocated,
				{
				
				dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_set,
				dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_get,
				dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_alloc,
				dnx_field_action_sw_db_fem_info_fg_id_info_fem_encoded_actions_is_allocated}
			,
				{
				
				dnx_field_action_sw_db_fem_info_fg_id_info_second_fg_id_set,
				dnx_field_action_sw_db_fem_info_fg_id_info_second_fg_id_get}
			,
				{
				
				dnx_field_action_sw_db_fem_info_fg_id_info_fg_id_set,
				dnx_field_action_sw_db_fem_info_fg_id_info_fg_id_get}
			,
				{
				
				dnx_field_action_sw_db_fem_info_fg_id_info_input_offset_set,
				dnx_field_action_sw_db_fem_info_fg_id_info_input_offset_get}
			,
				{
				
				dnx_field_action_sw_db_fem_info_fg_id_info_input_size_set,
				dnx_field_action_sw_db_fem_info_fg_id_info_input_size_get}
			,
				{
				
				dnx_field_action_sw_db_fem_info_fg_id_info_ignore_actions_set,
				dnx_field_action_sw_db_fem_info_fg_id_info_ignore_actions_get}
			}
		}
	,
		{
		
		dnx_field_action_sw_db_predefined_set,
		dnx_field_action_sw_db_predefined_get,
			{
			
			dnx_field_action_sw_db_predefined_field_id_set,
			dnx_field_action_sw_db_predefined_field_id_get}
		}
	}
;
#undef BSL_LOG_MODULE

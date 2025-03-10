/** \file algo/swstate/auto_generated/diagnostic/algo_trunk_diagnostic.c
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

#include <bcm_int/dnx/algo/swstate/auto_generated/diagnostic/algo_trunk_diagnostic.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/layout/algo_trunk_layout.h>
#if defined(DNX_SW_STATE_DIAGNOSTIC)
/*
 * Global Variables
 */

extern algo_trunk_sw_state_t * algo_trunk_db_data[SOC_MAX_NUM_DEVICES];
/*
 * FUNCTIONs
 */

/*
 *
 * dump function for the variable algo_trunk_db
 * AUTO-GENERATED - DO NOT MODIFY
 *
 */
int
algo_trunk_db_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;
    SHR_IF_ERR_EXIT(algo_trunk_db_egress_trunk_dump(unit, filters));
    SHR_IF_ERR_EXIT(algo_trunk_db_pools_dump(unit, -1, filters));
    SHR_IF_ERR_EXIT(algo_trunk_db_psc_profiles_dump(unit, filters));
    SHR_IF_ERR_EXIT(algo_trunk_db_user_profile_manager_dump(unit, filters));
    DNXC_SW_STATE_FUNC_RETURN;
}


/*
 *
 * dump function for the variable egress_trunk
 * AUTO-GENERATED - DO NOT MODIFY
 *
 */
int
algo_trunk_db_egress_trunk_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_trunk egress_trunk") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_trunk egress_trunk\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_trunk_db/egress_trunk.txt",
            "algo_trunk_db[%d]->","((algo_trunk_sw_state_t*)sw_state_roots_array[%d][ALGO_TRUNK_MODULE_ID])->","egress_trunk: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "algo_trunk_db[%d]->","((algo_trunk_sw_state_t*)sw_state_roots_array[%d][ALGO_TRUNK_MODULE_ID])->","egress_trunk: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_TEMP_MNGR_PRINT(
            unit,
            ALGO_TRUNK_MODULE_ID,
            &((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->egress_trunk,
            dnx_algo_trunk_egresstrunk_profile_print_cb);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}


/*
 *
 * dump function for the variable pools
 * AUTO-GENERATED - DO NOT MODIFY
 *
 */
int
algo_trunk_db_pools_dump(int  unit,  int  pools_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;
    SHR_IF_ERR_EXIT(algo_trunk_db_pools_groups_dump(unit, pools_idx_0, -1, filters));
    DNXC_SW_STATE_FUNC_RETURN;
}


/*
 *
 * dump function for the variable groups
 * AUTO-GENERATED - DO NOT MODIFY
 *
 */
int
algo_trunk_db_pools_groups_dump(int  unit,  int  pools_idx_0,  int  groups_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;
    SHR_IF_ERR_EXIT(algo_trunk_db_pools_groups_spa_id_manager_dump(unit, pools_idx_0, groups_idx_0, filters));
    SHR_IF_ERR_EXIT(algo_trunk_db_pools_groups_tm_index_manager_dump(unit, pools_idx_0, groups_idx_0, filters));
    DNXC_SW_STATE_FUNC_RETURN;
}


/*
 *
 * dump function for the variable spa_id_manager
 * AUTO-GENERATED - DO NOT MODIFY
 *
 */
int
algo_trunk_db_pools_groups_spa_id_manager_dump(int  unit,  int  pools_idx_0,  int  groups_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = pools_idx_0, I0 = pools_idx_0 + 1;
    int i1 = groups_idx_0, I1 = groups_idx_0 + 1, org_i1 = groups_idx_0;
    char *s0 = "", *s1 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_res_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_trunk pools groups spa_id_manager") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_trunk pools groups spa_id_manager\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_trunk_db/pools/groups/spa_id_manager.txt",
            "algo_trunk_db[%d]->","((algo_trunk_sw_state_t*)sw_state_roots_array[%d][ALGO_TRUNK_MODULE_ID])->","pools[].groups[].spa_id_manager: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID]));

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools);

        if (i0 == -1) {
            I0 = dnx_sw_state_get_nof_elements(unit,
                DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__SPA_ID_MANAGER,
                ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools);
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools
                , sizeof(*((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= dnx_sw_state_get_nof_elements(unit, DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__SPA_ID_MANAGER, ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools))
        {
            LOG_CLI((BSL_META("algo_trunk_db[]->((algo_trunk_sw_state_t*)sw_state_roots_array[][ALGO_TRUNK_MODULE_ID])->pools[].groups[].spa_id_manager: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(dnx_sw_state_get_nof_elements(unit, DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__SPA_ID_MANAGER, ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools) == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            /*coverity explanation: coverity has detected an out of bound read, due to i0 being incremented;
            However, we have a check if i0 > the end condition of the loop. If the check catches that i0 has
            reached the value of the end condition, we exit the function.
            What coverity is catching is the last increment of i0 before the loop ends. */
            /* coverity[overrun-local:FALSE] */
                DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
                    unit,
                    ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups);

            if (i1 == -1) {
                I1 = dnx_sw_state_get_nof_elements(unit,
                    DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__SPA_ID_MANAGER,
                    ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups);
                i1 = dnx_sw_state_dump_check_all_the_same(unit,
                    ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups
                    , sizeof(*((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups), I1, &s1) ? I1 - 1 : 0;
            }

            if(i1 >= dnx_sw_state_get_nof_elements(unit, DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__SPA_ID_MANAGER, ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups))
            {
                LOG_CLI((BSL_META("algo_trunk_db[]->((algo_trunk_sw_state_t*)sw_state_roots_array[][ALGO_TRUNK_MODULE_ID])->pools[].groups[].spa_id_manager: ")));
                LOG_CLI((BSL_META("Invalid index: %d \n"),i1));
                SHR_EXIT();
            }

            if(dnx_sw_state_get_nof_elements(unit, DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__SPA_ID_MANAGER, ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups) == 0)
            {
                SHR_EXIT();
            }

            for(; i1 < I1; i1++) {
                dnx_sw_state_dump_update_current_idx(unit, i1);
                DNX_SW_STATE_PRINT_MONITOR(
                    unit,
                    "algo_trunk_db[%d]->","((algo_trunk_sw_state_t*)sw_state_roots_array[%d][ALGO_TRUNK_MODULE_ID])->","pools[%s%d].groups[%s%d].spa_id_manager: ", s0, i0, s1, i1);

                DNX_SW_STATE_PRINT_FILE(
                    unit,
                    "[%s%d][%s%d]: ", s0, i0, s1, i1);

                DNX_ALGO_RES_MNGR_PRINT(
                    ALGO_TRUNK_MODULE_ID,
                    ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups[i1].spa_id_manager);

            }
            i1 = org_i1;
            dnx_sw_state_dump_end_of_stride(unit);
        }
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}


/*
 *
 * dump function for the variable tm_index_manager
 * AUTO-GENERATED - DO NOT MODIFY
 *
 */
int
algo_trunk_db_pools_groups_tm_index_manager_dump(int  unit,  int  pools_idx_0,  int  groups_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = pools_idx_0, I0 = pools_idx_0 + 1;
    int i1 = groups_idx_0, I1 = groups_idx_0 + 1, org_i1 = groups_idx_0;
    char *s0 = "", *s1 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_res_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_trunk pools groups tm_index_manager") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_trunk pools groups tm_index_manager\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_trunk_db/pools/groups/tm_index_manager.txt",
            "algo_trunk_db[%d]->","((algo_trunk_sw_state_t*)sw_state_roots_array[%d][ALGO_TRUNK_MODULE_ID])->","pools[].groups[].tm_index_manager: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID]));

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools);

        if (i0 == -1) {
            I0 = dnx_sw_state_get_nof_elements(unit,
                DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__TM_INDEX_MANAGER,
                ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools);
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools
                , sizeof(*((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= dnx_sw_state_get_nof_elements(unit, DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__TM_INDEX_MANAGER, ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools))
        {
            LOG_CLI((BSL_META("algo_trunk_db[]->((algo_trunk_sw_state_t*)sw_state_roots_array[][ALGO_TRUNK_MODULE_ID])->pools[].groups[].tm_index_manager: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(dnx_sw_state_get_nof_elements(unit, DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__TM_INDEX_MANAGER, ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools) == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            /*coverity explanation: coverity has detected an out of bound read, due to i0 being incremented;
            However, we have a check if i0 > the end condition of the loop. If the check catches that i0 has
            reached the value of the end condition, we exit the function.
            What coverity is catching is the last increment of i0 before the loop ends. */
            /* coverity[overrun-local:FALSE] */
                DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
                    unit,
                    ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups);

            if (i1 == -1) {
                I1 = dnx_sw_state_get_nof_elements(unit,
                    DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__TM_INDEX_MANAGER,
                    ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups);
                i1 = dnx_sw_state_dump_check_all_the_same(unit,
                    ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups
                    , sizeof(*((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups), I1, &s1) ? I1 - 1 : 0;
            }

            if(i1 >= dnx_sw_state_get_nof_elements(unit, DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__TM_INDEX_MANAGER, ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups))
            {
                LOG_CLI((BSL_META("algo_trunk_db[]->((algo_trunk_sw_state_t*)sw_state_roots_array[][ALGO_TRUNK_MODULE_ID])->pools[].groups[].tm_index_manager: ")));
                LOG_CLI((BSL_META("Invalid index: %d \n"),i1));
                SHR_EXIT();
            }

            if(dnx_sw_state_get_nof_elements(unit, DNX_SW_STATE_ALGO_TRUNK_DB__POOLS__GROUPS__TM_INDEX_MANAGER, ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups) == 0)
            {
                SHR_EXIT();
            }

            for(; i1 < I1; i1++) {
                dnx_sw_state_dump_update_current_idx(unit, i1);
                DNX_SW_STATE_PRINT_MONITOR(
                    unit,
                    "algo_trunk_db[%d]->","((algo_trunk_sw_state_t*)sw_state_roots_array[%d][ALGO_TRUNK_MODULE_ID])->","pools[%s%d].groups[%s%d].tm_index_manager: ", s0, i0, s1, i1);

                DNX_SW_STATE_PRINT_FILE(
                    unit,
                    "[%s%d][%s%d]: ", s0, i0, s1, i1);

                DNX_ALGO_RES_MNGR_PRINT(
                    ALGO_TRUNK_MODULE_ID,
                    ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->pools[i0].groups[i1].tm_index_manager);

            }
            i1 = org_i1;
            dnx_sw_state_dump_end_of_stride(unit);
        }
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}


/*
 *
 * dump function for the variable psc_profiles
 * AUTO-GENERATED - DO NOT MODIFY
 *
 */
int
algo_trunk_db_psc_profiles_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_trunk psc_profiles") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_trunk psc_profiles\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_trunk_db/psc_profiles.txt",
            "algo_trunk_db[%d]->","((algo_trunk_sw_state_t*)sw_state_roots_array[%d][ALGO_TRUNK_MODULE_ID])->","psc_profiles: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "algo_trunk_db[%d]->","((algo_trunk_sw_state_t*)sw_state_roots_array[%d][ALGO_TRUNK_MODULE_ID])->","psc_profiles: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_TEMP_MNGR_PRINT(
            unit,
            ALGO_TRUNK_MODULE_ID,
            &((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->psc_profiles,
            dnx_algo_trunk_psc_profiles_print_cb);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}


/*
 *
 * dump function for the variable user_profile_manager
 * AUTO-GENERATED - DO NOT MODIFY
 *
 */
int
algo_trunk_db_user_profile_manager_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_res_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_trunk user_profile_manager") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_trunk user_profile_manager\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_trunk_db/user_profile_manager.txt",
            "algo_trunk_db[%d]->","((algo_trunk_sw_state_t*)sw_state_roots_array[%d][ALGO_TRUNK_MODULE_ID])->","user_profile_manager: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "algo_trunk_db[%d]->","((algo_trunk_sw_state_t*)sw_state_roots_array[%d][ALGO_TRUNK_MODULE_ID])->","user_profile_manager: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_RES_MNGR_PRINT(
            ALGO_TRUNK_MODULE_ID,
            ((algo_trunk_sw_state_t*)sw_state_roots_array[unit][ALGO_TRUNK_MODULE_ID])->user_profile_manager);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}


/*
 * Global Variables
 */

dnx_sw_state_diagnostic_info_t algo_trunk_db_info[SOC_MAX_NUM_DEVICES][ALGO_TRUNK_DB_INFO_NOF_ENTRIES];
const char* algo_trunk_db_layout_str[ALGO_TRUNK_DB_INFO_NOF_ENTRIES] = {
    "ALGO_TRUNK_DB~",
    "ALGO_TRUNK_DB~EGRESS_TRUNK~",
    "ALGO_TRUNK_DB~POOLS~",
    "ALGO_TRUNK_DB~POOLS~GROUPS~",
    "ALGO_TRUNK_DB~POOLS~GROUPS~SPA_ID_MANAGER~",
    "ALGO_TRUNK_DB~POOLS~GROUPS~TM_INDEX_MANAGER~",
    "ALGO_TRUNK_DB~PSC_PROFILES~",
    "ALGO_TRUNK_DB~USER_PROFILE_MANAGER~",
};
#endif /* DNX_SW_STATE_DIAGNOSTIC */
#undef BSL_LOG_MODULE

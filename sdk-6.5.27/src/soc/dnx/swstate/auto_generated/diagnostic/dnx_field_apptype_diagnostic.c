
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_SWSTATEDNX_GENERAL

#include <soc/dnx/swstate/auto_generated/diagnostic/dnx_field_apptype_diagnostic.h>
#include <soc/dnx/swstate/auto_generated/layout/dnx_field_apptype_layout.h>
#if defined(DNX_SW_STATE_DIAGNOSTIC)


extern dnx_field_apptype_sw_t * dnx_field_apptype_sw_data[SOC_MAX_NUM_DEVICES];



int
dnx_field_apptype_sw_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_opcode_predef_info_dump(unit, -1, filters));
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_user_def_info_dump(unit, -1, filters));
    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_opcode_predef_info_dump(int  unit,  int  opcode_predef_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_opcode_predef_info_is_valid_dump(unit, opcode_predef_info_idx_0, filters));
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_opcode_predef_info_apptype_dump(unit, opcode_predef_info_idx_0, filters));
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_opcode_predef_info_cs_profile_id_dump(unit, opcode_predef_info_idx_0, filters));
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_opcode_predef_info_nof_fwd2_context_ids_dump(unit, opcode_predef_info_idx_0, filters));
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_opcode_predef_info_fwd2_context_ids_dump(unit, opcode_predef_info_idx_0, -1, filters));
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_opcode_predef_info_valid_for_kbp_dump(unit, opcode_predef_info_idx_0, filters));
    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_opcode_predef_info_is_valid_dump(int  unit,  int  opcode_predef_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = opcode_predef_info_idx_0, I0 = opcode_predef_info_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "uint8") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype opcode_predef_info is_valid") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype opcode_predef_info is_valid\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/opcode_predef_info/is_valid.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[].is_valid: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[].is_valid: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[%s%d].is_valid: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            dnx_sw_state_print_uint8(
                unit,
                &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[i0].is_valid);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_opcode_predef_info_apptype_dump(int  unit,  int  opcode_predef_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = opcode_predef_info_idx_0, I0 = opcode_predef_info_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "uint8") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype opcode_predef_info apptype") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype opcode_predef_info apptype\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/opcode_predef_info/apptype.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[].apptype: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[].apptype: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[%s%d].apptype: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            dnx_sw_state_print_uint8(
                unit,
                &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[i0].apptype);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_opcode_predef_info_cs_profile_id_dump(int  unit,  int  opcode_predef_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = opcode_predef_info_idx_0, I0 = opcode_predef_info_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "uint8") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype opcode_predef_info cs_profile_id") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype opcode_predef_info cs_profile_id\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/opcode_predef_info/cs_profile_id.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[].cs_profile_id: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[].cs_profile_id: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[%s%d].cs_profile_id: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            dnx_sw_state_print_uint8(
                unit,
                &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[i0].cs_profile_id);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_opcode_predef_info_nof_fwd2_context_ids_dump(int  unit,  int  opcode_predef_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = opcode_predef_info_idx_0, I0 = opcode_predef_info_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "uint8") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype opcode_predef_info nof_fwd2_context_ids") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype opcode_predef_info nof_fwd2_context_ids\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/opcode_predef_info/nof_fwd2_context_ids.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[].nof_fwd2_context_ids: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[].nof_fwd2_context_ids: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[%s%d].nof_fwd2_context_ids: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            dnx_sw_state_print_uint8(
                unit,
                &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[i0].nof_fwd2_context_ids);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_opcode_predef_info_fwd2_context_ids_dump(int  unit,  int  opcode_predef_info_idx_0,  int  fwd2_context_ids_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = opcode_predef_info_idx_0, I0 = opcode_predef_info_idx_0 + 1;
    int i1 = fwd2_context_ids_idx_0, I1 = fwd2_context_ids_idx_0 + 1, org_i1 = fwd2_context_ids_idx_0;
    char *s0 = "", *s1 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "uint8") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype opcode_predef_info fwd2_context_ids") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype opcode_predef_info fwd2_context_ids\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/opcode_predef_info/fwd2_context_ids.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[].fwd2_context_ids[]: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[].fwd2_context_ids[]: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            if (i1 == -1) {
                I1 = DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_MAX_FWD_CONTEXT_NUM_FOR_ONE_APPTYPE;
                i1 = dnx_sw_state_dump_check_all_the_same(unit,
                    ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[i0].fwd2_context_ids
                    , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[i0].fwd2_context_ids), I1, &s1) ? I1 - 1 : 0;
            }

            if(i1 >= DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_MAX_FWD_CONTEXT_NUM_FOR_ONE_APPTYPE)
            {
                LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[].fwd2_context_ids[]: ")));
                LOG_CLI((BSL_META("Invalid index: %d \n"),i1));
                SHR_EXIT();
            }

            if(DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_MAX_FWD_CONTEXT_NUM_FOR_ONE_APPTYPE == 0)
            {
                SHR_EXIT();
            }

            for(; i1 < I1; i1++) {
                dnx_sw_state_dump_update_current_idx(unit, i1);
                DNX_SW_STATE_PRINT_MONITOR(
                    unit,
                    "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[%s%d].fwd2_context_ids[%s%d]: ", s0, i0, s1, i1);

                DNX_SW_STATE_PRINT_FILE(
                    unit,
                    "[%s%d][%s%d]: ", s0, i0, s1, i1);

                dnx_sw_state_print_uint8(
                    unit,
                    &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[i0].fwd2_context_ids[i1]);

            }
            i1 = org_i1;
            dnx_sw_state_dump_end_of_stride(unit);
        }
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_opcode_predef_info_valid_for_kbp_dump(int  unit,  int  opcode_predef_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = opcode_predef_info_idx_0, I0 = opcode_predef_info_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "uint8") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype opcode_predef_info valid_for_kbp") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype opcode_predef_info valid_for_kbp\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/opcode_predef_info/valid_for_kbp.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[].valid_for_kbp: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[].valid_for_kbp: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","opcode_predef_info[%s%d].valid_for_kbp: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            dnx_sw_state_print_uint8(
                unit,
                &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->opcode_predef_info[i0].valid_for_kbp);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_user_def_info_dump(int  unit,  int  user_def_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_user_def_info_apptype_dump(unit, user_def_info_idx_0, filters));
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_user_def_info_acl_context_dump(unit, user_def_info_idx_0, filters));
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_user_def_info_base_opcode_dump(unit, user_def_info_idx_0, filters));
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_user_def_info_profile_id_dump(unit, user_def_info_idx_0, filters));
    SHR_IF_ERR_EXIT(dnx_field_apptype_sw_user_def_info_name_dump(unit, user_def_info_idx_0, filters));
    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_user_def_info_apptype_dump(int  unit,  int  user_def_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = user_def_info_idx_0, I0 = user_def_info_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "uint8") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype user_def_info apptype") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype user_def_info apptype\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/user_def_info/apptype.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","user_def_info[].apptype: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info[].apptype: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","user_def_info[%s%d].apptype: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            dnx_sw_state_print_uint8(
                unit,
                &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info[i0].apptype);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_user_def_info_acl_context_dump(int  unit,  int  user_def_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = user_def_info_idx_0, I0 = user_def_info_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "uint8") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype user_def_info acl_context") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype user_def_info acl_context\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/user_def_info/acl_context.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","user_def_info[].acl_context: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info[].acl_context: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","user_def_info[%s%d].acl_context: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            dnx_sw_state_print_uint8(
                unit,
                &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info[i0].acl_context);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_user_def_info_base_opcode_dump(int  unit,  int  user_def_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = user_def_info_idx_0, I0 = user_def_info_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "uint8") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype user_def_info base_opcode") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype user_def_info base_opcode\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/user_def_info/base_opcode.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","user_def_info[].base_opcode: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info[].base_opcode: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","user_def_info[%s%d].base_opcode: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            dnx_sw_state_print_uint8(
                unit,
                &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info[i0].base_opcode);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_user_def_info_profile_id_dump(int  unit,  int  user_def_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = user_def_info_idx_0, I0 = user_def_info_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "uint8") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype user_def_info profile_id") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype user_def_info profile_id\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/user_def_info/profile_id.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","user_def_info[].profile_id: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info[].profile_id: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","user_def_info[%s%d].profile_id: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            dnx_sw_state_print_uint8(
                unit,
                &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info[i0].profile_id);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



int
dnx_field_apptype_sw_user_def_info_name_dump(int  unit,  int  user_def_info_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = user_def_info_idx_0, I0 = user_def_info_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "sw_state_string_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_field_apptype user_def_info name") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_field_apptype user_def_info name\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_field_apptype_sw/user_def_info/name.txt",
            "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","user_def_info[].name: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info
                , sizeof(*((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF)
        {
            LOG_CLI((BSL_META("dnx_field_apptype_sw[]->((dnx_field_apptype_sw_t*)sw_state_roots_array[][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info[].name: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_DATA_MAX_FIELD_EXTERNAL_TCAM_APPTYPE_USER_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_field_apptype_sw[%d]->","((dnx_field_apptype_sw_t*)sw_state_roots_array[%d][DNX_FIELD_APPTYPE_MODULE_ID])->","user_def_info[%s%d].name: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            SW_STATE_STRING_STRING_PRINT(
                unit,
                DNX_FIELD_APPTYPE_MODULE_ID,
                &((dnx_field_apptype_sw_t*)sw_state_roots_array[unit][DNX_FIELD_APPTYPE_MODULE_ID])->user_def_info[i0].name);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}




dnx_sw_state_diagnostic_info_t dnx_field_apptype_sw_info[SOC_MAX_NUM_DEVICES][DNX_FIELD_APPTYPE_SW_INFO_NOF_ENTRIES];
const char* dnx_field_apptype_sw_layout_str[DNX_FIELD_APPTYPE_SW_INFO_NOF_ENTRIES] = {
    "DNX_FIELD_APPTYPE_SW~",
    "DNX_FIELD_APPTYPE_SW~OPCODE_PREDEF_INFO~",
    "DNX_FIELD_APPTYPE_SW~OPCODE_PREDEF_INFO~IS_VALID~",
    "DNX_FIELD_APPTYPE_SW~OPCODE_PREDEF_INFO~APPTYPE~",
    "DNX_FIELD_APPTYPE_SW~OPCODE_PREDEF_INFO~CS_PROFILE_ID~",
    "DNX_FIELD_APPTYPE_SW~OPCODE_PREDEF_INFO~NOF_FWD2_CONTEXT_IDS~",
    "DNX_FIELD_APPTYPE_SW~OPCODE_PREDEF_INFO~FWD2_CONTEXT_IDS~",
    "DNX_FIELD_APPTYPE_SW~OPCODE_PREDEF_INFO~VALID_FOR_KBP~",
    "DNX_FIELD_APPTYPE_SW~USER_DEF_INFO~",
    "DNX_FIELD_APPTYPE_SW~USER_DEF_INFO~APPTYPE~",
    "DNX_FIELD_APPTYPE_SW~USER_DEF_INFO~ACL_CONTEXT~",
    "DNX_FIELD_APPTYPE_SW~USER_DEF_INFO~BASE_OPCODE~",
    "DNX_FIELD_APPTYPE_SW~USER_DEF_INFO~PROFILE_ID~",
    "DNX_FIELD_APPTYPE_SW~USER_DEF_INFO~NAME~",
};
#endif 
#undef BSL_LOG_MODULE

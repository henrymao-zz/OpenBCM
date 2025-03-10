
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_FLDPROCDNX

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_field.h>
#include <bcm_int/dnx/field/field_context.h>








static shr_error_e
q2a_a0_dnx_data_field_base_ipmf1_cs_container_5_selected_bits_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_base_ipmf1;
    int define_index = dnx_data_field_base_ipmf1_define_cs_container_5_selected_bits_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
q2a_a0_dnx_data_field_base_ipmf3_cs_scratch_pad_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_base_ipmf3;
    int define_index = dnx_data_field_base_ipmf3_define_cs_scratch_pad_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 33;

    
    define->data = 33;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
q2a_a0_dnx_data_field_base_epmf_nof_keys_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_base_epmf;
    int define_index = dnx_data_field_base_epmf_define_nof_keys;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_base_epmf_nof_keys_alloc_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_base_epmf;
    int define_index = dnx_data_field_base_epmf_define_nof_keys_alloc;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_base_epmf_nof_keys_alloc_for_dir_ext_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_base_epmf;
    int define_index = dnx_data_field_base_epmf_define_nof_keys_alloc_for_dir_ext;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_base_epmf_dir_ext_single_key_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_base_epmf;
    int define_index = dnx_data_field_base_epmf_define_dir_ext_single_key_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 32;

    
    define->data = 32;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_base_epmf_dir_ext_first_key_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_base_epmf;
    int define_index = dnx_data_field_base_epmf_define_dir_ext_first_key;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_base_epmf_fes_key_select_for_zero_bit_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_base_epmf;
    int define_index = dnx_data_field_base_epmf_define_fes_key_select_for_zero_bit;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_LEXEM_59_0_4_B0;

    
    define->data = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_LEXEM_59_0_4_B0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_base_epmf_fes_shift_for_zero_bit_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_base_epmf;
    int define_index = dnx_data_field_base_epmf_define_fes_shift_for_zero_bit;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
q2a_a0_dnx_data_field_tcam_dt_max_key_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_tcam;
    int define_index = dnx_data_field_tcam_define_dt_max_key_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_tcam_hw_bank_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_tcam;
    int define_index = dnx_data_field_tcam_define_hw_bank_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2048;

    
    define->data = 2048;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_tcam_nof_big_bank_lines_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_tcam;
    int define_index = dnx_data_field_tcam_define_nof_big_bank_lines;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2048;

    
    define->data = 2048;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_tcam_nof_entries_160_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_tcam;
    int define_index = dnx_data_field_tcam_define_nof_entries_160_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 13312;

    
    define->data = 13312;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_tcam_nof_entries_80_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_tcam;
    int define_index = dnx_data_field_tcam_define_nof_entries_80_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 26624;

    
    define->data = 26624;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
q2a_a0_dnx_data_field_efes_max_nof_key_selects_per_field_io_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_efes;
    int define_index = dnx_data_field_efes_define_max_nof_key_selects_per_field_io;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
q2a_a0_dnx_data_field_efes_key_select_properties_set(
    int unit)
{
    int stage_index;
    int field_io_index;
    dnx_data_field_efes_key_select_properties_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_efes;
    int table_index = dnx_data_field_efes_table_key_select_properties;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DNX_FIELD_STAGE_NOF;
    table->info_get.key_size[0] = DNX_FIELD_STAGE_NOF;
    table->keys[1].size = DNX_DATA_MAX_FIELD_EFES_MAX_NOF_FIELD_IOS;
    table->info_get.key_size[1] = DNX_DATA_MAX_FIELD_EFES_MAX_NOF_FIELD_IOS;

    
    table->values[0].default_val = "{-1}";
    table->values[1].default_val = "{0}";
    table->values[2].default_val = "{0}";
    table->values[3].default_val = "{0}";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_field_efes_key_select_properties_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_field_efes_table_key_select_properties");

    
    default_data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    for (int i = 0; i < DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO; i++)  
        default_data->key_select[i] = -1;
    for (int i = 0; i < DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO; i++)  
        default_data->num_bits[i] = 0;
    for (int i = 0; i < DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO; i++)  
        default_data->lsb[i] = 0;
    for (int i = 0; i < DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO; i++)  
        default_data->num_bits_not_on_key[i] = 0;
    
    for (stage_index = 0; stage_index < table->keys[0].size; stage_index++)
    {
        for (field_io_index = 0; field_io_index < table->keys[1].size; field_io_index++)
        {
            data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, stage_index, field_io_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }
    
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0);
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_0_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_1_31_0_TCAM_0_63_32;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_1_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_2_31_0_TCAM_1_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_1_31_0_TCAM_0_63_32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 0;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_2 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_2);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_2_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_3_31_0_TCAM_2_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_2_31_0_TCAM_1_63_32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 0;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_3 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_3);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_3_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_4_31_0_TCAM_3_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_3_31_0_TCAM_2_63_32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 0;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_4 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_4);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_4_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_5_31_0_TCAM_4_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_4_31_0_TCAM_3_63_32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 0;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_5 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_5);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_5_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_6_31_0_TCAM_5_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_5_31_0_TCAM_4_63_32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 0;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_6 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_6);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_6_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_7_31_0_TCAM_6_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_6_31_0_TCAM_5_63_32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 0;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_7 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_7);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_7_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_LEXEM_27_0_4_B0_TCAM_7_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_7_31_0_TCAM_6_63_32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 0;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0_1);
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_0_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_1_31_0_TCAM_0_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_1_63_0;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_2_31_0_TCAM_1_63_32;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 32;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 64;
        data->lsb[3] = 96;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1_2 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1_2);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_1_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_2_31_0_TCAM_1_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_2_63_0;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_3_31_0_TCAM_2_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_1_31_0_TCAM_0_63_32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 64;
        data->lsb[3] = 96;
        data->lsb[4] = 0;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_2_3 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_2_3);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_2_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_3_31_0_TCAM_2_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_3_63_0;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_4_31_0_TCAM_3_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_2_31_0_TCAM_1_63_32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 64;
        data->lsb[3] = 96;
        data->lsb[4] = 0;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_4_5 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_4_5);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_4_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_5_31_0_TCAM_4_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_5_63_0;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_6_31_0_TCAM_5_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_4_31_0_TCAM_3_63_32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 64;
        data->lsb[3] = 96;
        data->lsb[4] = 0;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_5_6 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_5_6);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_5_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_6_31_0_TCAM_5_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_6_63_0;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_7_31_0_TCAM_6_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_5_31_0_TCAM_4_63_32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 64;
        data->lsb[3] = 96;
        data->lsb[4] = 0;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_6_7 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_6_7);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_6_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_7_31_0_TCAM_6_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_7_63_0;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_LEXEM_27_0_4_B0_TCAM_7_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_TCAM_6_31_0_TCAM_5_63_32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 64;
        data->lsb[3] = 96;
        data->lsb[4] = 0;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_LEXEM < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_LEXEM);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_LEXEM_27_0_4_B0_TCAM_7_63_32;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_LEXEM_59_0_4_B0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_SEXEM_27_0_4_B0_LEXEM_59_28;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 28;
        data->num_bits[1] = 60;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 28;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 36;
        data->num_bits_not_on_key[1] = 4;
        data->num_bits_not_on_key[2] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_SEXEM < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_SEXEM);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_SEXEM_27_0_4_B0_LEXEM_59_28;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_SEXEM_59_0_4_B0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_31_0_SEXEM_59_28;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 28;
        data->num_bits[1] = 60;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 28;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 36;
        data->num_bits_not_on_key[1] = 4;
        data->num_bits_not_on_key[2] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_DIRECT_0 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_DIRECT_0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_0_23_0_8_B0_KEY_J_159_128;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_0_55_0_8_B0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_0_87_24;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_0_119_56;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_1_23_0_8_B0_DIRECT_0_119_88;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 24;
        data->num_bits[1] = 56;
        data->num_bits[2] = 64;
        data->num_bits[3] = 64;
        data->num_bits[4] = 32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 24;
        data->lsb[3] = 56;
        data->lsb[4] = 88;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 40;
        data->num_bits_not_on_key[1] = 8;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_DIRECT_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_DIRECT_1);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_1_23_0_8_B0_DIRECT_0_119_88;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_1_55_0_8_B0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_1_87_24;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_1_119_56;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_STATE_TABLE_DATA_7_0_STATE_TABLE_ADDRESS_9_0_14_B0_DIRECT_1_119_88;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 24;
        data->num_bits[1] = 56;
        data->num_bits[2] = 64;
        data->num_bits[3] = 64;
        data->num_bits[4] = 32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 24;
        data->lsb[3] = 56;
        data->lsb[4] = 88;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 40;
        data->num_bits_not_on_key[1] = 8;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0);
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_31_0_SEXEM_59_28;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_63_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_95_32;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_127_64;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_159_96;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_31_0_KEY_I_159_128;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 32;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 64;
        data->num_bits[4] = 64;
        data->num_bits[5] = 32;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 32;
        data->lsb[3] = 64;
        data->lsb[4] = 96;
        data->lsb[5] = 128;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 32;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_1);
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_31_0_KEY_I_159_128;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_63_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_95_32;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_127_64;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_159_96;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_0_23_0_8_B0_KEY_J_159_128;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 32;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 64;
        data->num_bits[4] = 64;
        data->num_bits[5] = 32;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 32;
        data->lsb[3] = 64;
        data->lsb[4] = 96;
        data->lsb[5] = 128;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 32;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0_1);
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_31_0_SEXEM_59_28;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_63_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_95_32;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_127_64;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_I_159_96;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_31_0_KEY_I_159_128;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_63_0;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_95_32;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_127_64;
        data->key_select[9] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_KEY_J_159_96;
        data->key_select[10] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_DIRECT_0_23_0_8_B0_KEY_J_159_128;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 32;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 64;
        data->num_bits[4] = 64;
        data->num_bits[5] = 64;
        data->num_bits[6] = 64;
        data->num_bits[7] = 64;
        data->num_bits[8] = 64;
        data->num_bits[9] = 64;
        data->num_bits[10] = 32;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 32;
        data->lsb[3] = 64;
        data->lsb[4] = 96;
        data->lsb[5] = 128;
        data->lsb[6] = 160;
        data->lsb[7] = 192;
        data->lsb[8] = 224;
        data->lsb[9] = 256;
        data->lsb[10] = 288;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 32;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
        data->num_bits_not_on_key[9] = 0;
        data->num_bits_not_on_key[10] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF2 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_STATE_TABLE < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF2, DBAL_ENUM_FVAL_FIELD_IO_STATE_TABLE);
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FES_KEY_SELECT_STATE_TABLE_DATA_7_0_STATE_TABLE_ADDRESS_9_0_14_B0_DIRECT_1_119_88;
        data->num_bits[0] = 18;
        data->lsb[0] = 0;
        data->num_bits_not_on_key[0] = 46;
    }
    if (DNX_FIELD_STAGE_IPMF3 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF3, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0);
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_TCAM_0_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_TCAM_1_31_0_TCAM_0_63_32;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF3 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF3, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_TCAM_1_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_SEXEM_27_0_4_B0_TCAM_1_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_TCAM_1_31_0_TCAM_0_63_32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 0;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 32;
    }
    if (DNX_FIELD_STAGE_IPMF3 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF3, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0_1);
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_TCAM_0_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_TCAM_1_31_0_TCAM_0_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_TCAM_1_63_0;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_SEXEM_27_0_4_B0_TCAM_1_63_32;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 32;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 64;
        data->lsb[3] = 96;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF3 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_SEXEM < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF3, DBAL_ENUM_FVAL_FIELD_IO_SEXEM);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_SEXEM_27_0_4_B0_TCAM_1_63_32;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_SEXEM_59_0_4_B0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_31_0_SEXEM_59_28;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 28;
        data->num_bits[1] = 60;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 28;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 36;
        data->num_bits_not_on_key[1] = 4;
        data->num_bits_not_on_key[2] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF3 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_DIRECT_0 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF3, DBAL_ENUM_FVAL_FIELD_IO_DIRECT_0);
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_DIRECT_31_0_KEY_B_159_128;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_DIRECT_55_0_8_B0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_DIRECT_87_24;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_DIRECT_119_56;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 24;
        data->num_bits[1] = 56;
        data->num_bits[2] = 64;
        data->num_bits[3] = 64;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 24;
        data->lsb[3] = 56;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 40;
        data->num_bits_not_on_key[1] = 8;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF3 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF3, DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0);
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_31_0_SEXEM_59_28;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_63_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_95_32;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_127_64;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_159_96;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_31_0_KEY_A_159_128;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 32;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 64;
        data->num_bits[4] = 64;
        data->num_bits[5] = 32;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 32;
        data->lsb[3] = 64;
        data->lsb[4] = 96;
        data->lsb[5] = 128;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 32;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF3 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF3, DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_1);
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_31_0_KEY_A_159_128;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_63_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_95_32;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_127_64;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_159_96;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_DIRECT_31_0_KEY_B_159_128;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 32;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 64;
        data->num_bits[4] = 64;
        data->num_bits[5] = 32;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 32;
        data->lsb[3] = 64;
        data->lsb[4] = 96;
        data->lsb[5] = 128;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 32;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
    }
    if (DNX_FIELD_STAGE_IPMF3 < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_IPMF3, DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0_1);
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_31_0_SEXEM_59_28;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_63_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_95_32;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_127_64;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_A_159_96;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_31_0_KEY_A_159_128;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_63_0;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_95_32;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_127_64;
        data->key_select[9] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_KEY_B_159_96;
        data->key_select[10] = DBAL_ENUM_FVAL_FIELD_PMF_B_FES_KEY_SELECT_DIRECT_31_0_KEY_B_159_128;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 32;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 64;
        data->num_bits[4] = 64;
        data->num_bits[5] = 64;
        data->num_bits[6] = 64;
        data->num_bits[7] = 64;
        data->num_bits[8] = 64;
        data->num_bits[9] = 64;
        data->num_bits[10] = 32;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 32;
        data->lsb[3] = 64;
        data->lsb[4] = 96;
        data->lsb[5] = 128;
        data->lsb[6] = 160;
        data->lsb[7] = 192;
        data->lsb[8] = 224;
        data->lsb[9] = 256;
        data->lsb[10] = 288;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 32;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
        data->num_bits_not_on_key[9] = 0;
        data->num_bits_not_on_key[10] = 0;
    }
    if (DNX_FIELD_STAGE_EPMF < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_LEXEM < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_EPMF, DBAL_ENUM_FVAL_FIELD_IO_LEXEM);
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_LEXEM_59_0_4_B0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_TCAM_0_PAYLOAD_31_0_LEXEM_59_28;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 60;
        data->num_bits[1] = 32;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 28;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 4;
        data->num_bits_not_on_key[1] = 0;
    }
    if (DNX_FIELD_STAGE_EPMF < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_EPMF, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_TCAM_0_PAYLOAD_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_TCAM_1_PAYLOAD_31_0_TCAM_0_PAYLOAD_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_TCAM_0_PAYLOAD_31_0_LEXEM_59_28;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 0;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 32;
    }
    if (DNX_FIELD_STAGE_EPMF < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_EPMF, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1);
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_TCAM_1_PAYLOAD_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_TCAM_1_PAYLOAD_31_0_TCAM_0_PAYLOAD_63_32;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 32;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 32;
    }
    if (DNX_FIELD_STAGE_EPMF < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0_1 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_EPMF, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0_1);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_TCAM_0_PAYLOAD_63_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_TCAM_1_PAYLOAD_31_0_TCAM_0_PAYLOAD_63_32;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_TCAM_1_PAYLOAD_63_0;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_KEY_D_31_0_TCAM_1_PAYLOAD_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_TCAM_0_PAYLOAD_31_0_LEXEM_59_28;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 64;
        data->num_bits[1] = 64;
        data->num_bits[2] = 64;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 32;
        data->lsb[2] = 64;
        data->lsb[3] = 96;
        data->lsb[4] = 0;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_EFES_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 32;
    }
    if (DNX_FIELD_STAGE_EPMF < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0 < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_EPMF, DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0);
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_E_PMF_FES_KEY_SELECT_KEY_D_31_0_TCAM_1_PAYLOAD_63_32;
        data->num_bits[0] = 32;
        data->lsb[0] = 0;
        data->num_bits_not_on_key[0] = 32;
    }
    if (DNX_FIELD_STAGE_ACE < table->keys[0].size && DBAL_ENUM_FVAL_FIELD_IO_ACE < table->keys[1].size)
    {
        data = (dnx_data_field_efes_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DNX_FIELD_STAGE_ACE, DBAL_ENUM_FVAL_FIELD_IO_ACE);
        data->key_select[0] = 0;
        data->num_bits[0] = 104;
        data->lsb[0] = 0;
        data->num_bits_not_on_key[0] = 0;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
q2a_a0_dnx_data_field_fem_max_nof_key_selects_per_field_io_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_fem;
    int define_index = dnx_data_field_fem_define_max_nof_key_selects_per_field_io;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 21;

    
    define->data = 21;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
q2a_a0_dnx_data_field_fem_key_select_properties_set(
    int unit)
{
    int field_io_index;
    dnx_data_field_fem_key_select_properties_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_fem;
    int table_index = dnx_data_field_fem_table_key_select_properties;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DNX_DATA_MAX_FIELD_EFES_MAX_NOF_FIELD_IOS;
    table->info_get.key_size[0] = DNX_DATA_MAX_FIELD_EFES_MAX_NOF_FIELD_IOS;

    
    table->values[0].default_val = "{-1}";
    table->values[1].default_val = "{0}";
    table->values[2].default_val = "{0}";
    table->values[3].default_val = "{0}";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_field_fem_key_select_properties_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_field_fem_table_key_select_properties");

    
    default_data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    for (int i = 0; i < DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO; i++)  
        default_data->key_select[i] = -1;
    for (int i = 0; i < DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO; i++)  
        default_data->num_bits[i] = 0;
    for (int i = 0; i < DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO; i++)  
        default_data->lsb[i] = 0;
    for (int i = 0; i < DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO; i++)  
        default_data->num_bits_not_on_key[i] = 0;
    
    for (field_io_index = 0; field_io_index < table->keys[0].size; field_io_index++)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, field_io_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0, 0);
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_0_31_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_0_47_16;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_0_63_32;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_15_0_TCAM_0_63_48;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 32;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 16;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 16;
        data->lsb[2] = 32;
        data->lsb[3] = 48;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1, 0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_15_0_TCAM_0_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_15_0_TCAM_1_63_48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 16;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_2 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_2, 0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_15_0_TCAM_1_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_3_15_0_TCAM_2_63_48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 16;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_3 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_3, 0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_3_15_0_TCAM_2_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_3_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_3_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_3_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_4_15_0_TCAM_3_63_48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 16;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_4 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_4, 0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_4_15_0_TCAM_3_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_4_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_4_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_4_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_15_0_TCAM_4_63_48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 16;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_5 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_5, 0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_15_0_TCAM_4_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_15_0_TCAM_5_63_48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 16;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_6 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_6, 0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_15_0_TCAM_5_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_7_15_0_TCAM_6_63_48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 16;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_7 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_7, 0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_7_15_0_TCAM_6_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_7_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_7_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_7_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_LEXEM_11_0_4_B0_TCAM_7_63_48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 16;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0_1 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_0_1, 0);
        SHR_RANGE_VERIFY(8, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_0_31_0;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_0_47_16;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_0_63_32;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_15_0_TCAM_0_63_48;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_31_0;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_47_16;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_63_32;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_15_0_TCAM_1_63_48;
        SHR_RANGE_VERIFY(8, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 32;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 16;
        SHR_RANGE_VERIFY(8, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 16;
        data->lsb[2] = 32;
        data->lsb[3] = 48;
        data->lsb[4] = 64;
        data->lsb[5] = 80;
        data->lsb[6] = 96;
        data->lsb[7] = 112;
        SHR_RANGE_VERIFY(8, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 0;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1_2 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_1_2, 0);
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_15_0_TCAM_0_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_1_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_15_0_TCAM_1_63_48;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_31_0;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_47_16;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_63_32;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_3_15_0_TCAM_2_63_48;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 32;
        data->num_bits[8] = 16;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        data->lsb[5] = 64;
        data->lsb[6] = 80;
        data->lsb[7] = 96;
        data->lsb[8] = 112;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_2_3 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_2_3, 0);
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_15_0_TCAM_1_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_2_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_3_15_0_TCAM_2_63_48;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_3_31_0;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_3_47_16;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_3_63_32;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_4_15_0_TCAM_3_63_48;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 32;
        data->num_bits[8] = 16;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        data->lsb[5] = 64;
        data->lsb[6] = 80;
        data->lsb[7] = 96;
        data->lsb[8] = 112;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_4_5 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_4_5, 0);
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_4_15_0_TCAM_3_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_4_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_4_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_4_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_15_0_TCAM_4_63_48;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_31_0;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_47_16;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_63_32;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_15_0_TCAM_5_63_48;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 32;
        data->num_bits[8] = 16;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        data->lsb[5] = 64;
        data->lsb[6] = 80;
        data->lsb[7] = 96;
        data->lsb[8] = 112;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_5_6 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_5_6, 0);
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_15_0_TCAM_4_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_5_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_15_0_TCAM_5_63_48;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_31_0;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_47_16;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_63_32;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_7_15_0_TCAM_6_63_48;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 32;
        data->num_bits[8] = 16;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        data->lsb[5] = 64;
        data->lsb[6] = 80;
        data->lsb[7] = 96;
        data->lsb[8] = 112;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_6_7 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_INTERNAL_TCAM_6_7, 0);
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_15_0_TCAM_5_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_6_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_7_15_0_TCAM_6_63_48;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_7_31_0;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_7_47_16;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_TCAM_7_63_32;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_LEXEM_11_0_4_B0_TCAM_7_63_48;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 32;
        data->num_bits[8] = 16;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        data->lsb[5] = 64;
        data->lsb[6] = 80;
        data->lsb[7] = 96;
        data->lsb[8] = 112;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_LEXEM, 0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_LEXEM_11_0_4_B0_TCAM_7_63_48;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_LEXEM_27_0_4_B0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_LEXEM_43_12;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_LEXEM_59_28;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_SEXEM_11_0_4_B0_LEXEM_59_44;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 12;
        data->num_bits[1] = 28;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 16;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 12;
        data->lsb[3] = 28;
        data->lsb[4] = 44;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 20;
        data->num_bits_not_on_key[1] = 4;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_SEXEM < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_SEXEM, 0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_SEXEM_11_0_4_B0_LEXEM_59_44;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_SEXEM_27_0_4_B0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_SEXEM_43_12;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_SEXEM_59_28;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_16_0_SEXEM_59_44;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 12;
        data->num_bits[1] = 28;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 16;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 12;
        data->lsb[3] = 28;
        data->lsb[4] = 44;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 20;
        data->num_bits_not_on_key[1] = 4;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_DIRECT_0 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_DIRECT_0, 0);
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_0_7_0_8_B0_KEY_J_159_144;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_0_23_0_8_B0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_0_39_8;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_0_55_24;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_0_71_40;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_0_87_56;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_0_103_72;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_0_119_88;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_1_7_0_8_B0_DIRECT_0_119_104;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 8;
        data->num_bits[1] = 24;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 32;
        data->num_bits[8] = 16;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 8;
        data->lsb[3] = 24;
        data->lsb[4] = 40;
        data->lsb[5] = 56;
        data->lsb[6] = 72;
        data->lsb[7] = 88;
        data->lsb[8] = 104;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 24;
        data->num_bits_not_on_key[1] = 8;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_DIRECT_1 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_DIRECT_1, 0);
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_1_7_0_8_B0_DIRECT_0_119_104;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_1_23_0_8_B0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_1_39_8;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_1_55_24;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_1_71_40;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_1_87_56;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_1_103_72;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_1_119_88;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_STATE_TABLE_ADDRESS_1_0_14_B0_DIRECT_1_119_104;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 8;
        data->num_bits[1] = 24;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 32;
        data->num_bits[8] = 16;
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 8;
        data->lsb[3] = 24;
        data->lsb[4] = 40;
        data->lsb[5] = 56;
        data->lsb[6] = 72;
        data->lsb[7] = 88;
        data->lsb[8] = 104;
        SHR_RANGE_VERIFY(8, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 24;
        data->num_bits_not_on_key[1] = 8;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0, 0);
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_16_0_SEXEM_59_44;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_79_48;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_95_64;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_111_80;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_127_96;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_143_112;
        data->key_select[9] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_159_128;
        data->key_select[10] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_15_0_KEY_I_159_144;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 32;
        data->num_bits[8] = 32;
        data->num_bits[9] = 32;
        data->num_bits[10] = 16;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        data->lsb[5] = 64;
        data->lsb[6] = 80;
        data->lsb[7] = 96;
        data->lsb[8] = 112;
        data->lsb[9] = 128;
        data->lsb[10] = 144;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
        data->num_bits_not_on_key[9] = 0;
        data->num_bits_not_on_key[10] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_1 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_1, 0);
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_15_0_KEY_I_159_144;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_79_48;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_95_64;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_111_80;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_127_96;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_143_112;
        data->key_select[9] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_159_128;
        data->key_select[10] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_0_7_0_8_B0_KEY_J_159_144;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 32;
        data->num_bits[8] = 32;
        data->num_bits[9] = 32;
        data->num_bits[10] = 16;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        data->lsb[5] = 64;
        data->lsb[6] = 80;
        data->lsb[7] = 96;
        data->lsb[8] = 112;
        data->lsb[9] = 128;
        data->lsb[10] = 144;
        SHR_RANGE_VERIFY(11, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
        data->num_bits_not_on_key[9] = 0;
        data->num_bits_not_on_key[10] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0_1 < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_DIR_EXT_KEY_0_1, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_16_0_SEXEM_59_44;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_31_0;
        data->key_select[2] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_47_16;
        data->key_select[3] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_63_32;
        data->key_select[4] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_79_48;
        data->key_select[5] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_95_64;
        data->key_select[6] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_111_80;
        data->key_select[7] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_127_96;
        data->key_select[8] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_143_112;
        data->key_select[9] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_I_159_128;
        data->key_select[10] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_15_0_KEY_I_159_144;
        data->key_select[11] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_31_0;
        data->key_select[12] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_47_16;
        data->key_select[13] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_63_32;
        data->key_select[14] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_79_48;
        data->key_select[15] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_95_64;
        data->key_select[16] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_111_80;
        data->key_select[17] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_127_96;
        data->key_select[18] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_143_112;
        data->key_select[19] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_KEY_J_159_128;
        data->key_select[20] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_DIRECT_0_7_0_8_B0_KEY_J_159_144;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 16;
        data->num_bits[1] = 32;
        data->num_bits[2] = 32;
        data->num_bits[3] = 32;
        data->num_bits[4] = 32;
        data->num_bits[5] = 32;
        data->num_bits[6] = 32;
        data->num_bits[7] = 32;
        data->num_bits[8] = 32;
        data->num_bits[9] = 32;
        data->num_bits[10] = 32;
        data->num_bits[11] = 32;
        data->num_bits[12] = 32;
        data->num_bits[13] = 32;
        data->num_bits[14] = 32;
        data->num_bits[15] = 32;
        data->num_bits[16] = 32;
        data->num_bits[17] = 32;
        data->num_bits[18] = 32;
        data->num_bits[19] = 32;
        data->num_bits[20] = 16;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        data->lsb[2] = 16;
        data->lsb[3] = 32;
        data->lsb[4] = 48;
        data->lsb[5] = 64;
        data->lsb[6] = 80;
        data->lsb[7] = 96;
        data->lsb[8] = 112;
        data->lsb[9] = 128;
        data->lsb[10] = 144;
        data->lsb[11] = 160;
        data->lsb[12] = 176;
        data->lsb[13] = 192;
        data->lsb[14] = 208;
        data->lsb[15] = 224;
        data->lsb[16] = 240;
        data->lsb[17] = 256;
        data->lsb[18] = 272;
        data->lsb[19] = 288;
        data->lsb[20] = 304;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 16;
        data->num_bits_not_on_key[1] = 0;
        data->num_bits_not_on_key[2] = 0;
        data->num_bits_not_on_key[3] = 0;
        data->num_bits_not_on_key[4] = 0;
        data->num_bits_not_on_key[5] = 0;
        data->num_bits_not_on_key[6] = 0;
        data->num_bits_not_on_key[7] = 0;
        data->num_bits_not_on_key[8] = 0;
        data->num_bits_not_on_key[9] = 0;
        data->num_bits_not_on_key[10] = 0;
        data->num_bits_not_on_key[11] = 0;
        data->num_bits_not_on_key[12] = 0;
        data->num_bits_not_on_key[13] = 0;
        data->num_bits_not_on_key[14] = 0;
        data->num_bits_not_on_key[15] = 0;
        data->num_bits_not_on_key[16] = 0;
        data->num_bits_not_on_key[17] = 0;
        data->num_bits_not_on_key[18] = 0;
        data->num_bits_not_on_key[19] = 0;
        data->num_bits_not_on_key[20] = 0;
    }
    if (DBAL_ENUM_FVAL_FIELD_IO_STATE_TABLE < table->keys[0].size)
    {
        data = (dnx_data_field_fem_key_select_properties_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_FIELD_IO_STATE_TABLE, 0);
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_select[0] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_STATE_TABLE_ADDRESS_1_0_14_B0_DIRECT_1_119_104;
        data->key_select[1] = DBAL_ENUM_FVAL_FIELD_PMF_A_FEM_KEY_SELECT_STATE_TABLE_DATA_7_0_STATE_TABLE_ADDRESS_9_0_14_B0;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits[0] = 2;
        data->num_bits[1] = 18;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->lsb[0] = 0;
        data->lsb[1] = 0;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_FIELD_FEM_MAX_NOF_KEY_SELECTS_PER_FIELD_IO, _SHR_E_INTERNAL, "out of bound access to array")
        data->num_bits_not_on_key[0] = 30;
        data->num_bits_not_on_key[1] = 14;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
q2a_a0_dnx_data_field_qual_ifwd2_pbus_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_qual;
    int define_index = dnx_data_field_qual_define_ifwd2_pbus_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3175;

    
    define->data = 3175;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_qual_ipmf1_pbus_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_qual;
    int define_index = dnx_data_field_qual_define_ipmf1_pbus_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3362;

    
    define->data = 3362;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_qual_ipmf2_pbus_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_qual;
    int define_index = dnx_data_field_qual_define_ipmf2_pbus_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1384;

    
    define->data = 1384;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_qual_ipmf3_pbus_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_qual;
    int define_index = dnx_data_field_qual_define_ipmf3_pbus_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1822;

    
    define->data = 1822;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_qual_epmf_pbus_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_qual;
    int define_index = dnx_data_field_qual_define_epmf_pbus_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2562;

    
    define->data = 2562;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
q2a_a0_dnx_data_field_virtual_wire_in_lif_ac_wide_is_vw_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_virtual_wire;
    int feature_index = dnx_data_field_virtual_wire_in_lif_ac_wide_is_vw;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}








static shr_error_e
q2a_a0_dnx_data_field_exem_small_ipmf2_key_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_exem;
    int define_index = dnx_data_field_exem_define_small_ipmf2_key;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_exem_small_ipmf2_key_part_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_exem;
    int define_index = dnx_data_field_exem_define_small_ipmf2_key_part;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_exem_small_ipmf2_key_hw_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_exem;
    int define_index = dnx_data_field_exem_define_small_ipmf2_key_hw_value;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = (((dnx_data_field.exem.small_ipmf2_key_get(unit)/4)*2)+(dnx_data_field.exem.small_ipmf2_key_part_get(unit)));

    
    define->data = (((dnx_data_field.exem.small_ipmf2_key_get(unit)/4)*2)+(dnx_data_field.exem.small_ipmf2_key_part_get(unit)));

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_exem_small_ipmf2_key_hw_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_exem;
    int define_index = dnx_data_field_exem_define_small_ipmf2_key_hw_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2;

    
    define->data = 2;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_exem_ipmf1_key_configurable_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_exem;
    int define_index = dnx_data_field_exem_define_ipmf1_key_configurable;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_exem_ipmf1_key_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_exem;
    int define_index = dnx_data_field_exem_define_ipmf1_key;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}








static shr_error_e
q2a_a0_dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_tcam_memories_set(
    int unit)
{
    dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_tcam_memories_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_exem_learn_flush_machine;
    int table_index = dnx_data_field_exem_learn_flush_machine_table_sexem_flush_tcam_tcam_memories;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "MDB_MEM_78000m";
    table->values[1].default_val = "ITEM_0_0f";
    table->values[2].default_val = "ITEM_155_291f";
    table->values[3].default_val = "ITEM_8_144f";
    table->values[4].default_val = "ITEM_292_294f";
    table->values[5].default_val = "ITEM_145_147f";
    table->values[6].default_val = "ITEM_149_154f";
    table->values[7].default_val = "ITEM_2_7f";
    table->values[8].default_val = "ITEM_148_148f";
    table->values[9].default_val = "ITEM_1_1f";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_tcam_memories_t, (1 + 1  ), "data of dnx_data_field_exem_learn_flush_machine_table_sexem_flush_tcam_tcam_memories");

    
    default_data = (dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_tcam_memories_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->table_name = MDB_MEM_78000m;
    default_data->valid = ITEM_0_0f;
    default_data->entry_data = ITEM_155_291f;
    default_data->entry_mask = ITEM_8_144f;
    default_data->src_data = ITEM_292_294f;
    default_data->src_mask = ITEM_145_147f;
    default_data->appdb_id_data = ITEM_149_154f;
    default_data->appdb_id_mask = ITEM_2_7f;
    default_data->accessed_data = ITEM_148_148f;
    default_data->accessed_mask = ITEM_1_1f;
    
    data = (dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_tcam_memories_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_tcam_memories_set(
    int unit)
{
    dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_tcam_memories_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_exem_learn_flush_machine;
    int table_index = dnx_data_field_exem_learn_flush_machine_table_lexem_flush_tcam_tcam_memories;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "MDB_MEM_87000m";
    table->values[1].default_val = "ITEM_0_0f";
    table->values[2].default_val = "ITEM_275_531f";
    table->values[3].default_val = "ITEM_8_264f";
    table->values[4].default_val = "ITEM_532_534f";
    table->values[5].default_val = "ITEM_265_267f";
    table->values[6].default_val = "ITEM_269_274f";
    table->values[7].default_val = "ITEM_2_7f";
    table->values[8].default_val = "ITEM_268_268f";
    table->values[9].default_val = "ITEM_1_1f";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_tcam_memories_t, (1 + 1  ), "data of dnx_data_field_exem_learn_flush_machine_table_lexem_flush_tcam_tcam_memories");

    
    default_data = (dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_tcam_memories_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->table_name = MDB_MEM_87000m;
    default_data->valid = ITEM_0_0f;
    default_data->entry_data = ITEM_275_531f;
    default_data->entry_mask = ITEM_8_264f;
    default_data->src_data = ITEM_532_534f;
    default_data->src_mask = ITEM_265_267f;
    default_data->appdb_id_data = ITEM_269_274f;
    default_data->appdb_id_mask = ITEM_2_7f;
    default_data->accessed_data = ITEM_268_268f;
    default_data->accessed_mask = ITEM_1_1f;
    
    data = (dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_tcam_memories_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_data_rules_set(
    int unit)
{
    dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_data_rules_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_exem_learn_flush_machine;
    int table_index = dnx_data_field_exem_learn_flush_machine_table_sexem_flush_tcam_data_rules;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "MDB_MEM_79000m";
    table->values[1].default_val = "ITEM_0_3f";
    table->values[2].default_val = "ITEM_64_123f";
    table->values[3].default_val = "ITEM_4_63f";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_data_rules_t, (1 + 1  ), "data of dnx_data_field_exem_learn_flush_machine_table_sexem_flush_tcam_data_rules");

    
    default_data = (dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_data_rules_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->table_name = MDB_MEM_79000m;
    default_data->command = ITEM_0_3f;
    default_data->payload = ITEM_64_123f;
    default_data->payload_mask = ITEM_4_63f;
    
    data = (dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_data_rules_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_data_rules_set(
    int unit)
{
    dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_data_rules_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_exem_learn_flush_machine;
    int table_index = dnx_data_field_exem_learn_flush_machine_table_lexem_flush_tcam_data_rules;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "MDB_MEM_88000m";
    table->values[1].default_val = "ITEM_0_3f";
    table->values[2].default_val = "ITEM_64_123f";
    table->values[3].default_val = "ITEM_4_63f";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_data_rules_t, (1 + 1  ), "data of dnx_data_field_exem_learn_flush_machine_table_lexem_flush_tcam_data_rules");

    
    default_data = (dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_data_rules_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->table_name = MDB_MEM_88000m;
    default_data->command = ITEM_0_3f;
    default_data->payload = ITEM_64_123f;
    default_data->payload_mask = ITEM_4_63f;
    
    data = (dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_data_rules_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
q2a_a0_dnx_data_field_init_fec_dest_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_init;
    int define_index = dnx_data_field_init_define_fec_dest;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_init_l4_trap_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_init;
    int define_index = dnx_data_field_init_define_l4_trap;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_init_oam_layer_index_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_init;
    int define_index = dnx_data_field_init_define_oam_layer_index;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_init_oam_stat_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_init;
    int define_index = dnx_data_field_init_define_oam_stat;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_init_roo_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_init;
    int define_index = dnx_data_field_init_define_roo;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_init_jr1_ipmc_inlif_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_init;
    int define_index = dnx_data_field_init_define_jr1_ipmc_inlif;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_init_j1_same_port_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_init;
    int define_index = dnx_data_field_init_define_j1_same_port;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_init_j1_learning_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_init;
    int define_index = dnx_data_field_init_define_j1_learning;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_init_flow_id_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_init;
    int define_index = dnx_data_field_init_define_flow_id;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
q2a_a0_dnx_data_field_features_switch_to_acl_context_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_switch_to_acl_context;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_tcam_result_half_payload_on_msb_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_tcam_result_half_payload_on_msb;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_kbp_opcode_in_ipmf1_cs_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_kbp_opcode_in_ipmf1_cs;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_kbp_hitbits_correct_in_ipmf1_cs_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_kbp_hitbits_correct_in_ipmf1_cs;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_exem_vmv_removable_from_payload_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_exem_vmv_removable_from_payload;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_multiple_dynamic_mem_enablers_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_multiple_dynamic_mem_enablers;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_state_table_ipmf1_key_select_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_state_table_ipmf1_key_select;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_state_table_acr_bus_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_state_table_acr_bus;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_hitbit_volatile_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_hitbit_volatile;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_fem_replace_msb_instead_lsb_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_fem_replace_msb_instead_lsb;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_dir_ext_epmf_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_dir_ext_epmf;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_hashing_process_lsb_to_msb_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_hashing_process_lsb_to_msb;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_exem_age_flush_scan_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_exem_age_flush_scan;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_features_epmf_outlif_profile_map_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_features;
    int define_index = dnx_data_field_features_define_epmf_outlif_profile_map;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
q2a_a0_dnx_data_field_signal_sizes_dual_queue_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_signal_sizes;
    int define_index = dnx_data_field_signal_sizes_define_dual_queue_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_signal_sizes_ecn_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_signal_sizes;
    int define_index = dnx_data_field_signal_sizes_define_ecn;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
q2a_a0_dnx_data_field_tests_ingress_time_stamp_increased_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_tests;
    int define_index = dnx_data_field_tests_define_ingress_time_stamp_increased;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_tests_ace_debug_signals_exist_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_tests;
    int define_index = dnx_data_field_tests_define_ace_debug_signals_exist;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_tests_epmf_debug_rely_on_tcam0_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_tests;
    int define_index = dnx_data_field_tests_define_epmf_debug_rely_on_tcam0;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_field_tests_small_exem_addr_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_field;
    int submodule_index = dnx_data_field_submodule_tests;
    int define_index = dnx_data_field_tests_define_small_exem_addr_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 13;

    
    define->data = 13;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}




shr_error_e
q2a_a0_data_field_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_field;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_field_submodule_base_ipmf1;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_base_ipmf1_define_cs_container_5_selected_bits_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_base_ipmf1_cs_container_5_selected_bits_size_set;

    

    
    
    submodule_index = dnx_data_field_submodule_base_ipmf3;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_base_ipmf3_define_cs_scratch_pad_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_base_ipmf3_cs_scratch_pad_size_set;

    

    
    
    submodule_index = dnx_data_field_submodule_base_epmf;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_base_epmf_define_nof_keys;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_base_epmf_nof_keys_set;
    data_index = dnx_data_field_base_epmf_define_nof_keys_alloc;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_base_epmf_nof_keys_alloc_set;
    data_index = dnx_data_field_base_epmf_define_nof_keys_alloc_for_dir_ext;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_base_epmf_nof_keys_alloc_for_dir_ext_set;
    data_index = dnx_data_field_base_epmf_define_dir_ext_single_key_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_base_epmf_dir_ext_single_key_size_set;
    data_index = dnx_data_field_base_epmf_define_dir_ext_first_key;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_base_epmf_dir_ext_first_key_set;
    data_index = dnx_data_field_base_epmf_define_fes_key_select_for_zero_bit;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_base_epmf_fes_key_select_for_zero_bit_set;
    data_index = dnx_data_field_base_epmf_define_fes_shift_for_zero_bit;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_base_epmf_fes_shift_for_zero_bit_set;

    

    
    
    submodule_index = dnx_data_field_submodule_tcam;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_tcam_define_dt_max_key_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_tcam_dt_max_key_size_set;
    data_index = dnx_data_field_tcam_define_hw_bank_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_tcam_hw_bank_size_set;
    data_index = dnx_data_field_tcam_define_nof_big_bank_lines;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_tcam_nof_big_bank_lines_set;
    data_index = dnx_data_field_tcam_define_nof_entries_160_bits;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_tcam_nof_entries_160_bits_set;
    data_index = dnx_data_field_tcam_define_nof_entries_80_bits;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_tcam_nof_entries_80_bits_set;

    

    
    
    submodule_index = dnx_data_field_submodule_efes;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_efes_define_max_nof_key_selects_per_field_io;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_efes_max_nof_key_selects_per_field_io_set;

    

    
    data_index = dnx_data_field_efes_table_key_select_properties;
    table = &submodule->tables[data_index];
    table->set = q2a_a0_dnx_data_field_efes_key_select_properties_set;
    
    submodule_index = dnx_data_field_submodule_fem;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_fem_define_max_nof_key_selects_per_field_io;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_fem_max_nof_key_selects_per_field_io_set;

    

    
    data_index = dnx_data_field_fem_table_key_select_properties;
    table = &submodule->tables[data_index];
    table->set = q2a_a0_dnx_data_field_fem_key_select_properties_set;
    
    submodule_index = dnx_data_field_submodule_qual;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_qual_define_ifwd2_pbus_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_qual_ifwd2_pbus_size_set;
    data_index = dnx_data_field_qual_define_ipmf1_pbus_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_qual_ipmf1_pbus_size_set;
    data_index = dnx_data_field_qual_define_ipmf2_pbus_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_qual_ipmf2_pbus_size_set;
    data_index = dnx_data_field_qual_define_ipmf3_pbus_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_qual_ipmf3_pbus_size_set;
    data_index = dnx_data_field_qual_define_epmf_pbus_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_qual_epmf_pbus_size_set;

    

    
    
    submodule_index = dnx_data_field_submodule_virtual_wire;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_field_virtual_wire_in_lif_ac_wide_is_vw;
    feature = &submodule->features[data_index];
    feature->set = q2a_a0_dnx_data_field_virtual_wire_in_lif_ac_wide_is_vw_set;

    
    
    submodule_index = dnx_data_field_submodule_exem;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_exem_define_small_ipmf2_key;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_exem_small_ipmf2_key_set;
    data_index = dnx_data_field_exem_define_small_ipmf2_key_part;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_exem_small_ipmf2_key_part_set;
    data_index = dnx_data_field_exem_define_small_ipmf2_key_hw_value;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_exem_small_ipmf2_key_hw_value_set;
    data_index = dnx_data_field_exem_define_small_ipmf2_key_hw_bits;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_exem_small_ipmf2_key_hw_bits_set;
    data_index = dnx_data_field_exem_define_ipmf1_key_configurable;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_exem_ipmf1_key_configurable_set;
    data_index = dnx_data_field_exem_define_ipmf1_key;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_exem_ipmf1_key_set;

    

    
    
    submodule_index = dnx_data_field_submodule_exem_learn_flush_machine;
    submodule = &module->submodules[submodule_index];

    

    

    
    data_index = dnx_data_field_exem_learn_flush_machine_table_sexem_flush_tcam_tcam_memories;
    table = &submodule->tables[data_index];
    table->set = q2a_a0_dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_tcam_memories_set;
    data_index = dnx_data_field_exem_learn_flush_machine_table_lexem_flush_tcam_tcam_memories;
    table = &submodule->tables[data_index];
    table->set = q2a_a0_dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_tcam_memories_set;
    data_index = dnx_data_field_exem_learn_flush_machine_table_sexem_flush_tcam_data_rules;
    table = &submodule->tables[data_index];
    table->set = q2a_a0_dnx_data_field_exem_learn_flush_machine_sexem_flush_tcam_data_rules_set;
    data_index = dnx_data_field_exem_learn_flush_machine_table_lexem_flush_tcam_data_rules;
    table = &submodule->tables[data_index];
    table->set = q2a_a0_dnx_data_field_exem_learn_flush_machine_lexem_flush_tcam_data_rules_set;
    
    submodule_index = dnx_data_field_submodule_init;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_init_define_fec_dest;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_init_fec_dest_set;
    data_index = dnx_data_field_init_define_l4_trap;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_init_l4_trap_set;
    data_index = dnx_data_field_init_define_oam_layer_index;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_init_oam_layer_index_set;
    data_index = dnx_data_field_init_define_oam_stat;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_init_oam_stat_set;
    data_index = dnx_data_field_init_define_roo;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_init_roo_set;
    data_index = dnx_data_field_init_define_jr1_ipmc_inlif;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_init_jr1_ipmc_inlif_set;
    data_index = dnx_data_field_init_define_j1_same_port;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_init_j1_same_port_set;
    data_index = dnx_data_field_init_define_j1_learning;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_init_j1_learning_set;
    data_index = dnx_data_field_init_define_flow_id;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_init_flow_id_set;

    

    
    
    submodule_index = dnx_data_field_submodule_features;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_features_define_switch_to_acl_context;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_switch_to_acl_context_set;
    data_index = dnx_data_field_features_define_tcam_result_half_payload_on_msb;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_tcam_result_half_payload_on_msb_set;
    data_index = dnx_data_field_features_define_kbp_opcode_in_ipmf1_cs;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_kbp_opcode_in_ipmf1_cs_set;
    data_index = dnx_data_field_features_define_kbp_hitbits_correct_in_ipmf1_cs;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_kbp_hitbits_correct_in_ipmf1_cs_set;
    data_index = dnx_data_field_features_define_exem_vmv_removable_from_payload;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_exem_vmv_removable_from_payload_set;
    data_index = dnx_data_field_features_define_multiple_dynamic_mem_enablers;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_multiple_dynamic_mem_enablers_set;
    data_index = dnx_data_field_features_define_state_table_ipmf1_key_select;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_state_table_ipmf1_key_select_set;
    data_index = dnx_data_field_features_define_state_table_acr_bus;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_state_table_acr_bus_set;
    data_index = dnx_data_field_features_define_hitbit_volatile;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_hitbit_volatile_set;
    data_index = dnx_data_field_features_define_fem_replace_msb_instead_lsb;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_fem_replace_msb_instead_lsb_set;
    data_index = dnx_data_field_features_define_dir_ext_epmf;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_dir_ext_epmf_set;
    data_index = dnx_data_field_features_define_hashing_process_lsb_to_msb;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_hashing_process_lsb_to_msb_set;
    data_index = dnx_data_field_features_define_exem_age_flush_scan;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_exem_age_flush_scan_set;
    data_index = dnx_data_field_features_define_epmf_outlif_profile_map;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_features_epmf_outlif_profile_map_set;

    

    
    
    submodule_index = dnx_data_field_submodule_signal_sizes;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_signal_sizes_define_dual_queue_size;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_signal_sizes_dual_queue_size_set;
    data_index = dnx_data_field_signal_sizes_define_ecn;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_signal_sizes_ecn_set;

    

    
    
    submodule_index = dnx_data_field_submodule_tests;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_field_tests_define_ingress_time_stamp_increased;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_tests_ingress_time_stamp_increased_set;
    data_index = dnx_data_field_tests_define_ace_debug_signals_exist;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_tests_ace_debug_signals_exist_set;
    data_index = dnx_data_field_tests_define_epmf_debug_rely_on_tcam0;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_tests_epmf_debug_rely_on_tcam0_set;
    data_index = dnx_data_field_tests_define_small_exem_addr_bits;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_field_tests_small_exem_addr_bits_set;

    

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


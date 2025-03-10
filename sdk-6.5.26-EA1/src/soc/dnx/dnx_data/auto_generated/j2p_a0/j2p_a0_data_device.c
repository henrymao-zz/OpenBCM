
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_DEVICE

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_device.h>







static shr_error_e
j2p_a0_dnx_data_device_general_hard_reset_disable_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_hard_reset_disable;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;
    
    feature->property.name = spn_CUSTOM_FEATURE;
    feature->property.doc = 
        "\n"
        "Init the device without hard reset.\n"
        "Can be 0,1 and 2\n"
        "Default: 2 - CMIC only reset instead of the DMU hard reset.\n"
        "\n"
    ;
    feature->property.method = dnxc_data_property_method_suffix_enable;
    feature->property.method_str = "suffix_enable";
    feature->property.suffix = "init_without_device_hard_reset";
    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &feature->property, -1, &feature->data));
    
    feature->flags |= (DNXC_DATA_F_PROPERTY);


    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_device_general_protection_state_ignore_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_protection_state_ignore;
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
j2p_a0_dnx_data_device_general_fai_unknown_address_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_fai_unknown_address_supported;
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
j2p_a0_dnx_data_device_general_nof_cores_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_nof_cores;
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
j2p_a0_dnx_data_device_general_valid_cores_bitmap_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_valid_cores_bitmap;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x3;

    
    define->data = 0x3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_device_general_core_clock_khz_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_clock_khz;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1350000;

    
    define->data = 1350000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_CORE_CLOCK_SPEED;
    define->property.doc = 
        "\n"
        "Device core clock frequency in KHZ\n"
        "Synopsis: core_clock_speed_khz=#freq#\n"
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_range;
    define->property.method_str = "suffix_range";
    define->property.suffix = "khz";
    define->property.range_min = 300000;
    define->property.range_max = 3000000;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_device_general_system_ref_core_clock_khz_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_system_ref_core_clock_khz;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1600000;

    
    define->data = 1600000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_SYSTEM_REF_CORE_CLOCK;
    define->property.doc = 
        "\n"
        "Specifies system reference clock speed in kHz.\n"
        "For a system containing a legacy device,the system reference clock needs to be set according to the legacy device.\n"
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_range;
    define->property.method_str = "suffix_range";
    define->property.suffix = "khz";
    define->property.range_min = 300000;
    define->property.range_max = 3000000;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_device_general_ref_core_clock_mhz_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_ref_core_clock_mhz;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 50;

    
    define->data = 50;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_device_general_core_clock_ndiv_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_clock_ndiv_size;
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
j2p_a0_dnx_data_device_general_core_clock_mdiv_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_clock_mdiv_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_device_general_core_clock_ndiv_offset_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_clock_ndiv_offset;
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
j2p_a0_dnx_data_device_general_core_clock_mdiv_offset_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_clock_mdiv_offset;
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
j2p_a0_dnx_data_device_general_device_id_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_device_id;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x8850;

    
    define->data = 0x8850;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
j2p_a0_dnx_data_device_general_ecc_err_masking_key_map(
    int unit,
    int key0_val,
    int key1_val,
    int *key0_index,
    int *key1_index)
{
    SHR_FUNC_INIT_VARS(unit);

    switch (key0_val)
    {
        case SOC_BLK_CGM:
            *key0_index = 0;
            break;
        case SOC_BLK_ECGM:
            *key0_index = 1;
            break;
        default:
            *key0_index = -1;
            break;
    }

    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_device_general_ecc_err_masking_key_reverse_map(
    int unit,
    int key0_index,
    int key1_index,
    int *key0_val,
    int *key1_val)
{
    SHR_FUNC_INIT_VARS(unit);

    switch (key0_index)
    {
        case 0:
            *key0_val = SOC_BLK_CGM;
            break;
        case 1:
            *key0_val = SOC_BLK_ECGM;
            break;
        default:
            *key0_val = -1;
            break;
    }

    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_device_general_ecc_err_masking_set(
    int unit)
{
    int block_type_index;
    dnx_data_device_general_ecc_err_masking_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int table_index = dnx_data_device_general_table_ecc_err_masking;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 2;
    table->info_get.key_size[0] = 2;

    
    table->values[0].default_val = "-1";
    table->values[1].default_val = "-1";
    table->values[2].default_val = "-1";
    table->values[3].default_val = "-1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_device_general_ecc_err_masking_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_device_general_table_ecc_err_masking");

    
    default_data = (dnx_data_device_general_ecc_err_masking_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->ecc_1bit_err_mask_reg = -1;
    default_data->ecc_1bit_err_field[0] = -1;
    default_data->ecc_2bit_err_mask_reg = -1;
    default_data->ecc_2bit_err_field[0] = -1;
    
    for (block_type_index = 0; block_type_index < table->keys[0].size; block_type_index++)
    {
        data = (dnx_data_device_general_ecc_err_masking_t *) dnxc_data_mgmt_table_data_get(unit, table, block_type_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    table->key_map = j2p_a0_dnx_data_device_general_ecc_err_masking_key_map;
    table->key_map_reverse = j2p_a0_dnx_data_device_general_ecc_err_masking_key_reverse_map;
    
    data = (dnx_data_device_general_ecc_err_masking_t *) dnxc_data_mgmt_table_data_get(unit, table, SOC_BLK_ECGM, 0);
    data->ecc_1bit_err_mask_reg = ECGM_ECC_ERR_1B_MONITOR_MEM_MASKr;
    SHR_RANGE_VERIFY(12, 0, DNX_MAX_NOF_ECC_ERR_MEMS, _SHR_E_INTERNAL, "out of bound access to array")
    data->ecc_1bit_err_field[0] = QDCM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[1] = QQSM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[2] = PDCM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[3] = PQSM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[4] = FDCM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[5] = FQSM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[6] = -1;
    data->ecc_1bit_err_field[7] = -1;
    data->ecc_1bit_err_field[8] = -1;
    data->ecc_1bit_err_field[9] = -1;
    data->ecc_1bit_err_field[10] = -1;
    data->ecc_1bit_err_field[11] = -1;
    data->ecc_2bit_err_mask_reg = ECGM_ECC_ERR_2B_MONITOR_MEM_MASKr;
    SHR_RANGE_VERIFY(12, 0, DNX_MAX_NOF_ECC_ERR_MEMS, _SHR_E_INTERNAL, "out of bound access to array")
    data->ecc_2bit_err_field[0] = QDCM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[1] = QQSM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[2] = PDCM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[3] = PQSM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[4] = FDCM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[5] = FQSM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[6] = -1;
    data->ecc_2bit_err_field[7] = -1;
    data->ecc_2bit_err_field[8] = -1;
    data->ecc_2bit_err_field[9] = -1;
    data->ecc_2bit_err_field[10] = -1;
    data->ecc_2bit_err_field[11] = -1;
    data = (dnx_data_device_general_ecc_err_masking_t *) dnxc_data_mgmt_table_data_get(unit, table, SOC_BLK_CGM, 0);
    data->ecc_1bit_err_mask_reg = CGM_ECC_ERR_1B_MONITOR_MEM_MASKr;
    SHR_RANGE_VERIFY(13, 0, DNX_MAX_NOF_ECC_ERR_MEMS, _SHR_E_INTERNAL, "out of bound access to array")
    data->ecc_1bit_err_field[0] = VSQC_SRAM_PDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[1] = VSQC_SRAM_BUFFERS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[2] = VSQC_WORDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[3] = VSQE_WORDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[4] = VSQE_SRAM_PDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[5] = VSQE_SRAM_BUFFERS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[6] = VSQD_SRAM_PDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[7] = VSQD_SRAM_BUFFERS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[8] = VSQD_WORDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[9] = VSQF_WORDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[10] = VSQF_SRAM_PDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[11] = VSQF_SRAM_BUFFERS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[12] = -1;
    data->ecc_2bit_err_mask_reg = CGM_ECC_ERR_2B_MONITOR_MEM_MASKr;
    SHR_RANGE_VERIFY(13, 0, DNX_MAX_NOF_ECC_ERR_MEMS, _SHR_E_INTERNAL, "out of bound access to array")
    data->ecc_2bit_err_field[0] = VSQC_SRAM_PDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[1] = VSQC_SRAM_BUFFERS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[2] = VSQC_WORDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[3] = VSQE_WORDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[4] = VSQE_SRAM_PDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[5] = VSQE_SRAM_BUFFERS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[6] = VSQD_SRAM_PDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[7] = VSQD_SRAM_BUFFERS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[8] = VSQD_WORDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[9] = VSQF_WORDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[10] = VSQF_SRAM_PDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[11] = VSQF_SRAM_BUFFERS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[12] = -1;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
j2p_a0_dnx_data_device_emulation_fmac_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_emulation;
    int feature_index = dnx_data_device_emulation_fmac_supported;
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
j2p_a0_dnx_data_device_otp_nof_words_in_row_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_otp;
    int define_index = dnx_data_device_otp_define_nof_words_in_row;
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
j2p_a0_dnx_data_device_otp_otp_instance_attributes_set(
    int unit)
{
    int otp_instance_index_index;
    dnx_data_device_otp_otp_instance_attributes_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_otp;
    int table_index = dnx_data_device_otp_table_otp_instance_attributes;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = SOC_DNXC_OTP_INSTANCE_COUNT;
    table->info_get.key_size[0] = SOC_DNXC_OTP_INSTANCE_COUNT;

    
    table->values[0].default_val = "-1";
    table->values[1].default_val = "0";
    table->values[2].default_val = "-1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_device_otp_otp_instance_attributes_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_device_otp_table_otp_instance_attributes");

    
    default_data = (dnx_data_device_otp_otp_instance_attributes_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->block_id = -1;
    default_data->is_supported = 0;
    default_data->size = -1;
    
    for (otp_instance_index_index = 0; otp_instance_index_index < table->keys[0].size; otp_instance_index_index++)
    {
        data = (dnx_data_device_otp_otp_instance_attributes_t *) dnxc_data_mgmt_table_data_get(unit, table, otp_instance_index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (SOC_DNXC_OTP_INSTANCE_GENERAL_USE < table->keys[0].size)
    {
        data = (dnx_data_device_otp_otp_instance_attributes_t *) dnxc_data_mgmt_table_data_get(unit, table, SOC_DNXC_OTP_INSTANCE_GENERAL_USE, 0);
        data->block_id = 1984;
        data->is_supported = 1;
        data->size = 16384;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}



shr_error_e
j2p_a0_data_device_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_device;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_device_submodule_general;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_device_general_define_nof_cores;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_general_nof_cores_set;
    data_index = dnx_data_device_general_define_valid_cores_bitmap;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_general_valid_cores_bitmap_set;
    data_index = dnx_data_device_general_define_core_clock_khz;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_general_core_clock_khz_set;
    data_index = dnx_data_device_general_define_system_ref_core_clock_khz;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_general_system_ref_core_clock_khz_set;
    data_index = dnx_data_device_general_define_ref_core_clock_mhz;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_general_ref_core_clock_mhz_set;
    data_index = dnx_data_device_general_define_core_clock_ndiv_size;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_general_core_clock_ndiv_size_set;
    data_index = dnx_data_device_general_define_core_clock_mdiv_size;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_general_core_clock_mdiv_size_set;
    data_index = dnx_data_device_general_define_core_clock_ndiv_offset;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_general_core_clock_ndiv_offset_set;
    data_index = dnx_data_device_general_define_core_clock_mdiv_offset;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_general_core_clock_mdiv_offset_set;
    data_index = dnx_data_device_general_define_device_id;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_general_device_id_set;

    
    data_index = dnx_data_device_general_hard_reset_disable;
    feature = &submodule->features[data_index];
    feature->set = j2p_a0_dnx_data_device_general_hard_reset_disable_set;
    data_index = dnx_data_device_general_protection_state_ignore;
    feature = &submodule->features[data_index];
    feature->set = j2p_a0_dnx_data_device_general_protection_state_ignore_set;
    data_index = dnx_data_device_general_fai_unknown_address_supported;
    feature = &submodule->features[data_index];
    feature->set = j2p_a0_dnx_data_device_general_fai_unknown_address_supported_set;

    
    data_index = dnx_data_device_general_table_ecc_err_masking;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_device_general_ecc_err_masking_set;
    
    submodule_index = dnx_data_device_submodule_emulation;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_device_emulation_fmac_supported;
    feature = &submodule->features[data_index];
    feature->set = j2p_a0_dnx_data_device_emulation_fmac_supported_set;

    
    
    submodule_index = dnx_data_device_submodule_otp;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_device_otp_define_nof_words_in_row;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_device_otp_nof_words_in_row_set;

    

    
    data_index = dnx_data_device_otp_table_otp_instance_attributes;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_device_otp_otp_instance_attributes_set;

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


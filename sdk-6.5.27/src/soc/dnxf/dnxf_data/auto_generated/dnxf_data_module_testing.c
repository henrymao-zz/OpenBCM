
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_COMMON

#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_internal_module_testing.h>



#ifdef BCM_DNXF1_SUPPORT

extern shr_error_e ramon_a0_data_module_testing_attach(
    int unit);

#endif 



static shr_error_e
dnxf_data_module_testing_unsupported_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "unsupported";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnxf_data_module_testing_unsupported_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data module_testing unsupported features");

    submodule_data->features[dnxf_data_module_testing_unsupported_supported_feature].name = "supported_feature";
    submodule_data->features[dnxf_data_module_testing_unsupported_supported_feature].doc = "";
    submodule_data->features[dnxf_data_module_testing_unsupported_supported_feature].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnxf_data_module_testing_unsupported_unsupported_feature].name = "unsupported_feature";
    submodule_data->features[dnxf_data_module_testing_unsupported_unsupported_feature].doc = "";
    submodule_data->features[dnxf_data_module_testing_unsupported_unsupported_feature].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnxf_data_module_testing_unsupported_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data module_testing unsupported defines");

    submodule_data->defines[dnxf_data_module_testing_unsupported_define_supported_def].name = "supported_def";
    submodule_data->defines[dnxf_data_module_testing_unsupported_define_supported_def].doc = "";
    
    submodule_data->defines[dnxf_data_module_testing_unsupported_define_supported_def].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnxf_data_module_testing_unsupported_define_unsupported_def].name = "unsupported_def";
    submodule_data->defines[dnxf_data_module_testing_unsupported_define_unsupported_def].doc = "";
    
    submodule_data->defines[dnxf_data_module_testing_unsupported_define_unsupported_def].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnxf_data_module_testing_unsupported_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data module_testing unsupported tables");

    
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].name = "supported_table";
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].doc = "";
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].size_of_values = sizeof(dnxf_data_module_testing_unsupported_supported_table_t);
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].entry_get = dnxf_data_module_testing_unsupported_supported_table_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].nof_keys = 0;

    
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].nof_values, "_dnxf_data_module_testing_unsupported_table_supported_table table values");
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].values[0].name = "num";
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_supported_table].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_unsupported_supported_table_t, num);

    
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].name = "unsupported_table";
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].doc = "";
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].size_of_values = sizeof(dnxf_data_module_testing_unsupported_unsupported_table_t);
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].entry_get = dnxf_data_module_testing_unsupported_unsupported_table_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].nof_keys = 0;

    
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].nof_values, "_dnxf_data_module_testing_unsupported_table_unsupported_table table values");
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].values[0].name = "num";
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_unsupported_table_unsupported_table].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_unsupported_unsupported_table_t, num);


exit:
    SHR_FUNC_EXIT;
}


int
dnxf_data_module_testing_unsupported_feature_get(
    int unit,
    dnxf_data_module_testing_unsupported_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_unsupported, feature);
}


uint32
dnxf_data_module_testing_unsupported_supported_def_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_unsupported, dnxf_data_module_testing_unsupported_define_supported_def);
}

uint32
dnxf_data_module_testing_unsupported_unsupported_def_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_unsupported, dnxf_data_module_testing_unsupported_define_unsupported_def);
}



const dnxf_data_module_testing_unsupported_supported_table_t *
dnxf_data_module_testing_unsupported_supported_table_get(
    int unit)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_unsupported, dnxf_data_module_testing_unsupported_table_supported_table);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    return (const dnxf_data_module_testing_unsupported_supported_table_t *) data;

}

const dnxf_data_module_testing_unsupported_unsupported_table_t *
dnxf_data_module_testing_unsupported_unsupported_table_get(
    int unit)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_unsupported, dnxf_data_module_testing_unsupported_table_unsupported_table);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    return (const dnxf_data_module_testing_unsupported_unsupported_table_t *) data;

}


shr_error_e
dnxf_data_module_testing_unsupported_supported_table_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_unsupported_supported_table_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_unsupported, dnxf_data_module_testing_unsupported_table_supported_table);
    data = (const dnxf_data_module_testing_unsupported_supported_table_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, 0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->num);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_module_testing_unsupported_unsupported_table_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_unsupported_unsupported_table_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_unsupported, dnxf_data_module_testing_unsupported_table_unsupported_table);
    data = (const dnxf_data_module_testing_unsupported_unsupported_table_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, 0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->num);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnxf_data_module_testing_unsupported_supported_table_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_unsupported, dnxf_data_module_testing_unsupported_table_supported_table);

}

const dnxc_data_table_info_t *
dnxf_data_module_testing_unsupported_unsupported_table_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_unsupported, dnxf_data_module_testing_unsupported_table_unsupported_table);

}






static shr_error_e
dnxf_data_module_testing_types_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "types";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnxf_data_module_testing_types_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data module_testing types features");

    
    submodule_data->nof_defines = _dnxf_data_module_testing_types_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data module_testing types defines");

    
    submodule_data->nof_tables = _dnxf_data_module_testing_types_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data module_testing types tables");

    
    submodule_data->tables[dnxf_data_module_testing_types_table_all].name = "all";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].doc = "";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_types_table_all].size_of_values = sizeof(dnxf_data_module_testing_types_all_t);
    submodule_data->tables[dnxf_data_module_testing_types_table_all].entry_get = dnxf_data_module_testing_types_all_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_types_table_all].nof_keys = 0;

    
    submodule_data->tables[dnxf_data_module_testing_types_table_all].nof_values = 9;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_types_table_all].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_types_table_all].nof_values, "_dnxf_data_module_testing_types_table_all table values");
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[0].name = "intval";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[0].type = "int";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_types_all_t, intval);
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[1].name = "uint8val";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[1].type = "uint8";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[1].doc = "";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[1].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_types_all_t, uint8val);
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[2].name = "charval";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[2].type = "char";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[2].doc = "";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[2].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_types_all_t, charval);
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[3].name = "uint16val";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[3].type = "uint16";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[3].doc = "";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[3].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_types_all_t, uint16val);
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[4].name = "enumval";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[4].type = "bcm_fabric_device_type_t";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[4].doc = "";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[4].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_types_all_t, enumval);
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[5].name = "arrval";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[5].type = "uint32[10]";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[5].doc = "";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[5].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_types_all_t, arrval);
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[6].name = "pbmpval";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[6].type = "bcm_pbmp_t";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[6].doc = "";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[6].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_types_all_t, pbmpval);
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[7].name = "strval";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[7].type = "char *";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[7].doc = "";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[7].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_types_all_t, strval);
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[8].name = "bufferval";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[8].type = "char[100]";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[8].doc = "";
    submodule_data->tables[dnxf_data_module_testing_types_table_all].values[8].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_types_all_t, bufferval);


exit:
    SHR_FUNC_EXIT;
}


int
dnxf_data_module_testing_types_feature_get(
    int unit,
    dnxf_data_module_testing_types_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_types, feature);
}




const dnxf_data_module_testing_types_all_t *
dnxf_data_module_testing_types_all_get(
    int unit)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_types, dnxf_data_module_testing_types_table_all);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    return (const dnxf_data_module_testing_types_all_t *) data;

}


shr_error_e
dnxf_data_module_testing_types_all_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_types_all_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_types, dnxf_data_module_testing_types_table_all);
    data = (const dnxf_data_module_testing_types_all_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, 0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->intval);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->uint8val);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->charval);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->uint16val);
            break;
        case 4:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->enumval);
            break;
        case 5:
            DNXC_DATA_MGMT_ARR_STR(buffer, 10, data->arrval);
            break;
        case 6:
            DNXC_DATA_MGMT_PBMP_STR(buffer, data->pbmpval);
            break;
        case 7:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%s", data->strval == NULL ? "" : data->strval);
            break;
        case 8:
            DNXC_DATA_MGMT_ARR_STR(buffer, 100, data->bufferval);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnxf_data_module_testing_types_all_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_types, dnxf_data_module_testing_types_table_all);

}






static shr_error_e
dnxf_data_module_testing_property_methods_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "property_methods";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnxf_data_module_testing_property_methods_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data module_testing property_methods features");

    submodule_data->features[dnxf_data_module_testing_property_methods_feature_enable].name = "feature_enable";
    submodule_data->features[dnxf_data_module_testing_property_methods_feature_enable].doc = "";
    submodule_data->features[dnxf_data_module_testing_property_methods_feature_enable].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnxf_data_module_testing_property_methods_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data module_testing property_methods defines");

    submodule_data->defines[dnxf_data_module_testing_property_methods_define_numeric_range].name = "numeric_range";
    submodule_data->defines[dnxf_data_module_testing_property_methods_define_numeric_range].doc = "";
    
    submodule_data->defines[dnxf_data_module_testing_property_methods_define_numeric_range].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnxf_data_module_testing_property_methods_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data module_testing property_methods tables");

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].name = "enable";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].size_of_values = sizeof(dnxf_data_module_testing_property_methods_enable_t);
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].entry_get = dnxf_data_module_testing_property_methods_enable_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].nof_keys = 0;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].nof_values, "_dnxf_data_module_testing_property_methods_table_enable table values");
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].values[0].name = "val";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_enable].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_property_methods_enable_t, val);

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].name = "port_enable";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].size_of_values = sizeof(dnxf_data_module_testing_property_methods_port_enable_t);
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].entry_get = dnxf_data_module_testing_property_methods_port_enable_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].nof_keys = 1;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].keys[0].name = "port";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].nof_values, "_dnxf_data_module_testing_property_methods_table_port_enable table values");
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].values[0].name = "val";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_enable].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_property_methods_port_enable_t, val);

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].name = "suffix_enable";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].size_of_values = sizeof(dnxf_data_module_testing_property_methods_suffix_enable_t);
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].entry_get = dnxf_data_module_testing_property_methods_suffix_enable_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].nof_keys = 1;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].keys[0].name = "link";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].nof_values, "_dnxf_data_module_testing_property_methods_table_suffix_enable table values");
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].values[0].name = "val";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_enable].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_property_methods_suffix_enable_t, val);

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].name = "range";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].size_of_values = sizeof(dnxf_data_module_testing_property_methods_range_t);
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].entry_get = dnxf_data_module_testing_property_methods_range_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].nof_keys = 0;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].nof_values, "_dnxf_data_module_testing_property_methods_table_range table values");
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].values[0].name = "val";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_range].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_property_methods_range_t, val);

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].name = "port_range";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].size_of_values = sizeof(dnxf_data_module_testing_property_methods_port_range_t);
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].entry_get = dnxf_data_module_testing_property_methods_port_range_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].nof_keys = 1;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].keys[0].name = "port";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].nof_values, "_dnxf_data_module_testing_property_methods_table_port_range table values");
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].values[0].name = "val";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_range].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_property_methods_port_range_t, val);

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].name = "suffix_range";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].size_of_values = sizeof(dnxf_data_module_testing_property_methods_suffix_range_t);
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].entry_get = dnxf_data_module_testing_property_methods_suffix_range_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].nof_keys = 1;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].keys[0].name = "link";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].nof_values, "_dnxf_data_module_testing_property_methods_table_suffix_range table values");
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].values[0].name = "val";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_range].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_property_methods_suffix_range_t, val);

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].name = "direct_map";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].size_of_values = sizeof(dnxf_data_module_testing_property_methods_direct_map_t);
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].entry_get = dnxf_data_module_testing_property_methods_direct_map_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].nof_keys = 0;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].nof_values, "_dnxf_data_module_testing_property_methods_table_direct_map table values");
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].values[0].name = "val";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_direct_map].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_property_methods_direct_map_t, val);

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].name = "port_direct_map";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].size_of_values = sizeof(dnxf_data_module_testing_property_methods_port_direct_map_t);
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].entry_get = dnxf_data_module_testing_property_methods_port_direct_map_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].nof_keys = 1;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].keys[0].name = "port";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].nof_values, "_dnxf_data_module_testing_property_methods_table_port_direct_map table values");
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].values[0].name = "val";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_port_direct_map].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_property_methods_port_direct_map_t, val);

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].name = "suffix_direct_map";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].size_of_values = sizeof(dnxf_data_module_testing_property_methods_suffix_direct_map_t);
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].entry_get = dnxf_data_module_testing_property_methods_suffix_direct_map_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].nof_keys = 1;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].keys[0].name = "link";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].nof_values, "_dnxf_data_module_testing_property_methods_table_suffix_direct_map table values");
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].values[0].name = "val";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_suffix_direct_map].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_property_methods_suffix_direct_map_t, val);

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].name = "custom";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].size_of_values = sizeof(dnxf_data_module_testing_property_methods_custom_t);
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].entry_get = dnxf_data_module_testing_property_methods_custom_entry_str_get;

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].nof_keys = 2;
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].keys[0].name = "link";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].keys[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].keys[1].name = "pipe";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].keys[1].doc = "";

    
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].nof_values, "_dnxf_data_module_testing_property_methods_table_custom table values");
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].values[0].name = "val";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].values[0].doc = "";
    submodule_data->tables[dnxf_data_module_testing_property_methods_table_custom].values[0].offset = UTILEX_OFFSETOF(dnxf_data_module_testing_property_methods_custom_t, val);


exit:
    SHR_FUNC_EXIT;
}


int
dnxf_data_module_testing_property_methods_feature_get(
    int unit,
    dnxf_data_module_testing_property_methods_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, feature);
}


uint32
dnxf_data_module_testing_property_methods_numeric_range_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_define_numeric_range);
}



const dnxf_data_module_testing_property_methods_enable_t *
dnxf_data_module_testing_property_methods_enable_get(
    int unit)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_enable);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    return (const dnxf_data_module_testing_property_methods_enable_t *) data;

}

const dnxf_data_module_testing_property_methods_port_enable_t *
dnxf_data_module_testing_property_methods_port_enable_get(
    int unit,
    int port)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_port_enable);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, port, 0);
    return (const dnxf_data_module_testing_property_methods_port_enable_t *) data;

}

const dnxf_data_module_testing_property_methods_suffix_enable_t *
dnxf_data_module_testing_property_methods_suffix_enable_get(
    int unit,
    int link)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_suffix_enable);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, link, 0);
    return (const dnxf_data_module_testing_property_methods_suffix_enable_t *) data;

}

const dnxf_data_module_testing_property_methods_range_t *
dnxf_data_module_testing_property_methods_range_get(
    int unit)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_range);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    return (const dnxf_data_module_testing_property_methods_range_t *) data;

}

const dnxf_data_module_testing_property_methods_port_range_t *
dnxf_data_module_testing_property_methods_port_range_get(
    int unit,
    int port)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_port_range);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, port, 0);
    return (const dnxf_data_module_testing_property_methods_port_range_t *) data;

}

const dnxf_data_module_testing_property_methods_suffix_range_t *
dnxf_data_module_testing_property_methods_suffix_range_get(
    int unit,
    int link)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_suffix_range);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, link, 0);
    return (const dnxf_data_module_testing_property_methods_suffix_range_t *) data;

}

const dnxf_data_module_testing_property_methods_direct_map_t *
dnxf_data_module_testing_property_methods_direct_map_get(
    int unit)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_direct_map);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    return (const dnxf_data_module_testing_property_methods_direct_map_t *) data;

}

const dnxf_data_module_testing_property_methods_port_direct_map_t *
dnxf_data_module_testing_property_methods_port_direct_map_get(
    int unit,
    int port)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_port_direct_map);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, port, 0);
    return (const dnxf_data_module_testing_property_methods_port_direct_map_t *) data;

}

const dnxf_data_module_testing_property_methods_suffix_direct_map_t *
dnxf_data_module_testing_property_methods_suffix_direct_map_get(
    int unit,
    int link)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_suffix_direct_map);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, link, 0);
    return (const dnxf_data_module_testing_property_methods_suffix_direct_map_t *) data;

}

const dnxf_data_module_testing_property_methods_custom_t *
dnxf_data_module_testing_property_methods_custom_get(
    int unit,
    int link,
    int pipe)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_custom);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, link, pipe);
    return (const dnxf_data_module_testing_property_methods_custom_t *) data;

}


shr_error_e
dnxf_data_module_testing_property_methods_enable_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_property_methods_enable_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_enable);
    data = (const dnxf_data_module_testing_property_methods_enable_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, 0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_module_testing_property_methods_port_enable_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_property_methods_port_enable_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_port_enable);
    data = (const dnxf_data_module_testing_property_methods_port_enable_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_module_testing_property_methods_suffix_enable_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_property_methods_suffix_enable_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_suffix_enable);
    data = (const dnxf_data_module_testing_property_methods_suffix_enable_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_module_testing_property_methods_range_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_property_methods_range_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_range);
    data = (const dnxf_data_module_testing_property_methods_range_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, 0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_module_testing_property_methods_port_range_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_property_methods_port_range_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_port_range);
    data = (const dnxf_data_module_testing_property_methods_port_range_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_module_testing_property_methods_suffix_range_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_property_methods_suffix_range_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_suffix_range);
    data = (const dnxf_data_module_testing_property_methods_suffix_range_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_module_testing_property_methods_direct_map_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_property_methods_direct_map_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_direct_map);
    data = (const dnxf_data_module_testing_property_methods_direct_map_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, 0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_module_testing_property_methods_port_direct_map_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_property_methods_port_direct_map_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_port_direct_map);
    data = (const dnxf_data_module_testing_property_methods_port_direct_map_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_module_testing_property_methods_suffix_direct_map_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_property_methods_suffix_direct_map_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_suffix_direct_map);
    data = (const dnxf_data_module_testing_property_methods_suffix_direct_map_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_module_testing_property_methods_custom_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_module_testing_property_methods_custom_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_custom);
    data = (const dnxf_data_module_testing_property_methods_custom_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, key1);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnxf_data_module_testing_property_methods_enable_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_enable);

}

const dnxc_data_table_info_t *
dnxf_data_module_testing_property_methods_port_enable_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_port_enable);

}

const dnxc_data_table_info_t *
dnxf_data_module_testing_property_methods_suffix_enable_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_suffix_enable);

}

const dnxc_data_table_info_t *
dnxf_data_module_testing_property_methods_range_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_range);

}

const dnxc_data_table_info_t *
dnxf_data_module_testing_property_methods_port_range_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_port_range);

}

const dnxc_data_table_info_t *
dnxf_data_module_testing_property_methods_suffix_range_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_suffix_range);

}

const dnxc_data_table_info_t *
dnxf_data_module_testing_property_methods_direct_map_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_direct_map);

}

const dnxc_data_table_info_t *
dnxf_data_module_testing_property_methods_port_direct_map_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_port_direct_map);

}

const dnxc_data_table_info_t *
dnxf_data_module_testing_property_methods_suffix_direct_map_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_suffix_direct_map);

}

const dnxc_data_table_info_t *
dnxf_data_module_testing_property_methods_custom_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_property_methods, dnxf_data_module_testing_property_methods_table_custom);

}






static shr_error_e
dnxf_data_module_testing_max_test_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "max_test";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnxf_data_module_testing_max_test_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data module_testing max_test features");

    
    submodule_data->nof_defines = _dnxf_data_module_testing_max_test_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data module_testing max_test defines");

    submodule_data->defines[dnxf_data_module_testing_max_test_define_greater_d3].name = "greater_d3";
    submodule_data->defines[dnxf_data_module_testing_max_test_define_greater_d3].doc = "";
    
    submodule_data->defines[dnxf_data_module_testing_max_test_define_greater_d3].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnxf_data_module_testing_max_test_define_greater_d1].name = "greater_d1";
    submodule_data->defines[dnxf_data_module_testing_max_test_define_greater_d1].doc = "";
    
    submodule_data->defines[dnxf_data_module_testing_max_test_define_greater_d1].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnxf_data_module_testing_max_test_define_same_value].name = "same_value";
    submodule_data->defines[dnxf_data_module_testing_max_test_define_same_value].doc = "";
    
    submodule_data->defines[dnxf_data_module_testing_max_test_define_same_value].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnxf_data_module_testing_max_test_define_d1_undefined].name = "d1_undefined";
    submodule_data->defines[dnxf_data_module_testing_max_test_define_d1_undefined].doc = "";
    
    submodule_data->defines[dnxf_data_module_testing_max_test_define_d1_undefined].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnxf_data_module_testing_max_test_define_d3_undefined].name = "d3_undefined";
    submodule_data->defines[dnxf_data_module_testing_max_test_define_d3_undefined].doc = "";
    
    submodule_data->defines[dnxf_data_module_testing_max_test_define_d3_undefined].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnxf_data_module_testing_max_test_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data module_testing max_test tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnxf_data_module_testing_max_test_feature_get(
    int unit,
    dnxf_data_module_testing_max_test_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_max_test, feature);
}


uint32
dnxf_data_module_testing_max_test_greater_d3_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_max_test, dnxf_data_module_testing_max_test_define_greater_d3);
}

uint32
dnxf_data_module_testing_max_test_greater_d1_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_max_test, dnxf_data_module_testing_max_test_define_greater_d1);
}

uint32
dnxf_data_module_testing_max_test_same_value_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_max_test, dnxf_data_module_testing_max_test_define_same_value);
}

uint32
dnxf_data_module_testing_max_test_d1_undefined_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_max_test, dnxf_data_module_testing_max_test_define_d1_undefined);
}

uint32
dnxf_data_module_testing_max_test_d3_undefined_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_module_testing, dnxf_data_module_testing_submodule_max_test, dnxf_data_module_testing_max_test_define_d3_undefined);
}







shr_error_e
dnxf_data_module_testing_init(
    int unit,
    dnxc_data_module_t *module_data)
{
    SHR_FUNC_INIT_VARS(unit);

    
    module_data->name = "module_testing";
    module_data->nof_submodules = _dnxf_data_module_testing_submodule_nof;
    DNXC_DATA_ALLOC(module_data->submodules, dnxc_data_submodule_t, module_data->nof_submodules, "_dnxc_data module_testing submodules");

    
    SHR_IF_ERR_EXIT(dnxf_data_module_testing_unsupported_init(unit, &module_data->submodules[dnxf_data_module_testing_submodule_unsupported]));
    SHR_IF_ERR_EXIT(dnxf_data_module_testing_types_init(unit, &module_data->submodules[dnxf_data_module_testing_submodule_types]));
    SHR_IF_ERR_EXIT(dnxf_data_module_testing_property_methods_init(unit, &module_data->submodules[dnxf_data_module_testing_submodule_property_methods]));
    SHR_IF_ERR_EXIT(dnxf_data_module_testing_max_test_init(unit, &module_data->submodules[dnxf_data_module_testing_submodule_max_test]));
    
#ifdef BCM_DNXF1_SUPPORT

    if (dnxc_data_mgmt_is_ramon(unit))
    {
        SHR_IF_ERR_EXIT(ramon_a0_data_module_testing_attach(unit));
    }
    else

#endif 
    {
        SHR_EXIT();
    }

exit:
    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


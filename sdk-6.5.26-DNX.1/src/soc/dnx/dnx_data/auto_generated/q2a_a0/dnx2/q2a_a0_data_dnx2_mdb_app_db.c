
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

#include <soc/dnx/dnx_data/auto_generated/dnx2/dnx_data_internal_dnx2_mdb_app_db.h>








static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_1TAG_STAT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_1TAG_STAT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_1TAG_STAT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_1TAG_STAT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_1TAG_STAT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_1TAG_STAT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 22;

    
    define->data = 22;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 23;

    
    define->data = 23;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 24;

    
    define->data = 24;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 19;

    
    define->data = 19;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 17;

    
    define->data = 17;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 13;

    
    define->data = 13;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 37;

    
    define->data = 37;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 29;

    
    define->data = 29;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 25;

    
    define->data = 25;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 49;

    
    define->data = 49;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 17;

    
    define->data = 17;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 9;

    
    define->data = 9;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2;

    
    define->data = 2;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 9;

    
    define->data = 9;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___ESEM_COMMAND_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___ESEM_COMMAND;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___ESEM_COMMAND", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___ESEM_COMMAND___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___ESEM_COMMAND___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___ESEM_COMMAND___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 9;

    
    define->data = 9;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___ESEM_COMMAND_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___ESEM_COMMAND;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___ESEM_COMMAND", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___ESEM_COMMAND___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___ESEM_COMMAND___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___ESEM_COMMAND___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___ESEM_COMMAND_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___ESEM_COMMAND;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___ESEM_COMMAND", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___ESEM_COMMAND___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___ESEM_COMMAND___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___ESEM_COMMAND___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___ESEM_COMMAND_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___ESEM_COMMAND;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___ESEM_COMMAND", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___ESEM_COMMAND___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___ESEM_COMMAND___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___ESEM_COMMAND___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 16;

    
    define->data = 16;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_PROTECTION_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_PROTECTION;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_PROTECTION", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_PROTECTION___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_PROTECTION___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_PROTECTION___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_TRIPLE_TAG_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_TRIPLE_TAG;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_TRIPLE_TAG", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_TRIPLE_TAG___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_TRIPLE_TAG___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_TRIPLE_TAG___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___1____set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___1___;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___1___", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___1______valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___1______valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___1______valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___1____set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___1___;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___1___", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___1______valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___1______valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___1______valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_L2_FODO_VLANS_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_L2_FODO_VLANS;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_L2_FODO_VLANS", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 33;

    
    define->data = 33;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_L2_FODO_VLANS___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_L2_FODO_VLANS___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_L2_FODO_VLANS___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_RSPAN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_RSPAN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_RSPAN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 43;

    
    define->data = 43;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_RSPAN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_RSPAN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_RSPAN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___1____set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___1___;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___1___", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___1______valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___1______valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___1______valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___1____set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___1___;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___1___", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___1______valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___1______valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___1______valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_Custom_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_Custom;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_Custom", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 5;

    
    define->data = 5;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_Custom___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_Custom___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_Custom___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_tunneling_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_tunneling;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_tunneling", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2;

    
    define->data = 2;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_tunneling___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_tunneling___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_tunneling___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_STAT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_STAT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_STAT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_STAT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_STAT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_STAT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1____set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_Default___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_Default___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PP_Port_SA_Based_Default___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_Default___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_Default___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PP_Port_SA_Based_Default___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_Tagged___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_Tagged___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PP_Port_SA_Based_Tagged___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_Tagged___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_Tagged___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PP_Port_SA_Based_Tagged___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_VLAN_Specific___MAPPED_PP_PORT_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_VLAN_Specific___MAPPED_PP_PORT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PP_Port_SA_Based_VLAN_Specific___MAPPED_PP_PORT", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_VLAN_Specific___MAPPED_PP_PORT___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_VLAN_Specific___MAPPED_PP_PORT___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___PP_Port_SA_Based_VLAN_Specific___MAPPED_PP_PORT___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2;

    
    define->data = 2;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    int define_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}




shr_error_e
q2a_a0_data_dnx2_mdb_app_db_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_dnx2_mdb_app_db;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_dnx2_mdb_app_db_submodule_fields;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_1TAG_STAT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_1TAG_STAT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_1TAG_STAT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ARP_AC_1TAG_STAT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___ESEM_COMMAND;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___ESEM_COMMAND_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___ESEM_COMMAND___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___ESEM_COMMAND___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___ESEM_COMMAND;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___ESEM_COMMAND_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___ESEM_COMMAND___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___ESEM_COMMAND___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___ESEM_COMMAND;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___ESEM_COMMAND_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___ESEM_COMMAND___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___ESEM_COMMAND___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___ESEM_COMMAND;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___ESEM_COMMAND_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___ESEM_COMMAND___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___ESEM_COMMAND___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_PROTECTION;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_PROTECTION_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_PROTECTION___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_STAT_PROTECTION___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_TRIPLE_TAG;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_TRIPLE_TAG_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_TRIPLE_TAG___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_AC_TRIPLE_TAG___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___1___;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___1____set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___1______valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC_1TAG_STAT___1______valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___1___;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___1____set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___1______valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_ARP_AC___1______valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_L2_FODO_VLANS;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_L2_FODO_VLANS_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_L2_FODO_VLANS___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_L2_FODO_VLANS___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_RSPAN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_RSPAN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_RSPAN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_EM_BUSTER___ETPS_RSPAN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___1___;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___1____set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___1______valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC_1TAG_STAT___1______valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___1___;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___1____set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___1______valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_AC___1______valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_Custom;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_Custom_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_Custom___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_Custom___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_tunneling;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_tunneling_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_tunneling___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ARP_SA_tunneling___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_STAT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_STAT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_STAT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_STAT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1____set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_Default___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_Default___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_Default___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_Default___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_Tagged___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_Tagged___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_Tagged___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_Tagged___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_VLAN_Specific___MAPPED_PP_PORT;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_VLAN_Specific___MAPPED_PP_PORT_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PP_Port_SA_Based_VLAN_Specific___MAPPED_PP_PORT___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PP_Port_SA_Based_VLAN_Specific___MAPPED_PP_PORT___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN_set;
    data_index = dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid;
    define = &submodule->defines[data_index];
    define->set = q2a_a0_dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid_set;

    

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


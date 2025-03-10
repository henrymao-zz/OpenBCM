
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



#ifdef BCM_DNX2_SUPPORT

extern shr_error_e jr2_a0_data_dnx2_mdb_app_db_attach(
    int unit);

#endif 
#ifdef BCM_DNX2_SUPPORT

extern shr_error_e jr2_b0_data_dnx2_mdb_app_db_attach(
    int unit);

#endif 
#ifdef BCM_DNX2_SUPPORT

extern shr_error_e j2c_a0_data_dnx2_mdb_app_db_attach(
    int unit);

#endif 
#ifdef BCM_DNX2_SUPPORT

extern shr_error_e q2a_a0_data_dnx2_mdb_app_db_attach(
    int unit);

#endif 
#ifdef BCM_DNX2_SUPPORT

extern shr_error_e q2a_b0_data_dnx2_mdb_app_db_attach(
    int unit);

#endif 
#ifdef BCM_DNX2_SUPPORT

extern shr_error_e j2p_a0_data_dnx2_mdb_app_db_attach(
    int unit);

#endif 
#ifdef BCM_DNX2_SUPPORT

extern shr_error_e j2x_a0_data_dnx2_mdb_app_db_attach(
    int unit);

#endif 



static shr_error_e
dnx_data_dnx2_mdb_app_db_fields_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "fields";
    submodule_data->doc = "MDB modified fields";
    
    submodule_data->nof_features = _dnx_data_dnx2_mdb_app_db_fields_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data dnx2_mdb_app_db fields features");

    
    submodule_data->nof_defines = _dnx_data_dnx2_mdb_app_db_fields_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data dnx2_mdb_app_db fields defines");

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid].name = "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3].name = "numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3].doc = "configures field size of numeric numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid].name = "numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid].doc = "configures field validity of numeric numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN].name = "numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid].name = "numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING].doc = "configures field size of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID].doc = "configures field size of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE].name = "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE].name = "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE].name = "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE].name = "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE].name = "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE].name = "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE].name = "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE].name = "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE].name = "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE].name = "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE].name = "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid].name = "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE].name = "numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE].name = "numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE].name = "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE].name = "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE].name = "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE].name = "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE].name = "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE].name = "numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE].name = "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE].name = "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE].name = "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE].name = "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE].name = "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE].doc = "configures field size of numeric numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid].name = "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE].name = "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE].name = "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE].name = "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA].name = "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA].doc = "configures field size of numeric numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid].name = "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE].name = "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid].name = "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE].name = "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE].name = "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE].name = "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE].name = "numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN].name = "numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE].name = "numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE].name = "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE].name = "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN].name = "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE].name = "numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT].name = "numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT].doc = "configures field size of numeric numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid].name = "numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING].name = "numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING].doc = "configures field size of numeric numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid].name = "numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE].name = "numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid].name = "numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG].name = "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG].doc = "configures field size of numeric numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid].name = "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid].doc = "configures field validity of numeric numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF].name = "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF].doc = "configures field size of numeric numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid].name = "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid].doc = "configures field validity of numeric numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___].name = "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___].doc = "configures field size of numeric numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid].name = "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid].doc = "configures field validity of numeric numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT].name = "numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT].name = "numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT].name = "numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT].name = "numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT].name = "numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT].name = "numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN].name = "numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid].name = "numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN].name = "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid].name = "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN].name = "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid].name = "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN].name = "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid].name = "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN].name = "numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT].name = "numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT].name = "numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].name = "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].doc = "configures field size of numeric numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].name = "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].doc = "configures field validity of numeric numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].name = "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].doc = "configures field size of numeric numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].name = "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].doc = "configures field validity of numeric numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE].name = "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE].doc = "configures field size of numeric numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].name = "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].doc = "configures field validity of numeric numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN].name = "numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid].name = "numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN].name = "numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid].name = "numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT].name = "numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT].name = "numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN].name = "numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid].name = "numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT].name = "numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid].name = "numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT].name = "numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT].doc = "configures field size of numeric numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid].name = "numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid].doc = "configures field validity of numeric numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN].name = "numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid].name = "numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN].name = "numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid].name = "numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC].name = "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC].doc = "configures field size of numeric numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid].name = "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid].doc = "configures field validity of numeric numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING].name = "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING].doc = "configures field size of numeric numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid].name = "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid].doc = "configures field validity of numeric numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN].name = "numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid].name = "numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN].name = "numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN].doc = "configures field size of numeric numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid].name = "numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid].doc = "configures field validity of numeric numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___0].name = "numeric_mdb_field___0";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___0].doc = "configures field size of numeric 0";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___0].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___0___valid].name = "numeric_mdb_field___0___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___0___valid].doc = "configures field validity of numeric 0";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___0___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___1].name = "numeric_mdb_field___1";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___1].doc = "configures field size of numeric 1";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___1].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___1___valid].name = "numeric_mdb_field___1___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___1___valid].doc = "configures field validity of numeric 1";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___1___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___2].name = "numeric_mdb_field___2";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___2].doc = "configures field size of numeric 2";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___2].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___2___valid].name = "numeric_mdb_field___2___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___2___valid].doc = "configures field validity of numeric 2";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___2___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___3].name = "numeric_mdb_field___3";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___3].doc = "configures field size of numeric 3";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___3].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___3___valid].name = "numeric_mdb_field___3___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___3___valid].doc = "configures field validity of numeric 3";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___3___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___4].name = "numeric_mdb_field___4";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___4].doc = "configures field size of numeric 4";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___4].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___4___valid].name = "numeric_mdb_field___4___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___4___valid].doc = "configures field validity of numeric 4";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___4___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___5].name = "numeric_mdb_field___5";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___5].doc = "configures field size of numeric 5";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___5].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___5___valid].name = "numeric_mdb_field___5___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___5___valid].doc = "configures field validity of numeric 5";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___5___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___6].name = "numeric_mdb_field___6";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___6].doc = "configures field size of numeric 6";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___6].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___6___valid].name = "numeric_mdb_field___6___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___6___valid].doc = "configures field validity of numeric 6";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___6___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___7].name = "numeric_mdb_field___7";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___7].doc = "configures field size of numeric 7";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___7].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___7___valid].name = "numeric_mdb_field___7___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___7___valid].doc = "configures field validity of numeric 7";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___7___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___8].name = "numeric_mdb_field___8";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___8].doc = "configures field size of numeric 8";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___8].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___8___valid].name = "numeric_mdb_field___8___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___8___valid].doc = "configures field validity of numeric 8";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___8___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___9].name = "numeric_mdb_field___9";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___9].doc = "configures field size of numeric 9";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___9].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___9___valid].name = "numeric_mdb_field___9___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___9___valid].doc = "configures field validity of numeric 9";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___9___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___10].name = "numeric_mdb_field___10";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___10].doc = "configures field size of numeric 10";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___10].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___10___valid].name = "numeric_mdb_field___10___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___10___valid].doc = "configures field validity of numeric 10";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___10___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___11].name = "numeric_mdb_field___11";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___11].doc = "configures field size of numeric 11";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___11].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___11___valid].name = "numeric_mdb_field___11___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___11___valid].doc = "configures field validity of numeric 11";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___11___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___12].name = "numeric_mdb_field___12";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___12].doc = "configures field size of numeric 12";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___12].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___12___valid].name = "numeric_mdb_field___12___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___12___valid].doc = "configures field validity of numeric 12";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___12___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___13].name = "numeric_mdb_field___13";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___13].doc = "configures field size of numeric 13";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___13].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___13___valid].name = "numeric_mdb_field___13___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___13___valid].doc = "configures field validity of numeric 13";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___13___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___14].name = "numeric_mdb_field___14";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___14].doc = "configures field size of numeric 14";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___14].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___14___valid].name = "numeric_mdb_field___14___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___14___valid].doc = "configures field validity of numeric 14";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___14___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___15].name = "numeric_mdb_field___15";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___15].doc = "configures field size of numeric 15";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___15].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___15___valid].name = "numeric_mdb_field___15___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___15___valid].doc = "configures field validity of numeric 15";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___15___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___16].name = "numeric_mdb_field___16";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___16].doc = "configures field size of numeric 16";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___16].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___16___valid].name = "numeric_mdb_field___16___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___16___valid].doc = "configures field validity of numeric 16";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___16___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___17].name = "numeric_mdb_field___17";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___17].doc = "configures field size of numeric 17";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___17].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___17___valid].name = "numeric_mdb_field___17___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___17___valid].doc = "configures field validity of numeric 17";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___17___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___18].name = "numeric_mdb_field___18";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___18].doc = "configures field size of numeric 18";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___18].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___18___valid].name = "numeric_mdb_field___18___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___18___valid].doc = "configures field validity of numeric 18";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___18___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___19].name = "numeric_mdb_field___19";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___19].doc = "configures field size of numeric 19";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___19].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___19___valid].name = "numeric_mdb_field___19___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___19___valid].doc = "configures field validity of numeric 19";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___19___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___20].name = "numeric_mdb_field___20";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___20].doc = "configures field size of numeric 20";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___20].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___20___valid].name = "numeric_mdb_field___20___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___20___valid].doc = "configures field validity of numeric 20";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___20___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___21].name = "numeric_mdb_field___21";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___21].doc = "configures field size of numeric 21";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___21].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___21___valid].name = "numeric_mdb_field___21___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___21___valid].doc = "configures field validity of numeric 21";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___21___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___22].name = "numeric_mdb_field___22";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___22].doc = "configures field size of numeric 22";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___22].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___22___valid].name = "numeric_mdb_field___22___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___22___valid].doc = "configures field validity of numeric 22";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___22___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___23].name = "numeric_mdb_field___23";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___23].doc = "configures field size of numeric 23";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___23].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___23___valid].name = "numeric_mdb_field___23___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___23___valid].doc = "configures field validity of numeric 23";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___23___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___24].name = "numeric_mdb_field___24";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___24].doc = "configures field size of numeric 24";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___24].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___24___valid].name = "numeric_mdb_field___24___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___24___valid].doc = "configures field validity of numeric 24";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___24___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___25].name = "numeric_mdb_field___25";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___25].doc = "configures field size of numeric 25";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___25].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___25___valid].name = "numeric_mdb_field___25___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___25___valid].doc = "configures field validity of numeric 25";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___25___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___26].name = "numeric_mdb_field___26";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___26].doc = "configures field size of numeric 26";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___26].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___26___valid].name = "numeric_mdb_field___26___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___26___valid].doc = "configures field validity of numeric 26";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___26___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___27].name = "numeric_mdb_field___27";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___27].doc = "configures field size of numeric 27";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___27].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___27___valid].name = "numeric_mdb_field___27___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___27___valid].doc = "configures field validity of numeric 27";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___27___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___28].name = "numeric_mdb_field___28";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___28].doc = "configures field size of numeric 28";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___28].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___28___valid].name = "numeric_mdb_field___28___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___28___valid].doc = "configures field validity of numeric 28";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___28___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___29].name = "numeric_mdb_field___29";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___29].doc = "configures field size of numeric 29";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___29].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___29___valid].name = "numeric_mdb_field___29___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___29___valid].doc = "configures field validity of numeric 29";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___29___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___30].name = "numeric_mdb_field___30";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___30].doc = "configures field size of numeric 30";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___30].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___30___valid].name = "numeric_mdb_field___30___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___30___valid].doc = "configures field validity of numeric 30";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___30___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___31].name = "numeric_mdb_field___31";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___31].doc = "configures field size of numeric 31";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___31].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___31___valid].name = "numeric_mdb_field___31___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___31___valid].doc = "configures field validity of numeric 31";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___31___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___32].name = "numeric_mdb_field___32";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___32].doc = "configures field size of numeric 32";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___32].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___32___valid].name = "numeric_mdb_field___32___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___32___valid].doc = "configures field validity of numeric 32";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___32___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___33].name = "numeric_mdb_field___33";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___33].doc = "configures field size of numeric 33";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___33].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___33___valid].name = "numeric_mdb_field___33___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___33___valid].doc = "configures field validity of numeric 33";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___33___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___34].name = "numeric_mdb_field___34";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___34].doc = "configures field size of numeric 34";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___34].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___34___valid].name = "numeric_mdb_field___34___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___34___valid].doc = "configures field validity of numeric 34";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___34___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___35].name = "numeric_mdb_field___35";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___35].doc = "configures field size of numeric 35";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___35].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___35___valid].name = "numeric_mdb_field___35___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___35___valid].doc = "configures field validity of numeric 35";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___35___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___36].name = "numeric_mdb_field___36";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___36].doc = "configures field size of numeric 36";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___36].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___36___valid].name = "numeric_mdb_field___36___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___36___valid].doc = "configures field validity of numeric 36";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___36___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___37].name = "numeric_mdb_field___37";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___37].doc = "configures field size of numeric 37";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___37].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___37___valid].name = "numeric_mdb_field___37___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___37___valid].doc = "configures field validity of numeric 37";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___37___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___38].name = "numeric_mdb_field___38";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___38].doc = "configures field size of numeric 38";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___38].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___38___valid].name = "numeric_mdb_field___38___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___38___valid].doc = "configures field validity of numeric 38";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___38___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___39].name = "numeric_mdb_field___39";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___39].doc = "configures field size of numeric 39";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___39].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___39___valid].name = "numeric_mdb_field___39___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___39___valid].doc = "configures field validity of numeric 39";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___39___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___40].name = "numeric_mdb_field___40";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___40].doc = "configures field size of numeric 40";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___40].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___40___valid].name = "numeric_mdb_field___40___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___40___valid].doc = "configures field validity of numeric 40";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___40___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___41].name = "numeric_mdb_field___41";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___41].doc = "configures field size of numeric 41";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___41].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___41___valid].name = "numeric_mdb_field___41___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___41___valid].doc = "configures field validity of numeric 41";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___41___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___42].name = "numeric_mdb_field___42";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___42].doc = "configures field size of numeric 42";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___42].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___42___valid].name = "numeric_mdb_field___42___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___42___valid].doc = "configures field validity of numeric 42";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___42___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___43].name = "numeric_mdb_field___43";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___43].doc = "configures field size of numeric 43";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___43].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___43___valid].name = "numeric_mdb_field___43___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___43___valid].doc = "configures field validity of numeric 43";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___43___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___44].name = "numeric_mdb_field___44";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___44].doc = "configures field size of numeric 44";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___44].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___44___valid].name = "numeric_mdb_field___44___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___44___valid].doc = "configures field validity of numeric 44";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___44___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___45].name = "numeric_mdb_field___45";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___45].doc = "configures field size of numeric 45";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___45].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___45___valid].name = "numeric_mdb_field___45___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___45___valid].doc = "configures field validity of numeric 45";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___45___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___46].name = "numeric_mdb_field___46";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___46].doc = "configures field size of numeric 46";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___46].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___46___valid].name = "numeric_mdb_field___46___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___46___valid].doc = "configures field validity of numeric 46";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___46___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___47].name = "numeric_mdb_field___47";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___47].doc = "configures field size of numeric 47";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___47].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___47___valid].name = "numeric_mdb_field___47___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___47___valid].doc = "configures field validity of numeric 47";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___47___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___48].name = "numeric_mdb_field___48";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___48].doc = "configures field size of numeric 48";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___48].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___48___valid].name = "numeric_mdb_field___48___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___48___valid].doc = "configures field validity of numeric 48";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___48___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___49].name = "numeric_mdb_field___49";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___49].doc = "configures field size of numeric 49";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___49].flags |= DNXC_DATA_F_NUMERIC;
    }

    if (soc_is(unit, DNX2_DEVICE))
    {
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___49___valid].name = "numeric_mdb_field___49___valid";
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___49___valid].doc = "configures field validity of numeric 49";
        
        submodule_data->defines[dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___49___valid].flags |= DNXC_DATA_F_NUMERIC;
    }

    
    submodule_data->nof_tables = _dnx_data_dnx2_mdb_app_db_fields_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data dnx2_mdb_app_db fields tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_dnx2_mdb_app_db_fields_feature_get(
    int unit,
    dnx_data_dnx2_mdb_app_db_fields_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, feature);
}


uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BFD_IPV4_EXTRA_SIP___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_BASE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_ETH_RIF___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_COPY_INNER___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_GRE_GENEVE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_1_AH___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_1_AH___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_2_AH___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_2_3_AH___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_FHEI_Plus___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_MPLS_IFIT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___ETPP_ETPS_FORMATS___ETPS_SVTAG___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ARR_INDEX___IRPP_IN_LIF_FORMATS___IN_LIF_IPvX_3___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___BFER_2ND_PASS_TERMINATION_WO_BFIR___NEXT_LAYER_NETWORK_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC_1TAG_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_AC___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___DUAL_HOMING___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_Custom___STAT_OBJECT_ID___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP_SA_tunneling___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ARP___ETPS_ARP___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_BASE___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_BIER___ETPS_BIER_NON_MPLS_INITIAL_4BYTES___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI_Plus___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_FHEI___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_DUMMY_TABLE_NOT_TO_USE___ETPS_MPLS_PHP___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv2___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_ERSPAN___ETPS_ERSPANv3___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_AH___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___ESEM_NAME_SPACE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_IML___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_EVPN___ETPS_MPLS_1___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_GTP___ETPS_GTPv1U___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPFIX_PSAMP___ETPS_IPFIX_PSAMP___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_BFD_IPV4_EXTRA_SIP___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_COPY_INNER___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_DOUBLE_UDP_VXLAN___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_GRE_GENEVE___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_UDP___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE_ECN___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL_VXLAN_GPE___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV4_TUNNEL___ETPS_IPV4_TUNNEL___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GENEVE___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_GRE___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_RAW___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_Scale___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_UDP___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN_ECN___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_IPV6_TUNNEL___ETPS_IPV6_TUNNEL_VXLAN___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_L2TP___ETPS_L2TPv2___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_LAWFUL_INTERCEPT___ETPS_DATA_VAR_SIZE_DATA___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___REMARK_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_IFIT___ETPS_MPLS_IFIT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_AH___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1_TANDEM___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_1___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_1_AH___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_2_AH___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_3_AH___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2_TANDEM___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_2___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_MPLS_TUNNEL___ETPS_MPLS_PHP_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_NULL___ETPS_NULL___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OAM_REFLECTOR___ETPS_REFLECTOR_OAM___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION_NON_EM_BUSTER___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_STAT_PROTECTION___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_OUT_AC___ETPS_AC_TRIPLE_TAG___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PPPOE___ETPS_PPPOE___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_IOAM_FL___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___ESEM_NAME_SPACE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_AH___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_PWE___ETPS_MPLS_1___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RCH___ETPS_RCHv2___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR_L2_MC___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_REFLECTOR___ETPS_REFLECTOR___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RIF_BASIC___ETPS_ETH_RIF___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___ESEM_NAME_SPACE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_RSPAN___ETPS_RSPAN___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_first___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_EXT_second___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_DP___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SFLOW___ETPS_SFLOW_HDR_SAMP___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6_NO_SIDS___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_SRV6___ETPS_SRV6___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___EEDB_LL_EXTRA_DATA___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EEDB_TWAMP___ETPS_REFLECTOR_TWAMP___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_DUAL_HOMING_PER_INTERFACE_NAMESPACE_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_AC_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___REMARK_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO_VLANS___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___REMARK_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L2_FODO___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___REMARK_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ETPS_L3_FODO___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_DB___ZERO_PADDING___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_DEVICE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_AC_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___REMARK_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_FORWARD_DOMAIN_MAPPING_PER_INTERFACE_NAMESPACE_DB___ETPS_L2_FODO___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_AC_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___ETPS_DUAL_HOMING___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_BASED_SOURCE_ADDRESS_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___OUT_TM_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_PORT_SVTAG___ZERO_PADDING___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ESEM_TUNNEL_SVTAG___ETPS_SVTAG___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_SVTAG_ENABLE___ETPS_SVTAG___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1____get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1___);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___ETPS_TYPE_ARR_INDEX___EEDB_TYPE_VSD_ENABLE___ETPS_ETH_RIF___1______valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM3_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_IGNORE_MAC___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PER_PORT_MY_MAC___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___EXEM_PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___GTP_CLASSIFICATION___NEXT_LAYER_NETWORK_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_0_VLANS___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_1_VLANS___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___INNER_ETHERNET_VLAN_CLASSIFICATION_NETWORK_SCOPED_VLAN_2_VLANS___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_C_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_C_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_C_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_S_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_S_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_TCAM_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_AC_UNTAGGED_DB___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_C_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_S_VLAN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___IN_BR_E_VLAN_DB___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___EGRESS_LLVP_PROFILE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___ESEM_NAME_SPACE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV2_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___L2TPV3_DATA_MESSAGE_TT___NEXT_LAYER_NETWORK_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MAC_IN_MAC_LEARN_INFO___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MIM_TUNNEL_EM___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___MPLS_TERMINATION_SINGLE_LABEL_WITH_NETWORK_DOMAIN_DB___VLAN_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PEM_PER_PORT_DB___KEY___IN_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_C_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_C_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_DTC_S_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_S_TAG_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNMATCHED_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___PON_UNTAGGED_CLASSIFICATION___MAPPED_PP_PORT___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___TNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONPTC___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VIRT_TCAM___PRTTCAM_KEY_VP_PONZERO_PADDING___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VRF___NEXT_LAYER_NETWORK_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___VNI2VSI___NEXT_LAYER_NETWORK_DOMAIN___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___0_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___0", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___0);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___0___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___0___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___0___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___1_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___1", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___1);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___1___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___1___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___1___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___2_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___2", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___2);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___2___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___2___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___2___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___3_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___3", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___3);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___3___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___3___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___3___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___4_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___4", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___4);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___4___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___4___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___4___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___5_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___5", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___5);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___5___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___5___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___5___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___6_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___6", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___6);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___6___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___6___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___6___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___7_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___7", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___7);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___7___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___7___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___7___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___8_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___8", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___8);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___8___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___8___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___8___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___9_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___9", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___9);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___9___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___9___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___9___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___10_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___10", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___10);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___10___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___10___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___10___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___11_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___11", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___11);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___11___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___11___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___11___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___12_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___12", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___12);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___12___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___12___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___12___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___13_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___13", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___13);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___13___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___13___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___13___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___14_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___14", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___14);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___14___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___14___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___14___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___15_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___15", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___15);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___15___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___15___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___15___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___16_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___16", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___16);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___16___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___16___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___16___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___17_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___17", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___17);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___17___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___17___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___17___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___18_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___18", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___18);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___18___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___18___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___18___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___19_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___19", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___19);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___19___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___19___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___19___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___20_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___20", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___20);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___20___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___20___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___20___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___21_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___21", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___21);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___21___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___21___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___21___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___22_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___22", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___22);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___22___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___22___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___22___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___23_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___23", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___23);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___23___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___23___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___23___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___24_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___24", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___24);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___24___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___24___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___24___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___25_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___25", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___25);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___25___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___25___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___25___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___26_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___26", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___26);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___26___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___26___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___26___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___27_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___27", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___27);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___27___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___27___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___27___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___28_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___28", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___28);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___28___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___28___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___28___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___29_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___29", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___29);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___29___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___29___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___29___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___30_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___30", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___30);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___30___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___30___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___30___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___31_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___31", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___31);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___31___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___31___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___31___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___32_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___32", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___32);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___32___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___32___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___32___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___33_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___33", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___33);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___33___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___33___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___33___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___34_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___34", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___34);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___34___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___34___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___34___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___35_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___35", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___35);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___35___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___35___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___35___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___36_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___36", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___36);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___36___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___36___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___36___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___37_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___37", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___37);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___37___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___37___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___37___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___38_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___38", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___38);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___38___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___38___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___38___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___39_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___39", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___39);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___39___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___39___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___39___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___40_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___40", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___40);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___40___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___40___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___40___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___41_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___41", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___41);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___41___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___41___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___41___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___42_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___42", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___42);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___42___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___42___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___42___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___43_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___43", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___43);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___43___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___43___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___43___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___44_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___44", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___44);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___44___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___44___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___44___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___45_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___45", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___45);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___45___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___45___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___45___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___46_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___46", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___46);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___46___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___46___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___46___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___47_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___47", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___47);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___47___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___47___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___47___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___48_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___48", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___48);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___48___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___48___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___48___valid);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___49_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___49", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___49);
}

uint32
dnx_data_dnx2_mdb_app_db_fields_numeric_mdb_field___49___valid_get(
    int unit)
{
    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_get(unit, "numeric_mdb_field___49___valid", "DNX2");
    }
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_dnx2_mdb_app_db, dnx_data_dnx2_mdb_app_db_submodule_fields, dnx_data_dnx2_mdb_app_db_fields_define_numeric_mdb_field___49___valid);
}







shr_error_e
dnx_data_dnx2_mdb_app_db_init(
    int unit,
    dnxc_data_module_t *module_data)
{
    SHR_FUNC_INIT_VARS(unit);

    
    module_data->name = "dnx2_mdb_app_db";
    module_data->nof_submodules = _dnx_data_dnx2_mdb_app_db_submodule_nof;
    DNXC_DATA_ALLOC(module_data->submodules, dnxc_data_submodule_t, module_data->nof_submodules, "_dnxc_data dnx2_mdb_app_db submodules");

    
    SHR_IF_ERR_EXIT(dnx_data_dnx2_mdb_app_db_fields_init(unit, &module_data->submodules[dnx_data_dnx2_mdb_app_db_submodule_fields]));
    
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_jr2_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_jr2_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(jr2_b0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_jr2_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(jr2_b0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_j2c_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_j2c_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_q2a_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_q2a_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(q2a_b0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_q2a_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(q2a_b0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_j2p_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_j2p_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_j2p_a2(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_dnx2_mdb_app_db_attach(unit));
    }
    else

#endif 
#ifdef BCM_DNX2_SUPPORT

    if (dnxc_data_mgmt_is_j2x_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_dnx2_mdb_app_db_attach(unit));
        SHR_IF_ERR_EXIT(j2x_a0_data_dnx2_mdb_app_db_attach(unit));
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


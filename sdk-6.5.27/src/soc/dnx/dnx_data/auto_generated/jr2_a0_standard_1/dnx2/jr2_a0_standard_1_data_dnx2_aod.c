
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

#include <soc/dnx/dnx_data/auto_generated/dnx2/dnx_data_internal_dnx2_aod.h>









static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER___image_set(
    int unit)
{
    dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER___image_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_ERPP_FWD_CONTEXT_FILTER___image;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "ERPP_FWD_CONTEXT_FILTER___image", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "standard_1";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER___image_t, (1 + 1  ), "data of dnx_data_dnx2_aod_tables_table_ERPP_FWD_CONTEXT_FILTER___image");

    
    default_data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER___image_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->image = "standard_1";
    
    data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER___image_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_set(
    int unit)
{
    int index_index;
    dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_ERPP_FWD_CONTEXT_FILTER;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "ERPP_FWD_CONTEXT_FILTER", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 64;
    table->info_get.key_size[0] = 64;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "default";
    table->values[2].default_val = "none";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    table->values[6].default_val = "0";
    table->values[7].default_val = "0";
    table->values[8].default_val = "0";
    table->values[9].default_val = "0";
    table->values[10].default_val = "0";
    table->values[11].default_val = "0";
    table->values[12].default_val = "0";
    table->values[13].default_val = "0";
    table->values[14].default_val = "0";
    table->values[15].default_val = "0";
    table->values[16].default_val = "0";
    table->values[17].default_val = "0";
    table->values[18].default_val = "0";
    table->values[19].default_val = "0";
    table->values[20].default_val = "0";
    table->values[21].default_val = "0";
    table->values[22].default_val = "0";
    table->values[23].default_val = "0";
    table->values[24].default_val = "0";
    table->values[25].default_val = "0";
    table->values[26].default_val = "0";
    table->values[27].default_val = "0";
    table->values[28].default_val = "0";
    table->values[29].default_val = "0";
    table->values[30].default_val = "0";
    table->values[31].default_val = "0";
    table->values[32].default_val = "0";
    table->values[33].default_val = "0";
    table->values[34].default_val = "0";
    table->values[35].default_val = "0";
    table->values[36].default_val = "0";
    table->values[37].default_val = "0";
    table->values[38].default_val = "0";
    table->values[39].default_val = "0";
    table->values[40].default_val = "0";
    table->values[41].default_val = "0";
    table->values[42].default_val = "0";
    table->values[43].default_val = "0";
    table->values[44].default_val = "0";
    table->values[45].default_val = "0";
    table->values[46].default_val = "0";
    table->values[47].default_val = "0";
    table->values[48].default_val = "0";
    table->values[49].default_val = "0";
    table->values[50].default_val = "0";
    table->values[51].default_val = "0";
    table->values[52].default_val = "0";
    table->values[53].default_val = "0";
    table->values[54].default_val = "0";
    table->values[55].default_val = "0";
    table->values[56].default_val = "0";
    table->values[57].default_val = "0";
    table->values[58].default_val = "0";
    table->values[59].default_val = "0";
    table->values[60].default_val = "0";
    table->values[61].default_val = "0";
    table->values[62].default_val = "0";
    table->values[63].default_val = "0";
    table->values[64].default_val = "0";
    table->values[65].default_val = "0";
    table->values[66].default_val = "0";
    table->values[67].default_val = "0";
    table->values[68].default_val = "0";
    table->values[69].default_val = "0";
    table->values[70].default_val = "0";
    table->values[71].default_val = "0";
    table->values[72].default_val = "0";
    table->values[73].default_val = "0";
    table->values[74].default_val = "0";
    table->values[75].default_val = "0";
    table->values[76].default_val = "0";
    table->values[77].default_val = "0";
    table->values[78].default_val = "0";
    table->values[79].default_val = "0";
    table->values[80].default_val = "0";
    table->values[81].default_val = "0";
    table->values[82].default_val = "0";
    table->values[83].default_val = "0";
    table->values[84].default_val = "0";
    table->values[85].default_val = "0";
    table->values[86].default_val = "0";
    table->values[87].default_val = "0";
    table->values[88].default_val = "0";
    table->values[89].default_val = "0";
    table->values[90].default_val = "0";
    table->values[91].default_val = "0";
    table->values[92].default_val = "0";
    table->values[93].default_val = "0";
    table->values[94].default_val = "0";
    table->values[95].default_val = "0";
    table->values[96].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_dnx2_aod_tables_table_ERPP_FWD_CONTEXT_FILTER");

    
    default_data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->valid = 0;
    default_data->doc = "default";
    default_data->Egress_FWD_Code = "none";
    default_data->Egress_FWD_Code_mask = 0;
    default_data->Egress_FWD_Code_valid = 0;
    default_data->DSS_Stacking = 0;
    default_data->DSS_Stacking_valid = 0;
    default_data->Exclude_Source = 0;
    default_data->Exclude_Source_valid = 0;
    default_data->GLEM_PP_or_NON_PP = 0;
    default_data->GLEM_PP_or_NON_PP_valid = 0;
    default_data->Hairpin_or_Same_Interface = 0;
    default_data->Hairpin_or_Same_Interface_valid = 0;
    default_data->IPv4_Filters = 0;
    default_data->IPv4_Filters_valid = 0;
    default_data->IPv4_Filters_Dip_Zero = 0;
    default_data->IPv4_Filters_Dip_Zero_valid = 0;
    default_data->IPv4_Filters_Header_Checksum = 0;
    default_data->IPv4_Filters_Header_Checksum_valid = 0;
    default_data->IPv4_Filters_Header_Length = 0;
    default_data->IPv4_Filters_Header_Length_valid = 0;
    default_data->IPv4_Filters_Options = 0;
    default_data->IPv4_Filters_Options_valid = 0;
    default_data->IPv4_Filters_Sip_Equal_Dip = 0;
    default_data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
    default_data->IPv4_Filters_Sip_Multicast = 0;
    default_data->IPv4_Filters_Sip_Multicast_valid = 0;
    default_data->IPv4_Filters_Total_Length = 0;
    default_data->IPv4_Filters_Total_Length_valid = 0;
    default_data->IPv4_Filters_Version = 0;
    default_data->IPv4_Filters_Version_valid = 0;
    default_data->IPv6_Filters = 0;
    default_data->IPv6_Filters_valid = 0;
    default_data->IPv6_Filters_Dip_Is_All = 0;
    default_data->IPv6_Filters_Dip_Is_All_valid = 0;
    default_data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
    default_data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
    default_data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
    default_data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
    default_data->IPv6_Filters_Link_Local_Dst = 0;
    default_data->IPv6_Filters_Link_Local_Dst_valid = 0;
    default_data->IPv6_Filters_Link_Local_Src = 0;
    default_data->IPv6_Filters_Link_Local_Src_valid = 0;
    default_data->IPv6_Filters_Loopback = 0;
    default_data->IPv6_Filters_Loopback_valid = 0;
    default_data->IPv6_Filters_Mc_Dst = 0;
    default_data->IPv6_Filters_Mc_Dst_valid = 0;
    default_data->IPv6_Filters_Next_Header_Is_Zeros = 0;
    default_data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
    default_data->IPv6_Filters_Sip_Is_All = 0;
    default_data->IPv6_Filters_Sip_Is_All_valid = 0;
    default_data->IPv6_Filters_Sip_Is_Mc = 0;
    default_data->IPv6_Filters_Sip_Is_Mc_valid = 0;
    default_data->IPv6_Filters_Site_Local_Dst = 0;
    default_data->IPv6_Filters_Site_Local_Dst_valid = 0;
    default_data->IPv6_Filters_Site_Local_Src = 0;
    default_data->IPv6_Filters_Site_Local_Src_valid = 0;
    default_data->IPv6_Filters_Version = 0;
    default_data->IPv6_Filters_Version_valid = 0;
    default_data->Invalid_OTM = 0;
    default_data->Invalid_OTM_valid = 0;
    default_data->L4_Filters = 0;
    default_data->L4_Filters_valid = 0;
    default_data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
    default_data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
    default_data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
    default_data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
    default_data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
    default_data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
    default_data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
    default_data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
    default_data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
    default_data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
    default_data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
    default_data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
    default_data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
    default_data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
    default_data->LAG_Multicast = 0;
    default_data->LAG_Multicast_valid = 0;
    default_data->MTU = 0;
    default_data->MTU_valid = 0;
    default_data->RQP_Discard = 0;
    default_data->RQP_Discard_valid = 0;
    default_data->Split_Horizon = 0;
    default_data->Split_Horizon_valid = 0;
    default_data->TDM_Indication = 0;
    default_data->TDM_Indication_valid = 0;
    default_data->TTL_Scoping = 0;
    default_data->TTL_Scoping_valid = 0;
    default_data->TTL_eq_0 = 0;
    default_data->TTL_eq_0_valid = 0;
    default_data->TTL_eq_1 = 0;
    default_data->TTL_eq_1_valid = 0;
    default_data->Unacceptable_Frame_Types = 0;
    default_data->Unacceptable_Frame_Types_valid = 0;
    default_data->Unknown_DA = 0;
    default_data->Unknown_DA_valid = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "ETHERNET";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 0;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 0;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 0;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 1;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 1;
        data->Unknown_DA_valid = 1;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 1;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 1;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 1;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 1;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 1;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 1;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 1;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 1;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 1;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 1;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 1;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 1;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 1;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 1;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 1;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 1;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 1;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 1;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "BIER_MPLS_BFR";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 0;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 0;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 0;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "BIER_NON_MPLS_BFR";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 0;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 0;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 0;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "INGRESS_TRAPPED_JR1_LEGACY";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 0;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 0;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 0;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 0;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 0;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 0;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 0;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 0;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "Stacking_Port";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 0;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 0;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 0;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 0;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 0;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 0;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 0;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 1;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 0;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 0;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 0;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_HBH_PT_MidPoint";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 0;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 0;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 0;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "MPLS";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 0;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 1;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 1;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 1;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 1;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 1;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 1;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 1;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 0;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 1;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 1;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 1;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 1;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 1;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 1;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 1;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 1;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 1;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 1;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 1;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 1;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 1;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6__HBH_PT_MidPoint_UC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->DSS_Stacking = 1;
        data->DSS_Stacking_valid = 1;
        data->Exclude_Source = 0;
        data->Exclude_Source_valid = 1;
        data->GLEM_PP_or_NON_PP = 1;
        data->GLEM_PP_or_NON_PP_valid = 1;
        data->Hairpin_or_Same_Interface = 1;
        data->Hairpin_or_Same_Interface_valid = 1;
        data->IPv4_Filters = 0;
        data->IPv4_Filters_valid = 1;
        data->IPv4_Filters_Dip_Zero = 0;
        data->IPv4_Filters_Dip_Zero_valid = 0;
        data->IPv4_Filters_Header_Checksum = 0;
        data->IPv4_Filters_Header_Checksum_valid = 0;
        data->IPv4_Filters_Header_Length = 0;
        data->IPv4_Filters_Header_Length_valid = 0;
        data->IPv4_Filters_Options = 0;
        data->IPv4_Filters_Options_valid = 0;
        data->IPv4_Filters_Sip_Equal_Dip = 0;
        data->IPv4_Filters_Sip_Equal_Dip_valid = 0;
        data->IPv4_Filters_Sip_Multicast = 0;
        data->IPv4_Filters_Sip_Multicast_valid = 0;
        data->IPv4_Filters_Total_Length = 0;
        data->IPv4_Filters_Total_Length_valid = 0;
        data->IPv4_Filters_Version = 0;
        data->IPv4_Filters_Version_valid = 0;
        data->IPv6_Filters = 1;
        data->IPv6_Filters_valid = 1;
        data->IPv6_Filters_Dip_Is_All = 0;
        data->IPv6_Filters_Dip_Is_All_valid = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst = 0;
        data->IPv6_Filters_Ipv4_Cmp_Dst_valid = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst = 0;
        data->IPv6_Filters_Ipv4_Mapped_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Dst = 0;
        data->IPv6_Filters_Link_Local_Dst_valid = 0;
        data->IPv6_Filters_Link_Local_Src = 0;
        data->IPv6_Filters_Link_Local_Src_valid = 0;
        data->IPv6_Filters_Loopback = 0;
        data->IPv6_Filters_Loopback_valid = 0;
        data->IPv6_Filters_Mc_Dst = 0;
        data->IPv6_Filters_Mc_Dst_valid = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros = 0;
        data->IPv6_Filters_Next_Header_Is_Zeros_valid = 0;
        data->IPv6_Filters_Sip_Is_All = 0;
        data->IPv6_Filters_Sip_Is_All_valid = 0;
        data->IPv6_Filters_Sip_Is_Mc = 0;
        data->IPv6_Filters_Sip_Is_Mc_valid = 0;
        data->IPv6_Filters_Site_Local_Dst = 0;
        data->IPv6_Filters_Site_Local_Dst_valid = 0;
        data->IPv6_Filters_Site_Local_Src = 0;
        data->IPv6_Filters_Site_Local_Src_valid = 0;
        data->IPv6_Filters_Version = 0;
        data->IPv6_Filters_Version_valid = 0;
        data->Invalid_OTM = 1;
        data->Invalid_OTM_valid = 1;
        data->L4_Filters = 1;
        data->L4_Filters_valid = 1;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr = 0;
        data->L4_Filters_Tcp_Fragment_Incomplete_Hdr_valid = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8 = 0;
        data->L4_Filters_Tcp_Fragment_Offset_Less_Than_8_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Set_valid = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero = 0;
        data->L4_Filters_Tcp_Seq_Num_Zero_Flags_Zero_valid = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Tcp_Src_Port_Equals_Dst_Port_valid = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set = 0;
        data->L4_Filters_Tcp_Syn_And_Fin_Are_Set_valid = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port = 0;
        data->L4_Filters_Udp_Src_Port_Equals_Dst_Port_valid = 0;
        data->LAG_Multicast = 1;
        data->LAG_Multicast_valid = 1;
        data->MTU = 0;
        data->MTU_valid = 1;
        data->RQP_Discard = 1;
        data->RQP_Discard_valid = 1;
        data->Split_Horizon = 0;
        data->Split_Horizon_valid = 1;
        data->TDM_Indication = 1;
        data->TDM_Indication_valid = 1;
        data->TTL_Scoping = 0;
        data->TTL_Scoping_valid = 1;
        data->TTL_eq_0 = 1;
        data->TTL_eq_0_valid = 1;
        data->TTL_eq_1 = 1;
        data->TTL_eq_1_valid = 1;
        data->Unacceptable_Frame_Types = 0;
        data->Unacceptable_Frame_Types_valid = 1;
        data->Unknown_DA = 0;
        data->Unknown_DA_valid = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE___image_set(
    int unit)
{
    dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE___image_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_EGRESS_PER_FORWARD_CODE___image;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "EGRESS_PER_FORWARD_CODE___image", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "standard_1";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE___image_t, (1 + 1  ), "data of dnx_data_dnx2_aod_tables_table_EGRESS_PER_FORWARD_CODE___image");

    
    default_data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE___image_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->image = "standard_1";
    
    data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE___image_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_set(
    int unit)
{
    int index_index;
    int soc_value_index;
    dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_EGRESS_PER_FORWARD_CODE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "EGRESS_PER_FORWARD_CODE", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 64;
    table->info_get.key_size[0] = 64;
    table->keys[1].size = 2;
    table->info_get.key_size[1] = 2;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "default";
    table->values[2].default_val = "none";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    table->values[6].default_val = "0";
    table->values[7].default_val = "0";
    table->values[8].default_val = "0";
    table->values[9].default_val = "0";
    table->values[10].default_val = "0";
    table->values[11].default_val = "0";
    table->values[12].default_val = "0";
    table->values[13].default_val = "0";
    table->values[14].default_val = "0";
    table->values[15].default_val = "0";
    table->values[16].default_val = "0";
    table->values[17].default_val = "0";
    table->values[18].default_val = "0";
    table->values[19].default_val = "0";
    table->values[20].default_val = "0";
    table->values[21].default_val = "0";
    table->values[22].default_val = "0";
    table->values[23].default_val = "0";
    table->values[24].default_val = "0";
    table->values[25].default_val = "0";
    table->values[26].default_val = "0";
    table->values[27].default_val = "0";
    table->values[28].default_val = "0";
    table->values[29].default_val = "0";
    table->values[30].default_val = "0";
    table->values[31].default_val = "0";
    table->values[32].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_dnx2_aod_tables_table_EGRESS_PER_FORWARD_CODE");

    
    default_data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->valid = 0;
    default_data->doc = "default";
    default_data->Egress_FWD_Code = "none";
    default_data->Egress_FWD_Code_mask = 0;
    default_data->Egress_FWD_Code_valid = 0;
    default_data->Acceptable_Frame_Type_Enable = 0;
    default_data->Acceptable_Frame_Type_Enable_valid = 0;
    default_data->FWD_Context_is_PP_Enable = 0;
    default_data->FWD_Context_is_PP_Enable_valid = 0;
    default_data->Forward_Code_IPv4_or_IPv6 = 0;
    default_data->Forward_Code_IPv4_or_IPv6_valid = 0;
    default_data->Learn_Enable = 0;
    default_data->Learn_Enable_valid = 0;
    default_data->Protocol_Ethernet_Enable = 0;
    default_data->Protocol_Ethernet_Enable_valid = 0;
    default_data->Protocol_IPv4_MC_Enable = 0;
    default_data->Protocol_IPv4_MC_Enable_valid = 0;
    default_data->Protocol_IPv4_UC_Enable = 0;
    default_data->Protocol_IPv4_UC_Enable_valid = 0;
    default_data->Protocol_IPv6_MC_Enable = 0;
    default_data->Protocol_IPv6_MC_Enable_valid = 0;
    default_data->Protocol_IPv6_UC_Enable = 0;
    default_data->Protocol_IPv6_UC_Enable_valid = 0;
    default_data->Protocol_MPLS_Enable = 0;
    default_data->Protocol_MPLS_Enable_valid = 0;
    default_data->STP_Enable = 0;
    default_data->STP_Enable_valid = 0;
    default_data->Split_Horizon_Enable = 0;
    default_data->Split_Horizon_Enable_valid = 0;
    default_data->Termination_Enable = 0;
    default_data->Termination_Enable_valid = 0;
    default_data->Vlan_Membership_Enable = 0;
    default_data->Vlan_Membership_Enable_valid = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        for (soc_value_index = 0; soc_value_index < table->keys[1].size; soc_value_index++)
        {
            data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, soc_value_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }
    
    if (0 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "ETHERNET";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 1;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 1;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 1;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 1;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 1;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 1;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (1 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (2 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 1;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (3 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 1;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (4 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 1;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 1;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (5 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 1;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 1;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (6 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "BIER_MPLS_BFR";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (7 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "BIER_NON_MPLS_BFR";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (8 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "INGRESS_TRAPPED_JR1_LEGACY";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 0;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (9 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "RAW_PROCESSING";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (10 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "CPU_PORT";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (11 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "ERPP_TRAPPED";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (12 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "Stacking_Port";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (13 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (14 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_PSP";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (15 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_PSP_Extended_cut";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (16 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 0;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (17 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_HBH_PT_MidPoint";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (18 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "MPLS_INJECTED_FROM_OAMP";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 1;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (19 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "DO_NOT_EDIT";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (20 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "MPLS";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 1;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (21 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 21, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "PPP";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (22 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 22, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 1;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (23 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 23, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 1;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (24 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 24, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 1;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 1;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (25 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 25, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 1;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 1;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (26 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 26, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6__HBH_PT_MidPoint_UC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 1;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 1;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (27 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 27, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6__HBH_PT_MidPoint_UC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 1;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 1;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (28 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 28, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "EXT_ENCAP_DO_NOTHING";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (29 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 29, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "IPFIX_RX_FWD_CODE";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (30 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 30, 1);
        data->valid = 1;
        data->Egress_FWD_Code = "FWD_CODE_BUG_CODE";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (0 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "ETHERNET";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 1;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 1;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 1;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 1;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 1;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 1;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (1 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (2 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 1;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (3 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 1;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (4 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 1;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 1;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (5 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R0";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 1;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 1;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (6 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "BIER_MPLS_BFR";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (7 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "BIER_NON_MPLS_BFR";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (8 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "INGRESS_TRAPPED_JR1_LEGACY";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 0;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (9 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "RAW_PROCESSING";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (10 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "CPU_PORT";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (11 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "ERPP_TRAPPED";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (12 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "Stacking_Port";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (13 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (14 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_PSP";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (15 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (16 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_HBH_PT_MidPoint";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (17 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "MPLS_INJECTED_FROM_OAMP";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (18 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "DO_NOT_EDIT";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (19 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "MPLS";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 1;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (20 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "PPP";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (21 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 21, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 1;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (22 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 22, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 1;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (23 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 23, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 1;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 1;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (24 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 24, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R1";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 1;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 1;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (25 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 25, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "IPFIX_RX_FWD_CODE";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 0;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }
    if (26 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 26, 0);
        data->valid = 1;
        data->Egress_FWD_Code = "FWD_CODE_BUG_CODE";
        data->Egress_FWD_Code_mask = 0;
        data->Egress_FWD_Code_valid = 1;
        data->Acceptable_Frame_Type_Enable = 0;
        data->Acceptable_Frame_Type_Enable_valid = 1;
        data->FWD_Context_is_PP_Enable = 1;
        data->FWD_Context_is_PP_Enable_valid = 1;
        data->Forward_Code_IPv4_or_IPv6 = 0;
        data->Forward_Code_IPv4_or_IPv6_valid = 1;
        data->Learn_Enable = 0;
        data->Learn_Enable_valid = 1;
        data->Protocol_Ethernet_Enable = 0;
        data->Protocol_Ethernet_Enable_valid = 1;
        data->Protocol_IPv4_MC_Enable = 0;
        data->Protocol_IPv4_MC_Enable_valid = 1;
        data->Protocol_IPv4_UC_Enable = 0;
        data->Protocol_IPv4_UC_Enable_valid = 1;
        data->Protocol_IPv6_MC_Enable = 0;
        data->Protocol_IPv6_MC_Enable_valid = 1;
        data->Protocol_IPv6_UC_Enable = 0;
        data->Protocol_IPv6_UC_Enable_valid = 1;
        data->Protocol_MPLS_Enable = 0;
        data->Protocol_MPLS_Enable_valid = 1;
        data->STP_Enable = 0;
        data->STP_Enable_valid = 1;
        data->Split_Horizon_Enable = 0;
        data->Split_Horizon_Enable_valid = 1;
        data->Termination_Enable = 1;
        data->Termination_Enable_valid = 1;
        data->Vlan_Membership_Enable = 0;
        data->Vlan_Membership_Enable_valid = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION___image_set(
    int unit)
{
    dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION___image_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_ERPP_FORWARD_CODE_SELECTION___image;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "ERPP_FORWARD_CODE_SELECTION___image", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "standard_1";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION___image_t, (1 + 1  ), "data of dnx_data_dnx2_aod_tables_table_ERPP_FORWARD_CODE_SELECTION___image");

    
    default_data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION___image_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->image = "standard_1";
    
    data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION___image_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_set(
    int unit)
{
    int index_index;
    int soc_value_index;
    dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_ERPP_FORWARD_CODE_SELECTION;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "ERPP_FORWARD_CODE_SELECTION", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 64;
    table->info_get.key_size[0] = 64;
    table->keys[1].size = 2;
    table->info_get.key_size[1] = 2;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "default";
    table->values[2].default_val = "0";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    table->values[6].default_val = "0";
    table->values[7].default_val = "0";
    table->values[8].default_val = "none";
    table->values[9].default_val = "0";
    table->values[10].default_val = "0";
    table->values[11].default_val = "none";
    table->values[12].default_val = "0";
    table->values[13].default_val = "0";
    table->values[14].default_val = "0";
    table->values[15].default_val = "0";
    table->values[16].default_val = "0";
    table->values[17].default_val = "0";
    table->values[18].default_val = "0";
    table->values[19].default_val = "0";
    table->values[20].default_val = "0";
    table->values[21].default_val = "0";
    table->values[22].default_val = "0";
    table->values[23].default_val = "0";
    table->values[24].default_val = "0";
    table->values[25].default_val = "0";
    table->values[26].default_val = "none";
    table->values[27].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_dnx2_aod_tables_table_ERPP_FORWARD_CODE_SELECTION");

    
    default_data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->valid = 0;
    default_data->doc = "default";
    default_data->FAI = 0;
    default_data->FAI_mask = 0;
    default_data->FAI_valid = 0;
    default_data->FWD_Layer_Qualifier = 0;
    default_data->FWD_Layer_Qualifier_mask = 0;
    default_data->FWD_Layer_Qualifier_valid = 0;
    default_data->FWD_Layer_Type = "none";
    default_data->FWD_Layer_Type_mask = 0;
    default_data->FWD_Layer_Type_valid = 0;
    default_data->FWD_code_port_profile = "none";
    default_data->FWD_code_port_profile_mask = 0;
    default_data->FWD_code_port_profile_valid = 0;
    default_data->TM_Action_Type = 0;
    default_data->TM_Action_Type_mask = 0;
    default_data->TM_Action_Type_valid = 0;
    default_data->ingress_trapped = 0;
    default_data->ingress_trapped_mask = 0;
    default_data->ingress_trapped_valid = 0;
    default_data->is_Applet = 0;
    default_data->is_Applet_mask = 0;
    default_data->is_Applet_valid = 0;
    default_data->is_TDM = 0;
    default_data->is_TDM_mask = 0;
    default_data->is_TDM_valid = 0;
    default_data->Egress_FWD_Code = "none";
    default_data->Egress_FWD_Code_valid = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        for (soc_value_index = 0; soc_value_index < table->keys[1].size; soc_value_index++)
        {
            data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, soc_value_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }
    
    if (38 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 38, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "FWD_CODE_BUG_CODE";
        data->Egress_FWD_Code_valid = 1;
    }
    if (20 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "TDM_BS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TDM_BS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (0 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "RCH";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "EXT_ENCAP_DO_NOTHING";
        data->Egress_FWD_Code_valid = 1;
    }
    if (21 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 21, 1);
        data->valid = 1;
        data->FAI = 8;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 6338;
        data->FWD_Layer_Qualifier_mask = 57345;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6__HBH_PT_MidPoint_UC_R1";
        data->Egress_FWD_Code_valid = 1;
    }
    if (22 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 22, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 6338;
        data->FWD_Layer_Qualifier_mask = 57345;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6__HBH_PT_MidPoint_UC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (23 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 23, 1);
        data->valid = 1;
        data->FAI = 10;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R1";
        data->Egress_FWD_Code_valid = 1;
    }
    if (24 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 24, 1);
        data->valid = 1;
        data->FAI = 8;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R1";
        data->Egress_FWD_Code_valid = 1;
    }
    if (12 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 1);
        data->valid = 1;
        data->FAI = 10;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv4";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R1";
        data->Egress_FWD_Code_valid = 1;
    }
    if (13 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 1);
        data->valid = 1;
        data->FAI = 8;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv4";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R1";
        data->Egress_FWD_Code_valid = 1;
    }
    if (25 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 25, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "PPP";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "PPP";
        data->Egress_FWD_Code_valid = 1;
    }
    if (26 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 26, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "MPLS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MPLS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (14 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 1);
        data->valid = 1;
        data->FAI = 5;
        data->FAI_mask = 2;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv4";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "DO_NOT_EDIT";
        data->Egress_FWD_Code_valid = 1;
    }
    if (15 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 1);
        data->valid = 1;
        data->FAI = 5;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "MPLS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "DO_NOT_EDIT";
        data->Egress_FWD_Code_valid = 1;
    }
    if (16 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 1);
        data->valid = 1;
        data->FAI = 5;
        data->FAI_mask = 2;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "DO_NOT_EDIT";
        data->Egress_FWD_Code_valid = 1;
    }
    if (17 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 1);
        data->valid = 1;
        data->FAI = 5;
        data->FAI_mask = 10;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "MPLS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MPLS_INJECTED_FROM_OAMP";
        data->Egress_FWD_Code_valid = 1;
    }
    if (6 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 1;
        data->is_TDM_mask = 0;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TDM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (27 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 27, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 1;
        data->FWD_Layer_Qualifier_mask = 65520;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "SRv6_Endpoint";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_HBH_PT_MidPoint";
        data->Egress_FWD_Code_valid = 1;
    }
    if (28 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 28, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "INITIALIZATION";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 0;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (29 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 29, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "SRV6_RCH_USP_PSP_AND_PSP_EXT";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_PSP_Extended_cut";
        data->Egress_FWD_Code_valid = 1;
    }
    if (30 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 30, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 8;
        data->FWD_Layer_Qualifier_mask = 65520;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "SRv6_Endpoint";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_PSP";
        data->Egress_FWD_Code_valid = 1;
    }
    if (31 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 31, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65520;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "SRv6_Endpoint";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint";
        data->Egress_FWD_Code_valid = 1;
    }
    if (8 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "STACKING_Port";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "Stacking_Port";
        data->Egress_FWD_Code_valid = 1;
    }
    if (4 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "CPU_Port";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "CPU_PORT";
        data->Egress_FWD_Code_valid = 1;
    }
    if (5 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "RAW_Processing";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "RAW_PROCESSING";
        data->Egress_FWD_Code_valid = 1;
    }
    if (11 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 1;
        data->ingress_trapped_mask = 0;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "INGRESS_TRAPPED_JR1_LEGACY";
        data->Egress_FWD_Code_valid = 1;
    }
    if (32 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 32, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "BIER_NON_MPLS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "BIER_NON_MPLS_BFR";
        data->Egress_FWD_Code_valid = 1;
    }
    if (33 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 33, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IN_BIER_BASE_EG_BIER_MPLS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "BIER_MPLS_BFR";
        data->Egress_FWD_Code_valid = 1;
    }
    if (34 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 34, 1);
        data->valid = 1;
        data->FAI = 2;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (35 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 35, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (18 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 1);
        data->valid = 1;
        data->FAI = 2;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv4";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (19 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv4";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (9 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 2;
        data->TM_Action_Type_mask = 0;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (10 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 3;
        data->TM_Action_Type_mask = 0;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (36 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 36, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPvX";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (37 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 37, 1);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "ETHERNET";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "ETHERNET";
        data->Egress_FWD_Code_valid = 1;
    }
    if (7 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->valid = 1;
        data->FAI = 5;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MPLS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (0 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 1;
        data->is_TDM_mask = 0;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TDM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (8 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->valid = 1;
        data->FAI = 15;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "INITIALIZATION";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (1 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "CPU_Port";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "CPU_PORT";
        data->Egress_FWD_Code_valid = 1;
    }
    if (2 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "RAW_Processing";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "RAW_PROCESSING";
        data->Egress_FWD_Code_valid = 1;
    }
    if (6 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->valid = 1;
        data->FAI = 7;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "INGRESS_TRAPPED_JR1_LEGACY";
        data->Egress_FWD_Code_valid = 1;
    }
    if (9 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->valid = 1;
        data->FAI = 4;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (10 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->valid = 1;
        data->FAI = 3;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (11 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->valid = 1;
        data->FAI = 2;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (12 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->valid = 1;
        data->FAI = 1;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (4 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 1;
        data->TM_Action_Type_mask = 0;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (5 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 2;
        data->TM_Action_Type_mask = 0;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (13 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->valid = 1;
        data->FAI = 0;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "ETHERNET";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "ETHERNET";
        data->Egress_FWD_Code_valid = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION___image_set(
    int unit)
{
    dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION___image_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_ETPP_FORWARD_CODE_SELECTION___image;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "ETPP_FORWARD_CODE_SELECTION___image", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "standard_1";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION___image_t, (1 + 1  ), "data of dnx_data_dnx2_aod_tables_table_ETPP_FORWARD_CODE_SELECTION___image");

    
    default_data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION___image_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->image = "standard_1";
    
    data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION___image_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_set(
    int unit)
{
    int index_index;
    int soc_value_index;
    dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_ETPP_FORWARD_CODE_SELECTION;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "ETPP_FORWARD_CODE_SELECTION", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 64;
    table->info_get.key_size[0] = 64;
    table->keys[1].size = 2;
    table->info_get.key_size[1] = 2;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "default";
    table->values[2].default_val = "none";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    table->values[6].default_val = "0";
    table->values[7].default_val = "0";
    table->values[8].default_val = "0";
    table->values[9].default_val = "0";
    table->values[10].default_val = "0";
    table->values[11].default_val = "none";
    table->values[12].default_val = "0";
    table->values[13].default_val = "0";
    table->values[14].default_val = "none";
    table->values[15].default_val = "0";
    table->values[16].default_val = "0";
    table->values[17].default_val = "0";
    table->values[18].default_val = "0";
    table->values[19].default_val = "0";
    table->values[20].default_val = "0";
    table->values[21].default_val = "0";
    table->values[22].default_val = "0";
    table->values[23].default_val = "0";
    table->values[24].default_val = "0";
    table->values[25].default_val = "0";
    table->values[26].default_val = "0";
    table->values[27].default_val = "0";
    table->values[28].default_val = "0";
    table->values[29].default_val = "none";
    table->values[30].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_dnx2_aod_tables_table_ETPP_FORWARD_CODE_SELECTION");

    
    default_data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->valid = 0;
    default_data->doc = "default";
    default_data->ACE_Value = "none";
    default_data->ACE_Value_mask = 0;
    default_data->ACE_Value_valid = 0;
    default_data->FAI = 0;
    default_data->FAI_mask = 0;
    default_data->FAI_valid = 0;
    default_data->FWD_Layer_Qualifier = 0;
    default_data->FWD_Layer_Qualifier_mask = 0;
    default_data->FWD_Layer_Qualifier_valid = 0;
    default_data->FWD_Layer_Type = "none";
    default_data->FWD_Layer_Type_mask = 0;
    default_data->FWD_Layer_Type_valid = 0;
    default_data->FWD_code_port_profile = "none";
    default_data->FWD_code_port_profile_mask = 0;
    default_data->FWD_code_port_profile_valid = 0;
    default_data->TM_Action_Type = 0;
    default_data->TM_Action_Type_mask = 0;
    default_data->TM_Action_Type_valid = 0;
    default_data->ingress_trapped = 0;
    default_data->ingress_trapped_mask = 0;
    default_data->ingress_trapped_valid = 0;
    default_data->is_Applet = 0;
    default_data->is_Applet_mask = 0;
    default_data->is_Applet_valid = 0;
    default_data->is_TDM = 0;
    default_data->is_TDM_mask = 0;
    default_data->is_TDM_valid = 0;
    default_data->Egress_FWD_Code = "none";
    default_data->Egress_FWD_Code_valid = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        for (soc_value_index = 0; soc_value_index < table->keys[1].size; soc_value_index++)
        {
            data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, soc_value_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }
    
    if (38 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 38, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "FWD_CODE_BUG_CODE";
        data->Egress_FWD_Code_valid = 1;
    }
    if (20 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "TDM_BS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TDM_BS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (0 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "RCH";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "EXT_ENCAP_DO_NOTHING";
        data->Egress_FWD_Code_valid = 1;
    }
    if (21 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 21, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 8;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 6338;
        data->FWD_Layer_Qualifier_mask = 57345;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6__HBH_PT_MidPoint_UC_R1";
        data->Egress_FWD_Code_valid = 1;
    }
    if (22 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 22, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 6338;
        data->FWD_Layer_Qualifier_mask = 57345;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6__HBH_PT_MidPoint_UC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (23 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 23, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 10;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R1";
        data->Egress_FWD_Code_valid = 1;
    }
    if (24 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 24, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 8;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R1";
        data->Egress_FWD_Code_valid = 1;
    }
    if (12 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 10;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv4";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R1";
        data->Egress_FWD_Code_valid = 1;
    }
    if (13 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 8;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv4";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R1";
        data->Egress_FWD_Code_valid = 1;
    }
    if (25 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 25, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "PPP";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "PPP";
        data->Egress_FWD_Code_valid = 1;
    }
    if (26 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 26, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "MPLS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MPLS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (14 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 5;
        data->FAI_mask = 2;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv4";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "DO_NOT_EDIT";
        data->Egress_FWD_Code_valid = 1;
    }
    if (15 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 5;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "MPLS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "DO_NOT_EDIT";
        data->Egress_FWD_Code_valid = 1;
    }
    if (16 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 5;
        data->FAI_mask = 2;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "DO_NOT_EDIT";
        data->Egress_FWD_Code_valid = 1;
    }
    if (17 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 5;
        data->FAI_mask = 10;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "MPLS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MPLS_INJECTED_FROM_OAMP";
        data->Egress_FWD_Code_valid = 1;
    }
    if (6 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 1;
        data->is_TDM_mask = 0;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TDM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (27 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 27, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 1;
        data->FWD_Layer_Qualifier_mask = 65520;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "SRv6_Endpoint";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_HBH_PT_MidPoint";
        data->Egress_FWD_Code_valid = 1;
    }
    if (1 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 1);
        data->valid = 1;
        data->ACE_Value = "J_Mode_FWD_Code_Override";
        data->ACE_Value_mask = 0;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "RAW_Processing";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (2 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 1);
        data->valid = 1;
        data->ACE_Value = "J_Mode_FWD_Code_Override";
        data->ACE_Value_mask = 0;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 1;
        data->is_TDM_mask = 0;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (7 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 1);
        data->valid = 1;
        data->ACE_Value = "J_Mode_FWD_Code_Override";
        data->ACE_Value_mask = 0;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (28 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 28, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "INITIALIZATION";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 0;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (29 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 29, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "SRV6_RCH_USP_PSP_AND_PSP_EXT";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_PSP_Extended_cut";
        data->Egress_FWD_Code_valid = 1;
    }
    if (30 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 30, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 8;
        data->FWD_Layer_Qualifier_mask = 65520;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "SRv6_Endpoint";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint_PSP";
        data->Egress_FWD_Code_valid = 1;
    }
    if (31 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 31, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65520;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "SRv6_Endpoint";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "SRv6_Endpoint";
        data->Egress_FWD_Code_valid = 1;
    }
    if (8 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "STACKING_Port";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "Stacking_Port";
        data->Egress_FWD_Code_valid = 1;
    }
    if (3 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 1);
        data->valid = 1;
        data->ACE_Value = "ERPP_Trapped";
        data->ACE_Value_mask = 0;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "ERPP_TRAPPED";
        data->Egress_FWD_Code_valid = 1;
    }
    if (4 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "CPU_Port";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "CPU_PORT";
        data->Egress_FWD_Code_valid = 1;
    }
    if (5 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "RAW_Processing";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "RAW_PROCESSING";
        data->Egress_FWD_Code_valid = 1;
    }
    if (11 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 1;
        data->ingress_trapped_mask = 0;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "INGRESS_TRAPPED_JR1_LEGACY";
        data->Egress_FWD_Code_valid = 1;
    }
    if (32 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 32, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "BIER_NON_MPLS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "BIER_NON_MPLS_BFR";
        data->Egress_FWD_Code_valid = 1;
    }
    if (33 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 33, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IN_BIER_BASE_EG_BIER_MPLS";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "BIER_MPLS_BFR";
        data->Egress_FWD_Code_valid = 1;
    }
    if (34 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 34, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 2;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (35 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 35, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv6";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (18 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 2;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv4";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (19 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 5;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPv4";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (9 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 2;
        data->TM_Action_Type_mask = 0;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (10 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 3;
        data->TM_Action_Type_mask = 0;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (36 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 36, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "IPvX";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (37 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 37, 1);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "ETHERNET";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "ETHERNET";
        data->Egress_FWD_Code_valid = 1;
    }
    if (7 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 5;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MPLS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (0 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 1;
        data->is_TDM_mask = 0;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TDM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (3 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->valid = 1;
        data->ACE_Value = "J_Mode_FWD_Code_Override";
        data->ACE_Value_mask = 0;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (8 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 15;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "INITIALIZATION";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "TM";
        data->Egress_FWD_Code_valid = 1;
    }
    if (1 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "CPU_Port";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "CPU_PORT";
        data->Egress_FWD_Code_valid = 1;
    }
    if (2 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "RAW_Processing";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "RAW_PROCESSING";
        data->Egress_FWD_Code_valid = 1;
    }
    if (6 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 7;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "INGRESS_TRAPPED_JR1_LEGACY";
        data->Egress_FWD_Code_valid = 1;
    }
    if (9 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 4;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_MC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (10 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 3;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv6_UC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (11 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 2;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_MC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (12 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 1;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "IPv4_UC_R0";
        data->Egress_FWD_Code_valid = 1;
    }
    if (4 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 1;
        data->TM_Action_Type_mask = 0;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (5 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 15;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "0";
        data->FWD_Layer_Type_mask = 31;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 2;
        data->TM_Action_Type_mask = 0;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "MIRROR_OR_SS";
        data->Egress_FWD_Code_valid = 1;
    }
    if (13 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->valid = 1;
        data->ACE_Value = "0";
        data->ACE_Value_mask = 3;
        data->ACE_Value_valid = 1;
        data->FAI = 0;
        data->FAI_mask = 0;
        data->FAI_valid = 1;
        data->FWD_Layer_Qualifier = 0;
        data->FWD_Layer_Qualifier_mask = 65535;
        data->FWD_Layer_Qualifier_valid = 1;
        data->FWD_Layer_Type = "ETHERNET";
        data->FWD_Layer_Type_mask = 0;
        data->FWD_Layer_Type_valid = 1;
        data->FWD_code_port_profile = "Normal";
        data->FWD_code_port_profile_mask = 0;
        data->FWD_code_port_profile_valid = 1;
        data->TM_Action_Type = 0;
        data->TM_Action_Type_mask = 3;
        data->TM_Action_Type_valid = 1;
        data->ingress_trapped = 0;
        data->ingress_trapped_mask = 1;
        data->ingress_trapped_valid = 1;
        data->is_Applet = 0;
        data->is_Applet_mask = 1;
        data->is_Applet_valid = 1;
        data->is_TDM = 0;
        data->is_TDM_mask = 1;
        data->is_TDM_valid = 1;
        data->Egress_FWD_Code = "ETHERNET";
        data->Egress_FWD_Code_valid = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT___image_set(
    int unit)
{
    dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT___image_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_START_TYPE_CONTEXT___image;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "EGRESS_PARSING_START_TYPE_CONTEXT___image", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "standard_1";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT___image_t, (1 + 1  ), "data of dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_START_TYPE_CONTEXT___image");

    
    default_data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT___image_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->image = "standard_1";
    
    data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT___image_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_set(
    int unit)
{
    int index_index;
    int soc_value_index;
    dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_START_TYPE_CONTEXT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "EGRESS_PARSING_START_TYPE_CONTEXT", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 32;
    table->info_get.key_size[0] = 32;
    table->keys[1].size = 2;
    table->info_get.key_size[1] = 2;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "default";
    table->values[2].default_val = "none";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "none";
    table->values[6].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_START_TYPE_CONTEXT");

    
    default_data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->valid = 0;
    default_data->doc = "default";
    default_data->Parsing_Start_Type = "none";
    default_data->Parsing_Start_Type_mask = 0;
    default_data->Parsing_Start_Type_valid = 0;
    default_data->Egress_1st_Parser_Parser_Context = "none";
    default_data->Egress_1st_Parser_Parser_Context_valid = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        for (soc_value_index = 0; soc_value_index < table->keys[1].size; soc_value_index++)
        {
            data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, soc_value_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }
    
    if (0 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "ETHERNET";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "Eth_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (1 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "INITIALIZATION";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "TM";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (2 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "ITMH_VAL";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "TM";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (3 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "IPv4";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "IPv4_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (4 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "IPv6";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "IPv6_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (5 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "SRv6_Endpoint";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "SRv6Endpoint_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (6 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "IN_BIER_BASE_EG_BIER_MPLS";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "BIER_MPLS_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (7 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "BIER_NON_MPLS";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "BIER_NON_MPLS_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (8 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "INGRESS_SCTP_EGRESS_FTMH";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "FTMH_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (9 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "PPP";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "PPP_A";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (10 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "IPv4_12B";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "IPv4_12B_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (11 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "IPv6_8B";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "IPv6_8B_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (12 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "MPLS";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "MPLS_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (13 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "MPLS_UNTERM";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "MPLS_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (14 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "DUMMY_ETHERNET";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "DUMMY_ETH";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (15 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "RCH_EXTENDED_ENCAP";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "RCH_EXTENDED_ENCAP";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (16 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "SRV6_RCH_USP_PSP_AND_PSP_EXT";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "SRv6_PSP_EXTENDED_TERMINATION";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (17 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "SRv6_Endpoint_PSP";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "SRv6Endpoint_PSP_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (18 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "MPLS_DUMMY";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "MPLS_DUMMY";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (19 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "FORCE_MIRROR_OR_SS";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "FORCE_MIRROR_OR_SS";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (20 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 1);
        data->valid = 1;
        data->Parsing_Start_Type = "TDM_BS";
        data->Parsing_Start_Type_mask = 0;
        data->Parsing_Start_Type_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "TDM_BS";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE___image_set(
    int unit)
{
    dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE___image_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE___image;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "EGRESS_PARSING_CONTEXT_MAP_JR1_MODE___image", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "standard_1";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE___image_t, (1 + 1  ), "data of dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE___image");

    
    default_data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE___image_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->image = "standard_1";
    
    data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE___image_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_set(
    int unit)
{
    int index_index;
    int soc_value_index;
    dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "EGRESS_PARSING_CONTEXT_MAP_JR1_MODE", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 16;
    table->info_get.key_size[0] = 16;
    table->keys[1].size = 2;
    table->info_get.key_size[1] = 2;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "default";
    table->values[2].default_val = "none";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "none";
    table->values[6].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE");

    
    default_data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->valid = 0;
    default_data->doc = "default";
    default_data->JR_FWD_CODE = "none";
    default_data->JR_FWD_CODE_mask = 0;
    default_data->JR_FWD_CODE_valid = 0;
    default_data->Egress_1st_Parser_Parser_Context = "none";
    default_data->Egress_1st_Parser_Parser_Context_valid = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        for (soc_value_index = 0; soc_value_index < table->keys[1].size; soc_value_index++)
        {
            data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, soc_value_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }
    
    if (0 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->valid = 1;
        data->JR_FWD_CODE = "Bridge";
        data->JR_FWD_CODE_mask = 0;
        data->JR_FWD_CODE_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "Eth_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (1 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->valid = 1;
        data->JR_FWD_CODE = "Snoop_OR_Mirror";
        data->JR_FWD_CODE_mask = 0;
        data->JR_FWD_CODE_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "Eth_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (2 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->valid = 1;
        data->JR_FWD_CODE = "TM";
        data->JR_FWD_CODE_mask = 0;
        data->JR_FWD_CODE_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "TM";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (3 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->valid = 1;
        data->JR_FWD_CODE = "IPv4_UC";
        data->JR_FWD_CODE_mask = 0;
        data->JR_FWD_CODE_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "IPv4_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (4 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->valid = 1;
        data->JR_FWD_CODE = "IPv4_MC";
        data->JR_FWD_CODE_mask = 0;
        data->JR_FWD_CODE_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "IPv4_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (5 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->valid = 1;
        data->JR_FWD_CODE = "IPv6_UC";
        data->JR_FWD_CODE_mask = 0;
        data->JR_FWD_CODE_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "IPv6_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (6 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->valid = 1;
        data->JR_FWD_CODE = "IPv6_MC";
        data->JR_FWD_CODE_mask = 0;
        data->JR_FWD_CODE_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "IPv6_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }
    if (7 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->valid = 1;
        data->JR_FWD_CODE = "MPLS";
        data->JR_FWD_CODE_mask = 0;
        data->JR_FWD_CODE_valid = 1;
        data->Egress_1st_Parser_Parser_Context = "MPLS_A1";
        data->Egress_1st_Parser_Parser_Context_valid = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT___image_set(
    int unit)
{
    dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT___image_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_FER_FILTERS_PER_FWD_CONTEXT___image;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "FER_FILTERS_PER_FWD_CONTEXT___image", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "standard_1";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT___image_t, (1 + 1  ), "data of dnx_data_dnx2_aod_tables_table_FER_FILTERS_PER_FWD_CONTEXT___image");

    
    default_data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT___image_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->image = "standard_1";
    
    data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT___image_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_set(
    int unit)
{
    int index_index;
    dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_FER_FILTERS_PER_FWD_CONTEXT;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "FER_FILTERS_PER_FWD_CONTEXT", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 64;
    table->info_get.key_size[0] = 64;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "default";
    table->values[2].default_val = "none";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    table->values[6].default_val = "0";
    table->values[7].default_val = "none";
    table->values[8].default_val = "0";
    table->values[9].default_val = "0";
    table->values[10].default_val = "0";
    table->values[11].default_val = "0";
    table->values[12].default_val = "0";
    table->values[13].default_val = "0";
    table->values[14].default_val = "0";
    table->values[15].default_val = "0";
    table->values[16].default_val = "0";
    table->values[17].default_val = "0";
    table->values[18].default_val = "0";
    table->values[19].default_val = "0";
    table->values[20].default_val = "0";
    table->values[21].default_val = "0";
    table->values[22].default_val = "0";
    table->values[23].default_val = "0";
    table->values[24].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_dnx2_aod_tables_table_FER_FILTERS_PER_FWD_CONTEXT");

    
    default_data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->valid = 0;
    default_data->doc = "default";
    default_data->CTX_FWD2 = "none";
    default_data->CTX_FWD2_mask = 0;
    default_data->CTX_FWD2_valid = 0;
    default_data->FACILITY_INVALID = 0;
    default_data->FACILITY_INVALID_valid = 0;
    default_data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "none";
    default_data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 0;
    default_data->MC_EXPLICIT_RPF = 0;
    default_data->MC_EXPLICIT_RPF_valid = 0;
    default_data->MC_EXPLICIT_RPF_ECMP = 0;
    default_data->MC_EXPLICIT_RPF_ECMP_valid = 0;
    default_data->MC_SIP_BASED_RPF = 0;
    default_data->MC_SIP_BASED_RPF_valid = 0;
    default_data->OUTLIF_OVER_FLOW = 0;
    default_data->OUTLIF_OVER_FLOW_valid = 0;
    default_data->SAME_INTERFACE = 0;
    default_data->SAME_INTERFACE_valid = 0;
    default_data->SIP_TRANSPLANT_DETECTION = 0;
    default_data->SIP_TRANSPLANT_DETECTION_valid = 0;
    default_data->UC_LOOSE_RPF = 0;
    default_data->UC_LOOSE_RPF_valid = 0;
    default_data->UC_STRICT_RPF = 0;
    default_data->UC_STRICT_RPF_valid = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->valid = 1;
        data->CTX_FWD2 = "BRIDGE___IVL";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 0;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "DEFAULT";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 0;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 0;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 0;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 0;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 0;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->valid = 1;
        data->CTX_FWD2 = "BRIDGE___SVL";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 0;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "DEFAULT";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 0;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 0;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 0;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 0;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 0;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->valid = 1;
        data->CTX_FWD2 = "IPV4___MC_Private_W_BF_W_F2B";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 1;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "IP";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 1;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 1;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 1;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 0;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 0;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->valid = 1;
        data->CTX_FWD2 = "IPV4___MC_Private_WO_BF_W_F2B";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 1;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "IP";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 1;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 1;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 1;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 0;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 0;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->valid = 1;
        data->CTX_FWD2 = "IPV4___MC_Private_WO_BF_WO_F2B";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 1;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "IP";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 1;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 1;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 1;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 0;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 0;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->valid = 1;
        data->CTX_FWD2 = "IPV4___Private_UC_LEM_Only";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 1;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "IP";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 0;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 0;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 0;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 1;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 1;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->valid = 1;
        data->CTX_FWD2 = "IPV4___Private_UC";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 1;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "IP";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 0;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 0;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 0;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 1;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 1;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->valid = 1;
        data->CTX_FWD2 = "IPV6___MC_Private_W_BF_W_F2B";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 1;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "IP";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 1;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 1;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 1;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 0;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 0;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->valid = 1;
        data->CTX_FWD2 = "IPV6___MC_Private_WO_BF_W_F2B";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 1;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "IP";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 1;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 1;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 1;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 0;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 0;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->valid = 1;
        data->CTX_FWD2 = "IPV6___MC_Private_WO_BF_WO_F2B";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 1;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "IP";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 1;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 1;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 1;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 0;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 0;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->valid = 1;
        data->CTX_FWD2 = "IPV6___Private_UC_LEM_Only";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 1;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "IP";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 0;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 0;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 0;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 1;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 1;
        data->UC_STRICT_RPF_valid = 1;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->valid = 1;
        data->CTX_FWD2 = "IPV6___Private_UC";
        data->CTX_FWD2_mask = 0;
        data->CTX_FWD2_valid = 1;
        data->FACILITY_INVALID = 1;
        data->FACILITY_INVALID_valid = 1;
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE = "IP";
        data->FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_valid = 1;
        data->MC_EXPLICIT_RPF = 0;
        data->MC_EXPLICIT_RPF_valid = 1;
        data->MC_EXPLICIT_RPF_ECMP = 0;
        data->MC_EXPLICIT_RPF_ECMP_valid = 1;
        data->MC_SIP_BASED_RPF = 0;
        data->MC_SIP_BASED_RPF_valid = 1;
        data->OUTLIF_OVER_FLOW = 0;
        data->OUTLIF_OVER_FLOW_valid = 1;
        data->SAME_INTERFACE = 1;
        data->SAME_INTERFACE_valid = 1;
        data->SIP_TRANSPLANT_DETECTION = 0;
        data->SIP_TRANSPLANT_DETECTION_valid = 1;
        data->UC_LOOSE_RPF = 1;
        data->UC_LOOSE_RPF_valid = 1;
        data->UC_STRICT_RPF = 1;
        data->UC_STRICT_RPF_valid = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO___image_set(
    int unit)
{
    dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO___image_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_INGRESS_PRT_INFO___image;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "INGRESS_PRT_INFO___image", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "standard_1";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO___image_t, (1 + 1  ), "data of dnx_data_dnx2_aod_tables_table_INGRESS_PRT_INFO___image");

    
    default_data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO___image_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->image = "standard_1";
    
    data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO___image_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_set(
    int unit)
{
    int index_index;
    dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_INGRESS_PRT_INFO;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "INGRESS_PRT_INFO", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 256;
    table->info_get.key_size[0] = 256;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "default";
    table->values[2].default_val = "none";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "none";
    table->values[6].default_val = "0";
    table->values[7].default_val = "0";
    table->values[8].default_val = "0";
    table->values[9].default_val = "0";
    table->values[10].default_val = "0";
    table->values[11].default_val = "0";
    table->values[12].default_val = "0";
    table->values[13].default_val = "0";
    table->values[14].default_val = "0";
    table->values[15].default_val = "0";
    table->values[16].default_val = "0";
    table->values[17].default_val = "0";
    table->values[18].default_val = "0";
    table->values[19].default_val = "0";
    table->values[20].default_val = "0";
    table->values[21].default_val = "0";
    table->values[22].default_val = "0";
    table->values[23].default_val = "0";
    table->values[24].default_val = "0";
    table->values[25].default_val = "0";
    table->values[26].default_val = "0";
    table->values[27].default_val = "0";
    table->values[28].default_val = "0";
    table->values[29].default_val = "0";
    table->values[30].default_val = "0";
    table->values[31].default_val = "0";
    table->values[32].default_val = "0";
    table->values[33].default_val = "0";
    table->values[34].default_val = "0";
    table->values[35].default_val = "0";
    table->values[36].default_val = "0";
    table->values[37].default_val = "0";
    table->values[38].default_val = "0";
    table->values[39].default_val = "0";
    table->values[40].default_val = "0";
    table->values[41].default_val = "0";
    table->values[42].default_val = "0";
    table->values[43].default_val = "0";
    table->values[44].default_val = "0";
    table->values[45].default_val = "0";
    table->values[46].default_val = "0";
    table->values[47].default_val = "0";
    table->values[48].default_val = "0";
    table->values[49].default_val = "0";
    table->values[50].default_val = "0";
    table->values[51].default_val = "0";
    table->values[52].default_val = "0";
    table->values[53].default_val = "0";
    table->values[54].default_val = "0";
    table->values[55].default_val = "0";
    table->values[56].default_val = "0";
    table->values[57].default_val = "0";
    table->values[58].default_val = "0";
    table->values[59].default_val = "0";
    table->values[60].default_val = "0";
    table->values[61].default_val = "0";
    table->values[62].default_val = "0";
    table->values[63].default_val = "0";
    table->values[64].default_val = "0";
    table->values[65].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_dnx2_aod_tables_table_INGRESS_PRT_INFO");

    
    default_data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->valid = 0;
    default_data->doc = "default";
    default_data->PORT_TERMINATION_PTC_PROFILE = "none";
    default_data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
    default_data->PORT_TERMINATION_PTC_PROFILE_valid = 0;
    default_data->RECYCLE_CMD_PRT_PROFILE = "none";
    default_data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
    default_data->RECYCLE_CMD_PRT_PROFILE_valid = 0;
    default_data->FFC_0_Input_Offset = 0;
    default_data->FFC_0_Input_Offset_valid = 0;
    default_data->FFC_0_Offset = 0;
    default_data->FFC_0_Offset_valid = 0;
    default_data->FFC_0_Width = 0;
    default_data->FFC_0_Width_valid = 0;
    default_data->FFC_1_Input_Offset = 0;
    default_data->FFC_1_Input_Offset_valid = 0;
    default_data->FFC_1_Offset = 0;
    default_data->FFC_1_Offset_valid = 0;
    default_data->FFC_1_Width = 0;
    default_data->FFC_1_Width_valid = 0;
    default_data->FFC_2_Input_Offset = 0;
    default_data->FFC_2_Input_Offset_valid = 0;
    default_data->FFC_2_Offset = 0;
    default_data->FFC_2_Offset_valid = 0;
    default_data->FFC_2_Width = 0;
    default_data->FFC_2_Width_valid = 0;
    default_data->FFC_3_Input_Offset = 0;
    default_data->FFC_3_Input_Offset_valid = 0;
    default_data->FFC_3_Offset = 0;
    default_data->FFC_3_Offset_valid = 0;
    default_data->FFC_3_Width = 0;
    default_data->FFC_3_Width_valid = 0;
    default_data->FFC_4_Input_Offset = 0;
    default_data->FFC_4_Input_Offset_valid = 0;
    default_data->FFC_4_Offset = 0;
    default_data->FFC_4_Offset_valid = 0;
    default_data->FFC_4_Width = 0;
    default_data->FFC_4_Width_valid = 0;
    default_data->FFC_5_Input_Offset = 0;
    default_data->FFC_5_Input_Offset_valid = 0;
    default_data->FFC_5_Offset = 0;
    default_data->FFC_5_Offset_valid = 0;
    default_data->FFC_5_Width = 0;
    default_data->FFC_5_Width_valid = 0;
    default_data->Layer_Offset = 0;
    default_data->Layer_Offset_valid = 0;
    default_data->PP_Port_enable = 0;
    default_data->PP_Port_enable_valid = 0;
    default_data->PRT_Qualifier_KBR_Key = 0;
    default_data->PRT_Qualifier_KBR_Key_valid = 0;
    default_data->PRT_Qualifier_Mode = 0;
    default_data->PRT_Qualifier_Mode_valid = 0;
    default_data->Parser_Context_KBR_Key = 0;
    default_data->Parser_Context_KBR_Key_valid = 0;
    default_data->Parser_Context_Select = 0;
    default_data->Parser_Context_Select_valid = 0;
    default_data->Parsing_Start_Offset_KBR_Key = 0;
    default_data->Parsing_Start_Offset_KBR_Key_valid = 0;
    default_data->Source_System_Port_KBR_Key = 0;
    default_data->Source_System_Port_KBR_Key_valid = 0;
    default_data->Source_System_Port_PRT_Mode = 0;
    default_data->Source_System_Port_PRT_Mode_valid = 0;
    default_data->TCAM_Mode_Full_enable = 0;
    default_data->TCAM_Mode_Full_enable_valid = 0;
    default_data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 0;
    default_data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "PTCH2";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "NONE";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 240;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 7;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 252;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 3;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 255;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 0;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 0;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 0;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 0;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 2;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 0;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 2;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 1;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 4;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 1;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 0;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 0;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 1;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "PTCH1";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "NONE";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 232;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 15;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 252;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 3;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 255;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 0;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 321;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 16;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 248;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 2;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 0;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 232;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 15;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 3;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 1;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 2;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 1;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 4;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 1;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 16;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 32;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 2;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 0;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 9;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "ETHERNET";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "NONE";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 308;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 7;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 0;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 0;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 0;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 0;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 0;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 292;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 15;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 0;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 0;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 0;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 0;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 0;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 0;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 16;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 2;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 1;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "ETHERNET";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "PTCH2";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 240;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 7;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 252;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 3;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 255;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 0;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 0;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 292;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 15;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 2;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 0;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 2;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 1;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 4;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 1;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 16;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 0;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 1;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "ETHERNET";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "802_1BR_TYPE1";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 308;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 7;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 0;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 0;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 0;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 0;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 0;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 292;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 15;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 8;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 0;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 0;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 0;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 0;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 0;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 16;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 2;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 1;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "ETHERNET";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "802_1BR_TYPE2";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 308;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 7;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 0;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 0;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 0;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 0;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 0;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 292;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 15;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 8;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 0;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 0;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 0;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 0;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 0;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 16;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 2;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 1;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "RCH";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "NONE";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 200;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 15;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 0;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 0;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 200;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 15;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 0;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 0;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 0;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 316;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 4;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 0;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 1;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 0;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 0;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 32;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 1;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 4;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 2;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 0;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "COE";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "COE";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 224;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 5;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 308;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 6;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 7;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 0;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 0;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 321;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 14;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 2;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 0;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 0;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 4;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 1;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 0;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 0;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 0;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 0;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 0;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 1;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 0;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 11;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "RCH";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "PTCH2";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 240;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 7;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 252;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 3;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 128;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 15;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 280;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 4;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 0;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 0;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 2;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 0;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 2;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 1;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 4;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 1;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 0;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 0;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 1;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "PTCH2_JR1";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "NONE";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 240;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 7;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 252;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 3;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 255;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 0;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 321;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 1;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 1;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 0;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 0;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 2;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 0;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 2;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 1;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 12;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 1;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 0;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 0;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 1;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "ITMH";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "NONE";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 308;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 7;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 0;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 0;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 0;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 0;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 0;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 0;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 0;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 0;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 0;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 0;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 0;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 0;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 0;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 0;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 0;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 1;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "RAW";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "NONE";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 308;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 7;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 0;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 0;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 0;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 0;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 0;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 292;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 15;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 0;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 0;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 0;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 0;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 0;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 0;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 16;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 2;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 1;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "PON";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "COE";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 236;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 3;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 308;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 4;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 7;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 292;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 13;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 3;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 0;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 0;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 0;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 0;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 1;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 0;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 0;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 0;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 0;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 0;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 0;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 0;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 7;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "SRV6_USP_PSP";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "NONE";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 240;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 15;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 252;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 3;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 316;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 4;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 321;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 16;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 248;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 2;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 0;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 232;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 15;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 0;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 1;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 2;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 0;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 4;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 1;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 32;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 2;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 0;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->valid = 1;
        data->PORT_TERMINATION_PTC_PROFILE = "ETHERNET";
        data->PORT_TERMINATION_PTC_PROFILE_mask = 0;
        data->PORT_TERMINATION_PTC_PROFILE_valid = 1;
        data->RECYCLE_CMD_PRT_PROFILE = "ETH_APPEND64";
        data->RECYCLE_CMD_PRT_PROFILE_mask = 0;
        data->RECYCLE_CMD_PRT_PROFILE_valid = 1;
        data->FFC_0_Input_Offset = 308;
        data->FFC_0_Input_Offset_valid = 1;
        data->FFC_0_Offset = 0;
        data->FFC_0_Offset_valid = 1;
        data->FFC_0_Width = 7;
        data->FFC_0_Width_valid = 1;
        data->FFC_1_Input_Offset = 0;
        data->FFC_1_Input_Offset_valid = 1;
        data->FFC_1_Offset = 0;
        data->FFC_1_Offset_valid = 1;
        data->FFC_1_Width = 0;
        data->FFC_1_Width_valid = 1;
        data->FFC_2_Input_Offset = 280;
        data->FFC_2_Input_Offset_valid = 1;
        data->FFC_2_Offset = 0;
        data->FFC_2_Offset_valid = 1;
        data->FFC_2_Width = 4;
        data->FFC_2_Width_valid = 1;
        data->FFC_3_Input_Offset = 0;
        data->FFC_3_Input_Offset_valid = 1;
        data->FFC_3_Offset = 0;
        data->FFC_3_Offset_valid = 1;
        data->FFC_3_Width = 0;
        data->FFC_3_Width_valid = 1;
        data->FFC_4_Input_Offset = 292;
        data->FFC_4_Input_Offset_valid = 1;
        data->FFC_4_Offset = 0;
        data->FFC_4_Offset_valid = 1;
        data->FFC_4_Width = 15;
        data->FFC_4_Width_valid = 1;
        data->FFC_5_Input_Offset = 0;
        data->FFC_5_Input_Offset_valid = 1;
        data->FFC_5_Offset = 0;
        data->FFC_5_Offset_valid = 1;
        data->FFC_5_Width = 0;
        data->FFC_5_Width_valid = 1;
        data->Layer_Offset = 64;
        data->Layer_Offset_valid = 1;
        data->PP_Port_enable = 0;
        data->PP_Port_enable_valid = 1;
        data->PRT_Qualifier_KBR_Key = 0;
        data->PRT_Qualifier_KBR_Key_valid = 1;
        data->PRT_Qualifier_Mode = 0;
        data->PRT_Qualifier_Mode_valid = 1;
        data->Parser_Context_KBR_Key = 4;
        data->Parser_Context_KBR_Key_valid = 1;
        data->Parser_Context_Select = 1;
        data->Parser_Context_Select_valid = 1;
        data->Parsing_Start_Offset_KBR_Key = 0;
        data->Parsing_Start_Offset_KBR_Key_valid = 1;
        data->Source_System_Port_KBR_Key = 16;
        data->Source_System_Port_KBR_Key_valid = 1;
        data->Source_System_Port_PRT_Mode = 2;
        data->Source_System_Port_PRT_Mode_valid = 1;
        data->TCAM_Mode_Full_enable = 1;
        data->TCAM_Mode_Full_enable_valid = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key = 1;
        data->VP_TCAM_or_PP_Port_Direct_KBR_Key_valid = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP___image_set(
    int unit)
{
    dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP___image_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_MAP___image;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "MPLS_SPECIAL_LABEL_PROFILE_MAP___image", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "standard_1";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP___image_t, (1 + 1  ), "data of dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_MAP___image");

    
    default_data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP___image_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->image = "standard_1";
    
    data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP___image_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_set(
    int unit)
{
    int index_index;
    dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_MAP;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "MPLS_SPECIAL_LABEL_PROFILE_MAP", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 32;
    table->info_get.key_size[0] = 32;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "default";
    table->values[2].default_val = "0";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "none";
    table->values[6].default_val = "0";
    table->values[7].default_val = "0";
    table->values[8].default_val = "none";
    table->values[9].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_MAP");

    
    default_data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->valid = 0;
    default_data->doc = "default";
    default_data->BOS = 0;
    default_data->BOS_mask = 0;
    default_data->BOS_valid = 0;
    default_data->MPLS_Special_Label_Nibble = "none";
    default_data->MPLS_Special_Label_Nibble_mask = 0;
    default_data->MPLS_Special_Label_Nibble_valid = 0;
    default_data->MPLS_Special_Label_Profile = "none";
    default_data->MPLS_Special_Label_Profile_valid = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "IPv4_Explicit_NULL";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "IPv4_Explicit_NULL";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "IPv4_Explicit_NULL";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "IPv4_Explicit_NULL";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Router_Alert";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Router_Alert";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Router_Alert";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Router_Alert";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "IPv6_Explicit_NULL";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "IPv6_Explicit_NULL";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "IPv6_Explicit_NULL";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "IPv6_Explicit_NULL";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_3";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_3";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_4";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_4";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_5";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_5";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_6";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_6";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "ELI";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "ELI";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "ELI";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "ELI";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_8";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_8";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (18 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_9";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (19 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_9";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (20 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_10";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (21 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 21, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_10";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (22 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 22, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_11";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (23 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 23, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_11";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (24 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 24, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_12";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (25 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 25, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_12";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (26 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 26, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "GAL";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "GAL";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (27 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 27, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "GAL";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "GAL";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (28 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 28, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "OAM_Alert";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "OAM_Alert";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (29 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 29, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "OAM_Alert";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "OAM_Alert";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (30 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 30, 0);
        data->valid = 1;
        data->BOS = 0;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_15";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }
    if (31 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_t *) dnxc_data_mgmt_table_data_get(unit, table, 31, 0);
        data->valid = 1;
        data->BOS = 1;
        data->BOS_mask = 0;
        data->BOS_valid = 1;
        data->MPLS_Special_Label_Nibble = "Nibble_15";
        data->MPLS_Special_Label_Nibble_mask = 0;
        data->MPLS_Special_Label_Nibble_valid = 1;
        data->MPLS_Special_Label_Profile = "Invalid_Label";
        data->MPLS_Special_Label_Profile_valid = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES___image_set(
    int unit)
{
    dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES___image_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES___image;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES___image", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "standard_1";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES___image_t, (1 + 1  ), "data of dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES___image");

    
    default_data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES___image_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->image = "standard_1";
    
    data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES___image_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_standard_1_dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_set(
    int unit)
{
    int index_index;
    dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = dnx_data_dnx2_aod_submodule_tables;
    int table_index = dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES", "DNX2");
    }

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 8;
    table->info_get.key_size[0] = 8;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "default";
    table->values[2].default_val = "none";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    table->values[6].default_val = "0";
    table->values[7].default_val = "0";
    table->values[8].default_val = "0";
    table->values[9].default_val = "0";
    table->values[10].default_val = "0";
    table->values[11].default_val = "0";
    table->values[12].default_val = "0";
    table->values[13].default_val = "0";
    table->values[14].default_val = "0";
    table->values[15].default_val = "0";
    table->values[16].default_val = "0";
    table->values[17].default_val = "0";
    table->values[18].default_val = "0";
    table->values[19].default_val = "0";
    table->values[20].default_val = "0";
    table->values[21].default_val = "none";
    table->values[22].default_val = "0";
    table->values[23].default_val = "0";
    table->values[24].default_val = "0";
    table->values[25].default_val = "0";
    table->values[26].default_val = "0";
    table->values[27].default_val = "0";
    table->values[28].default_val = "0";
    table->values[29].default_val = "0";
    table->values[30].default_val = "0";
    table->values[31].default_val = "0";
    table->values[32].default_val = "0";
    table->values[33].default_val = "0";
    table->values[34].default_val = "0";
    table->values[35].default_val = "0";
    table->values[36].default_val = "0";
    table->values[37].default_val = "0";
    table->values[38].default_val = "0";
    table->values[39].default_val = "0";
    table->values[40].default_val = "0";
    table->values[41].default_val = "0";
    table->values[42].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES");

    
    default_data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->valid = 0;
    default_data->doc = "default";
    default_data->VTT_MPLS_Special_Label_Profile = "none";
    default_data->VTT_MPLS_Special_Label_Profile_mask = 0;
    default_data->VTT_MPLS_Special_Label_Profile_valid = 0;
    default_data->Check_Bos = 0;
    default_data->Check_Bos_valid = 0;
    default_data->ECN_Compare_Strength = 0;
    default_data->ECN_Compare_Strength_valid = 0;
    default_data->ECN_Mapping_Profile = 0;
    default_data->ECN_Mapping_Profile_valid = 0;
    default_data->ECN_Propagation_Strength = 0;
    default_data->ECN_Propagation_Strength_valid = 0;
    default_data->Expected_Bos = 0;
    default_data->Expected_Bos_valid = 0;
    default_data->Force_Has_CW = 0;
    default_data->Force_Has_CW_valid = 0;
    default_data->Force_Is_OAM = 0;
    default_data->Force_Is_OAM_valid = 0;
    default_data->Force_Parser_Context = 0;
    default_data->Force_Parser_Context_valid = 0;
    default_data->Force_Parser_Context_Value = "none";
    default_data->Force_Parser_Context_Value_valid = 0;
    default_data->Labels_To_Terminate = 0;
    default_data->Labels_To_Terminate_valid = 0;
    default_data->PHB_Compare_Strength = 0;
    default_data->PHB_Compare_Strength_valid = 0;
    default_data->PHB_Propagation_Strength = 0;
    default_data->PHB_Propagation_Strength_valid = 0;
    default_data->Qos_Mapping_Profile = 0;
    default_data->Qos_Mapping_Profile_valid = 0;
    default_data->Remark_Compare_Strength = 0;
    default_data->Remark_Compare_Strength_valid = 0;
    default_data->Remark_Propagation_Strength = 0;
    default_data->Remark_Propagation_Strength_valid = 0;
    default_data->Special_After_Tunnel = 0;
    default_data->Special_After_Tunnel_valid = 0;
    default_data->Special_Before_Tunnel = 0;
    default_data->Special_Before_Tunnel_valid = 0;
    default_data->TTL_Compare_Strength = 0;
    default_data->TTL_Compare_Strength_valid = 0;
    default_data->TTL_Propagation_Strength = 0;
    default_data->TTL_Propagation_Strength_valid = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->valid = 1;
        data->VTT_MPLS_Special_Label_Profile = "IPv4_Explicit_NULL";
        data->VTT_MPLS_Special_Label_Profile_mask = 0;
        data->VTT_MPLS_Special_Label_Profile_valid = 1;
        data->Check_Bos = 0;
        data->Check_Bos_valid = 1;
        data->ECN_Compare_Strength = 0;
        data->ECN_Compare_Strength_valid = 1;
        data->ECN_Mapping_Profile = 0;
        data->ECN_Mapping_Profile_valid = 1;
        data->ECN_Propagation_Strength = 0;
        data->ECN_Propagation_Strength_valid = 1;
        data->Expected_Bos = 0;
        data->Expected_Bos_valid = 1;
        data->Force_Has_CW = 0;
        data->Force_Has_CW_valid = 1;
        data->Force_Is_OAM = 0;
        data->Force_Is_OAM_valid = 1;
        data->Force_Parser_Context = 1;
        data->Force_Parser_Context_valid = 1;
        data->Force_Parser_Context_Value = "IPv4_NoEthB2";
        data->Force_Parser_Context_Value_valid = 1;
        data->Labels_To_Terminate = 0;
        data->Labels_To_Terminate_valid = 1;
        data->PHB_Compare_Strength = 0;
        data->PHB_Compare_Strength_valid = 1;
        data->PHB_Propagation_Strength = 1;
        data->PHB_Propagation_Strength_valid = 1;
        data->Qos_Mapping_Profile = 0;
        data->Qos_Mapping_Profile_valid = 1;
        data->Remark_Compare_Strength = 0;
        data->Remark_Compare_Strength_valid = 1;
        data->Remark_Propagation_Strength = 1;
        data->Remark_Propagation_Strength_valid = 1;
        data->Special_After_Tunnel = 0;
        data->Special_After_Tunnel_valid = 1;
        data->Special_Before_Tunnel = 1;
        data->Special_Before_Tunnel_valid = 1;
        data->TTL_Compare_Strength = 0;
        data->TTL_Compare_Strength_valid = 1;
        data->TTL_Propagation_Strength = 1;
        data->TTL_Propagation_Strength_valid = 1;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->valid = 1;
        data->VTT_MPLS_Special_Label_Profile = "IPv6_Explicit_NULL";
        data->VTT_MPLS_Special_Label_Profile_mask = 0;
        data->VTT_MPLS_Special_Label_Profile_valid = 1;
        data->Check_Bos = 0;
        data->Check_Bos_valid = 1;
        data->ECN_Compare_Strength = 0;
        data->ECN_Compare_Strength_valid = 1;
        data->ECN_Mapping_Profile = 0;
        data->ECN_Mapping_Profile_valid = 1;
        data->ECN_Propagation_Strength = 0;
        data->ECN_Propagation_Strength_valid = 1;
        data->Expected_Bos = 0;
        data->Expected_Bos_valid = 1;
        data->Force_Has_CW = 0;
        data->Force_Has_CW_valid = 1;
        data->Force_Is_OAM = 0;
        data->Force_Is_OAM_valid = 1;
        data->Force_Parser_Context = 1;
        data->Force_Parser_Context_valid = 1;
        data->Force_Parser_Context_Value = "IPv6_NoEthB2";
        data->Force_Parser_Context_Value_valid = 1;
        data->Labels_To_Terminate = 0;
        data->Labels_To_Terminate_valid = 1;
        data->PHB_Compare_Strength = 0;
        data->PHB_Compare_Strength_valid = 1;
        data->PHB_Propagation_Strength = 1;
        data->PHB_Propagation_Strength_valid = 1;
        data->Qos_Mapping_Profile = 0;
        data->Qos_Mapping_Profile_valid = 1;
        data->Remark_Compare_Strength = 0;
        data->Remark_Compare_Strength_valid = 1;
        data->Remark_Propagation_Strength = 1;
        data->Remark_Propagation_Strength_valid = 1;
        data->Special_After_Tunnel = 0;
        data->Special_After_Tunnel_valid = 1;
        data->Special_Before_Tunnel = 1;
        data->Special_Before_Tunnel_valid = 1;
        data->TTL_Compare_Strength = 0;
        data->TTL_Compare_Strength_valid = 1;
        data->TTL_Propagation_Strength = 1;
        data->TTL_Propagation_Strength_valid = 1;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->valid = 1;
        data->VTT_MPLS_Special_Label_Profile = "Router_Alert";
        data->VTT_MPLS_Special_Label_Profile_mask = 0;
        data->VTT_MPLS_Special_Label_Profile_valid = 1;
        data->Check_Bos = 1;
        data->Check_Bos_valid = 1;
        data->ECN_Compare_Strength = 0;
        data->ECN_Compare_Strength_valid = 1;
        data->ECN_Mapping_Profile = 0;
        data->ECN_Mapping_Profile_valid = 1;
        data->ECN_Propagation_Strength = 0;
        data->ECN_Propagation_Strength_valid = 1;
        data->Expected_Bos = 0;
        data->Expected_Bos_valid = 1;
        data->Force_Has_CW = 0;
        data->Force_Has_CW_valid = 1;
        data->Force_Is_OAM = 1;
        data->Force_Is_OAM_valid = 1;
        data->Force_Parser_Context = 0;
        data->Force_Parser_Context_valid = 1;
        data->Force_Parser_Context_Value = "Eth_B1";
        data->Force_Parser_Context_Value_valid = 1;
        data->Labels_To_Terminate = 0;
        data->Labels_To_Terminate_valid = 1;
        data->PHB_Compare_Strength = 0;
        data->PHB_Compare_Strength_valid = 1;
        data->PHB_Propagation_Strength = 0;
        data->PHB_Propagation_Strength_valid = 1;
        data->Qos_Mapping_Profile = 0;
        data->Qos_Mapping_Profile_valid = 1;
        data->Remark_Compare_Strength = 0;
        data->Remark_Compare_Strength_valid = 1;
        data->Remark_Propagation_Strength = 0;
        data->Remark_Propagation_Strength_valid = 1;
        data->Special_After_Tunnel = 0;
        data->Special_After_Tunnel_valid = 1;
        data->Special_Before_Tunnel = 1;
        data->Special_Before_Tunnel_valid = 1;
        data->TTL_Compare_Strength = 0;
        data->TTL_Compare_Strength_valid = 1;
        data->TTL_Propagation_Strength = 0;
        data->TTL_Propagation_Strength_valid = 1;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->valid = 1;
        data->VTT_MPLS_Special_Label_Profile = "ELI";
        data->VTT_MPLS_Special_Label_Profile_mask = 0;
        data->VTT_MPLS_Special_Label_Profile_valid = 1;
        data->Check_Bos = 1;
        data->Check_Bos_valid = 1;
        data->ECN_Compare_Strength = 0;
        data->ECN_Compare_Strength_valid = 1;
        data->ECN_Mapping_Profile = 0;
        data->ECN_Mapping_Profile_valid = 1;
        data->ECN_Propagation_Strength = 0;
        data->ECN_Propagation_Strength_valid = 1;
        data->Expected_Bos = 0;
        data->Expected_Bos_valid = 1;
        data->Force_Has_CW = 0;
        data->Force_Has_CW_valid = 1;
        data->Force_Is_OAM = 0;
        data->Force_Is_OAM_valid = 1;
        data->Force_Parser_Context = 0;
        data->Force_Parser_Context_valid = 1;
        data->Force_Parser_Context_Value = "Eth_B1";
        data->Force_Parser_Context_Value_valid = 1;
        data->Labels_To_Terminate = 1;
        data->Labels_To_Terminate_valid = 1;
        data->PHB_Compare_Strength = 0;
        data->PHB_Compare_Strength_valid = 1;
        data->PHB_Propagation_Strength = 0;
        data->PHB_Propagation_Strength_valid = 1;
        data->Qos_Mapping_Profile = 0;
        data->Qos_Mapping_Profile_valid = 1;
        data->Remark_Compare_Strength = 0;
        data->Remark_Compare_Strength_valid = 1;
        data->Remark_Propagation_Strength = 0;
        data->Remark_Propagation_Strength_valid = 1;
        data->Special_After_Tunnel = 1;
        data->Special_After_Tunnel_valid = 1;
        data->Special_Before_Tunnel = 0;
        data->Special_Before_Tunnel_valid = 1;
        data->TTL_Compare_Strength = 0;
        data->TTL_Compare_Strength_valid = 1;
        data->TTL_Propagation_Strength = 0;
        data->TTL_Propagation_Strength_valid = 1;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->valid = 1;
        data->VTT_MPLS_Special_Label_Profile = "GAL";
        data->VTT_MPLS_Special_Label_Profile_mask = 0;
        data->VTT_MPLS_Special_Label_Profile_valid = 1;
        data->Check_Bos = 0;
        data->Check_Bos_valid = 1;
        data->ECN_Compare_Strength = 0;
        data->ECN_Compare_Strength_valid = 1;
        data->ECN_Mapping_Profile = 0;
        data->ECN_Mapping_Profile_valid = 1;
        data->ECN_Propagation_Strength = 0;
        data->ECN_Propagation_Strength_valid = 1;
        data->Expected_Bos = 0;
        data->Expected_Bos_valid = 1;
        data->Force_Has_CW = 1;
        data->Force_Has_CW_valid = 1;
        data->Force_Is_OAM = 0;
        data->Force_Is_OAM_valid = 1;
        data->Force_Parser_Context = 0;
        data->Force_Parser_Context_valid = 1;
        data->Force_Parser_Context_Value = "Eth_B1";
        data->Force_Parser_Context_Value_valid = 1;
        data->Labels_To_Terminate = 0;
        data->Labels_To_Terminate_valid = 1;
        data->PHB_Compare_Strength = 0;
        data->PHB_Compare_Strength_valid = 1;
        data->PHB_Propagation_Strength = 0;
        data->PHB_Propagation_Strength_valid = 1;
        data->Qos_Mapping_Profile = 0;
        data->Qos_Mapping_Profile_valid = 1;
        data->Remark_Compare_Strength = 0;
        data->Remark_Compare_Strength_valid = 1;
        data->Remark_Propagation_Strength = 0;
        data->Remark_Propagation_Strength_valid = 1;
        data->Special_After_Tunnel = 1;
        data->Special_After_Tunnel_valid = 1;
        data->Special_Before_Tunnel = 0;
        data->Special_Before_Tunnel_valid = 1;
        data->TTL_Compare_Strength = 0;
        data->TTL_Compare_Strength_valid = 1;
        data->TTL_Propagation_Strength = 0;
        data->TTL_Propagation_Strength_valid = 1;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->valid = 1;
        data->VTT_MPLS_Special_Label_Profile = "OAM_Alert";
        data->VTT_MPLS_Special_Label_Profile_mask = 0;
        data->VTT_MPLS_Special_Label_Profile_valid = 1;
        data->Check_Bos = 1;
        data->Check_Bos_valid = 1;
        data->ECN_Compare_Strength = 0;
        data->ECN_Compare_Strength_valid = 1;
        data->ECN_Mapping_Profile = 0;
        data->ECN_Mapping_Profile_valid = 1;
        data->ECN_Propagation_Strength = 0;
        data->ECN_Propagation_Strength_valid = 1;
        data->Expected_Bos = 1;
        data->Expected_Bos_valid = 1;
        data->Force_Has_CW = 0;
        data->Force_Has_CW_valid = 1;
        data->Force_Is_OAM = 1;
        data->Force_Is_OAM_valid = 1;
        data->Force_Parser_Context = 0;
        data->Force_Parser_Context_valid = 1;
        data->Force_Parser_Context_Value = "Eth_B1";
        data->Force_Parser_Context_Value_valid = 1;
        data->Labels_To_Terminate = 0;
        data->Labels_To_Terminate_valid = 1;
        data->PHB_Compare_Strength = 0;
        data->PHB_Compare_Strength_valid = 1;
        data->PHB_Propagation_Strength = 0;
        data->PHB_Propagation_Strength_valid = 1;
        data->Qos_Mapping_Profile = 0;
        data->Qos_Mapping_Profile_valid = 1;
        data->Remark_Compare_Strength = 0;
        data->Remark_Compare_Strength_valid = 1;
        data->Remark_Propagation_Strength = 0;
        data->Remark_Propagation_Strength_valid = 1;
        data->Special_After_Tunnel = 1;
        data->Special_After_Tunnel_valid = 1;
        data->Special_Before_Tunnel = 0;
        data->Special_Before_Tunnel_valid = 1;
        data->TTL_Compare_Strength = 0;
        data->TTL_Compare_Strength_valid = 1;
        data->TTL_Propagation_Strength = 0;
        data->TTL_Propagation_Strength_valid = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}



shr_error_e
jr2_a0_standard_1_data_dnx2_aod_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_dnx2_aod;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_dnx2_aod_submodule_tables;
    submodule = &module->submodules[submodule_index];

    

    

    
    data_index = dnx_data_dnx2_aod_tables_table_ERPP_FWD_CONTEXT_FILTER___image;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER___image_set;
    data_index = dnx_data_dnx2_aod_tables_table_ERPP_FWD_CONTEXT_FILTER;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ERPP_FWD_CONTEXT_FILTER_set;
    data_index = dnx_data_dnx2_aod_tables_table_EGRESS_PER_FORWARD_CODE___image;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE___image_set;
    data_index = dnx_data_dnx2_aod_tables_table_EGRESS_PER_FORWARD_CODE;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PER_FORWARD_CODE_set;
    data_index = dnx_data_dnx2_aod_tables_table_ERPP_FORWARD_CODE_SELECTION___image;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION___image_set;
    data_index = dnx_data_dnx2_aod_tables_table_ERPP_FORWARD_CODE_SELECTION;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ERPP_FORWARD_CODE_SELECTION_set;
    data_index = dnx_data_dnx2_aod_tables_table_ETPP_FORWARD_CODE_SELECTION___image;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION___image_set;
    data_index = dnx_data_dnx2_aod_tables_table_ETPP_FORWARD_CODE_SELECTION;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_ETPP_FORWARD_CODE_SELECTION_set;
    data_index = dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_START_TYPE_CONTEXT___image;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT___image_set;
    data_index = dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_START_TYPE_CONTEXT;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PARSING_START_TYPE_CONTEXT_set;
    data_index = dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE___image;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE___image_set;
    data_index = dnx_data_dnx2_aod_tables_table_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_EGRESS_PARSING_CONTEXT_MAP_JR1_MODE_set;
    data_index = dnx_data_dnx2_aod_tables_table_FER_FILTERS_PER_FWD_CONTEXT___image;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT___image_set;
    data_index = dnx_data_dnx2_aod_tables_table_FER_FILTERS_PER_FWD_CONTEXT;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_FER_FILTERS_PER_FWD_CONTEXT_set;
    data_index = dnx_data_dnx2_aod_tables_table_INGRESS_PRT_INFO___image;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO___image_set;
    data_index = dnx_data_dnx2_aod_tables_table_INGRESS_PRT_INFO;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_INGRESS_PRT_INFO_set;
    data_index = dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_MAP___image;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP___image_set;
    data_index = dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_MAP;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_MAP_set;
    data_index = dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES___image;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES___image_set;
    data_index = dnx_data_dnx2_aod_tables_table_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_standard_1_dnx_data_dnx2_aod_tables_MPLS_SPECIAL_LABEL_PROFILE_ATTRIBUTES_set;

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


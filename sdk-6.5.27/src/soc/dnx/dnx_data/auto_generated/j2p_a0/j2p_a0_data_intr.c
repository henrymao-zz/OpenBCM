
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_INTR

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_intr.h>
#include <soc/dnx/intr/auto_generated/j2p/j2p_intr.h>
#include <soc/mcm/allenum.h>
#include <soc/dnxc/dnxc_intr_corr_act_func.h>








static shr_error_e
j2p_a0_dnx_data_intr_general_nof_interrupts_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_general;
    int define_index = dnx_data_intr_general_define_nof_interrupts;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = J2P_INT_LAST;

    
    define->data = J2P_INT_LAST;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_general_epni_ebd_interrupt_assert_enable_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_general;
    int define_index = dnx_data_intr_general_define_epni_ebd_interrupt_assert_enable;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_CUSTOM_FEATURE;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_enable;
    define->property.method_str = "suffix_enable";
    define->property.suffix = "epni_ebd_interrupt_assert_enable";

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
j2p_a0_dnx_data_intr_general_active_on_init_set(
    int unit)
{
    int offset_index;
    dnx_data_intr_general_active_on_init_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_general;
    int table_index = dnx_data_intr_general_table_active_on_init;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 545;
    table->info_get.key_size[0] = 545;

    
    table->values[0].default_val = "INVALIDr";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_general_active_on_init_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_general_table_active_on_init");

    
    default_data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->intr = INVALIDr;
    
    for (offset_index = 0; offset_index < table->keys[0].size; offset_index++)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, offset_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->intr = J2P_INT_BDM_ERROR_ECC;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->intr = J2P_INT_CDB_ERROR_ECC;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->intr = J2P_INT_CDB_NBI_PKT_DROP_COUNTERS_0_75P_INTERRUPT;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->intr = J2P_INT_CDBM_ERROR_ECC;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->intr = J2P_INT_CDBM_NBI_PKT_DROP_COUNTERS_0_75P_INTERRUPT;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->intr = J2P_INT_CDPM_LINK_STATUS_CHANGE_INT;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->intr = J2P_INT_CFC_ERROR_ECC;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->intr = J2P_INT_CGM_ERROR_ECC;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->intr = J2P_INT_CGM_VOQ_OCCUPANCY_ERR_INT;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->intr = J2P_INT_CGM_VSQ_OCCUPANCY_ERR_INT;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->intr = J2P_INT_CGM_VOQ_TOTAL_OCCUPANCY_ERR_INT;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->intr = J2P_INT_CGM_VSQ_TOTAL_OCCUPANCY_ERR_INT;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->intr = J2P_INT_CGM_CONGESTION_INT;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->intr = J2P_INT_CGM_LOW_PRIORITY_INT;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->intr = J2P_INT_CGM_FIFO_ERR_INT;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->intr = J2P_INT_CRPS_ERROR_ECC;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->intr = J2P_INT_CRPS_ERROR_LM_COLLIDE;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->intr = J2P_INT_CRPS_ERROR_COUNTER_OVF;
    }
    if (18 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->intr = J2P_INT_CRPS_DMA_0_FULLNESS_EVENT;
    }
    if (19 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->intr = J2P_INT_CRPS_DMA_1_FULLNESS_EVENT;
    }
    if (20 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 0);
        data->intr = J2P_INT_CRPS_CONDITIONAL_TRIGGER_OCCURED;
    }
    if (21 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 21, 0);
        data->intr = J2P_INT_CRPS_CONDITIONAL_TRIGGER_WHILE_FIFO_IS_FULL;
    }
    if (22 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 22, 0);
        data->intr = J2P_INT_CRPS_DUAL_CNTR_SCAN_EVICTION_TO_IRE_CONFLICTS;
    }
    if (23 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 23, 0);
        data->intr = J2P_INT_CRPS_FIFOS_OVERFLOW;
    }
    if (24 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 24, 0);
        data->intr = J2P_INT_CRPS_FIFOS_UNDERFLOW;
    }
    if (25 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 25, 0);
        data->intr = J2P_INT_DDHA_ERROR_ECC;
    }
    if (26 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 26, 0);
        data->intr = J2P_INT_DDHB_ERROR_ECC;
    }
    if (27 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 27, 0);
        data->intr = J2P_INT_DDP_ERROR_ECC;
    }
    if (28 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 28, 0);
        data->intr = J2P_INT_DDP_ERROR_EXTERNAL_MEM;
    }
    if (29 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 29, 0);
        data->intr = J2P_INT_DDP_FIFO_ERROR;
    }
    if (30 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 30, 0);
        data->intr = J2P_INT_DDP_ERROR_ITE;
    }
    if (31 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 31, 0);
        data->intr = J2P_INT_DDP_ERROR_ITE_FIFO;
    }
    if (32 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 32, 0);
        data->intr = J2P_INT_DDP_ERROR_BDBC;
    }
    if (33 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 33, 0);
        data->intr = J2P_INT_DQM_ERROR_ECC;
    }
    if (34 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 34, 0);
        data->intr = J2P_INT_DQM_TX_FIFOS_ERR_INT;
    }
    if (35 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 35, 0);
        data->intr = J2P_INT_DQM_FIFO_ERR_INT;
    }
    if (36 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 36, 0);
        data->intr = J2P_INT_ECGM_ERROR_ECC;
    }
    if (37 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 37, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_INT_VEC;
    }
    if (38 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 38, 0);
        data->intr = J2P_INT_ECI_ERROR_ECC;
    }
    if (39 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 39, 0);
        data->intr = J2P_INT_EDB_ERROR_ECC;
    }
    if (40 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 40, 0);
        data->intr = J2P_INT_EPNI_ERROR_ECC;
    }
    if (41 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 41, 0);
        data->intr = J2P_INT_EPRE_ERROR_ECC;
    }
    if (42 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 42, 0);
        data->intr = J2P_INT_EPS_ERROR_ECC;
    }
    if (43 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 43, 0);
        data->intr = J2P_INT_EPS_FIFO_STATUS_INTERRUPT_REG;
    }
    if (44 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 44, 0);
        data->intr = J2P_INT_ERPP_ERROR_ECC;
    }
    if (45 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 45, 0);
        data->intr = J2P_INT_ERPP_ERPP_DISCARD_INT_VEC;
    }
    if (46 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 46, 0);
        data->intr = J2P_INT_ERPP_ERPP_DISCARD_INT_VEC_2;
    }
    if (47 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 47, 0);
        data->intr = J2P_INT_ESB_ERROR_ECC;
    }
    if (48 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 48, 0);
        data->intr = J2P_INT_ETPPA_ERROR_ECC;
    }
    if (49 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 49, 0);
        data->intr = J2P_INT_ETPPA_ETPP_PRP_INT_VEC;
    }
    if (50 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 50, 0);
        data->intr = J2P_INT_ETPPA_ETPPA_INT_VEC;
    }
    if (51 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 51, 0);
        data->intr = J2P_INT_ETPPB_ERROR_ECC;
    }
    if (52 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 52, 0);
        data->intr = J2P_INT_ETPPB_BTC_INT_VEC;
    }
    if (53 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 53, 0);
        data->intr = J2P_INT_ETPPB_ETPPB_INT_VEC;
    }
    if (54 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 54, 0);
        data->intr = J2P_INT_ETPPC_ERROR_ECC;
    }
    if (55 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 55, 0);
        data->intr = J2P_INT_ETPPC_ETPP_TERM_INT_VEC;
    }
    if (56 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 56, 0);
        data->intr = J2P_INT_ETPPC_ETPPC_INT_VEC;
    }
    if (57 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 57, 0);
        data->intr = J2P_INT_EVNT_ERROR_ECC;
    }
    if (58 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 58, 0);
        data->intr = J2P_INT_EVNT_EVENTOR_INTERRUPT;
    }
    if (59 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 59, 0);
        data->intr = J2P_INT_FCR_ERROR_ECC;
    }
    if (60 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 60, 0);
        data->intr = J2P_INT_FCT_ERROR_ECC;
    }
    if (61 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 61, 0);
        data->intr = J2P_INT_FDA_ERROR_ECC;
    }
    if (62 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 62, 0);
        data->intr = J2P_INT_FDR_ERROR_ECC;
    }
    if (63 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 63, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_0;
    }
    if (64 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 64, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_0;
    }
    if (65 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 65, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_1;
    }
    if (66 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 66, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_1;
    }
    if (67 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 67, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_2;
    }
    if (68 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 68, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_2;
    }
    if (69 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 69, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_3;
    }
    if (70 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 70, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_3;
    }
    if (71 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 71, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_4;
    }
    if (72 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 72, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_4;
    }
    if (73 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 73, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_5;
    }
    if (74 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 74, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_5;
    }
    if (75 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 75, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_6;
    }
    if (76 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 76, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_6;
    }
    if (77 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 77, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_7;
    }
    if (78 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 78, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_7;
    }
    if (79 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 79, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_8;
    }
    if (80 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 80, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_8;
    }
    if (81 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 81, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_9;
    }
    if (82 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 82, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_9;
    }
    if (83 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 83, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_10;
    }
    if (84 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 84, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_10;
    }
    if (85 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 85, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_1_MAC_11;
    }
    if (86 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 86, 0);
        data->intr = J2P_INT_FDR_INT_REG_P_2_MAC_11;
    }
    if (87 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 87, 0);
        data->intr = J2P_INT_FDR_INT_REG_GENERAL;
    }
    if (88 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 88, 0);
        data->intr = J2P_INT_FDT_ERROR_ECC;
    }
    if (89 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 89, 0);
        data->intr = J2P_INT_FDTL_ERROR_ECC;
    }
    if (90 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 90, 0);
        data->intr = J2P_INT_FMAC_ERROR_ECC;
    }
    if (91 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 91, 0);
        data->intr = J2P_INT_FMAC_INT_REG_1;
    }
    if (92 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 92, 0);
        data->intr = J2P_INT_FMAC_INT_REG_2;
    }
    if (93 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 93, 0);
        data->intr = J2P_INT_FMAC_INT_REG_3;
    }
    if (94 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 94, 0);
        data->intr = J2P_INT_FMAC_INT_REG_4;
    }
    if (95 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 95, 0);
        data->intr = J2P_INT_FMAC_INT_REG_5;
    }
    if (96 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 96, 0);
        data->intr = J2P_INT_FMAC_INT_REG_6;
    }
    if (97 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 97, 0);
        data->intr = J2P_INT_FMAC_INT_REG_7;
    }
    if (98 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 98, 0);
        data->intr = J2P_INT_FMAC_INT_REG_8;
    }
    if (99 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 99, 0);
        data->intr = J2P_INT_FMAC_INT_REG_9;
    }
    if (100 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 100, 0);
        data->intr = J2P_INT_FQP_ERROR_ECC;
    }
    if (101 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 101, 0);
        data->intr = J2P_INT_FSRD_ERROR_ECC;
    }
    if (102 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 102, 0);
        data->intr = J2P_INT_FSRD_INT_REG_0;
    }
    if (103 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 103, 0);
        data->intr = J2P_INT_HBC_ERROR_ECC;
    }
    if (104 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 104, 0);
        data->intr = J2P_INT_HBC_DSI_ERROR;
    }
    if (105 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 105, 0);
        data->intr = J2P_INT_HBC_RDR_ERROR;
    }
    if (106 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 106, 0);
        data->intr = J2P_INT_HBC_PIPELINES_ERROR;
    }
    if (107 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 107, 0);
        data->intr = J2P_INT_HBMC_ERROR_ECC;
    }
    if (108 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 108, 0);
        data->intr = J2P_INT_HRC_ERROR_ECC;
    }
    if (109 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 109, 0);
        data->intr = J2P_INT_ILE_ERROR_ECC;
    }
    if (110 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 110, 0);
        data->intr = J2P_INT_IPPA_ERROR_ECC;
    }
    if (111 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 111, 0);
        data->intr = J2P_INT_IPPB_ERROR_ECC;
    }
    if (112 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 112, 0);
        data->intr = J2P_INT_IPPB_LEL_INTERRUPT_REGISTER_ONE;
    }
    if (113 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 113, 0);
        data->intr = J2P_INT_IPPC_ERROR_ECC;
    }
    if (114 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 114, 0);
        data->intr = J2P_INT_IPPD_ERROR_ECC;
    }
    if (115 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 115, 0);
        data->intr = J2P_INT_IPPE_ERROR_ECC;
    }
    if (116 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 116, 0);
        data->intr = J2P_INT_IPPF_ERROR_ECC;
    }
    if (117 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 117, 0);
        data->intr = J2P_INT_IPS_ERROR_ECC;
    }
    if (118 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 118, 0);
        data->intr = J2P_INT_IPS_ACTIVE_QUEUE_COUNT_ERR_INT;
    }
    if (119 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 119, 0);
        data->intr = J2P_INT_IPS_FIFO_ERR_INT;
    }
    if (120 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 120, 0);
        data->intr = J2P_INT_IPT_ERROR_ECC;
    }
    if (121 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 121, 0);
        data->intr = J2P_INT_IPT_ERROR_FIFOS;
    }
    if (122 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 122, 0);
        data->intr = J2P_INT_IPT_ERROR_ITE;
    }
    if (123 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 123, 0);
        data->intr = J2P_INT_IPT_ERROR_ITE_FIFO;
    }
    if (124 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 124, 0);
        data->intr = J2P_INT_IQM_ERROR_ECC;
    }
    if (125 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 125, 0);
        data->intr = J2P_INT_IQM_FIFO_ERR_INT;
    }
    if (126 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 126, 0);
        data->intr = J2P_INT_IRE_ERROR_ECC;
    }
    if (127 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 127, 0);
        data->intr = J2P_INT_IRE_RCY_INTERFACE_ERROR;
    }
    if (128 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 128, 0);
        data->intr = J2P_INT_IRE_INTERNAL_INTERFACE_ERROR;
    }
    if (129 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 129, 0);
        data->intr = J2P_INT_IRE_NIF_ERROR;
    }
    if (130 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 130, 0);
        data->intr = J2P_INT_IRE_FIFO_ERROR;
    }
    if (131 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 131, 0);
        data->intr = J2P_INT_ITPP_ERROR_ECC;
    }
    if (132 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 132, 0);
        data->intr = J2P_INT_ITPPD_ERROR_ECC;
    }
    if (133 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 133, 0);
        data->intr = J2P_INT_KAPS_ERROR_ECC;
    }
    if (134 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 134, 0);
        data->intr = J2P_INT_MACT_ERROR_ECC;
    }
    if (135 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 135, 0);
        data->intr = J2P_INT_MACT_LOCAL_MACT_INT;
    }
    if (136 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 136, 0);
        data->intr = J2P_INT_MCP_ERROR_ECC;
    }
    if (137 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 137, 0);
        data->intr = J2P_INT_MDB_ERROR_ECC;
    }
    if (138 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 138, 0);
        data->intr = J2P_INT_MRPS_ERROR_ECC;
    }
    if (139 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 139, 0);
        data->intr = J2P_INT_MRPS_INGRESS_ENG_WRAP_ERR_INT;
    }
    if (140 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 140, 0);
        data->intr = J2P_INT_MRPS_EGRESS_ENG_WRAP_ERR_INT;
    }
    if (141 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 141, 0);
        data->intr = J2P_INT_MRPS_INGRESS_ENG_OOP_FIFO_NOT_EMPTY_INT;
    }
    if (142 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 142, 0);
        data->intr = J2P_INT_MRPS_EGRESS_ENG_OOP_FIFO_NOT_EMPTY_INT;
    }
    if (143 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 143, 0);
        data->intr = J2P_INT_MSD_MACSEC_INT;
    }
    if (144 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 144, 0);
        data->intr = J2P_INT_MSS_MACSEC_INT;
    }
    if (145 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 145, 0);
        data->intr = J2P_INT_MTM_ERROR_ECC;
    }
    if (146 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 146, 0);
        data->intr = J2P_INT_MTM_FIFO_STATUS_INTERRUPT_REG_0;
    }
    if (147 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 147, 0);
        data->intr = J2P_INT_MTM_FIFO_STATUS_INTERRUPT_REG_1;
    }
    if (148 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 148, 0);
        data->intr = J2P_INT_MTM_FIFO_STATUS_INTERRUPT_REG_2;
    }
    if (149 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 149, 0);
        data->intr = J2P_INT_NMG_ERROR_ECC;
    }
    if (150 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 150, 0);
        data->intr = J2P_INT_OAMP_ERROR_ECC;
    }
    if (151 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 151, 0);
        data->intr = J2P_INT_OCB_ERROR_ECC;
    }
    if (152 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 152, 0);
        data->intr = J2P_INT_OCBM_ERROR_ECC;
    }
    if (153 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 153, 0);
        data->intr = J2P_INT_OCBM_ERROR_FBC_BANK;
    }
    if (154 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 154, 0);
        data->intr = J2P_INT_OCBM_ERROR_FIFO_INT;
    }
    if (155 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 155, 0);
        data->intr = J2P_INT_OLP_ERROR_ECC;
    }
    if (156 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 156, 0);
        data->intr = J2P_INT_PDM_ERROR_ECC;
    }
    if (157 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 157, 0);
        data->intr = J2P_INT_PEM_ERROR_ECC;
    }
    if (158 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 158, 0);
        data->intr = J2P_INT_PQP_ERROR_ECC;
    }
    if (159 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 159, 0);
        data->intr = J2P_INT_PQP_FIFO_STATUS_INTERRUPT_REG;
    }
    if (160 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 160, 0);
        data->intr = J2P_INT_RQP_ERROR_ECC;
    }
    if (161 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 161, 0);
        data->intr = J2P_INT_RQP_PKT_REAS_INT_VEC;
    }
    if (162 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 162, 0);
        data->intr = J2P_INT_RTP_ERROR_ECC;
    }
    if (163 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 163, 0);
        data->intr = J2P_INT_SCH_ERROR_ECC;
    }
    if (164 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 164, 0);
        data->intr = J2P_INT_SIF_ERROR_ECC;
    }
    if (165 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 165, 0);
        data->intr = J2P_INT_SIF_STATISTICS_BILLING_FIFOS_ERR_INT;
    }
    if (166 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 166, 0);
        data->intr = J2P_INT_SIF_STATISTICS_QSIZE_FIFOS_ERR_INT;
    }
    if (167 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 167, 0);
        data->intr = J2P_INT_SIF_STATISTICS_BILLING_OPCODE_ERR_INT;
    }
    if (168 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 168, 0);
        data->intr = J2P_INT_SPB_ERROR_ECC;
    }
    if (169 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 169, 0);
        data->intr = J2P_INT_SPB_ERROR_REASSEMBLY;
    }
    if (170 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 170, 0);
        data->intr = J2P_INT_SPB_ERROR_FIFO;
    }
    if (171 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 171, 0);
        data->intr = J2P_INT_SPB_FIFO_ERROR;
    }
    if (172 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 172, 0);
        data->intr = J2P_INT_SQM_ERROR_ECC;
    }
    if (173 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 173, 0);
        data->intr = J2P_INT_SQM_TX_FIFOS_ERR_INT;
    }
    if (174 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 174, 0);
        data->intr = J2P_INT_SQM_FIFO_ERR_INT;
    }
    if (175 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 175, 0);
        data->intr = J2P_INT_TCAM_ERROR_ECC;
    }
    if (176 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 176, 0);
        data->intr = J2P_INT_TDU_ERROR_ECC;
    }
    if (177 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 177, 0);
        data->intr = J2P_INT_CDB_ECC_PARITY_ERR_INT;
    }
    if (178 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 178, 0);
        data->intr = J2P_INT_CDBM_ECC_PARITY_ERR_INT;
    }
    if (179 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 179, 0);
        data->intr = J2P_INT_ERPP_ECC_PARITY_ERR_INT;
    }
    if (180 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 180, 0);
        data->intr = J2P_INT_ETPPA_ECC_PARITY_ERR_INT;
    }
    if (181 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 181, 0);
        data->intr = J2P_INT_ETPPB_ECC_PARITY_ERR_INT;
    }
    if (182 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 182, 0);
        data->intr = J2P_INT_ETPPC_ECC_PARITY_ERR_INT;
    }
    if (183 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 183, 0);
        data->intr = J2P_INT_HBC_ECC_PARITY_ERR_INT;
    }
    if (184 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 184, 0);
        data->intr = J2P_INT_IPPA_ECC_PARITY_ERR_INT;
    }
    if (185 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 185, 0);
        data->intr = J2P_INT_IPPB_ECC_PARITY_ERR_INT;
    }
    if (186 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 186, 0);
        data->intr = J2P_INT_IPPC_ECC_PARITY_ERR_INT;
    }
    if (187 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 187, 0);
        data->intr = J2P_INT_IPPD_ECC_PARITY_ERR_INT;
    }
    if (188 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 188, 0);
        data->intr = J2P_INT_IPPE_ECC_PARITY_ERR_INT;
    }
    if (189 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 189, 0);
        data->intr = J2P_INT_IPPF_ECC_PARITY_ERR_INT;
    }
    if (190 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 190, 0);
        data->intr = J2P_INT_IRE_ECC_PARITY_ERR_INT;
    }
    if (191 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 191, 0);
        data->intr = J2P_INT_MDB_ECC_PARITY_ERR_INT;
    }
    if (192 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 192, 0);
        data->intr = J2P_INT_RQP_ECC_PARITY_ERR_INT;
    }
    if (193 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 193, 0);
        data->intr = J2P_INT_SCH_ECC_PARITY_ERR_INT;
    }
    if (194 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 194, 0);
        data->intr = J2P_INT_SPB_ECC_PARITY_ERR_INT;
    }
    if (195 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 195, 0);
        data->intr = J2P_INT_BDM_ECC_ECC_1B_ERR_INT;
    }
    if (196 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 196, 0);
        data->intr = J2P_INT_CDB_ECC_ECC_1B_ERR_INT;
    }
    if (197 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 197, 0);
        data->intr = J2P_INT_CDBM_ECC_ECC_1B_ERR_INT;
    }
    if (198 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 198, 0);
        data->intr = J2P_INT_CFC_ECC_ECC_1B_ERR_INT;
    }
    if (199 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 199, 0);
        data->intr = J2P_INT_CGM_ECC_ECC_1B_ERR_INT;
    }
    if (200 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 200, 0);
        data->intr = J2P_INT_CRPS_ECC_ECC_1B_ERR_INT;
    }
    if (201 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 201, 0);
        data->intr = J2P_INT_DDHA_ECC_ECC_1B_ERR_INT;
    }
    if (202 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 202, 0);
        data->intr = J2P_INT_DDHB_ECC_ECC_1B_ERR_INT;
    }
    if (203 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 203, 0);
        data->intr = J2P_INT_DDP_ECC_ECC_1B_ERR_INT;
    }
    if (204 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 204, 0);
        data->intr = J2P_INT_DQM_ECC_ECC_1B_ERR_INT;
    }
    if (205 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 205, 0);
        data->intr = J2P_INT_ECGM_ECC_ECC_1B_ERR_INT;
    }
    if (206 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 206, 0);
        data->intr = J2P_INT_ECI_ECC_ECC_1B_ERR_INT;
    }
    if (207 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 207, 0);
        data->intr = J2P_INT_EDB_ECC_ECC_1B_ERR_INT;
    }
    if (208 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 208, 0);
        data->intr = J2P_INT_EPNI_ECC_ECC_1B_ERR_INT;
    }
    if (209 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 209, 0);
        data->intr = J2P_INT_EPRE_ECC_ECC_1B_ERR_INT;
    }
    if (210 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 210, 0);
        data->intr = J2P_INT_EPS_ECC_ECC_1B_ERR_INT;
    }
    if (211 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 211, 0);
        data->intr = J2P_INT_ERPP_ECC_ECC_1B_ERR_INT;
    }
    if (212 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 212, 0);
        data->intr = J2P_INT_ESB_ECC_ECC_1B_ERR_INT;
    }
    if (213 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 213, 0);
        data->intr = J2P_INT_ETPPA_ECC_ECC_1B_ERR_INT;
    }
    if (214 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 214, 0);
        data->intr = J2P_INT_ETPPB_ECC_ECC_1B_ERR_INT;
    }
    if (215 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 215, 0);
        data->intr = J2P_INT_ETPPC_ECC_ECC_1B_ERR_INT;
    }
    if (216 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 216, 0);
        data->intr = J2P_INT_EVNT_ECC_ECC_1B_ERR_INT;
    }
    if (217 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 217, 0);
        data->intr = J2P_INT_FCR_ECC_ECC_1B_ERR_INT;
    }
    if (218 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 218, 0);
        data->intr = J2P_INT_FCT_ECC_ECC_1B_ERR_INT;
    }
    if (219 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 219, 0);
        data->intr = J2P_INT_FDA_ECC_ECC_1B_ERR_INT;
    }
    if (220 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 220, 0);
        data->intr = J2P_INT_FDR_ECC_ECC_1B_ERR_INT;
    }
    if (221 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 221, 0);
        data->intr = J2P_INT_FDT_ECC_ECC_1B_ERR_INT;
    }
    if (222 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 222, 0);
        data->intr = J2P_INT_FDTL_ECC_ECC_1B_ERR_INT;
    }
    if (223 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 223, 0);
        data->intr = J2P_INT_FMAC_ECC_ECC_1B_ERR_INT;
    }
    if (224 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 224, 0);
        data->intr = J2P_INT_FQP_ECC_ECC_1B_ERR_INT;
    }
    if (225 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 225, 0);
        data->intr = J2P_INT_HBC_ECC_ECC_1B_ERR_INT;
    }
    if (226 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 226, 0);
        data->intr = J2P_INT_HRC_ECC_ECC_1B_ERR_INT;
    }
    if (227 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 227, 0);
        data->intr = J2P_INT_ILE_ECC_ECC_1B_ERR_INT;
    }
    if (228 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 228, 0);
        data->intr = J2P_INT_IPPA_ECC_ECC_1B_ERR_INT;
    }
    if (229 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 229, 0);
        data->intr = J2P_INT_IPPB_ECC_ECC_1B_ERR_INT;
    }
    if (230 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 230, 0);
        data->intr = J2P_INT_IPPC_ECC_ECC_1B_ERR_INT;
    }
    if (231 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 231, 0);
        data->intr = J2P_INT_IPPD_ECC_ECC_1B_ERR_INT;
    }
    if (232 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 232, 0);
        data->intr = J2P_INT_IPPE_ECC_ECC_1B_ERR_INT;
    }
    if (233 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 233, 0);
        data->intr = J2P_INT_IPPF_ECC_ECC_1B_ERR_INT;
    }
    if (234 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 234, 0);
        data->intr = J2P_INT_IPS_ECC_ECC_1B_ERR_INT;
    }
    if (235 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 235, 0);
        data->intr = J2P_INT_IPT_ECC_ECC_1B_ERR_INT;
    }
    if (236 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 236, 0);
        data->intr = J2P_INT_IQM_ECC_ECC_1B_ERR_INT;
    }
    if (237 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 237, 0);
        data->intr = J2P_INT_IRE_ECC_ECC_1B_ERR_INT;
    }
    if (238 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 238, 0);
        data->intr = J2P_INT_ITPP_ECC_ECC_1B_ERR_INT;
    }
    if (239 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 239, 0);
        data->intr = J2P_INT_ITPPD_ECC_ECC_1B_ERR_INT;
    }
    if (240 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 240, 0);
        data->intr = J2P_INT_KAPS_ECC_ECC_1B_ERR_INT;
    }
    if (241 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 241, 0);
        data->intr = J2P_INT_MACT_ECC_ECC_1B_ERR_INT;
    }
    if (242 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 242, 0);
        data->intr = J2P_INT_MCP_ECC_ECC_1B_ERR_INT;
    }
    if (243 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 243, 0);
        data->intr = J2P_INT_MDB_ECC_ECC_1B_ERR_INT;
    }
    if (244 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 244, 0);
        data->intr = J2P_INT_MRPS_ECC_ECC_1B_ERR_INT;
    }
    if (245 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 245, 0);
        data->intr = J2P_INT_MTM_ECC_ECC_1B_ERR_INT;
    }
    if (246 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 246, 0);
        data->intr = J2P_INT_NMG_ECC_ECC_1B_ERR_INT;
    }
    if (247 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 247, 0);
        data->intr = J2P_INT_OAMP_ECC_ECC_1B_ERR_INT;
    }
    if (248 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 248, 0);
        data->intr = J2P_INT_OCB_ECC_ECC_1B_ERR_INT;
    }
    if (249 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 249, 0);
        data->intr = J2P_INT_OCBM_ECC_ECC_1B_ERR_INT;
    }
    if (250 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 250, 0);
        data->intr = J2P_INT_OLP_ECC_ECC_1B_ERR_INT;
    }
    if (251 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 251, 0);
        data->intr = J2P_INT_PDM_ECC_ECC_1B_ERR_INT;
    }
    if (252 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 252, 0);
        data->intr = J2P_INT_PEM_ECC_ECC_1B_ERR_INT;
    }
    if (253 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 253, 0);
        data->intr = J2P_INT_PQP_ECC_ECC_1B_ERR_INT;
    }
    if (254 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 254, 0);
        data->intr = J2P_INT_RQP_ECC_ECC_1B_ERR_INT;
    }
    if (255 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 255, 0);
        data->intr = J2P_INT_RTP_ECC_ECC_1B_ERR_INT;
    }
    if (256 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 256, 0);
        data->intr = J2P_INT_SCH_ECC_ECC_1B_ERR_INT;
    }
    if (257 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 257, 0);
        data->intr = J2P_INT_SIF_ECC_ECC_1B_ERR_INT;
    }
    if (258 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 258, 0);
        data->intr = J2P_INT_SPB_ECC_ECC_1B_ERR_INT;
    }
    if (259 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 259, 0);
        data->intr = J2P_INT_SQM_ECC_ECC_1B_ERR_INT;
    }
    if (260 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 260, 0);
        data->intr = J2P_INT_TCAM_ECC_ECC_1B_ERR_INT;
    }
    if (261 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 261, 0);
        data->intr = J2P_INT_TDU_ECC_ECC_1B_ERR_INT;
    }
    if (262 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 262, 0);
        data->intr = J2P_INT_BDM_ECC_ECC_2B_ERR_INT;
    }
    if (263 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 263, 0);
        data->intr = J2P_INT_CDB_ECC_ECC_2B_ERR_INT;
    }
    if (264 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 264, 0);
        data->intr = J2P_INT_CDBM_ECC_ECC_2B_ERR_INT;
    }
    if (265 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 265, 0);
        data->intr = J2P_INT_CFC_ECC_ECC_2B_ERR_INT;
    }
    if (266 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 266, 0);
        data->intr = J2P_INT_CGM_ECC_ECC_2B_ERR_INT;
    }
    if (267 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 267, 0);
        data->intr = J2P_INT_CRPS_ECC_ECC_2B_ERR_INT;
    }
    if (268 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 268, 0);
        data->intr = J2P_INT_DDHA_ECC_ECC_2B_ERR_INT;
    }
    if (269 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 269, 0);
        data->intr = J2P_INT_DDHB_ECC_ECC_2B_ERR_INT;
    }
    if (270 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 270, 0);
        data->intr = J2P_INT_DDP_ECC_ECC_2B_ERR_INT;
    }
    if (271 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 271, 0);
        data->intr = J2P_INT_DQM_ECC_ECC_2B_ERR_INT;
    }
    if (272 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 272, 0);
        data->intr = J2P_INT_ECGM_ECC_ECC_2B_ERR_INT;
    }
    if (273 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 273, 0);
        data->intr = J2P_INT_ECI_ECC_ECC_2B_ERR_INT;
    }
    if (274 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 274, 0);
        data->intr = J2P_INT_EDB_ECC_ECC_2B_ERR_INT;
    }
    if (275 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 275, 0);
        data->intr = J2P_INT_EPNI_ECC_ECC_2B_ERR_INT;
    }
    if (276 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 276, 0);
        data->intr = J2P_INT_EPRE_ECC_ECC_2B_ERR_INT;
    }
    if (277 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 277, 0);
        data->intr = J2P_INT_EPS_ECC_ECC_2B_ERR_INT;
    }
    if (278 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 278, 0);
        data->intr = J2P_INT_ERPP_ECC_ECC_2B_ERR_INT;
    }
    if (279 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 279, 0);
        data->intr = J2P_INT_ESB_ECC_ECC_2B_ERR_INT;
    }
    if (280 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 280, 0);
        data->intr = J2P_INT_ETPPA_ECC_ECC_2B_ERR_INT;
    }
    if (281 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 281, 0);
        data->intr = J2P_INT_ETPPB_ECC_ECC_2B_ERR_INT;
    }
    if (282 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 282, 0);
        data->intr = J2P_INT_ETPPC_ECC_ECC_2B_ERR_INT;
    }
    if (283 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 283, 0);
        data->intr = J2P_INT_EVNT_ECC_ECC_2B_ERR_INT;
    }
    if (284 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 284, 0);
        data->intr = J2P_INT_FCR_ECC_ECC_2B_ERR_INT;
    }
    if (285 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 285, 0);
        data->intr = J2P_INT_FCT_ECC_ECC_2B_ERR_INT;
    }
    if (286 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 286, 0);
        data->intr = J2P_INT_FDA_ECC_ECC_2B_ERR_INT;
    }
    if (287 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 287, 0);
        data->intr = J2P_INT_FDR_ECC_ECC_2B_ERR_INT;
    }
    if (288 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 288, 0);
        data->intr = J2P_INT_FDT_ECC_ECC_2B_ERR_INT;
    }
    if (289 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 289, 0);
        data->intr = J2P_INT_FDTL_ECC_ECC_2B_ERR_INT;
    }
    if (290 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 290, 0);
        data->intr = J2P_INT_FMAC_ECC_ECC_2B_ERR_INT;
    }
    if (291 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 291, 0);
        data->intr = J2P_INT_FQP_ECC_ECC_2B_ERR_INT;
    }
    if (292 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 292, 0);
        data->intr = J2P_INT_HBC_ECC_ECC_2B_ERR_INT;
    }
    if (293 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 293, 0);
        data->intr = J2P_INT_HRC_ECC_ECC_2B_ERR_INT;
    }
    if (294 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 294, 0);
        data->intr = J2P_INT_ILE_ECC_ECC_2B_ERR_INT;
    }
    if (295 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 295, 0);
        data->intr = J2P_INT_IPPA_ECC_ECC_2B_ERR_INT;
    }
    if (296 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 296, 0);
        data->intr = J2P_INT_IPPB_ECC_ECC_2B_ERR_INT;
    }
    if (297 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 297, 0);
        data->intr = J2P_INT_IPPC_ECC_ECC_2B_ERR_INT;
    }
    if (298 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 298, 0);
        data->intr = J2P_INT_IPPD_ECC_ECC_2B_ERR_INT;
    }
    if (299 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 299, 0);
        data->intr = J2P_INT_IPPE_ECC_ECC_2B_ERR_INT;
    }
    if (300 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 300, 0);
        data->intr = J2P_INT_IPPF_ECC_ECC_2B_ERR_INT;
    }
    if (301 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 301, 0);
        data->intr = J2P_INT_IPS_ECC_ECC_2B_ERR_INT;
    }
    if (302 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 302, 0);
        data->intr = J2P_INT_IPT_ECC_ECC_2B_ERR_INT;
    }
    if (303 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 303, 0);
        data->intr = J2P_INT_IQM_ECC_ECC_2B_ERR_INT;
    }
    if (304 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 304, 0);
        data->intr = J2P_INT_IRE_ECC_ECC_2B_ERR_INT;
    }
    if (305 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 305, 0);
        data->intr = J2P_INT_ITPP_ECC_ECC_2B_ERR_INT;
    }
    if (306 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 306, 0);
        data->intr = J2P_INT_ITPPD_ECC_ECC_2B_ERR_INT;
    }
    if (307 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 307, 0);
        data->intr = J2P_INT_KAPS_ECC_ECC_2B_ERR_INT;
    }
    if (308 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 308, 0);
        data->intr = J2P_INT_MACT_ECC_ECC_2B_ERR_INT;
    }
    if (309 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 309, 0);
        data->intr = J2P_INT_MCP_ECC_ECC_2B_ERR_INT;
    }
    if (310 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 310, 0);
        data->intr = J2P_INT_MDB_ECC_ECC_2B_ERR_INT;
    }
    if (311 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 311, 0);
        data->intr = J2P_INT_MRPS_ECC_ECC_2B_ERR_INT;
    }
    if (312 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 312, 0);
        data->intr = J2P_INT_MTM_ECC_ECC_2B_ERR_INT;
    }
    if (313 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 313, 0);
        data->intr = J2P_INT_NMG_ECC_ECC_2B_ERR_INT;
    }
    if (314 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 314, 0);
        data->intr = J2P_INT_OAMP_ECC_ECC_2B_ERR_INT;
    }
    if (315 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 315, 0);
        data->intr = J2P_INT_OCB_ECC_ECC_2B_ERR_INT;
    }
    if (316 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 316, 0);
        data->intr = J2P_INT_OCBM_ECC_ECC_2B_ERR_INT;
    }
    if (317 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 317, 0);
        data->intr = J2P_INT_OLP_ECC_ECC_2B_ERR_INT;
    }
    if (318 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 318, 0);
        data->intr = J2P_INT_PDM_ECC_ECC_2B_ERR_INT;
    }
    if (319 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 319, 0);
        data->intr = J2P_INT_PEM_ECC_ECC_2B_ERR_INT;
    }
    if (320 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 320, 0);
        data->intr = J2P_INT_PQP_ECC_ECC_2B_ERR_INT;
    }
    if (321 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 321, 0);
        data->intr = J2P_INT_RQP_ECC_ECC_2B_ERR_INT;
    }
    if (322 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 322, 0);
        data->intr = J2P_INT_RTP_ECC_ECC_2B_ERR_INT;
    }
    if (323 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 323, 0);
        data->intr = J2P_INT_SCH_ECC_ECC_2B_ERR_INT;
    }
    if (324 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 324, 0);
        data->intr = J2P_INT_SIF_ECC_ECC_2B_ERR_INT;
    }
    if (325 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 325, 0);
        data->intr = J2P_INT_SPB_ECC_ECC_2B_ERR_INT;
    }
    if (326 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 326, 0);
        data->intr = J2P_INT_SQM_ECC_ECC_2B_ERR_INT;
    }
    if (327 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 327, 0);
        data->intr = J2P_INT_TCAM_ECC_ECC_2B_ERR_INT;
    }
    if (328 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 328, 0);
        data->intr = J2P_INT_TDU_ECC_ECC_2B_ERR_INT;
    }
    if (329 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 329, 0);
        data->intr = J2P_INT_TCAM_TCAM_PROTECTION_ERROR_1_BIT_ECC;
    }
    if (330 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 330, 0);
        data->intr = J2P_INT_TCAM_TCAM_PROTECTION_ERROR_2_BIT_ECC;
    }
    if (331 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 331, 0);
        data->intr = J2P_INT_DDP_DELETE_BDB_FIFO_NOT_EMPTY;
    }
    if (332 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 332, 0);
        data->intr = J2P_INT_DDP_DELETE_BDB_FIFO_FULL;
    }
    if (333 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 333, 0);
        data->intr = J2P_INT_RQP_PKT_REAS_INT_VEC;
    }
    if (334 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 334, 0);
        data->intr = J2P_INT_MSS_MACSEC_MACSEC_INTERRUPT_REGISTER;
    }
    if (335 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 335, 0);
        data->intr = J2P_INT_MSD_MACSEC_MACSEC_INTERRUPT_REGISTER;
    }
    if (336 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 336, 0);
        data->intr = J2P_INT_EPNI_ETPP_TOTAL_INC_ABOVE_TH_WITH_EBD_INT;
    }
    if (337 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 337, 0);
        data->intr = J2P_INT_EPNI_ETPP_EBD_ERR_INT;
    }
    if (338 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 338, 0);
        data->intr = J2P_INT_ETPPB_BTC_HEADER_SIZE_EXCEED;
    }
    if (339 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 339, 0);
        data->intr = J2P_INT_ETPPB_BTC_NOF_INSTRUCTIONS_EXCEED;
    }
    if (340 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 340, 0);
        data->intr = J2P_INT_ETPPB_BTC_HEADER_SIZE_NOT_BYTE_ALLIGNED;
    }
    if (341 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 341, 0);
        data->intr = J2P_INT_EPNI_ETPP_SOP_DEC_ABOVE_TH_INT;
    }
    if (342 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 342, 0);
        data->intr = J2P_INT_EPNI_ETPP_EOP_DEC_ABOVE_TH_INT;
    }
    if (343 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 343, 0);
        data->intr = J2P_INT_EPNI_ETPP_EOP_AND_SOP_DEC_ABOVE_TH_INT;
    }
    if (344 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 344, 0);
        data->intr = J2P_INT_ILE_ILKN_RX_PORT_0_STATUS_CHANGE_INT;
    }
    if (345 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 345, 0);
        data->intr = J2P_INT_ILE_ILKN_RX_PORT_1_STATUS_CHANGE_INT;
    }
    if (346 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 346, 0);
        data->intr = J2P_INT_DDP_ERROR_PACKET_OVERSIZE;
    }
    if (347 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 347, 0);
        data->intr = J2P_INT_DDP_ERROR_DRAM_BUNDLE_OVERSIZE;
    }
    if (348 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 348, 0);
        data->intr = J2P_INT_DDP_ERROR_SRAM_16B_CNT_OVRF;
    }
    if (349 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 349, 0);
        data->intr = J2P_INT_DDP_ERROR_OMAC_CNT_OVRF;
    }
    if (350 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 350, 0);
        data->intr = J2P_INT_DDP_ERROR_UNPACK_PACKET_SIZE_ERROR;
    }
    if (351 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 351, 0);
        data->intr = J2P_INT_DDP_ERROR_UNPACK_PACKET_SIZE_MISMATCH;
    }
    if (352 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 352, 0);
        data->intr = J2P_INT_DDP_ERROR_UNPACK_BUNDLE_OVERFLOW_ERROR;
    }
    if (353 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 353, 0);
        data->intr = J2P_INT_DDP_DELETE_BDB_FIFO_FULL;
    }
    if (354 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 354, 0);
        data->intr = J2P_INT_DDP_DELETE_BDB_FIFO_NOT_EMPTY;
    }
    if (355 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 355, 0);
        data->intr = J2P_INT_DDP_EXT_MEM_ERR_PKUP_CPYDAT_ECC_1B_ERR_INT;
    }
    if (356 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 356, 0);
        data->intr = J2P_INT_DDP_EXT_MEM_ERR_PKUP_CPYDAT_ECC_2B_ERR_INT;
    }
    if (357 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 357, 0);
        data->intr = J2P_INT_DDP_EXT_MEM_ERR_PKUP_CPYDAT_CRC_ERR_INT;
    }
    if (358 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 358, 0);
        data->intr = J2P_INT_DDP_EXT_MEM_ERR_PKUP_PACKET_CRC_ERR_INT;
    }
    if (359 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 359, 0);
        data->intr = J2P_INT_DDP_EXT_MEM_ERR_BTC_TDU_ECC_1B_ERR_INT;
    }
    if (360 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 360, 0);
        data->intr = J2P_INT_DDP_EXT_MEM_ERR_BTC_TDU_ECC_2B_ERR_INT;
    }
    if (361 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 361, 0);
        data->intr = J2P_INT_DDP_EXT_MEM_ERR_PKUP_LAST_BUFF_CRC_ERR_INT;
    }
    if (362 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 362, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_RX_CFIF_OVERFLOW;
    }
    if (363 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 363, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_RX_CFIF_UNDERFLOW;
    }
    if (364 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 364, 0);
        data->intr = J2P_INT_DDP_FIFO_PKP_OUT_FIF_OVERFLOW;
    }
    if (365 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 365, 0);
        data->intr = J2P_INT_DDP_FIFO_BEC_PTR_FIFO_OVERFLOW;
    }
    if (366 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 366, 0);
        data->intr = J2P_INT_DDP_FIFO_BEC_PTR_FIFO_UNDERFLOW;
    }
    if (367 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 367, 0);
        data->intr = J2P_INT_DDP_FIFO_BEC_WAIT_FIFO_OVERFLOW;
    }
    if (368 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 368, 0);
        data->intr = J2P_INT_DDP_FIFO_BEC_WAIT_FIFO_UNDERFLOW;
    }
    if (369 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 369, 0);
        data->intr = J2P_INT_DDP_FIFO_BDBC_RESULT_FIF_OVERFLOW;
    }
    if (370 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 370, 0);
        data->intr = J2P_INT_DDP_FIFO_BDBC_RESULT_FIF_UNDERFLOW;
    }
    if (371 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 371, 0);
        data->intr = J2P_INT_DDP_FIFO_BDBC_SUB_REQ_FIF_OVERFLOW;
    }
    if (372 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 372, 0);
        data->intr = J2P_INT_DDP_FIFO_BDBC_SUB_REQ_FIF_UNDERFLOW;
    }
    if (373 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 373, 0);
        data->intr = J2P_INT_DDP_FIFO_BEC_ENQ_FIFO_OVERFLOW;
    }
    if (374 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 374, 0);
        data->intr = J2P_INT_DDP_FIFO_BEC_ENQ_FIFO_UNDERFLOW;
    }
    if (375 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 375, 0);
        data->intr = J2P_INT_DDP_FIFO_DBDF_OVERFLOW;
    }
    if (376 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 376, 0);
        data->intr = J2P_INT_DDP_FIFO_DBDF_UNDERFLOW;
    }
    if (377 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 377, 0);
        data->intr = J2P_INT_DDP_FIFO_PKP_RX_CFIF_OVERFLOW;
    }
    if (378 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 378, 0);
        data->intr = J2P_INT_DDP_FIFO_PKP_RX_CFIF_UNDERFLOW;
    }
    if (379 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 379, 0);
        data->intr = J2P_INT_DDP_FIFO_PKP_RX_DFIF_OVERFLOW;
    }
    if (380 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 380, 0);
        data->intr = J2P_INT_DDP_FIFO_PKP_RX_DFIF_UNDERFLOW;
    }
    if (381 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 381, 0);
        data->intr = J2P_INT_DDP_FIFO_WCF_OVERFLOW;
    }
    if (382 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 382, 0);
        data->intr = J2P_INT_DDP_FIFO_WCF_UNDERFLOW;
    }
    if (383 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 383, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_BDBC_PEND_FIF_OVERFLOW;
    }
    if (384 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 384, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_BDBC_PEND_FIF_UNDERFLOW;
    }
    if (385 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 385, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_END_OF_BUFFER_FIF_OVERFLOW;
    }
    if (386 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 386, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_END_OF_BUFFER_FIF_UNDERFLOW;
    }
    if (387 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 387, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_QUARANTINE_FIF_OVERFLOW;
    }
    if (388 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 388, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_QUARANTINE_FIF_UNDERFLOW;
    }
    if (389 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 389, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_RX_DFIF_OVERFLOW;
    }
    if (390 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 390, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_RX_DFIF_UNDERFLOW;
    }
    if (391 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 391, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_RX_METADATA_FIF_OVERFLOW;
    }
    if (392 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 392, 0);
        data->intr = J2P_INT_DDP_FIFO_PKUP_RX_METADATA_FIF_UNDERFLOW;
    }
    if (393 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 393, 0);
        data->intr = J2P_INT_DDP_ITE_ERR_FTMH_PKT_SIZE_IS_NOT_STAMPPED;
    }
    if (394 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 394, 0);
        data->intr = J2P_INT_DDP_ITE_ERR_FTMH_IS_NOT_STAMPPED;
    }
    if (395 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 395, 0);
        data->intr = J2P_INT_DDP_ITE_ERR_BYTES_TO_ADD_ABOVE_MAX;
    }
    if (396 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 396, 0);
        data->intr = J2P_INT_DDP_ITE_ERR_BYTES_TO_REMOVE_ABOVE_PSIZE;
    }
    if (397 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 397, 0);
        data->intr = J2P_INT_DDP_ITE_ERR_FTMH_PSIZE_MISMATCH;
    }
    if (398 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 398, 0);
        data->intr = J2P_INT_DDP_ITE_ERR_PSIZE_MISMATCH;
    }
    if (399 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 399, 0);
        data->intr = J2P_INT_DDP_ITE_ERR_EXPECTED_ITPP_DELTA_MISMATCH;
    }
    if (400 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 400, 0);
        data->intr = J2P_INT_DDP_ITE_ERR_NEGATIVE_DELTA;
    }
    if (401 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 401, 0);
        data->intr = J2P_INT_DDP_ITE_FIFO_BYPASS_FIFO_OVERFLOW;
    }
    if (402 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 402, 0);
        data->intr = J2P_INT_DDP_ITE_FIFO_BYPASS_FIFO_UNDERFLOW;
    }
    if (403 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 403, 0);
        data->intr = J2P_INT_DDP_ITE_FIFO_WDF_OVERFLOW;
    }
    if (404 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 404, 0);
        data->intr = J2P_INT_DDP_ITE_FIFO_WDF_UNDERFLOW;
    }
    if (405 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 405, 0);
        data->intr = J2P_INT_DDP_ITE_FIFO_WDF_CPYDAT_OVERFLOW;
    }
    if (406 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 406, 0);
        data->intr = J2P_INT_DDP_ITE_FIFO_WDF_CPYDAT_UNDERFLOW;
    }
    if (407 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 407, 0);
        data->intr = J2P_INT_DDP_BDBC_TX_FIF_OVF;
    }
    if (408 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 408, 0);
        data->intr = J2P_INT_DDP_BDBC_RX_SUB_REQ_FIF_OVF;
    }
    if (409 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 409, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RRF_OVERFLOW_0;
    }
    if (410 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 410, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RRF_OVERFLOW_1;
    }
    if (411 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 411, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RRF_OVERFLOW_2;
    }
    if (412 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 412, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RRF_UNDERFLOW_0;
    }
    if (413 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 413, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RRF_UNDERFLOW_1;
    }
    if (414 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 414, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RRF_UNDERFLOW_2;
    }
    if (415 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 415, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RRF_MISCONFIG_0;
    }
    if (416 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 416, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RRF_MISCONFIG_1;
    }
    if (417 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 417, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RRF_MISCONFIG_2;
    }
    if (418 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 418, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RRF_OVERSIZE;
    }
    if (419 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 419, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RDF_CRDT_OVERFLOW_0;
    }
    if (420 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 420, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RDF_CRDT_OVERFLOW_1;
    }
    if (421 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 421, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RDF_CRDT_OVERFLOW_2;
    }
    if (422 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 422, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RDF_SRAM_OVERFLOW_0;
    }
    if (423 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 423, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RDF_SRAM_OVERFLOW_1;
    }
    if (424 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 424, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RDF_SRAM_OVERFLOW_2;
    }
    if (425 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 425, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RDF_SRAM_UNDERFLOW_0;
    }
    if (426 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 426, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RDF_SRAM_UNDERFLOW_1;
    }
    if (427 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 427, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RDF_SRAM_UNDERFLOW_2;
    }
    if (428 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 428, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_RDF_SRAM_OVERSIZE;
    }
    if (429 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 429, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_DQCF_OVERFLOW;
    }
    if (430 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 430, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_DQCF_UNDERFLOW;
    }
    if (431 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 431, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_DQCF_OVERSIZE;
    }
    if (432 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 432, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_D_BLF_OVERFLOW;
    }
    if (433 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 433, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_D_BLF_UNDERFLOW;
    }
    if (434 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 434, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_PBF_OVERFLOW;
    }
    if (435 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 435, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_PBF_UNDERFLOW;
    }
    if (436 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 436, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_PBF_MISCONFIG;
    }
    if (437 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 437, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_PBF_OVERSIZE;
    }
    if (438 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 438, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_S_2D_DQCF_OVERFLOW;
    }
    if (439 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 439, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_S_2D_DQCF_UNDERFLOW;
    }
    if (440 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 440, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_S_2D_DQCF_OVERSIZE;
    }
    if (441 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 441, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_S_2D_D_BLF_OVERFLOW;
    }
    if (442 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 442, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_S_2D_D_BLF_UNDERFLOW;
    }
    if (443 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 443, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_S_2D_D_BLF_MISCONFIG;
    }
    if (444 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 444, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_S_2D_PBF_OVERFLOW;
    }
    if (445 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 445, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_S_2D_PBF_UNDERFLOW;
    }
    if (446 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 446, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_S_2D_PBF_MISCONFIG;
    }
    if (447 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 447, 0);
        data->intr = J2P_INT_IPT_FIFO_ERROR_S_2D_PBF_OVERSIZE;
    }
    if (448 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 448, 0);
        data->intr = J2P_INT_IPT_FIFO_COMP_CNT_UNDERFLOW;
    }
    if (449 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 449, 0);
        data->intr = J2P_INT_IPT_FIFO_COMP_CNT_OVERFLOW;
    }
    if (450 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 450, 0);
        data->intr = J2P_INT_IPT_FIFO_SCS_UNDERFLOW;
    }
    if (451 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 451, 0);
        data->intr = J2P_INT_IPT_FIFO_RDF_EOB_FIFO_OVERFLOW_0;
    }
    if (452 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 452, 0);
        data->intr = J2P_INT_IPT_FIFO_RDF_EOB_FIFO_OVERFLOW_1;
    }
    if (453 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 453, 0);
        data->intr = J2P_INT_IPT_FIFO_RDF_EOB_FIFO_OVERFLOW_2;
    }
    if (454 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 454, 0);
        data->intr = J2P_INT_IPT_FIFO_RDF_EOB_FIFO_OVERFLOW_3;
    }
    if (455 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 455, 0);
        data->intr = J2P_INT_IPT_FIFO_RDF_EOB_FIFO_UNDERFLOW_0;
    }
    if (456 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 456, 0);
        data->intr = J2P_INT_IPT_FIFO_RDF_EOB_FIFO_UNDERFLOW_1;
    }
    if (457 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 457, 0);
        data->intr = J2P_INT_IPT_FIFO_RDF_EOB_FIFO_UNDERFLOW_2;
    }
    if (458 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 458, 0);
        data->intr = J2P_INT_IPT_FIFO_RDF_EOB_FIFO_UNDERFLOW_3;
    }
    if (459 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 459, 0);
        data->intr = J2P_INT_IPT_FIFO_RDF_DRAM_FIFO_OVERFLOW;
    }
    if (460 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 460, 0);
        data->intr = J2P_INT_IPT_FIFO_RDF_DRAM_FIFO_UNDERFLOW;
    }
    if (461 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 461, 0);
        data->intr = J2P_INT_IPT_ITE_ERR_FTMH_PKT_SIZE_IS_NOT_STAMPPED;
    }
    if (462 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 462, 0);
        data->intr = J2P_INT_IPT_ITE_ERR_FTMH_IS_NOT_STAMPPED;
    }
    if (463 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 463, 0);
        data->intr = J2P_INT_IPT_ITE_ERR_BYTES_TO_ADD_ABOVE_MAX;
    }
    if (464 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 464, 0);
        data->intr = J2P_INT_IPT_ITE_ERR_BYTES_TO_REMOVE_ABOVE_PSIZE;
    }
    if (465 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 465, 0);
        data->intr = J2P_INT_IPT_ITE_ERR_FTMH_PSIZE_MISMATCH;
    }
    if (466 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 466, 0);
        data->intr = J2P_INT_IPT_ITE_ERR_PSIZE_MISMATCH;
    }
    if (467 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 467, 0);
        data->intr = J2P_INT_IPT_ITE_ERR_EXPECTED_ITPP_DELTA_MISMATCH;
    }
    if (468 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 468, 0);
        data->intr = J2P_INT_IPT_ITE_ERR_NEGATIVE_DELTA;
    }
    if (469 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 469, 0);
        data->intr = J2P_INT_IPT_ITE_FIFO_BYPASS_FIFO_OVERFLOW;
    }
    if (470 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 470, 0);
        data->intr = J2P_INT_IPT_ITE_FIFO_BYPASS_FIFO_UNDERFLOW;
    }
    if (471 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 471, 0);
        data->intr = J2P_INT_IPT_ITE_FIFO_WDF_OVERFLOW;
    }
    if (472 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 472, 0);
        data->intr = J2P_INT_IPT_ITE_FIFO_WDF_UNDERFLOW;
    }
    if (473 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 473, 0);
        data->intr = J2P_INT_IPT_ITE_FIFO_WDF_CPYDAT_OVERFLOW;
    }
    if (474 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 474, 0);
        data->intr = J2P_INT_IPT_ITE_FIFO_WDF_CPYDAT_UNDERFLOW;
    }
    if (475 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 475, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_INT_VEC;
    }
    if (476 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 476, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_TOTAL_DB_OVERFLOW_REP_AROUND_INTERRUPT;
    }
    if (477 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 477, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_TOTAL_DB_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (478 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 478, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_TOTAL_PD_OVERFLOW_REP_AROUND_INTERRUPT;
    }
    if (479 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 479, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_TOTAL_PD_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (480 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 480, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_RSVD_PD_SP_0_REP_AROUND_INTERRUPT;
    }
    if (481 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 481, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_RSVD_PD_SP_1_REP_AROUND_INTERRUPT;
    }
    if (482 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 482, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_RSVD_DB_SP_0_REP_AROUND_INTERRUPT;
    }
    if (483 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 483, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_RSVD_DB_SP_1_REP_AROUND_INTERRUPT;
    }
    if (484 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 484, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_0_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (485 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 485, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_1_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (486 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 486, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_2_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (487 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 487, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_3_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (488 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 488, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_4_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (489 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 489, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_5_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (490 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 490, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_6_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (491 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 491, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_7_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (492 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 492, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_8_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (493 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 493, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_9_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (494 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 494, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_10_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (495 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 495, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_11_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (496 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 496, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_12_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (497 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 497, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_13_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (498 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 498, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_14_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (499 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 499, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_MC_PD_SP_TC_15_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (500 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 500, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_PDCM_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (501 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 501, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_PDCM_OVERFLOW_REP_AROUND_INTERRUPT;
    }
    if (502 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 502, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_QDCM_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (503 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 503, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_QDCM_OVERFLOW_REP_AROUND_INTERRUPT;
    }
    if (504 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 504, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_PQSM_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (505 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 505, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_PQSM_OVERFLOW_REP_AROUND_INTERRUPT;
    }
    if (506 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 506, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_QQSM_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (507 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 507, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_QQSM_OVERFLOW_REP_AROUND_INTERRUPT;
    }
    if (508 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 508, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_FQSM_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (509 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 509, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_FQSM_OVERFLOW_REP_AROUND_INTERRUPT;
    }
    if (510 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 510, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_FDCM_UNDERFLOW_REP_AROUND_INTERRUPT;
    }
    if (511 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 511, 0);
        data->intr = J2P_INT_ECGM_CGM_REP_AROUND_FDCM_OVERFLOW_REP_AROUND_INTERRUPT;
    }
    if (512 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 512, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_PAYLOAD_FIFO_OVERFLOW_INT_0;
    }
    if (513 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 513, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_PAYLOAD_FIFO_OVERFLOW_INT_1;
    }
    if (514 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 514, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_PAYLOAD_FIFO_OVERFLOW_INT_2;
    }
    if (515 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 515, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_PAYLOAD_FIFO_OVERFLOW_INT_3;
    }
    if (516 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 516, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_PAYLOAD_FIFO_UNDERRUN_INT_0;
    }
    if (517 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 517, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_PAYLOAD_FIFO_UNDERRUN_INT_1;
    }
    if (518 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 518, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_PAYLOAD_FIFO_UNDERRUN_INT_2;
    }
    if (519 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 519, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_PAYLOAD_FIFO_UNDERRUN_INT_3;
    }
    if (520 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 520, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_HEADER_FIFO_OVERFLOW_INT_0;
    }
    if (521 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 521, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_HEADER_FIFO_OVERFLOW_INT_1;
    }
    if (522 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 522, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_HEADER_FIFO_OVERFLOW_INT_2;
    }
    if (523 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 523, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_HEADER_FIFO_OVERFLOW_INT_3;
    }
    if (524 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 524, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_HEADER_FIFO_UNDERRUN_INT_0;
    }
    if (525 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 525, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_HEADER_FIFO_UNDERRUN_INT_1;
    }
    if (526 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 526, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_HEADER_FIFO_UNDERRUN_INT_2;
    }
    if (527 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 527, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_HEADER_FIFO_UNDERRUN_INT_3;
    }
    if (528 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 528, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_SIZE_PREFETCH_FIFO_OVERFLOW_INT_0;
    }
    if (529 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 529, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_SIZE_PREFETCH_FIFO_OVERFLOW_INT_1;
    }
    if (530 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 530, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_SIZE_PREFETCH_FIFO_OVERFLOW_INT_2;
    }
    if (531 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 531, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_SIZE_PREFETCH_FIFO_OVERFLOW_INT_3;
    }
    if (532 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 532, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_SIZE_PREFETCH_FIFO_UNDERRUN_INT_0;
    }
    if (533 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 533, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_SIZE_PREFETCH_FIFO_UNDERRUN_INT_1;
    }
    if (534 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 534, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_SIZE_PREFETCH_FIFO_UNDERRUN_INT_2;
    }
    if (535 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 535, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_SIZE_PREFETCH_FIFO_UNDERRUN_INT_3;
    }
    if (536 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 536, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_CTRL_FIFO_OVERFLOW_INT_0;
    }
    if (537 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 537, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_CTRL_FIFO_OVERFLOW_INT_1;
    }
    if (538 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 538, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_CTRL_FIFO_OVERFLOW_INT_2;
    }
    if (539 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 539, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_CTRL_FIFO_OVERFLOW_INT_3;
    }
    if (540 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 540, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_CTRL_FIFO_UNDERRUN_INT_0;
    }
    if (541 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 541, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_CTRL_FIFO_UNDERRUN_INT_1;
    }
    if (542 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 542, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_CTRL_FIFO_UNDERRUN_INT_2;
    }
    if (543 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 543, 0);
        data->intr = J2P_INT_FMAC_FMAC_9_TX_CTRL_FIFO_UNDERRUN_INT_3;
    }
    if (544 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 544, 0);
        data->intr = INVALIDr;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_general_disable_on_init_set(
    int unit)
{
    int offset_index;
    dnx_data_intr_general_disable_on_init_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_general;
    int table_index = dnx_data_intr_general_table_disable_on_init;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 11;
    table->info_get.key_size[0] = 11;

    
    table->values[0].default_val = "INVALIDr";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_general_disable_on_init_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_general_table_disable_on_init");

    
    default_data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->intr = INVALIDr;
    
    for (offset_index = 0; offset_index < table->keys[0].size; offset_index++)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, offset_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->intr = J2P_INT_FDT_FDT_CORE_0_DTQ_OVF_INT;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->intr = J2P_INT_FDT_FDT_CORE_1_DTQ_OVF_INT;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->intr = J2P_INT_FDT_FDT_CORE_0_DTQ_UNDF_INT;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->intr = J2P_INT_FDT_FDT_CORE_1_DTQ_UNDF_INT;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->intr = J2P_INT_FDT_FDT_INBAND_ACK_OVF_INT;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->intr = J2P_INT_FDT_FDT_INBAND_ACK_UNDF_INT;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->intr = J2P_INT_FDTL_INTERRUPT_REGISTER_FIELD_0;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->intr = J2P_INT_FDTL_INTERRUPT_REGISTER_FIELD_1;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->intr = J2P_INT_FDTL_INTERRUPT_REGISTER_FIELD_2;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->intr = J2P_INT_FDTL_INTERRUPT_REGISTER_FIELD_3;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->intr = INVALIDr;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_general_disable_print_on_init_set(
    int unit)
{
    int offset_index;
    dnx_data_intr_general_disable_print_on_init_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_general;
    int table_index = dnx_data_intr_general_table_disable_print_on_init;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 7;
    table->info_get.key_size[0] = 7;

    
    table->values[0].default_val = "INVALIDr";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_general_disable_print_on_init_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_general_table_disable_print_on_init");

    
    default_data = (dnx_data_intr_general_disable_print_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->intr = INVALIDr;
    
    for (offset_index = 0; offset_index < table->keys[0].size; offset_index++)
    {
        data = (dnx_data_intr_general_disable_print_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, offset_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_print_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->intr = J2P_INT_OAMP_PENDING_EVENT;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_print_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->intr = J2P_INT_OAMP_STAT_PENDING_EVENT;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_print_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->intr = J2P_INT_MSS_MACSEC_MACSEC_INTERRUPT_REGISTER;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_print_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->intr = J2P_INT_MSD_MACSEC_MACSEC_INTERRUPT_REGISTER;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_print_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->intr = J2P_INT_ILE_ILKN_RX_PORT_0_STATUS_CHANGE_INT;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_print_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->intr = J2P_INT_ILE_ILKN_RX_PORT_1_STATUS_CHANGE_INT;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_disable_print_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->intr = INVALIDr;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_general_block_intr_field_mapping_set(
    int unit)
{
    int offset_index;
    dnx_data_intr_general_block_intr_field_mapping_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_general;
    int table_index = dnx_data_intr_general_table_block_intr_field_mapping;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 2048;
    table->info_get.key_size[0] = 2048;

    
    table->values[0].default_val = "INVALIDr";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_general_block_intr_field_mapping_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_general_table_block_intr_field_mapping");

    
    default_data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->intr = INVALIDr;
    
    for (offset_index = 0; offset_index < table->keys[0].size; offset_index++)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, offset_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (206 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 206, 0);
        data->intr = BDM_0_INTERRUPTf;
    }
    if (398 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 398, 0);
        data->intr = BDM_1_INTERRUPTf;
    }
    if (250 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 250, 0);
        data->intr = CDB_0_INTERRUPTf;
    }
    if (251 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 251, 0);
        data->intr = CDB_1_INTERRUPTf;
    }
    if (252 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 252, 0);
        data->intr = CDB_2_INTERRUPTf;
    }
    if (253 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 253, 0);
        data->intr = CDB_3_INTERRUPTf;
    }
    if (254 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 254, 0);
        data->intr = CDB_4_INTERRUPTf;
    }
    if (255 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 255, 0);
        data->intr = CDB_5_INTERRUPTf;
    }
    if (256 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 256, 0);
        data->intr = CDB_6_INTERRUPTf;
    }
    if (257 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 257, 0);
        data->intr = CDB_7_INTERRUPTf;
    }
    if (442 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 442, 0);
        data->intr = CDB_8_INTERRUPTf;
    }
    if (443 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 443, 0);
        data->intr = CDB_9_INTERRUPTf;
    }
    if (444 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 444, 0);
        data->intr = CDB_10_INTERRUPTf;
    }
    if (445 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 445, 0);
        data->intr = CDB_11_INTERRUPTf;
    }
    if (446 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 446, 0);
        data->intr = CDB_12_INTERRUPTf;
    }
    if (447 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 447, 0);
        data->intr = CDB_13_INTERRUPTf;
    }
    if (448 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 448, 0);
        data->intr = CDB_14_INTERRUPTf;
    }
    if (449 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 449, 0);
        data->intr = CDB_15_INTERRUPTf;
    }
    if (258 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 258, 0);
        data->intr = CDBM_0_INTERRUPTf;
    }
    if (450 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 450, 0);
        data->intr = CDBM_1_INTERRUPTf;
    }
    if (241 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 241, 0);
        data->intr = CDPM_0_INTERRUPTf;
    }
    if (242 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 242, 0);
        data->intr = CDPM_1_INTERRUPTf;
    }
    if (243 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 243, 0);
        data->intr = CDPM_2_INTERRUPTf;
    }
    if (244 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 244, 0);
        data->intr = CDPM_3_INTERRUPTf;
    }
    if (245 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 245, 0);
        data->intr = CDPM_4_INTERRUPTf;
    }
    if (246 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 246, 0);
        data->intr = CDPM_5_INTERRUPTf;
    }
    if (247 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 247, 0);
        data->intr = CDPM_6_INTERRUPTf;
    }
    if (248 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 248, 0);
        data->intr = CDPM_7_INTERRUPTf;
    }
    if (249 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 249, 0);
        data->intr = CDPM_8_INTERRUPTf;
    }
    if (433 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 433, 0);
        data->intr = CDPM_9_INTERRUPTf;
    }
    if (434 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 434, 0);
        data->intr = CDPM_10_INTERRUPTf;
    }
    if (435 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 435, 0);
        data->intr = CDPM_11_INTERRUPTf;
    }
    if (436 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 436, 0);
        data->intr = CDPM_12_INTERRUPTf;
    }
    if (437 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 437, 0);
        data->intr = CDPM_13_INTERRUPTf;
    }
    if (438 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 438, 0);
        data->intr = CDPM_14_INTERRUPTf;
    }
    if (439 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 439, 0);
        data->intr = CDPM_15_INTERRUPTf;
    }
    if (440 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 440, 0);
        data->intr = CDPM_16_INTERRUPTf;
    }
    if (441 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 441, 0);
        data->intr = CDPM_17_INTERRUPTf;
    }
    if (1520 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1520, 0);
        data->intr = CDPM_0_PM_INTERRUPTf;
    }
    if (1536 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1536, 0);
        data->intr = CDPM_1_PM_INTERRUPTf;
    }
    if (1552 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1552, 0);
        data->intr = CDPM_2_PM_INTERRUPTf;
    }
    if (1568 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1568, 0);
        data->intr = CDPM_3_PM_INTERRUPTf;
    }
    if (1584 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1584, 0);
        data->intr = CDPM_4_PM_INTERRUPTf;
    }
    if (1600 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1600, 0);
        data->intr = CDPM_5_PM_INTERRUPTf;
    }
    if (1616 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1616, 0);
        data->intr = CDPM_6_PM_INTERRUPTf;
    }
    if (1632 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1632, 0);
        data->intr = CDPM_7_PM_INTERRUPTf;
    }
    if (1648 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1648, 0);
        data->intr = CDPM_8_PM_INTERRUPTf;
    }
    if (1664 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1664, 0);
        data->intr = CDPM_9_PM_INTERRUPTf;
    }
    if (1680 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1680, 0);
        data->intr = CDPM_10_PM_INTERRUPTf;
    }
    if (1696 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1696, 0);
        data->intr = CDPM_11_PM_INTERRUPTf;
    }
    if (1712 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1712, 0);
        data->intr = CDPM_12_PM_INTERRUPTf;
    }
    if (1728 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1728, 0);
        data->intr = CDPM_13_PM_INTERRUPTf;
    }
    if (1744 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1744, 0);
        data->intr = CDPM_14_PM_INTERRUPTf;
    }
    if (1760 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1760, 0);
        data->intr = CDPM_15_PM_INTERRUPTf;
    }
    if (1776 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1776, 0);
        data->intr = CDPM_16_PM_INTERRUPTf;
    }
    if (1792 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1792, 0);
        data->intr = CDPM_17_PM_INTERRUPTf;
    }
    if (769 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 769, 0);
        data->intr = CFC_0_INTERRUPTf;
    }
    if (770 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 770, 0);
        data->intr = CFC_1_INTERRUPTf;
    }
    if (192 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 192, 0);
        data->intr = CGM_0_INTERRUPTf;
    }
    if (384 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 384, 0);
        data->intr = CGM_1_INTERRUPTf;
    }
    if (197 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 197, 0);
        data->intr = CRPS_0_INTERRUPTf;
    }
    if (389 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 389, 0);
        data->intr = CRPS_1_INTERRUPTf;
    }
    if (576 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 576, 0);
        data->intr = DDHA_0_INTERRUPTf;
    }
    if (577 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 577, 0);
        data->intr = DDHA_1_INTERRUPTf;
    }
    if (578 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 578, 0);
        data->intr = DDHA_2_INTERRUPTf;
    }
    if (579 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 579, 0);
        data->intr = DDHA_3_INTERRUPTf;
    }
    if (580 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 580, 0);
        data->intr = DDHB_0_INTERRUPTf;
    }
    if (581 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 581, 0);
        data->intr = DDHB_1_INTERRUPTf;
    }
    if (582 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 582, 0);
        data->intr = DDHB_2_INTERRUPTf;
    }
    if (583 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 583, 0);
        data->intr = DDHB_3_INTERRUPTf;
    }
    if (200 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 200, 0);
        data->intr = DDP_0_INTERRUPTf;
    }
    if (392 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 392, 0);
        data->intr = DDP_1_INTERRUPTf;
    }
    if (194 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 194, 0);
        data->intr = DQM_0_INTERRUPTf;
    }
    if (386 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 386, 0);
        data->intr = DQM_1_INTERRUPTf;
    }
    if (210 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 210, 0);
        data->intr = ECGM_0_INTERRUPTf;
    }
    if (402 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 402, 0);
        data->intr = ECGM_1_INTERRUPTf;
    }
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->intr = ECI_INTERRUPTf;
    }
    if (212 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 212, 0);
        data->intr = EDB_0_INTERRUPTf;
    }
    if (404 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 404, 0);
        data->intr = EDB_1_INTERRUPTf;
    }
    if (217 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 217, 0);
        data->intr = EPNI_0_INTERRUPTf;
    }
    if (409 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 409, 0);
        data->intr = EPNI_1_INTERRUPTf;
    }
    if (216 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 216, 0);
        data->intr = EPRE_0_INTERRUPTf;
    }
    if (408 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 408, 0);
        data->intr = EPRE_1_INTERRUPTf;
    }
    if (214 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 214, 0);
        data->intr = EPS_0_INTERRUPTf;
    }
    if (406 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 406, 0);
        data->intr = EPS_1_INTERRUPTf;
    }
    if (220 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 220, 0);
        data->intr = ERPP_0_INTERRUPTf;
    }
    if (412 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 412, 0);
        data->intr = ERPP_1_INTERRUPTf;
    }
    if (218 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 218, 0);
        data->intr = ESB_0_INTERRUPTf;
    }
    if (410 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 410, 0);
        data->intr = ESB_1_INTERRUPTf;
    }
    if (221 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 221, 0);
        data->intr = ETPPA_0_INTERRUPTf;
    }
    if (413 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 413, 0);
        data->intr = ETPPA_1_INTERRUPTf;
    }
    if (222 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 222, 0);
        data->intr = ETPPB_0_INTERRUPTf;
    }
    if (414 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 414, 0);
        data->intr = ETPPB_1_INTERRUPTf;
    }
    if (223 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 223, 0);
        data->intr = ETPPC_0_INTERRUPTf;
    }
    if (415 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 415, 0);
        data->intr = ETPPC_1_INTERRUPTf;
    }
    if (590 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 590, 0);
        data->intr = EVNT_INTERRUPTf;
    }
    if (772 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 772, 0);
        data->intr = FCR_INTERRUPTf;
    }
    if (773 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 773, 0);
        data->intr = FCT_INTERRUPTf;
    }
    if (776 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 776, 0);
        data->intr = FDA_INTERRUPTf;
    }
    if (209 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 209, 0);
        data->intr = FDR_0_INTERRUPTf;
    }
    if (401 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 401, 0);
        data->intr = FDR_1_INTERRUPTf;
    }
    if (774 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 774, 0);
        data->intr = FDT_INTERRUPTf;
    }
    if (208 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 208, 0);
        data->intr = FDTL_0_INTERRUPTf;
    }
    if (400 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 400, 0);
        data->intr = FDTL_1_INTERRUPTf;
    }
    if (960 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 960, 0);
        data->intr = FMAC_0_INTERRUPTf;
    }
    if (961 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 961, 0);
        data->intr = FMAC_1_INTERRUPTf;
    }
    if (963 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 963, 0);
        data->intr = FMAC_2_INTERRUPTf;
    }
    if (964 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 964, 0);
        data->intr = FMAC_3_INTERRUPTf;
    }
    if (966 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 966, 0);
        data->intr = FMAC_4_INTERRUPTf;
    }
    if (967 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 967, 0);
        data->intr = FMAC_5_INTERRUPTf;
    }
    if (969 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 969, 0);
        data->intr = FMAC_6_INTERRUPTf;
    }
    if (970 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 970, 0);
        data->intr = FMAC_7_INTERRUPTf;
    }
    if (972 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 972, 0);
        data->intr = FMAC_8_INTERRUPTf;
    }
    if (973 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 973, 0);
        data->intr = FMAC_9_INTERRUPTf;
    }
    if (975 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 975, 0);
        data->intr = FMAC_10_INTERRUPTf;
    }
    if (976 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 976, 0);
        data->intr = FMAC_11_INTERRUPTf;
    }
    if (978 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 978, 0);
        data->intr = FMAC_12_INTERRUPTf;
    }
    if (979 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 979, 0);
        data->intr = FMAC_13_INTERRUPTf;
    }
    if (981 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 981, 0);
        data->intr = FMAC_14_INTERRUPTf;
    }
    if (982 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 982, 0);
        data->intr = FMAC_15_INTERRUPTf;
    }
    if (984 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 984, 0);
        data->intr = FMAC_16_INTERRUPTf;
    }
    if (985 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 985, 0);
        data->intr = FMAC_17_INTERRUPTf;
    }
    if (987 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 987, 0);
        data->intr = FMAC_18_INTERRUPTf;
    }
    if (988 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 988, 0);
        data->intr = FMAC_19_INTERRUPTf;
    }
    if (990 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 990, 0);
        data->intr = FMAC_20_INTERRUPTf;
    }
    if (991 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 991, 0);
        data->intr = FMAC_21_INTERRUPTf;
    }
    if (993 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 993, 0);
        data->intr = FMAC_22_INTERRUPTf;
    }
    if (994 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 994, 0);
        data->intr = FMAC_23_INTERRUPTf;
    }
    if (1008 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1008, 0);
        data->intr = FMAC_24_INTERRUPTf;
    }
    if (1009 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1009, 0);
        data->intr = FMAC_25_INTERRUPTf;
    }
    if (1011 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1011, 0);
        data->intr = FMAC_26_INTERRUPTf;
    }
    if (1012 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1012, 0);
        data->intr = FMAC_27_INTERRUPTf;
    }
    if (1014 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1014, 0);
        data->intr = FMAC_28_INTERRUPTf;
    }
    if (1015 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1015, 0);
        data->intr = FMAC_29_INTERRUPTf;
    }
    if (1017 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1017, 0);
        data->intr = FMAC_30_INTERRUPTf;
    }
    if (1018 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1018, 0);
        data->intr = FMAC_31_INTERRUPTf;
    }
    if (1020 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1020, 0);
        data->intr = FMAC_32_INTERRUPTf;
    }
    if (1021 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1021, 0);
        data->intr = FMAC_33_INTERRUPTf;
    }
    if (1023 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1023, 0);
        data->intr = FMAC_34_INTERRUPTf;
    }
    if (1024 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1024, 0);
        data->intr = FMAC_35_INTERRUPTf;
    }
    if (1026 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1026, 0);
        data->intr = FMAC_36_INTERRUPTf;
    }
    if (1027 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1027, 0);
        data->intr = FMAC_37_INTERRUPTf;
    }
    if (1029 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1029, 0);
        data->intr = FMAC_38_INTERRUPTf;
    }
    if (1030 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1030, 0);
        data->intr = FMAC_39_INTERRUPTf;
    }
    if (1032 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1032, 0);
        data->intr = FMAC_40_INTERRUPTf;
    }
    if (1033 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1033, 0);
        data->intr = FMAC_41_INTERRUPTf;
    }
    if (1035 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1035, 0);
        data->intr = FMAC_42_INTERRUPTf;
    }
    if (1036 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1036, 0);
        data->intr = FMAC_43_INTERRUPTf;
    }
    if (1038 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1038, 0);
        data->intr = FMAC_44_INTERRUPTf;
    }
    if (1039 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1039, 0);
        data->intr = FMAC_45_INTERRUPTf;
    }
    if (1041 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1041, 0);
        data->intr = FMAC_46_INTERRUPTf;
    }
    if (1042 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1042, 0);
        data->intr = FMAC_47_INTERRUPTf;
    }
    if (215 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 215, 0);
        data->intr = FQP_0_INTERRUPTf;
    }
    if (407 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 407, 0);
        data->intr = FQP_1_INTERRUPTf;
    }
    if (962 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 962, 0);
        data->intr = FSRD_0_INTERRUPTf;
    }
    if (965 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 965, 0);
        data->intr = FSRD_1_INTERRUPTf;
    }
    if (968 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 968, 0);
        data->intr = FSRD_2_INTERRUPTf;
    }
    if (971 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 971, 0);
        data->intr = FSRD_3_INTERRUPTf;
    }
    if (974 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 974, 0);
        data->intr = FSRD_4_INTERRUPTf;
    }
    if (977 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 977, 0);
        data->intr = FSRD_5_INTERRUPTf;
    }
    if (980 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 980, 0);
        data->intr = FSRD_6_INTERRUPTf;
    }
    if (983 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 983, 0);
        data->intr = FSRD_7_INTERRUPTf;
    }
    if (986 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 986, 0);
        data->intr = FSRD_8_INTERRUPTf;
    }
    if (989 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 989, 0);
        data->intr = FSRD_9_INTERRUPTf;
    }
    if (992 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 992, 0);
        data->intr = FSRD_10_INTERRUPTf;
    }
    if (995 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 995, 0);
        data->intr = FSRD_11_INTERRUPTf;
    }
    if (1010 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1010, 0);
        data->intr = FSRD_12_INTERRUPTf;
    }
    if (1013 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1013, 0);
        data->intr = FSRD_13_INTERRUPTf;
    }
    if (1016 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1016, 0);
        data->intr = FSRD_14_INTERRUPTf;
    }
    if (1019 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1019, 0);
        data->intr = FSRD_15_INTERRUPTf;
    }
    if (1022 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1022, 0);
        data->intr = FSRD_16_INTERRUPTf;
    }
    if (1025 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1025, 0);
        data->intr = FSRD_17_INTERRUPTf;
    }
    if (1028 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1028, 0);
        data->intr = FSRD_18_INTERRUPTf;
    }
    if (1031 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1031, 0);
        data->intr = FSRD_19_INTERRUPTf;
    }
    if (1034 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1034, 0);
        data->intr = FSRD_20_INTERRUPTf;
    }
    if (1037 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1037, 0);
        data->intr = FSRD_21_INTERRUPTf;
    }
    if (1040 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1040, 0);
        data->intr = FSRD_22_INTERRUPTf;
    }
    if (1043 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 1043, 0);
        data->intr = FSRD_23_INTERRUPTf;
    }
    if (270 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 270, 0);
        data->intr = HBC_0_INTERRUPTf;
    }
    if (271 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 271, 0);
        data->intr = HBC_1_INTERRUPTf;
    }
    if (272 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 272, 0);
        data->intr = HBC_2_INTERRUPTf;
    }
    if (273 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 273, 0);
        data->intr = HBC_3_INTERRUPTf;
    }
    if (274 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 274, 0);
        data->intr = HBC_4_INTERRUPTf;
    }
    if (275 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 275, 0);
        data->intr = HBC_5_INTERRUPTf;
    }
    if (276 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 276, 0);
        data->intr = HBC_6_INTERRUPTf;
    }
    if (277 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 277, 0);
        data->intr = HBC_7_INTERRUPTf;
    }
    if (462 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 462, 0);
        data->intr = HBC_8_INTERRUPTf;
    }
    if (463 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 463, 0);
        data->intr = HBC_9_INTERRUPTf;
    }
    if (464 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 464, 0);
        data->intr = HBC_10_INTERRUPTf;
    }
    if (465 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 465, 0);
        data->intr = HBC_11_INTERRUPTf;
    }
    if (466 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 466, 0);
        data->intr = HBC_12_INTERRUPTf;
    }
    if (467 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 467, 0);
        data->intr = HBC_13_INTERRUPTf;
    }
    if (468 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 468, 0);
        data->intr = HBC_14_INTERRUPTf;
    }
    if (469 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 469, 0);
        data->intr = HBC_15_INTERRUPTf;
    }
    if (268 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 268, 0);
        data->intr = HBMC_0_INTERRUPTf;
    }
    if (460 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 460, 0);
        data->intr = HBMC_1_INTERRUPTf;
    }
    if (269 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 269, 0);
        data->intr = HRC_0_INTERRUPTf;
    }
    if (461 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 461, 0);
        data->intr = HRC_1_INTERRUPTf;
    }
    if (234 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 234, 0);
        data->intr = ILE_0_INTERRUPTf;
    }
    if (235 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 235, 0);
        data->intr = ILE_1_INTERRUPTf;
    }
    if (426 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 426, 0);
        data->intr = ILE_2_INTERRUPTf;
    }
    if (427 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 427, 0);
        data->intr = ILE_3_INTERRUPTf;
    }
    if (226 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 226, 0);
        data->intr = IPPA_0_INTERRUPTf;
    }
    if (418 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 418, 0);
        data->intr = IPPA_1_INTERRUPTf;
    }
    if (227 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 227, 0);
        data->intr = IPPB_0_INTERRUPTf;
    }
    if (419 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 419, 0);
        data->intr = IPPB_1_INTERRUPTf;
    }
    if (228 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 228, 0);
        data->intr = IPPC_0_INTERRUPTf;
    }
    if (420 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 420, 0);
        data->intr = IPPC_1_INTERRUPTf;
    }
    if (229 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 229, 0);
        data->intr = IPPD_0_INTERRUPTf;
    }
    if (421 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 421, 0);
        data->intr = IPPD_1_INTERRUPTf;
    }
    if (224 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 224, 0);
        data->intr = IPPE_0_INTERRUPTf;
    }
    if (416 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 416, 0);
        data->intr = IPPE_1_INTERRUPTf;
    }
    if (225 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 225, 0);
        data->intr = IPPF_0_INTERRUPTf;
    }
    if (417 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 417, 0);
        data->intr = IPPF_1_INTERRUPTf;
    }
    if (193 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 193, 0);
        data->intr = IPS_0_INTERRUPTf;
    }
    if (385 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 385, 0);
        data->intr = IPS_1_INTERRUPTf;
    }
    if (203 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 203, 0);
        data->intr = IPT_0_INTERRUPTf;
    }
    if (395 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 395, 0);
        data->intr = IPT_1_INTERRUPTf;
    }
    if (196 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 196, 0);
        data->intr = IQM_0_INTERRUPTf;
    }
    if (388 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 388, 0);
        data->intr = IQM_1_INTERRUPTf;
    }
    if (199 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 199, 0);
        data->intr = IRE_0_INTERRUPTf;
    }
    if (391 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 391, 0);
        data->intr = IRE_1_INTERRUPTf;
    }
    if (204 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 204, 0);
        data->intr = ITPP_0_INTERRUPTf;
    }
    if (396 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 396, 0);
        data->intr = ITPP_1_INTERRUPTf;
    }
    if (202 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 202, 0);
        data->intr = ITPPD_0_INTERRUPTf;
    }
    if (394 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 394, 0);
        data->intr = ITPPD_1_INTERRUPTf;
    }
    if (586 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 586, 0);
        data->intr = KAPS_0_INTERRUPTf;
    }
    if (587 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 587, 0);
        data->intr = KAPS_1_INTERRUPTf;
    }
    if (591 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 591, 0);
        data->intr = MACT_INTERRUPTf;
    }
    if (198 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 198, 0);
        data->intr = MCP_0_INTERRUPTf;
    }
    if (390 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 390, 0);
        data->intr = MCP_1_INTERRUPTf;
    }
    if (588 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 588, 0);
        data->intr = MDB_INTERRUPTf;
    }
    if (2000 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 2000, 0);
        data->intr = MDB_ARM_INTERRUPTf;
    }
    if (775 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 775, 0);
        data->intr = MESH_TOPOLOGY_INTERRUPTf;
    }
    if (207 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 207, 0);
        data->intr = MRPS_0_INTERRUPTf;
    }
    if (399 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 399, 0);
        data->intr = MRPS_1_INTERRUPTf;
    }
    if (236 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 236, 0);
        data->intr = MSD_0_INTERRUPTf;
    }
    if (237 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 237, 0);
        data->intr = MSD_1_INTERRUPTf;
    }
    if (238 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 238, 0);
        data->intr = MSD_2_INTERRUPTf;
    }
    if (239 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 239, 0);
        data->intr = MSD_3_INTERRUPTf;
    }
    if (428 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 428, 0);
        data->intr = MSD_4_INTERRUPTf;
    }
    if (429 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 429, 0);
        data->intr = MSD_5_INTERRUPTf;
    }
    if (430 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 430, 0);
        data->intr = MSD_6_INTERRUPTf;
    }
    if (431 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 431, 0);
        data->intr = MSD_7_INTERRUPTf;
    }
    if (240 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 240, 0);
        data->intr = MSS_0_INTERRUPTf;
    }
    if (432 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 432, 0);
        data->intr = MSS_1_INTERRUPTf;
    }
    if (768 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 768, 0);
        data->intr = MTM_INTERRUPTf;
    }
    if (259 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 259, 0);
        data->intr = NMG_0_INTERRUPTf;
    }
    if (451 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 451, 0);
        data->intr = NMG_1_INTERRUPTf;
    }
    if (589 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 589, 0);
        data->intr = OAMP_INTERRUPTf;
    }
    if (262 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 262, 0);
        data->intr = OCB_0_INTERRUPTf;
    }
    if (263 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 263, 0);
        data->intr = OCB_1_INTERRUPTf;
    }
    if (264 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 264, 0);
        data->intr = OCB_2_INTERRUPTf;
    }
    if (265 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 265, 0);
        data->intr = OCB_3_INTERRUPTf;
    }
    if (454 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 454, 0);
        data->intr = OCB_4_INTERRUPTf;
    }
    if (455 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 455, 0);
        data->intr = OCB_5_INTERRUPTf;
    }
    if (456 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 456, 0);
        data->intr = OCB_6_INTERRUPTf;
    }
    if (457 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 457, 0);
        data->intr = OCB_7_INTERRUPTf;
    }
    if (261 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 261, 0);
        data->intr = OCBM_0_INTERRUPTf;
    }
    if (453 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 453, 0);
        data->intr = OCBM_1_INTERRUPTf;
    }
    if (592 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 592, 0);
        data->intr = OLP_INTERRUPTf;
    }
    if (205 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 205, 0);
        data->intr = PDM_0_INTERRUPTf;
    }
    if (397 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 397, 0);
        data->intr = PDM_1_INTERRUPTf;
    }
    if (230 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 230, 0);
        data->intr = PEM_0_INTERRUPTf;
    }
    if (231 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 231, 0);
        data->intr = PEM_1_INTERRUPTf;
    }
    if (232 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 232, 0);
        data->intr = PEM_2_INTERRUPTf;
    }
    if (233 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 233, 0);
        data->intr = PEM_3_INTERRUPTf;
    }
    if (422 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 422, 0);
        data->intr = PEM_4_INTERRUPTf;
    }
    if (423 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 423, 0);
        data->intr = PEM_5_INTERRUPTf;
    }
    if (424 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 424, 0);
        data->intr = PEM_6_INTERRUPTf;
    }
    if (425 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 425, 0);
        data->intr = PEM_7_INTERRUPTf;
    }
    if (213 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 213, 0);
        data->intr = PQP_0_INTERRUPTf;
    }
    if (405 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 405, 0);
        data->intr = PQP_1_INTERRUPTf;
    }
    if (211 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 211, 0);
        data->intr = RQP_0_INTERRUPTf;
    }
    if (403 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 403, 0);
        data->intr = RQP_1_INTERRUPTf;
    }
    if (771 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 771, 0);
        data->intr = RTP_INTERRUPTf;
    }
    if (219 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 219, 0);
        data->intr = SCH_0_INTERRUPTf;
    }
    if (411 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 411, 0);
        data->intr = SCH_1_INTERRUPTf;
    }
    if (260 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 260, 0);
        data->intr = SIF_0_INTERRUPTf;
    }
    if (452 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 452, 0);
        data->intr = SIF_1_INTERRUPTf;
    }
    if (201 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 201, 0);
        data->intr = SPB_0_INTERRUPTf;
    }
    if (393 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 393, 0);
        data->intr = SPB_1_INTERRUPTf;
    }
    if (195 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 195, 0);
        data->intr = SQM_0_INTERRUPTf;
    }
    if (387 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 387, 0);
        data->intr = SQM_1_INTERRUPTf;
    }
    if (584 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 584, 0);
        data->intr = KTM_0_INTERRUPTf;
    }
    if (585 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 585, 0);
        data->intr = KTM_1_INTERRUPTf;
    }
    if (266 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 266, 0);
        data->intr = TDU_0_INTERRUPTf;
    }
    if (267 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 267, 0);
        data->intr = TDU_1_INTERRUPTf;
    }
    if (458 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 458, 0);
        data->intr = TDU_2_INTERRUPTf;
    }
    if (459 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 459, 0);
        data->intr = TDU_3_INTERRUPTf;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_general_skip_clear_on_init_set(
    int unit)
{
    int offset_index;
    dnx_data_intr_general_skip_clear_on_init_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_general;
    int table_index = dnx_data_intr_general_table_skip_clear_on_init;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 2;
    table->info_get.key_size[0] = 2;

    
    table->values[0].default_val = "INVALIDr";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_general_skip_clear_on_init_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_general_table_skip_clear_on_init");

    
    default_data = (dnx_data_intr_general_skip_clear_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->intr = INVALIDr;
    
    for (offset_index = 0; offset_index < table->keys[0].size; offset_index++)
    {
        data = (dnx_data_intr_general_skip_clear_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, offset_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_skip_clear_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->intr = J2P_INT_ILE_ILKN_RX_PORT_0_STATUS_CHANGE_INT;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_skip_clear_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->intr = J2P_INT_ILE_ILKN_RX_PORT_1_STATUS_CHANGE_INT;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_general_force_unmask_on_init_set(
    int unit)
{
    int offset_index;
    dnx_data_intr_general_force_unmask_on_init_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_general;
    int table_index = dnx_data_intr_general_table_force_unmask_on_init;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 2;
    table->info_get.key_size[0] = 2;

    
    table->values[0].default_val = "INVALIDr";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_general_force_unmask_on_init_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_general_table_force_unmask_on_init");

    
    default_data = (dnx_data_intr_general_force_unmask_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->intr = INVALIDr;
    
    for (offset_index = 0; offset_index < table->keys[0].size; offset_index++)
    {
        data = (dnx_data_intr_general_force_unmask_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, offset_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_force_unmask_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->intr = J2P_INT_MSS_MACSEC_MACSEC_INTERRUPT_REGISTER;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_force_unmask_on_init_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->intr = J2P_INT_MSD_MACSEC_MACSEC_INTERRUPT_REGISTER;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_general_skip_clear_on_regress_set(
    int unit)
{
    int offset_index;
    dnx_data_intr_general_skip_clear_on_regress_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_general;
    int table_index = dnx_data_intr_general_table_skip_clear_on_regress;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 4;
    table->info_get.key_size[0] = 4;

    
    table->values[0].default_val = "INVALIDr";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_general_skip_clear_on_regress_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_general_table_skip_clear_on_regress");

    
    default_data = (dnx_data_intr_general_skip_clear_on_regress_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->intr = INVALIDr;
    
    for (offset_index = 0; offset_index < table->keys[0].size; offset_index++)
    {
        data = (dnx_data_intr_general_skip_clear_on_regress_t *) dnxc_data_mgmt_table_data_get(unit, table, offset_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_skip_clear_on_regress_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->intr = J2P_INT_FMAC_FMAC_5_CORRECTABLE_ERROR_0;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_skip_clear_on_regress_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->intr = J2P_INT_FMAC_FMAC_5_CORRECTABLE_ERROR_1;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_skip_clear_on_regress_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->intr = J2P_INT_FMAC_FMAC_5_CORRECTABLE_ERROR_2;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_intr_general_skip_clear_on_regress_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->intr = J2P_INT_FMAC_FMAC_5_CORRECTABLE_ERROR_3;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
j2p_a0_dnx_data_intr_ser_tcam_protection_issue_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_ser;
    int define_index = dnx_data_intr_ser_define_tcam_protection_issue;
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
j2p_a0_dnx_data_intr_ser_mem_mask_set(
    int unit)
{
    int index_index;
    dnx_data_intr_ser_mem_mask_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_ser;
    int table_index = dnx_data_intr_ser_table_mem_mask;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 171;
    table->info_get.key_size[0] = 171;

    
    table->values[0].default_val = "INVALIDr";
    table->values[1].default_val = "INVALIDf";
    table->values[2].default_val = "dnxc_mem_mask_mode_none";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_ser_mem_mask_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_ser_table_mem_mask");

    
    default_data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->reg = INVALIDr;
    default_data->field = INVALIDf;
    default_data->mode = dnxc_mem_mask_mode_none;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->reg = BDM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->reg = CDBM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->reg = CDB_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->reg = CFC_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->reg = CGM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->reg = CRPS_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->reg = DDHA_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->reg = DDHB_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->reg = DDP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->reg = DQM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->reg = ECGM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->reg = ECI_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->reg = EDB_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->reg = EPNI_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->reg = EPRE_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->reg = EPS_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->reg = ERPP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->reg = ESB_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (18 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->reg = ETPPA_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (19 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->reg = ETPPB_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (20 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 0);
        data->reg = ETPPC_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (21 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 21, 0);
        data->reg = EVNT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (22 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 22, 0);
        data->reg = FCR_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (23 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 23, 0);
        data->reg = FCT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (24 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 24, 0);
        data->reg = FDA_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (25 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 25, 0);
        data->reg = FDR_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (26 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 26, 0);
        data->reg = FDTL_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (27 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 27, 0);
        data->reg = FDT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (28 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 28, 0);
        data->reg = FMAC_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (29 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 29, 0);
        data->reg = FQP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (30 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 30, 0);
        data->reg = HBC_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (31 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 31, 0);
        data->reg = HRC_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (32 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 32, 0);
        data->reg = ILE_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (33 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 33, 0);
        data->reg = IPPA_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (34 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 34, 0);
        data->reg = IPPB_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (35 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 35, 0);
        data->reg = IPPC_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (36 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 36, 0);
        data->reg = IPPD_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (37 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 37, 0);
        data->reg = IPPE_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (38 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 38, 0);
        data->reg = IPPF_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (39 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 39, 0);
        data->reg = IPS_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (40 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 40, 0);
        data->reg = IPT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (41 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 41, 0);
        data->reg = IQM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (42 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 42, 0);
        data->reg = IRE_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (43 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 43, 0);
        data->reg = ITPPD_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (44 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 44, 0);
        data->reg = ITPP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (45 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 45, 0);
        data->reg = KAPS_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (46 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 46, 0);
        data->reg = MACT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (47 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 47, 0);
        data->reg = MCP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (48 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 48, 0);
        data->reg = MDB_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (49 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 49, 0);
        data->reg = MRPS_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (50 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 50, 0);
        data->reg = MTM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (51 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 51, 0);
        data->reg = NMG_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (52 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 52, 0);
        data->reg = OAMP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (53 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 53, 0);
        data->reg = OCBM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (54 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 54, 0);
        data->reg = OCB_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (55 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 55, 0);
        data->reg = OLP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (56 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 56, 0);
        data->reg = PDM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (57 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 57, 0);
        data->reg = PEM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (58 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 58, 0);
        data->reg = PQP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (59 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 59, 0);
        data->reg = RQP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (60 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 60, 0);
        data->reg = RTP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (61 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 61, 0);
        data->reg = SCH_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (62 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 62, 0);
        data->reg = SIF_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (63 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 63, 0);
        data->reg = SPB_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (64 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 64, 0);
        data->reg = SQM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (65 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 65, 0);
        data->reg = TCAM_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (66 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 66, 0);
        data->reg = TDU_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (67 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 67, 0);
        data->reg = BDM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (68 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 68, 0);
        data->reg = CDBM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (69 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 69, 0);
        data->reg = CDB_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (70 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 70, 0);
        data->reg = CFC_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (71 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 71, 0);
        data->reg = CGM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (72 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 72, 0);
        data->reg = CRPS_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (73 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 73, 0);
        data->reg = DDHA_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (74 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 74, 0);
        data->reg = DDHB_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (75 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 75, 0);
        data->reg = DDP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (76 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 76, 0);
        data->reg = DQM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (77 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 77, 0);
        data->reg = ECGM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (78 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 78, 0);
        data->reg = ECI_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (79 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 79, 0);
        data->reg = EDB_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (80 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 80, 0);
        data->reg = EPNI_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (81 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 81, 0);
        data->reg = EPRE_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (82 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 82, 0);
        data->reg = EPS_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (83 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 83, 0);
        data->reg = ERPP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (84 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 84, 0);
        data->reg = ESB_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (85 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 85, 0);
        data->reg = ETPPA_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (86 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 86, 0);
        data->reg = ETPPB_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (87 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 87, 0);
        data->reg = ETPPC_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (88 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 88, 0);
        data->reg = EVNT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (89 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 89, 0);
        data->reg = FCR_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (90 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 90, 0);
        data->reg = FCT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (91 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 91, 0);
        data->reg = FDA_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (92 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 92, 0);
        data->reg = FDR_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (93 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 93, 0);
        data->reg = FDTL_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (94 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 94, 0);
        data->reg = FDT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (95 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 95, 0);
        data->reg = FMAC_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (96 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 96, 0);
        data->reg = FQP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (97 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 97, 0);
        data->reg = HBC_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (98 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 98, 0);
        data->reg = HRC_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (99 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 99, 0);
        data->reg = ILE_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (100 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 100, 0);
        data->reg = IPPA_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (101 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 101, 0);
        data->reg = IPPB_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (102 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 102, 0);
        data->reg = IPPC_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (103 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 103, 0);
        data->reg = IPPD_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (104 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 104, 0);
        data->reg = IPPE_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (105 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 105, 0);
        data->reg = IPPF_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (106 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 106, 0);
        data->reg = IPS_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (107 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 107, 0);
        data->reg = IPT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (108 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 108, 0);
        data->reg = IQM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (109 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 109, 0);
        data->reg = IRE_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (110 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 110, 0);
        data->reg = ITPPD_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (111 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 111, 0);
        data->reg = ITPP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (112 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 112, 0);
        data->reg = KAPS_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (113 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 113, 0);
        data->reg = MACT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (114 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 114, 0);
        data->reg = MCP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (115 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 115, 0);
        data->reg = MDB_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (116 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 116, 0);
        data->reg = MRPS_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (117 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 117, 0);
        data->reg = MTM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (118 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 118, 0);
        data->reg = NMG_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (119 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 119, 0);
        data->reg = OAMP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (120 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 120, 0);
        data->reg = OCBM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (121 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 121, 0);
        data->reg = OCB_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (122 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 122, 0);
        data->reg = OLP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (123 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 123, 0);
        data->reg = PDM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (124 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 124, 0);
        data->reg = PEM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (125 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 125, 0);
        data->reg = PQP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (126 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 126, 0);
        data->reg = RQP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (127 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 127, 0);
        data->reg = RTP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (128 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 128, 0);
        data->reg = SCH_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (129 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 129, 0);
        data->reg = SIF_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (130 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 130, 0);
        data->reg = SPB_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (131 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 131, 0);
        data->reg = SQM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (132 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 132, 0);
        data->reg = TCAM_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (133 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 133, 0);
        data->reg = TDU_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (134 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 134, 0);
        data->reg = CDBM_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (135 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 135, 0);
        data->reg = CDB_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (136 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 136, 0);
        data->reg = ERPP_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (137 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 137, 0);
        data->reg = ETPPA_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (138 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 138, 0);
        data->reg = ETPPB_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (139 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 139, 0);
        data->reg = ETPPC_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (140 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 140, 0);
        data->reg = HBC_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (141 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 141, 0);
        data->reg = IPPA_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (142 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 142, 0);
        data->reg = IPPB_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (143 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 143, 0);
        data->reg = IPPC_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (144 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 144, 0);
        data->reg = IPPD_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (145 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 145, 0);
        data->reg = IPPE_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (146 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 146, 0);
        data->reg = IPPF_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (147 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 147, 0);
        data->reg = IRE_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (148 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 148, 0);
        data->reg = MDB_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (149 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 149, 0);
        data->reg = RQP_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (150 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 150, 0);
        data->reg = SCH_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (151 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 151, 0);
        data->reg = SPB_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_one;
    }
    if (152 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 152, 0);
        data->reg = RTP_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->field = UNICAST_DISTRIBUTION_MEMORY_ECC_1B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (153 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 153, 0);
        data->reg = RTP_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->field = UNICAST_DISTRIBUTION_MEMORY_ECC_2B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (154 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 154, 0);
        data->reg = FDT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_0_ECC_1B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (155 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 155, 0);
        data->reg = FDT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_1_ECC_1B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (156 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 156, 0);
        data->reg = FDT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_2_ECC_1B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (157 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 157, 0);
        data->reg = FDT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_3_ECC_1B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (158 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 158, 0);
        data->reg = FDT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_4_ECC_1B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (159 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 159, 0);
        data->reg = FDT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_5_ECC_1B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (160 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 160, 0);
        data->reg = FDT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_6_ECC_1B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (161 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 161, 0);
        data->reg = FDT_ECC_ERR_1B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_7_ECC_1B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (162 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 162, 0);
        data->reg = FDT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_0_ECC_2B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (163 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 163, 0);
        data->reg = FDT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_1_ECC_2B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (164 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 164, 0);
        data->reg = FDT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_2_ECC_2B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (165 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 165, 0);
        data->reg = FDT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_3_ECC_2B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (166 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 166, 0);
        data->reg = FDT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_4_ECC_2B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (167 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 167, 0);
        data->reg = FDT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_5_ECC_2B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (168 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 168, 0);
        data->reg = FDT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_6_ECC_2B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (169 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 169, 0);
        data->reg = FDT_ECC_ERR_2B_MONITOR_MEM_MASKr;
        data->field = IPT_PAYLOAD_7_ECC_2B_ERR_MASKf;
        data->mode = dnxc_mem_mask_mode_zero;
    }
    if (170 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_get(unit, table, 170, 0);
        data->reg = RQP_PAR_ERR_MEM_MASKr;
        data->mode = dnxc_mem_mask_mode_zero;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_ser_xor_mem_set(
    int unit)
{
    int index_index;
    dnx_data_intr_ser_xor_mem_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_ser;
    int table_index = dnx_data_intr_ser_table_xor_mem;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 46;
    table->info_get.key_size[0] = 46;

    
    table->values[0].default_val = "INVALIDm";
    table->values[1].default_val = "0";
    table->values[2].default_val = "0";
    table->values[3].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_ser_xor_mem_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_ser_table_xor_mem");

    
    default_data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->mem = INVALIDm;
    default_data->sram_banks_bits = 0;
    default_data->entry_used_bits = 0;
    default_data->flags = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->mem = CGM_PB_VSQ_PRMSm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 9;
        data->flags = 0;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->mem = CGM_IPP_MAPm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 9;
        data->flags = 0;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->mem = CGM_VSQF_PRMSm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 9;
        data->flags = 0;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->mem = CGM_VOQ_VSQS_PRMSm;
        data->sram_banks_bits = 4;
        data->entry_used_bits = 12;
        data->flags = 0;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->mem = CGM_VOQ_PROFILESm;
        data->sram_banks_bits = 2;
        data->entry_used_bits = 13;
        data->flags = 0;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->mem = CGM_VOQ_DRAM_BOUND_PRMSm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->mem = CGM_VOQ_DRAM_RECOVERY_PRMSm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->mem = CGM_SYS_RED_QSIZE_RANGESm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->mem = CGM_VOQ_DRAM_RECOVERY_CACHE_PRMSm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->mem = CGM_VOQ_GRNTD_PRMSm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->mem = DDHA_MACRO_0_PHYSICAL_ENTRY_BANKm;
        data->sram_banks_bits = 3;
        data->entry_used_bits = 11;
        data->flags = 0;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->mem = DDHA_MACRO_1_PHYSICAL_ENTRY_BANKm;
        data->sram_banks_bits = 2;
        data->entry_used_bits = 11;
        data->flags = 0;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->mem = DDHB_MACRO_0_PHYSICAL_ENTRY_BANKm;
        data->sram_banks_bits = 3;
        data->entry_used_bits = 11;
        data->flags = 0;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->mem = DDHB_MACRO_1_PHYSICAL_ENTRY_BANKm;
        data->sram_banks_bits = 3;
        data->entry_used_bits = 11;
        data->flags = 0;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->mem = DDHB_MACRO_2_PHYSICAL_ENTRY_BANKm;
        data->sram_banks_bits = 2;
        data->entry_used_bits = 11;
        data->flags = 0;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->mem = FDR_FDR_MCm;
        data->sram_banks_bits = 2;
        data->entry_used_bits = 10;
        data->flags = 0;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->mem = MTM_ING_BITMAP_MAPPING_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 8;
        data->flags = 0;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->mem = ECGM_QQST_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 6;
        data->flags = 0;
    }
    if (18 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->mem = ECGM_QDCT_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 6;
        data->flags = 0;
    }
    if (19 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->mem = ERPP_PER_PP_PORT_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 9;
        data->flags = 0;
    }
    if (20 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 0);
        data->mem = ERPP_OUTLIF_BTA_SOPm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 11;
        data->flags = 0;
    }
    if (21 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 21, 0);
        data->mem = ETPPA_LAYER_NWK_QOS_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 10;
        data->flags = 0;
    }
    if (22 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 22, 0);
        data->mem = ETPPA_PRP_EES_ARR_CONFIGURATIONm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 11;
        data->flags = 0;
    }
    if (23 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 23, 0);
        data->mem = ETPPB_NEW_QOS_MAPm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 10;
        data->flags = 0;
    }
    if (24 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 24, 0);
        data->mem = ETPPB_QOS_DP_MAPm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 10;
        data->flags = 0;
    }
    if (25 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 25, 0);
        data->mem = ETPPB_EGRESS_MEMBERSHIPm;
        data->sram_banks_bits = 2;
        data->entry_used_bits = 10;
        data->flags = 0;
    }
    if (26 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 26, 0);
        data->mem = ETPPB_SOURCE_ADRS_MAP_0m;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (27 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 27, 0);
        data->mem = ETPPB_SOURCE_ADRS_MAP_1m;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (28 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 28, 0);
        data->mem = ETPPB_ENC_2_ARR_0_FORMAT_CONFIGURATION_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (29 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 29, 0);
        data->mem = ETPPB_ENC_3_ARR_0_FORMAT_CONFIGURATION_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (30 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 30, 0);
        data->mem = ETPPB_ENC_4_ARR_0_FORMAT_CONFIGURATION_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (31 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 31, 0);
        data->mem = ETPPB_ENC_5_ARR_0_FORMAT_CONFIGURATION_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (32 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 32, 0);
        data->mem = ETPPC_NEW_QOS_MAPm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 10;
        data->flags = 0;
    }
    if (33 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 33, 0);
        data->mem = ETPPC_PROTECTION_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 12;
        data->flags = 0;
    }
    if (34 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 34, 0);
        data->mem = ETPPC_QOS_DP_MAPm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 10;
        data->flags = 0;
    }
    if (35 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 35, 0);
        data->mem = ETPPC_ENC_1_ARR_0_FORMAT_CONFIGURATION_TABLEm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 5;
        data->flags = 0;
    }
    if (36 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 36, 0);
        data->mem = IPPB_ETHERNET_OAM_OPCODE_MAPm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 7;
        data->flags = 0;
    }
    if (37 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 37, 0);
        data->mem = IPPD_DESTINATION_STATUSm;
        data->sram_banks_bits = 2;
        data->entry_used_bits = 11;
        data->flags = 0;
    }
    if (38 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 38, 0);
        data->mem = IPS_QTYPEm;
        data->sram_banks_bits = 2;
        data->entry_used_bits = 13;
        data->flags = 0;
    }
    if (39 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 39, 0);
        data->mem = IPS_QSPMm;
        data->sram_banks_bits = 3;
        data->entry_used_bits = 13;
        data->flags = 0;
    }
    if (40 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 40, 0);
        data->mem = IPS_QFMm;
        data->sram_banks_bits = 3;
        data->entry_used_bits = 13;
        data->flags = 0;
    }
    if (41 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 41, 0);
        data->mem = IPS_SPMm;
        data->sram_banks_bits = 2;
        data->entry_used_bits = 13;
        data->flags = 0;
    }
    if (42 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 42, 0);
        data->mem = IPS_CRBAL_THm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 4;
        data->flags = 0;
    }
    if (43 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 43, 0);
        data->mem = IPS_SLOW_FACTOR_THm;
        data->sram_banks_bits = 1;
        data->entry_used_bits = 4;
        data->flags = 0;
    }
    if (44 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 44, 0);
        data->mem = IPS_QPRIORITYm;
        data->sram_banks_bits = 2;
        data->entry_used_bits = 11;
        data->flags = 0;
    }
    if (45 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 45, 0);
        data->mem = INVALIDm;
        data->sram_banks_bits = 0;
        data->entry_used_bits = 0;
        data->flags = 0;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_ser_intr_exception_set(
    int unit)
{
    int index_index;
    dnx_data_intr_ser_intr_exception_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_ser;
    int table_index = dnx_data_intr_ser_table_intr_exception;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 12;
    table->info_get.key_size[0] = 12;

    
    table->values[0].default_val = "INVALIDr";
    table->values[1].default_val = "NULL";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_ser_intr_exception_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_ser_table_intr_exception");

    
    default_data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->intr = INVALIDr;
    default_data->exception_get_cb = NULL;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->intr = J2P_INT_CGM_CONGESTION_GLBL_DRAM_BDBS_FC_INT;
        data->exception_get_cb = dnx_intr_exceptional_dram_not_present;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->intr = J2P_INT_CGM_LOW_PRIORITY_GLBL_DRAM_BDBS_FC_LP_INT;
        data->exception_get_cb = dnx_intr_exceptional_dram_not_present;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->intr = J2P_INT_FDT_FDT_CORE_0_DTQ_OVF_INT;
        data->exception_get_cb = NULL;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->intr = J2P_INT_FDT_FDT_CORE_1_DTQ_OVF_INT;
        data->exception_get_cb = NULL;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->intr = J2P_INT_FDT_FDT_CORE_0_DTQ_UNDF_INT;
        data->exception_get_cb = NULL;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->intr = J2P_INT_FDT_FDT_CORE_1_DTQ_UNDF_INT;
        data->exception_get_cb = NULL;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->intr = J2P_INT_FDT_FDT_INBAND_ACK_OVF_INT;
        data->exception_get_cb = NULL;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->intr = J2P_INT_FDT_FDT_INBAND_ACK_UNDF_INT;
        data->exception_get_cb = NULL;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->intr = J2P_INT_FDTL_INTERRUPT_REGISTER_FIELD_0;
        data->exception_get_cb = NULL;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->intr = J2P_INT_FDTL_INTERRUPT_REGISTER_FIELD_1;
        data->exception_get_cb = NULL;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->intr = J2P_INT_FDTL_INTERRUPT_REGISTER_FIELD_2;
        data->exception_get_cb = NULL;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_intr_exception_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->intr = J2P_INT_FDTL_INTERRUPT_REGISTER_FIELD_3;
        data->exception_get_cb = NULL;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_ser_static_mem_set(
    int unit)
{
    int index_index;
    dnx_data_intr_ser_static_mem_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_ser;
    int table_index = dnx_data_intr_ser_table_static_mem;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 1;
    table->info_get.key_size[0] = 1;

    
    table->values[0].default_val = "INVALIDm";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_ser_static_mem_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_ser_table_static_mem");

    
    default_data = (dnx_data_intr_ser_static_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->mem = INVALIDm;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_intr_ser_static_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_static_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->mem = ETPPA_PRP_EES_ARR_CONFIGURATIONm;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_ser_dynamic_mem_set(
    int unit)
{
    int index_index;
    dnx_data_intr_ser_dynamic_mem_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_ser;
    int table_index = dnx_data_intr_ser_table_dynamic_mem;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 3;
    table->info_get.key_size[0] = 3;

    
    table->values[0].default_val = "INVALIDm";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_ser_dynamic_mem_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_ser_table_dynamic_mem");

    
    default_data = (dnx_data_intr_ser_dynamic_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->mem = INVALIDm;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_intr_ser_dynamic_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_dynamic_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->mem = IPPB_MEM_1E00000m;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_dynamic_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->mem = IPPB_MEM_1E10000m;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_dynamic_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->mem = IPPB_MEM_1E20000m;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_ser_mdb_mem_map_set(
    int unit)
{
    int index_index;
    dnx_data_intr_ser_mdb_mem_map_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_ser;
    int table_index = dnx_data_intr_ser_table_mdb_mem_map;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 8;
    table->info_get.key_size[0] = 8;

    
    table->values[0].default_val = "INVALIDm";
    table->values[1].default_val = "INVALIDm";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_ser_mdb_mem_map_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_ser_table_mdb_mem_map");

    
    default_data = (dnx_data_intr_ser_mdb_mem_map_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->acc_mem = INVALIDm;
    default_data->phy_mem = INVALIDm;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_intr_ser_mdb_mem_map_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mdb_mem_map_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->acc_mem = DDHA_MACRO_0_ENTRY_BANKm;
        data->phy_mem = DDHA_MACRO_0_PHYSICAL_ENTRY_BANKm;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mdb_mem_map_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->acc_mem = DDHA_MACRO_1_ENTRY_BANKm;
        data->phy_mem = DDHA_MACRO_1_PHYSICAL_ENTRY_BANKm;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mdb_mem_map_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->acc_mem = DDHB_MACRO_0_ENTRY_BANKm;
        data->phy_mem = DDHB_MACRO_0_PHYSICAL_ENTRY_BANKm;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mdb_mem_map_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->acc_mem = DDHB_MACRO_1_ENTRY_BANKm;
        data->phy_mem = DDHB_MACRO_1_PHYSICAL_ENTRY_BANKm;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_mdb_mem_map_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->acc_mem = DDHB_MACRO_2_ENTRY_BANKm;
        data->phy_mem = DDHB_MACRO_2_PHYSICAL_ENTRY_BANKm;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2p_a0_dnx_data_intr_ser_severity_mem_set(
    int unit)
{
    int index_index;
    dnx_data_intr_ser_severity_mem_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_intr;
    int submodule_index = dnx_data_intr_submodule_ser;
    int table_index = dnx_data_intr_ser_table_severity_mem;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 28;
    table->info_get.key_size[0] = 28;

    
    table->values[0].default_val = "INVALIDm";
    table->values[1].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_intr_ser_severity_mem_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_intr_ser_table_severity_mem");

    
    default_data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->mem = INVALIDm;
    default_data->severity = 0;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->mem = CGM_IPP_MAPm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->mem = CGM_LATENCY_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->mem = CGM_SYSTEM_RED_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->mem = CGM_VOQ_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->mem = CGM_VSQC_SRAM_BUFFERS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->mem = CGM_VSQC_SRAM_PDS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->mem = CGM_VSQC_WORDS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->mem = CGM_VSQD_SRAM_BUFFERS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->mem = CGM_VSQD_SRAM_PDS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->mem = CGM_VSQD_WORDS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->mem = CGM_VSQE_SRAM_BUFFERS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->mem = CGM_VSQE_SRAM_PDS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->mem = CGM_VSQE_WORDS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->mem = CGM_VSQF_SRAM_BUFFERS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->mem = CGM_VSQF_SRAM_PDS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->mem = CGM_VSQF_WORDS_STATEm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->mem = ESB_FLEXMm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->mem = ESB_SDMm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (18 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->mem = ESB_EOBMm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (19 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->mem = ESB_FBMm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (20 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 0);
        data->mem = ESB_HPMm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (21 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 21, 0);
        data->mem = ESB_LBMm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (22 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 22, 0);
        data->mem = ESB_TPMm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (23 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 23, 0);
        data->mem = EPNI_SATMm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (24 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 24, 0);
        data->mem = EPNI_ASMm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (25 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 25, 0);
        data->mem = EPNI_ACMm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (26 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 26, 0);
        data->mem = EPNI_SPECIAL_IFC_SHARED_BUFFERm;
        data->severity = SOC_MEM_SEVERE_HIGH;
    }
    if (27 < table->keys[0].size)
    {
        data = (dnx_data_intr_ser_severity_mem_t *) dnxc_data_mgmt_table_data_get(unit, table, 27, 0);
        data->mem = OAMP_RXP_R_MEP_INDEX_FIFOm;
        data->severity = SOC_MEM_SEVERE_MEDIUM;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}



shr_error_e
j2p_a0_data_intr_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_intr;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_intr_submodule_general;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_intr_general_define_nof_interrupts;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_intr_general_nof_interrupts_set;
    data_index = dnx_data_intr_general_define_epni_ebd_interrupt_assert_enable;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_intr_general_epni_ebd_interrupt_assert_enable_set;

    

    
    data_index = dnx_data_intr_general_table_active_on_init;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_general_active_on_init_set;
    data_index = dnx_data_intr_general_table_disable_on_init;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_general_disable_on_init_set;
    data_index = dnx_data_intr_general_table_disable_print_on_init;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_general_disable_print_on_init_set;
    data_index = dnx_data_intr_general_table_block_intr_field_mapping;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_general_block_intr_field_mapping_set;
    data_index = dnx_data_intr_general_table_skip_clear_on_init;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_general_skip_clear_on_init_set;
    data_index = dnx_data_intr_general_table_force_unmask_on_init;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_general_force_unmask_on_init_set;
    data_index = dnx_data_intr_general_table_skip_clear_on_regress;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_general_skip_clear_on_regress_set;
    
    submodule_index = dnx_data_intr_submodule_ser;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_intr_ser_define_tcam_protection_issue;
    define = &submodule->defines[data_index];
    define->set = j2p_a0_dnx_data_intr_ser_tcam_protection_issue_set;

    

    
    data_index = dnx_data_intr_ser_table_mem_mask;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_ser_mem_mask_set;
    data_index = dnx_data_intr_ser_table_xor_mem;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_ser_xor_mem_set;
    data_index = dnx_data_intr_ser_table_intr_exception;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_ser_intr_exception_set;
    data_index = dnx_data_intr_ser_table_static_mem;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_ser_static_mem_set;
    data_index = dnx_data_intr_ser_table_dynamic_mem;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_ser_dynamic_mem_set;
    data_index = dnx_data_intr_ser_table_mdb_mem_map;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_ser_mdb_mem_map_set;
    data_index = dnx_data_intr_ser_table_severity_mem;
    table = &submodule->tables[data_index];
    table->set = j2p_a0_dnx_data_intr_ser_severity_mem_set;

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


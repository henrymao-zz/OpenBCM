/*
 * 
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * SOC RAMON FABRIC CELL
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif

#define BSL_LOG_MODULE BSL_LS_SOCDNX_FABRIC
#include <shared/bsl.h>
#include <shared/utilex/utilex_bitstream.h>

#include <soc/mcm/memregs.h>
#include <soc/error.h>
#include <soc/defs.h>

#include <soc/dnxc/error.h>
#include <soc/dnxc/dnxc_cells_buffer.h>
#include <soc/sand/sand_mem.h>

#include <soc/dnxf/cmn/dnxf_drv.h>

#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_device.h>
#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_fabric.h>
#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_port.h>

#include <soc/dnxf/ramon/ramon_fabric_cell.h>
#include <soc/dnxf/ramon/ramon_fabric_status.h>

#define DNXF_RAMON_DATA_CELL_DATA_REG_FIELD_SIZE_BITS (256)

shr_error_e
soc_ramon_sr_cell_format(
    int unit,
    const dnxc_vsc256_sr_cell_t * cell,
    int buf_size_bytes,
    uint32 *buf)
{
    shr_error_e rc;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(buf, 0, buf_size_bytes);

    if (buf_size_bytes < RAMON_DATA_CELL_BYTE_SIZE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "SR cell minimum buffer size is %d", RAMON_DATA_CELL_BYTE_SIZE);
    }

    rc = soc_dnxc_vsc256_sr_cell_build_header(unit, cell, buf_size_bytes - (RAMON_SR_DATA_CELL_PAYLOAD_LENGTH / 8),
                                              (uint32 *) (((uint8 *) buf) + (RAMON_SR_DATA_CELL_PAYLOAD_LENGTH / 8) +
                                                          dnxf_data_fabric.
                                                          cell.source_routed_cells_header_offset_get(unit) / 8));
    SHR_IF_ERR_EXIT(rc);

    SHR_BITCOPY_RANGE(buf, RAMON_SR_DATA_CELL_PAYLOAD_START, cell->payload.data, 0, RAMON_SR_DATA_CELL_PAYLOAD_LENGTH);

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
soc_ramon_sr_cell_send(
    int unit,
    const dnxc_vsc256_sr_cell_t * cell)
{
    uint8 buf[RAMON_DATA_CELL_BYTE_SIZE];
    shr_error_e rc;
    soc_port_t first_link, inner_link;
    soc_reg_above_64_val_t reg_val;
    uint32 reg_val32;
    int blk_id = 0;
    SHR_FUNC_INIT_VARS(unit);

    rc = soc_ramon_sr_cell_format(unit, cell, RAMON_DATA_CELL_BYTE_SIZE, (uint32 *) buf);
    SHR_IF_ERR_EXIT(rc);

    switch (cell->header.source_level)
    {
        case bcmFabricDeviceTypeFIP:
            first_link = cell->header.fip_link;
            break;
        case bcmFabricDeviceTypeFE1:
            first_link = cell->header.fe1_link;
            break;
        case bcmFabricDeviceTypeFE2:
            first_link = cell->header.fe2_link;
            break;
        case bcmFabricDeviceTypeFE3:
            first_link = cell->header.fe3_link;
            break;
        case bcmFabricDeviceTypeFAP:
        case bcmFabricDeviceTypeFE13:
        case bcmFabricDeviceTypeFOP:
        case bcmFabricDeviceTypeUnknown:
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Can't retrieve first link from cell");
    }

    rc = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_drv_link_to_block_mapping,
                               (unit, first_link, &blk_id, &inner_link, SOC_BLK_DCML));
    SHR_IF_ERR_EXIT(rc);

    SOC_REG_ABOVE_64_CLEAR(reg_val);
    SHR_BITCOPY_RANGE(reg_val, 0, (uint32 *) buf, 0 * 256, 256);
    SHR_IF_ERR_EXIT(soc_reg_above_64_set(unit, DCML_TX_CPU_CELL_DATA_0r, blk_id, 0, reg_val));

    SOC_REG_ABOVE_64_CLEAR(reg_val);
    SHR_BITCOPY_RANGE(reg_val, 0, (uint32 *) buf, 1 * 256, 256);
    SHR_IF_ERR_EXIT(soc_reg_above_64_set(unit, DCML_TX_CPU_CELL_DATA_1r, blk_id, 0, reg_val));

    SOC_REG_ABOVE_64_CLEAR(reg_val);
    SHR_BITCOPY_RANGE(reg_val, 0, (uint32 *) buf, 2 * 256, 120);
    SHR_IF_ERR_EXIT(soc_reg_above_64_set(unit, DCML_TX_CPU_CELL_HEADERr, blk_id, 0, reg_val));

    rc = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_drv_link_to_block_mapping,
                               (unit, first_link, &blk_id, &inner_link, SOC_BLK_LCM));
    SHR_IF_ERR_EXIT(rc);

    reg_val32 = 0;
    soc_reg_field_set(unit, LCM_TX_CPU_CELL_OUTPUT_LINKr, &reg_val32, TX_CPU_CELL_LINK_NUMf, inner_link);

    soc_reg_field_set(unit, LCM_TX_CPU_CELL_OUTPUT_LINKr, &reg_val32, TX_CPU_CELL_SIZEf,
                      (DNXC_FABRIC_CELL_SOURCE_ROUTED_CELL_SIZE - 1));
    SHR_IF_ERR_EXIT(soc_reg32_set(unit, LCM_TX_CPU_CELL_OUTPUT_LINKr, blk_id, 0, reg_val32));

    SHR_IF_ERR_EXIT(soc_reg32_set(unit, LCM_TX_CPU_CELL_TRGr, blk_id, 0, 0x1));

exit:
    SHR_FUNC_EXIT;

}

shr_error_e
soc_ramon_control_cell_filter_set(
    int unit,
    uint32 flags,
    soc_dnxc_control_cell_types_t cell_type,
    uint32 array_size,
    soc_dnxc_control_cell_filter_type_t * filter_type_arr,
    uint32 *filter_type_val)
{
    int i;
    uint32 reg_val32;
    soc_reg_above_64_val_t reg_val, mask_val;
    soc_dnxf_cell_filter_mode_t filter_mode = (soc_dnxf_cell_filter_mode_t) soc_dnxf_control_cell_filter_copy_mode;

    SHR_FUNC_INIT_VARS(unit);

    if ((flags & SOC_CELL_FILTER_FLAG_DONT_FORWARD) && (flags & SOC_CELL_FILTER_FLAG_DONT_TRAP))
    {
        filter_mode = (soc_dnxf_cell_filter_mode_t) soc_dnxf_control_cell_filter_filter_mode;
    }
    else if (flags & SOC_CELL_FILTER_FLAG_DONT_FORWARD)
    {
        filter_mode = (soc_dnxf_cell_filter_mode_t) soc_dnxf_control_cell_filter_capture_mode;
    }
    else if (flags & SOC_CELL_FILTER_FLAG_DONT_TRAP)
    {
        filter_mode = (soc_dnxf_cell_filter_mode_t) soc_dnxf_control_cell_filter_normal_mode;
    }

    for (i = 0; i < dnxf_data_device.blocks.nof_instances_cch_get(unit); i++)
    {
        SHR_IF_ERR_EXIT(soc_reg32_get(unit, CCH_DEBUG_CONFIGURATIONSr, i, 0, &reg_val32));
        soc_reg_field_set(unit, CCH_DEBUG_CONFIGURATIONSr, &reg_val32, CAPTURE_OPERATIONf, filter_mode);

        soc_reg_field_set(unit, CCH_DEBUG_CONFIGURATIONSr, &reg_val32, AUTO_DOC_NAME_3f,
                          (cell_type == soc_dnxc_fe2_filtered_cell) ? 1 : 0);
        SHR_IF_ERR_EXIT(soc_reg32_set(unit, CCH_DEBUG_CONFIGURATIONSr, i, 0, reg_val32));
    }

    SOC_REG_ABOVE_64_CLEAR(reg_val);

    SOC_REG_ABOVE_64_ALLONES(mask_val);

    if (cell_type == soc_dnxc_flow_status_cell || cell_type == soc_dnxc_credit_cell)
    {
        for (i = 0; i < array_size; i++)
        {
            switch (filter_type_arr[i])
            {
                case soc_dnxc_filter_control_cell_type_source_device:
                    if ((filter_type_val[i] & (~0x7FF)) != 0)
                    {
                        SHR_ERR_EXIT(_SHR_E_PARAM, "source device id is out of range");
                    }
                    SHR_BITCOPY_RANGE(reg_val, RAMON_VSC256_CONTROL_CELL_SOURCE_ID_START, &(filter_type_val[i]), 0,
                                      RAMON_VSC256_CONTROL_CELL_SOURCE_ID_LENGTH);

                    SHR_BITCLR_RANGE(mask_val, RAMON_VSC256_CONTROL_CELL_SOURCE_ID_START,
                                     RAMON_VSC256_CONTROL_CELL_SOURCE_ID_LENGTH);
                    break;
                case soc_dnxc_filter_control_cell_type_dest_device:
                    if ((filter_type_val[i] & (~0x7FF)) != 0)
                    {
                        SHR_ERR_EXIT(_SHR_E_PARAM, "dest device id is out of range");
                    }
                    SHR_BITCOPY_RANGE(reg_val, RAMON_VSC256_CONTROL_CELL_DEST_DEVICE_START, &(filter_type_val[i]), 0,
                                      RAMON_VSC256_CONTROL_CELL_DEST_DEVICE_LENGTH);

                    SHR_BITCLR_RANGE(mask_val, RAMON_VSC256_CONTROL_CELL_DEST_DEVICE_START,
                                     RAMON_VSC256_CONTROL_CELL_DEST_DEVICE_LENGTH);
                    break;
                default:
                    SHR_ERR_EXIT(_SHR_E_PARAM, "unsupported filter type");
            }
        }
    }
    else if (cell_type == soc_dnxc_reachability_cell)
    {
        SHR_BITCOPY_RANGE(reg_val, RAMON_VSC256_CONTROL_CELL_REACHABILITY_SOURCE_ID_START, &(filter_type_val[0]), 0,
                          RAMON_VSC256_CONTROL_CELL_SOURCE_ID_LENGTH);

        SHR_BITCLR_RANGE(mask_val, RAMON_VSC256_CONTROL_CELL_REACHABILITY_SOURCE_ID_START,
                         RAMON_VSC256_CONTROL_CELL_SOURCE_ID_LENGTH);
    }
    else
    {
    }

    SHR_BITCOPY_RANGE(reg_val, RAMON_VSC256_CONTROL_CELL_CONTROL_TYPE_START, &cell_type, 0,
                      RAMON_VSC256_CONTROL_CELL_CONTROL_TYPE_LENGTH);

    SHR_BITCLR_RANGE(mask_val, RAMON_VSC256_CONTROL_CELL_CONTROL_TYPE_START,
                     RAMON_VSC256_CONTROL_CELL_CONTROL_TYPE_LENGTH);

    for (i = 0; i < dnxf_data_device.blocks.nof_instances_cch_get(unit); i++)
    {
        SHR_IF_ERR_EXIT(soc_reg_above_64_set(unit, CCH_CAPTURE_FILTER_CELL_0r, i, 0, reg_val));
        SHR_IF_ERR_EXIT(soc_reg_above_64_set(unit, CCH_CAPTURE_FILTER_MASK_0r, i, 0, mask_val));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
soc_ramon_control_cell_filter_clear(
    int unit)
{
    soc_reg_above_64_val_t reg_val;
    uint32 reg_val32;
    int i;
    SHR_FUNC_INIT_VARS(unit);

    SOC_REG_ABOVE_64_CLEAR(reg_val);

    for (i = 0; i < dnxf_data_device.blocks.nof_instances_cch_get(unit); i++)
    {
        SHR_IF_ERR_EXIT(soc_reg_above_64_set(unit, CCH_CAPTURE_FILTER_CELL_0r, i, 0, reg_val));

        SHR_IF_ERR_EXIT(soc_reg_above_64_set(unit, CCH_CAPTURE_FILTER_MASK_0r, i, 0, reg_val));

        SHR_IF_ERR_EXIT(soc_reg32_get(unit, CCH_DEBUG_CONFIGURATIONSr, i, 0, &reg_val32));
        soc_reg_field_set(unit, CCH_DEBUG_CONFIGURATIONSr, &reg_val32, AUTO_DOC_NAME_3f, 0);
        SHR_IF_ERR_EXIT(soc_reg32_set(unit, CCH_DEBUG_CONFIGURATIONSr, i, 0, reg_val32));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
soc_ramon_control_cell_filter_receive(
    int unit,
    soc_dnxc_captured_control_cell_t * data_out)
{
    soc_reg_above_64_val_t reg_val;
    int i;
    uint32 valid_cell_reg;
    SHR_FUNC_INIT_VARS(unit);

    for (i = 0; i < dnxf_data_device.blocks.nof_instances_cch_get(unit); i++)
    {
        SHR_IF_ERR_EXIT(soc_reg32_get(unit, CCH_CAPTURED_CELL_VALIDr, i, 0, &valid_cell_reg));
        if (valid_cell_reg)
        {
            data_out->valid = 1;
            break;
        }
    }

    if (data_out->valid)
    {
        SHR_IF_ERR_EXIT(soc_reg_above_64_get(unit, CCH_CAPTURED_CELLr, i, 0, reg_val));

        SHR_BITCOPY_RANGE((uint32 *) &(data_out->control_type), 0, reg_val,
                          RAMON_VSC256_CONTROL_CELL_CONTROL_TYPE_START, RAMON_VSC256_CONTROL_CELL_CONTROL_TYPE_LENGTH);

        switch (data_out->control_type)
        {
            case soc_dnxc_flow_status_cell:
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->dest_port), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_FSM_DEST_PORT_START,
                                  RAMON_VSC256_CONTROL_CELL_FSM_DEST_PORT_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->src_queue_num), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_FSM_SRC_QUEUE_NUM_START,
                                  RAMON_VSC256_CONTROL_CELL_FSM_SRC_QUEUE_NUM_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->flow_id), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_FSM_FLOW_ID_START,
                                  RAMON_VSC256_CONTROL_CELL_FSM_FLOW_ID_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->source_device), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_SOURCE_ID_START,
                                  RAMON_VSC256_CONTROL_CELL_SOURCE_ID_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->dest_device), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_DEST_DEVICE_START,
                                  RAMON_VSC256_CONTROL_CELL_DEST_DEVICE_LENGTH);
                break;
            case soc_dnxc_credit_cell:
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->dest_queue_num), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_CREDIT_DEST_Q_NUM_START,
                                  RAMON_VSC256_CONTROL_CELL_CREDIT_DEST_Q_NUM_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->sub_flow_id), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_CREDIT_SUB_FLOW_ID_START,
                                  RAMON_VSC256_CONTROL_CELL_CREDIT_SUB_FLOW_ID_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->flow_id), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_CREDIT_FLOW_ID_START,
                                  RAMON_VSC256_CONTROL_CELL_CREDIT_FLOW_ID_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->source_device), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_SOURCE_ID_START,
                                  RAMON_VSC256_CONTROL_CELL_SOURCE_ID_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->dest_device), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_DEST_DEVICE_START,
                                  RAMON_VSC256_CONTROL_CELL_DEST_DEVICE_LENGTH);
                break;
            case soc_dnxc_reachability_cell:
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->reachability_bitmap), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_REACHABILITY_BITMAP_START,
                                  RAMON_VSC256_CONTROL_CELL_REACHABILITY_BITMAP_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->base_index), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_REACHABILITY_BASE_ID_START,
                                  RAMON_VSC256_CONTROL_CELL_REACHABILITY_BASE_ID_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->source_link_number), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_REACHABILITY_SRC_LINK_NUM_START,
                                  RAMON_VSC256_CONTROL_CELL_REACHABILITY_SRC_LINK_NUM_LENGTH);
                SHR_BITCOPY_RANGE((uint32 *) &(data_out->source_device), 0, reg_val,
                                  RAMON_VSC256_CONTROL_CELL_REACHABILITY_SOURCE_ID_START,
                                  RAMON_VSC256_CONTROL_CELL_SOURCE_ID_LENGTH);
                break;
            default:
                SHR_ERR_EXIT(_SHR_E_PARAM, "unsupported filter type");
        }
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
soc_ramon_fabric_cell_get(
    int unit,
    soc_dnxc_fabric_cell_entry_t entry)
{
    uint32 reg = 0;
    uint32 is_fifo_not_empty = 0;
    int found_cell = 0;
    int blk_idx = 0;
    SHR_FUNC_INIT_VARS(unit);

    for (blk_idx = 0; blk_idx < dnxf_data_device.blocks.nof_instances_dcml_get(unit); blk_idx++)
    {
        SHR_IF_ERR_EXIT(soc_reg32_get(unit, DCML_INTERRUPT_REGISTERr, blk_idx, 0, &reg));
        is_fifo_not_empty = soc_reg_field_get(unit, DCML_INTERRUPT_REGISTERr, reg, DFL_CPU_CELL_FIFO_NE_INTf);

        if (is_fifo_not_empty)
        {
            sal_memset(entry, 0x00, sizeof(soc_dnxc_fabric_cell_entry_t));

            SHR_IF_ERR_EXIT(sand_mem_array_wide_access
                            (unit, SOC_MEM_NO_FLAGS, DCML_AUTO_DOC_NAME_55m, 0, DCML_BLOCK(unit, blk_idx), 0, entry,
                             1));
            found_cell = 1;
            break;
        }
    }

    if (!found_cell)
    {
        SHR_SET_CURRENT_ERR(_SHR_E_EMPTY);
        SHR_EXIT();
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
soc_ramon_fabric_cell_parse_table_get(
    int unit,
    soc_dnxc_fabric_cell_entry_t entry,
    soc_dnxc_fabric_cell_type_t * cell_type,
    soc_dnxc_fabric_cell_parse_table_t * parse_table)
{
    int line = 0;
    uint32 data_in_msb = 0, cell_size_bytes = 0;
    soc_dnxc_fabric_cell_parse_table_t captured_cell_common_table[] = { SOC_RAMON_FABRIC_CAPTURED_CELL_COMMON_FORMAT };
    SHR_FUNC_INIT_VARS(unit);

    soc_dnxc_fabric_cell_table_field_row_get(unit, soc_dnxc_fabric_cell_field_data_in_msb, captured_cell_common_table,
                                             &line);
    SHR_BITCOPY_RANGE(&data_in_msb, 0, entry, captured_cell_common_table[line].src_start_bit,
                      captured_cell_common_table[line].length);

    soc_dnxc_fabric_cell_table_field_row_get(unit, soc_dnxc_fabric_cell_field_cell_size, captured_cell_common_table,
                                             &line);
    SHR_BITCOPY_RANGE(&cell_size_bytes, 0, entry, captured_cell_common_table[line].src_start_bit,
                      captured_cell_common_table[line].length);

    cell_size_bytes += 1;

    soc_dnxc_fabric_cell_table_field_row_get(unit, soc_dnxc_fabric_cell_field_cell_type, captured_cell_common_table,
                                             &line);
    SHR_BITCOPY_RANGE((uint32 *) cell_type, 0, entry, captured_cell_common_table[line].src_start_bit,
                      captured_cell_common_table[line].length);

    if (*cell_type == soc_dnxc_fabric_cell_type_sr_cell)
    {
        soc_dnxc_fabric_cell_parse_table_t temp_table_src[] = SOC_RAMON_FABRIC_CELL_CAPTURED_SR_CELL_FORMAT_TABLE;

        sal_memcpy(parse_table, temp_table_src, sizeof(temp_table_src));

        soc_dnxc_fabric_cell_table_field_row_get(unit, soc_dnxc_fabric_cell_field_payload, parse_table, &line);

        if (cell_size_bytes <= SOC_RAMON_FABRIC_CAPTURED_CELL_SMALL_CELL_MAX_SIZE)
        {

            if (data_in_msb)
            {

                parse_table[line].src_start_bit += SOC_RAMON_FABRIC_CAPTURED_CELL_DATA_IN_MSB_OFFSET;
            }
            else
            {

            }

            parse_table[line].src_start_bit +=
                BYTES2BITS(SOC_RAMON_FABRIC_CAPTURED_CELL_SMALL_CELL_MAX_SIZE -
                           (DNXC_FABRIC_CELL_SOURCE_ROUTED_CELL_SIZE - 1));
            parse_table[line].length = BYTES2BITS(cell_size_bytes);
        }
        else
        {

        }

    }
    else
    {
        soc_dnxc_fabric_cell_parse_table_t temp_table_src[] = SOC_RAMON_FABRIC_CELL_CAPTURED_DATA_CELL_FORMAT_TABLE;

        sal_memcpy(parse_table, temp_table_src, sizeof(temp_table_src));
        soc_dnxc_fabric_cell_table_field_row_get(unit, soc_dnxc_fabric_cell_field_payload, parse_table, &line);

        if (cell_size_bytes <= SOC_RAMON_FABRIC_CAPTURED_CELL_SMALL_CELL_MAX_SIZE)
        {
            if (data_in_msb)
            {

                parse_table[line].src_start_bit += SOC_RAMON_FABRIC_CAPTURED_CELL_DATA_IN_MSB_OFFSET;
            }
            else
            {

                parse_table[line].dest_start_bit += SOC_RAMON_FABRIC_CAPTURED_CELL_DATA_IN_MSB_OFFSET;
                parse_table[line].length -= SOC_RAMON_FABRIC_CAPTURED_CELL_DATA_IN_MSB_OFFSET;
            }
        }

    }

    SHR_FUNC_EXIT;
}

shr_error_e
soc_ramon_dest_routed_cell_send(
    int unit,
    dnxc_dest_routed_cell_t * cell)
{
    uint32 header_buf[DNXC_DESTINATION_ROUTED_CELL_HEADER_SIZE_UINT32];
    soc_reg_above_64_val_t cell_header_reg;
    int dch_block = 0, links_count = 0, reg_arr_index = 0, max_reg_arr_index = 0, word_index = 0;
    int reg_bit_offset, bytes_written = 0, bytes_offset = 0, nof_bits_to_copy = 0;
    uint32 links_array[DNXF_DATA_MAX_PORT_GENERAL_NOF_LINKS] = { 0 };
    uint32 reg_val32, temp_val32;
    soc_reg_above_64_val_t reg_val;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(soc_ramon_fabric_reachability_status_get
                    (unit, cell->header.dest_modid, dnxf_data_port.general.nof_links_get(unit), links_array,
                     &links_count));
    if (links_count == 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Module ID %d not reachable ", cell->header.dest_modid);
    }

    dch_block = links_array[0] / dnxf_data_device.blocks.nof_links_in_dch_get(unit);

    sal_memset(header_buf, 0, WORDS2BYTES(DNXC_DESTINATION_ROUTED_CELL_HEADER_SIZE_UINT32));
    SHR_IF_ERR_EXIT(soc_dnxc_dest_routed_cell_build_header
                    (unit, cell, DNXC_DESTINATION_ROUTED_CELL_HEADER_SIZE_UINT32, header_buf));
    SOC_REG_ABOVE_64_CLEAR(cell_header_reg);
    SOC_REG_ABOVE_64_RANGE_COPY(cell_header_reg, 0, header_buf, 0, DNXC_DESTINATION_ROUTED_CELL_HEADER_SIZE_BITS);
    SHR_IF_ERR_EXIT(WRITE_DCH_TX_CPU_CELL_HEADERr(unit, dch_block, cell_header_reg));

    SHR_IF_ERR_EXIT(soc_reg32_get(unit, DCH_TX_CPU_CELL_INFOr, dch_block, 0, &reg_val32));
    soc_reg_field_set(unit, DCH_TX_CPU_CELL_INFOr, &reg_val32, TX_CPU_CELL_TWO_PIPESf,
                      dnxf_data_fabric.pipes.nof_pipes_get(unit) == 2 ? 1 : 0);
    soc_reg_field_set(unit, DCH_TX_CPU_CELL_INFOr, &reg_val32, TX_CPU_CELL_THREE_PIPESf,
                      dnxf_data_fabric.pipes.nof_pipes_get(unit) == 3 ? 1 : 0);
    soc_reg_field_set(unit, DCH_TX_CPU_CELL_INFOr, &reg_val32, TX_CPU_CELL_USE_MC_CELL_PRIOf, 0);
    soc_reg_field_set(unit, DCH_TX_CPU_CELL_INFOr, &reg_val32, TX_CPU_CELL_SIZEf, cell->payload_size - 1);
    SHR_IF_ERR_EXIT(soc_reg32_set(unit, DCH_TX_CPU_CELL_INFOr, dch_block, 0, reg_val32));

    SOC_REG_ABOVE_64_CLEAR(reg_val);
    max_reg_arr_index =
        BYTES2BITS(DNXC_VSC256_DESTINATION_ROUTED_CELL_PAYLOAD_SIZE_BYTES) /
        DNXF_RAMON_DATA_CELL_DATA_REG_FIELD_SIZE_BITS - 1;
    for (reg_arr_index = 0; reg_arr_index <= max_reg_arr_index; reg_arr_index++)
    {

        if (bytes_written >= cell->payload_size)
        {
            break;
        }
        for (word_index = 0; word_index < BITS2WORDS(DNXF_RAMON_DATA_CELL_DATA_REG_FIELD_SIZE_BITS); word_index++)
        {
            reg_bit_offset =
                DNXF_RAMON_DATA_CELL_DATA_REG_FIELD_SIZE_BITS - (word_index * WORDS2BITS(1)) - WORDS2BITS(1);
            bytes_offset =
                reg_arr_index * BITS2BYTES(DNXF_RAMON_DATA_CELL_DATA_REG_FIELD_SIZE_BITS) +
                (word_index * WORDS2BYTES(1));
            bytes_written =
                reg_arr_index * BITS2BYTES(DNXF_RAMON_DATA_CELL_DATA_REG_FIELD_SIZE_BITS) +
                ((word_index + 1) * WORDS2BYTES(1));

            if (bytes_offset > cell->payload_size)
            {
                nof_bits_to_copy = BYTES2BITS(bytes_offset - cell->payload_size + DNXC_FTMH_CRC_SIZE_BYTES);
            }
            else
            {
                nof_bits_to_copy = WORDS2BITS(1);
            }

            temp_val32 = _shr_uint32_read(&(cell->payload[bytes_offset]));
            SHR_BITCOPY_RANGE(reg_val, reg_bit_offset, &temp_val32, 0, nof_bits_to_copy);

            if (bytes_written >= cell->payload_size)
            {
                break;
            }
        }

        SHR_IF_ERR_EXIT(soc_reg_above_64_set
                        (unit, DCH_TX_CPU_CELL_DATAr, dch_block, max_reg_arr_index - reg_arr_index, reg_val));

    }

    SHR_IF_ERR_EXIT(WRITE_DCH_TX_CPU_CELL_TRGr(unit, dch_block, 1));

exit:
    SHR_FUNC_EXIT;
}

#undef BSL_LOG_MODULE

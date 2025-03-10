/*
 * 
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#if defined(INCLUDE_LIB_CINT)
#include <soc/drv.h>
#include <appl/diag/system.h>
#include <appl/diag/diag.h>

#include <shared/bsl.h>
#include <sdk_config.h>

#include <soc/i2c.h>
#include <soc/cm.h>
#include <soc/drv.h>
#include <soc/error.h>
#include <soc/register.h>
#include <soc/mem.h>
#include <soc/intr.h>

#include <cint_config.h>
#include <cint_types.h>
#include <cint_porting.h>

#if defined(BCM_SAND_SUPPORT) || defined(BCM_ESW_SUPPORT)
#include <bcm/port.h>
#include <soc/mcm/memregs.h>
#if defined(BCM_DNX_SUPPORT)  || defined(BCM_DNXF_SUPPORT)
#include <soc/sand/sand_mem.h>
#endif

#if defined(BCM_PETRA_SUPPORT)
#include <soc/dpp/drv.h>
#include <soc/dcmn/dcmn_mem.h>
#include <shared/swstate/access/sw_state_access.h>
#include <bcm_int/dpp/counters.h>
#include <bcm_int/dpp/stat.h>
#endif

#if defined(BCM_PETRA_SUPPORT) || defined(BCM_DFE_SUPPORT)
#include <appl/diag/dcmn/diag.h>
#include <appl/diag/shell.h>
#include <appl/diag/dcmn/init_deinit.h>
#endif

#include <sal/core/libc.h>
#include <sal/core/boot.h>
#include <sal/appl/i2c.h>

#if defined(BCM_PETRA_SUPPORT)
#include <soc/dpp/ARAD/arad_tbl_access.h>
#include <soc/dpp/ARAD/arad_init.h>
#include <soc/dpp/ARAD/arad_sw_db.h>
#include <soc/dpp/ARAD/arad_ingress_packet_queuing.h>
#include <soc/dpp/multicast.h>
#endif
#ifdef BCM_JERICHO_SUPPORT
#include <soc/dpp/JER/jer_init.h>
#include <soc/dpp/multicast.h>
#endif

#ifdef BCM_88950_A0
#include <soc/dfe/fe3200/fe3200_drv.h>
#endif
#ifdef BCM_88790_A0
#include <soc/dnxf/ramon/ramon_drv.h>
#endif
#ifdef BCM_DNX_SUPPORT
#include <soc/dnx/drv.h>
#include <soc/dnxc/drv_dnxc_utils.h>
#endif
#ifdef BCM_CMICM_SUPPORT
#include <soc/cmicm.h>
#endif

#if defined(BCM_DFE_SUPPORT) || defined(BCM_PETRA_SUPPORT)
#if defined(INCLUDE_INTR)
#include <appl/dcmn/rx_los/rx_los.h>
#endif
#endif
#if defined(BCM_DNX_SUPPORT)
#include <appl/diag/dnx/diag_dnx_diag.h>
#endif
#endif /* defined(BCM_SAND_SUPPORT) || defined(BCM_ESW_SUPPORT) */

#if (defined(BCM_DNX_SUPPORT)  || defined(BCM_DNXF_SUPPORT) ) && defined(BCM_ACCESS_SUPPORT)
#include <soc/access/pci.h>
#endif


#if defined(BCM_SAND_SUPPORT) || defined(BCM_ESW_SUPPORT)

/* fill the table with the same given entry, using the device specific wrapper for the SLAM DMA function */
static int diag_mem_fill(int unit, char *name, void *buffer) /* buffer needs to be allocated by soc_cm_salloc() / diag_pointer(unit, "dmabuf_alloc", void **pointer_var, char *size) */
{
    int rv = SOC_E_NONE;

    if (!SOC_UNIT_VALID(unit)) {
        cli_out("Invalid unit.\n");
        return SOC_E_UNIT;
    }
    if (name == NULL) {
        cli_out("NULL mem name given.\n");
        return SOC_E_PARAM;
    }

#ifdef BCM_ACCESS_SUPPORT
    if (ACCESS_IS_INITIALIZED(unit))
    {
        access_runtime_info_t *runtime_info = ACCESS_RUNTIME_INFO(unit); /* Access information for the device */
        const access_device_type_info_t *device_info = runtime_info->device_type_info;  /* Constant access information for the device type */
        const access_device_regmem_t *rm_info = NULL;
        access_block_instance_num_t inst_i = ACCESS_ALL_BLOCK_INSTANCES;
        access_local_regmem_id_t regmem_i;
        int parse_memory_name_rv, first_array_ind, last_array_ind;
        uint16 arr_ind = -1;

        parse_memory_name_rv = access_parse_memory_name(runtime_info, name, &arr_ind, &inst_i, &regmem_i);
        /* If access_parse_memory_name returns -1, there is an error/failure from the user input */
        if (parse_memory_name_rv < 0)
        {
            return SOC_E_PARAM;
        }
        /* If access_parse_memory_name returns 1, there is no exact match of memory name */
        if (parse_memory_name_rv == 1)
        {
            cli_out("Unknown memory %s:\n", name);
            return SOC_E_PARAM;
        }
        /* Memory to access */
        rm_info = device_info->local_regs + regmem_i;

        if ((rm_info->flags & ACCESS_REGMEM_FLAG_IS_ALIAS) != 0)
        {
            regmem_i = rm_info->u.mem.alias_regmem;
            rm_info = device_info->local_regs + regmem_i;
        }

        if (arr_ind == (uint16)(-1) && rm_info->nof_array_indices > 1)
        {
            cli_out("WARNING: writing to all array indices of register array %s:\n", access_global_names[global_regmem_name_indices[rm_info->global_regmem_id]]);
        }

        if (arr_ind == (uint16)(-1))
        {
            first_array_ind = rm_info->first_array_index;
            last_array_ind = rm_info->nof_array_indices + rm_info->first_array_index - 1;
        }
        else
        {
            first_array_ind = last_array_ind = arr_ind;
        }

        /* Loop over array indices to write the memory to each one */
        for (arr_ind = first_array_ind; arr_ind <= last_array_ind; arr_ind++)
        {
            if (buffer && (rv = access_local_regmem_sbusdma(runtime_info, FLAG_ACCESS_IS_WRITE | FLAG_ACCESS_IS_FILL, regmem_i, inst_i, arr_ind, 0, rm_info->u.mem.mem_nof_elements, 0, buffer)))
            {
                cli_out("ERROR: access_local_regmem_sbusdma failed to write memory ");
                diag_print_regmem_info(runtime_info, rm_info, inst_i, arr_ind, -1);
                return SOC_E_PARAM;
            }
        }
    }
#endif /* BCM_ACCESS_SUPPORT */
    else
    {
        int copyno;
        soc_mem_t mem;
        unsigned array_index;

        if (parse_memory_name(unit, &mem, name, &copyno, &array_index) < 0) {
            cli_out("ERROR: unknown table \"%s\"\n",name);
            return SOC_E_PARAM;
        }
        if (buffer && ((rv = soc_mem_fill(unit, mem, copyno, buffer)))) {
            cli_out("soc_mem_fill() failed in memory %s.%d returned %d\n",
                    SOC_MEM_UFNAME(unit, mem), copyno==COPYNO_ALL ? 0 : copyno, rv);
        }
    }
    return rv;
}

/* fill the table with the same given entry, using the device specific wrapper for the SLAM DMA function */
static int diag_mem_array_fill_range(
    int unit,              /* unit of the memory */
    char *name,            /* Memory, block and array index to be written to */
    unsigned min_ar_index, /* min array index to be written to, not used in memories which are not arrays */
    unsigned max_ar_index, /* max array index to be written to, not used in memories which are not arrays */
    int index_min,         /* first memory index to write to */
    int index_max,         /* last memory index to write to */
    void *buffer)          /* buffer of they entry to write. If the memory can be written to by SLAM DMA,
                              then the buffer must be allocated using soc_cm_salloc() / diag_pointer(unit, "dmabuf_alloc", void **pointer_var, char *size). */
{
    int rv = SOC_E_NONE;

    if (!SOC_UNIT_VALID(unit)) {
        cli_out("Invalid unit.\n");
        return SOC_E_UNIT;
    }
    if (name == NULL) {
        cli_out("NULL mem name given.\n");
        return SOC_E_PARAM;
    }

#ifdef BCM_ACCESS_SUPPORT
    if (ACCESS_IS_INITIALIZED(unit))
    {
        access_runtime_info_t *runtime_info = ACCESS_RUNTIME_INFO(unit); /* Access information for the device */
        const access_device_type_info_t *device_info = runtime_info->device_type_info;  /* Constant access information for the device type */
        const access_device_regmem_t *rm_info = NULL;
        access_block_instance_num_t inst_i = ACCESS_ALL_BLOCK_INSTANCES;
        access_local_regmem_id_t regmem_i;
        int parse_memory_name_rv;
        uint16 arr_ind = -1;

        parse_memory_name_rv = access_parse_memory_name(runtime_info, name, &arr_ind, &inst_i, &regmem_i);
        /* If access_parse_memory_name returns -1, there is an error/failure from the user input */
        if (parse_memory_name_rv < 0)
        {
            return SOC_E_PARAM;
        }
        /* If access_parse_memory_name returns 1, there is no exact match of memory name */
        if (parse_memory_name_rv == 1)
        {
            cli_out("Unknown memory %s:\n", name);
            return SOC_E_PARAM;
        }
        /* Memory to access */
        rm_info = device_info->local_regs + regmem_i;

        if ((rm_info->flags & ACCESS_REGMEM_FLAG_IS_ALIAS) != 0)
        {
            regmem_i = rm_info->u.mem.alias_regmem;
            rm_info = device_info->local_regs + regmem_i;
        }

        /* Loop over array indices to write the memory to each one */
        for (arr_ind = min_ar_index; arr_ind <= max_ar_index; arr_ind++)
        {
            if (buffer && (rv = access_local_regmem_sbusdma(runtime_info, FLAG_ACCESS_IS_WRITE | FLAG_ACCESS_IS_FILL, regmem_i, inst_i, arr_ind, index_min, index_max - index_min + 1, 0, buffer)))
            {
                cli_out("ERROR: access_local_regmem_sbusdma failed to write memory ");
                diag_print_regmem_info(runtime_info, rm_info, inst_i, arr_ind, -1);
                return SOC_E_PARAM;
            }
        }
    }
#endif /* BCM_ACCESS_SUPPORT */
    else
    {
        int copyno;
        soc_mem_t mem;
        unsigned array_index;

        if (parse_memory_name(unit, &mem, name, &copyno, &array_index) < 0) {
            cli_out("ERROR: unknown table \"%s\"\n",name);
            return SOC_E_PARAM;
        }
        if (buffer && ((rv = soc_mem_array_fill_range(unit, mem, min_ar_index, max_ar_index, copyno, index_min, index_max, buffer)))) {
            cli_out("soc_mem_fill() failed in memory %s.%d[%u] indices[%d:%d] returned %d\n",
                    SOC_MEM_UFNAME(unit, mem), copyno==COPYNO_ALL ? 0 : copyno, array_index, min_ar_index, max_ar_index, rv);
        }
    }
    return rv;
}


/* fill the table with the same given entry, using the device specific wrapper for the SLAM DMA function */
static int diag_fill_table(int unit, char *name, mem_val value)
{
    int rv = SOC_E_NONE;

    if (!SOC_UNIT_VALID(unit)) {
        cli_out("Invalid unit.\n");
        return SOC_E_UNIT;
    }
    if (name == NULL) {
        cli_out("NULL mem name given.\n");
        return SOC_E_PARAM;
    }

#ifdef BCM_ACCESS_SUPPORT
    if (ACCESS_IS_INITIALIZED(unit))
    {
        rv = diag_mem_fill(unit, name, (void*)value);
    }
#endif /* BCM_ACCESS_SUPPORT */
    else
    {
        int copyno;
        soc_mem_t mem;
        unsigned array_index;

        if (parse_memory_name(unit, &mem, name, &copyno, &array_index) < 0) {
            cli_out("ERROR: unknown table \"%s\"\n",name);
            return SOC_E_PARAM;
        }

        if (!SOC_MEM_IS_VALID(unit, mem)) {
            cli_out("Error: Memory %s not valid for chip %s.\n",
                    SOC_MEM_UFNAME(unit, mem), SOC_UNIT_NAME(unit));
            return SOC_E_PARAM;
        }

        if (soc_mem_is_readonly(unit, mem)) {
            cli_out("ERROR: Table %s is read-only\n",
                    SOC_MEM_UFNAME(unit, mem));
            return SOC_E_PARAM;
        }

    #if defined(BCM_PETRA_SUPPORT)
        if(SOC_IS_ARAD(unit)) {
            if ((value) && ((rv = arad_fill_partial_table_with_entry(unit, mem, array_index, array_index, copyno, 0, soc_mem_index_max(unit, mem), value)))) {
                cli_out("Fill ERROR: table %s.%d: 0x%x\n",
                        SOC_MEM_UFNAME(unit, mem), copyno==COPYNO_ALL ?
                        0 : copyno, rv);
            }
        } else
    #endif
        {
            cli_out("fast table filling not supported on this device\n");
            rv = SOC_E_UNIT;
        }
    }
    return rv;
}


/* test the J2CP memory configuration improvement */
static int diag_mem_conf_test(int unit, uint32 test_value)
{
    uint32 rv = SOC_E_NONE;
#ifdef BCM_88850_A0
    uint32 value;
    extern CONST soc_reg_t j2p_per_block_config_reg[];
#endif
    if (!SOC_UNIT_VALID(unit)) {
        cli_out("Invalid unit.\n");
        return SOC_E_UNIT;
    }

#ifdef BCM_88850_A0
    if (SOC_IS_J2P(unit)) {
        soc_reg_above_64_val_t data;
        int i, nof_errors = 0;
        for (i = 0; j2p_per_block_config_reg[i] != INVALIDr; i++)
        {
            rv = soc_reg_above_64_get(unit, j2p_per_block_config_reg[i], REG_PORT_ANY, 0, data);
            if (rv) {
                cli_out("Test %s register read failed\n", SOC_REG_NAME(unit, j2p_per_block_config_reg[i]));
                nof_errors++;
            }
            else
            {
                value = soc_reg_above_64_field32_get(unit, j2p_per_block_config_reg[i], data, ITEM_19_30f);
                cli_out("Testing register %s - Value read is %d\n", SOC_REG_NAME(unit, j2p_per_block_config_reg[i]), value);
                if (value != test_value)
                {
                    nof_errors++;
                    cli_out("ERROR: Register %s is with different field value %d \n", SOC_REG_NAME(unit, j2p_per_block_config_reg[i]), value);
                }
            }
        }
        if (nof_errors) rv = SOC_E_FAIL;
    } else
#endif
    {
        cli_out("Test not supported on this device\n");
        rv = SOC_E_UNIT;
    }
    return rv;
}
/* Test unified access macros for register access */

#ifdef BCM_SAND_SUPPORT /* for shrextend_debug.h */
#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/ua.h>
#define BSL_LOG_MODULE BSL_LS_SOC_INIT

/** unified access test function for DNX devices (uses DNX registers) */
shr_error_e
test_ua_macros(
    int unit)
{
    uint32 reg_value[2];
    uint32 field_value;

    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT((UA_REG_IS_VALID(unit, ECI_VERSION_REGISTER) && UA_REG_FIELD_IS_VALID(unit, ECI_VERSION_REGISTER, CHIP_TYPE)) ?
      SOC_E_NONE : SOC_E_PARAM);
    SHR_IF_ERR_EXIT((UA_REG_FIELD_SIZE(unit, ECI_TEST_REGISTER, TEST_REGISTER) == 32) ?
      SOC_E_NONE : SOC_E_PARAM);
    /* read the version register, get its chip type field and print the field and register values */
    SHR_IF_ERR_EXIT(UA_REG_READ(unit, ECI_VERSION_REGISTER, 0, 0, reg_value));
    SHR_IF_ERR_EXIT(UA_REG_FIELD_GET(unit, ECI_VERSION_REGISTER, reg_value, CHIP_TYPE, &field_value));
    LOG_ERROR(BSL_LS_SOC_INIT, ("Register ECI_VERSION_REGISTER=0x%x field CHIP_TYPE=0x%x\n", reg_value[0], field_value));

    /* set a value to the field of the test register which composes all the register, write the value to the register and read it back.
     * The test register logically negated values written to it. Then we print the value written to and read form the register */
    field_value = 0xff005aa5;
    SHR_IF_ERR_EXIT(UA_REG_FIELD_SET(unit, ECI_TEST_REGISTER, reg_value, TEST_REGISTER, &field_value));
    SHR_IF_ERR_EXIT(UA_REG_WRITE(unit, ECI_TEST_REGISTER, 0, 0, reg_value));
    SHR_IF_ERR_EXIT(UA_REG_READ(unit, ECI_TEST_REGISTER, 0, 0, reg_value + 1));
    LOG_ERROR(BSL_LS_SOC_INIT, ("Register ECI_TEST_REGISTER changed value 0x%x to 0x%x\n", reg_value[0], reg_value[1]));

exit:
    SHR_FUNC_EXIT;
}
#endif /* BCM_SAND_SUPPORT */



/* perform an MBIST test, destroying the contents of memories */
static int diag_mbist(int unit, int skip_errors)
{
    uint32 rv = SOC_E_NONE;
    uint32 rv2 = SOC_E_NONE;
    bcm_switch_event_t switch_event;
    bcm_switch_event_control_t type;
    bcm_switch_service_config_t config;
    uint32 value;
    switch_event = BCM_SWITCH_EVENT_DEVICE_INTERRUPT;
    type.event_id = BCM_SWITCH_EVENT_CONTROL_ALL;
    type.index = 0;
    type.action = bcmSwitchEventMask;
    value = 1;
    bcm_switch_event_control_set(unit, switch_event, type, value);
    bcm_switch_service_config_t_init(&config);
    config.enabled = bcmServiceStateDisabled;

#if defined(BCM_RPC_SUPPORT) || defined(BCM_ESW_SUPPORT) || defined(BCM_LOOP_SUPPORT) || defined(BCM_PETRA_SUPPORT)
    bcm_switch_service_set(unit, bcmServiceCounterCollection, &config);
#else
    return SOC_E_FAIL;
#endif

    if (!SOC_UNIT_VALID(unit)) {
        cli_out("Invalid unit.\n");
        return SOC_E_UNIT;
    }

#if  defined(BCM_88660_A0) 
/* { */
    if (SOC_IS_ARADPLUS_AND_BELOW(unit)) {
        {
            rv = soc_bist_all_arad(unit, skip_errors);
        }
    } else
/* } */
#endif
#ifdef BCM_88950_A0
    if (SOC_IS_FE3200(unit)) {
        rv = soc_fe3200_bist_all(unit, skip_errors);
    } else
#endif
#if defined(BCM_88470_A0) || defined(BCM_88270_A0)
    if (SOC_IS_QAX(unit)) {
        rv = soc_bist_all_qax(unit, skip_errors);
    } else
#endif
#if  defined(BCM_88675_A0) || defined(BCM_88375_A0)
    if (SOC_IS_JERICHO_AND_BELOW(unit) || SOC_IS_JERICHO_PLUS(unit)) {
        rv = soc_bist_all_jer(unit, skip_errors);
    } else
#endif
#if  defined(BCM_88790_A0) 
    if (SOC_IS_RAMON(unit)) {
        rv = soc_ramon_bist_all(unit, skip_errors);
    } else
#endif
#ifdef BCM_88690_A0
    if (SOC_IS_JERICHO2(unit)) {
        rv = soc_bist_all_jr2(unit, skip_errors);
    } else
#endif
#ifdef BCM_88800_A0
    if (SOC_IS_J2C(unit)) {
        rv = soc_bist_all_j2c(unit, skip_errors);
    } else
#endif
#ifdef BCM_88480_A0
    if (SOC_IS_Q2A(unit)) {
        rv = soc_bist_all_q2a(unit, skip_errors);
    } else
#endif
#ifdef BCM_88850_A0
    if (SOC_IS_J2P(unit)) {
        rv = soc_bist_all_j2p(unit, skip_errors);
    } else
#endif
    {
        cli_out("software MBIST not supported on this device\n");
        rv2 = rv = SOC_E_UNIT;
    }
    if (rv != rv2) {
        cli_out("MBIST failed\n");
    }

    rv2 = bcm_switch_event_control_set(unit, switch_event, type, value);
    if (rv2 != BCM_E_NONE)
    {
        printf("Error, bcm_switch_event_control_set\n");
        if (rv == SOC_E_NONE)
        {
            rv = rv2;
        }
    }
    return rv;
}

/* perform an MBIST bases SER test, destroying the contents of memories */
static int diag_mbist_ser_test(const int unit, const int skip_errors, const uint32 nof_repeats, const uint32 time_to_wait, const uint32 ser_test_num)
{
    uint32 rv = SOC_E_NONE;

    if (!SOC_UNIT_VALID(unit)) {
        cli_out("Invalid unit.\n");
        return SOC_E_UNIT;
    }

#if defined(BCM_PETRA_SUPPORT)
    if (SOC_IS_ARADPLUS_AND_BELOW(unit)) {
        rv = soc_bist_arad_ser_test(unit, skip_errors, nof_repeats, time_to_wait, ser_test_num);

        if (rv) {
            cli_out("MBIST SER test failed\n");
        }
    } else
#endif
    {
        cli_out("MBIST SER test not supported on this device\n");
        rv = SOC_E_UNIT;
    }

    return rv;
}

/* read and return the temperature of the given HBM, return a negative value on error */
static int diag_get_hbm_temp(const int unit, const unsigned hbm_number)
{
#ifdef BCM_DNX_SUPPORT
    uint32 temp = -1;
#endif
    if (!SOC_UNIT_VALID(unit)) {
        cli_out("Invalid unit.\n");
        return SOC_E_UNIT;
    } else if (!(SOC_IS_J2C(unit) || SOC_IS_JERICHO2(unit))) {
        cli_out("Device not supported.\n");
        return SOC_E_PARAM;
    }
#ifdef BCM_DNX_SUPPORT
    if (dnx_drv_soc_dnx_read_hbm_temp(unit, hbm_number, &temp)) {
        cli_out("Failed to read the HBM temperature.\n");
        return SOC_E_FAIL;
    }
    return temp;
#endif
}

/* clear, print or re-populate the Arad direct mapping modport2sysport table */
static int diag_modport2sysport(int unit)
{
    uint32 rv = SOC_E_NONE;

    if (!SOC_UNIT_VALID(unit)) {
        cli_out("Invalid unit.\n");
        return SOC_E_UNIT;
    }

#if defined(BCM_PETRA_SUPPORT)
    if(SOC_IS_ARAD(unit)) {
        uint32 mod, port;
        ARAD_SYSPORT sysport;
        for (mod = 0; mod < ARAD_NOF_FAPS_IN_SYSTEM; ++mod) {
            for (port = 0; port < ARAD_NOF_FAP_PORTS; ++port) {
                if (arad_sw_db_modport2sysport_get(unit, mod, port, &sysport)) {
                     cli_out("failed to get the mapping for "
                             "module %u port %u\n", mod, port);
                     return SOC_E_FAIL;
                } else if (sysport != ARAD_NOF_SYS_PHYS_PORTS_GET(unit)) {
                     cli_out("%u , %u -> %u\n", mod, port, sysport);
                }
            }
        }
    } else
#endif
    {
        cli_out("not supported on this device\n");
        rv = SOC_E_UNIT;
    }

    return rv;
}

int
fill_memory_with_incremental_field(const int unit, const soc_mem_t mem, const soc_field_t field,
                                unsigned array_index_min, unsigned array_index_max,
                                const int copyno,
                                int index_min, int index_max,
                                const void *initial_entry)
{
    int    rv = 0, mem_words, mem_size, entry_words, indices_num;
    int    index, blk, tmp;
    unsigned array_index;
    uint32 *buf;
    uint32 *buf2;
    const uint32 *input_entry = initial_entry;
    uint32 field_buf[4] = {0}; /* To hold the field, max size 128 bits */

    if (initial_entry == NULL) {
        return SOC_E_PARAM;
    }

    /* get legal values for indices, if too small/big use the memory's boundaries */
    tmp = soc_mem_index_min(unit, mem);
    if (index_min < soc_mem_index_min(unit, mem)) {
      index_min = tmp;
    }
    if (index_max < index_min) {
        index_max = index_min;
    } else {
         tmp = soc_mem_index_max(unit, mem);
         if (index_max > tmp) {
             index_max = tmp;
         }
    }

    entry_words = soc_mem_entry_words(unit, mem);
    indices_num = index_max - index_min + 1;
    mem_words = indices_num * entry_words;
    mem_size = mem_words * 4;

    /* get the initial field from the input */
    soc_mem_field_get(unit, mem, initial_entry, field, field_buf);

    buf = soc_cm_salloc(unit, mem_size, "mem_clear_buf"); /* allocate DMA memory buffer */
    if (buf == NULL) {
        return SOC_E_MEMORY;
    }

    /* get legal values for memory array indices */
    if (SOC_MEM_IS_ARRAY(unit, mem)) {
        soc_mem_array_info_t *maip = SOC_MEM_ARRAY_INFOP(unit, mem);
        if (maip) {
            if (array_index_max >= maip->numels + maip->first_array_index) {
                array_index_max = (maip->numels - 1) + maip->first_array_index;
            } else if (array_index_min < array_index_max) {
                array_index_min =  maip->first_array_index;
            }
        }
    } else {
        array_index_min = array_index_max = 0;
    }

    /* fill the allocated memory with the input entry */
    for (index = 0; index < mem_words; ++index) {
        buf[index] = input_entry[index % entry_words];
    }

    SOC_MEM_BLOCK_ITER(unit, mem, blk) {
        if (copyno != COPYNO_ALL && copyno != blk) {
            continue;
        }
        for (array_index = array_index_min; array_index <= array_index_min; ++array_index) {
            /* update the field of all the entries in the buffer */
            for (index = 0, buf2 = buf; index < indices_num; ++index, buf2+=entry_words) {
                soc_mem_field_set(unit, mem, buf2, field, field_buf); /* set the index */
                /* increment the field, to be used in next entry */
                if (!++field_buf[0]) {
                    if (!++field_buf[1]) {
                        if (!++field_buf[2]) {
                            ++field_buf[3];
                        }
                    }
                }
            }

#ifdef PLISIM
            if (SAL_BOOT_PLISIM) {
                for (index = index_min, buf2 = buf; index <= index_max; ++index, buf2+=entry_words) {
                    if ((rv = soc_mem_array_write(unit, mem, array_index, blk, index, buf2)) < 0) {
                        cli_out("Write ERROR: table %s.%d[%d]: %s\n",
                                SOC_MEM_UFNAME(unit, mem), copyno==COPYNO_ALL ?
                                0 : copyno, index,
                                soc_errmsg(rv));
                    }
                }
            } else
#endif
            {
                if ((rv = soc_mem_array_write_range(unit, 0, mem, array_index, blk, index_min, index_max, buf)) < 0) {
                    cli_out("Write ERROR: table %s.%d[%d-%d]: %s\n",
                            SOC_MEM_UFNAME(unit, mem), copyno==COPYNO_ALL ?
                            0 : copyno, index_min, index_max,
                            soc_errmsg(rv));
                }
            }
        }
    }
    soc_cm_sfree(unit, buf);
    return rv;
}

/* pointer management functions */
static int diag_pointer(int unit, char *func_name, void **p, char *arg)
{
    int rv;
    unsigned long val;

    if (!SOC_UNIT_VALID(unit)) {
        cli_out("Invalid unit.\n");
        return SOC_E_UNIT;
    } else if (!func_name || !p || !arg) {
        return SOC_E_PARAM;
    }
    if (arg[0] == '0' && (arg[1] == 'x' || arg[1] == 'X')) {
        /* coverity[secure_coding] */
        rv = sscanf(arg + 2, "%lx", &val);
    } else {
        /* coverity[secure_coding] */
        rv = sscanf(arg, "%lu", &val);
    }
    if (rv != 1) {
        cli_out("could not interpret value\n");
        return SOC_E_PARAM;
    }
    if (!sal_strcmp(func_name, "set")) {
        *p = (void*)(uint8*)val;
    } else if (!sal_strcmp(func_name, "print")) {
        cli_out("pointer value: %p\n", *p);
    } else if (!sal_strcmp(func_name, "dmabuf_alloc")) {
        if (!(*p = soc_cm_salloc(unit, val, "diag_pointer"))) {
            cli_out("Could not allocte a DMA buffer of %lx bytes\n", val);
            return SOC_E_MEMORY;
        }
        cli_out("Allocted a %lu bytes DMA buffer at %p\n", val, *p);
    } else if (!sal_strcmp(func_name, "dmabuf_free")) {
        soc_cm_sfree(unit, *p);
    } else {
        cli_out("ERROR: unknown pointer command, use one of: "
            "set, print, dmabuf_alloc dmabuf_free\n");
        return SOC_E_PARAM;
    }
    return SOC_E_NONE;
}

static int diag_soc_device_reset(int unit, int mode, int action)
{
    int rv = 0;

    rv = soc_device_reset(unit, mode, action);
    if (rv) {
        cli_out("Error: soc_device_reset Failed. rv=%d\n", rv);
        return rv;
    }

    return rv;
}

static int diag_cm_get_unit_by_id(uint16 dev_id, int occur, int *unit)
{
    int 
        rv = 0,
        num_devices = 0,
        tmp_occur = 0,
        tmp_unit,
        found = 0;
    uint16 
        tmp_dev_id;
    uint8 
        tmp_rev_id;


    num_devices = soc_cm_get_num_devices();

    for (tmp_unit = 0 ; tmp_unit < num_devices ; tmp_unit++ ) {
        soc_cm_get_id(tmp_unit, &tmp_dev_id, &tmp_rev_id);

        if (tmp_dev_id == dev_id) {
            if (tmp_occur == occur) {
                found = 1;
                break;
            }
            tmp_occur++;
        }
    }

    if (found == 1) {
        *unit = tmp_unit;
    } else {
        *unit = 0xffffffff;
    }

    return rv;
}




static int diag_get_interrupt_id_byname(int unit, char *regName, int reg_index, char* fldName, int bit_in_field, int* interrupt_id)
{
    int rc = SOC_E_NONE;
    soc_reg_t reg=INVALIDr;
    soc_field_t field=INVALIDf;
    soc_regaddrlist_t alist;
    soc_reg_info_t *reginfo;
    int f;
    int field_found = 0;

    if (!SOC_INTR_IS_SUPPORTED(unit)) {
        cli_out("No interrupts for device\n");
        return BCM_E_INTERNAL;
    }

    if (soc_regaddrlist_alloc(&alist) < 0)
    {
        cli_out("Could not allocate address list.\n");
        return BCM_E_INTERNAL;
    }

    if (parse_symbolic_reference(unit, &alist, regName) < 0)
    {
        cli_out("Syntax error parsing %s\n", regName);
        soc_regaddrlist_free(&alist);
        return BCM_E_INTERNAL;
    }
    else if (alist.count < 1)
    {
        /** wrong register got */
        cli_out("get wrong register %s\n", regName);
        soc_regaddrlist_free(&alist);
        return BCM_E_INTERNAL;
    } else
    {
        /** get register */
        reg = alist.ainfo->reg;
        soc_regaddrlist_free(&alist);

        if (!SOC_REG_IS_VALID(unit,reg)) {
            cli_out("get invalid register %s\n", regName);
            return BCM_E_INTERNAL;
        }
        reginfo = &SOC_REG_INFO(unit, reg);

        for (f = reginfo->nFields - 1; f >= 0; f--)
        {
            soc_field_info_t *fld = &reginfo->fields[f];
            if (sal_strcasecmp(SOC_FIELD_NAME(unit, fld->field), fldName))
            {
                continue;
            }
            field_found = 1;
            field = fld->field;
        }
        if (!field_found) {
            cli_out("can not get field(%s) from %s\n", fldName, regName);
            return BCM_E_INTERNAL;
        }
    }

    rc = soc_get_interrupt_id(unit, reg, reg_index, field, bit_in_field, interrupt_id);
    return rc;
}

#endif /* defined(BCM_SANDSUPPORT) || defined(BCM_ESW_SUPPORT) */
#ifdef BCM_DNX_SUPPORT
static int diag_counter_value_get(
    int unit,
    const char *blkName,
    const char *counterName,
    uint64 *counter)
{
    int rc;
    rc = dnx_diag_get_counter_specific(unit, blkName, counterName, counter);
    return rc;
}

#endif
static void diag_printk(char *str)
{
    cli_out("%s", str);
}

#define DIAG_PRINTK_FLAGS_HEX 0x1

static void diag_printk_int(int num, int flags)
{
    if(flags & DIAG_PRINTK_FLAGS_HEX) {
        cli_out("%x",(uint32)num);
    } else {
        cli_out("%d",num);
    }
}

static void diag_pcie_read(int unit, uint32 addr, uint32 *val, int swap)
{

    *val = CMVEC(unit).read(&CMDEV(unit).dev, addr);

    if(swap) {
        *val = _shr_swap32(*val);
    }

    /* cli_out("%s(): unit=%d, addr=0x%x, swap=%d. after swap: *val=0x%x",
               FUNCTION_NAME(), unit, addr, swap, *val); */
}

static void diag_pcie_write(int unit, uint32 addr, uint32 val, int swap)
{
    /* cli_out("%s(): unit=%d, addr=0x%x, val=0x%x, swap=%d",
               FUNCTION_NAME(), unit, addr, val, swap); */

    if(swap) {
        val = _shr_swap32(val);
    }

    CMVEC(unit).write(&CMDEV(unit).dev, addr, val);

}


#if defined(BCM_DNX_SUPPORT)  || defined(BCM_DNXF_SUPPORT)
/* Performance test for BARs, memories, ... */
#define TEST_RAM_SIZE (64*1024*1024)
#define TEST_DMA_SIZE (16*1024*1024)
#define TEST_SRAM_SIZE (13*1024)
#define CMIC_TEST_SIZE (16*1024)
/** The SRAM is mapped to the 7th 1MB window in the 2nd (CMIC) BAR */
#define EVENTOR_SRAM_OFFSET_IN_BAR (7*1024*1024)
#define F64 COMPILER_64_PRINTF_FORMAT

static int diag_bar_access_test(int unit)
{
    unsigned i, j = 0, nof_indices, nof_iters, nof_words = 0;
    uint64 *ram = NULL, *dma = NULL;
    volatile uint64 *bar; /* BAR address of Eventor SRAM or CMIC sbus registers */
    uint64 *p64a, *p64b;
    uint32 *p32a, *p32b;
    sal_usecs_t  start, end, diff;
    int         rv = SOC_E_FAIL;

    if (!SOC_UNIT_VALID(unit) || !SOC_IS_DNX(unit)) {
        cli_out("Invalid unit.\n");
        return SOC_E_UNIT;
    }

    if (sand_alloc_mem(unit, &ram, TEST_RAM_SIZE, "diag_bar_access_test") ||
        ((((unsigned long)(uint8*)ram) & 7) != 0)) { /* check that we received a uint64 aligned pointer */
        cli_out("failed to allocate RAM memory\n");
    } else if ((dma = soc_cm_salloc(unit, TEST_DMA_SIZE, "test_dma")) == NULL ||
        ((((unsigned long)(uint8*)dma) & 7) != 0)) { /* check that we received a uint64 aligned pointer */
        cli_out("failed to allocate DMA memory\n");
    } else {

        start = sal_time_usecs();
        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) { /* fill the RAM */
            ram[i] = COMPILER_64_LITERAL(0x12344321ab000000) | i;
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("initialized %uMB RAM in %u us  "F64" ps/uint64\n", TEST_RAM_SIZE/(1024*1024), diff, ((uint64)diff * 1000000) / (TEST_RAM_SIZE / sizeof(uint64)));

        /* copy aligned memory using uint64s */
        p64a = ram + TEST_RAM_SIZE / (4 * sizeof(uint64));
        p64b = p64a + TEST_RAM_SIZE / (4 * sizeof(uint64));
        start = sal_time_usecs();
        for (i = 0; i < TEST_RAM_SIZE / (4 * sizeof(uint64)); ++i) {
            p64b[i] = p64a[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM aligned using uint64 %u us  "F64" ps/uint64\n", TEST_RAM_SIZE/(4*1024*1024),  diff, ((uint64)diff * 1000000) / (TEST_RAM_SIZE / (4 * sizeof(uint64))));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321ac000000) | i;} /* fill the RAM */
        /* copy aligned memory using uint32s */
        p32a = ((uint32*)ram) + TEST_RAM_SIZE / (4 * sizeof(uint32));
        p32b = p32a + TEST_RAM_SIZE / (4 * sizeof(uint32));
        start = sal_time_usecs();
        for (i = 0; i < TEST_RAM_SIZE / (4 * sizeof(uint32)); ++i) {
            p32b[i] = p32a[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM aligned using uint32 %u us  "F64" ps/uint64\n", TEST_RAM_SIZE/(4*1024*1024), diff, ((uint64)diff * 1000000) / (TEST_RAM_SIZE / (4 * sizeof(uint64))));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321ad000000) | i;} /* fill the RAM */
        /* copy aligned memory using memcpy */
        start = sal_time_usecs();
        sal_memcpy(p64b, p64a, TEST_RAM_SIZE / 4);
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM aligned using memcpy %u us  "F64" ps/uint64\n", TEST_RAM_SIZE/(4*1024*1024), diff, ((uint64)diff * 1000000) / (TEST_RAM_SIZE / (4 * sizeof(uint64))));

        /* initial write to DMA memory */
        start = sal_time_usecs();
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64); ++i) { /* fill the DMA RAM */
            dma[i] = COMPILER_64_LITERAL(0x1234567811000000) | i;
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("initialized %uMB DMA RAM in %u us  "F64" ps/uint64\n", TEST_DMA_SIZE/(1024*1024), diff, ((uint64)diff * 1000000) / (TEST_DMA_SIZE / sizeof(uint64)));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321ae000000) | i;} /* fill the RAM */
        /* copy aligned memory to DMA memory using uint64s */
        p64a = ram + TEST_RAM_SIZE / (4 * sizeof(uint64));
        p64b = (uint64*)(((uint32*)dma) + 1);
        p32a = ((uint32*)ram) + TEST_RAM_SIZE / (4 * sizeof(uint32));
        p32b = (uint32*)dma;
        start = sal_time_usecs();
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64); ++i) {
            dma[i] = p64a[i]; /* fill the DMA RAM */
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM to DMA aligned using uint64 %u us  "F64" ps/uint64\n", TEST_DMA_SIZE/(1024*1024), diff, ((uint64)diff * 1000000) / (TEST_DMA_SIZE / (sizeof(uint64))));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321af000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64); ++i) {dma[i] = COMPILER_64_LITERAL(0x1234567812000000) | i;} /* fill the DMA RAM */
        /* copy misaligned memory to DMA memory using uint64s */
        start = sal_time_usecs();
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64) - 1; ++i) {
            p64b[i] = p64a[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM to DMA misaligned using uint64 %u us  "F64" ps/uint64\n", TEST_DMA_SIZE/(1024*1024), diff, ((uint64)diff * 1000000) / (TEST_DMA_SIZE / (sizeof(uint64))-1));
        for (i=1; i < TEST_DMA_SIZE / sizeof(uint32) - 2; ++i ) {
            if (p32a[i] != p32b[i+1]) {
                cli_out("Found a mismatch at uint32 index %u: 0x%x!=0x%x\n", i, p32a[i], p32b[i+1]);
                /*cli_out("addresses: orig:%p %p   p64:%p %p   p32:%p %p   p64[3]:%p %p\n", ram, dma, p64a, p64b, p32a, p32b, &p64a[3], &p64b[3]);*/
                break;
            }
        }

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321bf000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64); ++i) {dma[i] = COMPILER_64_LITERAL(0x1234567813000000) | i;} /* fill the DMA RAM */
        /* copy aligned memory to DMA memory using uint32s */
        start = sal_time_usecs();
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint32); ++i) {
            p32b[i] = p32a[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM to DMA aligned using uint32 %u us  "F64" ps/uint64\n", TEST_DMA_SIZE/(1024*1024), diff, ((uint64)diff * 1000000) / (TEST_DMA_SIZE / (sizeof(uint64))));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b0000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64); ++i) {dma[i] = COMPILER_64_LITERAL(0x1234567814000000) | i;} /* fill the DMA RAM */
        /* copy aligned memory to DMA memory using memcpy */
        start = sal_time_usecs();
        sal_memcpy(dma, p64a, TEST_DMA_SIZE);
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM aligned using memcpy %u us  "F64" ps/uint64\n", TEST_DMA_SIZE/(1024*1024), diff, ((uint64)diff * 1000000) / (TEST_DMA_SIZE / (sizeof(uint64))));


        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b1000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64); ++i) {dma[i] = COMPILER_64_LITERAL(0x1234567812000000) | i;} /* fill the DMA RAM */
        /* copy aligned memory from DMA memory using uint64s */
        start = sal_time_usecs();
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64); ++i) {
            p64a[i] = dma[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM from DMA aligned using uint64 %u us  "F64" ps/uint64\n", TEST_DMA_SIZE/(1024*1024), diff, ((uint64)diff * 1000000) / (TEST_DMA_SIZE / (sizeof(uint64))));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321be000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64); ++i) {dma[i] = COMPILER_64_LITERAL(0x1234567813000000) | i;} /* fill the DMA RAM */
        /* copy misaligned memory from DMA memory using uint64s */
        start = sal_time_usecs();
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64) - 1; ++i) {
            p64a[i] = p64b[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM from DMA misaligned using uint64 %u us  "F64" ps/uint64\n", TEST_DMA_SIZE/(1024*1024), diff, ((uint64)diff * 1000000) / (TEST_DMA_SIZE / (sizeof(uint64))-1));
        for (i=1; i < TEST_DMA_SIZE / sizeof(uint32) - 2; ++i ) {
            if (p32a[i] != p32b[i+1]) {
                cli_out("Found a mismatch at uint32 index %u: 0x%x!=0x%x\n", i, p32a[i], p32b[i+1]);
                break;
            }
        }

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b2000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64); ++i) {dma[i] = COMPILER_64_LITERAL(0x1234567812000000) | i;} /* fill the DMA RAM */
        /* copy aligned memory from DMA memory using uint32s */
        start = sal_time_usecs();
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint32); ++i) {
            p32a[i] = p32b[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM from DMA aligned using uint32 %u us  "F64" ps/uint64\n", TEST_DMA_SIZE/(1024*1024), diff, ((uint64)diff * 1000000) / (TEST_DMA_SIZE / (sizeof(uint64))));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b3000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_DMA_SIZE / sizeof(uint64); ++i) {dma[i] = COMPILER_64_LITERAL(0x1234567814000000) | i;} /* fill the DMA RAM */
        /* copy aligned memory from DMA memory using memcpy */
        start = sal_time_usecs();
        sal_memcpy(p64a, dma, TEST_DMA_SIZE);
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uMB RAM from DMA aligned using memcpy %u us  "F64" ps/uint64\n", TEST_DMA_SIZE/(1024*1024), diff, ((uint64)diff * 1000000) / (TEST_DMA_SIZE / (sizeof(uint64))));


        /* get the 2nd bar address in user space */
#ifdef SOC_CM_MEMORY_BASE
        bar = (volatile uint64 *)(SOC_CM_MEMORY_BASE+(SOC_CM_MEMORY_OFFSET*unit));
#else
#ifdef SOC_CM_MEMORY
        bar = (volatile uint64 *)CMVEC(unit).base_address;
#else
#ifdef SOC_CM_FUNCTION
        bar = 0;
        /* no direct BAR access */
#else
        bar = (volatile uint64 *)CMVEC(unit).base_address;
#endif /* SOC_CM_FUNCTION */
#endif /* SOC_CM_MEMORY */
#endif /* SOC_CM_MEMORY_BASE */
        if (!bar) {
            cli_out("Cannot test BAR access performance as the BAR access support is not done directly\n");
            return SOC_E_NONE;
        }

        bar += EVENTOR_SRAM_OFFSET_IN_BAR / sizeof(uint64);

        /* Test with Eventor sram */
        /* initial write to sram */
        start = sal_time_usecs();
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64); ++i) { /* fill the SRAM */
            bar[i] = COMPILER_64_LITERAL(0x1234567811000000) | i;
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("initialized %uKB SRAM in %u us  "F64" ps/uint64\n", TEST_SRAM_SIZE/1024, diff, ((uint64)diff * 1000000) / (TEST_SRAM_SIZE / sizeof(uint64)));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321ae000000) | i;} /* fill the RAM */
        /* copy aligned memory to sram using uint64s */
        p64a = ram + TEST_RAM_SIZE / (4 * sizeof(uint64));
        p64b = (uint64*)(((uint32*)bar) + 1);
        p32a = ((uint32*)ram) + TEST_RAM_SIZE / (4 * sizeof(uint32));
        p32b = (uint32*)bar;
        start = sal_time_usecs();
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64); ++i) {
            bar[i] = p64a[i]; /* fill the SRAM */
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM to SRAM aligned using uint64 %u us  "F64" ps/uint64\n", TEST_SRAM_SIZE/1024, diff, ((uint64)diff * 1000000) / (TEST_SRAM_SIZE / (sizeof(uint64))));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321af000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64); ++i) {bar[i] = COMPILER_64_LITERAL(0x1234567812000000) | i;} /* fill the SRAM */
        /* copy misaligned memory to sram using uint64s */
        start = sal_time_usecs();
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64) - 1; ++i) {
            p64b[i] = p64a[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM to SRAM misaligned using uint64 %u us  "F64" ps/uint64\n", TEST_SRAM_SIZE/1024, diff, ((uint64)diff * 1000000) / (TEST_SRAM_SIZE / (sizeof(uint64))-1));
        for (i=1; i < TEST_SRAM_SIZE / sizeof(uint32) - 2; ++i ) {
            if (p32a[i] != p32b[i+1]) {
                cli_out("Found a mismatch at uint32 index %u: 0x%x!=0x%x\n", i, p32a[i], p32b[i+1]);
                /*cli_out("addresses: orig:%p %p   p64:%p %p   p32:%p %p   p64[3]:%p %p\n", ram, bar, p64a, p64b, p32a, p32b, &p64a[3], &p64b[3]);*/
                break;
            }
        }

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321bf000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64); ++i) {bar[i] = COMPILER_64_LITERAL(0x1234567813000000) | i;} /* fill the SRAM */
        /* copy aligned memory to sram using uint32s */
        start = sal_time_usecs();
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint32); ++i) {
            p32b[i] = p32a[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM to SRAM aligned using uint32 %u us  "F64" ps/uint64\n", TEST_SRAM_SIZE/1024, diff, ((uint64)diff * 1000000) / (TEST_SRAM_SIZE / (sizeof(uint64))));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b0000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64); ++i) {bar[i] = COMPILER_64_LITERAL(0x1234567814000000) | i;} /* fill the SRAM */
        /* copy aligned memory to sram using memcpy */
        start = sal_time_usecs();
        sal_memcpy((void*)bar, p64a, TEST_SRAM_SIZE);
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM aligned using memcpy %u us  "F64" ps/uint64\n", TEST_SRAM_SIZE/1024, diff, ((uint64)diff * 1000000) / (TEST_SRAM_SIZE / (sizeof(uint64))));


        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b1000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64); ++i) {bar[i] = COMPILER_64_LITERAL(0x1234567812000000) | i;} /* fill the SRAM */
        /* copy aligned memory from SRAM using uint64s */
        start = sal_time_usecs();
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64); ++i) {
            p64a[i] = bar[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM from SRAM aligned using uint64 %u us  "F64" ps/uint64\n", TEST_SRAM_SIZE/1024, diff, ((uint64)diff * 1000000) / (TEST_SRAM_SIZE / (sizeof(uint64))));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321be000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64); ++i) {bar[i] = COMPILER_64_LITERAL(0x1234567813000000) | i;} /* fill the SRAM */
        /* copy misaligned memory from sram using uint64s */
        start = sal_time_usecs();
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64) - 1; ++i) {
            p64a[i] = p64b[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM from SRAM misaligned using uint64 %u us  "F64" ps/uint64\n", TEST_SRAM_SIZE/1024, diff, ((uint64)diff * 1000000) / (TEST_SRAM_SIZE / (sizeof(uint64))-1));
        for (i=1; i < TEST_SRAM_SIZE / sizeof(uint32) - 2; ++i ) {
            if (p32a[i] != p32b[i+1]) {
                cli_out("Found a mismatch at uint32 index %u: 0x%x!=0x%x\n", i, p32a[i], p32b[i+1]);
                break;
            }
        }

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b2000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64); ++i) {bar[i] = COMPILER_64_LITERAL(0x1234567812000000) | i;} /* fill the SRAM */
        /* copy aligned memory from sram using uint32s */
        start = sal_time_usecs();
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint32); ++i) {
            p32a[i] = p32b[i];
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM from SRAM aligned using uint32 %u us  "F64" ps/uint64\n", TEST_SRAM_SIZE/1024, diff, ((uint64)diff * 1000000) / (TEST_SRAM_SIZE / (sizeof(uint64))));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b3000000) | i;} /* fill the RAM */
        for (i = 0; i < TEST_SRAM_SIZE / sizeof(uint64); ++i) {bar[i] = COMPILER_64_LITERAL(0x1234567814000000) | i;} /* fill the SRAM */
        /* copy aligned memory from sram using memcpy */
        start = sal_time_usecs();
        sal_memcpy(p64a, (void*)bar, TEST_SRAM_SIZE);
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM from SRAM aligned using memcpy %u us  "F64" ps/uint64\n", TEST_SRAM_SIZE/1024, diff, ((uint64)diff * 1000000) / (TEST_SRAM_SIZE / (sizeof(uint64))));

        bar -= EVENTOR_SRAM_OFFSET_IN_BAR / sizeof(uint64); /* Will now point to CMIC start */


        p64a = NULL;
        /* in iproc 17 CMIC_COMMON_POOL_SCHAN_CH0_MESSAGE0..CMIC_COMMON_POOL_SCHAN_CH9_MESSAGE31 */
        /* in iproc 15 CMIC_COMMON_POOL_SCHAN_CH0_MESSAGE0..CMIC_COMMON_POOL_SCHAN_CH4_MESSAGE21 */
        if (SOC_REG_IS_VALID(unit, CMIC_COMMON_POOL_SCHAN_CH4_MESSAGE21r) &&
            SOC_REG_IS_VALID(unit, CMIC_COMMON_POOL_SCHAN_CH0_MESSAGE0r)) {
            if (SOC_REG_IS_VALID(unit, CMIC_COMMON_POOL_SCHAN_CH9_MESSAGE31r)) {
                j = soc_reg_addr(unit, CMIC_COMMON_POOL_SCHAN_CH9_MESSAGE0r, REG_PORT_ANY, 0);
                nof_words = 32; /* nof consecutive uint32s in the CMIC sbus registers */
            } else {
                j = soc_reg_addr(unit, CMIC_COMMON_POOL_SCHAN_CH4_MESSAGE0r, REG_PORT_ANY, 0);
                nof_words = 22; /* nof consecutive uint32s in the CMIC sbus registers */
            }
        }
          
        if (!nof_words) {
            cli_out("Cannot test BAR access performance as the BAR access support is not done directly\n");
            return SOC_E_NONE;
        }

        /* Test with CMIC */
        bar = (uint64*)(((uint8*)bar) + j); /* start adress of CMIC message aligned by 4 and not by 8 */
        p64b = (uint64*)(((uint32*)bar) + 1);
        p32b = (uint32*)bar;


        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b0000000) | i;} /* fill the RAM */
        /* copy memory to misaligned CMIC using uint64s */
        p64a = ram + TEST_RAM_SIZE / (4 * sizeof(uint64));
        nof_indices = nof_words / (sizeof(uint64)/sizeof(uint32));
        nof_iters = (CMIC_TEST_SIZE + (nof_indices * (sizeof(uint64)/2))) / (nof_indices * sizeof(uint64));
        start = sal_time_usecs();
        for (j = nof_iters; j; --j) {
            for (i = 0; i < nof_indices; ++i) {
                bar[i] = *(p64a++); /* copy to CMIC */
            }
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM to misaligned CMIC using uint64 %u us  "F64" ps/uint64\n", CMIC_TEST_SIZE/1024, diff, ((uint64)diff * 1000000) / (nof_iters*nof_indices));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b1000000) | i;} /* fill the RAM */
        /* copy memory to aligned CMIC using uint64s */
        p64a = ram + TEST_RAM_SIZE / (4 * sizeof(uint64));
        nof_indices--;
        nof_iters = (CMIC_TEST_SIZE + (nof_indices * (sizeof(uint64)/2))) / (nof_indices * sizeof(uint64));
        start = sal_time_usecs();
        for (j = nof_iters; j; --j) {
            for (i = 0; i < nof_indices; ++i) {
                p64b[i] = *(p64a++); /* copy to CMIC */
            }
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM to aligned CMIC using uint64 %u us  "F64" ps/uint64\n", CMIC_TEST_SIZE/1024, diff, ((uint64)diff * 1000000) / (nof_iters*nof_indices));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b1000000) | i;} /* fill the RAM */
        /* copy memory to CMIC using uint32s */
        p32a = ((uint32*)ram) + TEST_RAM_SIZE / (4 * sizeof(uint32));
        nof_indices = nof_words;
        nof_iters = (CMIC_TEST_SIZE + (nof_indices * (sizeof(uint32)/2))) / (nof_indices * sizeof(uint32));
        start = sal_time_usecs();
        for (j = nof_iters; j; --j) {
            for (i = 0; i < nof_indices; ++i) {
                p32b[i] = *(p32a++); /* copy to CMIC */
            }
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM to aligned CMIC using uint32 %u us  "F64" ps/uint64\n", CMIC_TEST_SIZE/1024, diff, ((uint64)diff * 1000000 * (sizeof(uint64)/sizeof(uint32))) / (nof_iters*nof_indices));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b1000000) | i;} /* fill the RAM */
        /* copy memory to CMIC using memcpy */
        p32a = ((uint32*)ram) + TEST_RAM_SIZE / (4 * sizeof(uint32));
        nof_indices = nof_words * sizeof(uint32);
        start = sal_time_usecs();
        for (j = nof_iters; j; --j) {
            sal_memcpy((void*)bar, p32a, nof_indices);
            p32a += nof_words;
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM to CMIC using memcpy %u us  "F64" ps/uint64\n", CMIC_TEST_SIZE/1024, diff, ((uint64)diff * 1000000 * sizeof(uint64)) / (nof_iters*nof_indices));


        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b0000000) | i;} /* fill the RAM */
        /* copy memory from misaligned CMIC using uint64s */
        p64a = ram + TEST_RAM_SIZE / (4 * sizeof(uint64));
        nof_indices = nof_words / (sizeof(uint64)/sizeof(uint32));
        nof_iters = (CMIC_TEST_SIZE + (nof_indices * (sizeof(uint64)/2))) / (nof_indices * sizeof(uint64));
        start = sal_time_usecs();
        for (j = nof_iters; j; --j) {
            for (i = 0; i < nof_indices; ++i) {
                *(p64a++) = bar[i]; /* copy from CMIC */
            }
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM from misaligned CMIC using uint64 %u us  "F64" ps/uint64\n", CMIC_TEST_SIZE/1024, diff, ((uint64)diff * 1000000) / (nof_iters*nof_indices));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b1000000) | i;} /* fill the RAM */
        /* copy memory from aligned CMIC using uint64s */
        p64a = ram + TEST_RAM_SIZE / (4 * sizeof(uint64));
        nof_indices--;
        nof_iters = (CMIC_TEST_SIZE + (nof_indices * (sizeof(uint64)/2))) / (nof_indices * sizeof(uint64));
        start = sal_time_usecs();
        for (j = nof_iters; j; --j) {
            for (i = 0; i < nof_indices; ++i) {
                *(p64a++) = p64b[i]; /* copy from CMIC */
            }
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM from aligned CMIC using uint64 %u us  "F64" ps/uint64\n", CMIC_TEST_SIZE/1024, diff, ((uint64)diff * 1000000) / (nof_iters*nof_indices));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b1000000) | i;} /* fill the RAM */
        /* copy memory from CMIC using uint32s */
        p32a = ((uint32*)ram) + TEST_RAM_SIZE / (4 * sizeof(uint32));
        nof_indices = nof_words;
        nof_iters = (CMIC_TEST_SIZE + (nof_indices * (sizeof(uint32)/2))) / (nof_indices * sizeof(uint32));
        start = sal_time_usecs();
        for (j = nof_iters; j; --j) {
            for (i = 0; i < nof_indices; ++i) {
                *(p32a++) = p32b[i]; /* copy from CMIC */
            }
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM from aligned CMIC using uint32 %u us  "F64" ps/uint64\n", CMIC_TEST_SIZE/1024, diff, ((uint64)diff * 1000000 * (sizeof(uint64)/sizeof(uint32))) / (nof_iters*nof_indices));

        for (i = 0; i < TEST_RAM_SIZE / sizeof(uint64); ++i) {ram[i] = COMPILER_64_LITERAL(0x12344321b1000000) | i;} /* fill the RAM */
        /* copy memory from CMIC using memcpy */
        p32a = ((uint32*)ram) + TEST_RAM_SIZE / (4 * sizeof(uint32));
        nof_indices = nof_words * sizeof(uint32);
        start = sal_time_usecs();
        for (j = nof_iters; j; --j) {
            sal_memcpy(p32a, (void*)bar, nof_indices);
            p32a += nof_words;
        }
        end = sal_time_usecs(); diff = end - start;
        cli_out("copy %uKB RAM from CMIC using memcpy %u us  "F64" ps/uint64\n", CMIC_TEST_SIZE/1024, diff, ((uint64)diff * 1000000 * sizeof(uint64)) / (nof_iters*nof_indices));

        rv = SOC_E_NONE;
    }


    if (dma) soc_cm_sfree(unit, dma);
    sand_free_mem_if_not_null(unit, (void**)&ram);
    return rv;
}
#endif

#if defined(__DUNE_GTO_BCM_CPU__) || defined(__DUNE_WRX_BCM_CPU__) || defined(__DUNE_SLK_BCM_CPU__) || defined(__DUNE_GTS_BCM_CPU__) || defined(INCLUDE_CPU_I2C)
CINT_FWRAPPER_CREATE_RP4(int, int, 0, 0,
                         cpu_i2c_write,
                         int, int, chip, 0, 0,
                         int, int, addr, 0, 0,
                         CPU_I2C_BUS_LEN, CPU_I2C_BUS_LEN, alen, 0, 0,
                         int, int, val, 0, 0);

CINT_FWRAPPER_CREATE_RP4(int, int, 0, 0,
                         cpu_i2c_read,
                         int, int, chip, 0, 0,
                         int, int, addr, 0, 0,
                         CPU_I2C_BUS_LEN, CPU_I2C_BUS_LEN, alen, 0, 0,
                         int*, int, p_val, 1, 0);
CINT_FWRAPPER_CREATE_RP6(int, int, 0, 0,
                         sal_i2c_write,
                         int,int,i2c_bus,0,0,
                         uint16,uint16,i2c_dev,0,0,
                         uint32,uint32,addr,0,0,
                         uint8,uint8,addr_len,0,0,
                         uint8*,uint8,value_to_write,1,0,
                         uint8,uint8,data_len,0,0);
CINT_FWRAPPER_CREATE_RP6(int, int, 0, 0,
                         sal_i2c_write_int,
                         int,int,i2c_bus,0,0,
                         uint16,uint16,i2c_dev,0,0,
                         uint32,uint32,addr,0,0,
                         uint8,uint8,addr_len,0,0,
                         uint32,uint32,value_to_write,0,0,
                         uint8,uint8,data_len,0,0);
CINT_FWRAPPER_CREATE_RP6(int, int, 0, 0,
                         sal_i2c_read,
                         int,int,i2c_bus,0,0,
                         uint16,uint16,i2c_dev,0,0,
                         uint32,uint32,addr,0,0,
                         uint8,uint8,addr_len,0,0,
                         uint8*,uint8,value_to_read,1,0,
                         uint8,uint8,data_len,0,0);
CINT_FWRAPPER_CREATE_RP6(int, int, 0, 0,
                         sal_i2c_read_int,
                         int,int,i2c_bus,0,0,
                         uint16,uint16,i2c_dev,0,0,
                         uint32,uint32,addr,0,0,
                         uint8,uint8,addr_len,0,0,
                         uint32*,uint32,value_to_read,1,0,
                         uint8,uint8,data_len,0,0);
CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         sal_i2c_smbus_read,
                         int,int,i2c_bus,0,0,
                         uint16,uint16,i2c_dev,0,0,
                         uint8,uint8,data_address,0,0,
                         uint8,uint8,data_len,0,0,
                         uint32*,uint32,value_to_read,1,0);
CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         sal_i2c_smbus_write,
                         int,int,i2c_bus,0,0,
                         uint16,uint16,i2c_dev,0,0,
                         uint8,uint8,data_address,0,0,
                         uint8,uint8,data_len,0,0,
                         uint32,uint32,value_to_write,0,0);
#endif

CINT_FWRAPPER_CREATE_VP1(diag_printk,
                         char*, char, str, 1, 0);

CINT_FWRAPPER_CREATE_VP2(diag_printk_int,
                         int, int, num, 0, 0,
                         int, int, flags, 0, 0);

CINT_FWRAPPER_CREATE_VP4(diag_pcie_read,
                         int,int,unit,0,0,
                         uint32,uint32,addr,0,0,
                         uint32*,uint32,val,1,0,
                         int,int,swap,0,0);

CINT_FWRAPPER_CREATE_VP4(diag_pcie_write,
                         int,int,unit,0,0,
                         uint32,uint32,addr,0,0,
                         uint32,uint32,val,0,0,
                         int,int,swap,0,0);

#if defined(BCM_SAND_SUPPORT) || defined(BCM_ESW_SUPPORT)
CINT_FWRAPPER_CREATE_RP2(int, int, 0, 0,
                         diag_reg_bits,
                         int,int,unit,0,0,
                         char*,char,reg_name,1,0);

CINT_FWRAPPER_CREATE_RP3(int, int, 0, 0,
                         diag_reg_field_bits,
                         int,int,unit,0,0,
                         char*,char,reg_name,1,0,
                         char*,char,field_name,1,0);

CINT_FWRAPPER_CREATE_RP6(int, int, 0, 0,
                         diag_reg_info_get,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         int*,int,reg_id,1,0,
                         int*,int,block_instance_id,1,0,
                         unsigned int*,unsigned int,block_instance_number,1,0,
                         unsigned int*,unsigned int,array_index,1,0);

CINT_FWRAPPER_CREATE_RP3(int, int, 0, 0,
                         diag_reg_get,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         uint32*,uint32,value,1,0);

CINT_FWRAPPER_CREATE_RP4(int, int, 0, 0,
                         diag_reg_field_get,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         char*,char,field_name,1,0,
                         uint32*,uint32,value,1,0);

CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         diag_reg_field_only_get,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         uint32*,uint32,reg_value,1,0,
                         char*,char,field_name,1,0,
                         uint32*,uint32,field_value,1,0);

CINT_FWRAPPER_CREATE_RP3(int, int, 0, 0,
                         diag_reg_set,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         uint32*,uint32,value,1,0);

CINT_FWRAPPER_CREATE_RP4(int, int, 0, 0,
                         diag_reg_field_set,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         char*,char,field_name,1,0,
                         uint32*,uint32,value,1,0);

CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         diag_reg_field_only_set,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         uint32*,uint32,reg_value,1,0,
                         char*,char,field_name,1,0,
                         uint32*,uint32,field_value,1,0);

CINT_FWRAPPER_CREATE_RP3(int, int, 0, 0,
                         diag_soc_device_reset,
                         int,int,unit,0,0,
                         int,int,mode,0,0,
                         int,int,action,0,0);

CINT_FWRAPPER_CREATE_RP3(int, int, 0, 0,
                         diag_cm_get_unit_by_id,
                         uint16,uint16,dev_id,0,0,
                         int,int,occur,0,0,
                         int*,int,unit,1,0);

CINT_FWRAPPER_CREATE_RP6(int, int, 0, 0,
                         diag_mem_info_get,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         int* ,int ,mem,1,0,
                         int* ,int ,block_instance_id,1,0,
                         unsigned int* ,unsigned int ,block_instance_number,1,0,
                         unsigned int* ,unsigned int ,array_index,1,0);

CINT_FWRAPPER_CREATE_RP4(int, int, 0, 0,
                         diag_mem_get,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         int,int,start,0,0,
                         uint32*,uint32,value,1,0);

CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         diag_mem_field_get,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         char*,char,field_name,1,0,
                         int,int,start,0,0,
                         uint32*,uint32,value,1,0);

CINT_FWRAPPER_CREATE_RP6(int, int, 0, 0,
                         diag_mem_field_only_get,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         uint32*,uint32,value,1,0,
                         char*,char,field_name,1,0,
                         int,int,start,0,0,
                         uint32*,uint32,fval,1,0);

CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         diag_mem_set,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         int,int,start,0,0,
                         int,int,count,0,0,
                         uint32*,uint32,value,1,0);

CINT_FWRAPPER_CREATE_RP6(int, int, 0, 0,
                         diag_mem_field_set,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         char*,char,field_name,1,0,
                         int,int,start,0,0,
                         int,int,count,0,0,
                         uint32*,uint32,value,1,0);

CINT_FWRAPPER_CREATE_RP7(int, int, 0, 0,
                         diag_mem_field_only_set,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         uint32*,uint32,value,1,0,
                         char*,char,field_name,1,0,
                         int,int,start,0,0,
                         int,int,count,0,0,
                         uint32*,uint32,fval,1,0);

CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         diag_soc_mem_read_range,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         int,int,index1,0,0,
                         int,int,index2,0,0,
                         void*,void,buffer,1,0);

CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         diag_soc_mem_write_range,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         int,int,index1,0,0,
                         int,int,index2,0,0,
                         void*,void,buffer,1,0);

CINT_FWRAPPER_CREATE_RP3(int, int, 0, 0,
                         diag_mem_fill,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         void*,void,buffer,1,0);

CINT_FWRAPPER_CREATE_RP7(int, int, 0, 0,
                         diag_mem_array_fill_range,
                         int, int, unit, 0, 0,
                         char*, char, name, 1, 0,
                         unsigned int, unsigned int, min_ar_index, 0, 0,
                         unsigned int, unsigned int, max_ar_index, 0, 0,
                         int, int, index_min, 0, 0,
                         int, int, index_max, 0, 0,
                         void*, void, buffer, 1, 0);

CINT_FWRAPPER_CREATE_RP3(int, int, 0, 0,
                         diag_fill_table,
                         int,int,unit,0,0,
                         char*,char,name,1,0,
                         uint32*,uint32,value,1,0);

CINT_FWRAPPER_CREATE_RP2(int, int, 0, 0,
                         diag_mem_conf_test,
                         int,int,unit,0,0,
                         uint32,uint32,test_value,0,0);

CINT_FWRAPPER_CREATE_RP2(int, int, 0, 0,
                         diag_mbist,
                         int,int,unit,0,0,
                         int,int,skip_errors,0,0);

#ifdef BCM_SAND_SUPPORT
CINT_FWRAPPER_CREATE_RP1(int, int, 0, 0,
                         test_ua_macros,
                         int,int,unit,0,0);
#endif


CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         diag_mbist_ser_test,
                         int, int, unit, 0, 0,
                         int, int, skip_errors, 0, 0,
                         uint32, uint32, nof_repeats, 0, 0,
                         uint32, uint32, time_to_wait, 0, 0,
                         uint32, uint32, ser_test_num, 0, 0);

CINT_FWRAPPER_CREATE_RP2(int, int, 0, 0,
                         diag_get_hbm_temp,
                         int,int,unit,0,0,
                         unsigned int,unsigned int,hbm_number,0,0);

CINT_FWRAPPER_CREATE_RP1(int, int, 0, 0,
                         diag_modport2sysport,
                         int,int,unit,0,0);

CINT_FWRAPPER_CREATE_RP4(int, int, 0, 0,
                         diag_pointer,
                         int, int, unit, 0, 0,
                         char*, char, func_name, 1, 0,
                         void**, void, p, 2, 0,
                         char*, char, arg, 1, 0);

CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         soc_direct_reg_get,
                         int,int,unit,0,0,
                         int,int,cmic_block,0,0,
                         uint32,uint32,addr,0,0,
                         uint32,uint32,dwc_read,0,0,
                         uint32*,uint32,data,1,0);

CINT_FWRAPPER_CREATE_RP5(int, int, 0, 0,
                         soc_direct_reg_set,
                         int,int,unit,0,0,
                         int,int,cmic_block,0,0,
                         uint32,uint32,addr,0,0,
                         uint32,uint32,dwc_write,0,0,
                         uint32*,uint32,data,1,0);

CINT_FWRAPPER_CREATE_RP6(int, int, 0, 0,
                         soc_direct_memreg_get,
                         int,int,unit,0,0,
                         int,int,cmic_block,0,0,
                         uint32,uint32,addr,0,0,
                         uint32,uint32,dwc_read,0,0,
                         int, int, is_mem, 0, 0,
                         uint32*,uint32,data,1,0);

CINT_FWRAPPER_CREATE_RP6(int, int, 0, 0,
                         soc_direct_memreg_set,
                         int,int,unit,0,0,
                         int,int,cmic_block,0,0,
                         uint32,uint32,addr,0,0,
                         uint32,uint32,dwc_write,0,0,
                         int, int, is_mem, 0, 0,
                         uint32*,uint32,data,1,0);
CINT_FWRAPPER_CREATE_RP6(int,int, 0, 0,
                         diag_get_interrupt_id_byname,
                         int,int,unit,0,0,
                         char *,char,regName, 1,0,
                         int,int,reg_index, 0,0,
                         char *,char,fldName, 1,0,
                         int,int,bit_in_field, 0,0,
                         int *,int,interrupt_id, 1,0);
#ifdef BCM_DNX_SUPPORT
CINT_FWRAPPER_CREATE_RP4(int,int, 0, 0,
                         diag_counter_value_get,
                         int,int,unit,0,0,
                         char *,char,blkName, 1,0,
                         char *,char,counterName, 1,0,
                         uint64 *,uint64,counter, 1,0);
#endif

#if defined(BCM_DNX_SUPPORT)  || defined(BCM_DNXF_SUPPORT)
CINT_FWRAPPER_CREATE_RP1(int, int, 0, 0,
                         diag_bar_access_test,
                         int,int,unit,0,0);
#endif
#endif /* defined(BCM_SAND_SUPPORT) || defined(BCM_ESW_SUPPORT) */


static cint_function_t __cint_diag_functions[] =
{
    CINT_FWRAPPER_ENTRY(diag_printk),
    CINT_FWRAPPER_ENTRY(diag_printk_int),
    CINT_FWRAPPER_ENTRY(diag_pcie_read),
    CINT_FWRAPPER_ENTRY(diag_pcie_write),

#if defined(BCM_SAND_SUPPORT) || defined(BCM_ESW_SUPPORT)
    CINT_FWRAPPER_ENTRY(diag_reg_bits),
    CINT_FWRAPPER_ENTRY(diag_reg_field_bits),
    CINT_FWRAPPER_ENTRY(diag_reg_info_get),
    CINT_FWRAPPER_ENTRY(diag_reg_get),
    CINT_FWRAPPER_ENTRY(diag_reg_field_get),
    CINT_FWRAPPER_ENTRY(diag_reg_field_only_get),
    CINT_FWRAPPER_ENTRY(diag_reg_set),
    CINT_FWRAPPER_ENTRY(diag_reg_field_set),
    CINT_FWRAPPER_ENTRY(diag_reg_field_only_set),
    CINT_FWRAPPER_ENTRY(diag_mem_info_get),
    CINT_FWRAPPER_ENTRY(diag_mem_get),
    CINT_FWRAPPER_ENTRY(diag_mem_field_get),
    CINT_FWRAPPER_ENTRY(diag_mem_field_only_get),
    CINT_FWRAPPER_ENTRY(diag_mem_set),
    CINT_FWRAPPER_ENTRY(diag_mem_field_set),
    CINT_FWRAPPER_ENTRY(diag_mem_field_only_set),
    CINT_FWRAPPER_ENTRY(diag_soc_mem_read_range),
    CINT_FWRAPPER_ENTRY(diag_soc_mem_write_range),
    CINT_FWRAPPER_ENTRY(diag_mem_fill),
    CINT_FWRAPPER_ENTRY(diag_mem_array_fill_range),
    CINT_FWRAPPER_ENTRY(diag_fill_table),
    CINT_FWRAPPER_ENTRY(diag_mem_conf_test),
    CINT_FWRAPPER_ENTRY(diag_mbist),
#ifdef BCM_SAND_SUPPORT
    CINT_FWRAPPER_ENTRY(test_ua_macros),
#endif
    CINT_FWRAPPER_ENTRY(diag_mbist_ser_test),
    CINT_FWRAPPER_ENTRY(diag_get_hbm_temp),
    CINT_FWRAPPER_ENTRY(diag_modport2sysport),
    CINT_FWRAPPER_ENTRY(diag_pointer),
    CINT_FWRAPPER_ENTRY(soc_direct_reg_get),
    CINT_FWRAPPER_ENTRY(soc_direct_reg_set),
    CINT_FWRAPPER_ENTRY(soc_direct_memreg_get),
    CINT_FWRAPPER_ENTRY(soc_direct_memreg_set),
    CINT_FWRAPPER_ENTRY(diag_soc_device_reset),
    CINT_FWRAPPER_ENTRY(diag_cm_get_unit_by_id),
    CINT_FWRAPPER_ENTRY(diag_get_interrupt_id_byname),
#ifdef BCM_DNX_SUPPORT
    CINT_FWRAPPER_ENTRY(diag_counter_value_get),
#endif
#if defined(BCM_DNX_SUPPORT)  || defined(BCM_DNXF_SUPPORT)
    CINT_FWRAPPER_ENTRY(diag_bar_access_test),
#endif

#endif
#if defined(__DUNE_GTO_BCM_CPU__) || defined(__DUNE_WRX_BCM_CPU__) || defined(__DUNE_SLK_BCM_CPU__) || defined(__DUNE_GTS_BCM_CPU__) || defined(INCLUDE_CPU_I2C)
    CINT_FWRAPPER_ENTRY(cpu_i2c_write),
    CINT_FWRAPPER_ENTRY(cpu_i2c_read),
    CINT_FWRAPPER_ENTRY(sal_i2c_write),
    CINT_FWRAPPER_ENTRY(sal_i2c_write_int),
    CINT_FWRAPPER_ENTRY(sal_i2c_read),
    CINT_FWRAPPER_ENTRY(sal_i2c_read_int),
    CINT_FWRAPPER_ENTRY(sal_i2c_smbus_read),
    CINT_FWRAPPER_ENTRY(sal_i2c_smbus_write),
#endif


    CINT_ENTRY_LAST
};

static cint_parameter_desc_t __cint_typedefs[] =
{
    {
        "uint32",
        "reg_val",
        0,
        SOC_REG_ABOVE_64_MAX_SIZE_U32
    },
    {
        "uint32",
        "mem_val",
        0,
        SOC_MAX_MEM_WORDS
    },
    {NULL}
};

static cint_constants_t __cint_diag_constants[] =
{
   { "DIAG_PRINTK_FLAGS_HEX", DIAG_PRINTK_FLAGS_HEX },
   { NULL }
};

#if defined(INCLUDE_I2C) && (defined (__DUNE_GTO_BCM_CPU__) || defined(__DUNE_WRX_BCM_CPU__) || defined(__DUNE_SLK_BCM_CPU__) || defined(__DUNE_GTS_BCM_CPU__))
static cint_enum_map_t __cint_diag_enum_map__CPU_I2C_BUS_LEN[] =
{
  { "CPU_I2C_ALEN_NONE_DLEN_BYTE", CPU_I2C_ALEN_NONE_DLEN_BYTE },
  { "CPU_I2C_ALEN_NONE_DLEN_WORD", CPU_I2C_ALEN_NONE_DLEN_WORD },
  { "CPU_I2C_ALEN_NONE_DLEN_LONG", CPU_I2C_ALEN_NONE_DLEN_LONG },
  { "CPU_I2C_ALEN_BYTE_DLEN_BYTE", CPU_I2C_ALEN_BYTE_DLEN_BYTE },
  { "CPU_I2C_ALEN_BYTE_DLEN_WORD", CPU_I2C_ALEN_BYTE_DLEN_WORD },
  { "CPU_I2C_ALEN_WORD_DLEN_WORD", CPU_I2C_ALEN_WORD_DLEN_WORD },
  { "CPU_I2C_ALEN_BYTE_DLEN_LONG", CPU_I2C_ALEN_BYTE_DLEN_LONG },
  { "CPU_I2C_ALEN_WORD_DLEN_LONG", CPU_I2C_ALEN_WORD_DLEN_LONG },
  { "CPU_I2C_ALEN_LONG_DLEN_LONG", CPU_I2C_ALEN_LONG_DLEN_LONG },
  { NULL }
};
#endif

static cint_enum_type_t __cint_diag_enums[] =
{
#if defined(INCLUDE_I2C) && (defined (__DUNE_GTO_BCM_CPU__) || defined(__DUNE_WRX_BCM_CPU__) || defined(__DUNE_SLK_BCM_CPU__) || defined(__DUNE_GTS_BCM_CPU__))
  { "CPU_I2C_BUS_LEN", __cint_diag_enum_map__CPU_I2C_BUS_LEN },
#endif
  { NULL }
};

cint_data_t diag_cint_data =
{
    NULL,
    __cint_diag_functions,
    NULL,
    __cint_diag_enums,
    __cint_typedefs,
    __cint_diag_constants,
    NULL
};

#endif /* INCLUDE_LIB_CINT*/


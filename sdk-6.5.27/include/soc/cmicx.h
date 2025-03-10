/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * File:        cmicx.h
 * Purpose:     CMICX registers include file
 */
#ifndef _SOC_CMICX_H
#define _SOC_CMICX_H

#include <soc/mcm/cmicx.h>
#include <soc/cmic.h>

/* Use this file for stuff that are not Auto-Generated */
#define CMIC_CMC_NUM_MAX      (2)

#define CMIC_SCHAN_NUM_MAX      (3)
#define CMIC_CCMDMA_NUM_MAX     (2)
#define CMIC_TOP_SBUS_RING_ARB_CTRL_SET   (0xEEEEEEEE)

#define CMIC_COMMON_POOL_SCHAN_CHx_MESSAGEn(ch, n)       \
                              (CMIC_COMMON_POOL_SCHAN_CH0_MESSAGE_OFFSET + (ch*0x100) + (4*n))
#define CMIC_COMMON_POOL_SCHAN_CHx_CTRL(ch)       \
                              (CMIC_COMMON_POOL_SCHAN_CH0_CTRL_OFFSET + (ch*0x100))

#define CMIC_COMMON_POOL_SCHAN_CHx_ERR(ch)       \
                              (CMIC_COMMON_POOL_SCHAN_CH0_ERR_OFFSET + (ch*0x100))


/* CMIC_COMMON_POOL_SCHAN_CHx_CTRL(x) */
#define SC_CHx_MSG_CLR                 (0x00000000)
#define SC_CHx_MSG_START               (0x00000001)
#define SC_CHx_MSG_DONE                (0x00000002)
#define SC_CHx_SCHAN_ABORT             (0x00000004)
#define SC_CHx_MSG_SER_CHECK_FAIL      (0x00100000)
#define SC_CHx_MSG_NAK                 (0x00200000)
#define SC_CHx_MSG_TIMEOUT_TST         (0x00400000)
#define SC_CHx_MSG_SCHAN_ERR           (0x00800000)

/* CMIC_COMMON_POOL_SCHAN_CHx_ERR(x) */
#define SC_CHx_SCHAN_ERR_NACK_BIT        (0x00000001)
#define SC_CHx_SCHAN_ERR_ERR_BIT         (0x00000040)

/* CMC */
#define CMIC_CMCx_PCI                           (0x0)
#define CMIC_CMCx_AXI                           (0x1)

/* SBUSDMA stuff */

#define CMIC_CMCx_SBUSDMA_CHAN_MAX              (4)
#define CMIC_CMC0_SBUSDMA_CH_MASK               (0xf)
#define CMIC_CMC1_SBUSDMA_CH_MASK               (0xf)

#define CMIC_CMCx_SBUSDMA_CHy_CONTROL(x, y)                   \
            (CMIC_CMCx_SBUSDMA_CH0_CONTROL_OFFSET(x)                                  + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_REQUEST(x, y)                   \
            (CMIC_CMCx_SBUSDMA_CH0_REQUEST_OFFSET(x)                                  + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_COUNT(x, y)                     \
            (CMIC_CMCx_SBUSDMA_CH0_COUNT_OFFSET(x)                                    + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_OPCODE(x, y)                    \
            (CMIC_CMCx_SBUSDMA_CH0_OPCODE_OFFSET(x)                                   + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_ADDRESS(x, y)                   \
            (CMIC_CMCx_SBUSDMA_CH0_SBUS_START_ADDRESS_OFFSET(x)                       + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_HOSTADDR_LO(x, y)                  \
            (CMIC_CMCx_SBUSDMA_CH0_HOSTMEM_START_ADDRESS_LO_OFFSET(x)                 + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_HOSTADDR_HI(x, y)                  \
            (CMIC_CMCx_SBUSDMA_CH0_HOSTMEM_START_ADDRESS_HI_OFFSET(x)                 + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_DESCADDR_LO(x, y)                  \
            (CMIC_CMCx_SBUSDMA_CH0_DESC_START_ADDRESS_LO_OFFSET(x)                    + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_DESCADDR_HI(x, y)                  \
            (CMIC_CMCx_SBUSDMA_CH0_DESC_START_ADDRESS_HI_OFFSET(x)                    + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_STATUS(x, y)                    \
            (CMIC_CMCx_SBUSDMA_CH0_STATUS_OFFSET(x)                                   + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_SBUSDMA_CONFIG_OPCODE(x, y) \
            (CMIC_CMCx_SBUSDMA_CH0_CUR_SBUSDMA_CONFIG_OPCODE_OFFSET(x)                + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_SBUSDMA_CONFIG_ADDR_LO(x, y)   \
            (CMIC_CMCx_SBUSDMA_CH0_CUR_SBUSDMA_CONFIG_HOSTMEM_START_ADDRESS_LO_OFFSET(x) + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_SBUSDMA_CONFIG_ADDR_HI(x, y)   \
            (CMIC_CMCx_SBUSDMA_CH0_CUR_SBUSDMA_CONFIG_HOSTMEM_START_ADDRESS_HI_OFFSET(x) + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_SBUSDMA_CONFIG_COUNT(x, y)   \
            (CMIC_CMCx_SBUSDMA_CH0_CUR_SBUSDMA_CONFIG_COUNT_OFFSET(x)                  + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_SBUSDMA_CONFIG_REQUEST(x, y)                   \
            (CMIC_CMCx_SBUSDMA_CH0_CUR_SBUSDMA_CONFIG_REQUEST_OFFSET(x)                + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_SBUSDMA_CONFIG_SBUS_START_ADDRESS(x, y)                   \
            (CMIC_CMCx_SBUSDMA_CH0_CUR_SBUSDMA_CONFIG_SBUS_START_ADDRESS_OFFSET(x)     + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_SBUSDMA_ITER_COUNT(x, y)   \
            (CMIC_CMCx_SBUSDMA_CH0_ITER_COUNT_OFFSET(x)                                + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_HOSTMEM_ADDRESS_LO(x, y)   \
            (CMIC_CMCx_SBUSDMA_CH0_CUR_HOSTMEM_ADDRESS_LO_OFFSET(x)                    + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_HOSTMEM_ADDRESS_HI(x, y)   \
            (CMIC_CMCx_SBUSDMA_CH0_CUR_HOSTMEM_ADDRESS_HI_OFFSET(x)                    + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_DESC_ADDRESS_LO(x, y)   \
            (CMIC_CMCx_SBUSDMA_CH0_CUR_DESC_ADDRESS_LO_OFFSET(x)                       + (y * 0x100))
#define CMIC_CMCx_SBUSDMA_CHy_CUR_DESC_ADDRESS_HI(x, y)   \
            (CMIC_CMCx_SBUSDMA_CH0_CUR_DESC_ADDRESS_HI_OFFSET(x)                       + (y * 0x100))

/* CMIC_CMCx_SBUSDMA_CHy_CONTROL */
#define CMIC_CMCx_SBUSDMA_CHy_CONTROL_START                   1
#define CMIC_CMCx_SBUSDMA_CHy_CONTROL_ABORT                   2
#define CMIC_CMCx_SBUSDMA_CHy_CONTROL_MODE                    4
#define CMIC_CMCx_SBUSDMA_CHy_CONTROL_DESCRIPTOR_ENDIANESS    8
#define CMIC_CMCx_SBUSDMA_CHy_CONTROL_DESC_PREFETCH_ENABLE 0x10

/* CMIC_CMCx_SBUSDMA_CHy_STATUS */
#define CMIC_CMCx_SBUSDMA_CHy_STATUS_DONE                  1
#define CMIC_CMCx_SBUSDMA_CHy_STATUS_ERROR                 2
#define CMIC_CMCx_SBUSDMA_CHy_STATUS_HOSTMEMWR_ERROR       4
#define CMIC_CMCx_SBUSDMA_CHy_STATUS_HOSTMEMRD_ERROR       8
#define CMIC_CMCx_SBUSDMA_CHy_STATUS_SER_CHECK_FAIL     0x10

/* CMIC_CMCx_SBUSDMA_CHy_CONTROL */
#define CMIC_CMCx_SBUSDMA_CHy_CONTROL_START                   1
#define CMIC_CMCx_SBUSDMA_CHy_CONTROL_ABORT                   2
#define CMIC_CMCx_SBUSDMA_CHy_CONTROL_MODE                    4
#define CMIC_CMCx_SBUSDMA_CHy_CONTROL_DESCRIPTOR_ENDIANESS    8
#define CMIC_CMCx_SBUSDMA_CHy_CONTROL_DESC_PREFETCH_ENABLE 0x10

/* CMIC_CMCx_SBUSDMA_CHy_STATUS */
#define CMIC_CMCx_SBUSDMA_CHy_STATUS_DONE                  1
#define CMIC_CMCx_SBUSDMA_CHy_STATUS_ERROR                 2
#define CMIC_CMCx_SBUSDMA_CHy_STATUS_HOSTMEMWR_ERROR       4
#define CMIC_CMCx_SBUSDMA_CHy_STATUS_HOSTMEMRD_ERROR       8
#define CMIC_CMCx_SBUSDMA_CHy_STATUS_SER_CHECK_FAIL     0x10


/* SCHAN FIFO */
#define CMIC_SCHAN_FIFO_NUM_MAX      (2)
/* Number of commands SCHAN FIFO can accomodate in one channel */
#define CMIC_SCHAN_FIFO_CMD_SIZE_MAX   (16)
#define MAP_SCHAN_FIFO_MEMWR_REQ_CMC0        (0x00)
#define MAP_SCHAN_FIFO_MEMWR_REQ_CMC1        (0x01)
#define SCHAN_FIFO_MEMWR_WRR_WEIGHT          (0x0E)
#define SCHAN_FIFO_AXI_ID                    (0x05)
#define SCHAN_FIFO_RESPONSE_WORD_SIZE        (32) /*128 bytes aligned */
#define SCHAN_FIFO_SUMMARY_ACKDATA_MASK      (0xFF)
#define SCHAN_FIFO_SUMMARY_STAT_SHIFT         (8)



#define CMIC_SCHAN_FIFO_CHx_CTRL(x) \
                               (CMIC_COMMON_POOL_SCHAN_FIFO_0_CH0_CTRL_OFFSET + x*0x18)
#define CMIC_SCHAN_FIFO_CHx_RESP_ADDR_LOWER(x) \
             (CMIC_COMMON_POOL_SCHAN_FIFO_0_CH0_RESP_HOSTMEM_START_ADDR_LOWER_OFFSET + x * 0x18)
#define CMIC_SCHAN_FIFO_CHx_RESP_ADDR_UPPER(x) \
             (CMIC_COMMON_POOL_SCHAN_FIFO_0_CH0_RESP_HOSTMEM_START_ADDR_UPPER_OFFSET + x * 0x18)

#define CMIC_SCHAN_FIFO_CHx_STATUS(x) \
             (CMIC_COMMON_POOL_SCHAN_FIFO_0_CH0_STATUS_OFFSET + x * 0x18)
#define CMIC_SCHAN_FIFO_CHx_SUMMARY_ADDR_LOWER(x) \
             (CMIC_COMMON_POOL_SCHAN_FIFO_0_CH0_SUMMARY_HOSTMEM_START_ADDR_LOWER_OFFSET + x * 0x18)
#define CMIC_SCHAN_FIFO_CHx_SUMMARY_ADDR_UPPER(x) \
             (CMIC_COMMON_POOL_SCHAN_FIFO_0_CH0_SUMMARY_HOSTMEM_START_ADDR_UPPER_OFFSET + x * 0x18)
#define CMIC_SCHAN_FIFO_CHx_COMMAND(x, n) \
             (CMIC_COMMON_POOL_SCHAN_FIFO_0_CH0_COMMAND_MEMORY_OFFSET + (x * 0x580) + (4 * n))

#define SCHAN_FIFO_SUMRY_STAT_COMPLETE        (0x00 << (5 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))
#define SCHAN_FIFO_SUMRY_STAT_ECCERR          (0x01 << (5 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))
#define SCHAN_FIFO_SUMRY_STAT_SBUSERR         (0x02 << (5 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))
#define SCHAN_FIFO_SUMRY_STAT_OTHERR          (0x03 << (5 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))

#define SCHAN_FIFO_SUMRY_ERR_SBUSNACK         (0x01 + SCHAN_FIFO_SUMMARY_STAT_SHIFT)
#define SCHAN_FIFO_SUMRY_ERR_SBUSECODE        (0x03 << (1 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))
#define SCHAN_FIFO_SUMRY_ERR_SBUSERR          (0x01 << (3 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))
#define SCHAN_FIFO_SUMRY_ERR_OPCODE           (0x01 << (4 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))

#define SCHAN_FIFO_SUMRY_ABRT_ECCCMD          (0x01 + SCHAN_FIFO_SUMMARY_STAT_SHIFT)
#define SCHAN_FIFO_SUMRY_ABRT_OPCODE          (0x01 << (1 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))
#define SCHAN_FIFO_SUMRY_ABRT_CMDLEN          (0x01 << (2 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))
#define SCHAN_FIFO_SUMRY_ABRT_TIMOUT          (0x01 << (3 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))
#define SCHAN_FIFO_SUMRY_ABRT_DBEAT           (0x01 << (4 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))
#define SCHAN_FIFO_SUMRY_ABRT_ECCMEM          (0x01 << (5 + SCHAN_FIFO_SUMMARY_STAT_SHIFT))

#define SCHAN_FIFO_SUMMARY_UPDATE_INTERVAL    (0x10)
#define SCHAN_FIFO_MSG_DONE                   (0x01)

/* fields of CMIC_COMMON_POOL_SCHAN_FIFO_0_CHy_CTRL / CMIC_SCHAN_FIFO_CHx_CTRL */
#define SCHAN_FIFO_CTRL_START                 1
#define SCHAN_FIFO_CTRL_ABORT                 2
/* fields of CMIC_COMMON_POOL_SCHAN_FIFO_0_CHy_STATUS / CMIC_SCHAN_FIFO_CHx_STATUS(x) */
#define SCHAN_FIFO_STATUS_DONE                1
#define SCHAN_FIFO_STATUS_ERROR               2

/* CCM DMA */
#define CMICX_N_CCMDMA_CHAN                    2

#define CMIC_CMCx_CCMDMA_CHy_HOST0_MEM_START_ADDR_LO_OFFSET(x,y)    \
            (CMIC_CMCx_CCMDMA_CH0_HOST0_MEM_START_ADDR_LO_OFFSET(x) + (y * 0x80))
#define CMIC_CMCx_CCMDMA_CHy_HOST0_MEM_START_ADDR_HI_OFFSET(x,y)    \
            (CMIC_CMCx_CCMDMA_CH0_HOST0_MEM_START_ADDR_HI_OFFSET(x) + (y * 0x80))
#define CMIC_CMCx_CCMDMA_CHy_HOST1_MEM_START_ADDR_LO_OFFSET(x,y)    \
            (CMIC_CMCx_CCMDMA_CH0_HOST1_MEM_START_ADDR_LO_OFFSET(x) + (y * 0x80))
#define CMIC_CMCx_CCMDMA_CHy_HOST1_MEM_START_ADDR_HI_OFFSET(x,y)    \
            (CMIC_CMCx_CCMDMA_CH0_HOST1_MEM_START_ADDR_HI_OFFSET(x) + (y * 0x80))
#define CMIC_CMCx_CCMDMA_CHy_ENTRY_COUNT_OFFSET(x,y)    \
            (CMIC_CMCx_CCMDMA_CH0_ENTRY_COUNT_OFFSET(x) + (y * 0x80))
#define CMIC_CMCx_CCMDMA_CHy_CFG_OFFSET(x,y)    \
            (CMIC_CMCx_CCMDMA_CH0_CFG_OFFSET(x) + (y * 0x80))
#define CMIC_CMCx_CCMDMA_CHy_STAT_OFFSET(x,y)    \
            (CMIC_CMCx_CCMDMA_CH0_STAT_OFFSET(x) + (y * 0x80))

/* CMIC_CMCx_CCMDMA_CHy_CFG fields */
#define CMIC_CMCx_CCMDMA_CHy_CFG_EN    1
#define CMIC_CMCx_CCMDMA_CHy_CFG_ABORT 2
/* CMIC_CMCx_CCMDMA_CHy_STAT fields */
#define CMIC_CMCx_CCMDMA_CHy_STAT_DONE  1
#define CMIC_CMCx_CCMDMA_CHy_STAT_ERROR 2

/* PCI SLAVE OFFSET */
#define CMIC_PCIE_SO_OFFSET                  (0x10000000)

/* Packet DMA related macros */
#define CMIC_CMCx_PKTDMA_NOF_CHANS      8

#define CMIC_CMCx_PKTDMA_CHy_CTRL_OFFSET(x, y)                   (CMIC_CMCx_PKTDMA_CH0_CTRL_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_CURR_DESC_HI_OFFSET(x, y)           (CMIC_CMCx_PKTDMA_CH0_CURR_DESC_HI_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_CURR_DESC_LO_OFFSET(x, y)           (CMIC_CMCx_PKTDMA_CH0_CURR_DESC_LO_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_DESC_ADDR_HI_OFFSET(x, y)           (CMIC_CMCx_PKTDMA_CH0_DESC_ADDR_HI_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_DESC_ADDR_LO_OFFSET(x, y)           (CMIC_CMCx_PKTDMA_CH0_DESC_ADDR_LO_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_DESC_HALT_ADDR_HI_OFFSET(x, y)      (CMIC_CMCx_PKTDMA_CH0_DESC_HALT_ADDR_HI_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_DESC_HALT_ADDR_LO_OFFSET(x, y)      (CMIC_CMCx_PKTDMA_CH0_DESC_HALT_ADDR_LO_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_INTR_COAL_OFFSET(x,y)               (CMIC_CMCx_PKTDMA_CH0_INTR_COAL_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_PKT_COUNT_RXPKT_OFFSET(x, y)        (CMIC_CMCx_PKTDMA_CH0_PKT_COUNT_RXPKT_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_PKT_COUNT_RXPKT_DROP_OFFSET(x, y)   (CMIC_CMCx_PKTDMA_CH0_PKT_COUNT_RXPKT_DROP_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_PKT_COUNT_TXPKT_OFFSET(x, y)        (CMIC_CMCx_PKTDMA_CH0_PKT_COUNT_TXPKT_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_RXBUF_THRESHOLD_CONFIG_OFFSET(x,y)  (CMIC_CMCx_PKTDMA_CH0_RXBUF_THRESHOLD_CONFIG_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_STAT_OFFSET(x, y)                   (CMIC_CMCx_PKTDMA_CH0_STAT_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_COS_CTRL_RX_0_OFFSET(x, y)          (CMIC_CMCx_PKTDMA_CH0_COS_CTRL_RX_0_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_COS_CTRL_RX_1_OFFSET(x, y)          (CMIC_CMCx_PKTDMA_CH0_COS_CTRL_RX_1_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_DESC_COUNT_REQ_OFFSET(x, y)         (CMIC_CMCx_PKTDMA_CH0_DESC_COUNT_REQ_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_DESC_COUNT_RX_OFFSET(x, y)          (CMIC_CMCx_PKTDMA_CH0_DESC_COUNT_RX_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_DESC_COUNT_STATUS_WR_OFFSET(x, y)   (CMIC_CMCx_PKTDMA_CH0_DESC_COUNT_STATUS_WR_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_DEBUG_CONTROL_OFFSET(x, y)          (CMIC_CMCx_PKTDMA_CH0_DEBUG_CONTROL_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_DEBUG_STATUS_OFFSET(x, y)           (CMIC_CMCx_PKTDMA_CH0_DEBUG_STATUS_OFFSET(x) + (y*0x80))
#define CMIC_CMCx_PKTDMA_CHy_DEBUG_SM_STATUS_OFFSET(x, y)        (CMIC_CMCx_PKTDMA_CH0_DEBUG_SM_STATUS_OFFSET(x) + (y*0x80))

/* CMIC_CMCx_CHy_DMA_CTRL */
#define PKTDMA_DIRECTION                (0x00000001)
#define PKTDMA_ENABLE                   (0x00000002)
#define PKTDMA_ABORT                    (0x00000004)
#define PKTDMA_BIG_ENDIAN               (0x00000008)
#define PKTDMA_DESC_BIG_ENDIAN          (0x00000010)
#define PKTDMA_DROP_RX_PKT_ON_CHAIN_END (0x00000020)
#define PKTDMA_RLD_STATUS_UPD_DIS       (0x00000040)
#define PKTDMA_DESC_DONE_INTR_MODE      (0x00000080)
#define PKTDMA_CONTINUOUS_ENABLE        (0x00000100)
#define PKTDMA_CONTIGUOUS_DESCRIPTORS   (0x00000200)
#define PKTDMA_HEADER_ENDIAN            (0x00001000)
#define PKTDMA_DISABLE_ABORT_ON_ERROR   (0x00002000)
#define PKTDMA_ALMNT_BYTES              (0x00000c00)

#define PKTDMA_CHAIN_DONE               (0x00000001)
#define PKTDMA_CH_IS_ACTIVE             (0x00000002)
#define PKTDMA_CH_IN_HALT               (0x00000040)
#define PKTDMA_ADDR_DECODE_ERR          (0x0000001C)


/* TBD */
#define IRQ_CMCx_CHy_CNTLD_INTR(cmc, chan)      0xFFFFFFFF
#define IRQ_CMCx_CHy_DESC_DONE(cmc, chan)       0xEEEEEEEE
#define IRQ_CMCx_CHy_CHAIN_DONE(cmc, chan)      0xDDDDDDDD
#define IRQ_CMCx_CHy_COAL_INTR(cmc, chan)       0xCCCCCCCC

/* CMIC_CMC0_SHARED_IRQ_STAT0(x) */
#define DS_CMCx_CHy_DMA_DESC_DONE(y)            ((uint32)0x00000001 << (y * 4))
#define DS_CMCx_CHy_DMA_CHAIN_DONE(y)           ((uint32)0x00000002 << (y * 4))
#define DS_CMCx_CHy_COALESCING_INTR(y)          ((uint32)0x00000004 << (y * 4))
#define DS_CMCx_CHy_DESC_CONTROLLED_INTR(y)     ((uint32)0x00000008 << (y * 4))

/* CMIC_CMC0_SHARED_IRQ_STAT_CLR0(x) */
#define DS_CMCx_CHy_DMA_DESC_DONE_CLR(y)        ((uint32)0x00000001 << (y * 4))
#define DS_CMCx_CHy_DMA_CHAIN_DONE_CLR(y)       ((uint32)0x00000002 << (y * 4))
#define DS_CMCx_CHy_COALESCING_INTR_CLR(y)      ((uint32)0x00000004 << (y * 4))
#define DS_CMCx_CHy_DESC_CONTROLLED_INTR_CLR(y) ((uint32)0x00000008 << (y * 4))

/* FIFO DMA stuff */
#define MAP_FIFO_DMA_MEMWR_REQ_CMC0          (0x00)
#define MAP_FIFO_DMA_MEMWR_REQ_CMC1          (0x01)
#define CMICX_FIFO_DMA_MEMWR_WRR_WEIGHT      (0x0E)
#define CMICX_FIFO_DMA_AXI_ID                (0x06)

#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_CFG_OFFSET(y)                      (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_CFG_OFFSET + (y*0x80))
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_CFG_1_OFFSET(y)                    (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_CFG_1_OFFSET + (y*0x80))
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_SBUS_START_ADDRESS_OFFSET(y)       (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_SBUS_START_ADDRESS_OFFSET + (y*0x80))
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_HOSTMEM_START_ADDRESS_LO_OFFSET(y) (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_HOSTMEM_START_ADDRESS_LO_OFFSET + (y*0x80))
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_HOSTMEM_START_ADDRESS_HI_OFFSET(y) (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_HOSTMEM_START_ADDRESS_HI_OFFSET + (y*0x80))
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_NUM_OF_ENTRIES_READ_FRM_HOSTMEM_OFFSET(y) \
                                                                            (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_NUM_OF_ENTRIES_READ_FRM_HOSTMEM_OFFSET + (y*0x80))
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_NUM_OF_ENTRIES_VALID_IN_HOSTMEM_OFFSET(y) \
                                                                            (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_NUM_OF_ENTRIES_VALID_IN_HOSTMEM_OFFSET + (y*0x80))
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_HOSTMEM_THRESHOLD_OFFSET(y)        (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_HOSTMEM_THRESHOLD_OFFSET + (y*0x80))
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_STAT_OFFSET(y)                     (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_STAT_OFFSET + (y*0x80))
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_STAT_CLR_OFFSET(y)                 (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_STAT_CLR_OFFSET + (y*0x80))
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_OPCODE_OFFSET(y)                          \
                                                                            (CMIC_COMMON_POOL_FIFO_CH0_RD_DMA_OPCODE_OFFSET + (y*0x80))
/* CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_CFG fields */
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_CFG_ENABLE           1
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_CFG_ABORT   0x80000000
/* CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_STAT fields */
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_STAT_ERROR       1
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_STAT_ACTIVE      2
#define CMIC_COMMON_POOL_FIFO_CHy_RD_DMA_STAT_ABORTED  0x10

/*
 * This macro may be used to transfer T from microseconds to the value to be entered into
 * CMIC_COMMON_POOL_FIFO_CH*_RD_DMA_CFG*.TIMEOUT_COUNT*.
 * Timer runs on reference clock 25MHz.
 */
#define CMIC_COMMON_POOL_FIFO_USEC_TO_DMA_CFG_TIMEOUT_COUNT(T) (T *= 25); 

/* MDIO Clock Frquency for TD3/TH3 is 250 MHz
 * Set external MDIO freq to around 5 MHz
 * Hence divisor is set to 50
 * HR4/FB6 its set to 20 as per HW design
 */
#define RATE_EXT_MDIO_DIVISOR_DEF(unit)       \
          ((SOC_IS_HURRICANE4(unit) || SOC_IS_FIREBOLT6(unit)) ? 20 : 50)

#if defined(SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined(BCM_ESW_SUPPORT)
extern void soc_cmicx_verify_before_idb_reset(int unit);
extern void soc_cmicx_top_ip_intf_credit_reset(int unit);
extern void soc_cmicx_verify_after_idb_reset(int unit);
#endif
#endif  /* !_SOC_CMICX_H */

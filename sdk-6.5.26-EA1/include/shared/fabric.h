/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * This file defines common network port parameters.
 *
 * Its contents are not used directly by applications; it is used only
 * by header files of parent APIs which need to define port parameters.
 */

#ifndef _SHR_FABRIC_H
#define _SHR_FABRIC_H

#define _SHR_FABRIC_LINK_STATUS_CRC_ERROR    0x00000001 /* A cell with CRC error was received on this link. */
#define _SHR_FABRIC_LINK_STATUS_SIZE_ERROR   0x00000002 /* A data cell with wrong size was received .
                                                           A high rate of size error indicates a bad link that
                                                           should be shut down or requires SerDes tuning.*/
#define _SHR_FABRIC_LINK_STATUS_CODE_GROUP_ERROR 0x00000004 /* FEC uncorrectable error. */
#define _SHR_FABRIC_LINK_STATUS_MISALIGN     0x00000008 /* Loss of FEC sync is detected
                                                           on this link. */
#define _SHR_FABRIC_LINK_STATUS_NO_SIG_LOCK  0x00000010 /* SerDes signal lock error */
#define _SHR_FABRIC_LINK_STATUS_NO_SIG_ACCEP 0x00000020 /* No PMD lock in the SerDes. */
#define _SHR_FABRIC_LINK_STATUS_ERRORED_TOKENS 0x00000040 /* The tokens are increased when cells with
                                                            no CRC errors and no decoding errors arrive,
                                                            and decreased when a faulty cell is detected.
                                                            Value less than 63 indicates an unacceptable amount
                                                            of faulty cells received on link. */
#define _SHR_FABRIC_LINK_STATUS_LOCAL_FAULT    0x00000080 /* Local Fault */
#define _SHR_FABRIC_LINK_STATUS_REMOTE_FAULT   0x00000100 /* Remote Fault */

#define _SHR_FABRIC_LINK_NO_CONNECTIVITY (0xFFFFFFFF) /* FABRIC_LINK_NO_CONNECTIVITY */

/* fabric link up indication source macros */
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MASK                      (0xFFFFFFFF)

#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MAC_                      (0x00000001)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MAC_SET(arg)              (arg |= _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MAC_)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MAC_GET(arg)              (arg & _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MAC_)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MAC_CLEAR(arg)            \
        (arg &= (_SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MASK ^ _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MAC_))

#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_FEC                       (0x00000002)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_FEC_SET(arg)              (arg |= _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_FEC)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_FEC_GET(arg)              ((arg & _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_FEC) >> 1)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_FEC_CLEAR(arg)    \
        (arg &= (_SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MASK ^ _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_FEC))

#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_SERDES                    (0x00000004)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_SERDES_SET(arg)           (arg |= _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_SERDES)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_SERDES_GET(arg)           ((arg & _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_SERDES) >> 2)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_SERDES_CLEAR(arg)         \
        (arg &= (_SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MASK ^ _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_SERDES))

#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_LOCAL_FAULT               (0x00000008)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_LOCAL_FAULT_SET(arg)      (arg |= _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_LOCAL_FAULT)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_LOCAL_FAULT_GET(arg)      ((arg & _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_LOCAL_FAULT) >> 3)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_LOCAL_FAULT_CLEAR(arg)    \
        (arg &= (_SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MASK ^ _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_LOCAL_FAULT))

#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_REMOTE_FAULT              (0x00000010)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_REMOTE_FAULT_SET(arg)     (arg |= _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_REMOTE_FAULT)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_REMOTE_FAULT_GET(arg)     ((arg & _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_REMOTE_FAULT) >> 4)
#define _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_REMOTE_FAULT_CLEAR(arg)   \
        (arg &= (_SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_MASK ^ _SHR_FABRIC_LINK_UP_SOURCE_MAP_INDICATION_REMOTE_FAULT))


#define _SHR_FABRIC_FLAG_GET                 0x0
#define _SHR_FABRIC_FLAG_SET                 0x1

/* bcm_fabric_priority_* flags */
#define _SHR_FABRIC_QUEUE_PRIORITY_HIGH_ONLY 0x1        
#define _SHR_FABRIC_QUEUE_PRIORITY_LOW_ONLY  0x2             
#define _SHR_FABRIC_PRIORITY_MULTICAST       0x8  
#define _SHR_FABRIC_PRIORITY_TDM             0x10
#define _SHR_FABRIC_PRIORITY_OCB_MIX_ONLY    0x20        
#define _SHR_FABRIC_PRIORITY_OCB_ONLY_ONLY   0x40        

/*bcm_fabric_multicast_* flgas*/
#define _SHR_FABRIC_MULTICAST_SET_ONLY       0x1
#define _SHR_FABRIC_MULTICAST_COMMIT_ONLY    0x2
#define _SHR_FABRIC_MULTICAST_STATUS_ONLY    0x4

/*bcm_fabric_profile_threshold_* valid flags*/
#define _SHR_FABRIC_TH_FLAG_FE1_ONLY            0x01
#define _SHR_FABRIC_TH_FLAG_FE3_ONLY            0x02
#define _SHR_FABRIC_TH_FLAG_LR                  0x04
#define _SHR_FABRIC_TH_FLAG_NLR                 0x08

/* FabricLinkCellFormat flags */
#define _SHR_FABRIC_LINK_CELL_FORMAT_VSC256_V1              (0)/* VSC256_V1 cell format */
#define _SHR_FABRIC_LINK_CELL_FORMAT_VSC128                 (1)/* VSC128 cell format */
#define _SHR_FABRIC_LINK_CELL_FORMAT_VSC256_V2              (2)/* VSC256_V2 cell format */
#define _SHR_FABRIC_LINK_CELL_FORMAT_VSC256_V2x2            (3)/* VSC256_V2x2 cell format */
#define _SHR_FABRIC_LINK_CELL_FORMAT_VSC512                 (4)/* VSC512 cell format */

/* bcmFabricLLFControlType flags */
#define _SHR_FABRIC_LINK_LLFC_TYPE_NONE               (0)/* LLFC disabled */
#define _SHR_FABRIC_LINK_LLFC_TYPE_LLFC               (1)/* Regular/standart LLFC */
#define _SHR_FABRIC_LINK_LLFC_TYPE_CREDIT_BASED       (2)/* Credit based LLFC */

/* bcm_fabric_profile_threshold_* threshold_id MACROS */

#define _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT           (24)
#define _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_VAL             (0x1)
#define _SHR_FABRIC_TH_INDEX_CAST_PRIO_VAL              (0x2)
#define _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_VAL   (0x3)
#define _SHR_FABRIC_TH_INDEX_CAST_LEVEL_VAL             (0x4)
#define _SHR_FABRIC_TH_INDEX_PIPE_LINK_VAL              (0x5)
#define _SHR_FABRIC_TH_INDEX_MASK                       (0xff)
#define _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_INDICATION      (_SHR_FABRIC_TH_INDEX_PIPE_LEVEL_VAL << _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT)
#define _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_INDICATION   (_SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_VAL << _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT)
#define _SHR_FABRIC_TH_INDEX_CAST_PRIO_INDICATION       (_SHR_FABRIC_TH_INDEX_CAST_PRIO_VAL << _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT)
#define _SHR_FABRIC_TH_INDEX_CAST_LEVEL_INDICATION      (_SHR_FABRIC_TH_INDEX_CAST_LEVEL_VAL << _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT)
#define _SHR_FABRIC_TH_INDEX_PIPE_LINK_INDICATION       (_SHR_FABRIC_TH_INDEX_PIPE_LINK_VAL << _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT)

/* number of bits + 1, in order to represent (-1). For example we need 2 bits to represent 4 values of priority + 1 bit to represent (-1) which will be all ones  */
/*We also include a buffer space for each parameter of 3 bits for future use*/
#define _SHR_FABRIC_TH_INDEX_BUFFER_SPACE              (3)

#define _SHR_FABRIC_TH_INDEX_PIPE_NOF_BITS             (3 + _SHR_FABRIC_TH_INDEX_BUFFER_SPACE)
#define _SHR_FABRIC_TH_INDEX_LEVEL_NOF_BITS            (3 + _SHR_FABRIC_TH_INDEX_BUFFER_SPACE)
#define _SHR_FABRIC_TH_INDEX_FMC_NOF_BITS              (3 + _SHR_FABRIC_TH_INDEX_BUFFER_SPACE)
#define _SHR_FABRIC_TH_INDEX_SLOW_START_PHASE_NOF_BITS (1 + _SHR_FABRIC_TH_INDEX_BUFFER_SPACE)
#define _SHR_FABRIC_TH_INDEX_PRIO_NOF_BITS             (3 + _SHR_FABRIC_TH_INDEX_BUFFER_SPACE)
#define _SHR_FABRIC_TH_INDEX_CAST_NOF_BITS             (2)
#define _SHR_FABRIC_TH_INDEX_LINK_NOF_BITS             (16)

#define _SHR_FABRIC_TH_INDEX_PRIO_MASK                 ((1<<_SHR_FABRIC_TH_INDEX_PRIO_NOF_BITS) - 1 )
#define _SHR_FABRIC_TH_INDEX_CAST_MASK                 ((1<<_SHR_FABRIC_TH_INDEX_CAST_NOF_BITS) - 1 )
    
#define _BCM_FABRIC_LINK_TH_LR_ONLY                 _SHR_FABRIC_TH_FLAG_LR
#define _BCM_FABRIC_LINK_TH_NLR_ONLY                _SHR_FABRIC_TH_FLAG_NLR
#define _BCM_FABRIC_LINK_TH_FE1_LINKS_ONLY          _SHR_FABRIC_TH_FLAG_FE1_ONLY
#define _BCM_FABRIC_LINK_TH_FE3_LINKS_ONLY          _SHR_FABRIC_TH_FLAG_FE3_ONLY

#define _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_PIPE_MASK     ((1 << _SHR_FABRIC_TH_INDEX_PIPE_NOF_BITS) - 1)
#define _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_LEVEL_MASK    ((1 << _SHR_FABRIC_TH_INDEX_LEVEL_NOF_BITS) - 1)
#define _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_LEVEL_SHIFT   (0)
#define _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_PIPE_SHIFT    (_SHR_FABRIC_TH_INDEX_LEVEL_NOF_BITS)

#define _SHR_FABRIC_TH_INDEX_PIPE_LINK_PIPE_MASK      ((1 << _SHR_FABRIC_TH_INDEX_PIPE_NOF_BITS) - 1)
#define _SHR_FABRIC_TH_INDEX_PIPE_LINK_LINK_MASK      ((1 << _SHR_FABRIC_TH_INDEX_LINK_NOF_BITS) - 1)
#define _SHR_FABRIC_TH_INDEX_PIPE_LINK_LINK_SHIFT     (0)
#define _SHR_FABRIC_TH_INDEX_PIPE_LINK_PIPE_SHIFT     (_SHR_FABRIC_TH_INDEX_LINK_NOF_BITS)

#define _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_FMC_MASK                ((1 << _SHR_FABRIC_TH_INDEX_FMC_NOF_BITS) - 1)
#define _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SLOW_START_PHASE_MASK   ((1 << _SHR_FABRIC_TH_INDEX_SLOW_START_PHASE_NOF_BITS) - 1)
#define _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SLOW_START_PHASE_SHIFT  (0)
#define _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_FMC_SHIFT               (_SHR_FABRIC_TH_INDEX_SLOW_START_PHASE_NOF_BITS)

#define _SHR_FABRIC_TH_INDEX_CAST_PRIO_CAST_MASK    ((1 << _SHR_FABRIC_TH_INDEX_CAST_NOF_BITS) - 1)
#define _SHR_FABRIC_TH_INDEX_CAST_PRIO_PRIO_MASK    ((1 << _SHR_FABRIC_TH_INDEX_PRIO_NOF_BITS) - 1)
#define _SHR_FABRIC_TH_INDEX_CAST_PRIO_PRIO_SHIFT   (0)
#define _SHR_FABRIC_TH_INDEX_CAST_PRIO_CAST_SHIFT   (_SHR_FABRIC_TH_INDEX_PRIO_NOF_BITS)

#define _SHR_FABRIC_TH_INDEX_CAST_LEVEL_CAST_MASK   ((1 << _SHR_FABRIC_TH_INDEX_CAST_NOF_BITS)  - 1)
#define _SHR_FABRIC_TH_INDEX_CAST_LEVEL_LEVEL_MASK  ((1 << _SHR_FABRIC_TH_INDEX_LEVEL_NOF_BITS) - 1)
#define _SHR_FABRIC_TH_INDEX_CAST_LEVEL_CAST_SHIFT  (0)
#define _SHR_FABRIC_TH_INDEX_CAST_LEVEL_LEVEL_SHIFT (_SHR_FABRIC_TH_INDEX_CAST_NOF_BITS)

#define _SHR_FABRIC_TH_INDEX_IS_PIPE_LEVEL(th_index)     \
        (((th_index >> _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT) & _SHR_FABRIC_TH_INDEX_MASK) == \
         _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_VAL)

#define _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_SET(pipe, level) \
        (_SHR_FABRIC_TH_INDEX_PIPE_LEVEL_INDICATION | \
         (((pipe) & _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_PIPE_MASK) << _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_PIPE_SHIFT) | \
         (((level) & _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_LEVEL_MASK) << _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_LEVEL_SHIFT))

#define _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_PIPE_GET(th_index) \
        ((((th_index) >> _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_PIPE_SHIFT) & \
                        _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_PIPE_MASK) == _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_PIPE_MASK ? -1 : \
         (((th_index) >> _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_PIPE_SHIFT) & \
                        _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_PIPE_MASK))

#define _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_LEVEL_GET(th_index) \
        ((((th_index) >> _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_LEVEL_SHIFT) & \
                         _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_LEVEL_MASK) == _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_LEVEL_MASK ? -1 : \
         (((th_index) >> _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_LEVEL_SHIFT) & \
                         _SHR_FABRIC_TH_INDEX_PIPE_LEVEL_LEVEL_MASK))

#define _SHR_FABRIC_TH_INDEX_IS_PIPE_LINK(th_index)     \
        (((th_index >> _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT) & _SHR_FABRIC_TH_INDEX_MASK) == \
         _SHR_FABRIC_TH_INDEX_PIPE_LINK_VAL)

#define _SHR_FABRIC_TH_INDEX_PIPE_LINK_SET(pipe, link) \
        (_SHR_FABRIC_TH_INDEX_PIPE_LINK_INDICATION | \
         (((pipe) & _SHR_FABRIC_TH_INDEX_PIPE_LINK_PIPE_MASK) << _SHR_FABRIC_TH_INDEX_PIPE_LINK_PIPE_SHIFT) | \
         (((link) & _SHR_FABRIC_TH_INDEX_PIPE_LINK_LINK_MASK) << _SHR_FABRIC_TH_INDEX_PIPE_LINK_LINK_SHIFT))

#define _SHR_FABRIC_TH_INDEX_PIPE_LINK_PIPE_GET(th_index) \
        ((((th_index) >> _SHR_FABRIC_TH_INDEX_PIPE_LINK_PIPE_SHIFT) & \
                        _SHR_FABRIC_TH_INDEX_PIPE_LINK_PIPE_MASK) == _SHR_FABRIC_TH_INDEX_PIPE_LINK_PIPE_MASK ? -1 : \
         (((th_index) >> _SHR_FABRIC_TH_INDEX_PIPE_LINK_PIPE_SHIFT) & \
                        _SHR_FABRIC_TH_INDEX_PIPE_LINK_PIPE_MASK))

#define _SHR_FABRIC_TH_INDEX_PIPE_LINK_LINK_GET(th_index) \
        ((((th_index) >> _SHR_FABRIC_TH_INDEX_PIPE_LINK_LINK_SHIFT) & \
                         _SHR_FABRIC_TH_INDEX_PIPE_LINK_LINK_MASK) == _SHR_FABRIC_TH_INDEX_PIPE_LINK_LINK_MASK ? -1 : \
         (((th_index) >> _SHR_FABRIC_TH_INDEX_PIPE_LINK_LINK_SHIFT) & \
                         _SHR_FABRIC_TH_INDEX_PIPE_LINK_LINK_MASK))

#define _SHR_FABRIC_TH_INDEX_IS_FMC_SLOW_START_PHASE(index)     \
        (((index >> _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT) & _SHR_FABRIC_TH_INDEX_MASK) == \
         _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_VAL)

#define _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SET(fmc_shaper, slow_start_phase) \
        (_SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_INDICATION | \
         (((fmc_shaper) & _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_FMC_MASK) << _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_FMC_SHIFT) | \
         (((slow_start_phase) & _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SLOW_START_PHASE_MASK) << _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SLOW_START_PHASE_SHIFT))

#define _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_FMC_GET(index) \
        ((((index) >> _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_FMC_SHIFT) & \
                        _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_FMC_MASK) == _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_FMC_MASK ? -1 : \
         (((index) >> _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_FMC_SHIFT) & \
                        _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_FMC_MASK))

#define _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SLOW_START_PHASE_GET(index) \
        ((((index) >> _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SLOW_START_PHASE_SHIFT) & \
                         _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SLOW_START_PHASE_MASK) == _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SLOW_START_PHASE_MASK ? -1 : \
         (((index) >> _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SLOW_START_PHASE_SHIFT) & \
                         _SHR_FABRIC_TH_INDEX_FMC_SLOW_START_PHASE_SLOW_START_PHASE_MASK))

#define _SHR_FABRIC_TH_INDEX_IS_CAST_PRIO(index)     \
        (((index >> _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT) & _SHR_FABRIC_TH_INDEX_MASK) == \
         _SHR_FABRIC_TH_INDEX_CAST_PRIO_VAL)

#define _SHR_FABRIC_TH_INDEX_CAST_PRIO_SET(cast, prio) \
        (_SHR_FABRIC_TH_INDEX_CAST_PRIO_INDICATION | \
         (((cast) & _SHR_FABRIC_TH_INDEX_CAST_MASK) << _SHR_FABRIC_TH_INDEX_CAST_PRIO_CAST_SHIFT) | \
         (((prio) & _SHR_FABRIC_TH_INDEX_PRIO_MASK) << _SHR_FABRIC_TH_INDEX_CAST_PRIO_PRIO_SHIFT))

#define _SHR_FABRIC_TH_INDEX_CAST_PRIO_CAST_GET(index) \
        ((((index) >> _SHR_FABRIC_TH_INDEX_CAST_PRIO_CAST_SHIFT) & \
                      _SHR_FABRIC_TH_INDEX_CAST_PRIO_CAST_MASK) == _SHR_FABRIC_TH_INDEX_CAST_PRIO_CAST_MASK ? -1 : \
         (((index) >> _SHR_FABRIC_TH_INDEX_CAST_PRIO_CAST_SHIFT) & \
                      _SHR_FABRIC_TH_INDEX_CAST_PRIO_CAST_MASK))

#define _SHR_FABRIC_TH_INDEX_CAST_PRIO_PRIO_GET(index) \
        ((((index) >> _SHR_FABRIC_TH_INDEX_CAST_PRIO_PRIO_SHIFT) & \
                      _SHR_FABRIC_TH_INDEX_CAST_PRIO_PRIO_MASK) == _SHR_FABRIC_TH_INDEX_CAST_PRIO_PRIO_MASK ? -1 : \
         (((index) >> _SHR_FABRIC_TH_INDEX_CAST_PRIO_PRIO_SHIFT) & \
                      _SHR_FABRIC_TH_INDEX_CAST_PRIO_PRIO_MASK))

#define _SHR_FABRIC_TH_INDEX_CAST_LEVEL_SET(cast, level) \
        (_SHR_FABRIC_TH_INDEX_CAST_LEVEL_INDICATION | \
         (((cast)  & _SHR_FABRIC_TH_INDEX_CAST_LEVEL_CAST_MASK)  << _SHR_FABRIC_TH_INDEX_CAST_LEVEL_CAST_SHIFT) | \
         (((level) & _SHR_FABRIC_TH_INDEX_CAST_LEVEL_LEVEL_MASK) << _SHR_FABRIC_TH_INDEX_CAST_LEVEL_LEVEL_SHIFT))

#define _SHR_FABRIC_TH_INDEX_IS_CAST_LEVEL(th_index) \
        (((th_index >> _SHR_FABRIC_TH_INDEX_INDICATION_SHIFT) & _SHR_FABRIC_TH_INDEX_MASK) == \
         _SHR_FABRIC_TH_INDEX_CAST_LEVEL_VAL)

#define _SHR_FABRIC_TH_INDEX_CAST_LEVEL_CAST_GET(th_index) \
        ((((th_index) >> _SHR_FABRIC_TH_INDEX_CAST_LEVEL_CAST_SHIFT) & \
                        _SHR_FABRIC_TH_INDEX_CAST_LEVEL_CAST_MASK) == _SHR_FABRIC_TH_INDEX_CAST_LEVEL_CAST_MASK ? -1 : \
         (((th_index) >> _SHR_FABRIC_TH_INDEX_CAST_LEVEL_CAST_SHIFT) & \
                        _SHR_FABRIC_TH_INDEX_CAST_LEVEL_CAST_MASK))

#define _SHR_FABRIC_TH_INDEX_CAST_LEVEL_LEVEL_GET(th_index) \
        ((((th_index) >> _SHR_FABRIC_TH_INDEX_CAST_LEVEL_LEVEL_SHIFT) & \
                         _SHR_FABRIC_TH_INDEX_CAST_LEVEL_LEVEL_MASK) == _SHR_FABRIC_TH_INDEX_CAST_LEVEL_LEVEL_MASK ? -1 : \
         (((th_index) >> _SHR_FABRIC_TH_INDEX_CAST_LEVEL_LEVEL_SHIFT) & \
                         _SHR_FABRIC_TH_INDEX_CAST_LEVEL_LEVEL_MASK))

#define _SHR_FABRIC_TH_FLAG_SUPPORT_FE1_FE3     (_SHR_FABRIC_TH_FLAG_FE3_ONLY | _SHR_FABRIC_TH_FLAG_FE1_ONLY)
#define _SHR_FABRIC_TH_FLAG_SUPPORT_NLR_LR      (_SHR_FABRIC_TH_FLAG_LR | _SHR_FABRIC_TH_FLAG_NLR)
#define _SHR_FABRIC_TH_FLAG_SUPPORT_ALL         (_SHR_FABRIC_TH_FLAG_SUPPORT_NLR_LR | _SHR_FABRIC_TH_FLAG_SUPPORT_FE1_FE3)

/* Bitmap of possible validity checks for each threshold*/
#define _SHR_FABRIC_CGM_VALIDITY_NONE                     0x0
#define _SHR_FABRIC_CGM_VALIDITY_NOT_PROFILE_DEPENDENT    0x1 /* Such thresholds cannot receive for a profile_id value different than 0*/
#define _SHR_FABRIC_CGM_VALIDITY_ONLY_TWO_PIPES           0x2 /* Such thresholds cannot receive for a pipe value different than 0 or 1*/
#define _SHR_FABRIC_CGM_VALIDITY_MODULO_4                 0x4 /* Such thresholds should receive values that don't have a remainder after devision by 4*/
#define _SHR_FABRIC_CGM_DISABLE_NOT_SUPPORTED             0x8 /* Such thresholds should not receive values of -1*/

/* DNXF types of CGM threshold indexes*/
typedef enum _shr_dnxf_cgm_index_type_e {
    _shr_dnxf_cgm_index_type_cast_prio,
    _shr_dnxf_cgm_index_type_priority,
    _shr_dnxf_cgm_index_type_pipe,
    _shr_dnxf_cgm_index_type_pipe_level,
    _shr_dnxf_cgm_index_type_pipe_link,
    _shr_dnxf_cgm_index_type_nof
} _shr_dnxf_cgm_index_type_t;

/* Fabric threshold ID */
typedef uint32 _shr_dnxf_threshold_id_t;

/* fabric_threshold_type */
typedef enum _shr_dnxf_threshold_type_e {
    _SHR_FABRIC_MID_TAG_DROP_CLASS_TH = 0,     /* INGRESS ADMISSION THRESHOLDS */
    _SHR_FABRIC_TX_LINK_LOAD_DROP_PIPE_TH = 1,
    _SHR_FABRIC_TX_FRAG_GUARANTEED_PIPE_TH = 2,
    _SHR_FABRIC_SHARED_DROP_CLASS_TH = 3,
    _SHR_FABRIC_SHARED_MC_COPIES_DROP_PRIO_TH = 4,
    _SHR_FABRIC_MID_FRAG_DROP_CLASS_TH = 5,
    _SHR_FABRIC_SHARED_BANK_MC_DROP_PRIO_TH = 6, /* DTL ADMISSION THRESHOLDS */
    _SHR_FABRIC_TX_TAG_DROP_CLASS_TH = 7,
    _SHR_FABRIC_TX_FRAG_DROP_CLASS_TH = 8,
    _SHR_FABRIC_TX_TAG_GCI_PIPE_TH = 9,      /* GCI GENERATION */
    _SHR_FABRIC_TX_FRAG_GCI_PIPE_TH = 10, 
    _SHR_FABRIC_MID_TAG_GCI_PIPE_TH = 11,
    _SHR_FABRIC_MID_FRAG_GCI_PIPE_TH = 12,
    _SHR_FABRIC_SHARED_GCI_PIPE_TH = 13,
    _SHR_FABRIC_SHARED_FRAG_COPIES_GCI_PIPE_TH = 14,
    _SHR_FABRIC_TX_FRAG_GUARANTEED_RCI_PIPE_TH = 15, /* RCI GENERATION */
    _SHR_FABRIC_TX_LINK_LOAD_RCI_PIPE_TH = 16,
    _SHR_FABRIC_TX_TAG_RCI_PIPE_TH = 17,
    _SHR_FABRIC_TX_FRAG_RCI_PIPE_TH = 18,
    _SHR_FABRIC_MID_TAG_RCI_PIPE_TH = 19,
    _SHR_FABRIC_MID_FRAG_RCI_PIPE_TH = 20,
    _SHR_FABRIC_SHARED_RCI_PIPE_TH = 21,
    _SHR_FABRIC_MID_MC_COPIES_FC_PRIO_TH = 22,  /* FC GENERATION */
    _SHR_FABRIC_MID_TAG_FC_PIPE_TH = 23,
    _SHR_FABRIC_MID_FRAG_FC_PIPE_TH = 24,
    _SHR_FABRIC_SHARED_FC_PIPE_TH = 25,
    _SHR_FABRIC_TX_TAG_FC_PIPE_TH = 26,
    _SHR_FABRIC_TX_FRAG_FC_PIPE_TH = 27,
    _SHR_FABRIC_MID_MASK_FC_PIPE_TH = 28,
    _SHR_FABRIC_TX_FE1_BYPASS_LLFCFC_PIPE_TH = 29,
    _SHR_FABRIC_RX_FRAG_DROP_PIPE_TH = 30,     /* DCH LEGACY THRESHOLDS */
    _SHR_FABRIC_RX_MC_LOW_PRIO_DROP_PIPE_TH = 31,
    _SHR_FABRIC_RX_FRAG_GCI_PIPE_TH = 32,
    _SHR_FABRIC_RX_LLFCFC_PIPE_TH = 33,
    _SHR_FABRIC_RX_WFQ_DYNAMIC_WEIGHT_PIPE_TH = 34, /* Dynamic weights*/
    _SHR_FABRIC_MID_WFQ_DYNAMIC_WEIGHT_PIPE_TH = 35,
    _SHR_FABRIC_TX_WFQ_DYNAMIC_WEIGHT_PIPE_TH = 36,
    _SHR_FABRIC_THRESHOLDS_COUNT = 37 /*This value should always be last*/
} _shr_dnxf_threshold_type_t;

#define _SHR_FABRIC_PIPE_ALL (-1)

/* Fabric cell header field types exposed to customer*/
typedef enum _shr_dnxc_fabric_cell_header_field_type_e {
    _shr_dnxc_fabric_cell_header_field_type_source_device = 0,
    _shr_dnxc_fabric_cell_header_field_type_fip_link,
    _shr_dnxc_fabric_cell_header_field_type_pipe,
    _shr_dnxc_fabric_cell_header_field_type_nof
} _shr_dnxc_fabric_cell_header_field_type_t;

#define _SHR_FABRIC_CELL_RX_HEADER_PREPEND            0x01


/* Fabric stat index macros */
#define _SHR_FABRIC_STAT_INDEX_MASK                             (0xF)
#define _SHR_FABRIC_STAT_INDEX_VAL                              (0x1)
#define _SHR_FABRIC_STAT_INDEX_DEVICE_INDICATION_SHIFT          (24)
#define _SHR_FABRIC_STAT_INDEX_DEVICE_INDICATION                (_SHR_FABRIC_STAT_INDEX_VAL << _SHR_FABRIC_STAT_INDEX_DEVICE_INDICATION_SHIFT)
#define _SHR_FABRIC_STAT_INDEX_LINK_INDICATION_SHIFT            (25)
#define _SHR_FABRIC_STAT_INDEX_LINK_INDICATION                  (_SHR_FABRIC_STAT_INDEX_VAL << _SHR_FABRIC_STAT_INDEX_LINK_INDICATION_SHIFT)
#define _SHR_FABRIC_STAT_INDEX_LINK_PIPE_INDICATION_SHIFT       (26)
#define _SHR_FABRIC_STAT_INDEX_LINK_PIPE_INDICATION             (_SHR_FABRIC_STAT_INDEX_VAL << _SHR_FABRIC_STAT_INDEX_LINK_PIPE_INDICATION_SHIFT)

#define _SHR_FABRIC_STAT_INDEX_BUFFER_SPACE                     (3)
#define _SHR_FABRIC_STAT_INDEX_LINK_NOF_BITS                    (10 + _SHR_FABRIC_STAT_INDEX_BUFFER_SPACE)
#define _SHR_FABRIC_STAT_INDEX_LINK_MASK                        ((1<<_SHR_FABRIC_STAT_INDEX_LINK_NOF_BITS) - 1)
#define _SHR_FABRIC_STAT_INDEX_PIPE_NOF_BITS                    (2 + _SHR_FABRIC_STAT_INDEX_BUFFER_SPACE)
#define _SHR_FABRIC_STAT_INDEX_PIPE_MASK                        ((1<<_SHR_FABRIC_STAT_INDEX_PIPE_NOF_BITS) - 1)
#define _SHR_FABRIC_STAT_INDEX_LINK_SHIFT                       (0)
#define _SHR_FABRIC_STAT_INDEX_PIPE_SHIFT                       (_SHR_FABRIC_STAT_INDEX_LINK_NOF_BITS)

/* Set index type */
#define _SHR_FABRIC_STAT_INDEX_DEVICE_SET()                     (_SHR_FABRIC_STAT_INDEX_DEVICE_INDICATION)

#define _SHR_FABRIC_STAT_INDEX_LINK_SET(link)     \
        (_SHR_FABRIC_STAT_INDEX_LINK_INDICATION | \
        (((link) & _SHR_FABRIC_STAT_INDEX_LINK_MASK) << _SHR_FABRIC_STAT_INDEX_LINK_SHIFT))

#define _SHR_FABRIC_STAT_INDEX_LINK_PIPE_SET(link,pipe) \
        (_SHR_FABRIC_STAT_INDEX_LINK_PIPE_INDICATION | \
        (((pipe) & _SHR_FABRIC_STAT_INDEX_PIPE_MASK) << _SHR_FABRIC_STAT_INDEX_PIPE_SHIFT) | \
        (((link) & _SHR_FABRIC_STAT_INDEX_LINK_MASK) << _SHR_FABRIC_STAT_INDEX_LINK_SHIFT))


/* Check index type */
#define _SHR_FABRIC_STAT_INDEX_IS_DEVICE(stat_index)    \
        (((stat_index >> _SHR_FABRIC_STAT_INDEX_DEVICE_INDICATION_SHIFT) & _SHR_FABRIC_STAT_INDEX_MASK) == \
            _SHR_FABRIC_STAT_INDEX_VAL)

#define _SHR_FABRIC_STAT_INDEX_IS_LINK(stat_index)    \
        (((stat_index >> _SHR_FABRIC_STAT_INDEX_LINK_INDICATION_SHIFT) & _SHR_FABRIC_STAT_INDEX_MASK) == \
            _SHR_FABRIC_STAT_INDEX_VAL)

#define _SHR_FABRIC_STAT_INDEX_IS_LINK_PIPE(stat_index)    \
        (((stat_index >> _SHR_FABRIC_STAT_INDEX_LINK_PIPE_INDICATION_SHIFT) & _SHR_FABRIC_STAT_INDEX_MASK) == \
            _SHR_FABRIC_STAT_INDEX_VAL)

/* Get index arguments*/
#define _SHR_FABRIC_STAT_INDEX_LINK_GET(stat_index)    \
        (((stat_index) >> _SHR_FABRIC_STAT_INDEX_LINK_SHIFT) & _SHR_FABRIC_STAT_INDEX_LINK_MASK)

#define _SHR_FABRIC_STAT_INDEX_PIPE_GET(stat_index)    \
        (((stat_index) >> _SHR_FABRIC_STAT_INDEX_PIPE_SHIFT) & _SHR_FABRIC_STAT_INDEX_PIPE_MASK)

typedef enum _shr_fabric_device_type_e {
    _SHR_FABRIC_DEVICE_TYPE_UNKNOWN = 0, /* Unknown device type */
    _SHR_FABRIC_DEVICE_TYPE_FE13 = 1,    /* FE13 device type */
    _SHR_FABRIC_DEVICE_TYPE_FE2 = 2,     /* FE2 device type */
    _SHR_FABRIC_DEVICE_TYPE_FAP = 3,     /* FAP device type */
    _SHR_FABRIC_DEVICE_TYPE_FE1 = 4,     /* FE1 device type */
    _SHR_FABRIC_DEVICE_TYPE_FE3 = 5,     /* FE3 device type */
    _SHR_FABRIC_DEVICE_TYPE_FIP = 6,     /* FIP device type */
    _SHR_FABRIC_DEVICE_TYPE_FOP = 7,     /* FOP device type */
    _SHR_FABRIC_DEVICE_TYPE_NOF = 8      /* Should be last */
} _shr_fabric_device_type_t;

#endif  /* !_SHR_FABRIC_H */

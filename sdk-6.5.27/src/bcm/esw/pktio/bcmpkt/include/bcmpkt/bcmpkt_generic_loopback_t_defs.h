#ifndef BCMPKT_GIH_DEFS_H
#define BCMPKT_GIH_DEFS_H
/*****************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by xfc_map_parser
 * from the NPL output file(s) header.yml.
 * Edits to this file will be lost when it is regenerated.
 *
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 * All Rights Reserved.$
 *
 * Tool Path: $SDK/INTERNAL/fltg/xfc_map_parser
 *
 ****************************************************************/

/*!
 * \name GIH field IDs.
 * \anchor BCMPKT_GIH_XXX
 */
#define BCMPKT_GIH_INPUT_PRIORITY     0
#define BCMPKT_GIH_RESERVED_1         1
#define BCMPKT_GIH_RESERVED_0         2
#define BCMPKT_GIH_INTERFACE_OBJ      3
#define BCMPKT_GIH_PROCESSING_CTRL_1  4
#define BCMPKT_GIH_PROCESSING_CTRL_0  5
#define BCMPKT_GIH_DESTINATION_OBJ    6
#define BCMPKT_GIH_SOURCE_SYSTEM_PORT 7
#define BCMPKT_GIH_HEADER_TYPE        8
#define BCMPKT_GIH_INTERFACE_CTRL     9
#define BCMPKT_GIH_FLAGS              10
#define BCMPKT_GIH_ENTROPY_OBJ        11
#define BCMPKT_GIH_DESTINATION_TYPE   12
#define BCMPKT_GIH_RESERVED_2         13
#define BCMPKT_GIH_QOS_OBJ            14

#define BCMPKT_GIH_FID_INVALID        -1
#define BCMPKT_GIH_FID_COUNT          15
#define BCMPKT_GIH_FID_START          0
#define BCMPKT_GIH_FID_END            (BCMPKT_GIH_FID_COUNT - 1)

#define BCMPKT_GIH_I_SUPPORT          0
#define BCMPKT_GIH_I_FID_COUNT        1

#define BCMPKT_GIH_FIELD_NAME_MAP_INIT \
    {"INPUT_PRIORITY", BCMPKT_GIH_INPUT_PRIORITY},\
    {"RESERVED_1", BCMPKT_GIH_RESERVED_1},\
    {"RESERVED_0", BCMPKT_GIH_RESERVED_0},\
    {"INTERFACE_OBJ", BCMPKT_GIH_INTERFACE_OBJ},\
    {"PROCESSING_CTRL_1", BCMPKT_GIH_PROCESSING_CTRL_1},\
    {"PROCESSING_CTRL_0", BCMPKT_GIH_PROCESSING_CTRL_0},\
    {"DESTINATION_OBJ", BCMPKT_GIH_DESTINATION_OBJ},\
    {"SOURCE_SYSTEM_PORT", BCMPKT_GIH_SOURCE_SYSTEM_PORT},\
    {"HEADER_TYPE", BCMPKT_GIH_HEADER_TYPE},\
    {"INTERFACE_CTRL", BCMPKT_GIH_INTERFACE_CTRL},\
    {"FLAGS", BCMPKT_GIH_FLAGS},\
    {"ENTROPY_OBJ", BCMPKT_GIH_ENTROPY_OBJ},\
    {"DESTINATION_TYPE", BCMPKT_GIH_DESTINATION_TYPE},\
    {"RESERVED_2", BCMPKT_GIH_RESERVED_2},\
    {"QOS_OBJ", BCMPKT_GIH_QOS_OBJ},\
    {"gih fid count", BCMPKT_GIH_FID_COUNT}

#define BCMPKT_GIH_LOOPBACK_HEADER_TYPE__TUNNEL  0
#define BCMPKT_GIH_LOOPBACK_HEADER_TYPE__GENERIC 1
#define BCMPKT_GIH_DESTINATION_TYPE__NO_OP       0
#define BCMPKT_GIH_DESTINATION_TYPE__L2_OIF      1
#define BCMPKT_GIH_DESTINATION_TYPE__RESERVED    2
#define BCMPKT_GIH_DESTINATION_TYPE__VP          3
#define BCMPKT_GIH_DESTINATION_TYPE__ECMP        4
#define BCMPKT_GIH_DESTINATION_TYPE__NHOP        5
#define BCMPKT_GIH_DESTINATION_TYPE__L2MC_GROUP  6
#define BCMPKT_GIH_DESTINATION_TYPE__L3MC_GROUP  7
#define BCMPKT_GIH_DESTINATION_TYPE__RESERVED_1  8
#define BCMPKT_GIH_DESTINATION_TYPE__ECMP_MEMBER 9
#define BCMPKT_GIH_LOOPBACK_HEADER_INTERFACE_CTRL__NOOP   0
#define BCMPKT_GIH_LOOPBACK_HEADER_INTERFACE_CTRL__VFI    1
#define BCMPKT_GIH_LOOPBACK_HEADER_INTERFACE_CTRL__L3_IIF 2
#endif /* BCMPKT_GIH_DEFS_H */

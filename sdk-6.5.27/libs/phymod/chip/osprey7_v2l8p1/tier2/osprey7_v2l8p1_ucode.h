/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 * All Rights Reserved.$
 */
#ifndef osprey7_v2l8p1_ucode_H_
#define osprey7_v2l8p1_ucode_H_ 

#include <phymod/phymod.h>


#define OSPREY7_V2L8P1_UCODE_IMAGE_VERSION "D003_02"  /* matches the version number from microcode */
#define OSPREY7_V2L8P1_UCODE_IMAGE_SIZE    150112
#define OSPREY7_V2L8P1_UCODE_STACK_SIZE    0x13F2
#define OSPREY7_V2L8P1_UCODE_IMAGE_CRC     0xDDB1
#define OSPREY7_V2L8P1_UCODE_DR_SIZE       0x0

extern unsigned char*  osprey7_v2l8p1_ucode_get(void);


#endif


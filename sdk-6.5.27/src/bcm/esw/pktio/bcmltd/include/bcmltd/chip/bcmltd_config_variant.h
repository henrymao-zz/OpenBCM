/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from Logical Table mapping files.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 ******************************************************************************/

#ifndef BCMLTD_CHIP_CONFIG_VARIANT_H
#define BCMLTD_CHIP_CONFIG_VARIANT_H

#ifndef DOXYGEN_IGNORE_AUTOGEN

#include <bcmdrd_config.h>

/* This determines whether a variant is included or excluded by default */
#ifndef BCMLTD_CONFIG_INCLUDE_VARIANT_DEFAULT
#define BCMLTD_CONFIG_INCLUDE_VARIANT_DEFAULT 1
#endif

#if BCMDRD_CONFIG_INCLUDE_BCM56980_A0
#ifndef BCMLTD_CONFIG_INCLUDE_BCM56980_A0_BASE
#define BCMLTD_CONFIG_INCLUDE_BCM56980_A0_BASE BCMLTD_CONFIG_INCLUDE_VARIANT_DEFAULT
#endif
#else
#define BCMLTD_CONFIG_INCLUDE_BCM56980_A0_BASE 0
#endif

#endif /* DOXYGEN_IGNORE_AUTOGEN */

#endif /* BCMLTD_CHIP_CONFIG_VARIANT_H */

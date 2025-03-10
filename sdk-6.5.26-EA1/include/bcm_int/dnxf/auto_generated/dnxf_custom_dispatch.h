/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * File:        dnxf_custom_dispatch.h
 * Purpose:     dnxf custom driver BCM API dispatch table
 * Generator:   modules_dispatch.py
 */

#ifndef _BCM_INT_DNXF_CUSTOM_DISPATCH_H
#define _BCM_INT_DNXF_CUSTOM_DISPATCH_H

#include <bcm/types.h>
#include <bcm_int/dispatch.h>

#ifdef BCM_DNXF_SUPPORT

extern int bcm_common_custom_register(int,bcm_custom_cb_t,void *);
extern int bcm_common_custom_unregister(int);
extern int bcm_common_custom_port_get(int,bcm_port_t,int,int,uint32 *,int *);
extern int bcm_common_custom_port_set(int,bcm_port_t,int,int,uint32 *);

#endif /* BCM_DNXF_SUPPORT */
#endif /* !_BCM_INT_DNXF_CUSTOM_DISPATCH_H */

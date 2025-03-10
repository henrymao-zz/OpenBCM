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
 * File:        dnx_twamp_dispatch.h
 * Purpose:     dnx twamp driver BCM API dispatch table
 * Generator:   modules_dispatch.py
 */

#ifndef _BCM_INT_DNX_TWAMP_DISPATCH_H
#define _BCM_INT_DNX_TWAMP_DISPATCH_H

#include <bcm/types.h>
#include <bcm_int/dispatch.h>

#ifdef BCM_DNX_SUPPORT

extern int bcm_dnx_twamp_sender_traverse(int,uint32,bcm_twamp_sender_traverse_cb,void *);
extern int bcm_dnx_twamp_sender_loss_get(int,bcm_twamp_sender_t,bcm_twamp_sender_lm_statistics_t *);
extern int bcm_dnx_twamp_sender_create(int,bcm_twamp_sender_info_t *);
extern int bcm_dnx_twamp_sender_get(int,bcm_twamp_sender_t,bcm_twamp_sender_info_t *);
extern int bcm_dnx_twamp_sender_delay_get(int,bcm_twamp_sender_t,bcm_twamp_sender_dm_statistics_t *);
extern int bcm_dnx_twamp_sender_destroy(int,bcm_twamp_sender_t);

#endif /* BCM_DNX_SUPPORT */
#endif /* !_BCM_INT_DNX_TWAMP_DISPATCH_H */

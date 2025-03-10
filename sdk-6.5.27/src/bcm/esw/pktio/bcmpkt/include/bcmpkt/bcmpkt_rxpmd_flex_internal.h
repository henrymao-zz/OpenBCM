/*! \file bcmpkt_rxpmd_flex_internal.h
 *
 * RX Packet Flex MetaData internal library.
 *
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef BCMPKT_RXPMD_FLEX_INTERNAL_H
#define BCMPKT_RXPMD_FLEX_INTERNAL_H

#ifdef PKTIO_IMPL
#include <pktio_dep.h>
#else
#include <shr/shr_types.h>
#endif
#include <bcmlrd/bcmlrd_conf.h>
#include <bcmpkt/bcmpkt_rxpmd_flex_defs.h>
#include <bcmpkt/bcmpkt_internal.h>

/*!
 * Array of RXPMD_FLEX field get functions for a particular device
 * type.
 */
typedef struct bcmpkt_rxpmd_flex_fget_s {
    /*! Array of flex field get functions. */
    bcmpkt_flex_field_get_f fget[BCMPKT_RXPMD_FLEX_FID_COUNT];
} bcmpkt_rxpmd_flex_fget_t;

/*!
 * Array of RXPMD_FLEX field set functions for a particular device
 * type. These functions are used for internally configuring packet
 * filter.
 */
typedef struct bcmpkt_rxpmd_flex_fset_s {
    /*! Array of flex field set functions. */
    bcmpkt_flex_field_set_f fset[BCMPKT_RXPMD_FLEX_FID_COUNT];
} bcmpkt_rxpmd_flex_fset_t;

/*!
 * Array of RXPMD_FLEX field address and length get functions for a multiple
 * words field of a particular device type.
 */
typedef struct bcmpkt_rxpmd_flex_figet_s {
    /*! Array of field get functions */
    bcmpkt_ifield_get_f fget[BCMPKT_RXPMD_FLEX_FID_COUNT];
} bcmpkt_rxpmd_flex_figet_t;

/*! \cond  Externs for the required functions. */
#define BCMLRD_VARIANT_ENTRY(_bd,_bu,_va,_ve,_vu,_vv,_vo,_vd,_r0,_r1) \
    extern void _bd##_vu##_va##_rxpmd_flex_reason_decode(const uint32_t* data, bcmpkt_rxpmd_flex_reasons_t* reasons);
#define BCMDRD_DEVLIST_OVERRIDE
#include <bcmlrd/chip/bcmlrd_variant.h>

#define BCMLRD_VARIANT_ENTRY(_bd,_bu,_va,_ve,_vu,_vv,_vo,_vd,_r0,_r1) \
    extern void _bd##_vu##_va##_rxpmd_flex_reason_encode(const bcmpkt_rxpmd_flex_reasons_t* reasons, uint32_t* data);
#define BCMDRD_DEVLIST_OVERRIDE
#include <bcmlrd/chip/bcmlrd_variant.h>

#define BCMLRD_VARIANT_ENTRY(_bd,_bu,_va,_ve,_vu,_vv,_vo,_vd,_r0,_r1) \
    extern void _bd##_vu##_va##_rxpmd_flex_view_info_get(bcmpkt_pmd_view_info_t *info);
#define BCMDRD_DEVLIST_OVERRIDE
#include <bcmlrd/chip/bcmlrd_variant.h>
/*! \endcond */

#endif /* BCMPKT_RXPMD_FLEX_INTERNAL_H */

/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * File:        cm.c
 * Purpose:     Configuration Manager
 *
 * This module provides an OS-independent abstraction for the low-level
 * manipulation of StrataSwitch devices and other system resources
 * needed by the driver.
 *
 * See <soc/cmtypes.h> for a description and requirements of the vectors.
 */
#include <shared/bsl.h>

#include <assert.h>
#include <sal/core/libc.h>
#include <sal/core/spl.h>
#include <sal/core/sync.h>
#include <soc/devids.h>
#include <soc/cmext.h>
#include <soc/cm.h>
#ifdef BCM_FIRELIGHT_SUPPORT
#include <soc/bondoptions.h>
#endif

#include <soc/drv.h>
#if defined(INCLUDE_CPU_I2C) && (defined(__DUNE_GTO_BCM_CPU__) || defined(__DUNE_WRX_BCM_CPU__) || defined(__DUNE_SLK_BCM_CPU__) || defined(__DUNE_GTS_BCM_CPU__))
#include <soc/i2c.h>
#endif
#ifdef BCM_DNX_SUPPORT
#include <soc/dnx/drv.h>
#endif
#ifdef BCM_DNXF_SUPPORT
#include <soc/dnxf/cmn/dnxf_drv.h>
#endif
#if defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)
#include <soc/dnxc/drv.h>
#endif
#if defined (BCM_PETRA_SUPPORT)
#include <soc/dpp/drv.h>
#endif
#ifdef BCM_DFE_SUPPORT
#include <soc/dfe/cmn/dfe_drv.h>
#endif
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
#include <soc/ltsw/drv.h>
#include <soc/ltsw/config.h>
#include <soc/ltsw/ha.h>
#include <soc/ltsw/issu.h>
#endif

#include <sal/core/memlog.h>

#if defined(BCM_ESW_SUPPORT) || defined(BCM_SAND_SUPPORT)
#define IHOST_S0_ADDR_START 0x19000000
#define IHOST_S0_ADDR_END  0x1901FFFF
#define IHOST_ACP_ADDR_START 0x19020000
#define IHOST_ACP_ADDR_END  0x19022FFF

#define IS_IHOST_S0_ADDR(addr) ((addr >= IHOST_S0_ADDR_START) && (addr <= IHOST_S0_ADDR_END))
#define IS_IHOST_ACP_ADDR(addr) ((addr >= IHOST_ACP_ADDR_START) && (addr <= IHOST_ACP_ADDR_END))
#endif

/* array of CM devices indexed by unit=logical device number=CM device handle */
cm_device_t                     soc_cm_device[SOC_MAX_NUM_DEVICES];
int                             soc_cm_device_count = 0;
/* number of composite devices */
unsigned                        soc_cm_nof_composite_devices = 0;
/* number of destroyed composite devices */
unsigned                        soc_cm_nof_destroyed_composite_devices = 0;
/* array of composite devices */
soc_cm_composite_dev_t          cm_composite_devices[SOC_MAX_NOF_COMPOSITE_DEVS];
/* indices of destroyed composite devices in cm_composite_devices */
unsigned                        cm_destroyed_composite_devices[SOC_MAX_NOF_COMPOSITE_DEVS];
/* Array mapping from BDE device ID (array index) to unit=logical device ids.
 * The mapping in the other direction is done using CMDEV(u).dev.dev
 * For any used unit u, and its BDE device d, we should have:
 * CMDEV(u).dev.dev == d && cm_bde_dev2unit[d] == u
 */
static int                      cm_bde_dev2unit[SOC_MAX_NUM_DEVICES];

/*
 * Table of all recognized chip IDs.
 *
 * There are fewer drivers than real chip IDs because some drivers
 * support more than one chip.  This table maps each real chip ID onto a
 * driver chip ID.  The driver IDs can be zero if equal to real IDs.
 *
 * Entries may be added to the table via soc_cm_id_to_driver_id_add().
 */

static soc_cm_device_info_t soc_device_info[] = {

#if defined(BCM_HERCULES15_SUPPORT)
    {   /* Hercules 1.5 with 8 ports */
        BCM5675_DEVICE_ID, BCM5675_A0_REV_ID,
        "BCM5675_A0",
        BCM5675_DEVICE_ID, BCM5675_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hercules 1.5 with 4 ports */
        BCM5676_DEVICE_ID, BCM5676_A0_REV_ID,
        "BCM5676_A0",
        BCM5675_DEVICE_ID, BCM5675_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hercules 1.5 with 8 ports */
        BCM5675_DEVICE_ID, BCM5675_A1_REV_ID,
        "BCM5675_A1",
        BCM5675_DEVICE_ID, BCM5675_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hercules 1.5 with 4 ports */
        BCM5676_DEVICE_ID, BCM5676_A1_REV_ID,
        "BCM5676_A1",
        BCM5675_DEVICE_ID, BCM5675_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_HERCULES15_SUPPORT */
#if defined(BCM_FIREBOLT_SUPPORT)
    {   /* Helix */
        BCM56300_DEVICE_ID, BCM56300_A0_REV_ID,
        "BCM56300_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56301_DEVICE_ID, BCM56301_A0_REV_ID,
        "BCM56301_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56302_DEVICE_ID, BCM56302_A0_REV_ID,
        "BCM56302_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56303_DEVICE_ID, BCM56303_A0_REV_ID,
        "BCM56303_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#if defined(BCM_HELIX1_SUPPORT)
    {   /* Helix */
        BCM56304_DEVICE_ID, BCM56304_A0_REV_ID,
        "BCM56304_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
    {   /* Helix */
        BCM56305_DEVICE_ID, BCM56305_A0_REV_ID,
        "BCM56305_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56306_DEVICE_ID, BCM56306_A0_REV_ID,
        "BCM56306_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56307_DEVICE_ID, BCM56307_A0_REV_ID,
        "BCM56307_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56308_DEVICE_ID, BCM56308_A0_REV_ID,
        "BCM56308_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56309_DEVICE_ID, BCM56309_A0_REV_ID,
        "BCM56309_A0",
        BCM56504_DEVICE_ID, BCM56503_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56300_DEVICE_ID, BCM56300_A1_REV_ID,
        "BCM56300_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56301_DEVICE_ID, BCM56301_A1_REV_ID,
        "BCM56301_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56302_DEVICE_ID, BCM56302_A1_REV_ID,
        "BCM56302_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56303_DEVICE_ID, BCM56303_A1_REV_ID,
        "BCM56303_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#if defined(BCM_HELIX1_SUPPORT)
    {   /* Helix */
        BCM56304_DEVICE_ID, BCM56304_A1_REV_ID,
        "BCM56304_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
    {   /* Helix */
        BCM56305_DEVICE_ID, BCM56305_A1_REV_ID,
        "BCM56305_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56306_DEVICE_ID, BCM56306_A1_REV_ID,
        "BCM56306_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56307_DEVICE_ID, BCM56307_A1_REV_ID,
        "BCM56307_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56308_DEVICE_ID, BCM56308_A1_REV_ID,
        "BCM56308_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56309_DEVICE_ID, BCM56309_A1_REV_ID,
        "BCM56309_A1",
        BCM56504_DEVICE_ID, BCM56503_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#if defined(BCM_FELIX1_SUPPORT)
    {   /* Felix */
        BCM56100_DEVICE_ID, BCM56100_A0_REV_ID,
        "BCM56100_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56101_DEVICE_ID, BCM56101_A0_REV_ID,
        "BCM56101_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        "BCM56102_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56105_DEVICE_ID, BCM56105_A0_REV_ID,
        "BCM56105_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56106_DEVICE_ID, BCM56106_A0_REV_ID,
        "BCM56106_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56107_DEVICE_ID, BCM56107_A0_REV_ID,
        "BCM56107_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56100_DEVICE_ID, BCM56100_A1_REV_ID,
        "BCM56100_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56101_DEVICE_ID, BCM56101_A1_REV_ID,
        "BCM56101_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56102_DEVICE_ID, BCM56102_A1_REV_ID,
        "BCM56102_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56105_DEVICE_ID, BCM56105_A1_REV_ID,
        "BCM56105_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56106_DEVICE_ID, BCM56106_A1_REV_ID,
        "BCM56106_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56107_DEVICE_ID, BCM56107_A1_REV_ID,
        "BCM56107_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_FELIX15_SUPPORT)
    {   /* Felix15 */
        BCM56110_DEVICE_ID, BCM56110_A0_REV_ID,
        "BCM56110_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56111_DEVICE_ID, BCM56111_A0_REV_ID,
        "BCM56111_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        "BCM56112_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56115_DEVICE_ID, BCM56115_A0_REV_ID,
        "BCM56115_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56116_DEVICE_ID, BCM56116_A0_REV_ID,
        "BCM56116_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56117_DEVICE_ID, BCM56117_A0_REV_ID,
        "BCM56117_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_FELIX15_SUPPORT */
#if defined(BCM_HELIX1_SUPPORT)
    {
        BCM53300_DEVICE_ID, BCM53300_A0_REV_ID,
        "BCM53300_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM53301_DEVICE_ID, BCM53301_A0_REV_ID,
        "BCM53301_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM53302_DEVICE_ID, BCM53302_A0_REV_ID,
        "BCM53302_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM53300_DEVICE_ID, BCM53300_A1_REV_ID,
        "BCM53300_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM53301_DEVICE_ID, BCM53301_A1_REV_ID,
        "BCM53301_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM53302_DEVICE_ID, BCM53302_A1_REV_ID,
        "BCM53302_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56300_DEVICE_ID, BCM56300_B0_REV_ID,
        "BCM56300_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56301_DEVICE_ID, BCM56301_B0_REV_ID,
        "BCM56301_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56302_DEVICE_ID, BCM56302_B0_REV_ID,
        "BCM56302_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56303_DEVICE_ID, BCM56303_B0_REV_ID,
        "BCM56303_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        "BCM56304_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56305_DEVICE_ID, BCM56305_B0_REV_ID,
        "BCM56305_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56306_DEVICE_ID, BCM56306_B0_REV_ID,
        "BCM56306_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56307_DEVICE_ID, BCM56307_B0_REV_ID,
        "BCM56307_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56308_DEVICE_ID, BCM56308_B0_REV_ID,
        "BCM56308_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56309_DEVICE_ID, BCM56309_B0_REV_ID,
        "BCM56309_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56300_DEVICE_ID, BCM56300_B1_REV_ID,
        "BCM56300_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56301_DEVICE_ID, BCM56301_B1_REV_ID,
        "BCM56301_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56302_DEVICE_ID, BCM56302_B1_REV_ID,
        "BCM56302_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56303_DEVICE_ID, BCM56303_B1_REV_ID,
        "BCM56303_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56304_DEVICE_ID, BCM56304_B1_REV_ID,
        "BCM56304_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56305_DEVICE_ID, BCM56305_B1_REV_ID,
        "BCM56305_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56306_DEVICE_ID, BCM56306_B1_REV_ID,
        "BCM56306_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56307_DEVICE_ID, BCM56307_B1_REV_ID,
        "BCM56307_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56308_DEVICE_ID, BCM56308_B1_REV_ID,
        "BCM56308_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56309_DEVICE_ID, BCM56309_B1_REV_ID,
        "BCM56309_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
    {   /* Helix15 */
        BCM56310_DEVICE_ID, BCM56310_A0_REV_ID,
        "BCM56310_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56311_DEVICE_ID, BCM56311_A0_REV_ID,
        "BCM56311_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56312_DEVICE_ID, BCM56312_A0_REV_ID,
        "BCM56312_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56313_DEVICE_ID, BCM56313_A0_REV_ID,
        "BCM56313_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        "BCM56314_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56315_DEVICE_ID, BCM56315_A0_REV_ID,
        "BCM56315_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56316_DEVICE_ID, BCM56316_A0_REV_ID,
        "BCM56316_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56317_DEVICE_ID, BCM56317_A0_REV_ID,
        "BCM56317_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56318_DEVICE_ID, BCM56318_A0_REV_ID,
        "BCM56318_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56319_DEVICE_ID, BCM56319_A0_REV_ID,
        "BCM56319_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-Helix */
        BCM56404_DEVICE_ID, BCM56404_A0_REV_ID,
        "BCM56304_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56500_DEVICE_ID, BCM56500_A0_REV_ID,
        "BCM56500_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56501_DEVICE_ID, BCM56501_A0_REV_ID,
        "BCM56501_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56502_DEVICE_ID, BCM56502_A0_REV_ID,
        "BCM56502_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56503_DEVICE_ID, BCM56503_A0_REV_ID,
        "BCM56503_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        "BCM56504_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56505_DEVICE_ID, BCM56505_A0_REV_ID,
        "BCM56505_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56506_DEVICE_ID, BCM56506_A0_REV_ID,
        "BCM56506_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56507_DEVICE_ID, BCM56507_A0_REV_ID,
        "BCM56507_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56508_DEVICE_ID, BCM56508_A0_REV_ID,
        "BCM56508_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56509_DEVICE_ID, BCM56509_A0_REV_ID,
        "BCM56509_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-Helix */
        BCM56404_DEVICE_ID, BCM56404_A1_REV_ID,
        "BCM56304_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56500_DEVICE_ID, BCM56500_A1_REV_ID,
        "BCM56500_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56501_DEVICE_ID, BCM56501_A1_REV_ID,
        "BCM56501_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56502_DEVICE_ID, BCM56502_A1_REV_ID,
        "BCM56502_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56503_DEVICE_ID, BCM56503_A1_REV_ID,
        "BCM56503_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56504_DEVICE_ID, BCM56504_A1_REV_ID,
        "BCM56504_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56505_DEVICE_ID, BCM56505_A1_REV_ID,
        "BCM56505_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56506_DEVICE_ID, BCM56506_A1_REV_ID,
        "BCM56506_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56507_DEVICE_ID, BCM56507_A1_REV_ID,
        "BCM56507_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56508_DEVICE_ID, BCM56508_A1_REV_ID,
        "BCM56508_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56509_DEVICE_ID, BCM56509_A1_REV_ID,
        "BCM56509_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56500_DEVICE_ID, BCM56500_B0_REV_ID,
        "BCM56500_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56501_DEVICE_ID, BCM56501_B0_REV_ID,
        "BCM56501_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56502_DEVICE_ID, BCM56502_B0_REV_ID,
        "BCM56502_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56503_DEVICE_ID, BCM56503_B0_REV_ID,
        "BCM56503_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        "BCM56504_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56505_DEVICE_ID, BCM56505_B0_REV_ID,
        "BCM56505_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56506_DEVICE_ID, BCM56506_B0_REV_ID,
        "BCM56506_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56507_DEVICE_ID, BCM56507_B0_REV_ID,
        "BCM56507_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56508_DEVICE_ID, BCM56508_B0_REV_ID,
        "BCM56508_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56509_DEVICE_ID, BCM56509_B0_REV_ID,
        "BCM56509_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56500_DEVICE_ID, BCM56500_B1_REV_ID,
        "BCM56500_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56501_DEVICE_ID, BCM56501_B1_REV_ID,
        "BCM56501_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56502_DEVICE_ID, BCM56502_B1_REV_ID,
        "BCM56502_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56503_DEVICE_ID, BCM56503_B1_REV_ID,
        "BCM56503_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56504_DEVICE_ID, BCM56504_B1_REV_ID,
        "BCM56504_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56505_DEVICE_ID, BCM56505_B1_REV_ID,
        "BCM56505_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56506_DEVICE_ID, BCM56506_B1_REV_ID,
        "BCM56506_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56507_DEVICE_ID, BCM56507_B1_REV_ID,
        "BCM56507_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56508_DEVICE_ID, BCM56508_B1_REV_ID,
        "BCM56508_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56509_DEVICE_ID, BCM56509_B1_REV_ID,
        "BCM56509_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56500_DEVICE_ID, BCM56500_B2_REV_ID,
        "BCM56500_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56501_DEVICE_ID, BCM56501_B2_REV_ID,
        "BCM56501_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56502_DEVICE_ID, BCM56502_B2_REV_ID,
        "BCM56502_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56503_DEVICE_ID, BCM56503_B2_REV_ID,
        "BCM56503_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56504_DEVICE_ID, BCM56504_B2_REV_ID,
        "BCM56504_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56505_DEVICE_ID, BCM56505_B2_REV_ID,
        "BCM56505_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56506_DEVICE_ID, BCM56506_B2_REV_ID,
        "BCM56506_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56507_DEVICE_ID, BCM56507_B2_REV_ID,
        "BCM56507_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56508_DEVICE_ID, BCM56508_B2_REV_ID,
        "BCM56508_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56509_DEVICE_ID, BCM56509_B2_REV_ID,
        "BCM56509_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_FIREBOLT_SUPPORT */

#if defined(BCM_RAPTOR1_SUPPORT)
    {   /* Raptor */
        BCM56218X_DEVICE_ID, BCM56218X_A0_REV_ID,
        "BCM56218_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        "BCM56218_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219_DEVICE_ID, BCM56219_A0_REV_ID,
        "BCM56219_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218R_DEVICE_ID, BCM56218R_A0_REV_ID,
        "BCM56218R_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219R_DEVICE_ID, BCM56219R_A0_REV_ID,
        "BCM56219R_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214_DEVICE_ID, BCM56214_A0_REV_ID,
        "BCM56214_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215_DEVICE_ID, BCM56215_A0_REV_ID,
        "BCM56215_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214R_DEVICE_ID, BCM56214R_A0_REV_ID,
        "BCM56214R_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215R_DEVICE_ID, BCM56215R_A0_REV_ID,
        "BCM56215R_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56216_DEVICE_ID, BCM56216_A0_REV_ID,
        "BCM56216_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56217_DEVICE_ID, BCM56217_A0_REV_ID,
        "BCM56217_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56212_DEVICE_ID, BCM56212_A0_REV_ID,
        "BCM56212_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56213_DEVICE_ID, BCM56213_A0_REV_ID,
        "BCM56213_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53718_DEVICE_ID, BCM53718_A0_REV_ID,
        "BCM53718_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53714_DEVICE_ID, BCM53714_A0_REV_ID,
        "BCM53714_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53716_DEVICE_ID, BCM53716_A0_REV_ID,
        "BCM53716_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56018_DEVICE_ID, BCM56018_A0_REV_ID,
        "BCM56018_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56014_DEVICE_ID, BCM56014_A0_REV_ID,
        "BCM56014_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218X_DEVICE_ID, BCM56218X_A1_REV_ID,
        "BCM56218_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218_DEVICE_ID, BCM56218_A1_REV_ID,
        "BCM56218_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219_DEVICE_ID, BCM56219_A1_REV_ID,
        "BCM56219_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218R_DEVICE_ID, BCM56218R_A1_REV_ID,
        "BCM56218R_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219R_DEVICE_ID, BCM56219R_A1_REV_ID,
        "BCM56219R_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214_DEVICE_ID, BCM56214_A1_REV_ID,
        "BCM56214_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215_DEVICE_ID, BCM56215_A1_REV_ID,
        "BCM56215_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214R_DEVICE_ID, BCM56214R_A1_REV_ID,
        "BCM56214R_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215R_DEVICE_ID, BCM56215R_A1_REV_ID,
        "BCM56215R_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56216_DEVICE_ID, BCM56216_A1_REV_ID,
        "BCM56216_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56217_DEVICE_ID, BCM56217_A1_REV_ID,
        "BCM56217_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56212_DEVICE_ID, BCM56212_A1_REV_ID,
        "BCM56212_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56213_DEVICE_ID, BCM56213_A1_REV_ID,
        "BCM56213_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53718_DEVICE_ID, BCM53718_A1_REV_ID,
        "BCM53718_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53714_DEVICE_ID, BCM53714_A1_REV_ID,
        "BCM53714_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53716_DEVICE_ID, BCM53716_A1_REV_ID,
        "BCM53716_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56018_DEVICE_ID, BCM56018_A1_REV_ID,
        "BCM56018_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56014_DEVICE_ID, BCM56014_A1_REV_ID,
        "BCM56014_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218_DEVICE_ID, BCM56218_A2_REV_ID,
        "BCM56218_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218X_DEVICE_ID, BCM56218X_A2_REV_ID,
        "BCM56218_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219_DEVICE_ID, BCM56219_A2_REV_ID,
        "BCM56219_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218R_DEVICE_ID, BCM56218R_A2_REV_ID,
        "BCM56218R_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219R_DEVICE_ID, BCM56219R_A2_REV_ID,
        "BCM56219R_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214_DEVICE_ID, BCM56214_A2_REV_ID,
        "BCM56214_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215_DEVICE_ID, BCM56215_A2_REV_ID,
        "BCM56215_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214R_DEVICE_ID, BCM56214R_A2_REV_ID,
        "BCM56214R_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215R_DEVICE_ID, BCM56215R_A2_REV_ID,
        "BCM56215R_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56216_DEVICE_ID, BCM56216_A2_REV_ID,
        "BCM56216_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56217_DEVICE_ID, BCM56217_A2_REV_ID,
        "BCM56217_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56212_DEVICE_ID, BCM56212_A2_REV_ID,
        "BCM56212_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56213_DEVICE_ID, BCM56213_A2_REV_ID,
        "BCM56213_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53718_DEVICE_ID, BCM53718_A2_REV_ID,
        "BCM53718_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53714_DEVICE_ID, BCM53714_A2_REV_ID,
        "BCM53714_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53716_DEVICE_ID, BCM53716_A2_REV_ID,
        "BCM53716_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56018_DEVICE_ID, BCM56018_A2_REV_ID,
        "BCM56018_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56014_DEVICE_ID, BCM56014_A2_REV_ID,
        "BCM56014_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_RAPTOR1_SUPPORT */

#if defined(BCM_GOLDWING_SUPPORT)
    {   /* Goldwing */
        BCM56580_DEVICE_ID, BCM56580_A0_REV_ID,
        "BCM56580_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_GOLDWING_SUPPORT */
#if defined(BCM_HUMV_SUPPORT)
    {   /* HUMV */
        BCM56700_DEVICE_ID, BCM56700_A0_REV_ID,
        "BCM56700_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* HUMV */
        BCM56701_DEVICE_ID, BCM56701_A0_REV_ID,
        "BCM56701_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_HUMV_SUPPORT */
#if defined(BCM_BRADLEY1_SUPPORT)
    /* Without HumV and Goldwing */
    {   /* Bradley */
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        "BCM56800_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Bradley */
        BCM56801_DEVICE_ID, BCM56801_A0_REV_ID,
        "BCM56801_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Bradley */
        BCM56802_DEVICE_ID, BCM56802_A0_REV_ID,
        "BCM56802_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Bradley */
        BCM56803_DEVICE_ID, BCM56803_A0_REV_ID,
        "BCM56803_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_BRADLEY1_SUPPORT */
    {   /* Firebolt2 */
        BCM56510_DEVICE_ID, BCM56510_A0_REV_ID,
        "BCM56510_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56511_DEVICE_ID, BCM56511_A0_REV_ID,
        "BCM56511_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56512_DEVICE_ID, BCM56512_A0_REV_ID,
        "BCM56512_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56513_DEVICE_ID, BCM56513_A0_REV_ID,
        "BCM56513_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        "BCM56514_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56516_DEVICE_ID, BCM56516_A0_REV_ID,
        "BCM56516_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56517_DEVICE_ID, BCM56517_A0_REV_ID,
        "BCM56517_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56518_DEVICE_ID, BCM56518_A0_REV_ID,
        "BCM56518_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56519_DEVICE_ID, BCM56519_A0_REV_ID,
        "BCM56519_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56620_DEVICE_ID, BCM56620_A0_REV_ID,
        "BCM56620_A0",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56620_DEVICE_ID, BCM56620_A1_REV_ID,
        "BCM56620_A1",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56620_DEVICE_ID, BCM56620_B0_REV_ID,
        "BCM56620_B0",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56620_DEVICE_ID, BCM56620_B1_REV_ID,
        "BCM56620_B1",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56620_DEVICE_ID, BCM56620_B2_REV_ID,
        "BCM56620_B2",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        "BCM56624_A0",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56624_DEVICE_ID, BCM56624_A1_REV_ID,
        "BCM56624_A1",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        "BCM56624_B0",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56624_DEVICE_ID, BCM56624_B1_REV_ID,
        "BCM56624_B1",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56624_DEVICE_ID, BCM56624_B2_REV_ID,
        "BCM56624_B2",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56626_DEVICE_ID, BCM56626_A0_REV_ID,
        "BCM56626_A0",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56626_DEVICE_ID, BCM56626_A1_REV_ID,
        "BCM56626_A1",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56626_DEVICE_ID, BCM56626_B0_REV_ID,
        "BCM56626_B0",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56626_DEVICE_ID, BCM56626_B1_REV_ID,
        "BCM56626_B1",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56626_DEVICE_ID, BCM56626_B2_REV_ID,
        "BCM56626_B2",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56628_DEVICE_ID, BCM56628_A0_REV_ID,
        "BCM56628_A0",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56628_DEVICE_ID, BCM56628_A1_REV_ID,
        "BCM56628_A1",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56628_DEVICE_ID, BCM56628_B0_REV_ID,
        "BCM56628_B0",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56628_DEVICE_ID, BCM56628_B1_REV_ID,
        "BCM56628_B1",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56628_DEVICE_ID, BCM56628_B2_REV_ID,
        "BCM56628_B2",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56629_DEVICE_ID, BCM56629_A0_REV_ID,
        "BCM56629_A0",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56629_DEVICE_ID, BCM56629_A1_REV_ID,
        "BCM56629_A1",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56629_DEVICE_ID, BCM56629_B0_REV_ID,
        "BCM56629_B0",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56629_DEVICE_ID, BCM56629_B1_REV_ID,
        "BCM56629_B1",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56629_DEVICE_ID, BCM56629_B2_REV_ID,
        "BCM56629_B2",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        "BCM56680_A0",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56680_DEVICE_ID, BCM56680_A1_REV_ID,
        "BCM56680_A1",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        "BCM56680_B0",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56680_DEVICE_ID, BCM56680_B1_REV_ID,
        "BCM56680_B1",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56680_DEVICE_ID, BCM56680_B2_REV_ID,
        "BCM56680_B2",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56684_DEVICE_ID, BCM56684_A0_REV_ID,
        "BCM56684_A0",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56684_DEVICE_ID, BCM56684_A1_REV_ID,
        "BCM56684_A1",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56684_DEVICE_ID, BCM56684_B0_REV_ID,
        "BCM56684_B0",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56684_DEVICE_ID, BCM56684_B1_REV_ID,
        "BCM56684_B1",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56684_DEVICE_ID, BCM56684_B2_REV_ID,
        "BCM56684_B2",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56686_DEVICE_ID, BCM56686_B0_REV_ID,
        "BCM56686_B0",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56686_DEVICE_ID, BCM56686_B1_REV_ID,
        "BCM56686_B1",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56686_DEVICE_ID, BCM56686_B2_REV_ID,
        "BCM56686_B2",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
# if defined(BCM_RAVEN_SUPPORT)
    {   /* Raven */

        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        "BCM56224_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56225_DEVICE_ID, BCM56225_A0_REV_ID,
        "BCM56225_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56226_DEVICE_ID, BCM56226_A0_REV_ID,
        "BCM56226_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56227_DEVICE_ID, BCM56227_A0_REV_ID,
        "BCM56227_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56228_DEVICE_ID, BCM56228_A0_REV_ID,
        "BCM56228_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56229_DEVICE_ID, BCM56229_A0_REV_ID,
        "BCM56229_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56024_DEVICE_ID, BCM56024_A0_REV_ID,
        "BCM56024_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56025_DEVICE_ID, BCM56025_A0_REV_ID,
        "BCM56025_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        "BCM56224_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56225_DEVICE_ID, BCM56225_B0_REV_ID,
        "BCM56225_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56226_DEVICE_ID, BCM56226_B0_REV_ID,
        "BCM56226_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56227_DEVICE_ID, BCM56227_B0_REV_ID,
        "BCM56227_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56228_DEVICE_ID, BCM56228_B0_REV_ID,
        "BCM56228_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56229_DEVICE_ID, BCM56229_B0_REV_ID,
        "BCM56229_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56024_DEVICE_ID, BCM56024_B0_REV_ID,
        "BCM56024_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56025_DEVICE_ID, BCM56025_B0_REV_ID,
        "BCM56025_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM53724_DEVICE_ID, BCM53724_B0_REV_ID,
        "BCM53724_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM53726_DEVICE_ID, BCM53726_B0_REV_ID,
        "BCM53726_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_SCORPION_SUPPORT)
    {   /* Scorpion */
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        "BCM56820_A0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56820_DEVICE_ID, BCM56820_B0_REV_ID,
        "BCM56820_B0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56821_DEVICE_ID, BCM56821_A0_REV_ID,
        "BCM56821_A0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56821_DEVICE_ID, BCM56821_B0_REV_ID,
        "BCM56821_B0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56822_DEVICE_ID, BCM56822_A0_REV_ID,
        "BCM56822_A0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56822_DEVICE_ID, BCM56822_B0_REV_ID,
        "BCM56822_B0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56823_DEVICE_ID, BCM56823_A0_REV_ID,
        "BCM56823_A0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56823_DEVICE_ID, BCM56823_B0_REV_ID,
        "BCM56823_B0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56825_DEVICE_ID, BCM56825_B0_REV_ID,
        "BCM56825_B0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#if defined(BCM_CONQUEROR_SUPPORT)
    {   /* HUMV plus */
        BCM56720_DEVICE_ID, BCM56720_A0_REV_ID,
        "BCM56720_A0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* HUMV plus */
        BCM56720_DEVICE_ID, BCM56720_B0_REV_ID,
        "BCM56720_B0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* HUMV plus */
        BCM56721_DEVICE_ID, BCM56721_A0_REV_ID,
        "BCM56721_A0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* HUMV plus */
        BCM56721_DEVICE_ID, BCM56721_B0_REV_ID,
        "BCM56721_B0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Conqueror */
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        "BCM56725_A0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Conqueror */
        BCM56725_DEVICE_ID, BCM56725_B0_REV_ID,
        "BCM56725_B0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_CONQUEROR_SUPPORT */
#endif

#if defined(BCM_HAWKEYE_SUPPORT)
    {   /* Hawkeye */
        BCM53312_DEVICE_ID, BCM53312_A0_REV_ID,
        "BCM53312_A0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye */
        BCM53312_DEVICE_ID, BCM53312_B0_REV_ID,
        "BCM53312_B0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye */
        BCM53313_DEVICE_ID, BCM53313_A0_REV_ID,
        "BCM53313_A0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye */
        BCM53313_DEVICE_ID, BCM53313_B0_REV_ID,
        "BCM53313_B0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye */
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        "BCM53314_A0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye */
        BCM53314_DEVICE_ID, BCM53314_B0_REV_ID,
        "BCM53314_B0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye EEE */
        BCM53322_DEVICE_ID, BCM53322_A0_REV_ID,
        "BCM53322_A0",
        BCM53324_DEVICE_ID, BCM53324_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye EEE */
        BCM53323_DEVICE_ID, BCM53323_A0_REV_ID,
        "BCM53323_A0",
        BCM53324_DEVICE_ID, BCM53324_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye EEE */
        BCM53324_DEVICE_ID, BCM53324_A0_REV_ID,
        "BCM53324_A0",
        BCM53324_DEVICE_ID, BCM53324_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_TRIUMPH2_SUPPORT)
    {   /* Triumph2 */

        BCM56630_DEVICE_ID, BCM56630_A0_REV_ID,
        "BCM56630_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56630_DEVICE_ID, BCM56630_B0_REV_ID,
        "BCM56630_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56634_DEVICE_ID, BCM56634_A0_REV_ID,
        "BCM56634_A0",
        BCM56634_DEVICE_ID, BCM56634_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        "BCM56634_B0",
        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56636_DEVICE_ID, BCM56636_A0_REV_ID,
        "BCM56636_A0",
        BCM56634_DEVICE_ID, BCM56634_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56636_DEVICE_ID, BCM56636_B0_REV_ID,
        "BCM56636_B0",
        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56638_DEVICE_ID, BCM56638_A0_REV_ID,
        "BCM56638_A0",
        BCM56634_DEVICE_ID, BCM56634_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56638_DEVICE_ID, BCM56638_B0_REV_ID,
        "BCM56638_B0",
        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56639_DEVICE_ID, BCM56639_A0_REV_ID,
        "BCM56639_A0",
        BCM56634_DEVICE_ID, BCM56634_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56639_DEVICE_ID, BCM56639_B0_REV_ID,
        "BCM56639_B0",
        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt 3 */

        BCM56538_DEVICE_ID, BCM56538_B0_REV_ID,
        "BCM56538_B0",
        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_VALKYRIE2_SUPPORT)
    {   /* Valkyrie2 */

        BCM56685_DEVICE_ID, BCM56685_A0_REV_ID,
        "BCM56685_A0",
        BCM56685_DEVICE_ID, BCM56685_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie2 */

        BCM56685_DEVICE_ID, BCM56685_B0_REV_ID,
        "BCM56685_B0",
        BCM56685_DEVICE_ID, BCM56685_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie2 */

        BCM56689_DEVICE_ID, BCM56689_A0_REV_ID,
        "BCM56689_A0",
        BCM56685_DEVICE_ID, BCM56685_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie2 */

        BCM56689_DEVICE_ID, BCM56689_B0_REV_ID,
        "BCM56689_B0",
        BCM56685_DEVICE_ID, BCM56685_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_APOLLO_SUPPORT)
    {   /* Apollo */

        BCM56520_DEVICE_ID, BCM56520_A0_REV_ID,
        "BCM56520_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56520_DEVICE_ID, BCM56520_B0_REV_ID,
        "BCM56520_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Apollo */

        BCM56521_DEVICE_ID, BCM56521_A0_REV_ID,
        "BCM56521_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56521_DEVICE_ID, BCM56521_B0_REV_ID,
        "BCM56521_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56522_DEVICE_ID, BCM56522_A0_REV_ID,
        "BCM56522_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56522_DEVICE_ID, BCM56522_B0_REV_ID,
        "BCM56522_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        "BCM56524_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        "BCM56524_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56526_DEVICE_ID, BCM56526_A0_REV_ID,
        "BCM56526_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56526_DEVICE_ID, BCM56526_B0_REV_ID,
        "BCM56526_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt 3 */

        BCM56534_DEVICE_ID, BCM56534_B0_REV_ID,
        "BCM56534_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_ENDURO_SUPPORT)
    {   /* Enduro */
        BCM56331_DEVICE_ID, BCM56331_A0_REV_ID,
        "BCM56331_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro */
        BCM56331_DEVICE_ID, BCM56331_B0_REV_ID,
        "BCM56331_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro */
        BCM56331_DEVICE_ID, BCM56331_B1_REV_ID,
        "BCM56331_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro */
        BCM56333_DEVICE_ID, BCM56333_A0_REV_ID,
        "BCM56333_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro */
        BCM56333_DEVICE_ID, BCM56333_B0_REV_ID,
        "BCM56333_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro */
        BCM56333_DEVICE_ID, BCM56333_B1_REV_ID,
        "BCM56333_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro - Default */
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        "BCM56334_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro */
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        "BCM56334_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro */
        BCM56334_DEVICE_ID, BCM56334_B1_REV_ID,
        "BCM56334_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro */
        BCM56338_DEVICE_ID, BCM56338_A0_REV_ID,
        "BCM56338_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro */
        BCM56338_DEVICE_ID, BCM56338_B0_REV_ID,
        "BCM56338_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro */
        BCM56338_DEVICE_ID, BCM56338_B1_REV_ID,
        "BCM56338_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56320_DEVICE_ID, BCM56320_A0_REV_ID,
        "BCM56320_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56320_DEVICE_ID, BCM56320_B0_REV_ID,
        "BCM56320_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56320_DEVICE_ID, BCM56320_B1_REV_ID,
        "BCM56320_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56321_DEVICE_ID, BCM56321_A0_REV_ID,
        "BCM56321_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56321_DEVICE_ID, BCM56321_B0_REV_ID,
        "BCM56321_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56321_DEVICE_ID, BCM56321_B1_REV_ID,
        "BCM56321_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Dagger  */
        BCM56230_DEVICE_ID, BCM56230_B1_REV_ID,
        "BCM56230_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Dagger  */
        BCM56231_DEVICE_ID, BCM56231_B1_REV_ID,
        "BCM56231_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_HURRICANE1_SUPPORT)
    {   /* Hurricane */
        BCM56140_DEVICE_ID, BCM56140_A0_REV_ID,
        "BCM56140_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        "BCM56142_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56143_DEVICE_ID, BCM56143_A0_REV_ID,
        "BCM56143_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56144_DEVICE_ID, BCM56144_A0_REV_ID,
        "BCM56144_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56146_DEVICE_ID, BCM56146_A0_REV_ID,
        "BCM56146_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56147_DEVICE_ID, BCM56147_A0_REV_ID,
        "BCM56147_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56149_DEVICE_ID, BCM56149_A0_REV_ID,
        "BCM56149_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_HURRICANE2_SUPPORT)
    {   /* Hurricane 2 */
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        "BCM56150_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane 2 */
        BCM56151_DEVICE_ID, BCM56151_A0_REV_ID,
        "BCM56151_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane 2 */
        BCM56152_DEVICE_ID, BCM56152_A0_REV_ID,
        "BCM56152_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound */
        BCM53342_DEVICE_ID, BCM53342_A0_REV_ID,
        "BCM53342_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound */
        BCM53343_DEVICE_ID, BCM53343_A0_REV_ID,
        "BCM53343_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound */
        BCM53344_DEVICE_ID, BCM53344_A0_REV_ID,
        "BCM53344_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound */
        BCM53346_DEVICE_ID, BCM53346_A0_REV_ID,
        "BCM53346_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {    /* Wolfhound */
        BCM53347_DEVICE_ID, BCM53347_A0_REV_ID,
        "BCM53347_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Foxhound */
        BCM53333_DEVICE_ID, BCM53333_A0_REV_ID,
        "BCM53333_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Foxhound */
        BCM53334_DEVICE_ID, BCM53334_A0_REV_ID,
        "BCM53334_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Deerhound */
        BCM53393_DEVICE_ID, BCM53393_A0_REV_ID,
        "BCM53393_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Deerhound */
        BCM53394_DEVICE_ID, BCM53394_A0_REV_ID,
        "BCM53394_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_GREYHOUND_SUPPORT)
    {   /* Greyhound */
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        "BCM53400_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53401_DEVICE_ID, BCM53401_A0_REV_ID,
        "BCM53401_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53411_DEVICE_ID, BCM53401_A0_REV_ID,
        "BCM53411_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53402_DEVICE_ID, BCM53402_A0_REV_ID,
        "BCM53402_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53412_DEVICE_ID, BCM53402_A0_REV_ID,
        "BCM53412_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53403_DEVICE_ID, BCM53403_A0_REV_ID,
        "BCM53403_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53413_DEVICE_ID, BCM53403_A0_REV_ID,
        "BCM53413_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53404_DEVICE_ID, BCM53404_A0_REV_ID,
        "BCM53404_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53414_DEVICE_ID, BCM53404_A0_REV_ID,
        "BCM53414_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53405_DEVICE_ID, BCM53405_A0_REV_ID,
        "BCM53405_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53415_DEVICE_ID, BCM53405_A0_REV_ID,
        "BCM53415_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53406_DEVICE_ID, BCM53406_A0_REV_ID,
        "BCM53406_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53416_DEVICE_ID, BCM53406_A0_REV_ID,
        "BCM53416_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53408_DEVICE_ID, BCM53408_A0_REV_ID,
        "BCM53408_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53418_DEVICE_ID, BCM53408_A0_REV_ID,
        "BCM53418_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger2 */
        BCM56060_DEVICE_ID, BCM56060_A0_REV_ID,
        "BCM56060_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger2 */
        BCM56062_DEVICE_ID, BCM56062_A0_REV_ID,
        "BCM56062_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger2 */
        BCM56063_DEVICE_ID, BCM56063_A0_REV_ID,
        "BCM56063_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger2 */
        BCM56064_DEVICE_ID, BCM56064_A0_REV_ID,
        "BCM56064_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger2 */
        BCM56065_DEVICE_ID, BCM56065_A0_REV_ID,
        "BCM56065_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },    
    {   /* Ranger2 */
        BCM56066_DEVICE_ID, BCM56066_A0_REV_ID,
        "BCM56066_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Elkhound */
        BCM53454_DEVICE_ID, BCM53454_A0_REV_ID,
        "BCM53454_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Elkhound */
        BCM53455_DEVICE_ID, BCM53454_A0_REV_ID,
        "BCM53455_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Elkhound */
        BCM53456_DEVICE_ID, BCM53456_A0_REV_ID,
        "BCM53456_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Elkhound */
        BCM53457_DEVICE_ID, BCM53456_A0_REV_ID,
        "BCM53457_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Bloodhound */
        BCM53422_DEVICE_ID, BCM53422_A0_REV_ID,
        "BCM53422_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Bloodhound */
        BCM53424_DEVICE_ID, BCM53424_A0_REV_ID,
        "BCM53424_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Bloodhound */
        BCM53426_DEVICE_ID, BCM53426_A0_REV_ID,
        "BCM53426_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound Lite w/o L3 */
        BCM53365_DEVICE_ID, BCM53365_A0_REV_ID,
        "BCM53365_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Greyhound */
        BCM53369_DEVICE_ID, BCM53369_A0_REV_ID,
        "BCM53369_A0",
        BCM53400_DEVICE_ID, BCM53400_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_HURRICANE3_SUPPORT)
    {   /* Hurricane3 */
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        "BCM56160_A0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3 */
        BCM56160_DEVICE_ID, BCM56160_B0_REV_ID,
        "BCM56160_B0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3 */
        BCM56162_DEVICE_ID, BCM56162_A0_REV_ID,
        "BCM56162_A0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3 */
        BCM56162_DEVICE_ID, BCM56162_B0_REV_ID,
        "BCM56162_B0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3 Lite */
        BCM56163_DEVICE_ID, BCM56163_A0_REV_ID,
        "BCM56163_A0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3 Lite */
        BCM56163_DEVICE_ID, BCM56163_B0_REV_ID,
        "BCM56163_B0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3 Lite */
        BCM56164_DEVICE_ID, BCM56164_A0_REV_ID,
        "BCM56164_A0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3 Lite */
        BCM56164_DEVICE_ID, BCM56164_B0_REV_ID,
        "BCM56164_B0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3 Lite */
        BCM56166_DEVICE_ID, BCM56166_A0_REV_ID,
        "BCM56166_A0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3 Lite */
        BCM56166_DEVICE_ID, BCM56166_B0_REV_ID,
        "BCM56166_B0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Buckhound */
        BCM53440_DEVICE_ID, BCM53440_A0_REV_ID,
        "BCM53440_A0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Buckhound */
        BCM53440_DEVICE_ID, BCM53440_B0_REV_ID,
        "BCM53440_B0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Buckhound */
        BCM53443_DEVICE_ID, BCM53443_A0_REV_ID,
        "BCM53443_A0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Buckhound */
        BCM53443_DEVICE_ID, BCM53443_B0_REV_ID,
        "BCM53443_B0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Buckhound */
        BCM53442_DEVICE_ID, BCM53442_A0_REV_ID,
        "BCM53442_A0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Buckhound */
        BCM53442_DEVICE_ID, BCM53442_B0_REV_ID,
        "BCM53442_B0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Foxhound2 */
        BCM53434_DEVICE_ID, BCM53434_A0_REV_ID,
        "BCM53434_A0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Foxhound2 */
        BCM53434_DEVICE_ID, BCM53434_B0_REV_ID,
        "BCM53434_B0",
        BCM56160_DEVICE_ID, BCM56160_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound2 */
        BCM53540_DEVICE_ID, BCM53540_A0_REV_ID,
        "BCM53540_A0",
        BCM53540_DEVICE_ID, BCM53540_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound2 */
        BCM53547_DEVICE_ID, BCM53547_A0_REV_ID,
        "BCM53547_A0",
        BCM53540_DEVICE_ID, BCM53540_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound2 */
        BCM53548_DEVICE_ID, BCM53548_A0_REV_ID,
        "BCM53548_A0",
        BCM53540_DEVICE_ID, BCM53540_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound2 */
        BCM53549_DEVICE_ID, BCM53549_A0_REV_ID,
        "BCM53549_A0",
        BCM53540_DEVICE_ID, BCM53540_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_HURRICANE4_SUPPORT)
    {   /* Hurricane4 */
        BCM56273_DEVICE_ID, BCM56273_A0_REV_ID,
        "BCM56273_A0",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56274_DEVICE_ID, BCM56274_A0_REV_ID,
        "BCM56274_A0",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        "BCM56275_A0",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56276_DEVICE_ID, BCM56276_A0_REV_ID,
        "BCM56276_A0",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56277_DEVICE_ID, BCM56277_A0_REV_ID,
        "BCM56277_A0",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56278_DEVICE_ID, BCM56278_A0_REV_ID,
        "BCM56278_A0",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56273_DEVICE_ID, BCM56273_A1_REV_ID,
        "BCM56273_A1",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56274_DEVICE_ID, BCM56274_A1_REV_ID,
        "BCM56274_A1",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56275_DEVICE_ID, BCM56275_A1_REV_ID,
        "BCM56275_A1",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56276_DEVICE_ID, BCM56276_A1_REV_ID,
        "BCM56276_A1",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56277_DEVICE_ID, BCM56277_A1_REV_ID,
        "BCM56277_A1",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56278_DEVICE_ID, BCM56278_A1_REV_ID,
        "BCM56278_A1",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56279_DEVICE_ID, BCM56279_A1_REV_ID,
        "BCM56279_A1",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane4 */
        BCM56575_DEVICE_ID, BCM56575_A1_REV_ID,
        "BCM56575_A1",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident3x1 */
        BCM56175_DEVICE_ID, BCM56175_A1_REV_ID,
        "BCM56175_A1",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident3x1 */
        BCM56176_DEVICE_ID, BCM56176_A1_REV_ID,
        "BCM56176_A1",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound3 */
        BCM53642_DEVICE_ID, BCM53642_A0_REV_ID,
        "BCM53642_A0",
        BCM56275_DEVICE_ID, BCM56275_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_HURRICANE4_SUPPORT */

#if defined(BCM_GREYHOUND2_SUPPORT)
    {   /* Hurricane3-MG */
        BCM56170_DEVICE_ID, BCM56170_A0_REV_ID,
        "BCM56170_A0",
        BCM53570_DEVICE_ID, BCM53570_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3-MG */
        BCM56170_DEVICE_ID, BCM56170_B0_REV_ID,
        "BCM56170_B0",
        BCM53570_DEVICE_ID, BCM53570_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3-MG */
        BCM56172_DEVICE_ID, BCM56172_A0_REV_ID,
        "BCM56172_A0",
        BCM53570_DEVICE_ID, BCM53570_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3-MG */
        BCM56172_DEVICE_ID, BCM56172_B0_REV_ID,
        "BCM56172_B0",
        BCM53570_DEVICE_ID, BCM53570_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3-MG */
        BCM56174_DEVICE_ID, BCM56174_A0_REV_ID,
        "BCM56174_A0",
        BCM53570_DEVICE_ID, BCM53570_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane3-MG */
        BCM56174_DEVICE_ID, BCM56174_B0_REV_ID,
        "BCM56174_B0",
        BCM53570_DEVICE_ID, BCM53570_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Quartz, Greyhound2 */
        BCM53570_DEVICE_ID, BCM53570_A0_REV_ID,
        "BCM53570_A0",
        BCM53570_DEVICE_ID, BCM53570_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Quartz, Greyhound2 */
        BCM53570_DEVICE_ID, BCM53570_B0_REV_ID,
        "BCM53570_B0",
        BCM53570_DEVICE_ID, BCM53570_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Quartz, Greyhound2 */
        BCM53575_DEVICE_ID, BCM53575_A0_REV_ID,
        "BCM53575_A0",
        BCM53570_DEVICE_ID, BCM53570_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Quartz, Greyhound2 */
        BCM53575_DEVICE_ID, BCM53575_B0_REV_ID,
        "BCM53575_B0",
        BCM53570_DEVICE_ID, BCM53570_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_GREYHOUND2_SUPPORT */
#if defined(BCM_FIRELIGHT_SUPPORT)
    {   /* Firelight */
        BCM56070_DEVICE_ID, BCM56070_A0_REV_ID,
        "BCM56070_A0",
        BCM56070_DEVICE_ID, BCM56070_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firelight */
        BCM56071_DEVICE_ID, BCM56071_A0_REV_ID,
        "BCM56071_A0",
        BCM56070_DEVICE_ID, BCM56070_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firelight */
        BCM56072_DEVICE_ID, BCM56072_A0_REV_ID,
        "BCM56072_A0",
        BCM56070_DEVICE_ID, BCM56070_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_FIRELIGHT_SUPPORT */
#if defined(BCM_TRIDENT_SUPPORT)
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        "BCM56840_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_A1_REV_ID,
        "BCM56840_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_A2_REV_ID,
        "BCM56840_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_A3_REV_ID,
        "BCM56840_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_A4_REV_ID,
        "BCM56840_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        "BCM56840_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_B1_REV_ID,
        "BCM56840_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_A0_REV_ID,
        "BCM56841_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_A1_REV_ID,
        "BCM56841_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_A2_REV_ID,
        "BCM56841_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_A3_REV_ID,
        "BCM56841_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_A4_REV_ID,
        "BCM56841_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_B0_REV_ID,
        "BCM56841_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_B1_REV_ID,
        "BCM56841_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_A0_REV_ID,
        "BCM56843_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_A1_REV_ID,
        "BCM56843_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_A2_REV_ID,
        "BCM56843_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_A3_REV_ID,
        "BCM56843_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_A4_REV_ID,
        "BCM56843_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_B0_REV_ID,
        "BCM56843_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_B1_REV_ID,
        "BCM56843_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_A0_REV_ID,
        "BCM56845_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_A1_REV_ID,
        "BCM56845_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_A2_REV_ID,
        "BCM56845_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_A3_REV_ID,
        "BCM56845_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_A4_REV_ID,
        "BCM56845_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_B0_REV_ID,
        "BCM56845_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_B1_REV_ID,
        "BCM56845_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_A0_REV_ID,
        "BCM56743_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_A1_REV_ID,
        "BCM56743_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_A2_REV_ID,
        "BCM56743_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_A3_REV_ID,
        "BCM56743_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_A4_REV_ID,
        "BCM56743_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_B0_REV_ID,
        "BCM56743_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_B1_REV_ID,
        "BCM56743_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_A0_REV_ID,
        "BCM56745_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_A1_REV_ID,
        "BCM56745_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_A2_REV_ID,
        "BCM56745_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_A3_REV_ID,
        "BCM56745_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_A4_REV_ID,
        "BCM56745_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_B0_REV_ID,
        "BCM56745_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_B1_REV_ID,
        "BCM56745_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56842_DEVICE_ID, BCM56842_A0_REV_ID,
        "BCM56842_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56842_DEVICE_ID, BCM56842_A1_REV_ID,
        "BCM56842_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56844_DEVICE_ID, BCM56844_A0_REV_ID,
        "BCM56844_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56844_DEVICE_ID, BCM56844_A1_REV_ID,
        "BCM56844_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56846_DEVICE_ID, BCM56846_A0_REV_ID,
        "BCM56846_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56846_DEVICE_ID, BCM56846_A1_REV_ID,
        "BCM56846_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56847_DEVICE_ID, BCM56847_A0_REV_ID,
        "BCM56847_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56847_DEVICE_ID, BCM56847_A1_REV_ID,
        "BCM56847_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56847_DEVICE_ID, BCM56847_A2_REV_ID,
        "BCM56847_A2",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56847_DEVICE_ID, BCM56847_A3_REV_ID,
        "BCM56847_A3",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56847_DEVICE_ID, BCM56847_A4_REV_ID,
        "BCM56847_A4",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56847_DEVICE_ID, BCM56847_B0_REV_ID,
        "BCM56847_B0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56847_DEVICE_ID, BCM56847_B1_REV_ID,
        "BCM56847_B1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56549_DEVICE_ID, BCM56549_A0_REV_ID,
        "BCM56549_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56053_DEVICE_ID, BCM56053_A0_REV_ID,
        "BCM56053_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56053_DEVICE_ID, BCM56053_A1_REV_ID,
        "BCM56053_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56549_DEVICE_ID, BCM56549_A1_REV_ID,
        "BCM56549_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56831_DEVICE_ID, BCM56831_A0_REV_ID,
        "BCM56831_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56831_DEVICE_ID, BCM56831_A1_REV_ID,
        "BCM56831_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56835_DEVICE_ID, BCM56835_A0_REV_ID,
        "BCM56835_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56835_DEVICE_ID, BCM56835_A1_REV_ID,
        "BCM56835_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56838_DEVICE_ID, BCM56838_A0_REV_ID,
        "BCM56838_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56838_DEVICE_ID, BCM56838_A1_REV_ID,
        "BCM56838_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56849_DEVICE_ID, BCM56849_A0_REV_ID,
        "BCM56849_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56849_DEVICE_ID, BCM56849_A1_REV_ID,
        "BCM56849_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56742_DEVICE_ID, BCM56742_A0_REV_ID,
        "BCM56742_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56742_DEVICE_ID, BCM56742_A1_REV_ID,
        "BCM56742_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56742_DEVICE_ID, BCM56742_A2_REV_ID,
        "BCM56742_A2",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56744_DEVICE_ID, BCM56744_A0_REV_ID,
        "BCM56744_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56744_DEVICE_ID, BCM56744_A1_REV_ID,
        "BCM56744_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56746_DEVICE_ID, BCM56746_A0_REV_ID,
        "BCM56746_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56746_DEVICE_ID, BCM56746_A1_REV_ID,
        "BCM56746_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_HELIX4_SUPPORT)
    {   /* FireScout */
        BCM56548H_DEVICE_ID, BCM56548H_A0_REV_ID,
        "BCM56548H_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FireScout */
        BCM56548_DEVICE_ID, BCM56548_A0_REV_ID,
        "BCM56548_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FireScout */
        BCM56547_DEVICE_ID, BCM56547_A0_REV_ID,
        "BCM56547_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix4 */
        BCM56346_DEVICE_ID, BCM56346_A0_REV_ID,
        "BCM56346_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix4 */
        BCM56345_DEVICE_ID, BCM56345_A0_REV_ID,
        "BCM56345_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix4 */
        BCM56344_DEVICE_ID, BCM56344_A0_REV_ID,
        "BCM56344_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix4 */
        BCM56342_DEVICE_ID, BCM56342_A0_REV_ID,
        "BCM56342_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix4 */
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        "BCM56340_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Spiral */
        BCM56049_DEVICE_ID, BCM56049_A0_REV_ID,
        "BCM56049_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Spiral */
        BCM56048_DEVICE_ID, BCM56048_A0_REV_ID,
        "BCM56048_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Spiral */
        BCM56047_DEVICE_ID, BCM56047_A0_REV_ID,
        "BCM56047_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger */
        BCM56042_DEVICE_ID, BCM56042_A0_REV_ID,
        "BCM56042_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger */
        BCM56041_DEVICE_ID, BCM56041_A0_REV_ID,
        "BCM56041_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger */
        BCM56040_DEVICE_ID, BCM56040_A0_REV_ID,
        "BCM56040_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_TRIUMPH3_SUPPORT)
    {   /* Triumph3 */
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        "BCM56640_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56640_DEVICE_ID, BCM56640_A1_REV_ID,
        "BCM56640_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56640_DEVICE_ID, BCM56640_B0_REV_ID,
        "BCM56640_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56643_DEVICE_ID, BCM56643_A0_REV_ID,
        "BCM56643_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56643_DEVICE_ID, BCM56643_A1_REV_ID,
        "BCM56643_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56643_DEVICE_ID, BCM56643_B0_REV_ID,
        "BCM56643_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56644_DEVICE_ID, BCM56644_A0_REV_ID,
        "BCM56644_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56644_DEVICE_ID, BCM56644_A1_REV_ID,
        "BCM56644_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56644_DEVICE_ID, BCM56644_B0_REV_ID,
        "BCM56644_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56648_DEVICE_ID, BCM56648_A0_REV_ID,
        "BCM56648_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56648_DEVICE_ID, BCM56648_A1_REV_ID,
        "BCM56648_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56648_DEVICE_ID, BCM56648_B0_REV_ID,
        "BCM56648_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56649_DEVICE_ID, BCM56649_A0_REV_ID,
        "BCM56649_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56649_DEVICE_ID, BCM56649_A1_REV_ID,
        "BCM56649_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56649_DEVICE_ID, BCM56649_B0_REV_ID,
        "BCM56649_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56545_DEVICE_ID, BCM56545_A0_REV_ID,
        "BCM56545_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56545_DEVICE_ID, BCM56545_A1_REV_ID,
        "BCM56545_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56545_DEVICE_ID, BCM56545_B0_REV_ID,
        "BCM56545_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56546_DEVICE_ID, BCM56546_A0_REV_ID,
        "BCM56546_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56546_DEVICE_ID, BCM56546_A1_REV_ID,
        "BCM56546_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56546_DEVICE_ID, BCM56546_B0_REV_ID,
        "BCM56546_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56540_DEVICE_ID, BCM56540_A0_REV_ID,
        "BCM56540_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56540_DEVICE_ID, BCM56540_A1_REV_ID,
        "BCM56540_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56540_DEVICE_ID, BCM56540_B0_REV_ID,
        "BCM56540_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56541_DEVICE_ID, BCM56541_A0_REV_ID,
        "BCM56541_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56541_DEVICE_ID, BCM56541_A1_REV_ID,
        "BCM56541_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56541_DEVICE_ID, BCM56541_B0_REV_ID,
        "BCM56541_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56542_DEVICE_ID, BCM56542_A0_REV_ID,
        "BCM56542_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56542_DEVICE_ID, BCM56542_A1_REV_ID,
        "BCM56542_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56542_DEVICE_ID, BCM56542_B0_REV_ID,
        "BCM56542_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56543_DEVICE_ID, BCM56543_A0_REV_ID,
        "BCM56543_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56543_DEVICE_ID, BCM56543_A1_REV_ID,
        "BCM56543_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56543_DEVICE_ID, BCM56543_B0_REV_ID,
        "BCM56543_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56544_DEVICE_ID, BCM56544_A0_REV_ID,
        "BCM56544_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56544_DEVICE_ID, BCM56544_A1_REV_ID,
        "BCM56544_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56544_DEVICE_ID, BCM56544_B0_REV_ID,
        "BCM56544_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56044_DEVICE_ID, BCM56044_B0_REV_ID,
        "BCM56044_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56045_DEVICE_ID, BCM56045_A0_REV_ID,
        "BCM56045_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56045_DEVICE_ID, BCM56045_A1_REV_ID,
        "BCM56045_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56045_DEVICE_ID, BCM56045_B0_REV_ID,
        "BCM56045_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56046_DEVICE_ID, BCM56046_A0_REV_ID,
        "BCM56046_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56046_DEVICE_ID, BCM56046_A1_REV_ID,
        "BCM56046_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56046_DEVICE_ID, BCM56046_B0_REV_ID,
        "BCM56046_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_KATANA_SUPPORT)
    {   /* Katana */
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        "BCM56440_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        "BCM56440_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56441_DEVICE_ID, BCM56441_A0_REV_ID,
        "BCM56441_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56441_DEVICE_ID, BCM56441_B0_REV_ID,
        "BCM56441_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56442_DEVICE_ID, BCM56442_A0_REV_ID,
        "BCM56442_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56442_DEVICE_ID, BCM56442_B0_REV_ID,
        "BCM56442_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56443_DEVICE_ID, BCM56443_A0_REV_ID,
        "BCM56443_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56443_DEVICE_ID, BCM56443_B0_REV_ID,
        "BCM56443_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56445_DEVICE_ID, BCM56445_A0_REV_ID,
        "BCM56445_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56445_DEVICE_ID, BCM56445_B0_REV_ID,
        "BCM56445_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56446_DEVICE_ID, BCM56446_A0_REV_ID,
        "BCM56446_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56446_DEVICE_ID, BCM56446_B0_REV_ID,
        "BCM56446_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56447_DEVICE_ID, BCM56447_A0_REV_ID,
        "BCM56447_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56447_DEVICE_ID, BCM56447_B0_REV_ID,
        "BCM56447_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56448_DEVICE_ID, BCM56448_A0_REV_ID,
        "BCM56448_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56448_DEVICE_ID, BCM56448_B0_REV_ID,
        "BCM56448_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-FE */
        BCM56449_DEVICE_ID, BCM56449_A0_REV_ID,
        "BCM56449_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-FE */
        BCM56449_DEVICE_ID, BCM56449_B0_REV_ID,
        "BCM56449_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56240_DEVICE_ID, BCM56240_A0_REV_ID,
        "BCM56240_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56240_DEVICE_ID, BCM56240_B0_REV_ID,
        "BCM56240_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56241_DEVICE_ID, BCM56241_A0_REV_ID,
        "BCM56241_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56241_DEVICE_ID, BCM56241_B0_REV_ID,
        "BCM56241_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56242_DEVICE_ID, BCM56242_A0_REV_ID,
        "BCM56242_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber*/
        BCM56242_DEVICE_ID, BCM56242_B0_REV_ID,
        "BCM56242_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56243_DEVICE_ID, BCM56243_A0_REV_ID,
        "BCM56243_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
   },
    {   /* Saber */
        BCM56243_DEVICE_ID, BCM56243_B0_REV_ID,
        "BCM56243_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56245_DEVICE_ID, BCM56245_A0_REV_ID,
        "BCM56245_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56245_DEVICE_ID, BCM56245_B0_REV_ID,
        "BCM56245_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56246_DEVICE_ID, BCM56246_A0_REV_ID,
        "BCM56246_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber*/
        BCM56246_DEVICE_ID, BCM56246_B0_REV_ID,
        "BCM56246_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-Access */
        BCM55440_DEVICE_ID, BCM55440_A0_REV_ID,
        "BCM55440_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-Access */
        BCM55440_DEVICE_ID, BCM55440_B0_REV_ID,
        "BCM55440_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-Access */
        BCM55441_DEVICE_ID, BCM55441_A0_REV_ID,
        "BCM55441_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-Access */
        BCM55441_DEVICE_ID, BCM55441_B0_REV_ID,
        "BCM55441_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_KATANA2_SUPPORT)
    {   /* Katana 2 1.A0 */
        BCM55450_DEVICE_ID, BCM55450_A0_REV_ID,
        "BCM55450_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 1.B0 */
        BCM55450_DEVICE_ID, BCM55450_B0_REV_ID,
        "BCM55450_B0",
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 1.B1 */
        BCM55450_DEVICE_ID, BCM55450_B1_REV_ID,
        "BCM55450_B1",
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Katana 2 2.A0 */
        BCM55455_DEVICE_ID, BCM55455_A0_REV_ID,
        "BCM55455_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 2.B0 */
        BCM55455_DEVICE_ID, BCM55455_B0_REV_ID,
        "BCM55455_B0",
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 2.B1 */
        BCM55455_DEVICE_ID, BCM55455_B1_REV_ID,
        "BCM55455_B1",
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Katana 2 3.A0 */
        BCM56248_DEVICE_ID, BCM56248_A0_REV_ID,
        "BCM56248_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 3.B0 */
        BCM56248_DEVICE_ID, BCM56248_B0_REV_ID,
        "BCM56248_B0",
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 3.B1 */
        BCM56248_DEVICE_ID, BCM56248_B1_REV_ID,
        "BCM56248_B1",
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Katana 2 4.A0 */
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        "BCM56450_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 4.B0 */
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        "BCM56450_B0",
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 4.B1*/
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        "BCM56450_B1",
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Katana 2 5.A0 */
        BCM56452_DEVICE_ID, BCM56452_A0_REV_ID,
        "BCM56452_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 5.B0 */
        BCM56452_DEVICE_ID, BCM56452_B0_REV_ID,
        "BCM56452_B0",
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 5.B1 */
        BCM56452_DEVICE_ID, BCM56452_B1_REV_ID,
        "BCM56452_B1",
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Katana 2 6.A0 */
        BCM56454_DEVICE_ID, BCM56454_A0_REV_ID,
        "BCM56454_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 6.B0 */
        BCM56454_DEVICE_ID, BCM56454_B0_REV_ID,
        "BCM56454_B0",
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 6.B1 */
        BCM56454_DEVICE_ID, BCM56454_B1_REV_ID,
        "BCM56454_B1",
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Katana 2 7.A0 */
        BCM56455_DEVICE_ID, BCM56455_A0_REV_ID,
        "BCM56455_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 7.B0 */
        BCM56455_DEVICE_ID, BCM56455_B0_REV_ID,
        "BCM56455_B0",
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 7.B1 */
        BCM56455_DEVICE_ID, BCM56455_B1_REV_ID,
        "BCM56455_B1",
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Katana 2 8.A0 */
        BCM56456_DEVICE_ID, BCM56456_A0_REV_ID,
        "BCM56456_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 8.B0 */
        BCM56456_DEVICE_ID, BCM56456_B0_REV_ID,
        "BCM56456_B0",
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 8.B1 */
        BCM56456_DEVICE_ID, BCM56456_B1_REV_ID,
        "BCM56456_B1",
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Katana 2 9.A0 */
        BCM56457_DEVICE_ID, BCM56457_A0_REV_ID,
        "BCM56457_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 9.B0 */
        BCM56457_DEVICE_ID, BCM56457_B0_REV_ID,
        "BCM56457_B0",
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 9.B1 */
        BCM56457_DEVICE_ID, BCM56457_B1_REV_ID,
        "BCM56457_B1",
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Katana 2 10.A0 */
        BCM56458_DEVICE_ID, BCM56458_A0_REV_ID,
        "BCM56458_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 10.B0 */
        BCM56458_DEVICE_ID, BCM56458_B0_REV_ID,
        "BCM56458_B0",
        BCM56450_DEVICE_ID, BCM56450_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2 10.B1 */
        BCM56458_DEVICE_ID, BCM56458_B1_REV_ID,
        "BCM56458_B1",
        BCM56450_DEVICE_ID, BCM56450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_SABER2_SUPPORT)
    {   /* Saber 2 1.A0 */
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        "BCM56260_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 1.B0 */
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        "BCM56260_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 2.A0 */
        BCM56261_DEVICE_ID, BCM56261_A0_REV_ID,
        "BCM56261_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 2.B0 */
        BCM56261_DEVICE_ID, BCM56261_B0_REV_ID,
        "BCM56261_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    
    {   /* Saber 2 3.A0 */
        BCM56262_DEVICE_ID, BCM56262_A0_REV_ID,
        "BCM56262_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 3.B0 */
        BCM56262_DEVICE_ID, BCM56262_B0_REV_ID,
        "BCM56262_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 4.A0 */
        BCM56263_DEVICE_ID, BCM56263_A0_REV_ID,
        "BCM56263_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 4.B0 */
        BCM56263_DEVICE_ID, BCM56263_B0_REV_ID,
        "BCM56263_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 5.A0 */
        BCM56265_DEVICE_ID, BCM56265_A0_REV_ID,
        "BCM56265_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 5.B0 */
        BCM56265_DEVICE_ID, BCM56265_B0_REV_ID,
        "BCM56265_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 6.A0 */
        BCM56266_DEVICE_ID, BCM56266_A0_REV_ID,
        "BCM56266_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 6.B0 */
        BCM56266_DEVICE_ID, BCM56266_B0_REV_ID,
        "BCM56266_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    
    {   /* Saber 2 7.A0 */
        BCM56267_DEVICE_ID, BCM56267_A0_REV_ID,
        "BCM56267_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 7.B0 */
        BCM56267_DEVICE_ID, BCM56267_B0_REV_ID,
        "BCM56267_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 8.A0 */
        BCM56268_DEVICE_ID, BCM56268_A0_REV_ID,
        "BCM56268_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 8.B0 */
        BCM56268_DEVICE_ID, BCM56268_B0_REV_ID,
        "BCM56268_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 9.A0 */
        BCM56460_DEVICE_ID, BCM56460_A0_REV_ID,
        "BCM56460_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 9.B0 */
        BCM56460_DEVICE_ID, BCM56460_B0_REV_ID,
        "BCM56460_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    
    {   /* Saber 2 10.A0 */
        BCM56461_DEVICE_ID, BCM56461_A0_REV_ID,
        "BCM56461_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 10.B0 */
        BCM56461_DEVICE_ID, BCM56461_B0_REV_ID,
        "BCM56461_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 11.A0 */
        BCM56462_DEVICE_ID, BCM56462_A0_REV_ID,
        "BCM56462_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 11.B0 */
        BCM56462_DEVICE_ID, BCM56462_B0_REV_ID,
        "BCM56462_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 12.A0 */
        BCM56463_DEVICE_ID, BCM56463_A0_REV_ID,
        "BCM56463_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 12.B0 */
        BCM56463_DEVICE_ID, BCM56463_B0_REV_ID,
        "BCM56463_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 13.A0 */
        BCM56465_DEVICE_ID, BCM56465_A0_REV_ID,
        "BCM56465_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 13.B0 */
        BCM56465_DEVICE_ID, BCM56465_B0_REV_ID,
        "BCM56465_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 14.A0 */
        BCM56466_DEVICE_ID, BCM56466_A0_REV_ID,
        "BCM56466_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 14.B0 */
        BCM56466_DEVICE_ID, BCM56466_B0_REV_ID,
        "BCM56466_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 15.A0 */
        BCM56467_DEVICE_ID, BCM56467_A0_REV_ID,
        "BCM56467_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 15.B0 */
        BCM56467_DEVICE_ID, BCM56467_B0_REV_ID,
        "BCM56467_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Saber 2 16.A0 */
        BCM56468_DEVICE_ID, BCM56468_A0_REV_ID,
        "BCM56468_A0",
        BCM56260_DEVICE_ID, BCM56260_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber 2 16.B0 */
        BCM56468_DEVICE_ID, BCM56468_B0_REV_ID,
        "BCM56468_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Dagger 2 17.B0 */
        BCM56233_DEVICE_ID, BCM56233_B0_REV_ID,
        "BCM56233_B0",
        BCM56260_DEVICE_ID, BCM56260_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_METROLITE_SUPPORT)
    {   /* Metrolite */
        BCM56270_DEVICE_ID, BCM56270_A0_REV_ID,
        "BCM56270_A0",
        BCM56270_DEVICE_ID, BCM56270_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Metrolite */
        BCM56271_DEVICE_ID, BCM56271_A0_REV_ID,
        "BCM56271_A0",
        BCM56270_DEVICE_ID, BCM56270_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Metrolite */
        BCM56272_DEVICE_ID, BCM56272_A0_REV_ID,
        "BCM56272_A0",
        BCM56270_DEVICE_ID, BCM56270_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Beagle */
        BCM53460_DEVICE_ID, BCM53460_A0_REV_ID,
        "BCM53460_A0",
        BCM56270_DEVICE_ID, BCM56270_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Beagle */
        BCM53461_DEVICE_ID, BCM53461_A0_REV_ID,
        "BCM53461_A0",
        BCM56270_DEVICE_ID, BCM56270_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

#endif

#if defined(BCM_TRIDENT2_SUPPORT)
    {   /* Trident 2 */
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        "BCM56850_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56850_DEVICE_ID, BCM56850_A1_REV_ID,
        "BCM56850_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56850_DEVICE_ID, BCM56850_A2_REV_ID,
        "BCM56850_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56851_DEVICE_ID, BCM56851_A0_REV_ID,
        "BCM56851_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56851_DEVICE_ID, BCM56851_A1_REV_ID,
        "BCM56851_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56851_DEVICE_ID, BCM56851_A2_REV_ID,
        "BCM56851_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56852_DEVICE_ID, BCM56852_A0_REV_ID,
        "BCM56852_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56852_DEVICE_ID, BCM56852_A1_REV_ID,
        "BCM56852_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56852_DEVICE_ID, BCM56852_A2_REV_ID,
        "BCM56852_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56853_DEVICE_ID, BCM56853_A0_REV_ID,
        "BCM56853_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56853_DEVICE_ID, BCM56853_A1_REV_ID,
        "BCM56853_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56853_DEVICE_ID, BCM56853_A2_REV_ID,
        "BCM56853_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56854_DEVICE_ID, BCM56854_A0_REV_ID,
        "BCM56854_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56854_DEVICE_ID, BCM56854_A1_REV_ID,
        "BCM56854_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56854_DEVICE_ID, BCM56854_A2_REV_ID,
        "BCM56854_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56855_DEVICE_ID, BCM56855_A0_REV_ID,
        "BCM56855_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56855_DEVICE_ID, BCM56855_A1_REV_ID,
        "BCM56855_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56855_DEVICE_ID, BCM56855_A2_REV_ID,
        "BCM56855_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56834_DEVICE_ID, BCM56834_A0_REV_ID,
        "BCM56834_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56834_DEVICE_ID, BCM56834_A1_REV_ID,
        "BCM56834_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56834_DEVICE_ID, BCM56834_A2_REV_ID,
        "BCM56834_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan 2 */
        BCM56750_DEVICE_ID, BCM56750_A0_REV_ID,
        "BCM56750_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan 2 */
        BCM56750_DEVICE_ID, BCM56750_A1_REV_ID,
        "BCM56750_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan 2 */
        BCM56750_DEVICE_ID, BCM56750_A2_REV_ID,
        "BCM56750_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion 960 */
        BCM56830_DEVICE_ID, BCM56830_A0_REV_ID,
        "BCM56830_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion 960 */
        BCM56830_DEVICE_ID, BCM56830_A1_REV_ID,
        "BCM56830_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion 960 */
        BCM56830_DEVICE_ID, BCM56830_A2_REV_ID,
        "BCM56830_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_TRIDENT2_SUPPORT */

#if defined(BCM_TOMAHAWK_SUPPORT)
    {   /* Tomahawk */
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        "BCM56960_A0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk B0*/
        BCM56960_DEVICE_ID, BCM56960_B0_REV_ID,
        "BCM56960_B0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk B1*/
        BCM56960_DEVICE_ID, BCM56960_B1_REV_ID,
        "BCM56960_B1",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk */
        BCM56961_DEVICE_ID, BCM56961_A0_REV_ID,
        "BCM56961_A0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk B0*/
        BCM56961_DEVICE_ID, BCM56961_B0_REV_ID,
        "BCM56961_B0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk B1*/
        BCM56961_DEVICE_ID, BCM56961_B1_REV_ID,
        "BCM56961_B1",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk */
        BCM56962_DEVICE_ID, BCM56962_A0_REV_ID,
        "BCM56962_A0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk B0*/
        BCM56962_DEVICE_ID, BCM56962_B0_REV_ID,
        "BCM56962_B0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk B1*/
        BCM56962_DEVICE_ID, BCM56962_B1_REV_ID,
        "BCM56962_B1",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk */
        BCM56963_DEVICE_ID, BCM56963_A0_REV_ID,
        "BCM56963_A0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk B0*/
        BCM56963_DEVICE_ID, BCM56963_B0_REV_ID,
        "BCM56963_B0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk B1*/
        BCM56963_DEVICE_ID, BCM56963_B1_REV_ID,
        "BCM56963_B1",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk */
        BCM56930_DEVICE_ID, BCM56930_A0_REV_ID,
        "BCM56930_A0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk B0*/
        BCM56930_DEVICE_ID, BCM56930_B0_REV_ID,
        "BCM56930_B0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk B1*/
        BCM56930_DEVICE_ID, BCM56930_B1_REV_ID,
        "BCM56930_B1",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titanhawk */
        BCM56968_DEVICE_ID, BCM56968_A0_REV_ID,
        "BCM56968_A0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titanhawk B0*/
        BCM56968_DEVICE_ID, BCM56968_B0_REV_ID,
        "BCM56968_B0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titanhawk B1*/
        BCM56968_DEVICE_ID, BCM56968_B1_REV_ID,
        "BCM56968_B1",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger3+ */
        BCM56168_DEVICE_ID, BCM56168_A0_REV_ID,
        "BCM56168_A0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger3+ B0 */
        BCM56168_DEVICE_ID, BCM56168_B0_REV_ID,
        "BCM56168_B0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger3+ B1 */
        BCM56168_DEVICE_ID, BCM56168_B1_REV_ID,
        "BCM56168_B1",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger3+ */
        BCM56169_DEVICE_ID, BCM56169_A0_REV_ID,
        "BCM56169_A0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger3+ B0 */
        BCM56169_DEVICE_ID, BCM56169_B0_REV_ID,
        "BCM56169_B0",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger3+ B1 */
        BCM56169_DEVICE_ID, BCM56169_B1_REV_ID,
        "BCM56169_B1",
        BCM56960_DEVICE_ID, BCM56960_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_TOMAHAWK_SUPPORT */

#if defined(BCM_TOMAHAWKPLUS_SUPPORT)
    {   /* Tomahawk+ */
        BCM56965_DEVICE_ID, BCM56965_A0_REV_ID,
        "BCM56965_A0",
        BCM56965_DEVICE_ID, BCM56965_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk+ */
        BCM56969_DEVICE_ID, BCM56969_A0_REV_ID,
        "BCM56969_A0",
        BCM56965_DEVICE_ID, BCM56965_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk+ */
        BCM56966_DEVICE_ID, BCM56966_A0_REV_ID,
        "BCM56966_A0",
        BCM56965_DEVICE_ID, BCM56965_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk+ */
        BCM56967_DEVICE_ID, BCM56967_A0_REV_ID,
        "BCM56967_A0",
        BCM56965_DEVICE_ID, BCM56965_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk+ */
        BCM56965_DEVICE_ID, BCM56965_A1_REV_ID,
        "BCM56965_A1",
        BCM56965_DEVICE_ID, BCM56965_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk+ */
        BCM56969_DEVICE_ID, BCM56965_A1_REV_ID,
        "BCM56969_A1",
        BCM56965_DEVICE_ID, BCM56965_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk+ */
        BCM56966_DEVICE_ID, BCM56965_A1_REV_ID,
        "BCM56966_A1",
        BCM56965_DEVICE_ID, BCM56965_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk+ */
        BCM56967_DEVICE_ID, BCM56965_A1_REV_ID,
        "BCM56967_A1",
        BCM56965_DEVICE_ID, BCM56965_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

#endif /* BCM_TOMAHAWKPLUS_SUPPORT */

#if defined(BCM_TOMAHAWK2_SUPPORT)
    {   /* Tomahawk 2 */
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        "BCM56970_A0",
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 2 */
        BCM56971_DEVICE_ID, BCM56971_A0_REV_ID,
        "BCM56971_A0",
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 2 */
        BCM56972_DEVICE_ID, BCM56972_A0_REV_ID,
        "BCM56972_A0",
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 2 */
        BCM56974_DEVICE_ID, BCM56974_A0_REV_ID,
        "BCM56974_A0",
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titanhawk 2 */
        BCM56975_DEVICE_ID, BCM56975_A0_REV_ID,
        "BCM56975_A0",
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 2 B0*/
        BCM56970_DEVICE_ID, BCM56970_B0_REV_ID,
        "BCM56970_B0",
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 2 B0*/
        BCM56971_DEVICE_ID, BCM56971_B0_REV_ID,
        "BCM56971_B0",
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 2 B0*/
        BCM56972_DEVICE_ID, BCM56972_B0_REV_ID,
        "BCM56972_B0",
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 2 B0*/
        BCM56974_DEVICE_ID, BCM56974_B0_REV_ID,
        "BCM56974_B0",
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titanhawk 2 B0*/
        BCM56975_DEVICE_ID, BCM56975_B0_REV_ID,
        "BCM56975_B0",
        BCM56970_DEVICE_ID, BCM56970_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_TOMAHAWK2_SUPPORT */

#if defined(BCM_TOMAHAWK3_SUPPORT)
    {   /* Tomahawak 3*/
        BCM56980_DEVICE_ID, BCM56980_A0_REV_ID,
        "BCM56980_A0",
        BCM56980_DEVICE_ID, BCM56980_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawak 3*/
        BCM56981_DEVICE_ID, BCM56981_A0_REV_ID,
        "BCM56981_A0",
        BCM56980_DEVICE_ID, BCM56980_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 3 */
        BCM56982_DEVICE_ID, BCM56982_A0_REV_ID,
        "BCM56982_A0",
        BCM56980_DEVICE_ID, BCM5698_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 3 */
        BCM56983_DEVICE_ID, BCM56983_A0_REV_ID,
        "BCM56983_A0",
        BCM56980_DEVICE_ID, BCM5698_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 3 */
        BCM56984_DEVICE_ID, BCM56984_A0_REV_ID,
        "BCM56984_A0",
        BCM56980_DEVICE_ID, BCM5698_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 3 B0*/
        BCM56980_DEVICE_ID, BCM56980_B0_REV_ID,
        "BCM56980_B0",
        BCM56980_DEVICE_ID, BCM56980_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 3 56983 B0*/
        BCM56983_DEVICE_ID, BCM56983_B0_REV_ID,
        "BCM56983_B0",
        BCM56980_DEVICE_ID, BCM5698_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 3 56982 B0 */
        BCM56982_DEVICE_ID, BCM56982_B0_REV_ID,
        "BCM56982_B0",
        BCM56980_DEVICE_ID, BCM5698_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Tomahawk 3 56984 B0*/
        BCM56984_DEVICE_ID, BCM56984_B0_REV_ID,
        "BCM56984_B0",
        BCM56980_DEVICE_ID, BCM5698_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_TOMAHAWK3_SUPPORT */

#if defined(BCM_TRIDENT2PLUS_SUPPORT)
    {   /* Trident 2 Plus */
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        "BCM56860_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56861_DEVICE_ID, BCM56861_A0_REV_ID,
        "BCM56861_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56862_DEVICE_ID, BCM56862_A0_REV_ID,
        "BCM56862_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56864_DEVICE_ID, BCM56864_A0_REV_ID,
        "BCM56864_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56865_DEVICE_ID, BCM56865_A0_REV_ID,
        "BCM56865_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56866_DEVICE_ID, BCM56866_A0_REV_ID,
        "BCM56866_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56867_DEVICE_ID, BCM56867_A0_REV_ID,
        "BCM56867_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56868_DEVICE_ID, BCM56868_A0_REV_ID,
        "BCM56868_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56832_DEVICE_ID, BCM56832_A0_REV_ID,
        "BCM56832_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56833_DEVICE_ID, BCM56833_A0_REV_ID,
        "BCM56833_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56836_DEVICE_ID, BCM56836_A0_REV_ID,
        "BCM56836_A0",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56860_DEVICE_ID, BCM56860_A1_REV_ID,
        "BCM56860_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56861_DEVICE_ID, BCM56861_A1_REV_ID,
        "BCM56861_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56862_DEVICE_ID, BCM56862_A1_REV_ID,
        "BCM56862_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56864_DEVICE_ID, BCM56864_A1_REV_ID,
        "BCM56864_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56865_DEVICE_ID, BCM56865_A1_REV_ID,
        "BCM56865_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56866_DEVICE_ID, BCM56866_A1_REV_ID,
        "BCM56866_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56867_DEVICE_ID, BCM56867_A1_REV_ID,
        "BCM56867_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56868_DEVICE_ID, BCM56868_A1_REV_ID,
        "BCM56868_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56832_DEVICE_ID, BCM56832_A1_REV_ID,
        "BCM56832_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56833_DEVICE_ID, BCM56833_A1_REV_ID,
        "BCM56833_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 Plus */
        BCM56836_DEVICE_ID, BCM56836_A1_REV_ID,
        "BCM56836_A1",
        BCM56860_DEVICE_ID, BCM56860_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_TRIDENT2PLUS_SUPPORT */

#if defined(BCM_TRIDENT3_SUPPORT)
    {   /* Trident3 */
        BCM56870_DEVICE_ID, BCM56870_A0_REV_ID,
        "BCM56870_A0",
        BCM56870_DEVICE_ID, BCM56870_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident3 2T SKU */
        BCM56873_DEVICE_ID, BCM56873_A0_REV_ID,
        "BCM56873_A0",
        BCM56870_DEVICE_ID, BCM56870_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_TRIDENT3_SUPPORT */

#if defined(BCM_HELIX5_SUPPORT)
    {   /* Helix5 */
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        "BCM56370_A0",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56371_DEVICE_ID, BCM56371_A0_REV_ID,
        "BCM56371_A0",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56372_DEVICE_ID, BCM56372_A0_REV_ID,
        "BCM56372_A0",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56374_DEVICE_ID, BCM56374_A0_REV_ID,
        "BCM56374_A0",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56375_DEVICE_ID, BCM56375_A0_REV_ID,
        "BCM56375_A0",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56376_DEVICE_ID, BCM56376_A0_REV_ID,
        "BCM56376_A0",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56377_DEVICE_ID, BCM56377_A0_REV_ID,
        "BCM56377_A0",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56577_DEVICE_ID, BCM56577_A0_REV_ID,
        "BCM56577_A0",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56578_DEVICE_ID, BCM56578_A0_REV_ID,
        "BCM56578_A0",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56579_DEVICE_ID, BCM56579_A0_REV_ID,
        "BCM56579_A0",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56370_DEVICE_ID, BCM56370_A1_REV_ID,
        "BCM56370_A1",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56371_DEVICE_ID, BCM56371_A1_REV_ID,
        "BCM56371_A1",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56372_DEVICE_ID, BCM56372_A1_REV_ID,
        "BCM56372_A1",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56374_DEVICE_ID, BCM56374_A1_REV_ID,
        "BCM56374_A1",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56375_DEVICE_ID, BCM56375_A1_REV_ID,
        "BCM56375_A1",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56376_DEVICE_ID, BCM56376_A1_REV_ID,
        "BCM56376_A1",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56377_DEVICE_ID, BCM56377_A1_REV_ID,
        "BCM56377_A1",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56577_DEVICE_ID, BCM56577_A1_REV_ID,
        "BCM56577_A1",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56578_DEVICE_ID, BCM56578_A1_REV_ID,
        "BCM56578_A1",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56579_DEVICE_ID, BCM56579_A1_REV_ID,
        "BCM56579_A1",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56370_DEVICE_ID, BCM56370_A2_REV_ID,
        "BCM56370_A2",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56371_DEVICE_ID, BCM56371_A2_REV_ID,
        "BCM56371_A2",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56372_DEVICE_ID, BCM56372_A2_REV_ID,
        "BCM56372_A2",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56374_DEVICE_ID, BCM56374_A2_REV_ID,
        "BCM56374_A2",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56375_DEVICE_ID, BCM56375_A2_REV_ID,
        "BCM56375_A2",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56376_DEVICE_ID, BCM56376_A2_REV_ID,
        "BCM56376_A2",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56377_DEVICE_ID, BCM56377_A2_REV_ID,
        "BCM56377_A2",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56577_DEVICE_ID, BCM56577_A2_REV_ID,
        "BCM56577_A2",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56578_DEVICE_ID, BCM56578_A2_REV_ID,
        "BCM56578_A2",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix5 */
        BCM56579_DEVICE_ID, BCM56579_A2_REV_ID,
        "BCM56579_A2",
        BCM56370_DEVICE_ID, BCM56370_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

#endif /* BCM_HELIX5_SUPPORT */

#if defined(BCM_MAVERICK2_SUPPORT)
    {   /* Maverick2 */
        BCM56770_DEVICE_ID, BCM56770_A0_REV_ID,
        "BCM56770_A0",
        BCM56770_DEVICE_ID, BCM56770_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick2 */
        BCM56771_DEVICE_ID, BCM56771_A0_REV_ID,
        "BCM56771_A0",
        BCM56770_DEVICE_ID, BCM56770_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_MAVERICK2_SUPPORT */

#if defined(BCM_FIREBOLT6_SUPPORT)
    {   /* FIREBOLT6 */
        BCM56470_DEVICE_ID, BCM56470_A0_REV_ID,
        "BCM56470_A0",
        BCM56470_DEVICE_ID, BCM56470_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FIREBOLT6 */
        BCM56471_DEVICE_ID, BCM56471_A0_REV_ID,
        "BCM56471_A0",
        BCM56470_DEVICE_ID, BCM56470_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FIREBOLT6 */
        BCM56472_DEVICE_ID, BCM56472_A0_REV_ID,
        "BCM56472_A0",
        BCM56470_DEVICE_ID, BCM56470_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FIREBOLT6 */
        BCM56475_DEVICE_ID, BCM56475_A0_REV_ID,
        "BCM56475_A0",
        BCM56470_DEVICE_ID, BCM56470_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FIREBOLT6 */
        BCM56474_DEVICE_ID, BCM56474_A0_REV_ID,
        "BCM56474_A0",
        BCM56470_DEVICE_ID, BCM56470_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

#endif /*BCM_FIREBOLT6_SUPPORT*/

#if defined(BCM_APACHE_SUPPORT)
    {   /* Apache */
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        "BCM56560_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apache B0 */
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        "BCM56560_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apache */
        BCM56561_DEVICE_ID, BCM56561_A0_REV_ID,
        "BCM56561_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apache B0 */
        BCM56561_DEVICE_ID, BCM56561_B0_REV_ID,
        "BCM56561_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apache */
        BCM56562_DEVICE_ID, BCM56562_A0_REV_ID,
        "BCM56562_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apache B0 */
        BCM56562_DEVICE_ID, BCM56562_B0_REV_ID,
        "BCM56562_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-5 */
        BCM56565_DEVICE_ID, BCM56565_A0_REV_ID,
        "BCM56565_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-5 B0 */
        BCM56565_DEVICE_ID, BCM56565_B0_REV_ID,
        "BCM56565_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-5 */
        BCM56566_DEVICE_ID, BCM56566_A0_REV_ID,
        "BCM56566_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-5 B0 */
        BCM56566_DEVICE_ID, BCM56566_B0_REV_ID,
        "BCM56566_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-5 */
        BCM56567_DEVICE_ID, BCM56567_A0_REV_ID,
        "BCM56567_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-5 B0 */
        BCM56567_DEVICE_ID, BCM56567_B0_REV_ID,
        "BCM56567_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-5 */
        BCM56568_DEVICE_ID, BCM56568_A0_REV_ID,
        "BCM56568_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-5 B0 */
        BCM56568_DEVICE_ID, BCM56568_B0_REV_ID,
        "BCM56568_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick */
        BCM56760_DEVICE_ID, BCM56760_A0_REV_ID,
        "BCM56760_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick B0 */
        BCM56760_DEVICE_ID, BCM56760_B0_REV_ID,
        "BCM56760_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick */
        BCM56761_DEVICE_ID, BCM56761_A0_REV_ID,
        "BCM56761_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick B0 */
        BCM56761_DEVICE_ID, BCM56761_B0_REV_ID,
        "BCM56761_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick */
        BCM56761_DEVICE_ID, BCM56761_A0_REV_ID,
        "BCM56761_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick B0 */
        BCM56761_DEVICE_ID, BCM56761_B0_REV_ID,
        "BCM56761_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick B1 */
        BCM56761_DEVICE_ID, BCM56761_B1_REV_ID,
        "BCM56761_B1",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick */
        BCM56762_DEVICE_ID, BCM56762_A0_REV_ID,
        "BCM56762_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick B0 */
        BCM56762_DEVICE_ID, BCM56762_B0_REV_ID,
        "BCM56762_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick */
        BCM56764_DEVICE_ID, BCM56764_A0_REV_ID,
        "BCM56764_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick B0 */
        BCM56764_DEVICE_ID, BCM56764_B0_REV_ID,
        "BCM56764_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick - TD2+ (50mmx50mm) */
        BCM56765_DEVICE_ID, BCM56765_A0_REV_ID,
        "BCM56765_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick B0 - TD2+ (50mmx50mm) */
        BCM56765_DEVICE_ID, BCM56765_B0_REV_ID,
        "BCM56765_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick - TD+ (50mmx50mm) */
        BCM56766_DEVICE_ID, BCM56766_A0_REV_ID,
        "BCM56766_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick B0 - TD+ (50mmx50mm) */
        BCM56766_DEVICE_ID, BCM56766_B0_REV_ID,
        "BCM56766_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick-880G */
        BCM56768_DEVICE_ID, BCM56768_A0_REV_ID,
        "BCM56768_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Maverick-880G B0 */
        BCM56768_DEVICE_ID, BCM56768_B0_REV_ID,
        "BCM56768_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger 2+ 880G */
        BCM56068_DEVICE_ID, BCM56068_A0_REV_ID,
        "BCM56068_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger 2+ B0 880G*/
        BCM56068_DEVICE_ID, BCM56068_B0_REV_ID,
        "BCM56068_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger 2+ 880G */
        BCM56068_DEVICE_ID, BCM56068_A0_REV_ID,
        "BCM56068_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger 2+ B0 880G*/
        BCM56068_DEVICE_ID, BCM56068_B0_REV_ID,
        "BCM56068_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger 2+ B1 880G*/
        BCM56068_DEVICE_ID, BCM56068_B1_REV_ID,
        "BCM56068_B1",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger 2+ */
        BCM56069_DEVICE_ID, BCM56069_A0_REV_ID,
        "BCM56069_A0",
        BCM56560_DEVICE_ID, BCM56560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger 2+ B0 */
        BCM56069_DEVICE_ID, BCM56069_B0_REV_ID,
        "BCM56069_B0",
        BCM56560_DEVICE_ID, BCM56560_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_APACHE_SUPPORT */
#if defined(BCM_MONTEREY_SUPPORT)
    {   /* Monterey */
        BCM56670_DEVICE_ID, BCM56670_A0_REV_ID,
        "BCM56670_A0",
        BCM56670_DEVICE_ID, BCM56670_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56671_DEVICE_ID, BCM56671_A0_REV_ID,
        "BCM56671_A0",
        BCM56670_DEVICE_ID, BCM56670_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56672_DEVICE_ID, BCM56672_A0_REV_ID,
        "BCM56672_A0",
        BCM56670_DEVICE_ID, BCM56672_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56675_DEVICE_ID, BCM56675_A0_REV_ID,
        "BCM56675_A0",
        BCM56670_DEVICE_ID, BCM56670_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56670_DEVICE_ID, BCM56670_B0_REV_ID,
        "BCM56670_B0",
        BCM56670_DEVICE_ID, BCM56670_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56671_DEVICE_ID, BCM56671_B0_REV_ID,
        "BCM56671_B0",
        BCM56670_DEVICE_ID, BCM56670_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56672_DEVICE_ID, BCM56672_B0_REV_ID,
        "BCM56672_B0",
        BCM56670_DEVICE_ID, BCM56670_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56675_DEVICE_ID, BCM56675_B0_REV_ID,
        "BCM56675_B0",
        BCM56670_DEVICE_ID, BCM56670_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56670_DEVICE_ID, BCM56670_C0_REV_ID,
        "BCM56670_C0",
        BCM56670_DEVICE_ID, BCM56670_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56671_DEVICE_ID, BCM56671_C0_REV_ID,
        "BCM56671_C0",
        BCM56670_DEVICE_ID, BCM56670_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56672_DEVICE_ID, BCM56672_C0_REV_ID,
        "BCM56672_C0",
        BCM56670_DEVICE_ID, BCM56670_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Monterey */
        BCM56675_DEVICE_ID, BCM56675_C0_REV_ID,
        "BCM56675_C0",
        BCM56670_DEVICE_ID, BCM56670_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_KSCPU_SUPPORT)
    /* CPU device */
    {
        BCM53000PCIE_DEVICE_ID, BCM53000_A0_REV_ID,
        "BCM53000_A0",
        BCM53000PCIE_DEVICE_ID, BCM53000_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_CPU_DEV_TYPE)
    },
#endif
#ifdef BCM_PETRA_SUPPORT
    {
        GEDI_DEVICE_ID, GEDI_REV_ID,
        "GEDI",
        GEDI_DEVICE_ID, GEDI_REV_ID,
        (SOC_EB_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        ARADPLUS_DEVICE_ID, ARADPLUS_A0_REV_ID,
        "BCM88660_A0",
        ARADPLUS_DEVICE_ID, ARADPLUS_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88350_DEVICE_ID, BCM88350_B1_REV_ID,
        "BCM88350_B1",
        BCM88350_DEVICE_ID, BCM88350_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88351_DEVICE_ID, BCM88351_B1_REV_ID,
        "BCM88351_B1",
        BCM88351_DEVICE_ID, BCM88351_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88450_DEVICE_ID, BCM88450_B1_REV_ID,
        "BCM88450_B1",
        BCM88450_DEVICE_ID, BCM88450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88451_DEVICE_ID, BCM88451_B1_REV_ID,
        "BCM88451_B1",
        BCM88451_DEVICE_ID, BCM88451_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88550_DEVICE_ID, BCM88550_B1_REV_ID,
        "BCM88550_B1",
        BCM88550_DEVICE_ID, BCM88550_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88551_DEVICE_ID, BCM88551_B1_REV_ID,
        "BCM88551_B1",
        BCM88551_DEVICE_ID, BCM88551_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
     {
        BCM88552_DEVICE_ID, BCM88552_B1_REV_ID,
        "BCM88552_B1",
        BCM88552_DEVICE_ID, BCM88552_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88360_DEVICE_ID, BCM88360_A0_REV_ID,
        "BCM88360_A0",
        BCM88360_DEVICE_ID, BCM88360_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88361_DEVICE_ID, BCM88361_A0_REV_ID,
        "BCM88361_A0",
        BCM88361_DEVICE_ID, BCM88361_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88363_DEVICE_ID, BCM88363_A0_REV_ID,
        "BCM88363_A0",
        BCM88363_DEVICE_ID, BCM88363_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88460_DEVICE_ID, BCM88460_A0_REV_ID,
        "BCM88460_A0",
        BCM88460_DEVICE_ID, BCM88460_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88461_DEVICE_ID, BCM88461_A0_REV_ID,
        "BCM88461_A0",
        BCM88461_DEVICE_ID, BCM88461_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88560_DEVICE_ID, BCM88560_A0_REV_ID,
        "BCM88560_A0",
        BCM88560_DEVICE_ID, BCM88560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88561_DEVICE_ID, BCM88561_A0_REV_ID,
        "BCM88561_A0",
        BCM88561_DEVICE_ID, BCM88561_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
     {
        BCM88562_DEVICE_ID, BCM88562_A0_REV_ID,
        "BCM88562_A0",
        BCM88562_DEVICE_ID, BCM88562_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88661_DEVICE_ID, BCM88661_A0_REV_ID,
        "BCM88661_A0",
        BCM88661_DEVICE_ID, BCM88661_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88664_DEVICE_ID, BCM88664_A0_REV_ID,
        "BCM88664_A0",
        BCM88664_DEVICE_ID, BCM88664_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        ACP_PCI_DEVICE_ID, ACP_PCI_REV_ID,
        "ACP",
        ACP_PCI_DEVICE_ID, ACP_PCI_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#ifdef BCM_JERICHO_SUPPORT
/* { */
    {
        JERICHO_DEVICE_ID, JERICHO_A0_REV_ID,
        "BCM88675_A0",
        JERICHO_DEVICE_ID, JERICHO_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        JERICHO_DEVICE_ID, JERICHO_B0_REV_ID,
        "BCM88675_B0",
        JERICHO_DEVICE_ID, JERICHO_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        JERICHO_DEVICE_ID, JERICHO_A1_REV_ID,
        "BCM88675_A1",
        JERICHO_DEVICE_ID, JERICHO_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88670_DEVICE_ID, BCM88670_A0_REV_ID,
        "BCM88670_A0",
        BCM88670_DEVICE_ID, BCM88670_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88670_DEVICE_ID, BCM88670_B0_REV_ID,
        "BCM88670_B0",
        BCM88670_DEVICE_ID, BCM88670_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88670_DEVICE_ID, BCM88670_A1_REV_ID,
        "BCM88670_A1",
        BCM88670_DEVICE_ID, BCM88670_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88671_DEVICE_ID, BCM88671_A0_REV_ID,
        "BCM88671_A0",
        BCM88671_DEVICE_ID, BCM88671_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88671_DEVICE_ID, BCM88671_B0_REV_ID,
        "BCM88671_B0",
        BCM88671_DEVICE_ID, BCM88671_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88671_DEVICE_ID, BCM88671_A1_REV_ID,
        "BCM88671_A1",
        BCM88671_DEVICE_ID, BCM88671_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88671M_DEVICE_ID, BCM88671M_A0_REV_ID,
        "BCM88671M_A0",
        BCM88671M_DEVICE_ID, BCM88671M_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88671M_DEVICE_ID, BCM88671M_B0_REV_ID,
        "BCM88671M_B0",
        BCM88671M_DEVICE_ID, BCM88671M_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88671M_DEVICE_ID, BCM88671M_A1_REV_ID,
        "BCM88671M_A1",
        BCM88671M_DEVICE_ID, BCM88671M_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88672_DEVICE_ID, BCM88672_A0_REV_ID,
        "BCM88672_A0",
        BCM88672_DEVICE_ID, BCM88672_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88672_DEVICE_ID, BCM88672_B0_REV_ID,
        "BCM88672_B0",
        BCM88672_DEVICE_ID, BCM88672_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88672_DEVICE_ID, BCM88672_A1_REV_ID,
        "BCM88672_A1",
        BCM88672_DEVICE_ID, BCM88672_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88673_DEVICE_ID, BCM88673_A0_REV_ID,
        "BCM88673_A0",
        BCM88673_DEVICE_ID, BCM88673_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88673_DEVICE_ID, BCM88673_B0_REV_ID,
        "BCM88673_B0",
        BCM88673_DEVICE_ID, BCM88673_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88673_DEVICE_ID, BCM88673_A1_REV_ID,
        "BCM88673_A1",
        BCM88673_DEVICE_ID, BCM88673_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88674_DEVICE_ID, BCM88674_A0_REV_ID,
        "BCM88674_A0",
        BCM88674_DEVICE_ID, BCM88674_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88674_DEVICE_ID, BCM88674_B0_REV_ID,
        "BCM88674_B0",
        BCM88674_DEVICE_ID, BCM88674_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88674_DEVICE_ID, BCM88674_A1_REV_ID,
        "BCM88674_A1",
        BCM88674_DEVICE_ID, BCM88674_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88675M_DEVICE_ID, BCM88675M_A0_REV_ID,
        "BCM88675M_A0",
        BCM88675M_DEVICE_ID, BCM88675M_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88675M_DEVICE_ID, BCM88675M_B0_REV_ID,
        "BCM88675M_B0",
        BCM88675M_DEVICE_ID, BCM88675M_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88675M_DEVICE_ID, BCM88675M_A1_REV_ID,
        "BCM88675M_A1",
        BCM88675M_DEVICE_ID, BCM88675M_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88676_DEVICE_ID, BCM88676_A0_REV_ID,
        "BCM88676_A0",
        BCM88676_DEVICE_ID, BCM88676_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88676_DEVICE_ID, BCM88676_B0_REV_ID,
        "BCM88676_B0",
        BCM88676_DEVICE_ID, BCM88676_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88676_DEVICE_ID, BCM88676_A1_REV_ID,
        "BCM88676_A1",
        BCM88676_DEVICE_ID, BCM88676_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88676M_DEVICE_ID, BCM88676M_A0_REV_ID,
        "BCM88676M_A0",
        BCM88676M_DEVICE_ID, BCM88676M_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88676M_DEVICE_ID, BCM88676M_B0_REV_ID,
        "BCM88676M_B0",
        BCM88676M_DEVICE_ID, BCM88676M_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88676M_DEVICE_ID, BCM88676M_A1_REV_ID,
        "BCM88676M_A1",
        BCM88676M_DEVICE_ID, BCM88676M_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88677_DEVICE_ID, BCM88677_A0_REV_ID,
        "BCM88677_A0",
        BCM88677_DEVICE_ID, BCM88677_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88677_DEVICE_ID, BCM88677_B0_REV_ID,
        "BCM88677_B0",
        BCM88677_DEVICE_ID, BCM88677_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88677_DEVICE_ID, BCM88677_A1_REV_ID,
        "BCM88677_A1",
        BCM88677_DEVICE_ID, BCM88677_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88678_DEVICE_ID, BCM88678_A0_REV_ID,
        "BCM88678_A0",
        BCM88678_DEVICE_ID, BCM88678_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88678_DEVICE_ID, BCM88678_B0_REV_ID,
        "BCM88678_B0",
        BCM88678_DEVICE_ID, BCM88678_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88678_DEVICE_ID, BCM88678_A1_REV_ID,
        "BCM88678_A1",
        BCM88678_DEVICE_ID, BCM88678_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88679_DEVICE_ID, BCM88679_A0_REV_ID,
        "BCM88679_A0",
        BCM88679_DEVICE_ID, BCM88679_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88679_DEVICE_ID, BCM88679_B0_REV_ID,
        "BCM88679_B0",
        BCM88679_DEVICE_ID, BCM88679_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88679_DEVICE_ID, BCM88679_A1_REV_ID,
        "BCM88679_A1",
        BCM88679_DEVICE_ID, BCM88679_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        QMX_DEVICE_ID, QMX_A0_REV_ID,
        "BCM88375_A0",
        QMX_DEVICE_ID, QMX_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        QMX_DEVICE_ID, QMX_B0_REV_ID,
        "BCM88375_B0",
        QMX_DEVICE_ID, QMX_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        QMX_DEVICE_ID, QMX_A1_REV_ID,
        "BCM88375_A1",
        QMX_DEVICE_ID, QMX_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88370_DEVICE_ID, BCM88370_A0_REV_ID,
        "BCM88370_A0",
        BCM88370_DEVICE_ID, BCM88370_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88370_DEVICE_ID, BCM88370_B0_REV_ID,
        "BCM88370_B0",
        BCM88370_DEVICE_ID, BCM88370_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88370_DEVICE_ID, BCM88370_A1_REV_ID,
        "BCM88370_A1",
        BCM88370_DEVICE_ID, BCM88370_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88371_DEVICE_ID, BCM88371_A0_REV_ID,
        "BCM88371_A0",
        BCM88371_DEVICE_ID, BCM88371_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88371_DEVICE_ID, BCM88371_B0_REV_ID,
        "BCM88371_B0",
        BCM88371_DEVICE_ID, BCM88371_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88371_DEVICE_ID, BCM88371_A1_REV_ID,
        "BCM88371_A1",
        BCM88371_DEVICE_ID, BCM88371_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88371M_DEVICE_ID, BCM88371M_A0_REV_ID,
        "BCM88371M_A0",
        BCM88371M_DEVICE_ID, BCM88371M_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88371M_DEVICE_ID, BCM88371M_B0_REV_ID,
        "BCM88371M_B0",
        BCM88371M_DEVICE_ID, BCM88371M_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88371M_DEVICE_ID, BCM88371M_A1_REV_ID,
        "BCM88371M_A1",
        BCM88371M_DEVICE_ID, BCM88371M_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88376_DEVICE_ID, BCM88376_A0_REV_ID,
        "BCM88376_A0",
        BCM88376_DEVICE_ID, BCM88376_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88376_DEVICE_ID, BCM88376_B0_REV_ID,
        "BCM88376_B0",
        BCM88376_DEVICE_ID, BCM88376_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88376_DEVICE_ID, BCM88376_A1_REV_ID,
        "BCM88376_A1",
        BCM88376_DEVICE_ID, BCM88376_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88376M_DEVICE_ID, BCM88376M_A0_REV_ID,
        "BCM88376M_A0",
        BCM88376M_DEVICE_ID, BCM88376M_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88376M_DEVICE_ID, BCM88376M_B0_REV_ID,
        "BCM88376M_B0",
        BCM88376M_DEVICE_ID, BCM88376M_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88376M_DEVICE_ID, BCM88376M_A1_REV_ID,
        "BCM88376M_A1",
        BCM88376M_DEVICE_ID, BCM88376M_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88377_DEVICE_ID, BCM88377_A0_REV_ID,
        "BCM88377_A0",
        BCM88377_DEVICE_ID, BCM88377_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88377_DEVICE_ID, BCM88377_B0_REV_ID,
        "BCM88377_B0",
        BCM88377_DEVICE_ID, BCM88377_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88377_DEVICE_ID, BCM88377_A1_REV_ID,
        "BCM88377_A1",
        BCM88377_DEVICE_ID, BCM88377_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88378_DEVICE_ID, BCM88378_A0_REV_ID,
        "BCM88378_A0",
        BCM88378_DEVICE_ID, BCM88378_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88378_DEVICE_ID, BCM88378_B0_REV_ID,
        "BCM88378_B0",
        BCM88378_DEVICE_ID, BCM88378_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88378_DEVICE_ID, BCM88378_A1_REV_ID,
        "BCM88378_A1",
        BCM88378_DEVICE_ID, BCM88378_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88379_DEVICE_ID, BCM88379_A0_REV_ID,
        "BCM88379_A0",
        BCM88379_DEVICE_ID, BCM88379_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88379_DEVICE_ID, BCM88379_B0_REV_ID,
        "BCM88379_B0",
        BCM88379_DEVICE_ID, BCM88379_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88379_DEVICE_ID, BCM88379_A1_REV_ID,
        "BCM88379_A1",
        BCM88379_DEVICE_ID, BCM88379_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88680_DEVICE_ID, BCM88680_A0_REV_ID,
        "BCM88680_A0",
        BCM88680_DEVICE_ID, BCM88680_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88680_DEVICE_ID, BCM88680_A1_REV_ID,
        "BCM88680_A1",
        BCM88680_DEVICE_ID, BCM88680_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88681_DEVICE_ID, BCM88680_A1_REV_ID,
        "BCM88681_A1",
        BCM88681_DEVICE_ID, BCM88680_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88682_DEVICE_ID, BCM88680_A1_REV_ID,
        "BCM88682_A1",
        BCM88682_DEVICE_ID, BCM88680_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88683_DEVICE_ID, BCM88680_A1_REV_ID,
        "BCM88683_A1",
        BCM88683_DEVICE_ID, BCM88680_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88684_DEVICE_ID, BCM88680_A1_REV_ID,
        "BCM88684_A1",
        BCM88684_DEVICE_ID, BCM88680_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88685_DEVICE_ID, BCM88680_A1_REV_ID,
        "BCM88685_A1",
        BCM88685_DEVICE_ID, BCM88680_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88687_DEVICE_ID, BCM88680_A1_REV_ID,
        "BCM88687_A1",
        BCM88687_DEVICE_ID, BCM88680_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88380_DEVICE_ID, BCM88680_A1_REV_ID,
        "BCM88380_A1",
        BCM88380_DEVICE_ID, BCM88680_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88381_DEVICE_ID, BCM88680_A1_REV_ID,
        "BCM88381_A1",
        BCM88381_DEVICE_ID, BCM88680_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88681_DEVICE_ID, BCM88681_A0_REV_ID,
        "BCM88681_A0",
        BCM88681_DEVICE_ID, BCM88681_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88682_DEVICE_ID, BCM88682_A0_REV_ID,
        "BCM88682_A0",
        BCM88682_DEVICE_ID, BCM88682_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88683_DEVICE_ID, BCM88683_A0_REV_ID,
        "BCM88683_A0",
        BCM88683_DEVICE_ID, BCM88683_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88684_DEVICE_ID, BCM88684_A0_REV_ID,
        "BCM88684_A0",
        BCM88684_DEVICE_ID, BCM88684_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88685_DEVICE_ID, BCM88685_A0_REV_ID,
        "BCM88685_A0",
        BCM88685_DEVICE_ID, BCM88685_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88687_DEVICE_ID, BCM88687_A0_REV_ID,
        "BCM88687_A0",
        BCM88687_DEVICE_ID, BCM88687_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88380_DEVICE_ID, BCM88380_A0_REV_ID,
        "BCM88380_A0",
        BCM88380_DEVICE_ID, BCM88380_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88381_DEVICE_ID, BCM88381_A0_REV_ID,
        "BCM88381_A0",
        BCM88381_DEVICE_ID, BCM88381_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        QAX_DEVICE_ID, QAX_A0_REV_ID,
        "BCM88470_A0",
        QAX_DEVICE_ID, QAX_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        QAX_DEVICE_ID, QAX_B0_REV_ID,
        "BCM88470_B0",
        QAX_DEVICE_ID, QAX_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88470P_DEVICE_ID, QAX_A0_REV_ID,
        "BCM88470P_A0",
        BCM88470P_DEVICE_ID, QAX_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88471_DEVICE_ID, QAX_A0_REV_ID,
        "BCM88471_A0",
        BCM88471_DEVICE_ID, QAX_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88471_DEVICE_ID, QAX_B0_REV_ID,
        "BCM88471_B0",
        BCM88471_DEVICE_ID, QAX_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88473_DEVICE_ID, QAX_A0_REV_ID,
        "BCM88473_A0",
        BCM88473_DEVICE_ID, QAX_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88474_DEVICE_ID, QAX_A0_REV_ID,
        "BCM88474_A0",
        BCM88474_DEVICE_ID, QAX_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88474_DEVICE_ID, QAX_B0_REV_ID,
        "BCM88474_B0",
        BCM88474_DEVICE_ID, QAX_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88474H_DEVICE_ID, QAX_A0_REV_ID,
        "BCM88474H_A0",
        BCM88474H_DEVICE_ID, QAX_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88474H_DEVICE_ID, QAX_B0_REV_ID,
        "BCM88474H_B0",
        BCM88474H_DEVICE_ID, QAX_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88476_DEVICE_ID, QAX_A0_REV_ID,
        "BCM88476_A0",
        BCM88476_DEVICE_ID, QAX_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88476_DEVICE_ID, QAX_B0_REV_ID,
        "BCM88476_B0",
        BCM88476_DEVICE_ID, QAX_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88477_DEVICE_ID, QAX_A0_REV_ID,
        "BCM88477_A0",
        BCM88477_DEVICE_ID, QAX_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88477_DEVICE_ID, QAX_B0_REV_ID,
        "BCM88477_B0",
        BCM88477_DEVICE_ID, QAX_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88479_DEVICE_ID, QAX_A0_REV_ID,
        "BCM88479_A0",
        BCM88479_DEVICE_ID, QAX_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88479_DEVICE_ID, QAX_B0_REV_ID,
        "BCM88479_B0",
        BCM88479_DEVICE_ID, QAX_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       QUX_DEVICE_ID, QUX_A0_REV_ID,
       "BCM88270_A0",
       QUX_DEVICE_ID, QUX_A0_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       QUX_DEVICE_ID, QUX_A1_REV_ID,
       "BCM88270_A1",
       QUX_DEVICE_ID, QUX_A1_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88271_DEVICE_ID, QUX_A1_REV_ID,
       "BCM88271_A1",
       BCM88271_DEVICE_ID, QUX_A1_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88272_DEVICE_ID, QUX_A0_REV_ID,
       "BCM88272_A0",
       BCM88272_DEVICE_ID, QUX_A0_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88272_DEVICE_ID, QUX_A1_REV_ID,
       "BCM88272_A1",
       BCM88272_DEVICE_ID, QUX_A1_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88273_DEVICE_ID, QUX_A0_REV_ID,
       "BCM88273_A0",
       BCM88273_DEVICE_ID, QUX_A0_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88273_DEVICE_ID, QUX_A1_REV_ID,
       "BCM88273_A1",
       BCM88273_DEVICE_ID, QUX_A1_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88274_DEVICE_ID, QUX_A0_REV_ID,
       "BCM88274_A0",
       BCM88274_DEVICE_ID, QUX_A0_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88274_DEVICE_ID, QUX_A1_REV_ID,
       "BCM88274_A1",
       BCM88274_DEVICE_ID, QUX_A1_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88276_DEVICE_ID, QUX_A1_REV_ID,
       "BCM88276_A1",
       BCM88276_DEVICE_ID, QUX_A1_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88278_DEVICE_ID, QUX_A0_REV_ID,
       "BCM88278_A0",
       BCM88278_DEVICE_ID, QUX_A0_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88278_DEVICE_ID, QUX_A1_REV_ID,
       "BCM88278_A1",
       BCM88278_DEVICE_ID, QUX_A1_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
       BCM88279_DEVICE_ID, QUX_A1_REV_ID,
       "BCM88279_A1",
       BCM88279_DEVICE_ID, QUX_A1_REV_ID,
       (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
/* } */
#endif
#ifdef BCM_DFE_SUPPORT
/* { */
    {
        BCM88770_DEVICE_ID, BCM88770_A1_REV_ID,
        "BCM88770_A1",
        BCM88770_DEVICE_ID, BCM88770_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88773_DEVICE_ID, BCM88773_A1_REV_ID,
        "BCM88773_A1",
        BCM88773_DEVICE_ID, BCM88773_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88774_DEVICE_ID, BCM88774_A1_REV_ID,
        "BCM88774_A1",
        BCM88774_DEVICE_ID, BCM88774_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88775_DEVICE_ID, BCM88775_A1_REV_ID,
        "BCM88775_A1",
        BCM88775_DEVICE_ID, BCM88775_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88776_DEVICE_ID, BCM88776_A1_REV_ID,
        "BCM88776_A1",
        BCM88776_DEVICE_ID, BCM88776_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88777_DEVICE_ID, BCM88777_A1_REV_ID,
        "BCM88777_A1",
        BCM88777_DEVICE_ID, BCM88777_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88950_DEVICE_ID, BCM88950_A0_REV_ID,
        "BCM88950_A0",
        BCM88950_DEVICE_ID, BCM88950_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88950_DEVICE_ID, BCM88950_A1_REV_ID,
        "BCM88950_A1",
        BCM88950_DEVICE_ID, BCM88950_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88953_DEVICE_ID, BCM88953_A1_REV_ID,
        "BCM88953_A1",
        BCM88953_DEVICE_ID, BCM88953_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88954_DEVICE_ID, BCM88954_A1_REV_ID,
        "BCM88954_A1",
        BCM88954_DEVICE_ID, BCM88954_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88955_DEVICE_ID, BCM88955_A1_REV_ID,
        "BCM88955_A1",
        BCM88955_DEVICE_ID, BCM88955_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88956_DEVICE_ID, BCM88956_A1_REV_ID,
        "BCM88956_A1",
        BCM88956_DEVICE_ID, BCM88956_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88772_DEVICE_ID, BCM88772_A1_REV_ID,
        "BCM88772_A1",
        BCM88772_DEVICE_ID, BCM88772_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88952_DEVICE_ID, BCM88952_A0_REV_ID,
        "BCM88952_A0",
        BCM88952_DEVICE_ID, BCM88952_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88952_DEVICE_ID, BCM88952_A1_REV_ID,
        "BCM88952_A1",
        BCM88952_DEVICE_ID, BCM88952_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
/* } */
#endif
#ifdef BCM_DNX_SUPPORT
/* { */
    {
        BCM88690_DEVICE_ID, BCM88690_A0_REV_ID | SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT,
        "BCM88690_A0",
        BCM88690_DEVICE_ID, BCM88690_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88690_DEVICE_ID, BCM88690_B0_REV_ID | SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT,
        "BCM88690_B0",
        BCM88690_DEVICE_ID, BCM88690_B0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88690_DEVICE_ID, BCM88690_B1_REV_ID | SOC_CM_DEVICE_LARGER_REVID_AND_ANY_LAST_DEVID_DIGIT,
        "BCM88690_B1",
        BCM88690_DEVICE_ID, BCM88690_B1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88800_DEVICE_ID, BCM88800_A0_REV_ID | SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT,
        "BCM88800_A0",
        BCM88800_DEVICE_ID, BCM88800_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88800_DEVICE_ID, BCM88800_A1_REV_ID | SOC_CM_DEVICE_LARGER_REVID_AND_ANY_LAST_DEVID_DIGIT,
        "BCM88800_A1",
        BCM88800_DEVICE_ID, BCM88800_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88820_DEVICE_ID, DNXC_A0_REV_ID | SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT,
        "BCM88820_A0",
        BCM88820_DEVICE_ID, DNXC_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88820_DEVICE_ID, DNXC_A1_REV_ID | SOC_CM_DEVICE_LARGER_REVID_AND_ANY_LAST_DEVID_DIGIT,
        "BCM88820_A1",
        BCM88820_DEVICE_ID, DNXC_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88850_DEVICE_ID, DNXC_A0_REV_ID | SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT,
        "BCM88850_A0",
        BCM88850_DEVICE_ID, DNXC_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88850_DEVICE_ID, DNXC_A1_REV_ID | SOC_CM_DEVICE_LARGER_REVID_AND_ANY_LAST_DEVID_DIGIT,
        "BCM88850_A1",
        BCM88850_DEVICE_ID, DNXC_A1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88840_DEVICE_ID, DNXC_A0_REV_ID | SOC_CM_DEVICE_LARGER_REVID_AND_ANY_LAST_DEVID_DIGIT,
        "BCM88840_A0",
        BCM88840_DEVICE_ID, DNXC_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88830_DEVICE_ID, DNXC_A0_REV_ID | SOC_CM_DEVICE_LARGER_REVID_AND_ANY_LAST_DEVID_DIGIT,
        "BCM88830_A0",
        BCM88830_DEVICE_ID, DNXC_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88480_DEVICE_ID, BCM88480_A0_REV_ID | SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT,
        "BCM88480_A0",
        BCM88480_DEVICE_ID, BCM88480_A0_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88480_DEVICE_ID, BCM88480_B0_REV_ID | SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT,
        "BCM88480_B0",
        BCM88480_DEVICE_ID, DNXC_B1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88480_DEVICE_ID, BCM88480_B1_REV_ID | SOC_CM_DEVICE_LARGER_REVID_AND_ANY_LAST_DEVID_DIGIT,
        "BCM88480_B1",
        BCM88480_DEVICE_ID, DNXC_B1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88280_DEVICE_ID, DNXC_B1_REV_ID | SOC_CM_DEVICE_LARGER_REVID_AND_ANY_LAST_DEVID_DIGIT,
        "BCM88280_B1",
        BCM88280_DEVICE_ID, DNXC_B1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        BCM88290_DEVICE_ID, DNXC_B1_REV_ID | SOC_CM_DEVICE_LARGER_REVID_AND_ANY_LAST_DEVID_DIGIT,
        "BCM88290_B1",
        BCM88290_DEVICE_ID, DNXC_B1_REV_ID,
        (SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },

/* } */
#endif
#ifdef BCM_DNXF_SUPPORT
/* { */
    {
        BCM88790_DEVICE_ID, BCM88790_A0_REV_ID | SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT,
        "BCM88790_A0",
        BCM88790_DEVICE_ID, BCM88790_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88790_DEVICE_ID, DNXC_A1_REV_ID | SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT,
        "BCM88790_A1",
        BCM88790_DEVICE_ID, DNXC_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88790_DEVICE_ID, BCM88790_B0_REV_ID | SOC_CM_DEVICE_LARGER_REVID_AND_ANY_LAST_DEVID_DIGIT,
        "BCM88790_B0",
        BCM88790_DEVICE_ID, BCM88790_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
/* } */
#endif
#ifdef BCM_LTSW_SUPPORT
    /* ltsw_if_bcm56880_a0 */
    {   /* Trident4 */
        BCM56880_DEVICE_ID, BCM56880_A0_REV_ID,
        "BCM56880_A0",
        BCM56880_DEVICE_ID, BCM56880_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 */
        BCM56880_DEVICE_ID, BCM56880_B0_REV_ID,
        "BCM56880_B0",
        BCM56880_DEVICE_ID, BCM56880_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 */
        BCM56881_DEVICE_ID, BCM56881_A0_REV_ID,
        "BCM56881_A0",
        BCM56880_DEVICE_ID, BCM56880_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 */
        BCM56881_DEVICE_ID, BCM56881_B0_REV_ID,
        "BCM56881_B0",
        BCM56880_DEVICE_ID, BCM56880_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 */
        BCM56883_DEVICE_ID, BCM56883_A0_REV_ID,
        "BCM56883_A0",
        BCM56880_DEVICE_ID, BCM56880_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 */
        BCM56883_DEVICE_ID, BCM56883_B0_REV_ID,
        "BCM56883_B0",
        BCM56880_DEVICE_ID, BCM56880_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
    /* ltsw_if_bcm56990_a0 */
    {   /* Tomahawk4 */
        BCM56990_DEVICE_ID, BCM56990_A0_REV_ID,
        "BCM56990_A0",
        BCM56990_DEVICE_ID, BCM56990_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
    /* ltsw_if_bcm56990_b0 */
    {   /* Tomahawk4 */
        BCM56990_DEVICE_ID, BCM56990_B0_REV_ID,
        "BCM56990_B0",
        BCM56990_DEVICE_ID, BCM56990_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Tomahawk4 */
        BCM56991_DEVICE_ID, BCM56991_B0_REV_ID,
        "BCM56991_B0",
        BCM56990_DEVICE_ID, BCM56990_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Tomahawk4 */
        BCM56992_DEVICE_ID, BCM56992_B0_REV_ID,
        "BCM56992_B0",
        BCM56990_DEVICE_ID, BCM56990_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Tomahawk4 */
        BCM56993_DEVICE_ID, BCM56993_B0_REV_ID,
        "BCM56993_B0",
        BCM56990_DEVICE_ID, BCM56990_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
    /* ltsw_if_bcm56890_a0 */
    {   /* Trident4X11C */
        BCM56890_DEVICE_ID, BCM56890_A0_REV_ID,
        "BCM56890_A0",
        BCM56890_DEVICE_ID, BCM56890_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
#endif /* BCM_LTSW_SUPPORT */
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    /* xtsw_if_bcm56780_a0 */
    {   /* Trident4 X9 */
        BCM56780_DEVICE_ID, BCM56780_A0_REV_ID,
        "BCM56780_A0",
        BCM56780_DEVICE_ID, BCM56780_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 X9 */
        BCM56782_DEVICE_ID, BCM56782_A0_REV_ID,
        "BCM56782_A0",
        BCM56780_DEVICE_ID, BCM56780_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 X9 */
        BCM56784_DEVICE_ID, BCM56784_A0_REV_ID,
        "BCM56784_A0",
        BCM56780_DEVICE_ID, BCM56780_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 X9 */
        BCM56785_DEVICE_ID, BCM56785_A0_REV_ID,
        "BCM56785_A0",
        BCM56780_DEVICE_ID, BCM56780_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 X9 */
        BCM56786_DEVICE_ID, BCM56786_A0_REV_ID,
        "BCM56786_A0",
        BCM56780_DEVICE_ID, BCM56780_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 X9 */
        BCM56787_DEVICE_ID, BCM56787_A0_REV_ID,
        "BCM56787_A0",
        BCM56780_DEVICE_ID, BCM56780_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 X9 */
        BCM56788_DEVICE_ID, BCM56788_A0_REV_ID,
        "BCM56788_A0",
        BCM56780_DEVICE_ID, BCM56780_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Trident4 X9 */
        BCM56789_DEVICE_ID, BCM56789_A0_REV_ID,
        "BCM56789_A0",
        BCM56780_DEVICE_ID, BCM56780_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* xtsw_endif */
#endif /* BCM_LTSW_SUPPORT || BCM_CTSW_SUPPORT*/
#ifdef BCM_LTSW_SUPPORT
    /* ltsw_if_bcm56996_a0 */
    {   /* Tomahawk4G */
        BCM56996_DEVICE_ID, BCM56996_A0_REV_ID,
        "BCM56996_A0",
        BCM56996_DEVICE_ID, BCM56996_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Tomahawk4G */
        BCM56997_DEVICE_ID, BCM56997_A0_REV_ID,
        "BCM56997_A0",
        BCM56996_DEVICE_ID, BCM56996_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
    /* ltsw_if_bcm56996_b0 */
    {   /* Tomahawk4G */
        BCM56996_DEVICE_ID, BCM56996_B0_REV_ID,
        "BCM56996_B0",
        BCM56996_DEVICE_ID, BCM56996_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Tomahawk4G */
        BCM56997_DEVICE_ID, BCM56997_B0_REV_ID,
        "BCM56997_B0",
        BCM56996_DEVICE_ID, BCM56996_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
    /* ltsw_if_bcm56998_a0 */
    {   /* Tomahawk4GT */
        BCM56998_DEVICE_ID, BCM56998_A0_REV_ID,
        "BCM56998_A0",
        BCM56998_DEVICE_ID, BCM56998_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
    /* ltsw_if_bcm56999_a0 */
    {   /* Tomahawk4D */
        BCM56999_DEVICE_ID, BCM56999_A0_REV_ID,
        "BCM56999_A0",
        BCM56999_DEVICE_ID, BCM56999_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Tomahawk4D */
        BCM56995_DEVICE_ID, BCM56995_A0_REV_ID,
        "BCM56995_A0",
        BCM56999_DEVICE_ID, BCM56999_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
    /* ltsw_if_bcm78900_b0 */
    {   /* Tomahawk5 */
        BCM78900_DEVICE_ID, BCM78900_B0_REV_ID,
        "BCM78900_B0",
        BCM78900_DEVICE_ID, BCM78900_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
    /* ltsw_if_bcm56080_a0 */
    {   /* Pex1 */
        BCM56080_DEVICE_ID, BCM56080_A0_REV_ID,
        "BCM56080_A0",
        BCM56080_DEVICE_ID, BCM56080_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Pex1 */
        BCM56081_DEVICE_ID, BCM56081_A0_REV_ID,
        "BCM56081_A0",
        BCM56080_DEVICE_ID, BCM56080_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Pex1 */
        BCM56082_DEVICE_ID, BCM56082_A0_REV_ID,
        "BCM56082_A0",
        BCM56080_DEVICE_ID, BCM56080_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Pex1 */
        BCM56083_DEVICE_ID, BCM56083_A0_REV_ID,
        "BCM56083_A0",
        BCM56080_DEVICE_ID, BCM56080_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    {   /* Pex1 */
        BCM56084_DEVICE_ID, BCM56084_A0_REV_ID,
        "BCM56084_A0",
        BCM56080_DEVICE_ID, BCM56080_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
#endif /* BCM_LTSW_SUPPORT */
#ifdef BCM_LTSW_SUPPORT
    /* ltsw_if_bcm56690_a0 */
    {   /* Trident4X7 */
        BCM56690_DEVICE_ID, BCM56690_A0_REV_ID,
        "BCM56690_A0",
        BCM56690_DEVICE_ID, BCM56690_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_LTSW_DRV_TYPE)
    },
    /* ltsw_endif */
#endif /* BCM_LTSW_SUPPORT */
};


/*
 * Table of all recognized composite device types.
 *
 * There are fewer drivers than real chip IDs because some drivers
 * support more than one chip.  This table maps each real chip ID onto a
 * driver chip ID.  The driver IDs can be zero if equal to real IDs.
 *
 * Entries may be added to the table via soc_cm_id_to_driver_id_add().
 */

static soc_cm_comp_device_info_t soc_comp_device_info[] = {
    { /* prevent empty initializer braces which ISO C forbids */
        { 0, 0, NULL, 0, 0, 0},
        -1,
        0
    },
};


/* Various control structures */

static int                      _soc_cm_init = 0;

#define AINIT()                 if (_soc_cm_init == 0) return SOC_E_INIT

static sal_mutex_t              _soc_cm_lock = NULL;

#ifdef BROADCOM_DEBUG
static shared_block_t *head = NULL;
static char           *shared_start = (char *)~(size_t)0;
static char           *shared_end   = (char *)0;
static sal_spinlock_t  dl = NULL;
#define CM_DB_LOCK()   sal_spinlock_lock(dl)
#define CM_DB_UNLOCK() sal_spinlock_unlock(dl)
#define CM_BUF_SZ      128
static uint32 _soc_cm_debug_enable[SOC_MAX_NUM_DEVICES] = {0};
static uint32 _soc_cm_debug_op[SOC_MAX_NUM_DEVICES] = {0};
#endif

static int system_restore = 0;

/*
 * Function:    _soc_cm_find_device     (private)
 * Purpose:     Search the device table for matching device.
 *
 * Parameters:  dev_id - the device id of the device.
 *              rev_id - the revision id of the device.
 *
 * Returns:     NULL - device not found
 *              non-NULL - pointer to soc_cm_device_info_t table entry
 *
 * Note:        The return value is a pointer to soc_cm_device_info_t.
 *              Positive values are valid, and should not be interpreted as error.
 *              If no device is found, NULL is returned.
 *
 * Notes:       An exact match for metal spin is not required.
 *              This routine will return the driver with the highest
 *              available metal spin.  This allows the driver to run
 *              forward-compatibly on subsequent metal spins.
 */

static const soc_cm_device_info_t *
_soc_cm_find_device(uint16 dev_id, uint16 rev_id)
{
    int                 i, tries;
    uint16 device_info_rev_id;

    for (tries = 0; tries < 16; tries++) {
        for (i = 0; i < COUNTOF(soc_device_info); i++) {
            if ((soc_device_info[i].rev_id & ~SOC_CM_REVID_MASK) == 0) {
                if (soc_device_info[i].dev_id == dev_id &&
                    soc_device_info[i].rev_id == rev_id) {
                    return &soc_device_info[i];
                }
            } else { /* If flags fore device/revision ID are specified handle them and do not automatically any last hex digit of the revision ID */
                device_info_rev_id = soc_device_info[i].rev_id & SOC_CM_REVID_MASK;
                if (((soc_device_info[i].rev_id & SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT) ? /* compare device ID */
                    /* any device ID with (ID & 0xfff0) == (specified device ID) */
                    (((soc_device_info[i].dev_id ^ dev_id) & 0xfff0) == 0) :
                    (soc_device_info[i].dev_id == dev_id)) &&
                    ((soc_device_info[i].rev_id & SOC_CM_DEVICE_OR_LARGER_REVID) ? /* compare revision ID */
                    /* any revision with ID >= ((specified revID) && SOC_CM_REVID_MASK) && ID < 0xff */
                    (rev_id >= device_info_rev_id && rev_id < SOC_CM_REVID_MASK) :
                    (device_info_rev_id == rev_id))) {
                    return &soc_device_info[i];
                }
            }
        }
        if ((rev_id & 0xf) == 0) {
            rev_id |= 0xf;
        } else {
            rev_id--;
        }
    }

    return NULL;
}




/******************************************************************
 *
 *                      SOC CM CLIENT ROUTINES
 *
 * These routines are the CLIENT interface to the SOC configuration
 * manager. The driver itself may not ca    ll these functions.
 *
 *****************************************************************/


#if (SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
/* { */
/*
 * Function:    soc_cm_deinit
 * Purpose:     Deinitialize the SOC configuration manager interface
 * Parameters:  None
 *
 * Returns:     SOC_E_XXX
 */
int
soc_cm_deinit(void)
{
    _soc_cm_init = 0;

#ifdef BROADCOM_DEBUG
    if (dl) {
        sal_spinlock_destroy(dl);
    }
#endif
    if (_soc_cm_lock) {
        sal_mutex_destroy(_soc_cm_lock);
        _soc_cm_lock = NULL;
    }
    return SOC_E_NONE;
}
/* } */
#endif

/*
 * Function:    soc_cm_init
 * Purpose:     Initialize the SOC configuration manager interface
 *
 * Returns:     SOC_E_XXX
 *
 * Notes:
 */
int
soc_cm_init(void)
{
    if (_soc_cm_init == 0) {
        _soc_cm_lock = sal_mutex_create("cm lock");
        if (_soc_cm_lock == NULL) {
             LOG_ERROR(BSL_LS_SOC_COMMON,
                       (BSL_META("ERROR creating CM lock\n")));
             return SOC_E_MEMORY;
        }
        sal_memset(soc_cm_device, 0, sizeof(soc_cm_device));
        _soc_cm_init = 1;
    }

#ifdef BROADCOM_DEBUG
    if (!dl) {
        dl = sal_spinlock_create("cm debug");
    }
#endif

    return SOC_E_NONE;
}


#if (SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
/* { */
/*
 * Function:    soc_cm_device_name_get
 * Purpose:     Return the symbolic name of a device.
 *
 * Parameters:  dev_id - the device id of the device.
 *              rev_id - the revision id of the device.
 *
 * Returns:     Static string
 *
 * Note:        The return value is a device name.
 *              String values are valid, and should not be interpreted as error.
 *              If no device is found, "UNKNOWN" is returned.
 */

const char *
soc_cm_device_name_get(uint16 dev_id, uint8 rev_id)
{
    return soc_cm_get_device_name(dev_id, rev_id);
}
/* } */
#endif

/*
 * Function:    soc_cm_device_supported
 * Purpose:     Determines whether the specified chip ID is known.
 *
 * Parameters:  dev_id - the device id of the device.
 *              rev_id - the revision id of the device.
 *
 * Returns:     SOC_E_NONE if the device is known.
 *              SOC_E_UNAVAIL if the device is not known.
 */

int
soc_cm_device_supported(uint16 dev_id, uint8 rev_id)
{
    AINIT();

    if (_soc_cm_find_device(dev_id, rev_id) == NULL) {
        return SOC_E_UNAVAIL;
    }

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_find_comp_dev_info
 * Purpose:     Find the composite device information
 *
 * Parameters:  comp_dev_id - the composite device id of the device, as specified in the composite_units soc property.
 *
 * Returns:     pointer to the information structure if found, or NULL.
 */

const soc_cm_comp_device_info_t*
soc_cm_find_comp_dev_info(uint32 composite_dev_type)
{
    int i;

    for (i = 0; i < sizeof(soc_comp_device_info)/sizeof(soc_comp_device_info[0]); ++i) {
        if (soc_comp_device_info[i].comp_dev_id == composite_dev_type) {
            return soc_comp_device_info + i;
        }
    }
    return NULL;
}

/*
 * Function:    soc_cm_find_comp_dev_info_by_subdev
 * Purpose:     Find the composite device information
 *
 * Parameters:  sub_dev_id - the device id of the sub devices of the required composite device.
 *              comp_dev_id-  output:Compodsite Device ID as may be specified in the composite_units soc property
 *              nof_sub_devs- output: The number of sub devices
 *
 * Returns:     SOC_E_NONE if successful, negative if the composite device type was not found
 */

int
soc_cm_find_comp_dev_info_by_subdev(uint16 sub_dev_id, uint32 *comp_dev_id, unsigned *nof_sub_devs)
{
    int i;
    const soc_cm_comp_device_info_t *info;

    for (i = 0; i < sizeof(soc_comp_device_info)/sizeof(soc_comp_device_info[0]); ++i) {
        info = soc_comp_device_info + i;
        if (info->info.dev_id == sub_dev_id) {
            *comp_dev_id = info->comp_dev_id;
            *nof_sub_devs = info->nof_sub_devs;
            return SOC_E_NONE;
        }
    }
    return SOC_E_NOT_FOUND;
}

/*
 * Function:    soc_cm_get_nof_sub_devices
 * Purpose:     Check if the given input id a composite device ID, and if so return its number of sub-devices.
 *
 * Parameters:  comp_dev_id - the composite device id of the device.
 *
 * Returns:     The number of sub devices, or zero if the composite device type was not found.
 */

unsigned
soc_cm_get_nof_sub_devices(uint32 composite_dev_type)
{
    const soc_cm_comp_device_info_t *info = soc_cm_find_comp_dev_info(composite_dev_type);
    return info ? info->nof_sub_devs : 0;
}


/*
 * Function:    soc_cm_device_create_id
 * Purpose:     Create a driver device.
 *
 * Parameters:  dev_id - the (PCIe) device id of the device.
 *              rev_id - the (PCIe) revision id of the device.
 *              cookie - private client pointer you wish
 *                       to have passed back to you when
 *                       driver operations occur.
 *              unit   - The unit=logical device ID=CM device handle to use
 *                       for the device, or -1 to use any available one.
 *              bde_dev- The BDE device ID
 *
 * Returns:     On success, a none-negative unit=logical device ID=CM device
 *              handle is returned. None-negative values are not errors.
 *              Negative values indicate a SOC_E_XXX error.
 *
 * Notes:       See <soc/cmext.h> for a complete description
 *              of driver creation/initialization.
 */


int
soc_cm_device_create_id(uint16 dev_id, uint16 rev_id, void *cookie, int unit, int bde_dev)
{
    const soc_cm_device_info_t *info;
    cm_device_t null_device;
    int dev_idx;

    AINIT();

    /*
     * User must verify soc_cm_device_supported() before trying to
     * attach.
     */

    if ((info = _soc_cm_find_device(dev_id, rev_id)) == NULL) {
        return SOC_E_UNAVAIL;
    }

    sal_mutex_take(_soc_cm_lock, sal_mutex_FOREVER);

    /*  Allocate device id. */
    sal_memset(&null_device, 0, sizeof(cm_device_t));
    if (-1 == unit) {
        for (dev_idx = 0; dev_idx < SOC_MAX_NUM_DEVICES; dev_idx++) {
            if (0 == sal_memcmp(&CMDEV(dev_idx), &null_device,
                                sizeof(cm_device_t))) {
                unit = dev_idx;
                break;
            }
        }
        if (-1 == unit) {
            sal_mutex_give(_soc_cm_lock);
            return SOC_E_UNIT;
        }
    } else {
        if (0 != sal_memcmp(&CMDEV(unit), &null_device, sizeof(cm_device_t))) {
            sal_mutex_give(_soc_cm_lock);
            return SOC_E_EXISTS;
        }
    }

    /*
     * The chip ID passed by the user is not necessarily equal to that
     * in table, although it may differ ONLY by metal spin.
     */

    CMDEV(unit).dev.dev = bde_dev;
    CMDEV(unit).dev.info = info;
    CMDEV(unit).dev.cookie = cookie;
    CMDEV(unit).dev.dev_id = dev_id;           /* Record chip ID passed by user */
    CMDEV(unit).dev.rev_id = rev_id;
    CMDEV(unit).dev.composite_index = SOC_CM_NONE_COMPOSITE_DEV;

    soc_cm_device_count++;

    /* Keep soc_ndev in sync */
    soc_all_ndev = soc_cm_device_count;
    if (info->dev_type & SOC_SWITCH_DEV_TYPE) {
        if ((info->dev_type & SOC_SUB_DEV_TYPE) == 0) {
            SOC_NDEV_IDX2DEV(soc_ndev) = unit; /* add the unit to unit looping */
            soc_ndev++;
        }
        if (bde_dev >= 0 && bde_dev < SOC_MAX_NUM_DEVICES) { /* map from BDE device to unit */
            cm_bde_dev2unit[bde_dev] = unit;
        }
    }
    sal_mutex_give(_soc_cm_lock);
    return unit;
}


/*
 * Function:    soc_cm_device_create_composite
 * Purpose:     Create a driver device.
 *
 * Parameters:  composite_dev_type - the composite device type to create.
 *              sub_units - An Array of the existing sub-units of the composite device.
 *              cookie - private client pointer you wish to have passed back to you when
 *                       driver operations occur.
 *              comp_unit - unit for the created composite device.
 *
 * Returns:     SOC_E_XXX
 *
 * Note:        The return value is device handle.
 *              positive values are valid, and should not be interpreted as error.
 *              Negative values indicate an error.
 *
 */


int
soc_cm_device_create_composite(uint32 composite_dev_type, int *sub_units, void *cookie, int comp_unit)
{
    cm_device_t null_device;
    unsigned nof_sub_devs, composite_device_index;
    int unit, sub_dev_i, is_first = 1;
    uint16 subdev_dev_id = -1;
    uint8  subdev_rev_id = -1;
    const soc_cm_comp_device_info_t *comp_dev_info = soc_cm_find_comp_dev_info(composite_dev_type);

    AINIT();
    if (soc_cm_nof_composite_devices >= SOC_MAX_NOF_COMPOSITE_DEVS) {
        LOG_ERROR(BSL_LS_SOC_COMMON, (BSL_META("ERROR: too many composite devices\n")));
        return SOC_E_FULL;
    }

    /* check input */
    if (comp_dev_info == NULL) {
        LOG_ERROR(BSL_LS_SOC_COMMON, ("error: could not find composite device with ID %u as specified in %s\n", composite_dev_type, spn_COMPOSITE_UNITS));
        return SOC_E_UNAVAIL; /* could not find the given composite device type */
    } else if (comp_unit < 0 || comp_unit >= SOC_MAX_NUM_DEVICES) {
        return SOC_E_PARAM;
    }
    nof_sub_devs = comp_dev_info->nof_sub_devs;
    if (nof_sub_devs >= SOC_MAX_NOF_COMPOSITE_SUB_DEVS || nof_sub_devs < 2 ) {
        LOG_ERROR(BSL_LS_SOC_COMMON, ("error: incorrect number of sub-devices is configured for composite device type 0x%x\n", composite_dev_type));
        return SOC_E_FULL;
    }

    sal_memset(&null_device, 0, sizeof(cm_device_t));
    sal_mutex_take(_soc_cm_lock, sal_mutex_FOREVER);
    if (0 != sal_memcmp(&CMDEV(comp_unit), &null_device, sizeof(cm_device_t))) {
        comp_unit = SOC_E_EXISTS; /* specified device already exists */
        goto handle_error;
    }

    /* Check correctness of the sub_units input */
    for (sub_dev_i = 0; sub_dev_i < nof_sub_devs; ++sub_dev_i) {
        unit = sub_units[sub_dev_i];
        if (unit >= SOC_MAX_NUM_DEVICES || unit < 0) {
            LOG_ERROR(BSL_LS_SOC_COMMON, ("specified sub-device %d is not in range 0..%u\n", unit, SOC_MAX_NUM_DEVICES-1));
            comp_unit = SOC_E_PARAM;
            goto handle_error;
        } else if (CMDEV(unit).dev.composite_index != SOC_CM_NONE_COMPOSITE_DEV || !CMDEV(unit).dev.info) {
            LOG_ERROR(BSL_LS_SOC_COMMON, ("specified sub-device %d was not configured properly\n", unit));
            comp_unit = SOC_E_PARAM;
            goto handle_error;
        } else if ((CMDEV(unit).dev.info->dev_type & SOC_COMPOSITE_DEV_TYPE) != 0) {
            LOG_ERROR(BSL_LS_SOC_COMMON, ("specified sub-device %d is composite\n", unit));
            comp_unit = SOC_E_PARAM;
            goto handle_error;
        }
        /* test the sub-devices PCIe IDs */
        if (is_first) {
            subdev_dev_id = CMDEV(unit).dev.dev_id;
            subdev_rev_id = CMDEV(unit).dev.rev_id;
            is_first = 0;
            if (((subdev_dev_id ^ (uint16)composite_dev_type) & 0xfff0) != 0) {
                LOG_ERROR(BSL_LS_SOC_COMMON, ("unexpected PCIe device ID 0x%.4x was found for composite device 0x%x\n", (unsigned)subdev_dev_id, composite_dev_type));
                comp_unit = SOC_E_PARAM;
                goto handle_error;
            }
        } else if (subdev_dev_id != CMDEV(unit).dev.dev_id || subdev_rev_id != CMDEV(unit).dev.rev_id) {
            LOG_ERROR(BSL_LS_SOC_COMMON, ("sub-device PCIe device,revision IDs 0x%.4x,0x%.2x does not match the first sub device: 0x%.4x,0x%.2x\n",
              (unsigned)CMDEV(unit).dev.dev_id, (unsigned)CMDEV(unit).dev.rev_id, (unsigned)subdev_dev_id, (unsigned)subdev_rev_id));
            comp_unit = SOC_E_PARAM;
            goto handle_error;
        }
    }

    /* Finished testing, set the composite device data structures */
    /* First get the index in cm_composite_devices to use */
    if (soc_cm_nof_destroyed_composite_devices > 0 ) {
        composite_device_index = cm_destroyed_composite_devices[--soc_cm_nof_destroyed_composite_devices];
    } else {
        composite_device_index = soc_cm_nof_composite_devices;
    }
    cm_composite_devices[composite_device_index].dev_type = comp_dev_info;
    for (sub_dev_i = 0; sub_dev_i < nof_sub_devs; ++sub_dev_i) {
        unit = sub_units[sub_dev_i];
        cm_composite_devices[composite_device_index].sub_units[sub_dev_i] = unit;
        CMDEV(unit).dev.composite_index = comp_unit;
    }

    CMDEV(comp_unit).dev.dev = -1;
    CMDEV(comp_unit).dev.info = &comp_dev_info->info;
    CMDEV(comp_unit).dev.cookie = cookie;
    CMDEV(comp_unit).dev.dev_id = subdev_dev_id; /* use the PCIe dev/rev IDs of the sub devices */
    CMDEV(comp_unit).dev.rev_id = subdev_rev_id;
    CMDEV(comp_unit).dev.composite_index = composite_device_index;
    soc_cm_nof_composite_devices++;
    assert(soc_cm_nof_destroyed_composite_devices + soc_cm_nof_composite_devices <= SOC_MAX_NOF_COMPOSITE_DEVS);

    soc_cm_device_count++;

    /* Keep soc_ndev in sync */
    soc_all_ndev = soc_cm_device_count;
    if (comp_dev_info->info.dev_type & SOC_SWITCH_DEV_TYPE) {
        SOC_NDEV_IDX2DEV(soc_ndev) = comp_unit;
        soc_ndev++;
    }

    /* Some additional testing */
/* #ifdef BROADCOM_DEBUG */
    for (sub_dev_i = 0; sub_dev_i < nof_sub_devs; ++sub_dev_i) {
        unit = sub_units[sub_dev_i];
        assert(CM_SUB2MAIN_DEV_SAFE(unit) == comp_unit);
        assert(CM_SUB2MAIN_DEV(unit) == comp_unit);
        assert(CM_MAIN2SUB_DEV_SAFE(comp_unit, sub_dev_i) == unit);
        assert(CM_MAIN2SUB_DEV(comp_unit, sub_dev_i) == unit);
    }
    assert(CM_MAIN2SUB_DEV_SAFE(comp_unit, sub_dev_i) == -1);
/* #endif */
    comp_unit = SOC_E_NONE;

handle_error:
    sal_mutex_give(_soc_cm_lock);
    return comp_unit;
}

/*
 * Function: soc_cm_get_composite_dev_info
 * Purpose: w=return the CM information for a composite device
 * Parameters: unit - the unit/device ID of the device
 * Returns: If the device is composite, returns its information structure,
 *          otherwise returns NULL.
 */
const soc_cm_composite_dev_t* soc_cm_get_composite_dev_info(int unit)
{
    soc_cm_dev_t *cm_dev = &CMDEV(unit).dev; /* configuration manager dev info */
    soc_cm_composite_dev_t *ret = NULL;
    if (((unsigned)unit) < SOC_MAX_NUM_DEVICES && cm_dev->dev == -1 &&
        cm_dev->composite_index != SOC_CM_NONE_COMPOSITE_DEV) {
         /* This is not a device or not a composite device */
        ret = cm_composite_devices + cm_dev->composite_index;
        assert(ret->dev_type->nof_sub_devs > 1 &&
               soc_cm_device[ret->sub_units[0]].dev.composite_index == unit &&
               soc_cm_device[ret->sub_units[1]].dev.composite_index == unit);
    }
    return ret;
}

/*
 * Function: soc_cm_get_nof_sub_units
 * Purpose: return the number of sub units of the given unit
 * Parameters: unit - the unit of the device
 * Returns: If the given unit is composite, returns its number of sub-units
 *          otherwise returns zero.
 */
unsigned soc_cm_get_nof_sub_units(int unit)
{
    soc_cm_dev_t *cm_dev = &CMDEV(unit).dev; /* configuration manager dev info */
    unsigned nof_sub_units = 0;

    if (((unsigned)unit) < SOC_MAX_NUM_DEVICES && cm_dev->dev == -1 &&
        (cm_dev->info->dev_type & (SOC_COMPOSITE_DEV_TYPE | SOC_SUB_DEV_TYPE)) == SOC_COMPOSITE_DEV_TYPE &&
        cm_dev->composite_index != SOC_CM_NONE_COMPOSITE_DEV) {
         /* This is not a device or not a composite device */
        nof_sub_units = cm_composite_devices[cm_dev->composite_index].dev_type->nof_sub_devs;
    }
    return nof_sub_units;
}


/*
 * Function:    soc_cm_device_create
 * Purpose:     Create a driver device.
 *
 * Parameters:  dev_id - the device id of the device.
 *              rev_id - the revision id of the device.
 *              cookie - private client pointer you wish
 *                       to have passed back to you when
 *                       driver operations occur.
 *              bde_dev- The BDE device ID.
 *
 * Returns:     On success, a none-negative unit=logical device ID=CM device
 *              handle is returned. None-negative values are not errors.
 *              Negative values indicate a SOC_E_XXX error.
 *
 * Notes:
 *
 *      See <soc/cmext.h> for a complete description
 *      of driver creation/initialization.
 */


int
soc_cm_device_create(uint16 dev_id, uint16 rev_id, void *cookie, int bde_dev)
{
    int dev = -1;
    int rv;

    rv = soc_cm_device_create_id(dev_id, rev_id, cookie, dev, bde_dev);

    /* coverity[identical_branches] */
    if (SOC_FAILURE(rv)) {
        return (rv);
    } else {
        return rv;
    }
}


/*
 * Function:    soc_cm_device_init
 * Purpose:     Initialize a SOC device.
 *
 * Parameters:  unit - logical device number, given to or selected by 
  *                    soc_cm_device_create_id()
 *              vectors - device access vectors
 *
 * Returns:     SOC_E_XXX
 *
 * Notes:
 *
 *      See <soc/cmtypes.h> for a complete description
 *      of driver creation/initialization.
 */

int
soc_cm_device_init(int unit, soc_cm_device_vectors_t *vectors)
{
    AINIT();

#if defined(INCLUDE_CPU_I2C) && (defined(__DUNE_GTO_BCM_CPU__) || defined(__DUNE_WRX_BCM_CPU__) || defined(__DUNE_SLK_BCM_CPU__) || defined(__DUNE_GTS_BCM_CPU__))
    if (SAL_BOOT_I2C_ACCESS && (((CMDEV(unit).dev.dev_id & DNXC_DEVID_FAMILY_MASK) == Q2A_DEVICE_ID) ||
      ((CMDEV(unit).dev.dev_id & J2C_DEVID_FAMILY_MASK) == J2C_DEVICE_ID))) {
        cpu_i2c_write(0x70, 0, 1, 8); /* set board mux to allow access to the device */
    }
#endif

#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    if (CMDEV(unit).dev.info->dev_type & SOC_LTSW_DRV_TYPE) {
        CMVEC(unit) = *vectors;
        CMVEC(unit).init = 1;

        return soc_ltsw_attach(unit);
    }
#endif /* BCM_LTSW_SUPPORT || BCM_CTSW_SUPPORT*/

    if (CMVEC(unit).interrupt_connect == NULL || !CMVEC(unit).init) {
        CMVEC(unit).init = 1;
#define REQUIRE(vName) if (! vectors->vName) return SOC_E_PARAM
        REQUIRE(interrupt_connect);
        REQUIRE(interrupt_disconnect);
#ifdef  SOC_CM_MEMORY_BASE
        REQUIRE(base_address);
        if (vectors->base_address !=
            (SOC_CM_MEMORY_BASE + (SOC_CM_MEMORY_OFFSET*unit))) {
            LOG_CLI((BSL_META("soc_cm_device_init: ERROR: unit %d "
                              "compiled in base address (%#x) "
                              "does not match run time (%#x)\n"),
                     unit,
                     SOC_CM_MEMORY_BASE + (SOC_CM_MEMORY_OFFSET*unit),
                     PTR_TO_INT(vectors->base_address)));
            return SOC_E_PARAM;
        }
#else
#ifdef  SOC_CM_MEMORY
        REQUIRE(base_address);
#else
#ifdef  SOC_CM_FUNCTION
        REQUIRE(read);
        REQUIRE(write);
#else
        if (vectors->base_address == 0 && !CM_IS_COMPOSITE_DEVICE(unit)) {
            REQUIRE(read);
            REQUIRE(write);
        }
#endif  /* SOC_CM_FUNCTION */
#endif  /* SOC_CM_MEMORY */
#endif  /* SOC_CM_MEMORY_BASE */
        if (vectors->bus_type & SOC_PCI_DEV_TYPE) {
            REQUIRE(pci_conf_read);
            REQUIRE(pci_conf_write);
        }
        REQUIRE(salloc);
        REQUIRE(sfree);

#undef REQUIRE

        CMVEC(unit) = *vectors;

        /* Initialize SOC driver here */
        if (CMDEV(unit).dev.info->dev_type & SOC_SWITCH_DEV_TYPE) {
            if (CMDEV(unit).dev.info->dev_type & SOC_SPI_DEV_TYPE) {
                LOG_ERROR(BSL_LS_SOC_COMMON,
                          (BSL_META("ERROR: devices should not be here !\n")));
            } else if (CMDEV(unit).dev.info->dev_type & SOC_ET_DEV_TYPE) {

                LOG_ERROR(BSL_LS_SOC_COMMON,
                          (BSL_META("ERROR: devices should not be here !\n")));
            } else if (CMDEV(unit).dev.info->dev_type & SOC_EMMI_DEV_TYPE){
                LOG_ERROR(BSL_LS_SOC_COMMON,
                          (BSL_META("ERROR: devices should not be here !\n")));
            } else {
#if defined(BCM_DNX_SUPPORT)
                if (SOC_IS_DNX_TYPE(CMDEV(unit).dev.info->dev_id)) {
                    return soc_dnxc_attach(unit);
                }
#endif

#if defined(BCM_PETRA_SUPPORT)
                if (SOC_IS_DPP_TYPE(CMDEV(unit).dev.info->dev_id)


                ) {
                    return soc_dpp_attach(unit);
                }
#endif
#if defined(BCM_DFE_SUPPORT)
                if (SOC_IS_DFE_TYPE(CMDEV(unit).dev.info->dev_id))
                {
                    return soc_dfe_attach(unit);
                }
#endif
#if defined(BCM_DNXF_SUPPORT)
                if (SOC_IS_DNXF_TYPE(CMDEV(unit).dev.info->dev_id))
                {
                    return soc_dnxf_attach(unit);
                }
#endif
#if defined(BCM_ESW_SUPPORT)
                return soc_attach(unit);
#endif
            }

#if defined(BCM_KSCPU_SUPPORT)
        } else if (CMDEV(unit).dev.info->dev_type & SOC_CPU_DEV_TYPE) {
            return SOC_E_NONE;
#endif
        }
            return SOC_E_UNIT;
    } else {
        /* Device already initialized */
        return SOC_E_UNIT;
    }
}


/*
 * Function:    soc_cm_device_destroy
 * Purpose:     Destroy a SOC driver.
 *
 * Parameters:  unit - logical device number, given to or selected by
  *                    soc_cm_device_create_id()
 *
 * Returns:     SOC_E_XXX
 *
 * Notes:
 */

int
soc_cm_device_destroy(int unit)
{
    const soc_cm_device_info_t *info;
    int rv = 0;
    int dev_idx; /* index of the unit in SOC_NDEV_IDX2DEV */
    int bde_dev;

    AINIT();

    if (!CMDEV(unit).dev.info) {
        return SOC_E_UNIT;
    }
    sal_mutex_take(_soc_cm_lock, sal_mutex_FOREVER);

    /* De-initialize SOC driver here */
    if (CMDEV(unit).dev.info->dev_type & SOC_SWITCH_DEV_TYPE) {
        if (CMDEV(unit).dev.info->dev_type & SOC_SPI_DEV_TYPE) {

            LOG_ERROR(BSL_LS_SOC_COMMON,
                      (BSL_META("ERROR: devices should not be here !\n")));
            rv = SOC_E_INTERNAL;
        } else if (CMDEV(unit).dev.info->dev_type & SOC_ET_DEV_TYPE) {

            LOG_ERROR(BSL_LS_SOC_COMMON,
                      (BSL_META("ERROR: devices should not be here !\n")));
            rv = SOC_E_INTERNAL;
        } else if (CMDEV(unit).dev.info->dev_type & SOC_LTSW_DRV_TYPE) {
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
            rv = soc_ltsw_detach(unit);
#endif /* BCM_LTSW_SUPPORT || BCM_CTSW_SUPPORT */
        } else {
#if defined(BCM_DNX_SUPPORT)
            if (SOC_IS_DNX_TYPE(CMDEV(unit).dev.info->dev_id)) {
                rv = soc_dnxc_detach(unit);
                if (CM_IS_COMPOSITE_DEVICE(unit)) {
                    /* destroy sub units of a composite unit before it is destroyed */
                    const soc_cm_composite_dev_t *comp_info = soc_cm_get_composite_dev_info(unit);
                    unsigned i, nof_sub_units, comp_index = comp_info - cm_composite_devices;
                    int rv2;
                    if (comp_info == NULL || comp_info->dev_type == NULL || (nof_sub_units = comp_info->dev_type->nof_sub_devs) == 0 || nof_sub_units > SOC_MAX_NOF_COMPOSITE_SUB_DEVS) {
                        LOG_ERROR(BSL_LS_SOC_COMMON, (BSL_META("ERROR: bad composite unit CM data!\n")));
                        if (rv == 0) {
                            rv = SOC_E_INTERNAL;
                        }
                    } else {
                        for (i = 0; i < nof_sub_units ; ++i) {
                            rv2 = soc_cm_device_destroy(comp_info->sub_units[i]);
                            if (rv == 0) {
                                rv = rv2;
                            }
                        }
                        assert(comp_index < soc_cm_nof_destroyed_composite_devices + soc_cm_nof_composite_devices && soc_cm_nof_composite_devices > 0 &&
                               soc_cm_nof_destroyed_composite_devices + soc_cm_nof_composite_devices <= SOC_MAX_NOF_COMPOSITE_DEVS);
                        cm_destroyed_composite_devices[soc_cm_nof_destroyed_composite_devices++] = comp_index;
                        soc_cm_nof_composite_devices--;
                    }
                }
            } else {
#endif
#if defined(BCM_PETRA_SUPPORT)
            if (SOC_IS_DPP_TYPE(CMDEV(unit).dev.info->dev_id)) {
                rv = soc_dpp_detach(unit);
            } else {
#endif /* BCM_PETRA_SUPPORT */
#if defined(BCM_DFE_SUPPORT)
            if (SOC_IS_DFE_TYPE(CMDEV(unit).dev.info->dev_id)) {
                rv = soc_dfe_detach(unit);
            } else {
#endif /* BCM_DFE_SUPPORT */
#if defined(BCM_DNXF_SUPPORT)
            if (SOC_IS_DNXF_TYPE(CMDEV(unit).dev.info->dev_id)) {
                rv = soc_dnxf_detach(unit);
            } else {
#endif /* BCM_DNXF_SUPPORT */
#if defined(BCM_ESW_SUPPORT)
                rv = soc_detach(unit);
#endif
#if defined(BCM_DNXF_SUPPORT)
            }
#endif
#if defined(BCM_DFE_SUPPORT)
            }
#endif
#if defined(BCM_PETRA_SUPPORT)
            }
#endif
#if defined(BCM_DNX_SUPPORT)
            }
#endif


#if !defined(BCM_ESW_SUPPORT) && !defined(BCM_SAND_SUPPORT)
            LOG_ERROR(BSL_LS_SOC_COMMON,
                      (BSL_META("ERROR: ESW devices should not be here !\n")));
            rv = SOC_E_INTERNAL;
#endif
        }
#if defined(BCM_KSCPU_SUPPORT)
    } else if (CMDEV(unit).dev.info->dev_type & SOC_CPU_DEV_TYPE) {
            sal_mutex_give(_soc_cm_lock);
            return SOC_E_NONE;
#endif
    } else {
        rv = SOC_E_INTERNAL;
    }

    info = _soc_cm_find_device(CMDEV(unit).dev.dev_id,
                               CMDEV(unit).dev.rev_id);
    if (NULL == info) {
        sal_mutex_give(_soc_cm_lock);
        return SOC_E_UNAVAIL;
    }

    /* remove the unit from the loop over units */
    if ((info->dev_type & SOC_SWITCH_DEV_TYPE) && !CM_IS_SUB_DEVICE(unit)) {
        for (dev_idx = 0; dev_idx < soc_ndev; ++dev_idx) {
            if(SOC_NDEV_IDX2DEV(dev_idx) == unit) {
                break;
            }
        }
        if(dev_idx == soc_ndev) {
            LOG_ERROR(BSL_LS_SOC_COMMON,
                      (BSL_META("ERROR: Device %d does not appear in the array soc_ndev_idx2dev_map !\n"), dev_idx));
            rv = SOC_E_NOT_FOUND;
        } else {
            for(++dev_idx; dev_idx < soc_ndev; ++dev_idx) {
                SOC_NDEV_IDX2DEV(dev_idx - 1) = SOC_NDEV_IDX2DEV(dev_idx);
            }
            soc_ndev--;
        }
    }
    soc_cm_device_count--;
    /* Keep soc_ndev in sync */
    soc_all_ndev = soc_cm_device_count;

    bde_dev = CMDEV(unit).dev.dev;
    if (bde_dev >= 0 && bde_dev < SOC_MAX_NUM_DEVICES) { /* Remove the mapping from BDE device to the unit */
        if (cm_bde_dev2unit[bde_dev] == unit) {
            cm_bde_dev2unit[bde_dev] = -1;
        } else {
            LOG_ERROR(BSL_LS_SOC_COMMON,
                      (BSL_META("WARNING: Destroyed unit %d has BDE device %d which is mapped to a different unit:%d\n"), unit, bde_dev, cm_bde_dev2unit[bde_dev]));
        }
    }
    /* Reset device structure.*/
    sal_memset(&CMDEV(unit), 0, sizeof(cm_device_t));

    CMVEC(unit).interrupt_connect = NULL;
    CMVEC(unit).init = 0;
    sal_mutex_give(_soc_cm_lock);

    return rv;
}


/*
 * Function:    soc_cm_bde_dev_2_unit
 * Purpose:     Return the unit=logical deviceID=CM handle give the bde device
 *
 * Parameters:  bde_dev_num - bde device ID or drd device handle
 *
 * Returns:     On success, a none-negative unit=logical device ID=CM device
 *              handle is returned. None-negative values are not errors.
 *              Negative values indicate a SOC_E_XXX error.
 *
 * Description: Set CMDEV(unit).dev.dev to the BDE or DRD device handle.
 *              This function is typically used by hybrid SDK, where the CM
 *              handle is not consistent with the bde or drd handle.
 */
int
soc_cm_bde_dev_2_unit(int bde_dev_num)
{
    AINIT();

    if (bde_dev_num < 0 || bde_dev_num >= SOC_MAX_NUM_DEVICES) {
        return SOC_E_UNIT;
    }

    return cm_bde_dev2unit[bde_dev_num];
}

/*
 * Function:    soc_cm_unit_2_bde_dev
 * Purpose:     Return the unit=logical deviceID=CM handle give the bde device
 *
 * Parameters:  unit - unit=logical device ID=CM device
 *
 * Returns:     On success, a none-negative BDE device ID is returned.
 *              None-negative values are not errors.
 *              Negative values indicate a SOC_E_XXX error.
 *
 * Description: Set CMDEV(unit).dev.dev to the BDE or DRD device handle.
 *              This function is typically used by hybrid SDK, where the CM
 *              handle is not consistent with the bde or drd handle.
 */
int
soc_cm_unit_2_bde_dev(int unit)
{
    int bde_dev = SOC_E_UNIT, possible_bde_dev;
    AINIT();

    if (unit >= 0 && unit < SOC_MAX_NUM_DEVICES) {
        possible_bde_dev = CMDEV(unit).dev.dev;
        if (possible_bde_dev >= 0 && possible_bde_dev < SOC_MAX_NUM_DEVICES) {
            bde_dev = possible_bde_dev;
        }
    }
    return bde_dev;
}

/*
 * Function:    soc_cm_get_main_unit
 * Purpose:     Return the main unit=logical deviceID=CM handle give a sub-unit
 *
 * Parameters:  unit - unit=logical device ID=CM device
 *
 * Returns:     On success, a none-negative unit=logical device ID=CM device
 *              handle is returned. None-negative values are not errors.
 *              Negative values indicate a SOC_E_XXX error.
 *              If the given unit is not a sub-unit, an error will be returned.
 *
 */
int
soc_cm_get_main_unit(int unit)
{
    int main_unit, return_unit = SOC_E_UNIT;
    if (unit >= 0 && unit < SOC_MAX_NUM_DEVICES &&
        CMDEV(unit).dev.info != NULL &&
        (CMDEV(unit).dev.info->dev_type & SOC_SUB_DEV_TYPE) != 0) {
        main_unit = CMDEV(unit).dev.composite_index;
        if (main_unit >= 0 && main_unit < SOC_MAX_NUM_DEVICES) {
            return_unit = main_unit;
        }
    }
    return return_unit;
}

#if 0
/*
 * Function:    soc_is_a_sub_unit
 * Purpose:     Checks if the given unit is a sub unit
 *
 * Parameters:  unit - unit=logical device ID=CM device
 *
 * Returns:     If the given unit is a sub unit, a positive value is returned.
 *              If the given unit is not a sub unit, zero is returned.
 *              If there is an error due to an invalid input or data structures
 *              error, a negative SOC_E_XXX error value is returned.
 *
 */
int
soc_is_a_sub_unit(int unit)
{
    int main_unit, return_val = SOC_E_UNIT;
    if (unit >= 0 && unit < SOC_MAX_NUM_DEVICES &&
        CMDEV(unit).dev.info != NULL) {
        main_unit = CMDEV(unit).dev.composite_index;
        if ((CMDEV(unit).dev.info->dev_type & (SOC_COMPOSITE_DEV_TYPE | SOC_SUB_DEV_TYPE)) == SOC_SUB_DEV_TYPE ||
            main_unit == SOC_CM_NONE_COMPOSITE_DEV) {
            return_val = 0;
        } else if (main_unit >= 0 && main_unit < SOC_MAX_NUM_DEVICES) {
            return_val = 1;
        }
    }
    return return_val;
}
#endif /* 0 */


/******************************************************************
 *
 *                      SOC CM INTERNAL ROUTINES
 *
 * These routines are the DRIVER interface to the SOC configuration
 * manager. These should be used only be the driver.
 *
 *****************************************************************/


/*
 * Function:    soc_cm_get_device_name
 * Purpose:     Return the symbolic name of a device.
 *
 * Parameters:  dev_id - the device id of the device.
 *              rev_id - the revision id of the device.
 *
 * Returns:     Static string
 *
 * Note:        The return value is a device name.
 *              String values are valid, and should not be interpreted as error.
 *              If no device is found, "UNKNOWN" is returned.
 */

const char *
soc_cm_get_device_name(uint16 dev_id, uint8 rev_id)
{
    const soc_cm_device_info_t *info;

    if ((info = _soc_cm_find_device(dev_id, rev_id)) != NULL) {
        return info->dev_name;
    } else {
        return "UNKNOWN";
    }
}

/*
 * Function:    soc_cm_get_name
 * Purpose:     returns the symbolic name of the device.
 *
 * Parameters:  unit - logical device number, given to or selected by
  *                    soc_cm_device_create_id()
 *
 * Returns:     symbolic name of this device.
 *
 * Note:        The return value is symbolic name of this device.
 *              String values are valid, and should not be interpreted as error.
 *              Negative values indicate an error.
 */

const char *
soc_cm_get_name(int unit)
{
#if defined(BCM_TRIUMPH3_SUPPORT) || defined(BCM_FIRELIGHT_SUPPORT)
    uint16          dev_id = 0;
    /*It is used to store the device name which should be renamed by feature*/
    static char _cm_dev_name[SOC_MAX_NUM_DEVICES][16];
#endif

#ifdef BCM_TRIUMPH3_SUPPORT
        uint32          rval;

        if ((NULL!=SOC_CONTROL(unit)) &&
               (SOC_FLAGS_GET(unit) & SOC_F_INITED)) {
            if (SOC_IS_HELIX4(unit)) {
                if (SOC_E_NONE == READ_TOP_SWITCH_FEATURE_ENABLEr(unit, &rval)) {
                    if (rval & 0x8) { /*rval&8==1 means MPLS is enabled*/
                        dev_id = CMDEV(unit).dev.dev_id;
                        if ((dev_id == BCM56340_DEVICE_ID) || (dev_id == BCM56342_DEVICE_ID)
                            || (dev_id == BCM56344_DEVICE_ID)) {
                            sal_memcpy(_cm_dev_name[unit], CMDEV(unit).dev.info->dev_name, 8);
                             _cm_dev_name[unit][8] = 'M';
                            sal_memcpy(&(_cm_dev_name[unit][9]), &(CMDEV(unit).dev.info->dev_name[8]),
                            sal_strlen(CMDEV(unit).dev.info->dev_name)-8);

                            return _cm_dev_name[unit];
                        }
                    }
                }
            }
            else if (SOC_IS_TRIUMPH3(unit)) {
                 if (SOC_E_NONE == READ_TOP_SWITCH_FEATURE_ENABLEr(unit, &rval)) {
                    if (rval & 0x1) { /*rval&1==1 means 1588 is enabled*/
                        dev_id = CMDEV(unit).dev.dev_id;
                        if ((dev_id == BCM56545_DEVICE_ID) || (dev_id == BCM56546_DEVICE_ID)) {
                            sal_memcpy(_cm_dev_name[unit], CMDEV(unit).dev.info->dev_name, 8);
                             _cm_dev_name[unit][8] = 'K';
                            sal_memcpy(&(_cm_dev_name[unit][9]), &(CMDEV(unit).dev.info->dev_name[8]),
                            sal_strlen(CMDEV(unit).dev.info->dev_name)-8);

                            return _cm_dev_name[unit];
                        }
                    }
                }
            }
        }
#endif

#if defined (BCM_DNX_SUPPORT) || defined (BCM_DNXF_SUPPORT)
    if (SOC_CONTROL(unit) && ((CMDEV(unit).dev.info->rev_id & SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT) != 0)) {
        return SOC_CONTROL(unit)->device_name;
    }
    else
#endif
    {
#ifdef BCM_FIRELIGHT_SUPPORT
        if (SOC_IS_FIRELIGHT(unit)) {
            dev_id = CMDEV(unit).dev.dev_id;
            if ((dev_id == BCM56071_DEVICE_ID) && SOC_BOND_INFO_FEATURE_GET(unit, socBondInfoFeatureNoMacsec)) {
                sal_memcpy(_cm_dev_name[unit], CMDEV(unit).dev.info->dev_name, 8);
                 _cm_dev_name[unit][8] = 'N';
                sal_memcpy(&(_cm_dev_name[unit][9]), &(CMDEV(unit).dev.info->dev_name[8]),
                sal_strlen(CMDEV(unit).dev.info->dev_name)-8);
                return _cm_dev_name[unit];
            } else {
                return CMDEV(unit).dev.info->dev_name;
            }
        } else
#endif
        {
            return CMDEV(unit).dev.info->dev_name;
        }
    }
}


/*
 * Function:    soc_cm_get_dev_type
 * Purpose:     returns the type of the device.
 *
 * Parameters:  unit - logical device number, given to or selected by
  *                    soc_cm_device_create_id()
 *
 * Returns:     uint32 of the type of this device.
 *
 * Note:        The return value is the type of this device.
 *              Positive values are valid, and should not be interpreted as error.
 *              Negative values indicate an error.
 */

uint32
soc_cm_get_dev_type(int unit)
{
    return CMDEV(unit).dev.info->dev_type;
}


/*
 * Function:    soc_cm_get_id
 * Purpose:     Returns the real device and revision ids for this device.
 *
 * Parameters:  dev_id - (OUTPUT) receives device id.
 *              rev_id - (OUTPUT) receives revision id.
 *
 * Returns:     SOC_E_NONE.
 */

int
soc_cm_get_id(int unit, uint16 *dev_id, uint8 *rev_id)
{
    AINIT();

    if (dev_id) {
        *dev_id = CMDEV(unit).dev.dev_id;
    }

    if (rev_id) {
        *rev_id = CMDEV(unit).dev.rev_id;
    }

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_get_id_driver
 * Purpose:     Returns the device and revision ids of the driver to
 *              use to handle this device.
 *
 * Parameters:  dev_id - (OUTPUT) receives device id.
 *              rev_id - (OUTPUT) receives revision id.
 *
 * Returns:     SOC_E_NONE - success
 *              SOC_E_NOT_FOUND - chip not supported
 *
 * Notes:       Several different real chip IDs may use the same driver.
 *              This routine maps real chip ID to driver chip ID.
 */

int
soc_cm_get_id_driver(uint16 dev_id, uint8 rev_id,
                     uint16 *dev_id_driver, uint16 *rev_id_driver)
{
    const soc_cm_device_info_t *info;

    if ((info = _soc_cm_find_device(dev_id, rev_id)) == NULL) {
        return SOC_E_NOT_FOUND;
    }

    if (info->dev_id_driver == 0) {
        /* This found dev/rev pair describes a regsfile */
        *dev_id_driver = info->dev_id;
        *rev_id_driver = info->rev_id & ~SOC_CM_REVID_MASK;
    } else {
        /* Found info not a regsfile type, so get associated regsfile */
        *dev_id_driver = info->dev_id_driver;
        *rev_id_driver = info->rev_id_driver;
    }

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_get_num_devices
 * Purpose:     Returns the total number of created devices.
 *
 * Parameters:  None
 *
 * Returns:     Total devices created.
 *
 * Note:        The return value is the number of devices created.
 *              Positive values are valid, and should not be interpreted as error.
 *              Negative values indicate an error.
 */


int
soc_cm_get_num_devices(void)
{
    return soc_cm_device_count;
}

/*
 * Function:    soc_cm_get_rcpu_cfg
 * Purpose:     Returns RCPU configurations of the device.
 *
 * Parameters:  unit - logical device number, given to or selected by
  *                    soc_cm_device_create_id()
 *              rcpu_cfg - (OUTPUT) RCPU configurations.
 *
 * Returns:     SOC_E_XXX
 */
#ifdef INCLUDE_RCPU
#if (SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined (BCM_ESW_SUPPORT)
/* { */
int
soc_cm_get_rcpu_cfg(int unit, soc_rcpu_cfg_t *rcpu_cfg)
{
    if (NULL == CMDEV(unit).dev.cookie) {
        return SOC_E_PARAM;
    }
    *rcpu_cfg = *(soc_rcpu_cfg_t *)CMDEV(unit).dev.cookie;
    return SOC_E_NONE;
}
int
soc_cm_set_rcpu_cfg(int unit, soc_rcpu_cfg_t *rcpu_cfg)
{
    CMDEV(unit).dev.cookie = (void *)rcpu_cfg;
    return SOC_E_NONE;
}
/* } */
#endif
#if (SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined(BCM_ESW_SUPPORT) || defined(INCLUDE_RCPU)
/* { */
int
soc_cm_set_rcpu_trans_tpr(int unit, rcpu_trans_ptr_t *rcpu_tp)
{
    CMVEC(unit).rcpu_tp = rcpu_tp;
    return SOC_E_NONE;
}
/* } */
#endif
#endif /* INCLUDE_RCPU */
/*
 * Function:    soc_cm_interrupt_connect
 * Purpose:     Used by the driver to connect its interrupt handler
 *              the device.
 *
 * Parameters:  unit     - device handle
 *              handler - interrupt handler
 *              data    - isr data.
 *
 * Returns:     0 if successful
 *              <0 if failed.
 */

int
soc_cm_interrupt_connect(int unit, soc_cm_isr_func_t handler, void *data)
{
    return CMVEC(unit).interrupt_connect(&CMDEV(unit).dev, handler, data);
}

/*
 * Function:    soc_cm_interrupt_disconnect
 * Purpose:     Used by the driver to disconnect its interrupt handler.
 *
 * Parameters:  unit - logical device number, given to or selected by
  *                    soc_cm_device_create_id()
 *
 * Returns:     0 if successful
 *              <0 if failed.
 */

int
soc_cm_interrupt_disconnect(int unit)
{
    return CMVEC(unit).interrupt_disconnect(&CMDEV(unit).dev);
}

#ifdef BROADCOM_DEBUG
static int soc_cm_debug_property_get(int unit)
{
    if (0 == _soc_cm_debug_op[unit]) {
        _soc_cm_debug_enable[unit] =
            soc_property_get(unit, "dma_mem_debug_enable", 0);
        _soc_cm_debug_op[unit] = 1;
    }
    return _soc_cm_debug_enable[unit];
}
int soc_cm_shared_good_range(int unit, shared_block_t *p)
{
    if (soc_cm_debug_property_get(unit)) {
        return (((char *)p >= shared_start) && ((char *)p < shared_end));
    }

    return(TRUE);
}
#endif


/*
 * Function:    soc_cm_salloc
 * Purpose:     Allocate shareable memory for communication with the device.
 *
 * Parameters:  unit    - device handle
 *              size    - amount of memory in bytes.
 *              name    - name of this memory (for debugging purposes only)
 *
 * Returns:     Pointer to the memory if successful, otherwise NULL.
 *
 * Note:        The return value is a pointer to the memory.
 *              Positive values are valid, and should not be interpreted as error.
 *              If unsuccesful, NULL is returned.
 */
void *
soc_cm_salloc(int unit, int size, const char *name)
{
    void *ptr;
#ifdef BROADCOM_DEBUG
    if (soc_cm_debug_property_get(unit)) {
        shared_block_t  *p = NULL;
        uint32             size_words = (size + 3) / 4;
        uint32             modified_size = 0;

        assert(name != NULL);        /* Don't pass NULLs in here! */
        assert(name[0] != 0);        /* Don't pass empty strings in here! */

        modified_size = sizeof (shared_block_t) + (size_words * 4);
        p = CMVEC(unit).salloc(&CMDEV(unit).dev, modified_size, name);

        if (p == NULL) {
            return NULL;
        }
        p->start_sentinel = 0xaabbccdd;
        p->description = (char *)name;
        p->size = size;
        p->modified_size = modified_size;
        p->user_data[size_words] = 0xddccbbaa;

        CM_DB_LOCK();
        if (head != NULL) {
            head->prev = p;
        }
        p->prev = NULL;
        p->next = head;
        head = p;
        if ((char *)p < (char *)shared_start) {
            shared_start = (char*)p;
        }
        if ((((char *)p) + modified_size) > shared_end) {
            shared_end = (char*)((char *)p + modified_size);
        }

        CM_DB_UNLOCK();
        /*
        LOG_VERBOSE(BSL_LS_SOC_MEM,
                   (BSL_META("Allocation: Start :%x: Description:%s: Size:%d:"
                              "ModifiedSize:%d: End:%x:\n"),
                   p->start_sentinel ,p->description, p->size,p->modified_size,
                   p->user_data[size_words]));
        */
        ptr = (void *)&p->user_data[0];
    }
    else {
        ptr = CMVEC(unit).salloc(&CMDEV(unit).dev, size, name);
    }
#else
    ptr = CMVEC(unit).salloc(&CMDEV(unit).dev, size, name);
#endif

    MEMLOG_ALLOC("soc_cm_salloc", ptr, size, name);

    return ptr;
}

/*
 * Function:    soc_cm_sfree
 * Purpose:     Free shared memory previously allocated with soc_cm_salloc
 *
 * Parameters:  unit    - device handle
 *              ptr     - shared memory pointer.
 *
 * Returns:     None.
 */

void
soc_cm_sfree(int unit, void *ptr)
{
#ifdef BROADCOM_DEBUG
    if (soc_cm_debug_property_get(unit)) {
        shared_block_t *p = NULL;
        /*
        int            size_words = 0;
        */

        p = (shared_block_t *) (((char*)ptr) -
        ( (((char*)&(((shared_block_t*)0)->user_data[0]))) - ((char*)(shared_block_t*)0) ));
        /* check sentinel */
        assert(SHARED_GOOD_FREE(p));
        assert(SHARED_GOOD_START(p));
        assert(SHARED_GOOD_END(p));

        /*
        size_words = (p->size + 3) / 4;
        LOG_VERBOSE(BSL_LS_SOC_MEM,
                (BSL_META("Freeing Start:%x: Desc:%s: Size:%d: 
                           ModifiedSize:%d: End:%x:\n"),
                 p->start_sentinel ,p->description, p->size,p->modified_size,
                 p->user_data[size_words]));
        */
        CM_DB_LOCK();
        if (p == head) {
            head = p->next;
            if (head != NULL) {
                head->prev = NULL;
            }
        } else {
            p->prev->next = p->next;
            if (p->next != NULL) {
                p->next->prev = p->prev;
            }
        }
        /* Detect redundant frees */
        p->start_sentinel = 0xdeadbeef;
        p->user_data[(p->size + 3) / 4] = 0xdddddddd;

        CM_DB_UNLOCK();
        CMVEC(unit).sfree(&CMDEV(unit).dev, p);
    }
    else {
        CMVEC(unit).sfree(&CMDEV(unit).dev, ptr);
    }
#else /* !BROADCOM_DEBUG */
    CMVEC(unit).sfree(&CMDEV(unit).dev, ptr);
#endif
    MEMLOG_FREE("soc_cm_free", ptr);
    return;
}
#ifdef BROADCOM_DEBUG
void soc_cm_dump_info(int unit)
{
    shared_block_t *p;
    int            size_words = 0, n = 0;
    char           *buf;
    int            len, rc;
    if (soc_cm_debug_property_get(unit)) {
        LOG_CLI((BSL_META("================== SHARED MEMORY INFO(BEGIN) \
                           ===========\n")));
        LOG_CLI((BSL_META("Shared_start:%p Shared_end:%p\n"),(void *)shared_start, \
                           (void *)shared_end));
        CM_DB_LOCK();
        p = head;
        while (p != NULL) {
            n++;
            p = p->next;
        }
        CM_DB_UNLOCK();
        len = n * CM_BUF_SZ;
        buf = sal_alloc(len, "soc cm info dump");
        if (!buf) {
            return;
        }
        sal_memset(buf, 0, len);
        /* coverity[double_lock:FALSE] */
        CM_DB_LOCK();
        p = head;
        while (p != NULL) {
            size_words = (p->size + 3) / 4;
            LOG_CLI((BSL_META("Info p=:%p: Start :0x%x: Desc:%s: Size:%d:"
                              "ModifiedSize:%d End:0x%x\n"),
                              (void *)p, p->start_sentinel, p->description, p->size,
                              p->modified_size, p->user_data[size_words]));
            rc = sal_snprintf(buf, len,
                          "Info p=:%p: Start :0x%x: Desc:%s: Size:%d:"
                          "ModifiedSize:%d End:0x%x\n",
                          (void *)p, p->start_sentinel, p->description, p->size,
                          p->modified_size, p->user_data[size_words]);
            len -= rc;
            if (len < CM_BUF_SZ) {
                break;
            }
            p = p->next;
        }
        CM_DB_UNLOCK();
        LOG_CLI((BSL_META("%s"), buf));
        LOG_CLI((BSL_META("==================== SHARED MEMORY INFO(END)   \
                           ===========\n")));
        sal_free(buf);
    }
    return;
}
#endif

/*
 * Function:    soc_cm_sflush
 * Purpose:     Perform a cache flush on a memory region, if required.
 *
 * Parameters:  unit    - device handle
 *              addr    - memory region
 *              length  - size of region
 *
 * Returns:     SOC_E_XXX
 */

int
soc_cm_sflush(int unit, void *addr, int length)
{
#ifdef BROADCOM_DEBUG
        shared_block_t *p = NULL;
        char           buf[CM_BUF_SZ];
        int            rc = 0;
#endif
    if (CMVEC(unit).sflush) {
#ifdef BROADCOM_DEBUG
        if (soc_cm_debug_property_get(unit)) {
            CM_DB_LOCK();
            p = (shared_block_t *) (((char*)addr) -
                ( (((char*)&(((shared_block_t*)0)->user_data[0]))) - ((char*)(shared_block_t*)0) ));
            if (soc_cm_shared_good_range(unit, p)) {
                /* Cannot use assert as counter thread is using middle address!! */
                if (SHARED_GOOD_START(p)  && SHARED_GOOD_END_DEBUG(p)) {
                    /* assert(SHARED_GOOD_START(p)); */
                    /* assert(SHARED_GOOD_END(p)); */
                    if (length > p->size) {
                        rc = sal_snprintf(buf, sizeof(buf),
                                          "Suspicious DMA length: "
                                          "Desc:%s: Size:%u: length:%u\n",
                                          p->description, p->size, length);
                    }
                }
            } else {
                rc = sal_snprintf(buf, sizeof(buf),
                                 "ERROR:ATTN: Address:%p:"
                                 "probably not in shared memory region \n", (void *)p);
            }
            CM_DB_UNLOCK();
            if (rc > 0 && rc < sizeof(buf)) {
                LOG_ERROR(BSL_LS_SOC_COMMON,
                          (BSL_META("%s"), buf));
            }
        }
#endif
        return CMVEC(unit).sflush(&CMDEV(unit).dev, addr, length);
    }

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_sinval
 * Purpose:     Invalidate a memory region, if required.
 *
 * Parameters:  unit    - device handle
 *              addr    - memory region
 *              length  - size of region
 *
 * Returns:     SOC_E_XXX
 */

int
soc_cm_sinval(int unit, void *addr, int length)
{
    if (CMVEC(unit).sinval) {
        return CMVEC(unit).sinval(&CMDEV(unit).dev, addr, length);
    }

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_l2p
 * Purpose:     Perform a logical (CPU relative) to
 *              physical (chip relative) address translation.
 *
 * Parameters:  unit    - device handle
 *              addr    - address to translate.
 *
 * Returns:     The translated address.
 *
 * Note:        The return value is the translated address.
 *              Positive values are valid, and should not be interpreted as error.
 *
 *              This translation occurs in the context of driver <->
 *              chip communications. * This means that this function may
 *              have to provide more than * a virtual mapping
 *              translation -- if the device is configured to use * a
 *              different physical *bus* address as well, then this
 *              function must provide that also.
 *
 *              The intent here is to share the memory in question with
 *              the hardware, * so this function must return an address
 *              that makes sense with respect to the hardware, as well.
 */

sal_paddr_t
soc_cm_l2p(int unit, void *addr)
{
        if (CMVEC(unit).l2p) {
            return CMVEC(unit).l2p(&CMDEV(unit).dev, addr);
        }

        return (sal_paddr_t)(sal_vaddr_t)addr;

}

/*
 * Function:    soc_cm_p2l
 * Purpose:     Perform a physical (chip relative) to logical
 *              (CPU relative) address translation.
 *
 * Parameters:  unit    - device handle
 *              addr    - address to translate.
 *
 * Returns:     The logical address.
 *
 * Note:        The return value is the logical address.
 *              Positive values are valid, and should not be interpreted as error.
 *
 *              See soc_cm_p2l() (above) for requirements.
 */

void*
soc_cm_p2l(int unit, sal_paddr_t addr)
{
    if (CMVEC(unit).p2l) {
        return CMVEC(unit).p2l(&CMDEV(unit).dev, addr);
    }

    return (void *)(sal_vaddr_t)addr;
}

#if (SRC_SOC_COMMON_ACTIVATE_UNUSED)
/* { */
/*
 * Function:    soc_cm_spi_read
 * Purpose:     Perform a device register read via spi interface
 *
 * Parameters:  unit     - device handle
 *              addr    - address to read.
 *              buf     - a buffer to store the data of the read register.
 *              len     - length to read.
 *
 * Returns:     -1 if error, otherwise 0 (or actual bytes read)
 */

int
soc_cm_spi_read(int unit, uint32 addr, uint8 *buf, int len)
{
    if (CMVEC(unit).spi_read) {
        return CMVEC(unit).spi_read(&CMDEV(unit).dev, addr, buf, len);
    }

    return -1;
}
/* } */
#endif
#if (SRC_SOC_COMMON_ACTIVATE_UNUSED)
/* { */
/*
 * Function:    soc_cm_spi_write
 * Purpose:     Perform a device register write via spi interface
 *
 * Parameters:  unit    - device handle
 *              addr    - address to write.
 *              buf     - a buffer to store the data of the write register.
 *              len     - length to write.
 *
 * Returns:     -1 if error, otherwise 0 (or actual bytes written)
 */

int
soc_cm_spi_write(int unit, uint32 addr, uint8 *buf, int len)
{
    if (CMVEC(unit).spi_write) {
        return CMVEC(unit).spi_write(&CMDEV(unit).dev, addr, buf, len);
    }

    return -1;
}
/* } */
#endif

/*
 * Function:    soc_cm_iproc_read
 * Purpose:     Read iProc register outside CMIC
 *
 * Parameters:  unit    - device handle
 *              addr    - address to read
 *
 * Returns:     Register value
 */

uint32
soc_cm_iproc_read(int unit, uint32 addr)
{
#if defined(BCM_ESW_SUPPORT) || defined(BCM_SAND_SUPPORT)
    uint32 regval;

#if defined(IPROC_ACCESS_DEBUG) && (defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT))
    if (SOC_IS_DNX(unit) || SOC_IS_DNXF(unit)) {
        assert(addr >= 0x80000); /* check that the address is in the currently supported address range of the iproc BAR in Jericho 2 and Ramon */
    }
#endif /* IPROC_ACCESS_DEBUG) && (defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT) */

#if defined(INCLUDE_CPU_I2C)
    if (SAL_BOOT_I2C_ACCESS) {
        regval = -1;
        CMVEC(unit).i2c_device_read(&CMDEV(unit).dev, addr, &regval);
        return regval;
    }
#endif

    /* accessing some iProc registers will hang the system when uC is shut down, need to block the operation */
    if (
#ifdef USE_NEW_ACCESS
        (!ACCESS_IS_INITIALIZED(unit)) &&
#endif /* USE_NEW_ACCESS */
        ((IS_IHOST_S0_ADDR(addr)) || (IS_IHOST_ACP_ADDR(addr))) &&
        (SOC_REG_IS_VALID(unit, CRU_IHOST_PWRDWN_STATUSr)) &&
        (SOC_REG_FIELD_VALID(unit, CRU_IHOST_PWRDWN_STATUSr, LOGIC_PWRDOWN_CPU0f)) &&
        (addr != soc_reg_addr(unit, CRU_IHOST_PWRDWN_STATUSr, REG_PORT_ANY, 0)) &&
        (CMVEC(unit).iproc_read)) {
        regval = CMVEC(unit).iproc_read(&CMDEV(unit).dev, soc_reg_addr(unit, CRU_IHOST_PWRDWN_STATUSr, REG_PORT_ANY, 0));
        if (soc_reg_field_get(unit, CRU_IHOST_PWRDWN_STATUSr, regval, LOGIC_PWRDOWN_CPU0f) == 1) {
            LOG_CLI((BSL_META("Error: the uC has been shut down, cannot read iproc register addr=0x%x.\n"), addr));
            return 0;
        }
    }
#endif

    if (CMVEC(unit).iproc_read) {
#if defined(SOC_PCI_DEBUG) && defined(IPROC_ACCESS_DEBUG)
        uint32 res = CMVEC(unit).iproc_read(&CMDEV(unit).dev, addr);
        LOG_DEBUG(BSL_LS_SOC_PCI, ("u=%d iprocR(0x%x)=0x%x\n", unit, (unsigned)addr, (unsigned)res));
        return res;
#else
        return CMVEC(unit).iproc_read(&CMDEV(unit).dev, addr);
#endif
    }

    return 0;
}

/*
 * Function:    soc_cm_iproc_write
 * Purpose:     Write iProc register outside CMIC
 *
 * Parameters:  unit    - device handle
 *              addr    - address to write
 *              val     - register value
 *
 * Returns:     None
 */

void
soc_cm_iproc_write(int unit, uint32 addr, uint32 val)
{
#if defined(BCM_ESW_SUPPORT) || defined(BCM_SAND_SUPPORT)
    uint32 regval;

#if defined(SOC_PCI_DEBUG) && defined(IPROC_ACCESS_DEBUG)
        LOG_DEBUG(BSL_LS_SOC_PCI, ("u=%d iprocW(0x%x)=0x%x\n", unit, (unsigned)addr, (unsigned)val));
#endif
#if defined(IPROC_ACCESS_DEBUG) && (defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT))
        if (SOC_IS_DNX(unit) || SOC_IS_DNXF(unit)) {
            assert(addr >= 0x80000); /* check that the address is in the currently supported address range of the iproc BAR in Jericho 2 and Ramon */
        }
#endif /* IPROC_ACCESS_DEBUG) && (defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT) */

#if defined(INCLUDE_CPU_I2C)
    if (SAL_BOOT_I2C_ACCESS) {
        CMVEC(unit).i2c_device_write(&CMDEV(unit).dev, addr, val);
        return;
    }
#endif

    /* accessing some iProc registers will hang the system when uC is shut down, need to block the operation */
    if (
#ifdef USE_NEW_ACCESS
        (!ACCESS_IS_INITIALIZED(unit)) &&
#endif /* USE_NEW_ACCESS */
        ((IS_IHOST_S0_ADDR(addr)) || (IS_IHOST_ACP_ADDR(addr))) &&
        (SOC_REG_IS_VALID(unit, CRU_IHOST_PWRDWN_STATUSr)) &&
        (SOC_REG_FIELD_VALID(unit, CRU_IHOST_PWRDWN_STATUSr, LOGIC_PWRDOWN_CPU0f)) &&
        (addr != soc_reg_addr(unit, CRU_IHOST_PWRDWN_STATUSr, REG_PORT_ANY, 0)) &&
        (CMVEC(unit).iproc_read)) {
        regval = CMVEC(unit).iproc_read(&CMDEV(unit).dev, soc_reg_addr(unit, CRU_IHOST_PWRDWN_STATUSr, REG_PORT_ANY, 0));
        if (soc_reg_field_get(unit, CRU_IHOST_PWRDWN_STATUSr, regval, LOGIC_PWRDOWN_CPU0f) == 1) {
            LOG_CLI((BSL_META("Error: the uC has been shut down, cannot write iproc register addr=0x%x.\n"), addr));
            return;
        }
    }
#endif

    if (CMVEC(unit).iproc_write) {
        CMVEC(unit).iproc_write(&CMDEV(unit).dev, addr, val);
    }

    return;
}

/*
 * Note:        The return value is the bus type.
 *              Positive values are valid, and should not be interpreted as error.
 */

uint32
soc_cm_get_bus_type(int unit)
{
    return CMVEC(unit).bus_type;
}

#if (SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined(BCM_ESW_SUPPORT)
/* { */
/*
 * Function:    soc_cm_pci_conf_read
 * Purpose:     Perform a pci config read
 *
 * Parameters:  unit    - device handle
 *              addr    - address to read
 *
 * Returns:     Register value
 */

uint32
soc_cm_pci_conf_read(int unit, uint32 addr)
{
    if (CMVEC(unit).pci_conf_read) {
        return CMVEC(unit).pci_conf_read(&CMDEV(unit).dev, addr);
    }

    return 0;
}
/* } */
#endif

#if (SRC_SOC_COMMON_ACTIVATE_UNUSED)
/* { */
/*
 * Function:    soc_cm_pci_conf_write
 * Purpose:     Perform a pci config write
 *
 * Parameters:  unit    - device handle
 *              addr    - address to write.
 *              data    - double word to write
 *
 * Returns:     None
 */

void
soc_cm_pci_conf_write(int unit, uint32 addr, uint32 data)
{
    if (CMVEC(unit).pci_conf_write) {
        CMVEC(unit).pci_conf_write(&CMDEV(unit).dev, addr, data);
    }

    return;
}
/* } */
#endif

/*
 * Function:    soc_cm_get_endian
 * Purpose:     Returns the required endian configuration for this device.
 *
 * Parameters:  unit    - device handle
 *              pio     - (OUTPUT) receives the PIO endian configuration.
 *              packet  - (OUTPUT) receives the PACKET endian configuration.
 *              other   - (OUTPUT) receives the OTHER endian configuration.
 *
 * Returns:     SOC_E_XXX
 */

int
soc_cm_get_endian(int unit, int *pio, int *packet, int *other)
{
    *pio = CMVEC(unit).big_endian_pio;
    *packet = CMVEC(unit).big_endian_packet;
    *other = CMVEC(unit).big_endian_other;
    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_dump
 * Purpose:     Output configuration information about this device.
 *
 * Parameters:  unit - logical device number, given to or selected by
  *                    soc_cm_device_create_id()
 *
 * Returns:     SOC_E_NONE
 */

int
soc_cm_dump(int unit)
{
    LOG_CLI((BSL_META("CM: Base=%p\n"), (void *)CMVEC(unit).base_address));

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_config_var_get
 * Purpose:     Gets the value a register should be initialized with when the
 *              during chip initialization.
 *
 * Parameters:  unit    - device handle
 *              name    - name of the register
 *
 * Returns:     A string version of the value.
 *
 * Note:        The return value a string version of reg value.
 *              String values are valid, and should not be interpreted as error.
 *              If not found, NULL is returned.
 */

char *
soc_cm_config_var_get(int unit, const char *name)
{
    if (CMVEC(unit).config_var_get == NULL) {
        return NULL;
    }
    return CMVEC(unit).config_var_get(&CMDEV(unit).dev, name);
}

#if (SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
/* { */
/*
 * Function:    soc_cm_config_init
 * Purpose:     Initialize configuration information during chip initialization.
 *
 * Parameters:  None.
 *
 * Returns:     Zero on success.
 *
 */
int
soc_cm_config_init(void)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_config_init();
#else
    return 0;
#endif
}
/* } */
#endif


#if (SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
/* { */
/*
 * Function:    soc_cm_config_str_set
 * Purpose:     Set a global configuration property in a device.
 *
 * Parameters:  unit    - Device handle
 *              name    - Name of configuration property
 *              value   - Value of configuration property
 *
 * Returns:     Zero on success.
 *
 */
int
soc_cm_config_str_set(int unit, const char *name, const char *val)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    int rv = 0;
    int dev_num = 0;

    if (CMDEV(unit).dev.info &&
        (CMDEV(unit).dev.info->dev_type & SOC_LTSW_DRV_TYPE)) {
        rv = soc_cm_dev_num_get(unit, &dev_num);
        if (rv < 0) {
            return rv;
        }

        return soc_ltsw_config_str_set(dev_num, name, val);
    }
#endif

    return -1;
}
/*
 * Function:    soc_cm_config_str_get
 * Purpose:     Get a global configuration property in a device.
 *
 * Parameters:  unit    - Device handle
 *              name    - Name of configuration property
 *
 * Returns:     Value of configuration property.
 *
 */
char *
soc_cm_config_str_get(int unit, const char *name)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    int rv = 0;
    int dev_num = 0;

    if (unit >= 0 && CMDEV(unit).dev.info &&
        (CMDEV(unit).dev.info->dev_type & SOC_LTSW_DRV_TYPE)) {
        rv = soc_cm_dev_num_get(unit, &dev_num);
        if (rv < 0) {
            return NULL;
        }

        return soc_ltsw_config_str_get(dev_num, name);
    }

    if (unit == SOC_UNIT_NONE_SAL_CONFIG) {
        int dev_idx;
        char *s;
        for (dev_idx = 0; dev_idx < SOC_MAX_NUM_DEVICES; dev_idx++) {
            if (CMDEV(dev_idx).dev.info &&
                (CMDEV(dev_idx).dev.info->dev_type & SOC_LTSW_DRV_TYPE)) {
                if (soc_cm_dev_num_get(dev_idx, &dev_num) < 0) {
                    continue;
                }
                if ((s = soc_ltsw_config_str_get(dev_num, name)) != NULL) {
                    return s;
                }
            }
        }
    }
#endif

    return NULL;
}
/*
 * Function:    soc_cm_config_str_delete
 * Purpose:     Delete a global configuration property in a device.
 *
 * Parameters:  unit    - Device handle
 *              name    - Name of configuration property
 *
 * Returns:     Zero on success.
 *
 */
int
soc_cm_config_str_delete(int unit, const char *name)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    int rv = 0;
    int dev_num = 0;

    if (CMDEV(unit).dev.info &&
        (CMDEV(unit).dev.info->dev_type & SOC_LTSW_DRV_TYPE)) {
        rv = soc_cm_dev_num_get(unit, &dev_num);
        if (rv < 0) {
            return rv;
        }

        return soc_ltsw_config_str_delete(dev_num, name);
    }
#endif

    return -1;
}
/*
 * Function:    soc_cm_config_port_str_set
 * Purpose:     Set a per-port configuration property in a device.
 *
 * Parameters:  unit    - Device handle
 *              port    - Port number
 *              name    - Name of configuration property
 *              value   - Value of configuration property
 *
 * Returns:     Zero on success.
 *
 */
int
soc_cm_config_port_str_set(int unit, int port, const char *name, const char *val)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    int rv = 0;
    int dev_num = 0;

    if (CMDEV(unit).dev.info &&
        (CMDEV(unit).dev.info->dev_type & SOC_LTSW_DRV_TYPE)) {
        rv = soc_cm_dev_num_get(unit, &dev_num);
        if (rv < 0) {
            return rv;
        }

        return soc_ltsw_config_port_str_set(dev_num, port, name, val);
    }
#endif

    return -1;
}
/*
 * Function:    soc_cm_config_port_str_get
 * Purpose:     Get a per-port configuration property in a device.
 *
 * Parameters:  unit    - Device handle
 *              port    - Port number
 *              name    - Name of configuration property
 *
 * Returns:     Value of configuration property.
 *
 */
char *
soc_cm_config_port_str_get(int unit, int port, const char *name)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    int rv = 0;
    int dev_num = 0;

    if (CMDEV(unit).dev.info &&
        (CMDEV(unit).dev.info->dev_type & SOC_LTSW_DRV_TYPE)) {
        rv = soc_cm_dev_num_get(unit, &dev_num);
        if (rv < 0) {
            return NULL;
        }

        return soc_ltsw_config_port_str_get(dev_num, port, name);
    }
#endif

    return NULL;
}
/*
 * Function:    soc_cm_config_port_str_delete
 * Purpose:     Delete a per-port configuration property in a device.
 *
 * Parameters:  unit    - Device handle
 *              port    - Port number
 *              name    - Name of configuration property
 *
 * Returns:     Zero on success.
 *
 */
int
soc_cm_config_port_str_delete(int unit, int port, const char *name)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    int rv = 0;
    int dev_num = 0;

    if (CMDEV(unit).dev.info &&
        (CMDEV(unit).dev.info->dev_type & SOC_LTSW_DRV_TYPE)) {
        rv = soc_cm_dev_num_get(unit, &dev_num);
        if (rv < 0) {
            return rv;
        }

        return soc_ltsw_config_port_str_delete(dev_num, port, name);
    }
#endif

    return -1;
}
/* } */
#endif

#if (SRC_SOC_COMMON_ACTIVATE_UNUSED)
/* { */
/* Provided as a back door for current work-around requirements.
 *
 * Note:        The return value is the base address.
 *              Positive values are valid, and should not be interpreted as error.
 */

sal_vaddr_t
soc_cm_get_base_address(int unit)
{
    return CMVEC(unit).base_address;
}
/* } */
#endif

/* Debug routine to display info about known chips
 *
 * Returns:      None.
 */
void
soc_cm_display_known_devices(void)
{
    int                 i;
    uint16              dev_id_driver = 0, last_devid_digit;
    uint16              rev_id_driver = 0;

    LOG_CLI((BSL_META("%-8s%-16s%-16s%-16s\n"),
             "Index", "Chip", "Chip   Dev/Rev", "Driver Dev/Rev"));

    for (i = 0; i < COUNTOF(soc_device_info); i++) {
        soc_cm_get_id_driver(soc_device_info[i].dev_id,
                             soc_device_info[i].rev_id,
                             &dev_id_driver, &rev_id_driver);
        last_devid_digit = soc_device_info[i].dev_id & 0xf;

        LOG_CLI((BSL_META("%-8d%-16s0x%03x%c 0x%02x%c     0x%04x 0x%02x\n"),
                 i,
                 soc_device_info[i].dev_name,
                 soc_device_info[i].dev_id >> 4,
                 (soc_device_info[i].rev_id & SOC_CM_DEVICE_ANY_LAST_DEVID_DIGIT) ? 'x' : (last_devid_digit < 10 ? '0' + last_devid_digit : ('a' - 10) + last_devid_digit),
                 soc_device_info[i].rev_id & SOC_CM_REVID_MASK,
                 (soc_device_info[i].rev_id & SOC_CM_DEVICE_OR_LARGER_REVID) ? '+' : ' ',
                 dev_id_driver,
                 rev_id_driver));
    }
}

#if (SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
/* { *//*
 * Function:    soc_cm_dev_num_get
 * Purpose:     Get device number
 *
 * Parameters:  unit - logical device number, given to or selected by
  *                    soc_cm_device_create_id(). (cm device handle)
 *              dev_num - bde device handle or drd device handle
 *
 * Returns:     SOC_E_XXX
 *
 * Description: Get CMDEV(unit).dev.dev to the BDE/DRD device number.
 *              This function is typically used by hybrid SDK, where the CM
 *              handle is not consistent with bde handle and drd handle.
 */
int
soc_cm_dev_num_get(int unit, int *dev_num)
{
    AINIT();

    if (unit >= SOC_MAX_NUM_DEVICES) {
        return SOC_E_UNIT;
    }

    *dev_num = CMDEV(unit).dev.dev;

    return SOC_E_NONE;
}
/* } */
#endif

/* 
 * Purpose:   Read a 4 byte word from the device using an I2C connection to the device.
 * 
 * Parameters:
 *            unit    - The device handle (from cm_device_create())
 *            addr    - The address to access in the internal device address space.
 *            value   - A pointer for storing the value to be read.
 *
 * Returns:   Zero on success.
 */
int
soc_cm_i2c_device_read(int unit, uint32 addr, uint32 *value)
{
    return CMVEC(unit).i2c_device_read ?
      CMVEC(unit).i2c_device_read(&CMDEV(unit).dev, addr, value) : -1;
}

/*
 * Purpose:   Write a 4 byte word to the device using an I2C connection to the device.
 * 
 * Parameters:
 *            unit    - The device handle (from cm_device_create())
 *            addr    - The address to access in the internal device address space.
 *            value   - The value to be written.
 *
 * Returns:   Zero on success.
 */
int
soc_cm_i2c_device_write(int unit, uint32 addr, uint32 value)
{
    return CMVEC(unit).i2c_device_write ?
      CMVEC(unit).i2c_device_write(&CMDEV(unit).dev, addr, value) : -1;
}

#if (SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
/* { */
/*
 * Purpose: Initialize unit HA memory.
 *
 * Parameters:
 *            unit       - The device handle (from cm_device_create())
 *            pool_alloc - Application provided callback function to
 *                         allocate or grow a HA memory pool.
 *            pool_free  - Application provided callback function to
 *                         free the HA memory block.
 *            pool_ctx   - Application-provided context, which will be
 *                         passed back whenever resize_func function
 *                         is invoked.
 *            pool_ptr   - Pointer to an existing HA memory pool.
 *            pool_size  - Size of the existing HA memory pool.
 *
 * Returns:   Zero on success.
 */
int
soc_cm_ha_mem_init(int unit,
                   soc_cm_ha_mem_pool_alloc_f pool_alloc,
                   soc_cm_ha_mem_pool_free_f pool_free,
                   void *pool_ctx,
                   void *pool_ptr,
                   int pool_size)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_ha_mem_init(unit, pool_alloc, pool_free, pool_ctx,
                                pool_ptr, pool_size);
#else
    return 0;
#endif
}
/* } */
#endif

/*
 * Purpose: Release HA memory resource.
 *
 * Parameters:
 *            unit       - The device handle (from cm_device_create())
 *
 * Returns:   Zero on success.
 */
int
soc_cm_ha_mem_cleanup(int unit)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_ha_mem_cleanup(unit);
#else
    return 0;
#endif
}
#if (SRC_SOC_COMMON_ACTIVATE_UNUSED) || defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
/* { */
/*
 * Purpose: Reset HA memory instance to its initial state.
 *
 * Parameters:
 *            unit       - The device handle (from cm_device_create())
 *
 * Returns:   Zero on success.
 */
int
soc_cm_ha_mem_reset(int unit)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_ha_mem_reset(unit);
#else
    return 0;
#endif
}

/*
 * Purpose: ISSU/FFB auto-start.
 *
 * This function initiates the ISSU/FFB process. This function simplifies the
 * interaction with the ISSU/FFB by hiding the need to know the start and
 * current ISSU version.
 *
 * Parameters:
 *      ffb_mode - Set to true if boot is in FFB mode. The value of this
 *                 parameter should reflect the policy of the application of
 *                 using FFB or ISSU for s/w upgrade.
 *
 *      dll_path - This may point to the DLL path when the DLL is being
 *                 placed at non-standard directory and the LD_LIBRARY_PATH
 *                 variable is not set. Otherwise, set this value to NULL.
 *
 * Return: SHR_E_NONE on success and error code otherwise.
 */
int
soc_cm_issu_auto_start(int ffb_mode, const char *dll_path)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    const char *sdk_ver, *sdklt_ver;
    int rv = 0;

    rv = soc_cm_default_curr_ver_get(&sdk_ver, &sdklt_ver);
    if (rv < 0) {
        return rv;
    }

    if (ffb_mode) {
        rv = soc_ltsw_ffb_start(NULL, sdk_ver, dll_path);
    } else {
        rv = soc_ltsw_issu_upgrade_start(NULL, sdk_ver, dll_path);
    }

    return rv;
#else
    return SOC_E_UNAVAIL;
#endif
}
/*
 * Purpose: ISSU upgrade start.
 *
 * This function initiates the ISSU process. It starts by loading the ISSU DLL.
 * It laters informs the system manager engine about the ongoing update by
 * assigning values to callback functions being executed during the pre config
 * stage.
 *
 * Parameters:
 *      from_ver - The previous version of software that was running.
 *                 If this is NULL the ISSU will attempt to retrieve the
 *                 stored value that was previously set using
 *                 soc_cm_issu_curr_ver_set().
 *      to_ver   - The version of the current software. This value can't be
 *                 NULL or empty string.
 *      dll_path - This may point to the DLL path when the DLL is being
 *                 placed at non-standard directory and the LD_LIBRARY_PATH
 *                 variable is not set. Otherwise, set this value to NULL.
 *
 * Return: SHR_E_NONE on success and error code otherwise.
 */
int
soc_cm_issu_upgrade_start(const char *from_ver, const char *to_ver,
                          const char *dll_path)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_issu_upgrade_start(from_ver, to_ver, dll_path);
#else
    return SOC_E_UNAVAIL;
#endif
}

/*
 * Purpose: ISSU upgrade done.
 *
 * This function releases all the resources that were used by the ISSU. In
 * particular it unloads the ISSU DLL. It is assume that this function is being
 * called once all the units had completed their upgrade.
 *
 * Return: SHR_E_NONE on success and error code otherwise.
 */
int
soc_cm_issu_upgrade_done(void)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_issu_upgrade_done();
#else
    return SOC_E_UNAVAIL;
#endif
}

/*
 * Purpose: Fast Fast boot start.
 *
 * This function initiates the FFB process.
 *
 * Parameters:
 *      from_ver - The previous version of software that was running.
 *                 If this is NULL the ISSU will attempt to retrieve the
 *                 stored value that was previously set using
 *                 soc_cm_issu_curr_ver_set().
 *      to_ver   - The version of the current software. This value can't be
 *                 NULL or empty string.
 *      dll_path - This may point to the DLL path when the DLL is being
 *                 placed at non-standard directory and the LD_LIBRARY_PATH
 *                 variable is not set. Otherwise, set this value to NULL.
 *
 * Return: SHR_E_NONE on success and error code otherwise.
 */
int
soc_cm_ffb_start(const char *from_ver, const char *to_ver,
                 const char *dll_path)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_ffb_start(from_ver, to_ver, dll_path);
#else
    return SOC_E_UNAVAIL;
#endif
}

/*
 * Purpose: Fast Fast boot done.
 *
 * This function indicates the FFB is completed.
 *
 * Return: SHR_E_NONE on success and error code otherwise.
 */
int
soc_cm_ffb_done(void)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_ffb_done();
#else
    return SOC_E_UNAVAIL;
#endif
}

/*
 * Purpose: Set the new software version.
 *
 * This function is called by the application to set the current s/w version
 * with the ISSU. This function should be called by the application with
 * respect to the HSDK version in one of two scenarios:
 * a. After cold boot
 * b. After completion of the ISSU process.
 * As a result the, the application will be able to use the stored value during
 * ISSU event by calling soc_cm_issu_start_ver_get().
 * The function will be available only for HSDK version. To set the SDKLT
 * version the caller should call bcmissu_curr_ver_set().

 * Parameters:
 *      version - The current running software version. This can be obtained
 *                from the RELEASE files.
 *
 * Return: SHR_E_NONE on success and error code otherwise.
 */
int
soc_cm_issu_curr_ver_set(const char *version)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_issu_curr_ver_set(version);
#else
    return SOC_E_UNAVAIL;
#endif
}

/*
 * Purpose: Get the original software version before starting an ISSU.
 *
 * The purpose of this function is to simplify the application and reduce
 * the application requirement to track the start software version. This in
 * particular as the HSDK and SDKLT presenting each a different version to
 * track.
 * This function will be able to provide the information (successfully) after
 * SDKLT completed its basic initialization (prior to device attach). The
 * information will be available only for HSDK version. To obtain the SDKLT
 * version the caller should call bcmissu_start_ver_get().
 *
 * Parameters:
 *      version - The start version as it was saved in previous runs.
 *
 * Return: SHR_E_NONE on success and error code otherwise.
 */
int
soc_cm_issu_start_ver_get(const char **version)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_issu_start_ver_get(version);
#else
    return SOC_E_UNAVAIL;
#endif
}

/*
 * Purpose: Get the current software version.
 *
 * This function is called by the application to get the software version
 * defined during building stage. This software version could be specified
 * by SDK_VER/SDKLT_VER. Otherwise, use version defined in RELEASE files.
 *
 * Parameters:
 *      sdk_ver - The SDK version specified when building image.
 *      sdklt_ver - The SDKLT version specified when building image.
 *
 * Return: SHR_E_NONE on success and error code otherwise.
 */
int
soc_cm_default_curr_ver_get(const char **sdk_ver, const char **sdklt_ver)
{
#if defined(BCM_LTSW_SUPPORT) || defined(BCM_CTSW_SUPPORT)
    return soc_ltsw_issu_compiled_ver_get(sdk_ver, sdklt_ver);
#else
    return SOC_E_UNAVAIL;
#endif
}
/* } */
#endif
/*
 * Purpose: Set the system state to restore state.
 *
 * Parameters:
 *      restore - Enable/Disable restore state
 *
 * Return: SHR_E_NONE on success and error code otherwise.
 */
void
soc_cm_system_restore_state_set(int restore)
{
    system_restore = restore;
}

/*
 * Purpose: Get the restore state.
 *
 * Parameters:
 *      restore - Enable/Disable restore state
 *
 * Return: SHR_E_NONE on success and error code otherwise.
 */
void
soc_cm_system_restore_state_get(int *restore)
{
    *restore = system_restore;
}

# $Id: Makefile,v 1.20 Broadcom SDK $
# This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
# 
# Copyright 2007-2022 Broadcom Inc. All rights reserved.
#
# Makefile for Broadcom Command Monitor (BCM) diagnostic shell
#

LOCALDIR = src/appl/diag

ifdef IMP_PROTECT
CFLAGS += -DIMP_SW_PROTECT
endif

CFGFLAGS += -DSOURCE_CHECK_LIBAPPL

include ${SDK}/make/Make.config

ifdef ESW_CHIPS
subdirs+=esw
endif

ifdef BUILD_SDKLT
subdirs+=lt
endif

ifneq (,$(findstring -DBCM_LTSW_SUPPORT,$(CFGFLAGS)))
subdirs+=ltsw
endif

ifneq (,$(findstring -DBCM_CTSW_SUPPORT,$(CFGFLAGS)))
subdirs+=ctsw
endif

#
# Note that DNX-only state is true for either one of DNX_CHIPS or DNXF_CHIPS
#
ifdef SAND_CHIPS
subdirs+=sand
endif
ifdef DPP_CHIPS
subdirs+=dpp dcmn
endif
ifdef DFE_CHIPS
subdirs+=dfe dcmn
endif
#
ifdef DNX_CHIPS
subdirs+=dnx dnxc
endif
ifdef DNXF_CHIPS
subdirs+=dnxf dnxc
endif

ifdef BUILD_EAV_APPL
subdirs+=eav
endif
ifdef COND_LIB_CINT
subdirs+=cint
ifdef COND_LIB_API_DIAG_BLD
subdirs+=api
endif
endif
ifdef COND_LIB_DIAG_APS
subdirs+=aps
endif
ifdef BUILD_PHYMOD
subdirs+= phymod
endif
ifdef PORTMOD_SUPPORT
subdirs+= portmod
endif

include ${SDK}/make/Make.subdirs

lib = libdiag
include ${SDK}/make/Make.lib

include ${SDK}/make/Make.depend

# $Id: Makefile,v 1.18 Broadcom SDK $
# This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
# 
# Copyright 2007-2022 Broadcom Inc. All rights reserved.
#
# Makefile for Switch on a Chip (SOC) driver and diagnostics
#

include ${SDK}/make/Make.config

subdirs =

ifdef BUILD_FLEXE
  subdirs += std
endif

ifdef BUILD_FLEXE_DBG
  subdirs += dbg
endif

include ${SDK}/make/Make.subdirs

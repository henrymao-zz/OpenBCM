/*
 *         
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *     
 * DO NOT EDIT THIS FILE!
 *
 */

#ifndef _PMOSILKN_50G_H__H_
#define _PMOSILKN_50G_H__H_

#include <phymod/phymod.h>
#include <phymod/phymod_diagnostics.h>
#include <phymod/phymod_reg.h>
#include <soc/cprimod/cprimod.h>
#include <soc/portmod/portmod_defs.h>
#include <sal/core/sync.h>
/*Add new port*/
int pmOsILKN_50G_port_attach(int unit, int port, pm_info_t pm_info, const portmod_port_add_info_t* add_info);

/*update Aggregated PMs information (type, id)*/
int pmOsILKN_50G_pm_aggregated_update(int unit, pm_info_t pm_info, int core_id, int nof_aggregated_pms, const pm_info_t* pms, const int* pm_ids);

/*Port remove in PM level*/
int pmOsILKN_50G_port_detach(int unit, int port, pm_info_t pm_info);

/*Port speed set\get*/
int pmOsILKN_50G_port_loopback_set(int unit, int port, pm_info_t pm_info, portmod_loopback_mode_t loopback_type, int enable);
int pmOsILKN_50G_port_loopback_get(int unit, int port, pm_info_t pm_info, portmod_loopback_mode_t loopback_type, int* enable);

/*Get lane phymod access structure. can be used for per lane operations*/
int pmOsILKN_50G_port_phy_lane_access_get(int unit, int port, pm_info_t pm_info, const portmod_access_get_params_t* params, int max_phys, phymod_phy_access_t* access, int* nof_phys, int* is_most_ext);

/*"logical lane order"*/
int pmOsILKN_50G_port_logical_lane_order_set(int unit, int port, pm_info_t pm_info, const int* lane_order, int lane_order_size);
int pmOsILKN_50G_port_logical_lane_order_get(int unit, int port, pm_info_t pm_info, int lane_order_max_size, int* lane_order, int* lane_order_actual_size);

/* set/get the speed config for the specified port.*/
int pmOsILKN_50G_port_speed_config_set(int unit, int port, pm_info_t pm_info, const portmod_speed_config_t* speed_config);
int pmOsILKN_50G_port_speed_config_get(int unit, int port, pm_info_t pm_info, portmod_speed_config_t* speed_config);

/* Enable credits for the port. */
int pmOsILKN_50G_port_credits_enable_set(int unit, int port, pm_info_t pm_info, int enable);

/* Get the sum of pmd_lock_counters of all the port's lanes */
int pmOsILKN_50G_port_pmd_lock_counter_get(int unit, int port, pm_info_t pm_info, uint32* pmd_lock_counter_sum);

/*Enable/Disable ILKN port lanes.*/
int pmOsILKN_50G_ilkn_port_lane_enable(int unit, int port, pm_info_t pm_info, int flags, int enable);

#endif /*_PMOSILKN_50G_H_*/

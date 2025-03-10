/* $Id:
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * File: cint_rx_trap_lif_with_esem_entry.c
 * Purpose: Shows an example for configuration of lif trap with ESEM entry.
 *
 * cint ../../../../src/examples/dnx/traps/cint_rx_trap_lif_with_esem_entry.c
 *
 * Main Function:
 *      cint_rx_trap_lif_with_esem_entry_main(unit, vsi, out_port, action_gport);
 * Destroy Function:
 *      cint_rx_trap_lif_with_esem_entry_destroy(unit);
 *
 * Example Config:
 * Test Scenario - start
  cint ../../../../src/examples/dnx/traps/cint_utils_rx.c
  cint ../../../../src/examples/dnx/traps/cint_ip_route_basic.c
  cint ../../../../src/examples/dnx/traps/cint_rx_trap_lif_with_esem_entry.c
  cint
  dnx_basic_example(0,200,202,kaps_result);
  bcm_gport_t action_gport;
  BCM_GPORT_TRAP_SET(action_gport, BCM_RX_TRAP_EG_TX_TRAP_ID_DROP, 13, 0);
  cint_rx_trap_lif_with_esem_entry_main(0, 100, 202, action_gport);
 * Test Scenario - end
 */

int cint_rx_trap_lif_with_esem_entry_id = 0;

/**
* \brief
*  Function that sets-up the desired lif trap for an ESEM entry.
* \par DIRECT INPUT:
*   \param [in] unit           - unit Id
*   \param [in] vsi           - VSI of route
*   \param [in] out_port      - out port
*   \param [in] action_gport  - action gport encoding either trap or mirror(only for egress)
*
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   int - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
int
cint_rx_trap_lif_with_esem_entry_main(
    int unit,
    int vsi,
    int out_port,
    bcm_gport_t action_gport)
{
    bcm_rx_trap_lif_config_t lif_config;
    bcm_vlan_port_t vlan_port;

    if(*dnxc_data_get(unit, "trap", "etpp", "stack_trap_etps_support", NULL) == 0)
    {
        printf("Cint is not supported on this device, lif traps are not supported for ESEM entries\n");
        return BCM_E_FAIL;
    }

    bcm_vlan_port_t_init(&vlan_port);
    vlan_port.criteria = BCM_VLAN_PORT_MATCH_PORT_VLAN;
    vlan_port.flags = BCM_VLAN_PORT_CREATE_EGRESS_ONLY|BCM_VLAN_PORT_VLAN_TRANSLATION;
    vlan_port.port = out_port;
    vlan_port.vsi = vsi;

	BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, &vlan_port), "");

    cint_rx_trap_lif_with_esem_entry_id = vlan_port.vlan_port_id;

    bcm_rx_trap_lif_config_t_init(&lif_config);
    lif_config.lif_type = bcmRxTrapLifTypeOutLif;
    lif_config.lif_gport = cint_rx_trap_lif_with_esem_entry_id;
    lif_config.action_gport = action_gport;
    
    BCM_IF_ERROR_RETURN_MSG(bcm_rx_trap_lif_set(unit, 0, &lif_config), "");

    return BCM_E_NONE;
}

/**
* \brief
*  Function that clears configuration for lif trap with ESEM entry.
* \par DIRECT INPUT:
*   \param [in] unit           - unit Id
*
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   int - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
int
cint_rx_trap_lif_with_esem_entry_destroy(
    int unit)
{
    bcm_rx_trap_lif_config_t lif_config;

    bcm_rx_trap_lif_config_t_init(&lif_config);
    lif_config.lif_type = bcmRxTrapLifTypeOutLif;
    lif_config.lif_gport = cint_rx_trap_lif_with_esem_entry_id;

    BCM_IF_ERROR_RETURN_MSG(bcm_rx_trap_lif_set(unit, 0, &lif_config), "");

	BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_destroy(unit, cint_rx_trap_lif_with_esem_entry_id), "");

    return BCM_E_NONE;
}


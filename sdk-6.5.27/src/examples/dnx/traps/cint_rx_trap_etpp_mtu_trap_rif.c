/*
 * File: cint_rx_trap_etpp_mtu_trap_rif.c
 * Purpose: Configuration that creates an ETPP User defined trap.
 *          Creates an MTU violation configuration PER RIF and attaches it,
 *          to the created ETPP trap.
 *
 * cint ../../../../src/examples/dnx/traps/cint_rx_trap_etpp_mtu_trap_rif.c
 *
 * Main Function:
 *      cint_rx_trap_etpp_mtu_trap_rif_main(unit,out_rif,layer_type,compressed_layer_type,trap_id,fwd_strength,snp_strength,mtu_val);
 * Destroy Function:
 *      cint_rx_trap_etpp_mtu_trap_lif_destroy(unit,out_rif,layer_type,compressed_layer_type);
 *
 * Example Config requires a valid(created) out_rif to be supplied:
 * Test Scenario - start
  cint ../../../../src/examples/dnx/traps/cint_utils_rx.c
  cint ../../../../src/examples/dnx/traps/cint_rx_trap_etpp_mtu_trap_rif.c
  cint
  cint_rx_trap_etpp_mtu_trap_rif_main(0,out_rif,3,3,4,7,0,0x20);
 * Test Scenario - end
 *
 */

/* The encoded User defined trap id */
int cint_etpp_mtu_trap_rif_trap_id;
bcm_rx_trap_config_t trap_config = {0};
/**
* \brief
* Creates an ETPP user defined trap, sets an action different than drop.
* Sets an MTU configuration and attaches it to the created trap, for RIF.
* \par DIRECT INPUT:
*   \param [in] unit         - Unit
*   \param [in] rif_intf     - RIF Interface.
*   \param [in] layer_type - Forwarding Layer Type
*   \param [in] compressed_layer_type - Compressed Forwarding Layer Type
*   \param [in] trap_id      - Trap ID.
*   \param [in] fwd_strength - Trap Strength
*   \param [in] snp_strength - Snoop Strength
*   \param [in] mtu_val      - MTU Value
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   int -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
int cint_rx_trap_etpp_mtu_trap_rif_main(
    int unit,
    bcm_if_t rif_intf,
    int layer_type,
    int compressed_layer_type,
    int trap_id,
    int fwd_strength,
    int snp_strength,
    int mtu_val,
    int mtu_profile)
{
    bcm_gport_t trap_gport;

    if(trap_id != BCM_RX_TRAP_EG_TX_TRAP_ID_DROP)
    {
        trap_config.is_recycle_append_ftmh = TRUE;

        BCM_IF_ERROR_RETURN_MSG(cint_utils_rx_trap_create_and_set(unit,BCM_RX_TRAP_WITH_ID, bcmRxTrapEgTxUserDefine, trap_config, &trap_id), "");
    }

    cint_etpp_mtu_trap_rif_trap_id = trap_id;
    BCM_GPORT_TRAP_SET(trap_gport, trap_id, fwd_strength, snp_strength);

    BCM_IF_ERROR_RETURN_MSG(cint_etpp_mtu_trap_mtu_rif_set(unit, rif_intf, trap_gport, mtu_val, layer_type, compressed_layer_type, mtu_profile), "");

    return BCM_E_NONE;
}

/**
* \brief
* Set an MTU Configuration.
* Set the compressed fwd layer type.
* \par DIRECT INPUT:
*   \param [in] unit        - Unit
*   \param [in] rif_intf    - RIF ID
*   \param [in] trap_gport  - Trap Gport
*   \param [in] mtu_val     - MTU Value
*   \param [in] layer_type - Forward Layer type
*   \param [in] compressed_layer_type - Compressed forward layer type
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   int -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
int cint_etpp_mtu_trap_mtu_rif_set(
    int unit,
    bcm_if_t rif_intf,
    bcm_gport_t trap_gport,
    int mtu_val,
    int layer_type,
    int compressed_layer_type,
    int mtu_profile)
{
    bcm_rx_mtu_config_t mtu_config;
    bcm_switch_control_key_t key;
    bcm_switch_control_info_t info;
    bcm_rx_mtu_profile_value_t mtu_value;
    bcm_rx_mtu_profile_key_t mtu_key;
    int mtu_layer_to_compressed_layer_mapping_support = 0;

    bcm_rx_mtu_config_t_init(&mtu_config);
    bcm_rx_mtu_profile_key_t_init(&mtu_key);
    bcm_rx_mtu_profile_value_t_init(&mtu_value);

    mtu_layer_to_compressed_layer_mapping_support = *(dnxc_data_get(unit, "trap", "etpp", "mtu_layer_to_compressed_layer_mapping_support", NULL));
    if (mtu_layer_to_compressed_layer_mapping_support)
    {
        /* Creating a compressed layer type */
        key.type = bcmSwitchLinkLayerMtuFilter;
        key.index = layer_type;

        info.value = compressed_layer_type;

        BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_indexed_set(unit, key, info), "");
    }
    else if (layer_type != 0)
    {
        printf("Error: layer_type is non-zero, for this device only compressed_layer_type should be supplied\n");
        return BCM_E_PARAM;
    }

    mtu_key.cmp_layer_type = compressed_layer_type;
    mtu_key.mtu_profile = mtu_profile;

    mtu_value.mtu_val = mtu_val;
    mtu_value.trap_gport = trap_gport;

    BCM_IF_ERROR_RETURN_MSG(bcm_rx_mtu_profile_set(unit, BCM_RX_MTU_RIF, &mtu_key, &mtu_value), "");

    mtu_config.flags = BCM_RX_MTU_RIF;
    mtu_config.intf = rif_intf;
    mtu_config.mtu_profile = mtu_profile;

    BCM_IF_ERROR_RETURN_MSG(bcm_rx_mtu_set(unit, &mtu_config), "");

    return BCM_E_NONE;
}

/**
* \brief
* Destroys the created trap and MTU configuration for the supplied out-RIF.
* \par DIRECT INPUT:
*   \param [in] unit                        - Unit
*   \param [in] rif_intf                    - OUT-RIF value.
*   \param [in] layer_type              - Forward Layer type
*   \param [in] compressed_layer_type       - Compressed fwd layer type.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   int -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
int cint_rx_trap_etpp_mtu_trap_rif_destroy(
    int unit,
    bcm_if_t rif_intf,
    int layer_type,
    int compressed_layer_type,
    int mtu_profile)
{
    bcm_rx_mtu_config_t  mtu_config;
    bcm_switch_control_key_t key;
    bcm_switch_control_info_t info;    
    bcm_rx_mtu_profile_value_t mtu_value;
    bcm_rx_mtu_profile_key_t mtu_key;
    int mtu_layer_to_compressed_layer_mapping_support = 0;

    bcm_rx_mtu_config_t_init(&mtu_config);
    bcm_rx_mtu_profile_key_t_init(&mtu_key);
    bcm_rx_mtu_profile_value_t_init(&mtu_value);

    if(cint_etpp_mtu_trap_rif_trap_id != BCM_RX_TRAP_EG_TX_TRAP_ID_DROP)
    {
        /* delete trap */
        BCM_IF_ERROR_RETURN_MSG(bcm_rx_trap_type_destroy(unit, cint_etpp_mtu_trap_rif_trap_id), "");
    }

    mtu_layer_to_compressed_layer_mapping_support = *(dnxc_data_get(unit, "trap", "etpp", "mtu_layer_to_compressed_layer_mapping_support", NULL));
    if (mtu_layer_to_compressed_layer_mapping_support)
    {
        /* Setting compressed layer type to zero */
        key.type = bcmSwitchLinkLayerMtuFilter;
        key.index = layer_type;

        info.value = 0;

        BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_indexed_set(unit, key, info), "");
    }

    mtu_config.flags = BCM_RX_MTU_RIF;
    mtu_config.intf = rif_intf;

    BCM_IF_ERROR_RETURN_MSG(bcm_rx_mtu_set(unit, &mtu_config), "");

    mtu_key.cmp_layer_type = compressed_layer_type;
    mtu_key.mtu_profile = mtu_profile;

    mtu_value.mtu_val = 0;
    mtu_value.trap_gport = BCM_GPORT_INVALID;

    BCM_IF_ERROR_RETURN_MSG(bcm_rx_mtu_profile_set(unit, BCM_RX_MTU_RIF, &mtu_key, &mtu_value), "");

    return BCM_E_NONE;
}


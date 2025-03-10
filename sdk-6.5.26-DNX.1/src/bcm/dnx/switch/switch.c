/**
 * \file switch/switch.c
 *
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_SWITCH

/*
 * Include files.
 * {
 */

#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/memory.h>
#include <soc/feature.h>
#include <soc/types.h>
#include <soc/register.h>
#include <soc/dnxc/drv_dnxc_utils.h>
#include <soc/dnxc/dnxc_diag.h>
#include <soc/uc_msg.h>
#include <soc/chip.h>
#include <soc/util.h>

#include <soc/counter.h>
#include <soc/shared/sat.h>
#include <soc/dnx/dbal/dbal.h>
#include <soc/dnx/dbal/auto_generated/dbal_defines_fields.h>
#include <soc/dnx/mdb.h>
#include <soc/dnxc/swstate/dnxc_sw_state_utils.h>
#include <bcm/types.h>
#include <bcm/switch.h>
#include <bcm_int/common/sat.h>
#include <bcm_int/dnx/algo/algo_gpm.h>
#include <bcm_int/dnx/stat/crps/crps_src_interface.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_dev_init.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_mpls.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_switch.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_trap.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_multicast.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_pvt.h>
#include <bcm_int/dnx/switch/switch.h>
#include <bcm_int/dnx/switch/switch_load_balancing.h>
#include <bcm_int/dnx/algo/port/algo_port_mgmt.h>
#include <bcm_int/dnx/policer/policer_mgmt.h>
#include <bcm_int/dnx/l2/l2_learn.h>
#include <bcm_int/dnx/l2/l2_traverse.h>
#include <bcm_int/dnx/l2/l2_station.h>
#include <bcm_int/dnx/l2/l2.h>
#include <bcm_int/dnx/mpls/mpls.h>
#include <bcm_int/dnx/l3/l3.h>
#include <bcm_int/dnx/l3/l3_fec.h>
#include <bcm_int/dnx/switch/switch_wide_data_ext.h>

#include <bcm_int/dnx/rx/rx_trap.h>
#include <bcm_int/dnx/rx/rx_trap_map.h>
#include <bcm_int/dnx/l3/l3_vrrp.h>
#include <bcm_int/dnx/port/port.h>
#include <bcm_int/dnx/oam/oam.h>
#include <bcm_int/dnx/port/port_pp.h>
#include <bcm_int/dnx/port/port_sit.h>
#include <bcm_int/dnx/port/port_flexe.h>
#include <bcm_int/dnx/port/flexe/flexe_core.h>
#include <bcm_int/dnx/algo/port/algo_port_soc.h>
#include <bcm_int/dnx/algo/oam/algo_oam.h>
#include <bcm_int/dnx/tdm/tdm.h>
#include <bcm_int/dnx/trunk/trunk.h>
#include <bcm_int/dnx/field/field_group.h>
#include <bcm_int/dnx/field/field_flush.h>
#include <bcm_int/dnx/kbp/kbp_mngr.h>
#include <bcm_int/dnx/kbp/kbp.h>
#include <bcm_int/dnx/kbp/kbp_connectivity.h>
#include <bcm_int/dnx/cosq/ingress/cosq_ingress.h>
#include <bcm_int/dnx/switch/switch_em_false_hit.h>
#include <bcm_int/dnx/lif/out_lif_headers_profile.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_lif.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_pp.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_synce.h>
#include <src/bcm/dnx/mpls_port/mpls_port.h>
#include <src/bcm/dnx/oam/oam_oamp.h>
#include <src/bcm/dnx/oam/oamp_v1/oam_oamp_v1.h>
#include "bcm_int/dnx/init/init_pp.h"
#include <bcm_int/dnx/stat/crps/crps_mgmt.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_headers.h>
#include <soc/dnxc/dnxc_intr.h>
#include <soc/dnx/swstate/auto_generated/access/interrupt_access.h>
#include <soc/dnx/swstate/auto_generated/access/switch_access.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_range_access.h>
#include <soc/dnxc/dnxc_mem.h>
#include <bcm_int/dnx/synce/synce.h>
#include <soc/sand/sand_mem.h>
#include <bcm_int/dnx/dram/dram.h>
#include <soc/dnx/utils/dnx_sbusdma_desc.h>
#include <soc/dnx/utils/dnx_pp_programmability_utils.h>
#include <bcm_int/dnx/field/field_map.h>
#include <soc/dnx/dnx_err_recovery_manager.h>
#include <bcm_int/dnx/bfd/bfd.h>
#include <bcm_int/dnx/cosq/latency/cosq_latency.h>
#include <bcm_int/dnx/port/imb/imb.h>
#include <soc/dnx/intr/dnx_intr.h>
#include <soc/dnxc/dnxc_intr_corr_act_func.h>
#include <soc/dnxc/dnxc_ha.h>
#include "src/soc/dnx/dbal/dbal_internal.h"
#include <soc/dnx/swstate/auto_generated/access/dnx_hard_reset_access.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/algo_l3_access.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/dnx_algo_port_access.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/flow_control_access.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/sec_access.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/vlan_access.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/algo_port_pp_access.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/algo_lif_profile_access.h>
#include <bcm_int/dnx/switch/switch_svtag.h>
#include <bcm_int/dnx/switch/switch_reflector.h>
#include <bcm_int/dnx/port/port_match.h>
#include <bcm_int/dnx/oam/oam_init.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_mdb.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_l2.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_dram.h>
#include <bcm_int/dnx/l3/l3_ecmp_vip.h>
#include <bcm_int/dnx/cmn/dnxcmn.h>
#include <soc/dnx/swstate/auto_generated/access/l2_access.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_oam.h>
#ifdef BCM_WARM_BOOT_SUPPORT
#include <soc/dnxc/dnxc_wb_test_utils.h>
#include <bcm_int/dnx/dram/hbmc/hbmc.h>
#endif /* BCM_WARM_BOOT_SUPPORT */
#ifdef INCLUDE_I2C
#include <bcm/bcmi2c.h>
#endif

#include <bcm_int/dnx/srv6/srv6.h>
#include <bcm_int/dnx/pvt/pvt.h>
#ifdef BCM_ACCESS_SUPPORT
#include <soc/access/access.h>
#include <soc/access/access_regmem_util.h>
#include <soc/access/access_intr.h>
#include <soc/dnxc/intr.h>
#endif
/*
 * }
 */
/*
 * Defines
 * {
 */
#define BCM_SWITCH_TUNNEL_ROUTE_DISABLE_SUPPORTED_FLAGS (BCM_SWITCH_TUNNEL_ROUTE_DISABLE_NONE | BCM_SWITCH_TUNNEL_ROUTE_DISABLE_TCP \
                    | BCM_SWITCH_TUNNEL_ROUTE_DISABLE_UDP | BCM_SWITCH_TUNNEL_ROUTE_DISABLE_ICMP | BCM_SWITCH_TUNNEL_ROUTE_DISABLE_IGMP \
                    | BCM_SWITCH_TUNNEL_ROUTE_DISABLE_UNKNOWN | BCM_SWITCH_TUNNEL_ROUTE_DISABLE_GRE_KEEP_ALIVE)

#define DNX_SWITCH_FIELD_NAME_MAX_SUBSTRING_LENGTH  (20)

/*
 * }
 */
/*
 * MACROs
 * {
 */

/*
 * }
 */

/*
 * Enum
 * {
 */
typedef enum dnx_parse_udp_e
{
    dnxParseUdpNextHeaderIpv4 = 0,      /* IPV4oUDP */
    dnxParseUdpNextHeaderIpv6 = 1,      /* IPV6oUDP */
    dnxParseUdpNextHeaderCount = 2,     /* count */
} dnx_parse_udp_next_header_t;

/*
 * }
 */
#if defined(BCM_RCPU_SUPPORT)
/*
 * {
 */
/*
 * Function:
 *      _bcm_dnx_rcpu_switch_enable_set
 * Description:
 *      Helper function to enable SCHEN, CMIC, MAC and VLAN for RCPU
 * Parameters:
 *      unit - Device unit number
 *  type - The desired configuration parameter to modify
 *  arg - The value to set
 * Returns:
 *      BCM_E_xxx
 */
static int
_bcm_dnx_rcpu_switch_enable_set(
    int unit,
    bcm_switch_control_t type,
    int arg)
{
    uint32 entry_handle_id, value;
    dbal_fields_e field;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    switch (type)
    {
        case bcmSwitchRemoteCpuSchanEnable:
            field = DBAL_FIELD_SCHAN_EN;
            break;
        case bcmSwitchRemoteCpuMatchLocalMac:
            field = DBAL_FIELD_MAC_MATCH_EN;
            break;
        case bcmSwitchRemoteCpuCmicEnable:
            field = DBAL_FIELD_CMIC_EN;
            break;
        case bcmSwitchRemoteCpuMatchVlan:
            field = DBAL_FIELD_VLAN_MATCH_EN;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid type=%d\r\n", type);
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_RCPU_ENABLE_CTRL, &entry_handle_id));

    value = (uint32) arg;
    dbal_entry_value_field32_set(unit, entry_handle_id, field, INST_SINGLE, value);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *      _bcm_dnx_rcpu_switch_enable_get
 * Description:
 *      Helper function to get enabling status of SCHEN, CMIC, MAC and VLAN for RCPU
 * Parameters:
 *      unit - Device unit number
 *  type - The desired configuration parameter to get
 *  arg - The value returned
 * Returns:
 *      BCM_E_xxx
 */
static int
_bcm_dnx_rcpu_switch_enable_get(
    int unit,
    bcm_switch_control_t type,
    int *arg)
{
    uint32 entry_handle_id, value;
    dbal_fields_e field;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    switch (type)
    {
        case bcmSwitchRemoteCpuSchanEnable:
            field = DBAL_FIELD_SCHAN_EN;
            break;
        case bcmSwitchRemoteCpuMatchLocalMac:
            field = DBAL_FIELD_MAC_MATCH_EN;
            break;
        case bcmSwitchRemoteCpuCmicEnable:
            field = DBAL_FIELD_CMIC_EN;
            break;
        case bcmSwitchRemoteCpuMatchVlan:
            field = DBAL_FIELD_VLAN_MATCH_EN;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid type=%d\r\n", type);
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_RCPU_ENABLE_CTRL, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field, INST_SINGLE, &value));

    *arg = (int) value;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *      _bcm_dnx_rcpu_switch_vlan_tpid_sig_set
 * Description:
 *      Helper function to set VLAN, TPID ot Signature for RCPU
 * Parameters:
 *      unit - Device unit number
 *  type - The desired configuration parameter to modify
 *  arg - The value to set
 * Returns:
 *      BCM_E_xxx
 */
static int
_bcm_dnx_rcpu_switch_vlan_tpid_sig_set(
    int unit,
    bcm_switch_control_t type,
    int arg)
{
    uint32 entry_handle_id, value;
    dbal_fields_e field;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    switch (type)
    {
        case bcmSwitchRemoteCpuVlan:
            field = DBAL_FIELD_VLAN_TCI;
            break;
        case bcmSwitchRemoteCpuTpid:
            field = DBAL_FIELD_TPID;
            break;
        case bcmSwitchRemoteCpuSignature:
            field = DBAL_FIELD_SIGNATURE;
            break;
        case bcmSwitchRemoteCpuEthertype:
            field = DBAL_FIELD_ETHERTYPE;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid type=%d\r\n", type);
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_RCPU_ENCAP_CTRL, &entry_handle_id));

    value = (arg & 0xffff);
    dbal_entry_value_field32_set(unit, entry_handle_id, field, INST_SINGLE, value);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *      _bcm_dnx_rcpu_switch_vlan_tpid_sig_get
 * Description:
 *      Helper function to get VLAN, TPID ot Signature for RCPU
 * Parameters:
 *      unit - Device unit number
 *  type - The desired configuration parameter to get
 *  arg - The value returned
 * Returns:
 *      BCM_E_xxx
 */
static int
_bcm_dnx_rcpu_switch_vlan_tpid_sig_get(
    int unit,
    bcm_switch_control_t type,
    int *arg)
{
    uint32 entry_handle_id, value;
    dbal_fields_e field;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    switch (type)
    {
        case bcmSwitchRemoteCpuVlan:
            field = DBAL_FIELD_VLAN_TCI;
            break;
        case bcmSwitchRemoteCpuTpid:
            field = DBAL_FIELD_TPID;
            break;
        case bcmSwitchRemoteCpuSignature:
            field = DBAL_FIELD_SIGNATURE;
            break;
        case bcmSwitchRemoteCpuEthertype:
            field = DBAL_FIELD_ETHERTYPE;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid type=%d\r\n", type);
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_RCPU_ENCAP_CTRL, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field, INST_SINGLE, &value));

    *arg = (int) value;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *      _bcm_dnx_rcpu_switch_mac_lo_set
 * Description:
 *      Set the low 24 bits of MAC address field for RCPU MAC registers
 * Parameters:
 *      unit        - StrataSwitch PCI device unit number (driver internal).
 *      port        - port number.
 *      type        - The required switch control type to set the mac for
 *      mac_lo      - MAC address
 * Returns:
 *      BCM_E_xxxx
 */
static int
_bcm_dnx_rcpu_switch_mac_lo_set(
    int unit,
    bcm_switch_control_t type,
    uint32 mac_lo)
{
    uint32 entry_handle_id, fieldval;
    dbal_fields_e field;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Given control type select field.
     */
    switch (type)
    {
        case bcmSwitchRemoteCpuLocalMacNonOui:
            field = DBAL_FIELD_SRC_MAC_LO;
            break;
        case bcmSwitchRemoteCpuDestMacNonOui:
            field = DBAL_FIELD_DST_MAC_LO;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid type=%d\r\n", type);
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_RCPU_ENCAP_CTRL, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field, INST_SINGLE, &fieldval));

    fieldval = (fieldval & 0xff000000) | (mac_lo & 0xffffff);
    dbal_entry_value_field32_set(unit, entry_handle_id, field, INST_SINGLE, fieldval);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *      _bcm_dnx_rcpu_switch_mac_hi_set
 * Description:
 *      Set the upper 24 bits of MAC address field for RCPU registers
 * Parameters:
 *      unit        - StrataSwitch PCI device unit number (driver internal).
 *      port        - port number.
 *      type        - The required switch control type to set upper MAC for
 *      mac_hi      - MAC address
 * Returns:
 *      BCM_E_xxxx
 */
static int
_bcm_dnx_rcpu_switch_mac_hi_set(
    int unit,
    bcm_switch_control_t type,
    uint32 mac_hi)
{
    uint32 entry_handle_id, fieldval;
    dbal_fields_e field_lo, field_hi;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Given control type select register.
     */
    switch (type)
    {
        case bcmSwitchRemoteCpuLocalMacOui:
            field_lo = DBAL_FIELD_SRC_MAC_LO;
            field_hi = DBAL_FIELD_SRC_MAC_HI;
            break;
        case bcmSwitchRemoteCpuDestMacOui:
            field_lo = DBAL_FIELD_DST_MAC_LO;
            field_hi = DBAL_FIELD_DST_MAC_HI;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid type=%d\r\n", type);
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_RCPU_ENCAP_CTRL, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field_lo, INST_SINGLE, &fieldval));
    fieldval = (fieldval & 0xffffff) | ((mac_hi & 0xff) << 24);
    dbal_entry_value_field32_set(unit, entry_handle_id, field_lo, INST_SINGLE, fieldval);

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field_hi, INST_SINGLE, &fieldval));
    fieldval = (mac_hi >> 8) & 0xffff;
    dbal_entry_value_field32_set(unit, entry_handle_id, field_hi, INST_SINGLE, fieldval);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *      _bcm_rcpu_switch_mac_lo_get
 * Description:
 *      Get the lower 24 bits of MAC address field for RCPU MAC registers
 * Parameters:
 *      unit        - StrataSwitch PCI device unit number (driver internal).
 *      port        - port number.
 *      type        - The required switch control type to get MAC for
 *      arg         - arg to get the lower MAC address
 * Returns:
 *      BCM_E_xxxx
 */
static int
_bcm_dnx_rcpu_switch_mac_lo_get(
    int unit,
    bcm_switch_control_t type,
    int *arg)
{
    uint32 entry_handle_id, fieldval;
    dbal_fields_e field;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Given control type select field.
     */
    switch (type)
    {
        case bcmSwitchRemoteCpuLocalMacNonOui:
            field = DBAL_FIELD_SRC_MAC_LO;
            break;
        case bcmSwitchRemoteCpuDestMacNonOui:
            field = DBAL_FIELD_DST_MAC_LO;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid type=%d\r\n", type);
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_RCPU_ENCAP_CTRL, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field, INST_SINGLE, &fieldval));

    *arg = (fieldval << 8) >> 8;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *      _bcm_rcpu_switch_mac_hi_get
 * Description:
 *      Get the upper 24 bits of MAC address field for RCPU MAC registers
 * Parameters:
 *      unit        - StrataSwitch PCI device unit number (driver internal).
 *      port        - port number.
 *      type        - The required switch control type to get MAC for
 *      arg         - arg to get the upper MAC address
 * Returns:
 *      BCM_E_xxxx
 */
static int
_bcm_dnx_rcpu_switch_mac_hi_get(
    int unit,
    bcm_switch_control_t type,
    int *arg)
{
    uint32 entry_handle_id, fieldval;
    dbal_fields_e field_lo, field_hi, mac;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Given control type select register.
     */
    switch (type)
    {
        case bcmSwitchRemoteCpuLocalMacOui:
            field_lo = DBAL_FIELD_SRC_MAC_LO;
            field_hi = DBAL_FIELD_SRC_MAC_HI;
            break;
        case bcmSwitchRemoteCpuDestMacOui:
            field_lo = DBAL_FIELD_DST_MAC_LO;
            field_hi = DBAL_FIELD_DST_MAC_HI;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid type=%d\r\n", type);
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_RCPU_ENCAP_CTRL, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field_lo, INST_SINGLE, &fieldval));
    mac = fieldval >> 24;

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field_hi, INST_SINGLE, &fieldval));
    mac |= fieldval << 8;

    *arg = (int) mac;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}
/*
 * }
 */
#endif /* #if defined(BCM_RCPU_SUPPORT) */

/**
 * see bcm_int/dnx/switch/switch.h
 */
shr_error_e
dnx_switch_network_group_id_verify(
    int unit,
    int is_ingress,
    bcm_switch_network_group_t network_group_id)
{

    uint32 nof_network_group_id;

    SHR_FUNC_INIT_VARS(unit);

    if (is_ingress == TRUE)
    {
        nof_network_group_id = dnx_data_lif.in_lif.in_lif_profile_allocate_orientation_get(unit);
    }
    else
    {
        nof_network_group_id = dnx_data_lif.out_lif.nof_out_lif_outgoing_orientation_get(unit);
    }

    if ((network_group_id < 0) || ((network_group_id >= nof_network_group_id) && (network_group_id != 0)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Error - network_group_id = %d, is out of rang [0:%d], is_ingress = %d.\n",
                     network_group_id, (nof_network_group_id - 1), is_ingress);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Verify function for dnx_switch_control_tunnel_route_disable_set
 *
 * \param [in] unit - unit Id
 * \param [in] arg - input flags (BCM_SWITCH_TUNNEL_ROUTE_DISABLE_XXX)
 *
 * \return
 *   shr_error_e - Error type
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_tunnel_route_disable_set_verify(
    int unit,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);
    /** Verify supported flags */
    if (_SHR_IS_FLAG_SET(arg, ~BCM_SWITCH_TUNNEL_ROUTE_DISABLE_SUPPORTED_FLAGS))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal Tunnel route disable flags are passed to the API.");
    }
    if (!dnx_data_tunnel.feature.tunnel_route_disable_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, " API is not supported for the device");
    }
exit:
    SHR_FUNC_EXIT;
}
/**
 * \brief -  Get out switch header type of port
 *
 * \param [in] unit - Relevant unit
 * \param [in] port - Port
 * \param [out] out_switch_header_type - Out switch port header type
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_header_type_out_get(
    int unit,
    bcm_port_t port,
    int *out_switch_header_type)
{

    bcm_trunk_t trunk_id = BCM_TRUNK_INVALID;
    uint32 in_switch_header_type = 0;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (BCM_GPORT_IS_TRUNK(port))
    {
        /** Get trunk id from port */
        trunk_id = BCM_GPORT_TRUNK_GET(port);
        SHR_IF_ERR_EXIT(dnx_trunk_header_types_get
                        (unit, trunk_id, &in_switch_header_type, (uint32 *) out_switch_header_type));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_header_type_out_get(unit, port, out_switch_header_type));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * See .h for reference
 */
shr_error_e
dnx_switch_header_type_in_get(
    int unit,
    bcm_port_t port,
    uint8 allow_port_in_lag,
    int *switch_header_type)
{
    uint32 in_switch_header_type;
    uint32 out_switch_header_type;
    int port_is_in_lag = 0;
    dnx_algo_gpm_gport_phy_info_t gport_info;
    bcm_gport_t gport;
    bcm_trunk_t trunk_id = BCM_TRUNK_INVALID;
    SHR_FUNC_INIT_VARS(unit);

    if (BCM_GPORT_IS_TRUNK(port))
    {
        trunk_id = BCM_GPORT_TRUNK_GET(port);
        SHR_IF_ERR_EXIT(dnx_trunk_header_types_get(unit, trunk_id, &in_switch_header_type, &out_switch_header_type));
        *switch_header_type = in_switch_header_type;
    }
    else
    {
        if (allow_port_in_lag)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_in_lag(unit, port, &port_is_in_lag));
            if (port_is_in_lag)
            {
                SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                                (unit, port, DNX_ALGO_GPM_GPORT_TO_PHY_OP_RETRIVE_SYS_PORT, &gport_info));
                BCM_GPORT_SYSTEM_PORT_ID_SET(gport, gport_info.sys_port);
                SHR_IF_ERR_EXIT(bcm_trunk_find(unit, -1, gport, &trunk_id));
                SHR_IF_ERR_EXIT(dnx_trunk_header_types_get
                                (unit, trunk_id, &in_switch_header_type, &out_switch_header_type));
                *switch_header_type = in_switch_header_type;
            }
            else
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_header_type_in_get(unit, port, switch_header_type));
            }
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_header_type_in_get(unit, port, switch_header_type));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get the switch header type of port for direction both (in,out)
 *
 * \param [in] unit - Relevant unit
 * \param [in] port - Port
 * \param [out] switch_header_type - Switch port header type
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_switch_header_type_both_get(
    int unit,
    bcm_port_t port,
    int *switch_header_type)
{
    uint32 in_switch_header_type;
    uint32 out_switch_header_type;
    bcm_trunk_t trunk_id;
    SHR_FUNC_INIT_VARS(unit);

    if (BCM_GPORT_IS_TRUNK(port))
    {
        trunk_id = BCM_GPORT_TRUNK_GET(port);
        SHR_IF_ERR_EXIT(dnx_trunk_header_types_get(unit, trunk_id, &in_switch_header_type, &out_switch_header_type));
        if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_ETH)
            && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_ETH))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_ETH;
        }
        else if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_RAW)
                 && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_RAW))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_RAW;
        }
        else if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW)
                 && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW;
        }
        else if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_INJECTED)
                 && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_INJECTED))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_INJECTED;
        }
        else if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_TM)
                 && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_TM))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_TM;
        }
        else
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Direction BOTH (in and out) API is only available for ETH, RAW, INJECTED, TM and MPLS_RAW header type trunk gports. Other types are non-directional. Please use bcm_switch_control_indexed_port_get API with direction IN or OUT instead. \n");
        }
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_header_type_in_get(unit, port, (int *) &in_switch_header_type));
        SHR_IF_ERR_EXIT(dnx_algo_port_header_type_out_get(unit, port, (int *) &out_switch_header_type));
        if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_ETH)
            && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_ETH))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_ETH;
        }
        else if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW)
                 && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW;
        }
        else if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_RAW)
                 && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_RAW))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_RAW;
        }
        else if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_INJECTED)
                 && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_INJECTED))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_INJECTED;
        }
        else if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_TM)
                 && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_TM))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_TM;
        }
        else if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_STACKING)
                 && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_STACKING))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_STACKING;
        }
        else if ((in_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_RCH_SRV6_USP_PSP)
                 && (out_switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_RCH_SRV6_USP_PSP))
        {
            *switch_header_type = BCM_SWITCH_PORT_HEADER_TYPE_RCH_SRV6_USP_PSP;
        }
        else
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Direction BOTH (in and out) API is only available for ETH, RAW, TM, INJECTED, MPLS_RAW, STACKING and RCH_SRV6_USP_PSP header types. Other types are non-directional. Please use bcm_switch_control_indexed_port_get API with direction IN or OUT instead. \n");
        }

    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Verify function used in dnx_switch_header_type_set_verify and dnx_switch_header_type_get_verify
 *   Used for verifying the direction and the used port
 */
static shr_error_e
dnx_switch_port_direction_verify(
    int unit,
    bcm_port_t port,
    int direction,
    int switch_header_type)
{
    SHR_FUNC_INIT_VARS(unit);

    if ((direction != DNX_SWITCH_PORT_HEADER_TYPE_INDEX_IN) &&
        (direction != DNX_SWITCH_PORT_HEADER_TYPE_INDEX_OUT) && (direction != DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Direction %d is not supported! It can be only BOTH (0), IN (1) or OUT (2)!",
                     direction);
    }

    if (!BCM_GPORT_IS_TRUNK(port))
    {
        dnx_algo_gpm_gport_phy_info_t gport_info;
        dnx_algo_port_info_s port_info;
        int is_lag;
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                        (unit, port, DNX_ALGO_GPM_GPORT_TO_PHY_OP_LOCAL_IS_MANDATORY, &gport_info));

        /** Get the port type */
        SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, gport_info.local_port, &port_info));
        SHR_IF_ERR_EXIT(dnx_algo_port_in_lag(unit, gport_info.local_port, &is_lag));

        if ((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_IN)
            && (!DNX_ALGO_PORT_TYPE_IS_ING_PP(unit, port_info, is_lag)))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Port %d is not ingress port! Direction IN can be used only for ingress ports!",
                         gport_info.local_port);
        }

        if ((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_OUT)
            && (!DNX_ALGO_PORT_TYPE_IS_EGR_PP(unit, port_info, is_lag)))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Port %d is not egress port! Direction OUT can be used only for egress ports!",
                         gport_info.local_port);
        }

        if ((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH)
            && ((!DNX_ALGO_PORT_TYPE_IS_ING_PP(unit, port_info, is_lag))
                || (!DNX_ALGO_PORT_TYPE_IS_EGR_PP(unit, port_info, is_lag))))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Port %d is not supported on both IN and OUT direction!", gport_info.local_port);
        }
    }
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Verify function for dnx_switch_header_type_get
 */
static shr_error_e
dnx_switch_header_type_get_verify(
    int unit,
    bcm_port_t port,
    int direction,
    int *switch_header_type)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(switch_header_type, _SHR_E_PARAM, "switch_header_type");
    SHR_IF_ERR_EXIT(dnx_switch_port_direction_verify(unit, port, direction, *switch_header_type));

exit:
    SHR_FUNC_EXIT;
}

/** See .h for reference */
int
dnx_switch_header_type_get(
    int unit,
    bcm_port_t port,
    int direction,
    int *switch_header_type)
{
    dnx_algo_gpm_gport_phy_info_t gport_info;

    SHR_FUNC_INIT_VARS(unit);

    if (!BCM_GPORT_IS_TRUNK(port))
    {
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                        (unit, port, DNX_ALGO_GPM_GPORT_TO_PHY_OP_LOCAL_IS_MANDATORY, &gport_info));
        port = gport_info.local_port;
    }

    SHR_INVOKE_VERIFY_DNXC(dnx_switch_header_type_get_verify(unit, port, direction, switch_header_type));

    switch (direction)
    {
        case DNX_SWITCH_PORT_HEADER_TYPE_INDEX_IN:
        {
            SHR_IF_ERR_EXIT(dnx_switch_header_type_in_get(unit, port, FALSE, switch_header_type));
            break;
        }
        case DNX_SWITCH_PORT_HEADER_TYPE_INDEX_OUT:
        {
            SHR_IF_ERR_EXIT(dnx_switch_header_type_out_get(unit, port, switch_header_type));
            break;
        }
        case DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH:
        {
            SHR_IF_ERR_EXIT(dnx_switch_header_type_both_get(unit, port, switch_header_type));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid direction =%d! It can be both (0), in (1) or out (2). \n", direction);
        }
    }
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Retrieve Port-attributes according to key
 *
 * \param [in] unit - Relevant unit
 * \param [in] port - Port
 * \param [in] key - Key index and key type
 * \param [out] value - Value that should be retrieved
 *
 * bcmSwitchPortHeaderType:
 * key.index can be 0, 1 and 2. 0 means both directions (in and out), 1 means 'in' and 2 means 'out'.
 * value indicates the port header type value according to BCM_SWITCH_PORT_HEADER_TYPE_XXX.
 *
 * \return
 *   int
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_control_indexed_port_get(
    int unit,
    bcm_port_t port,
    bcm_switch_control_key_t key,
    bcm_switch_control_info_t * value)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (key.type)
    {
        case bcmSwitchPortHeaderType:
        {
            SHR_IF_ERR_EXIT(dnx_switch_header_type_get(unit, port, key.index, &value->value));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Type %d is not supported!", key.type);
            break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*   API gets info for port-specific and device-wide operating
*   modes
* \par DIRECT INPUT:
*   \param [in] unit - unit ID
*   \param [in] port - port
*   \param [in] type - switch control type
*   \param [out] arg  - value
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   int -
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   *
* \see
*   * None
*/
int
bcm_dnx_switch_control_port_get(
    int unit,
    bcm_port_t port,
    bcm_switch_control_t type,
    int *arg)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (type)
    {
        case bcmSwitchMeterAdjust:
        {
            SHR_IF_ERR_EXIT(dnx_policer_mgmt_ingress_port_compensation_delta_get(unit, port, arg));
            break;
        }
        case bcmSwitchPrependTagEnable:
        {
            SHR_IF_ERR_EXIT(dnx_port_sit_prepend_tag_get(unit, port, arg));
            break;
        }
        case bcmSwitchTagPcpDeiSrc:
        {
            SHR_IF_ERR_EXIT(dnx_port_sit_tag_pcp_dei_src_get(unit, port, arg));
            break;
        }
        case bcmSwitchPortHeaderType:
        {
            bcm_switch_control_info_t value;
            bcm_switch_control_key_t key;
            value.value = 0;
            key.type = type;
            key.index = DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH;
            SHR_IF_ERR_EXIT(bcm_dnx_switch_control_indexed_port_get(unit, port, key, &value));
            *arg = value.value;
            break;
        }
        case bcmSwitchHashLayersDisable:
        {
            if (dnx_data_switch.load_balancing.hashing_selection_per_layer_get(unit))
            {
                SHR_IF_ERR_EXIT(dnx_port_load_balancing_hash_layers_disable_get(unit, port, (uint32 *) arg));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "The switch type bcmSwitchHashLayersDisable is not supported.");
            }
            break;
        }
        case bcmSwitchL3HeaderErrToCpu:
        {
            /*
             * No real used, internal testing only
             */
            SHR_IF_ERR_EXIT(dnx_switch_svtag_port_get(unit, port, (uint8 *) arg));
            break;
        }

        default:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Switch control not supported!, %d", type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Verify function for dnx_switch_header_type_set
 */
static shr_error_e
dnx_switch_header_type_set_verify(
    int unit,
    bcm_port_t port,
    int direction,
    int switch_header_type)
{
    dnx_algo_gpm_gport_phy_info_t gport_info;
    bcm_port_t local_port;
    dnx_algo_port_info_s port_info;
    int prd_enable_mode;
    int is_port_channelized = 0;
    int system_headers_mode = 0, ref_count = 0;
    dbal_enum_value_field_port_termination_ptc_profile_e old_prt_ptc_profile = 0;
    dnx_algo_skip_first_header_info_t profile_data;
    uint32 user_defined_port_type = DNX_PORT_FIRST_HEADER_SIZE_DATA_PORT_TYPE_NONE;
    dnx_algo_port_tdm_mode_e port_tdm_mode;
    SHR_FUNC_INIT_VARS(unit);

    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);

    if ((switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_ETH)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_TM)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_CPU)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RAW)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RAW_WITH_ORIGINAL_SYSTEM_HEADERS)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_ENCAP_EXTERNAL_CPU)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_TDM_ETH)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RCH_0)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RCH_1)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RCH_SRV6_USP_PSP)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_STACKING)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_IBCH1_MODE)
        && ((system_headers_mode != dnx_data_headers.system_headers.system_headers_mode_jericho_get(unit))
            && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP_JR1_MODE))
        && ((system_headers_mode != dnx_data_headers.system_headers.system_headers_mode_jericho_get(unit))
            && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_JR1_MODE)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Switch header type (%d) is not supported for system_headers_mode=%d!",
                     switch_header_type, system_headers_mode);
    }

    SHR_IF_ERR_EXIT(dnx_switch_port_direction_verify(unit, port, direction, switch_header_type));

    if ((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_IN) && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_ETH)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_TM)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RAW)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP_JR1_MODE)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_JR1_MODE)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_TDM_ETH)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RCH_0)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RCH_1)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RCH_SRV6_USP_PSP)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_STACKING)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_IBCH1_MODE))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Switch header type (%d) for direction IN is not supported for system_headers_mode=%d!",
                     switch_header_type, system_headers_mode);
    }

    if ((system_headers_mode == dnx_data_headers.system_headers.system_headers_mode_jericho2_get(unit)) &&
        ((switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP_JR1_MODE)
         || (switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_JR1_MODE)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Switch header type (%d) is not supported for system_headers_mode=%d!",
                     switch_header_type, system_headers_mode);
    }
    if ((!dnx_data_headers.
         system_headers.feature_get(unit, dnx_data_headers_system_headers_system_headers_ibch1_supported))
        && (switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_IBCH1_MODE))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Switch header type (IBCH1_MODE) is not supported for the device");
    }
    if ((dnx_data_headers.
         system_headers.feature_get(unit, dnx_data_headers_system_headers_system_headers_ibch1_supported))
        && ((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_IN)
            || (direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH))
        && ((switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_RCH_0)
            || (switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_RCH_1)
            || (switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_RCH_SRV6_USP_PSP)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Switch header type %d (direction %d) is not supported for the device",
                     switch_header_type, direction);
    }
    if (!dnx_data_port.general.feature_get(unit, dnx_data_port_general_is_header_type_rch_srv6_usp_psp_supported)
        && (switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_RCH_SRV6_USP_PSP))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Switch header type (RCH_SRV6_USP_PSP) is not supported for the device");
    }

    if ((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_IN) && (!BCM_GPORT_IS_TRUNK(port))
        && ((switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP)
            || (switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP_JR1_MODE)
            || (switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_JR1_MODE)))
    {
        /** Get the port type */
        SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, port, &port_info));
        if (DNX_ALGO_PORT_TYPE_IS_RCY_MIRROR(unit, port_info))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Switch port header type %d is not supported for port %d as it is RCY_MIRROR port!",
                         switch_header_type, port);
        }
    }

    if ((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_OUT) && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_ETH)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_CPU)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RAW)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RAW_WITH_ORIGINAL_SYSTEM_HEADERS)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_ENCAP_EXTERNAL_CPU)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_STACKING)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_TM)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RCH_SRV6_USP_PSP))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Switch header type (%d) for direction OUT is not supported!", switch_header_type);
    }

    if ((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_ETH)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RAW)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_INJECTED)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_TM)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_STACKING)
        && (switch_header_type != BCM_SWITCH_PORT_HEADER_TYPE_RCH_SRV6_USP_PSP))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Switch header type (%d) for direction BOTH is not supported!", switch_header_type);
    }

    /** Verify PRD is disabled for NIF ports */
    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get(unit, port, DNX_ALGO_GPM_GPORT_TO_PHY_OP_NONE, &gport_info));
    BCM_PBMP_ITER(gport_info.local_port_bmp, local_port)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, local_port, &port_info));
        SHR_IF_ERR_EXIT(dnx_algo_port_is_channelized_get(unit, local_port, &is_port_channelized));
        SHR_IF_ERR_EXIT(dnx_algo_port_tdm_get(unit, local_port, &port_tdm_mode));
        /*
         * When adding switch header type for channelized port which is not the master,
         * make sure that PRD is not enabled in case we set different header type then the one on master.
         * - Master and Slave - same header type , no PRD enabled - OK
         * - Master and Slave - different header type , no PRD enabled - OK
         * - Master and Slave - different header type , with PRD enabled - Error
         *
         * Exception: In case of ILKN there can be TDM and non-TDM channels, so checks above apply to
         * the non-TDM channels.
         */
        if (DNX_ALGO_PORT_TYPE_IS_NIF(unit, port_info, DNX_ALGO_PORT_TYPE_INCLUDE(STIF)) && is_port_channelized
            && direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_IN && port_tdm_mode == DNX_ALGO_PORT_TDM_MODE_NONE)
        {
            bcm_port_t port_channel = local_port;
            bcm_pbmp_t logical_port_channels;
            bcm_port_t logical_port_i;
            dnx_algo_port_info_s port_info;
            int is_lag;
            int port_channel_switch_header_type;

            /*
             * Get first channel of the port which is of Igress PP type and non-TDM. Then get its switch hreader type.
             */
            SHR_IF_ERR_EXIT(dnx_algo_port_channels_get(unit, local_port, 0, &logical_port_channels));
            BCM_PBMP_ITER(logical_port_channels, logical_port_i)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, logical_port_i, &port_info));
                SHR_IF_ERR_EXIT(dnx_algo_port_in_lag(unit, logical_port_i, &is_lag));
                /*
                 * Check if the channel is non-TDM
                 */
                SHR_IF_ERR_EXIT(dnx_algo_port_tdm_get(unit, logical_port_i, &port_tdm_mode));

                if (logical_port_i != local_port && DNX_ALGO_PORT_TYPE_IS_ING_PP(unit, port_info, is_lag)
                    && port_tdm_mode == DNX_ALGO_PORT_TDM_MODE_NONE)
                {
                    port_channel = logical_port_i;
                    break;
                }
            }

            /*
             * Do checks only if we found another channel of the interface with IN header type and non-TDM.
             */
            if (local_port != port_channel)
            {
                SHR_IF_ERR_EXIT(dnx_switch_header_type_get
                                (unit, port_channel, direction, &port_channel_switch_header_type));

                /*
                 * Check if PRD is enabled on the interface
                 */
                SHR_IF_ERR_EXIT(imb_prd_enable_get(unit, local_port, &prd_enable_mode));

                /*
                 * If PRD is enabled and Master and Slave have different switch headert types - Return error
                 */
                if (prd_enable_mode != bcmCosqIngressPortDropDisable
                    && port_channel_switch_header_type != switch_header_type)
                {
                    SHR_ERR_EXIT(_SHR_E_CONFIG,
                                 "Channelized ports %d and %d can't have different switch header types when PRD is enabled for the interface.\nPlease disable PRD.\n",
                                 local_port, port_channel);
                }
            }
        }

        if ((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_IN)
            || (direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH))
        {
            SHR_IF_ERR_EXIT(dnx_port_first_header_size_to_skip_port_type_from_port_header_type_convert
                            (unit, local_port, switch_header_type, &user_defined_port_type));
            /** Get the old ptc profile */
            SHR_IF_ERR_EXIT(dnx_port_prt_ptc_profile_get(unit, local_port, &old_prt_ptc_profile));
            if ((old_prt_ptc_profile == DBAL_ENUM_FVAL_PORT_TERMINATION_PTC_PROFILE_UD1)
                || (old_prt_ptc_profile == DBAL_ENUM_FVAL_PORT_TERMINATION_PTC_PROFILE_UD2)
                || (old_prt_ptc_profile == DBAL_ENUM_FVAL_PORT_TERMINATION_PTC_PROFILE_UD3)
                || (old_prt_ptc_profile == DBAL_ENUM_FVAL_PORT_TERMINATION_PTC_PROFILE_UD4)
                || (old_prt_ptc_profile == DBAL_ENUM_FVAL_PORT_TERMINATION_PTC_PROFILE_UD5)
                || (old_prt_ptc_profile == DBAL_ENUM_FVAL_PORT_TERMINATION_PTC_PROFILE_UD6))
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_db.skip_first_user_defined_header_size_profile_data.profile_data_get(unit,
                                                                                                                   old_prt_ptc_profile,
                                                                                                                   &ref_count,
                                                                                                                   &profile_data));
                if (profile_data.port_type != user_defined_port_type)
                {
                    /** Return an error in case that the user defined header is not from the same type as the new ptc profile */
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 "It is illegal to change the port header type! First should be disabled the skipping of the first header size for port %d!\n",
                                 local_port);
                }
            }
        }
    }

    if (((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH) || (direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_OUT))
        && (switch_header_type == BCM_SWITCH_PORT_HEADER_TYPE_TM))
    {
        if (!dnx_data_headers.otmh.feature_get(unit, dnx_data_headers_otmh_otmh_enable))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Switch header type (%d) for direction BOTH/OUT is not supported in this device!",
                         switch_header_type);

        }

        if (dnx_data_tdm.params.mode_get(unit) != TDM_MODE_NONE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Switch header type (%d) for direction BOTH/OUT is not supported when TDM is enabled!",
                         switch_header_type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_switch_bcm_to_dnx_header_type_convert(
    int unit,
    int bcm_header_type,
    dnx_algo_port_header_mode_e * dnx_header_type)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(dnx_header_type, _SHR_E_PARAM, "dnx_header_type");
    switch (bcm_header_type)
    {
        case BCM_SWITCH_PORT_HEADER_TYPE_TDM_ETH:
        case BCM_SWITCH_PORT_HEADER_TYPE_ETH:
        {
            *dnx_header_type = DNX_ALGO_PORT_HEADER_MODE_ETH;
            break;
        }
        case BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW:
        {
            *dnx_header_type = DNX_ALGO_PORT_HEADER_MODE_MPLS_RAW;
            break;
        }
        case BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP:
        case BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP_JR1_MODE:
        {
            *dnx_header_type = DNX_ALGO_PORT_HEADER_MODE_INJECTED_2_PP;
            break;
        }
        default:
        {
            *dnx_header_type = DNX_ALGO_PORT_HEADER_MODE_NON_PP;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Configure general Port-attributes according to key and value
 *
 * \param [in] unit - Relevant unit
 * \param [in] port - Port
 * \param [in] direction - Port direction
 * \param [in] switch_header_type - Header type that should be set
 *
 * Port direction can be 0, 1 and 2. 0 means both directions (in and out), 1 means 'in' and 2 means 'out'.
 *
 * \return
 *   int
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static int
dnx_switch_header_type_set(
    int unit,
    bcm_port_t port,
    int direction,
    int switch_header_type)
{

    bcm_port_t local_port;
    dnx_algo_port_header_mode_e header_mode;
    bcm_trunk_t trunk_id = BCM_TRUNK_INVALID;
    uint32 in_switch_header_type;
    uint32 out_switch_header_type;
    dnx_algo_gpm_gport_phy_info_t gport_info;
    dnx_algo_port_info_s port_info;
    int is_lag;

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_switch_header_type_set_verify(unit, port, direction, switch_header_type));

    /** Translate BCM Header type to DNX Header mode */
    SHR_IF_ERR_EXIT(dnx_switch_bcm_to_dnx_header_type_convert(unit, switch_header_type, &header_mode));

    if (BCM_GPORT_IS_TRUNK(port))
    {
        /** get gport info */
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get(unit, port, DNX_ALGO_GPM_GPORT_TO_PHY_OP_NONE, &gport_info));

        /** get trunk id from gport */
        trunk_id = BCM_GPORT_TRUNK_GET(port);
    }
    else
    {
        /** get gport info */
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                        (unit, port, DNX_ALGO_GPM_GPORT_TO_PHY_OP_LOCAL_IS_MANDATORY, &gport_info));

        /** Get the port type */
        SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, gport_info.local_port, &port_info));
        SHR_IF_ERR_EXIT(dnx_algo_port_in_lag(unit, gport_info.local_port, &is_lag));
    }

    if (direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH || direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_IN)
    {

        /** set header type/ header mode to SW-state */
        if (BCM_GPORT_IS_TRUNK(port))
        {
            SHR_IF_ERR_EXIT(dnx_trunk_header_types_get
                            (unit, trunk_id, &in_switch_header_type, &out_switch_header_type));
            in_switch_header_type = switch_header_type;
            SHR_IF_ERR_EXIT(dnx_trunk_header_types_set(unit, trunk_id, in_switch_header_type, out_switch_header_type));
        }
        else
        {
            /** Modify SW state */
            SHR_IF_ERR_EXIT(dnx_algo_port_header_type_in_set(unit, gport_info.local_port, switch_header_type));

            if (!DNX_ALGO_PORT_TYPE_IS_RCY_MIRROR(unit, port_info))
            {
                for (int pp_port_index = 0; pp_port_index < gport_info.internal_port_pp_info.nof_pp_ports;
                     pp_port_index++)
                {
                    dnx_algo_port_db.pp.header_mode.set(unit, gport_info.internal_port_pp_info.core_id[pp_port_index],
                                                        gport_info.internal_port_pp_info.pp_port[pp_port_index],
                                                        header_mode);
                }
            }
        }

        if (BCM_GPORT_IS_TRUNK(port) || !DNX_ALGO_PORT_TYPE_IS_RCY_MIRROR(unit, port_info))
        {
            /*
             * Port Ethernet bitmap is considered only for incoming port
             * RCY_MIRROR ports are internal ports and should not be added to Ethernet bitmap
             */
            BCM_PBMP_ITER(gport_info.local_port_bmp, local_port)
            {
                SHR_IF_ERR_EXIT(dnx_algo_port_soc_info_port_eth_bitmap_set(unit, local_port, header_mode));
            }

            /*
             * Configure Ingress Ethernet properties
             * For mirror ports no Ethernet properties should be configured
             */
            SHR_IF_ERR_EXIT(dnx_port_initial_eth_properties_set(unit, port, switch_header_type));
        }
        else
        {
            /*
             * Set the parsing context of rcy_mirror port to NOP
             */
            SHR_IF_ERR_EXIT(dnx_port_pp_parsing_context_set
                            (unit, port, DBAL_ENUM_FVAL_IRPP_1ST_PARSER_PARSER_CONTEXT_NOP));
        }

        if (!BCM_GPORT_IS_TRUNK(port))
        {
            /** Configure Port Termination PTC Profile according to the switch header type */
            SHR_IF_ERR_EXIT(dnx_port_pp_prt_ptc_profile_set(unit, port, switch_header_type));
        }

    }
    /** Configure the outgoing port */
    if ((direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_OUT || direction == DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH))
    {
        if (BCM_GPORT_IS_TRUNK(port) || DNX_ALGO_PORT_TYPE_IS_EGR_PP(unit, port_info, is_lag))
        {
            SHR_IF_ERR_EXIT(dnx_port_pp_egress_set(unit, port, switch_header_type));
            SHR_IF_ERR_EXIT(dnx_port_estimate_header_mode_set(unit, port, switch_header_type));
        }

        if (BCM_GPORT_IS_TRUNK(port))
        {
            SHR_IF_ERR_EXIT(dnx_trunk_header_types_get
                            (unit, trunk_id, &in_switch_header_type, &out_switch_header_type));
            out_switch_header_type = switch_header_type;
            SHR_IF_ERR_EXIT(dnx_trunk_header_types_set(unit, trunk_id, in_switch_header_type, out_switch_header_type));
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_header_type_out_set(unit, gport_info.local_port, switch_header_type));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Configure general Port-attributes according to key and value
 *
 * \param [in] unit - Relevant unit
 * \param [in] port - Port
 * \param [in] key - Key index and key type.
 * \param [in] value - Value that should be set
 * bcmSwitchPortHeaderType:
 * key.index can be 0, 1 and 2. 0 means both directions (in and out), 1 means 'in' and 2 means 'out'.
 * value indicates the port header type value according to BCM_SWITCH_PORT_HEADER_TYPE_XXX.
 *
 * \return
 *   int
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_control_indexed_port_set(
    int unit,
    bcm_port_t port,
    bcm_switch_control_key_t key,
    bcm_switch_control_info_t value)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (key.type)
    {
        case bcmSwitchPortHeaderType:
        {
            SHR_IF_ERR_EXIT(dnx_switch_header_type_set(unit, port, key.index, value.value));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Type %d is not supported!", key.type);
            break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*   API gets info for port-specific and device-wide operating
*   modes
*
* Use cases:
*
* 1.
* Description
* Parameters:
* - type -
* - arg -
*
* 130.
* Meter - set ingress compensation delta value per port
* Parameters:
* - type - bcmSwitchMeterAdjust
* - arg -  delta value in range (-64) - (+63)
*
* 739.
* Sets TM port header type.
* Parameters:
* -type - bcmSwitchPortHeaderType
* -arg - BCM_SWITCH_PORT_HEADER_TYPE_ETH, BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP, BCM_SWITCH_PORT_HEADER_TYPE_MPLS_RAW
*
* \par DIRECT INPUT:
*   \param [in] unit - unit ID
*   \param [in] port - port
*   \param [in] type - switch control type
*   \param [in] arg  - value
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   int -
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   *
* \see
*   * None
*/
int
bcm_dnx_switch_control_port_set(
    int unit,
    bcm_port_t port,
    bcm_switch_control_t type,
    int arg)
{
    bcm_switch_control_key_t key;
    bcm_switch_control_info_t value;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    key.type = type;
    key.index = DNX_SWITCH_PORT_HEADER_TYPE_INDEX_BOTH;
    value.value = arg;

    /*
     * Use case per type
     */
    switch (type)
    {
        case bcmSwitchMeterAdjust:
        {
            SHR_IF_ERR_EXIT(dnx_policer_mgmt_ingress_port_compensation_delta_set(unit, port, arg));
            break;
        }
        case bcmSwitchPrependTagEnable:
        {
            SHR_IF_ERR_EXIT(dnx_port_sit_prepend_tag_set(unit, port, (arg ? 1 : 0)));
            break;
        }
        case bcmSwitchTagPcpDeiSrc:
        {
            SHR_IF_ERR_EXIT(dnx_port_sit_tag_pcp_dei_src_set(unit, port, arg));
            break;
        }
        case bcmSwitchPortHeaderType:
        {
            SHR_IF_ERR_EXIT(bcm_dnx_switch_control_indexed_port_set(unit, port, key, value));
            break;
        }
        case bcmSwitchHashLayersDisable:
        {
            if (dnx_data_switch.load_balancing.hashing_selection_per_layer_get(unit))
            {
                SHR_IF_ERR_EXIT(dnx_port_load_balancing_hash_layers_disable_set(unit, port, (uint32) arg));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The switch type bcmSwitchHashLayersDisable is not supported.");
            }
            break;
        }
        case bcmSwitchL3HeaderErrToCpu:
        {
            /*
             * No real used, internal testing only
             * In case the second bit is on don't use this option 
             */
            if (BCM_GPORT_IS_TRUNK(port) && ((arg & 0x2) == 0))
            {
                int pool;
                int group;
                int trunk_id = BCM_GPORT_TRUNK_GET(port);
                BCM_TRUNK_ID_POOL_GET(pool, trunk_id);
                BCM_TRUNK_ID_GROUP_GET(group, trunk_id);
                SHR_IF_ERR_EXIT(dnx_sec_db.control_sec.trunk_info.is_macsec_enabled.set(unit, pool, group, arg & 0x1));
            }

            SHR_IF_ERR_EXIT(dnx_switch_svtag_port_set(unit, port, (uint8) (arg & 0x1)));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Switch control not supported!, %d", type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

#ifdef BCM_WARM_BOOT_SUPPORT

/*
 * performs a full sync
 */

static int
_bcm_dnx_switch_control_sync(
    int unit,
    int arg)
{
    int rv = _SHR_E_NONE;
    int lock_taken = FALSE;
    SHR_FUNC_INIT_VARS(unit);
    /*
     * Set flag TRUE, which indicates that sync started.
     */
    SHR_IF_ERR_EXIT(dnxc_sw_state_alloc_during_sync_set(unit, TRUE));

    rv = mdb_lpm_db_kaps_sync(unit);
    SHR_IF_ERR_EXIT(rv);

#if defined(INCLUDE_KBP)
    rv = kbp_mngr_wb_sync(unit);
    SHR_IF_ERR_EXIT(rv);
#endif

    rv = bcm_common_sat_wb_sync(unit, 0);
    SHR_IF_ERR_EXIT(rv);

#ifdef BCM_CMICM_SUPPORT
    if (dnx_drv_soc_feature(unit, soc_feature_cmicm))
    {
        soc_cmic_uc_msg_apps_notify(unit, SOC_CMIC_UC_SHUTDOWN_NOHALT);
    }
#endif /* BCM_CMICM_SUPPORT */


    /*
     * Take counter processor's dma fifos lock. mainly to not allow changing the state while main thread is syncing
     */
    {
        rv = dnx_crps_fifo_state_lock_take(unit);
        SHR_IF_ERR_EXIT(rv);
        lock_taken = TRUE;
    }

    /*
     * commit the scache to persistent storage (all scache buffers)
     */
    rv = soc_scache_commit(unit);
    SHR_IF_ERR_EXIT(rv);
    {
        /*
         * Mark scache as clean
         */
        uint32 *scache_dirty_p;

        SHR_IF_ERR_EXIT(soc_control_element_address_get(unit, SCACHE_DIRTY, (void **) (&scache_dirty_p)));
        dnx_drv_soc_control_lock(unit);
        *scache_dirty_p = 0;
        dnx_drv_soc_control_unlock(unit);
    }
    SHR_IF_ERR_EXIT(rv);

exit:
    /*
     * Set flag FALSE, which indicates that sync finished.
     */
    SHR_IF_ERR_EXIT(dnxc_sw_state_alloc_during_sync_set(unit, FALSE));

    if (lock_taken)
    {
        /*
         * Give counter processor's dma fifos lock.
         */
        rv = dnx_crps_fifo_state_lock_give(unit);
        SHR_IF_ERR_EXIT(rv);
    }
#ifdef BCM_WARM_BOOT_SUPPORT
    /*
     * don't perform wb reset test on switch control API that was called for wb sync
     */
    dnxc_wb_test_mode_skip_wb_sequence(unit);
#endif /* BCM_WARM_BOOT_SUPPORT */
    SHR_FUNC_EXIT;
}

#endif /* BCM_WARM_BOOT_SUPPORT */

/* Manual sync + stop all active bg threads is made by API bcm_switch_control_set
 * (type=bcmSwitchControlSync, arg= BCM_SWITCH_CONTROL_SYNC_FULL)
 * this call should be made immediately before exiting the driver.
 */

static int
dnx_switch_control_sync_handle(
    int unit,
    int arg)
{
    int rv = BCM_E_NONE;
    SHR_FUNC_INIT_VARS(unit);

#if defined(BCM_WARM_BOOT_SUPPORT)
    if (arg == BCM_SWITCH_CONTROL_SYNC_FULL)
    {
        /** disable the eviction from crps engine, read all counters and disconnect the DMA_FIFO and bg thread. */
        /** After this operation, crps counters will not update the sw state and sync can be made */

        {
            rv = dnx_crps_eviction_disable_wrapper(unit);
            SHR_IF_ERR_EXIT(rv);
        }

        /** disable the eviction from crps engine, read all counters and disconnect the DMA_FIFO and bg thread. */
        /** After this operation, crps counters will not update the sw state and sync can be made */
        rv = soc_counter_stop(unit);
        SHR_IF_ERR_EXIT(rv);

        {
            int is_active;
            /*
             * Stops temp monitoring thread, thread has to be active.
             */
            SHR_IF_ERR_EXIT(dnx_hbmc_temp_monitor_is_active(unit, &is_active));
            if (is_active)
            {
                rv = dnx_hbmc_temp_monitor_pause(unit);
                SHR_IF_ERR_EXIT(rv);
            }
        }

        if (dnx_data_nif.framer.feature_get(unit, dnx_data_nif_framer_is_supported))
        {
            SHR_IF_ERR_EXIT(flexe_core_sync(unit));
        }
    }

    if (!sw_state_is_warm_boot(unit))
    {
        rv = _bcm_dnx_switch_control_sync(unit, arg);
        SHR_IF_ERR_EXIT(rv);
    }
#else
    rv = _SHR_E_UNAVAIL;
    SHR_IF_ERR_EXIT(rv);
#endif

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - configures traverse mode of the MDB-LEM. Move from different bulk states and normal traverse. In bulk traverse the rules are set and then the
 *        flush starts. In normal mode the flush machine is running after each rule that is set.
 */
static shr_error_e
dnx_switch_traverse_mode_set(
    int unit,
    int flush_mode)
{
    SHR_FUNC_INIT_VARS(unit);

    switch (flush_mode)
    {
        case bcmSwitchTableUpdateNormal:
        {
            SHR_IF_ERR_EXIT(dbal_bulk_mode_set(unit, DBAL_ACCESS_METHOD_MDB, DBAL_BULK_MODULE_MDB_LEM_FLUSH, 0));
            break;
        }
        case bcmSwitchTableUpdateRuleAdd:
        {
            SHR_IF_ERR_EXIT(dbal_bulk_mode_set(unit, DBAL_ACCESS_METHOD_MDB, DBAL_BULK_MODULE_MDB_LEM_FLUSH, 1));
            break;
        }
        case bcmSwitchTableUpdateRuleClear:
        {
            SHR_IF_ERR_EXIT(dbal_bulk_clear(unit, DBAL_ACCESS_METHOD_MDB, DBAL_BULK_MODULE_MDB_LEM_FLUSH));
            break;
        }
        case bcmSwitchTableUpdateRuleCommit:
        {
            SHR_IF_ERR_EXIT(dbal_bulk_commit(unit, DBAL_ACCESS_METHOD_MDB, DBAL_BULK_MODULE_MDB_LEM_FLUSH));
            break;
        }
        case bcmSwitchTableUpdateRuleCommitNonBlocking:
        {
            SHR_IF_ERR_EXIT(dbal_bulk_commit
                            (unit, DBAL_ACCESS_METHOD_MDB, DBAL_BULK_MODULE_MDB_LEM_NON_BLOCKING_FLUSH));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported flush mode");
            break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Sync function for KBP (External TCAM)
* \param [in] unit        - Device Id
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None.
*/
static int
dnx_switch_control_external_tcam_sync_handle(
    int unit)
{
    int device_locked;
    int device_exists;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_map_is_external_tcam_available(unit, &device_exists));
    if (!device_exists)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "External TCAM device is not enabled\n");
    }

    /** If bcm_switch_control_set() type=bcmSwitchExternalTcamSync was called - print warning and do nothing */
    SHR_IF_ERR_EXIT(dnx_field_map_is_device_locked(unit, &device_locked));
    if (device_locked)
    {
        LOG_WARN(BSL_LS_BCM_SWITCH, (BSL_META_U(unit, "Warning: External TCAM device is already synced\n")));
        SHR_EXIT();
    }
    /*
     * Apply the ACL configuration and sunc (Lock) the External Tcam device
     */
    SHR_IF_ERR_EXIT(dnx_field_group_external_tcam_sync_set(unit));

exit:
    SHR_FUNC_EXIT;
}
/**
* \brief
*  Init/De-init function for KBP (External TCAM)
* \param [in] unit        - Device Id
* \param [in] arg         - Init or De-init
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None.
*/
static int
dnx_switch_control_external_tcam_init_deinit_handle(
    int unit,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);

#if defined(INCLUDE_KBP)
    if (arg)
    {
        SHR_IF_ERR_EXIT(dnx_kbp_init(unit));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_kbp_deinit(unit));
    }
#else
    SHR_ERR_EXIT(_SHR_E_CONFIG, "KBP is not compiled");
#endif
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set routed learning mode for supported applications according to input flags
 *
 * \param [in] unit - unit Id
 * \param [in] arg - input flags (BCM_SWITCH_CONTROL_L3_LEARN_XXX)
 *
 * \return
 *   shr_error_e - Error type
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_routed_learn_set(
    int unit,
    int arg)
{
    uint32 entry_handle_id;
    char field_name[DBAL_MAX_STRING_LENGTH];
    char field_name_substr[DNX_SWITCH_FIELD_NAME_MAX_SUBSTRING_LENGTH] = { 0 };
    char **field_name_tokens = NULL;
    unsigned int num_of_tokens;
    uint8 learn_enable;
    size_t str_len = sizeof(field_name) - 1;
    dbal_fields_e next_field_id;
    uint8 ipv4_uc_learn_enable, ipv4_mc_learn_enable, ipv6_uc_learn_enable, ipv6_mc_learn_enable, mpls_learn_enable;
    int nof_ipv4_host_entries = 0, nof_ipv6_host_entries = 0;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    ipv4_uc_learn_enable = _SHR_IS_FLAG_SET(arg, BCM_SWITCH_CONTROL_L3_LEARN_IPV4_UC);
    ipv4_mc_learn_enable = _SHR_IS_FLAG_SET(arg, BCM_SWITCH_CONTROL_L3_LEARN_IPV4_MC);
    ipv6_uc_learn_enable = _SHR_IS_FLAG_SET(arg, BCM_SWITCH_CONTROL_L3_LEARN_IPV6_UC);
    ipv6_mc_learn_enable = _SHR_IS_FLAG_SET(arg, BCM_SWITCH_CONTROL_L3_LEARN_IPV6_MC);
    mpls_learn_enable = _SHR_IS_FLAG_SET(arg, BCM_SWITCH_CONTROL_L3_LEARN_MPLS);

    {
        SHR_IF_ERR_EXIT(DBAL_SW_STATE_TBL_PROP.
                        nof_entries.get(unit, DBAL_TABLE_IPV4_UNICAST_PRIVATE_HOST, &nof_ipv4_host_entries));
        SHR_IF_ERR_EXIT(DBAL_SW_STATE_TBL_PROP.
                        nof_entries.get(unit, DBAL_TABLE_IPV6_UNICAST_PRIVATE_HOST, &nof_ipv6_host_entries));
        if (nof_ipv4_host_entries || nof_ipv6_host_entries)
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Couldn't switch on/off routing learning when host entry number:%d isn't 0",
                         (nof_ipv4_host_entries + nof_ipv6_host_entries));
        }
    }

    /** Save router learning value (bitmap) */
    SHR_IF_ERR_EXIT(l2_db_context.routing_learning.set(unit, arg));

    /*
     * Routed learning is controlled by PEMLA_FWD1_CONTEXT_LEARN_ALLOWED table.
     * We are deciding which of it's fields should be set according to the field names.
     * Assumptions:
     * 1. all fields names include 3 sub-string separated by "___"
     * 2. 1st sub-string is always "FWD1"
     * 3. 2nd sub-string indicated the application type, e.g MPLS, IPV4, FCOE etc.
     * 4. 3rd sub-string indicates specific characteristics. in IPvX related fields, UC/MC indication exists in the sub-string.
     *
     * Going over all the field names and deciding according to the input flags which should be set.
     */
    if (ipv4_uc_learn_enable || ipv6_uc_learn_enable)
    {
        {
            sal_strncpy(field_name_substr, "_UC", sizeof(field_name_substr) - 1);
        }
    }

    /** Get table info (in order to go over the fields names) */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_FWD1_CONTEXT_LEARN_ALLOWED, &entry_handle_id));

    SHR_IF_ERR_EXIT(dbal_tables_next_field_get
                    (unit, DBAL_TABLE_PEMLA_FWD1_CONTEXT_LEARN_ALLOWED, DBAL_FIELD_EMPTY, 0, 0, &next_field_id));
    while (next_field_id != DBAL_FIELD_EMPTY)
    {
        learn_enable = 0;
        sal_memset(field_name, 0, sizeof(field_name));

        if (sal_strnlen(dbal_field_to_string(unit, next_field_id), SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH) <
            sizeof(field_name))
        {
            str_len =
                sal_strnlen(dbal_field_to_string(unit, next_field_id), SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH);
        }

        /** Get sub-strings separated by "___" */
        sal_strncpy(field_name, dbal_field_to_string(unit, next_field_id), str_len);
        field_name_tokens = utilex_str_split(field_name, "___", 3, &num_of_tokens);

        /*
         * validating assumption #1
         *
         * Although (num_of_tokens != 3) guarantees that (field_name_tokens != NULL), to prevent Coverity comment above
         * each appearance of field_name_tokens the NULL check is performed.
         */
        if ((field_name_tokens == NULL) || (num_of_tokens != 3))
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Unexpected field name structure");
        }

        if (ipv4_uc_learn_enable)
        {
            if (sal_strncmp
                ("IPV4", field_name_tokens[1],
                 sal_strnlen(field_name_tokens[1], SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH)) == 0)
            {
                if (sal_strnstr(field_name_tokens[2], field_name_substr, SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH)
                    != NULL)
                {
                    learn_enable = 1;
                }
            }
        }
        if (ipv4_mc_learn_enable && (learn_enable == 0))
        {
            if (sal_strncmp
                ("IPV4", field_name_tokens[1],
                 sal_strnlen(field_name_tokens[1], SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH)) == 0)
            {
                if (sal_strnstr(field_name_tokens[2], "MC_", SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH) != NULL)
                {
                    learn_enable = 1;
                }
            }
        }
        if (ipv6_uc_learn_enable && (learn_enable == 0))
        {
            if (sal_strncmp
                ("IPV6", field_name_tokens[1],
                 sal_strnlen(field_name_tokens[1], SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH)) == 0)
            {
                if (sal_strnstr(field_name_tokens[2], field_name_substr, SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH)
                    != NULL)
                {
                    learn_enable = 1;
                }
            }
        }
        if (ipv6_mc_learn_enable && (learn_enable == 0))
        {
            if (sal_strncmp
                ("IPV6", field_name_tokens[1],
                 sal_strnlen(field_name_tokens[1], SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH)) == 0)
            {
                if (sal_strnstr(field_name_tokens[2], "MC_", SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH) != NULL)
                {
                    learn_enable = 1;
                }
            }
        }
        if (mpls_learn_enable && (learn_enable == 0))
        {
            if (sal_strncmp
                ("MPLS", field_name_tokens[1],
                 sal_strnlen(field_name_tokens[1], SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH)) == 0)
            {
                learn_enable = 1;
            }
        }

        dbal_entry_value_field8_set(unit, entry_handle_id, next_field_id, INST_SINGLE, learn_enable);

        utilex_str_split_free(field_name_tokens, num_of_tokens);
        field_name_tokens = NULL;

        SHR_IF_ERR_EXIT(dbal_tables_next_field_get
                        (unit, DBAL_TABLE_PEMLA_FWD1_CONTEXT_LEARN_ALLOWED, next_field_id, 0, 0, &next_field_id));
    }

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_application_v1))
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_PEMLA_MACTSOURCELKP, entry_handle_id));
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IPV4UC, INST_SINGLE, ipv4_uc_learn_enable);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IPV4MC, INST_SINGLE, ipv4_mc_learn_enable);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IPV6UC, INST_SINGLE, ipv6_uc_learn_enable);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IPV6MC, INST_SINGLE, ipv6_mc_learn_enable);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MPLS, INST_SINGLE, mpls_learn_enable);

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    if (field_name_tokens != NULL)
    {
        utilex_str_split_free(field_name_tokens, num_of_tokens);
    }
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** See .h for reference */
shr_error_e
dnx_switch_control_routed_learn_get(
    int unit,
    int *arg)
{
    uint32 routed_learning;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(l2_db_context.routing_learning.get(unit, &routed_learning));
    *arg = routed_learning;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set tunnel route disable mode for supported applications according to input flags
 *
 * \param [in] unit - unit Id
 * \param [in] arg - input flags (BCM_SWITCH_TUNNEL_ROUTE_DISABLE_XXX)
 *
 * \return
 *   shr_error_e - Error type
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_tunnel_route_disable_set(
    int unit,
    int arg)
{
    uint8 tcp_tunnel_route_disable, udp_tunnel_route_disable, icmp_tunnel_route_disable,
        unknown_tunnel_route_disable, gre_keep_alive_tunnel_route_disable, igmp_tunnel_route_disable;
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_switch_control_tunnel_route_disable_set_verify(unit, arg));

    /**Based on the input flags, decide whether to enable/disable the Context selection*/
    if (arg == BCM_SWITCH_TUNNEL_ROUTE_DISABLE_NONE)
    {
        tcp_tunnel_route_disable = 0;
        udp_tunnel_route_disable = 0;
        icmp_tunnel_route_disable = 0;
        unknown_tunnel_route_disable = 0;
        gre_keep_alive_tunnel_route_disable = 0;
        igmp_tunnel_route_disable = 0;
    }
    else
    {
        tcp_tunnel_route_disable = ((arg & BCM_SWITCH_TUNNEL_ROUTE_DISABLE_TCP) ? 1 : 0);
        udp_tunnel_route_disable = ((arg & BCM_SWITCH_TUNNEL_ROUTE_DISABLE_UDP) ? 1 : 0);
        icmp_tunnel_route_disable = ((arg & BCM_SWITCH_TUNNEL_ROUTE_DISABLE_ICMP) ? 1 : 0);
        unknown_tunnel_route_disable = ((arg & BCM_SWITCH_TUNNEL_ROUTE_DISABLE_UNKNOWN) ? 1 : 0);
        gre_keep_alive_tunnel_route_disable = ((arg & BCM_SWITCH_TUNNEL_ROUTE_DISABLE_GRE_KEEP_ALIVE) ? 1 : 0);
        igmp_tunnel_route_disable = ((arg & BCM_SWITCH_TUNNEL_ROUTE_DISABLE_IGMP) ? 1 : 0);
    }

    /** Save in SW state the values of the input flags */
    SHR_IF_ERR_EXIT(switch_db.tunnel_route_disabled.set(unit, arg));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_DISABLE_TUNNEL, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_GRE_KEEP_ALIVE, INST_SINGLE,
                                 gre_keep_alive_tunnel_route_disable);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ICMP, INST_SINGLE, icmp_tunnel_route_disable);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IGMP, INST_SINGLE, igmp_tunnel_route_disable);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TCP, INST_SINGLE, tcp_tunnel_route_disable);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDP, INST_SINGLE, udp_tunnel_route_disable);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UNKNOWN, INST_SINGLE, unknown_tunnel_route_disable);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get tunnel route disable flags
 *
 * \param [in] unit - unit Id
 * \param [out] arg - flags (BCM_SWITCH_TUNNEL_ROUTE_DISABLE_XXX)
 *
 * \return
 *   shr_error_e - Error type
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_tunnel_route_disable_get(
    int unit,
    int *arg)
{
    uint32 tunnel_route_disable;

    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_tunnel.feature.tunnel_route_disable_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, " API is not supported for the device \n");
    }
    SHR_IF_ERR_EXIT(switch_db.tunnel_route_disabled.get(unit, &tunnel_route_disable));
    *arg = tunnel_route_disable;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set per port special label termination 
 *
 * \param [in] unit - unit Id
 * \param [in] arg - enabel/disable
 *
 * \return
 *   shr_error_e - Error type
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_per_port_special_label_termination_disable_set(
    int unit,
    int arg)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(switch_db.per_port_special_label_termination_disabled.set(unit, arg));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_MPLS_TERM, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SPECIAL_LABEL_TERMINATION_PER_PORT, INST_SINGLE,
                                 (arg == 1) ? 0 : 1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get per port special label termination state
 *
 * \param [in] unit - unit Id
 * \param [out] arg - state 
 *
 * \return
 *   shr_error_e - Error type
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_per_port_special_label_termination_disable_get(
    int unit,
    int *arg)
{
    uint32 disable;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(switch_db.per_port_special_label_termination_disabled.get(unit, &disable));
    *arg = disable;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set pre tunnel termination IPv4 VRF reselect enable
 *
 * \param [in] unit - unit Id
 * \param [in] arg - enable
 *
 * \return
 *   shr_error_e - Error type
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_switch_control_tunnel_termination_ipv4_vrf_reselect_enable_set(
    int unit,
    int arg)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (!dnx_data_l3.feature.feature_get(unit, dnx_data_l3_feature_vpbr_tunnel_available))
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, " API is not supported for the device");
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_TT_IPV4_VRF_RESELECT, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ENABLE_RESELECT, INST_SINGLE, (arg ? 1 : 0));
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get pre tunnel termination IPv4 VRF reselect enable
 *
 * \param [in] unit - unit Id
 * \param [out] arg - enable
 *
 * \return
 *   shr_error_e - Error type
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_switch_control_tunnel_termination_ipv4_vrf_reselect_enable_get(
    int unit,
    int *arg)
{
    uint32 entry_handle_id;
    uint32 enable;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (!dnx_data_l3.feature.feature_get(unit, dnx_data_l3_feature_vpbr_tunnel_available))
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, " API is not supported for the device");
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_TT_IPV4_VRF_RESELECT, &entry_handle_id));
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_ENABLE_RESELECT, INST_SINGLE, &enable);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    *arg = enable;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  Set the default forwarding destination for all programs in FWD1 and FWD2 to be the given trap ID
 * \param [in] unit - unit ID
 * \param [in] trap_id - the ID of the trap type (bcm_rx_trap_t) which will be configured as destination.
 * \return
 *   shr_error_e - Error type
 */
static shr_error_e
dnx_switch_fwd_not_found_trap_set(
    int unit,
    int trap_id)
{
    uint8 is_default_image = FALSE;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_pp_prgm_default_image_check(unit, &is_default_image));

    if (is_default_image)
    {
        uint32 entry_handle_id;
        uint32 trap_dest_w_default_bit;
        uint32 trap_dest;
        bcm_gport_t trap_gport;

        BCM_GPORT_TRAP_SET(trap_gport, trap_id, dnx_data_trap.strength.default_trap_strength_get(unit), 0);
        SHR_IF_ERR_EXIT(algo_gpm_encode_destination_field_from_gport
                        (unit, ALGO_GPM_ENCODE_DESTINATION_FLAGS_NONE, trap_gport, &trap_dest));
        trap_dest_w_default_bit = trap_dest << 1 | 0x1;
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_ING_FWD_DEFAULT_FORWARD_RESULT, &entry_handle_id));
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DEFAULT_GROUP_NON_MPLS, INST_SINGLE,
                                     trap_dest_w_default_bit);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  Receive the default forwarding destination
 *  which has been set using dnx_switch_fwd_not_found_trap_set
 *  for all programs in FWD1 and FWD2.
 * \param [in] unit - unit ID
 * \param [out] trap_id - the ID of the trap which is set.
 * \return
 *   shr_error_e - Error type
 */
static shr_error_e
dnx_switch_fwd_not_found_trap_get(
    int unit,
    int *trap_id)
{
    uint32 entry_handle_id;
    uint32 trap_dest;
    uint32 trap_dest_w_default_bit;
    bcm_gport_t trap_gport;
    uint8 is_default_image = FALSE;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_pp_prgm_default_image_check(unit, &is_default_image));

    if (is_default_image)
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_ING_FWD_DEFAULT_FORWARD_RESULT, &entry_handle_id));
        SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                        (unit, entry_handle_id, DBAL_FIELD_DEFAULT_GROUP_NON_MPLS, INST_SINGLE,
                         &trap_dest_w_default_bit));

        trap_dest = trap_dest_w_default_bit >> 1;
        SHR_IF_ERR_EXIT(algo_gpm_gport_from_encoded_destination_field
                        (unit, ALGO_GPM_ENCODE_DESTINATION_FLAGS_NONE, trap_dest, &trap_gport));
        *trap_id = BCM_GPORT_TRAP_GET_ID(trap_gport);
    }
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}
/**
 * \brief - Configure expected UDP destination port at parser to
 * identify UDP next protocol.
 * \param [in] unit - Relevant unit.
 * \param [in] field_e - field per udp next protocol.
 * \param [in] udp_destination_port_value - new udp destination
 *        port value for next protocol
 * \return
 *   Error indication according to shr_error_e enum
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_udp_destination_port_parser_configure(
    int unit,
    dbal_fields_e field_e,
    uint32 udp_destination_port_value)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** set parsing value */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_PARSERUDP, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, field_e, INST_SINGLE, udp_destination_port_value);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - get expected UDP destination port at parser to
 * identify UDP next protocol.
 * \param [in] unit - Relevant unit.
 * \param [in] field_e - field per udp next protocol.
 * \param [out] udp_destination_port_value - udp destination
 *        port value for next protocol
 * \return
 *   Error indication according to shr_error_e enum
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_udp_destination_port_parser_get(
    int unit,
    dbal_fields_e field_e,
    uint32 *udp_destination_port_value)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** set parsing value */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_PARSERUDP, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field_e, INST_SINGLE,
                                                        udp_destination_port_value));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Configure expected UDP destination port at parser to
 * identify UDP next protocol.
 * At egress, udp header encapsule UDP header with udp
 * destination value for the specified next protocol

 * \param [in] unit - Relevant unit.
 * \param [in] type - Indicate for which next protocol we're
 *        configuring the udp destination port
 * \param [in] udp_destination_port_value - new udp destination
 *        port value for next protocol
 * \return
 *   Error indication according to shr_error_e enum
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_udp_destination_port_configure(
    int unit,
    bcm_switch_control_t type,
    uint32 udp_destination_port_value)
{
    dbal_enum_value_field_etpp_next_protocol_namespace_e protocol_namespace_e;
    dbal_fields_e field_e;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * part of the mapping key (next protocol x next protocol namespace -> next protocol value)
     */
    protocol_namespace_e = DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT;

    switch (type)
    {
        case bcmSwitchUdpTunnelIPv4DstPort:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTIPV4;
            /** update udp destination port at encapsulation by setting:
             *  next protocol x protocol namespace -> next protocol value */
            SHR_IF_ERR_EXIT(dnx_init_pp_egress_current_next_protocol_config_table_configure(unit, DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_UC  /* which
                                                                                                                                                 * protocol
                                                                                                                                                 * to update 
                                                                                                                                                 */ ,
                                                                                            protocol_namespace_e, udp_destination_port_value    /* next
                                                                                                                                                 * protocol
                                                                                                                                                 * value */ ));
            SHR_IF_ERR_EXIT(dnx_init_pp_egress_current_next_protocol_config_table_configure(unit, DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_MC  /* which
                                                                                                                                                 * protocol
                                                                                                                                                 * to update 
                                                                                                                                                 */ ,
                                                                                            protocol_namespace_e, udp_destination_port_value    /* next
                                                                                                                                                 * protocol
                                                                                                                                                 * value */ ));
            break;
        case bcmSwitchUdpTunnelIPv6DstPort:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTIPV6;
            /** update udp destination port at encapsulation by setting:
             *  next protocol x protocol namespace -> next protocol value */
            SHR_IF_ERR_EXIT(dnx_init_pp_egress_current_next_protocol_config_table_configure(unit, DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_UC  /* which
                                                                                                                                                 * protocol
                                                                                                                                                 * to update 
                                                                                                                                                 */ ,
                                                                                            protocol_namespace_e, udp_destination_port_value    /* next
                                                                                                                                                 * protocol
                                                                                                                                                 * value */ ));
            SHR_IF_ERR_EXIT(dnx_init_pp_egress_current_next_protocol_config_table_configure(unit, DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_MC  /* which
                                                                                                                                                 * protocol
                                                                                                                                                 * to update 
                                                                                                                                                 */ ,
                                                                                            protocol_namespace_e, udp_destination_port_value    /* next
                                                                                                                                                 * protocol
                                                                                                                                                 * value */ ));
            break;
        case bcmSwitchUdpTunnelMplsDstPort:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTMPLS;
            /** update udp destination port at encapsulation by setting:
             *  next protocol x protocol namespace -> next protocol value */
            SHR_IF_ERR_EXIT(dnx_init_pp_egress_current_next_protocol_config_table_configure(unit, DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_MPLS     /* which
                                                                                                                                                 * protocol
                                                                                                                                                 * to update 
                                                                                                                                                 */ ,
                                                                                            protocol_namespace_e, udp_destination_port_value    /* next
                                                                                                                                                 * protocol
                                                                                                                                                 * value */ ));
            break;
        case bcmSwitchVxlanUdpDestPortSet:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTVXLAN_1;
            /** update udp destination for additional header profile */
            SHR_IF_ERR_EXIT(dnx_egress_additional_headers_map_tables_configuration_vxlan_udp_dest_update
                            (unit, udp_destination_port_value,
                             DBAL_ENUM_FVAL_ETPP_ADDITIONAL_HEADER_PROFILE_STACK_ATTRIBUTES_AHS_VXLAN));
            break;
        case bcmSwitchVxlanGpeUdpDestPortSet:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTVXLAN_2;
            /** update udp destination for additional header profile */
            SHR_IF_ERR_EXIT(dnx_egress_additional_headers_map_tables_configuration_vxlan_udp_dest_update
                            (unit, udp_destination_port_value,
                             DBAL_ENUM_FVAL_ETPP_ADDITIONAL_HEADER_PROFILE_STACK_ATTRIBUTES_AHS_VXLAN_GPE));
            break;
        case bcmSwitchGeneveUdpDestPortSet:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTGENEVE;
            /** update udp destination for additional header profile */
            SHR_IF_ERR_EXIT(dnx_egress_additional_headers_map_tables_configuration_geneve_udp_dest_update
                            (unit, udp_destination_port_value,
                             DBAL_ENUM_FVAL_ETPP_ADDITIONAL_HEADER_PROFILE_STACK_ATTRIBUTES_AHS_GENEVE));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Unsupported type for bcm_switch_control_set %d\n", type);
    }

    /** set parsing value */
    SHR_IF_ERR_EXIT(dnx_switch_control_udp_destination_port_parser_configure
                    (unit, field_e, udp_destination_port_value));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - get expected UDP destination port at parser to
 * identify UDP next protocol.
 * At egress, udp header encapsule UDP header with udp
 * destination value for the specified next protocol.
 *

 * \param [in] unit - Relevant unit.
 * \param [in] type - Indicate for which next protocol we're
 *        configuring the udp destination port
 * \param [out] udp_destination_port_value - new udp destination
 *        port value for next protocol
 * \return
 *   Error indication according to shr_error_e enum
 *
 * \remark
 *   * We only get the udp from the parser
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_udp_destination_port_get(
    int unit,
    bcm_switch_control_t type,
    uint32 *udp_destination_port_value)
{
    dbal_fields_e field_e;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    switch (type)
    {
        case bcmSwitchUdpTunnelIPv4DstPort:
            /** set dbal field to get in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTIPV4;
            break;
        case bcmSwitchUdpTunnelIPv6DstPort:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTIPV6;
            break;
        case bcmSwitchUdpTunnelMplsDstPort:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTMPLS;
            break;
        case bcmSwitchVxlanUdpDestPortSet:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTVXLAN_1;
            break;
        case bcmSwitchVxlanGpeUdpDestPortSet:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTVXLAN_2;
            break;
        case bcmSwitchGeneveUdpDestPortSet:
            /** set dbal field to update in parsing udp dst table   */
            field_e = DBAL_FIELD_DSTPORTGENEVE;
            break;

        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Unsupported type for bcm_switch_control_get %d\n", type);
    }
    /** get parsing value */
    SHR_IF_ERR_EXIT(dnx_switch_control_udp_destination_port_parser_get(unit, field_e, udp_destination_port_value));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set the age refresh hit bit mode.
 *
 * \param [in] unit - Relevant unit.
 * \param [in] arg -  The hit bit mode.
 * can be one of the following:
 * bcmSwitchAgeRefreshModeSrc
 * bcmSwitchAgeRefreshModeDest
 * bcmSwitchAgeRefreshModeSrcAndDest
 * bcmSwitchAgeRefreshModeSrcOrDest
 * \return
 *   Error indication according to shr_error_e enum
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_mact_age_refresh_mode_set(
    int unit,
    uint32 arg)
{
    uint32 hit_bit_mode;

    mdb_physical_table_e mdb_table = MDB_NOF_PHYSICAL_TABLES;
    SHR_FUNC_INIT_VARS(unit);

    mdb_table = MDB_PHYSICAL_TABLE_LEM;

    switch (arg)
    {
        case bcmSwitchAgeRefreshModeSrc:
        {
            hit_bit_mode = DBAL_ENUM_FVAL_MDB_EM_AGING_HIT_BIT_MODE_A;
            break;
        }
        case bcmSwitchAgeRefreshModeDest:
        {
            hit_bit_mode = DBAL_ENUM_FVAL_MDB_EM_AGING_HIT_BIT_MODE_B;
            break;
        }
        case bcmSwitchAgeRefreshModeSrcAndDest:
        {
            hit_bit_mode = DBAL_ENUM_FVAL_MDB_EM_AGING_HIT_BIT_MODE_A_AND_B;
            break;
        }
        case bcmSwitchAgeRefreshModeSrcOrDest:
        {
            hit_bit_mode = DBAL_ENUM_FVAL_MDB_EM_AGING_HIT_BIT_MODE_A_OR_B;
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported age refresh mode");
            break;
        }
    }

    /** Set the hit bit mode in the mdb table*/
    SHR_IF_ERR_EXIT(mdb_em_mact_age_refresh_mode_set(unit, mdb_table, hit_bit_mode));
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Configure the global TOD mode
 *
 * \param [in] unit - Relevant unit.
 * \param [in] mode - TOD mode.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_global_tod_mode_set(
    int unit,
    bcm_switch_tod_mode_t mode)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_TOD_GENERAL_CONFIGURATION, &entry_handle_id));
    /*
     * Set the value
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECI_TOD_MODE, INST_SINGLE, mode);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get the global TOD mode
 *
 * \param [in] unit - Relevant unit.
 * \param [out] mode - TOD mode.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_global_tod_mode_get(
    int unit,
    bcm_switch_tod_mode_t * mode)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_TOD_GENERAL_CONFIGURATION, &entry_handle_id));

    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_ECI_TOD_MODE, INST_SINGLE, (uint32 *) mode);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Converts the L3 tunnel protocol to its corresponding DBAL field
 *
 * \param [in] unit - Relevant unit.
 * \param [in] protocol - protocol to convert to its corresponding DBAL field.
 * \param [out] field - The DBAL field.
 *
 * \remark
 *   This function is used only for UDP tunnel protocol disabling
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_l3_tunnel_protocol_to_dbal_field(
    int unit,
    bcm_switch_l3_tunnel_t protocol,
    dbal_fields_e * field)
{
    SHR_FUNC_INIT_VARS(unit);

    switch (protocol)
    {
        case bcmSwitchL3TunnelL2TP:
            *field = DBAL_FIELD_L2TPOUDP_ENABLE;
            break;
        case bcmSwitchL3TunnelVxLan:
            *field = DBAL_FIELD_VXLANOUDP_ENABLE;
            break;
        case bcmSwitchL3TunnelGtpU:
            *field = DBAL_FIELD_GTPUOUDP_ENABLE;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unknown bcm_switch_l3_tunnel_t protocol enum: %d\n", protocol);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Disables/Enables UDP tunnel collapsing for given protocol
 *
 * \param [in] unit - Relevant unit.
 * \param [in] protocol - protocol to disable UDP tunnel collapsing for.
 * \param [in] value    - TRUE to disable UDP tunnel collapsing for protocol. FALSE to enable it.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_l3_tunnel_disable_set(
    int unit,
    bcm_switch_l3_tunnel_t protocol,
    int value)
{
    uint32 entry_handle_id;
    dbal_fields_e field = DBAL_NOF_FIELDS;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_PARSERUDP, &entry_handle_id));

    SHR_IF_ERR_EXIT(dnx_switch_control_l3_tunnel_protocol_to_dbal_field(unit, protocol, &field));
    /*
     * Set value negated (in case disable is TRUE value should be converted to FALSE)
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, field, INST_SINGLE, !value);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Retrieves the status of UDP tunnel collapsing for given protocol
 *
 * \param [in] unit - Relevant unit.
 * \param [in] protocol - protocol to get UDP tunnel collapsing status for.
 * \param [out] value   - TRUE if protocol is disable, FALSE otherwise.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_l3_tunnel_disable_get(
    int unit,
    bcm_switch_l3_tunnel_t protocol,
    int *value)
{
    uint32 entry_handle_id;
    dbal_fields_e field = DBAL_NOF_FIELDS;
    uint32 ret_val;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_PARSERUDP, &entry_handle_id));

    SHR_IF_ERR_EXIT(dnx_switch_control_l3_tunnel_protocol_to_dbal_field(unit, protocol, &field));

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field, INST_SINGLE, &ret_val));

    /*
     * Negate ret_val to map HW value to API value
     */
    *value = !ret_val;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Converts the given BCM Range Type to its corresponding DBAL value
 *
 * \param [in] unit             - Relevant unit.
 * \param [in] range_type       - BCM range type to convert.
 * \param [out] dbal_range_type - The converted DBAL range type.
 *
 * \remark
 *   This function is used only for UDP tunnel protocol disabling
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_convert_bcm_range_type_to_dbal(
    int unit,
    bcm_field_range_type_t range_type,
    dbal_enum_value_field_l4_ops_extnd_ranges_type_e * dbal_range_type)
{
    SHR_FUNC_INIT_VARS(unit);

    switch (range_type)
    {
        case bcmFieldRangeTypeL4SrcPort:
            *dbal_range_type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_TYPE_L4_SRC_PORT;
            break;
        case bcmFieldRangeTypeL4DstPort:
            *dbal_range_type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_TYPE_L4_DST_PORT;
            break;
        case bcmFieldRangeTypeL4OpsPacketHeaderSize:
            *dbal_range_type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_TYPE_PACKET_HEADER_SIZE;
            break;
        case bcmFieldRangeTypeInTTL:
            *dbal_range_type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_TYPE_IN_TLL;
            break;
        case bcmFieldRangeTypeUserDefined1Low:
            *dbal_range_type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_TYPE_FFC_1_LOW;
            break;
        case bcmFieldRangeTypeUserDefined1High:
            *dbal_range_type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_TYPE_FFC_1_HIGH;
            break;
        case bcmFieldRangeTypeUserDefined2Low:
            *dbal_range_type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_TYPE_FFC_2_LOW;
            break;
        case bcmFieldRangeTypeUserDefined2High:
            *dbal_range_type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_TYPE_FFC_2_HIGH;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unknown or non-supported range_type: %d\n", range_type);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Sets the range type for the given range index
 *
 * \param [in] unit        - Relevant unit.
 * \param [in] range_index - Index to set the type for.
 * \param [in] range_type  - BCM range type to set.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_range_type_set(
    int unit,
    int range_index,
    bcm_field_range_type_t range_type)
{
    uint32 entry_handle_id;
    dbal_enum_value_field_l4_ops_extnd_ranges_type_e dbal_range_type;
    dnx_field_range_type_e dnx_range_type;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_FIELD_IPMF1_L4_OPS_RANGES_CFG_FIELD_SELECT, &entry_handle_id));

    SHR_IF_ERR_EXIT(dnx_switch_control_convert_bcm_range_type_to_dbal(unit, range_type, &dbal_range_type));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_OPS_RANGE_ID, range_index);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_OPS_FIELD_TYPE_SELECT, INST_SINGLE,
                                 dbal_range_type);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    /*
     * Update field range swstate
     */
    SHR_IF_ERR_EXIT(dnx_field_map_range_type_bcm_to_dnx(unit, range_type, &dnx_range_type));
    SHR_IF_ERR_EXIT(dnx_field_range_sw_db.ext_l4_ops_range_types.set(unit, range_index, dnx_range_type));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Retrieves the range type for the given range index
 *
 * \param [in] unit         - Relevant unit.
 * \param [in] range_index  - Index to get the type for.
 * \param [out] range_type  - The retrieved BCM range type.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_range_type_get(
    int unit,
    int range_index,
    bcm_field_range_type_t * range_type)
{
    dnx_field_range_type_e dnx_range_type;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_range_sw_db.ext_l4_ops_range_types.get(unit, range_index, &dnx_range_type));
    SHR_IF_ERR_EXIT(dnx_field_map_range_type_dnx_to_bcm(unit, dnx_range_type, range_type));

exit:
    SHR_FUNC_EXIT;
}

/*
 * \brief - Converts the range_result_map BCM value to HW value
 *
 * \param [in] unit             - Relevant unit.
 * \param [in] range_result_map - The range result map BCM value to convert.
 * \param [out] encode_select   - The converted encode_select (DBAL) value.
 *
 * \remark
 *   None
 * \see
 *
 *   * None
 */
static shr_error_e
dnx_switch_control_range_result_bcm_to_dbal(
    int unit,
    bcm_switch_range_result_map_t range_result_map,
    dbal_enum_value_field_l4_ops_extnd_ranges_encode_select_e * encode_select)
{
    SHR_FUNC_INIT_VARS(unit);

    *encode_select = 0x0;

    switch (range_result_map)
    {
        case bcmSwitchRangeResultMapNone:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_NONE;
            break;
        case bcmSwitchRangeResultMapFirstOnly:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST;
            break;
        case bcmSwitchRangeResultMapSecondOnly:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_SECOND;
            break;
        case bcmSwitchRangeResultMapThirdOnly:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_THIRD;
            break;
        case bcmSwitchRangeResultMapForthOnly:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FORTH;
            break;
        case bcmSwitchRangeResultMapFirstnSecond:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_SECOND;
            break;
        case bcmSwitchRangeResultMapFirstnThird:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_THIRD;
            break;
        case bcmSwitchRangeResultMapFirstnForth:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_FORTH;
            break;
        case bcmSwitchRangeResultMapSecondnThird:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_SECOND_THIRD;
            break;
        case bcmSwitchRangeResultMapSecondnForth:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_SECOND_FORTH;
            break;
        case bcmSwitchRangeResultMapThirdnForth:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_THIRD_FORTH;
            break;
        case bcmSwitchRangeResultMapFirstnSecondnThird:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_SECOND_THIRD;
            break;
        case bcmSwitchRangeResultMapFirstnSecondnForth:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_SECOND_FORTH;
            break;
        case bcmSwitchRangeResultMapFirstnThirdnForth:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_THIRD_FORTH;
            break;
        case bcmSwitchRangeResultMapSecondnThirdnForth:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_SECOND_THIRD_FORTH;
            break;
        case bcmSwitchRangeResultMapFirstnSecondnThirdnForth:
            *encode_select = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_SECOND_THIRD_FORTH;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unknown or non-supported range_result map: %d\n", range_result_map);
    }
exit:
    SHR_FUNC_EXIT;
}

/*
 * \brief - Converts the range_result_map HW value to BCM value
 *
 * \param [in] unit              - Relevant unit.
 * \param [in] encode_select     - encode_select (DBAL) to convert
 * \param [out] range_result_map - The converted range result map BCM value.
 *
 * \remark
 *   None
 * \see
 *
 *   * None
 */
static shr_error_e
dnx_switch_control_range_result_dbal_to_bcm(
    int unit,
    dbal_enum_value_field_l4_ops_extnd_ranges_encode_select_e encode_select,
    bcm_switch_range_result_map_t * range_result_map)
{
    SHR_FUNC_INIT_VARS(unit);

    *range_result_map = bcmSwitchRangeResultMapNone;

    switch (encode_select)
    {
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_NONE:
            *range_result_map = bcmSwitchRangeResultMapNone;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST:
            *range_result_map = bcmSwitchRangeResultMapFirstOnly;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_SECOND:
            *range_result_map = bcmSwitchRangeResultMapSecondOnly;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_THIRD:
            *range_result_map = bcmSwitchRangeResultMapThirdOnly;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FORTH:
            *range_result_map = bcmSwitchRangeResultMapForthOnly;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_SECOND:
            *range_result_map = bcmSwitchRangeResultMapFirstnSecond;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_THIRD:
            *range_result_map = bcmSwitchRangeResultMapFirstnThird;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_FORTH:
            *range_result_map = bcmSwitchRangeResultMapFirstnForth;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_SECOND_THIRD:
            *range_result_map = bcmSwitchRangeResultMapSecondnThird;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_SECOND_FORTH:
            *range_result_map = bcmSwitchRangeResultMapSecondnForth;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_THIRD_FORTH:
            *range_result_map = bcmSwitchRangeResultMapThirdnForth;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_SECOND_THIRD:
            *range_result_map = bcmSwitchRangeResultMapFirstnSecondnThird;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_SECOND_FORTH:
            *range_result_map = bcmSwitchRangeResultMapFirstnSecondnForth;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_THIRD_FORTH:
            *range_result_map = bcmSwitchRangeResultMapFirstnThirdnForth;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_SECOND_THIRD_FORTH:
            *range_result_map = bcmSwitchRangeResultMapSecondnThirdnForth;
            break;
        case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_ENCODE_SELECT_FIRST_SECOND_THIRD_FORTH:
            *range_result_map = bcmSwitchRangeResultMapFirstnSecondnThirdnForth;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Unrecognized range_result_map DBAL value: %d\n", encode_select);
    }
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Configures the given encoder index with the given range result bitmap
 *
 * \param [in] unit              - Relevant unit.
 * \param [in] encoder_index     - Encoder index to configure.
 * \param [in] range_result_map  - The range result map to configure the encoder with.
 *
 * \remark
 *   None
 * \see
 *
 *   * None
 */
static shr_error_e
dnx_switch_control_range_result_bmp_set(
    int unit,
    int encoder_index,
    bcm_switch_range_result_map_t range_result_map)
{
    uint32 entry_handle_id;
    dbal_enum_value_field_l4_ops_extnd_ranges_encode_select_e encode_select;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_FIELD_IPMF1_L4_OPS_ENCODE_CFG, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_OPS_ENCODE_IDX, encoder_index);
    SHR_IF_ERR_EXIT(dnx_switch_control_range_result_bcm_to_dbal(unit, range_result_map, &encode_select));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_OPS_ENCODE_MAP, INST_SINGLE, encode_select);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Retrieves the range result bitmap of the given encoder index
 *
 * \param [in] unit              - Relevant unit.
 * \param [in] encoder_index     - Encoder index to retrieve its configuration.
 * \param [out] range_result_bmp - The retrieved range result bitmap that the encoder is configured with.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_range_result_bmp_get(
    int unit,
    int encoder_index,
    bcm_switch_range_result_map_t * range_result_bmp)
{
    uint32 entry_handle_id;
    dbal_enum_value_field_l4_ops_extnd_ranges_encode_select_e encode_select;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_FIELD_IPMF1_L4_OPS_ENCODE_CFG, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_OPS_ENCODE_IDX, encoder_index);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_L4_OPS_ENCODE_MAP, INST_SINGLE, &encode_select));

    SHR_IF_ERR_EXIT(dnx_switch_control_range_result_dbal_to_bcm(unit, encode_select, range_result_bmp));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - This struct contains all the dbal parameters for the range operator table
 */

typedef struct
{
    dbal_enum_value_field_l4_ops_extnd_ranges_op_type_e type;
    dbal_enum_value_field_l4_ops_extnd_ranges_op_width_e width;
    dbal_enum_value_field_l4_ops_extnd_ranges_op_pair_e pair;
} dnx_switch_control_range_operator_params;

/**
 * \brief - Converts the given bcm range OP into its corresponding DBAL range OP params
 *
 * \param [in] unit           - Relevant unit.
 * \param [in] range_operator - BCM Range OP to convert.
 * \param [out] op_params     - The converted DBAL OP params.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_range_operator_bcm_to_dbal(
    int unit,
    bcm_switch_range_operator_t range_operator,
    dnx_switch_control_range_operator_params * op_params)
{
    SHR_FUNC_INIT_VARS(unit);
    switch (range_operator)
    {
        case bcmSwitchRangeOperatorNone:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_NONE;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_NONE;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32;
            break;
        case bcmSwitchRangeOperatorFirstPairAnd:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_AND;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_FIRST;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32;
            break;
        case bcmSwitchRangeOperatorSecondPairAnd:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_AND;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_SECOND;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32;
            break;
        case bcmSwitchRangeOperatorBothPairAnd:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_AND;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_BOTH;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32;
            break;
        case bcmSwitchRangeOperator64bPairAndLow:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_AND;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_FIRST;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_64;
            break;
        case bcmSwitchRangeOperator64bPairAndHigh:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_AND;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_SECOND;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_64;
            break;
        case bcmSwitchRangeOperatorFirstPairOr:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_OR;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_FIRST;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32;
            break;
        case bcmSwitchRangeOperatorSecondPairOr:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_OR;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_SECOND;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32;
            break;
        case bcmSwitchRangeOperatorBothPairOr:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_OR;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_BOTH;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32;
            break;
        case bcmSwitchRangeOperator64bPairOrLow:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_OR;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_FIRST;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_64;
            break;
        case bcmSwitchRangeOperator64bPairOrHigh:
            op_params->type = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_OR;
            op_params->pair = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_SECOND;
            op_params->width = DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_64;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid bcm range operator %d\n", range_operator);
    }
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Converts the given DBAL params range OP into its corresponding BCM range OP
 *
 * \param [in] unit            - Relevant unit.
 * \param [in] op_params       - DBAL OP params to convert.
 * \param [out] range_operator - The converted BCM Range OP.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_range_operator_dbal_to_bcm(
    int unit,
    dnx_switch_control_range_operator_params op_params,
    bcm_switch_range_operator_t * range_operator)
{
    SHR_FUNC_INIT_VARS(unit);

    *range_operator = bcmSwitchRangeOperatorNone;

    if (op_params.type == DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_AND)
    {
        switch (op_params.pair)
        {
            case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_FIRST:
                *range_operator = (op_params.width == DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32) ?
                    bcmSwitchRangeOperatorFirstPairAnd : bcmSwitchRangeOperator64bPairAndLow;
                break;
            case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_SECOND:
                *range_operator = (op_params.width == DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32) ?
                    bcmSwitchRangeOperatorSecondPairAnd : bcmSwitchRangeOperator64bPairAndHigh;
                break;
            case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_BOTH:
                *range_operator = bcmSwitchRangeOperatorBothPairAnd;
                break;
            default:
                SHR_ERR_EXIT(_SHR_E_INTERNAL, "Invalid range pair %d\n", op_params.pair);
        }
    }
    else if (op_params.type == DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_OR)
    {
        switch (op_params.pair)
        {
            case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_FIRST:
                *range_operator = (op_params.width == DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32) ?
                    bcmSwitchRangeOperatorFirstPairOr : bcmSwitchRangeOperator64bPairOrLow;
                break;
            case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_SECOND:
                *range_operator = (op_params.width == DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_WIDTH_32) ?
                    bcmSwitchRangeOperatorSecondPairOr : bcmSwitchRangeOperator64bPairOrHigh;
                break;
            case DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_PAIR_BOTH:
                *range_operator = bcmSwitchRangeOperatorBothPairOr;
                break;
            default:
                SHR_ERR_EXIT(_SHR_E_INTERNAL, "Invalid range pair %d\n", op_params.pair);
        }
    }
    else if (op_params.type != DBAL_ENUM_FVAL_L4_OPS_EXTND_RANGES_OP_TYPE_NONE)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Invalid range type %d\n", op_params.type);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Configures Extended L4 Op range operator with the given BCM range operator
 *
 * \param [in] unit            - Relevant unit.
 * \param [in] range_operator  - BCM Range operator to configure.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_range_operator_set(
    int unit,
    bcm_switch_range_operator_t range_operator)
{
    uint32 entry_handle_id;
    dnx_switch_control_range_operator_params op_params;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_FIELD_IPMF1_L4_OPS_RANGES_OPERATOR_CFG, &entry_handle_id));

    SHR_IF_ERR_EXIT(dnx_switch_control_range_operator_bcm_to_dbal(unit, range_operator, &op_params));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_OPS_BITMAP_OPERATOR_TYPE, INST_SINGLE,
                                 op_params.type);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_OPS_BITMAP_OPERATOR_WIDTH, INST_SINGLE,
                                 op_params.width);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_OPS_BITMAP_OPERATOR_PAIR, INST_SINGLE,
                                 op_params.pair);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Retrieves the Extended L4 Op range operator configuration.
 *
 * \param [in] unit            - Relevant unit.
 * \param [out] range_operator - The retrieved BCM range operator.
 *
 * \remark
 *   None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_control_range_operator_get(
    int unit,
    bcm_switch_range_operator_t * range_operator)
{
    uint32 entry_handle_id;
    dnx_switch_control_range_operator_params op_params;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_FIELD_IPMF1_L4_OPS_RANGES_OPERATOR_CFG, &entry_handle_id));

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_L4_OPS_BITMAP_OPERATOR_TYPE, INST_SINGLE, &(op_params.type)));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_L4_OPS_BITMAP_OPERATOR_WIDTH, INST_SINGLE, &(op_params.width)));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_L4_OPS_BITMAP_OPERATOR_PAIR, INST_SINGLE, &(op_params.pair)));

    SHR_IF_ERR_EXIT(dnx_switch_control_range_operator_dbal_to_bcm(unit, op_params, range_operator));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Enable/disable ignoring protection state for OAMP inject packets.
* \param [in] unit  -
*   Relevant unit.
* \param [in] control_value  -
*    Set enable or disable value.
* \retval
*   shr_error_none
* \remark
*   * None
* \see
*   * \ref dnx_switch_control_oam_bfd_failover_state_ignore_get
*/
static shr_error_e
dnx_switch_control_oam_bfd_failover_state_ignore_set(
    int unit,
    int control_value)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Ignoring protection state for OAMP inject packets.
     */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PRT_QUALIFIER_INFO, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PRT_QUALIFIER,
                               DBAL_ENUM_FVAL_PRT_QUALIFIER_OAMP_INJECTION_DOWN);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PROTECTION_IGNORE, INST_SINGLE, control_value);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get ignoring protection state for OAMP inject packets.
* \param [in] unit  -
*   Relevant unit.
* \param [out] control_value  -
*    enable or disable value.
* \retval
*   shr_error_none
* \remark
*   * None
* \see
*   * \ref dnx_switch_control_oam_bfd_failover_state_ignore_set
*/
shr_error_e
dnx_switch_control_oam_bfd_failover_state_ignore_get(
    int unit,
    int *control_value)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Get ignoring protection state for OAMP inject packets.
     */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PRT_QUALIFIER_INFO, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PRT_QUALIFIER,
                               DBAL_ENUM_FVAL_PRT_QUALIFIER_OAMP_INJECTION_DOWN);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_PROTECTION_IGNORE, INST_SINGLE,
                               (uint32 *) control_value);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_parse_udp_next_header_to_dbal_field(
    int unit,
    dnx_parse_udp_next_header_t dnx_parse_udp_next_header,
    dbal_fields_e * field)
{
    SHR_FUNC_INIT_VARS(unit);
    switch (dnx_parse_udp_next_header)
    {
        case dnxParseUdpNextHeaderIpv4:
            *field = DBAL_FIELD_IPV4OUDP_ENABLE;
            break;
        case dnxParseUdpNextHeaderIpv6:
            *field = DBAL_FIELD_IPV6OUDP_ENABLE;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unknown dnx_parse_udp_next_header_t enum: %d\n", dnx_parse_udp_next_header);
    }

exit:
    SHR_FUNC_EXIT;

}

static shr_error_e
dnx_switch_control_parse_udp_enable_set(
    int unit,
    dnx_parse_udp_next_header_t dnx_parse_udp_next_header,
    uint8 value)
{
    uint32 entry_handle_id;
    dbal_fields_e field = DBAL_NOF_FIELDS;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_PARSERUDP, &entry_handle_id));
    SHR_IF_ERR_EXIT(dnx_parse_udp_next_header_to_dbal_field(unit, dnx_parse_udp_next_header, &field));
    dbal_entry_value_field32_set(unit, entry_handle_id, field, INST_SINGLE, value);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_switch_control_parse_udp_enable_get(
    int unit,
    dnx_parse_udp_next_header_t dnx_parse_udp_next_header,
    int *value)
{
    uint32 entry_handle_id;
    dbal_fields_e field = DBAL_NOF_FIELDS;
    uint32 ret_val;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_PARSERUDP, &entry_handle_id));

    SHR_IF_ERR_EXIT(dnx_parse_udp_next_header_to_dbal_field(unit, dnx_parse_udp_next_header, &field));

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, field, INST_SINGLE, &ret_val));

    *value = ret_val;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Configures the value of next protocol ETH to be recognized by the parser.
*  The default configuration is 143, which is configured with '1', otherwise it's 59, selected by 0.
* \param [in] unit  -
*   Relevant unit.
* \param [in] arg  -
*    enable or disable value.
* \return
*   \retval Zero if no error was detected
*   \retval Negative if error was detected. See \ref shr_error_e
*/
static shr_error_e
dnx_ip_next_protocol_eth_configure_set(
    int unit,
    int arg)
{
    uint32 entry_handle_id;
    uint32 current_next_protocol;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if ((arg != 0) && (arg != 1))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid value provided, should be either 0 or 1, provided is: %d\n", arg);
    }
    /** Configure the virtual register values for next protocol eth and no next protocol*/
    current_next_protocol =
        (arg ==
         1) ? DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_ETHERNET_OVER_IP :
        DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_NO_NEXT_PROTOCOL_OVER_IP;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_PARSERETHSRV6, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NEXTPROTOCOLETH, INST_SINGLE, arg);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NONEXTPROTOCOL, INST_SINGLE, (arg == 1) ? 0 : 1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_EGRESS_CURRENT_NEXT_PROTOCOL_MAP_TABLE, entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CURRENT_PROTOCOL_TYPE,
                               DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_ETHERNET);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_NEXT_PROTOCOL_NAMESPACE,
                               DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CURRENT_NEXT_PROTOCOL, INST_SINGLE,
                                 current_next_protocol);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  The function indicates what type of value for next protocol ETH is recognized by the parser.
*  In case 143, the returned value is 1, otherwse for 59 - it's 0
* \param [in] unit  -
*   Relevant unit.
* \param [out] arg  -
*    enable or disable value.
* \return
*   \retval Zero if no error was detected
*   \retval Negative if error was detected. See \ref shr_error_e
*/
static shr_error_e
dnx_ip_next_protocol_eth_configure_get(
    int unit,
    int *arg)
{
    uint32 entry_handle_id;
    uint32 next_protocol_eth;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Read the Virtual Register value and decide the next protocol value */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_PARSERETHSRV6, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_NEXTPROTOCOLETH, INST_SINGLE, &next_protocol_eth));
    *arg = (int) next_protocol_eth;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  The function indicates which mpls last term mode is used.
*  The default configuration is 0 - VTT5 is the last MPLS term stage;  
*                               1 - VTT4 is the last MPLS term stage
* \param [in] unit  -
*   Relevant unit.
* \param [out] arg  -
*    present to which VTT stage is the last MPLS term stagw.
* \return
*   \retval Zero if no error was detected
*   \retval Negative if error was detected. See \ref shr_error_e
*/
static shr_error_e
dnx_switch_control_mpls_last_term_mode_set(
    int unit,
    int arg)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_MPLS_TERM, &entry_handle_id));

    if (dnx_data_pp.stages.params_get(unit, DNX_PP_STAGE_VTT5)->valid)
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VTT4_IS_LAST_MPLS_TERM_STAGE, INST_SINGLE, arg);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VTT5_IS_LAST_MPLS_TERM_STAGE, INST_SINGLE,
                                     (arg == 0) ? 1 : 0);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }
    else
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VTT4_IS_LAST_MPLS_TERM_STAGE, INST_SINGLE,
                                     (arg == 0) ? 1 : 0);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Configures MPLS last termination mode.
*  The default configuration is 0 - VTT5 is the last MPLS term stage;  
*                               1 - VTT4 is the last MPLS term stage
* \param [in] unit  -
*   Relevant unit.
* \param [in] arg  -
*    present to which VTT stage is the last MPLS term stagw.
* \return
*   \retval Zero if no error was detected
*   \retval Negative if error was detected. See \ref shr_error_e
*/
static shr_error_e
dnx_switch_control_mpls_last_term_mode_get(
    int unit,
    int *arg)
{
    uint32 entry_handle_id;
    uint32 mpls_last_term_mode = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Read the Virtual Register value and decide the next protocol value */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_MPLS_TERM, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
    if (dnx_data_pp.stages.params_get(unit, DNX_PP_STAGE_VTT5)->valid)
    {
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                        (unit, entry_handle_id, DBAL_FIELD_VTT4_IS_LAST_MPLS_TERM_STAGE, INST_SINGLE,
                         &mpls_last_term_mode));
    }
    else
    {
    }
    *arg = (int) mpls_last_term_mode;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify function for
*  dnx_switch_control_last_ivec_fhei_size_set().
*  Verifies that the last IVEC FHEI size isn't allocated while
*  attempting to reset it's FHEI size.
* \param [in] unit  -
*   Relevant unit.
* \param [in] last_ivec  -
*    The IVEC number of the last entry.
* \param [in] fhei_size  -
*    The FHEI size value to set.
* \return
*   \retval Zero if no error was detected
*   \retval Negative if error was detected. See \ref shr_error_e
*/
static shr_error_e
dnx_switch_control_last_ivec_fhei_size_set_verify(
    int unit,
    uint32 last_ivec,
    uint32 fhei_size)
{
    uint8 is_allocated;
    int system_headers_mode;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Disallow usage of the API in JR1 mode
     */
    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);
    if (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE)
    {
        SHR_ERR_EXIT(_SHR_E_EXISTS, "Error, API invalid for JR1 mode\n");
    }

    /*
     * Verify that the last IVEC isn't allocated when the IVEC size is reset
     */
    if (fhei_size == DBAL_ENUM_FVAL_FHEI_SIZE_0B)
    {
        SHR_IF_ERR_EXIT(vlan_db.action_id_ingress.is_allocated(unit, last_ivec, &is_allocated));
        if (is_allocated == TRUE)
        {
            SHR_ERR_EXIT(_SHR_E_EXISTS, "Error, FHEI size for IVEC %d can't be set while the entry is allocated.\n",
                         last_ivec);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  The function sets the FHEI size for the last Ingress
*  VLAN-Edit command. The default configuration 5B:
*  0 - 0B FHEI size
*  1 - 5B FHEI size
* \param [in] unit  -
*   Relevant unit.
* \param [out] arg  -
*    Select a value that represnts the requested FHEI size.
* \return
*   \retval Zero if no error was detected
*   \retval Negative if error was detected. See \ref shr_error_e
*/
static shr_error_e
dnx_switch_control_last_ivec_fhei_size_set(
    int unit,
    int arg)
{
    uint32 entry_handle_id, fhei_size;
    int last_ivec;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    last_ivec = dnx_data_vlan.vlan_translate.nof_ingress_vlan_edit_action_ids_get(unit) - 1;
    fhei_size = (arg) ? DBAL_ENUM_FVAL_FHEI_SIZE_0B : DBAL_ENUM_FVAL_FHEI_SIZE_5B;

    SHR_INVOKE_VERIFY_DNXC(dnx_switch_control_last_ivec_fhei_size_set_verify(unit, last_ivec, fhei_size));

    /*
     * Allocate the last IVEC when FHEI size is reset, so that the user won't be able to use it.
     * Free it when the FHEI size is restored.
     */
    if (fhei_size == DBAL_ENUM_FVAL_FHEI_SIZE_0B)
    {
        SHR_IF_ERR_EXIT(vlan_db.
                        action_id_ingress.allocate_single(unit, DNX_ALGO_RES_ALLOCATE_WITH_ID, NULL, &last_ivec));
    }
    else
    {
        SHR_IF_ERR_EXIT(vlan_db.action_id_ingress.free_single(unit, last_ivec, NULL));
    }

    /*
     * Store the FHEI size in an LBP table
     */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_LBP_VLAN_EDITING, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_VLAN_EDIT_CMD_INDEX, last_ivec);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FHEI_IVE_SIZE_TYPE, INST_SINGLE, fhei_size);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  The function retrieves the FHEI size for the last Ingress
*  VLAN-Edit command:
*  0 - 0B FHEI size
*  1 - 5B FHEI size
* \param [in] unit  -
*   Relevant unit.
* \param [out] arg  -
*    The retrieved value that represents the FHEI size.
* \return
*   \retval Zero if no error was detected
*   \retval Negative if error was detected. See \ref shr_error_e
*/
static shr_error_e
dnx_switch_control_last_ivec_fhei_size_get(
    int unit,
    int *arg)
{
    uint32 entry_handle_id, last_ivec, fhei_size;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    last_ivec = dnx_data_vlan.vlan_translate.nof_ingress_vlan_edit_action_ids_get(unit) - 1;
    fhei_size = (arg) ? DBAL_ENUM_FVAL_FHEI_SIZE_0B : DBAL_ENUM_FVAL_FHEI_SIZE_5B;

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_LBP_VLAN_EDITING, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_VLAN_EDIT_CMD_INDEX, last_ivec);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_PPH_FHEI_IVE_SIZE_TYPE, INST_SINGLE, &fhei_size));
    *arg = (fhei_size == DBAL_ENUM_FVAL_FHEI_SIZE_0B) ? TRUE : FALSE;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Configure port-specific and device-wide operating modes.
 *
 * Use cases:
 *
 * 1.
 * Description
 * Parameters:
 * - type -
 * - arg -
 *
 * 373. Scan all MAC addresses and decrement age-status in case that aging is disabled and age machine is not still working.
 * Parameters:
 * - type - bcmSwitchL2AgeScan
 *
 * 728.
 * Meter - enable disable fairness mechanism (adding random number to the bucket level) for all
 *         meter databases (ingress/egress/global) and for CBL and EBL buckets.
 * Parameters:
 * - type - bcmSwitchPolicerFairness
 * - arg -  TRUE/FALSE to enable/disable the feature
 *
 * 780.
 * Enable/disable learning events when a limit is reached.
 * Parameters:
 * - type - bcmSwitchL2LearnLimitToCpu
 * - arg -  '1' means enable learning events when a limit is reached.
 *          '0' means disable learning events when a limit is reached.
 *
 * \param [in] unit - unit id
 * \param [in] type - configuration option taken from bcm_switch_control_t
 * \param [in] arg - argument for the configuration
 *
 * \return
 *   int
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_control_set(
    int unit,
    bcm_switch_control_t type,
    int arg)
{
    int rv = BCM_E_NONE;
    dnx_rx_trap_protocol_my_arp_ndp_config_t my_arp_ndp_config;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED_SWITCH(unit);

    switch (type)
    {
        case bcmSwitchECMPHashConfig:
        case bcmSwitchECMPSecondHierHashConfig:
        case bcmSwitchECMPThirdHierHashConfig:
        case bcmSwitchTrunkHashConfig:
        case bcmSwitchNwkHashConfig:
        {
            if (dnx_data_switch.load_balancing.feature_get(unit, dnx_data_switch_load_balancing_fwd_hashing_method) ==
                DNX_SWITCH_LB_FWD_HASH_METHOD_CRC_FUNCTION)
            {
                int index;
                dnx_switch_lb_tcam_key_t tcam_key;
                dnx_switch_lb_tcam_result_t tcam_result;
                dnx_switch_lb_valid_t tcam_valid;
                uint32 physical_client;

                index = 0;
                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_tcam_info_get
                                (unit, index, &tcam_key, &tcam_result, &tcam_valid));
                /*
                 * Convert logical client to physical so it can be loaded into tcam
                 */
                SHR_IF_ERR_EXIT(dnx_switch_lb_logical_client_to_physical
                                (unit, (bcm_switch_control_t) type, &physical_client));

                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_crc_function_enum_to_hw_get
                                (unit, (bcm_switch_hash_config_t) (arg),
                                 &tcam_result.client_x_crc_16_sel[physical_client]));

                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_tcam_info_set
                                (unit, index, &tcam_key, &tcam_result, tcam_valid));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This type is not supported.\n");
            }

            break;
        }
        case bcmSwitchMplsStack0HashSeed:
        {
            dnx_switch_lb_general_seeds_t general_seeds;

            SHR_IF_ERR_EXIT(dnx_switch_load_balancing_general_seeds_get(unit, &general_seeds));
            general_seeds.mpls_stack_0 = (uint32) (arg);
            if (dnx_data_switch.load_balancing.mpls_split_stack_config_get(unit))
            {
                general_seeds.mpls_stack_1 = (uint32) (arg);
            }
            SHR_IF_ERR_EXIT(dnx_switch_load_balancing_general_seeds_set(unit, &general_seeds));
            break;
        }
        case bcmSwitchMplsStack1HashSeed:
        {
            SHR_ERR_EXIT(BCM_E_UNAVAIL, "'bcmSwitchMplsStack1HashSeed' (%d) is, currently, unsupported", type);
            break;
        }
        case bcmSwitchIpv6NextProtocolEthernet:
        {
            SHR_IF_ERR_EXIT(dnx_ip_next_protocol_eth_configure_set(unit, arg));
            break;
        }
        case bcmSwitchParserHashSeed:
        {
            if (dnx_data_switch.
                load_balancing.feature_get(unit, dnx_data_switch_load_balancing_paser_seed_update_supported))
            {
                dnx_switch_lb_general_seeds_t general_seeds;

                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_general_seeds_get(unit, &general_seeds));
                general_seeds.parser = (uint32) (arg);
                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_general_seeds_set(unit, &general_seeds));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The bcmSwitchParserHashSeed isn't supported in this device \n");
            }

            break;
        }
        case bcmSwitchTraverseMode:
        {
            SHR_IF_ERR_EXIT(dnx_switch_traverse_mode_set(unit, arg));
            break;
        }
        case bcmSwitchL2LearnMode:
        {
            rv = dnx_l2_learn_mode_set(unit, arg);
            SHR_IF_ERR_EXIT(rv);
            break;
        }
        case bcmSwitchMactAgeRefreshMode:
        {
            if (!dnx_data_l2.feature.feature_get(unit, dnx_data_l2_feature_age_refresh_mode_support))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "age refresh mode configuration is not supported for this device");
            }
            SHR_IF_ERR_EXIT(dnx_switch_mact_age_refresh_mode_set(unit, arg));
            break;
        }
        case bcmSwitchL2AgeScan:
        {
            rv = dnx_l2_age_scan_set(unit);
            SHR_IF_ERR_EXIT(rv);
            break;
        }
        case bcmSwitchL2LearnLimitToCpu:
        {
            rv = dnx_l2_learn_limit_to_cpu_set(unit, arg);
            SHR_IF_ERR_EXIT(rv);
            break;
        }
        case bcmSwitchL2StaticMoveToCpu:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmSwitchL2StaticMoveToCpu is not supported.\n");
        }
        case bcmSwitchEtagEthertype:
        {
            uint16 etag_tpid = 0;
            int i, ref_count;
            dnx_sit_profile_t sit_profile_info_get;
            if (arg > 0xFFFF)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid tpid value = 0x%x, bigger than the 0xFFFF.\n", arg);
            }
            etag_tpid = (uint16) arg;
            /** ingress E-TAG swap */
            rv = dnx_port_sit_tag_swap_tpid_set(unit, DNX_TAG_SWAP_TPID_INDEX_DOT1BR, etag_tpid);
            SHR_IF_ERR_EXIT(rv);

            /** egress E-TAG encap */
            for (i = DNX_PORT_DEFAULT_DOT1BR_SIT_PROFILE; i <= DNX_PORT_MAX_SIT_PROFILE; i++)
            {
                sal_memset(&sit_profile_info_get, 0, sizeof(dnx_sit_profile_t));
                SHR_IF_ERR_EXIT(dnx_port_sit_profile_hw_get(unit, i, &sit_profile_info_get));
                if (sit_profile_info_get.tag_type == DBAL_ENUM_FVAL_SIT_TAG_TYPE_802_1BR)
                {
                    sit_profile_info_get.tpid = etag_tpid;
                    SHR_IF_ERR_EXIT(dnx_port_sit_profile_hw_set(unit, i, &sit_profile_info_get));
                    /**Update sit profile swstate*/
                    SHR_IF_ERR_EXIT(algo_port_pp_db.egress_pp_port_sit_profile.profile_data_get
                                    (unit, i, &ref_count, &sit_profile_info_get));
                    sit_profile_info_get.tpid = etag_tpid;
                    SHR_IF_ERR_EXIT(algo_port_pp_db.egress_pp_port_sit_profile.replace_data
                                    (unit, i, &sit_profile_info_get));
                }
            }
            break;
        }
        case bcmSwitchL3UrpfDefaultRoute:
        {
            if (dnx_data_l3.feature.feature_get(unit, dnx_data_l3_feature_rpf_default_route_supported))
            {
                int is_uc = 1;
                if (arg != 0 && arg != 1)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 "Invalid value %d provided to switch control bcmSwitchL3UrpfDefaultRoute. Supported values are 0(off) and 1(on).\n",
                                 arg);
                }
                rv = dnx_l3_rpf_default_route_set(unit, is_uc, arg);
                SHR_IF_ERR_EXIT(rv);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Not supported bcmSwitchL3UrpfDefaultRoute \n");
            }
            break;
        }
        case bcmSwitchMeterMef10dot3Enable:
        {
            /** default mode - MEF 10.3 enable - user can disable it and
             *  work in mode 10.2 for ingress/egress */
            if (arg != 0 && arg != 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid value %d provided to switch control bcmSwitchMeterMef10dot3Enable. Supported values are 0(disable) and 1(enable).\n",
                             arg);
            }
            rv = dnx_policer_mgmt_mef_10_3_set(unit, arg);
            SHR_IF_ERR_EXIT(rv);
            break;
        }
        case bcmSwitchL3McRpfDefaultRoute:
        {
            int is_uc = 0;
            if (arg != 0 && arg != 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid value %d provided to switch control bcmSwitchL3McRpfDefaultRoute. Supported values are 0(off) and 1(on).\n",
                             arg);
            }
            rv = dnx_l3_rpf_default_route_set(unit, is_uc, arg);
            SHR_IF_ERR_EXIT(rv);
            break;
        }
        case bcmSwitchMplsPWControlWord:
        {
            if ((!dnx_data_mpls.general.mpls_control_word_supported_get(unit)))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid value 0x%x provided to switch control bcmSwitchMplsPWControlWord. Supported value is 0.\n",
                             arg);
            }
            SHR_IF_ERR_EXIT(dnx_mpls_cw_set(unit, arg));
            break;
        }
        /************************************************************************/
            /*
             * RCPU
             */
        /************************************************************************/
#if defined(BCM_RCPU_SUPPORT)
        case bcmSwitchRemoteCpuSchanEnable:
        case bcmSwitchRemoteCpuMatchLocalMac:
        case bcmSwitchRemoteCpuCmicEnable:
        case bcmSwitchRemoteCpuMatchVlan:
        {
            if ((arg != 0x0) && (arg != 0x1))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid value %d provided to switch control type=%d. Supported values are 0(disable) and 1(enable).\n",
                             arg, type);
            }
            if (dnx_drv_soc_feature(unit, soc_feature_rcpu_1))
            {
                rv = _bcm_dnx_rcpu_switch_enable_set(unit, type, arg);
                SHR_IF_ERR_EXIT(rv);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Feature unavailable: soc_feature_rcpu_1\r\n");
            }
            break;
        }
        case bcmSwitchRemoteCpuLocalMacOui:
        case bcmSwitchRemoteCpuDestMacOui:
        {
            if ((arg < 0x0) || (arg > 0xffffff))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid value %d provided to switch control type=%d. Supported values are 0~0xffffff.\n",
                             arg, type);
            }
            if (dnx_drv_soc_feature(unit, soc_feature_rcpu_1))
            {
                rv = _bcm_dnx_rcpu_switch_mac_hi_set(unit, type, arg);
                SHR_IF_ERR_EXIT(rv);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Feature unavailable: soc_feature_rcpu_1\r\n");
            }
            break;
        }
        case bcmSwitchRemoteCpuLocalMacNonOui:
        case bcmSwitchRemoteCpuDestMacNonOui:
        {
            if ((arg < 0x0) || (arg > 0xffffff))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid value %d provided to switch control type=%d. Supported values are 0~0xffffff.\n",
                             arg, type);
            }
            if (dnx_drv_soc_feature(unit, soc_feature_rcpu_1))
            {
                rv = _bcm_dnx_rcpu_switch_mac_lo_set(unit, type, arg);
                SHR_IF_ERR_EXIT(rv);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Feature unavailable: soc_feature_rcpu_1\r\n");
            }
            break;
        }
        case bcmSwitchRemoteCpuEthertype:
        case bcmSwitchRemoteCpuVlan:
        case bcmSwitchRemoteCpuTpid:
        case bcmSwitchRemoteCpuSignature:
        {
            if ((arg < 0x0) || (arg > 0xffff))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid value %d provided to switch control type=%d. Supported values are 0~0xffff.\n",
                             arg, type);
            }
            if (dnx_drv_soc_feature(unit, soc_feature_rcpu_1))
            {
                rv = _bcm_dnx_rcpu_switch_vlan_tpid_sig_set(unit, type, arg);
                SHR_IF_ERR_EXIT(rv);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Feature unavailable: soc_feature_rcpu_1\r\n");
            }
            break;
        }
#endif /* #if defined(BCM_RCPU_SUPPORT) */

        case bcmSwitchWarmBoot:
        case bcmSwitchStableSelect:
        case bcmSwitchStableSize:
        case bcmSwitchStableUsed:
            /*
             * all should be configured through config.bcm
             */
            SHR_ERR_EXIT(BCM_E_UNAVAIL, "Unsupported switch control");
        case bcmSwitchCrashRecoveryMode:
        case bcmSwitchCrTransactionStart:
        case bcmSwitchCrCommit:
        case bcmSwitchCrLastTransactionStatus:
        case bcmSwitchCrCouldNotRecover:
            SHR_ERR_EXIT(BCM_E_UNAVAIL, "Feature unavailable: crash recovery\n");
        case bcmSwitchControlAutoSync:
            SHR_ERR_EXIT(BCM_E_UNAVAIL, "Feature unavailable: autosync\n");
        case bcmSwitchControlSync:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_sync_handle(unit, arg));
            break;
        }

        case bcmSwitchMcastTrunkIngressCommit:
        {
            SHR_IF_ERR_EXIT(dnx_trunk_flip_active_configuration_selector(unit));
            break;
        }

        case bcmSwitchMcastTrunkEgressCommit:
        {
            if (!dnx_data_trunk.egress_trunk.feature_get(unit, dnx_data_trunk_egress_trunk_is_supported))
            {
                SHR_ERR_EXIT(BCM_E_UNAVAIL, "Feature unavailable: bcmSwitchMcastTrunkEgressCommit\n");
            }
            SHR_IF_ERR_EXIT(dnx_trunk_active_configuration_to_stand_by_configuration_copy(unit));
            break;
        }

        case bcmSwitchPolicerFairness:
        {
            SHR_IF_ERR_EXIT(dnx_policer_mgmt_fairness_set(unit, 0, arg));
            break;
        }
        case bcmSwitchCacheTableUpdateAll:
        {
#ifdef BCM_ACCESS_SUPPORT
            if (ACCESS_IS_INITIALIZED(unit))
            {
                SHR_IF_ERR_EXIT(access_cache_table_update_all(unit));
            }
            else
#endif
            {
                SHR_IF_ERR_EXIT(soc_sand_cache_table_update_all(unit));
            }
            break;
        }

        case bcmSwitchL2StationExtendedMode:
        {
            SHR_IF_ERR_EXIT(dnx_l2_station_multi_my_mac_exem_mode_set(unit, arg));
            break;
        }
        case bcmSwitchMplsPipeTunnelLabelExpSet:
        {
            SHR_ERR_EXIT(BCM_E_UNAVAIL,
                         "This configuration is redundant in current device. EXP in PIPE mode can be both SET and COPY according to mpls api flags configuration\n");
            break;
        }
        case bcmSwitchSynchronousPortClockSource:
        {
            SHR_IF_ERR_EXIT(dnx_synce_port_set(unit, 0, arg));
        }
            break;
        case bcmSwitchSynchronousPortClockSourceBkup:
        {
            SHR_IF_ERR_EXIT(dnx_synce_port_set(unit, 1, arg));
        }
            break;
        case bcmSwitchSynchronousPortClockSourceDivCtrl:
        {
            SHR_IF_ERR_EXIT(dnx_synce_divider_set(unit, 0, arg));
        }
            break;
        case bcmSwitchSynchronousPortClockSourceBkupDivCtrl:
        {
            SHR_IF_ERR_EXIT(dnx_synce_divider_set(unit, 1, arg));
        }
            break;
        /** Protocol traps additional switch control configuration */
        case bcmSwitchArpMyIp1:
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_arp_get(unit, &my_arp_ndp_config));
            my_arp_ndp_config.ip_1 = arg;
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_arp_set(unit, &my_arp_ndp_config));
            break;
        case bcmSwitchArpMyIp2:
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_arp_get(unit, &my_arp_ndp_config));
            my_arp_ndp_config.ip_2 = arg;
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_arp_set(unit, &my_arp_ndp_config));
            break;
        case bcmSwitchArpIgnoreDa:
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_arp_get(unit, &my_arp_ndp_config));
            my_arp_ndp_config.ignore_da = arg;
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_arp_set(unit, &my_arp_ndp_config));
            break;
        case bcmSwitchIcmpIgnoreDa:
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_icmp_ignore_da_hw_set(unit, arg));
            break;
        case bcmSwitchExternalTcamSync:
            SHR_IF_ERR_EXIT(dnx_switch_control_external_tcam_sync_handle(unit));
            break;
        case bcmSwitchExternalTcamInit:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_external_tcam_init_deinit_handle(unit, arg));
            break;
        }
        case bcmSwitchL3RouteCache:
        {
            SHR_IF_ERR_EXIT(dbal_bulk_mode_set(unit, DBAL_ACCESS_METHOD_KBP, DBAL_BULK_MODULE_KBP_FWD, arg));
            break;
        }
        case bcmSwitchL3RouteCommit:
        {
            SHR_IF_ERR_EXIT(dbal_bulk_commit(unit, DBAL_ACCESS_METHOD_KBP, DBAL_BULK_MODULE_KBP_FWD));
            break;
        }
        case bcmSwitchFieldCache:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                         "bcmSwitchFieldCache is no longer supported. Please use bcm_field_group_cache() for caching per FG.\n");
            break;
        }
        case bcmSwitchFieldCommit:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                         "bcmSwitchFieldCommit is no longer supported. Please use bcm_field_group_cache() for caching per FG.\n");
            break;
        }
        case bcmSwitchL3UrpfMode:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                         "bcmSwitchL3UrpfMode is not supported in DNX devices - global RPF mode is no longer supported, instead use per RIF option.\n");
            break;
        }
        case bcmSwitchL3McastL2:
        {
            if (arg >= DBAL_NOF_ENUM_L2_V4_MC_FWD_TYPE_VALUES)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid parameter provided to bcmSwitchL3McastL2 - expected DBAL_ENUM_FVAL_L2_V4_MC_FWD_TYPE_BRIDGE or DBAL_ENUM_FVAL_L2_V4_MC_FWD_TYPE_IPV4MC");
            }
            SHR_IF_ERR_EXIT(switch_db.l3mcastl2_ipv4_fwd_type.set(unit, (uint8) arg));
            break;
        }
        case bcmSwitchL3IP6McastL2:
        {
            if (arg >= DBAL_NOF_ENUM_L2_V6_MC_FWD_TYPE_VALUES)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid parameter provided to bcmSwitchL3IP6McastL2 - expected DBAL_ENUM_FVAL_L2_V6_MC_FWD_TYPE_BRIDGE or DBAL_ENUM_FVAL_L2_V6_MC_FWD_TYPE_IPV6MC");
            }
            SHR_IF_ERR_EXIT(switch_db.l3mcastl2_ipv6_fwd_type.set(unit, (uint8) arg));
            break;
        }
        case bcmSwitchDescCommit:
        {
            SHR_IF_ERR_EXIT(dnx_sbusdma_desc_wait_done(unit));
            break;
        }
        case bcmSwitchIngressRateLimitMpps:
        {
            SHR_IF_ERR_EXIT(dnx_cosq_ingress_receive_packet_rate_limit_set(unit, arg));
            break;
        }
        case bcmSwitchL3RoutedLearn:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_routed_learn_set(unit, arg));
            break;
        }
        case bcmSwitchTunnelRouteDisable:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_tunnel_route_disable_set(unit, arg));
            break;
        }
        case bcmSwitchL3VpbrTunnel:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_tunnel_termination_ipv4_vrf_reselect_enable_set(unit, arg));
            break;
        }
        case bcmSwitchEndToEndLatencyPerDestinationPort:
        {
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_per_port_set(unit, arg));
            break;
        }
        case bcmSwitchForwardLookupNotFoundTrap:
        {
            SHR_IF_ERR_EXIT(dnx_switch_fwd_not_found_trap_set(unit, arg));
            break;
        }
        case bcmSwitchFtmhEtherType:
        {
            /*
             * Set Ethertype for outgoing packets with FTMH forwarding header
             */
            if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_application_v1))
            {
                SHR_IF_ERR_EXIT(dnx_init_pp_egress_current_next_protocol_config_table_configure(unit,
                                                                                                DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_INGRESS_SCTP_EGRESS_FTMH,
                                                                                                DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
                                                                                                arg));
            }
            break;
        }
        case bcmSwitchSRV6EgressPSPEnable:
        {
            /** set SRv6 Egress to PSP mode */
            SHR_IF_ERR_EXIT(dnx_switch_srv6_modes_set(unit, bcmSwitchSRV6EgressPSPEnable, arg));
            break;
        }
        case bcmSwitchSRV6ReducedModeEnable:
        {
            /** set SRv6 Encapsulation to Reduced mode */
            SHR_IF_ERR_EXIT(dnx_switch_srv6_modes_set(unit, bcmSwitchSRV6ReducedModeEnable, arg));
            break;
        }
        case bcmSwitchSrv6GsidPrefixBits:
        {
            /** set SRv6 GSID to Prefix 64b mode */
            SHR_IF_ERR_EXIT(dnx_switch_srv6_modes_set(unit, bcmSwitchSrv6GsidPrefixBits, arg));
            break;
        }
        case bcmSwitchSrv6UsidPrefixBits:
        {
            /** set SRv6 GSID to Prefix 64b mode */
            SHR_IF_ERR_EXIT(dnx_switch_srv6_modes_set(unit, bcmSwitchSrv6UsidPrefixBits, arg));
            break;
        }
        case bcmSwitchUdpTunnelIPv4DstPort:
        case bcmSwitchUdpTunnelIPv6DstPort:
        case bcmSwitchUdpTunnelMplsDstPort:
        case bcmSwitchVxlanUdpDestPortSet:
        case bcmSwitchVxlanGpeUdpDestPortSet:
        case bcmSwitchGeneveUdpDestPortSet:
        {
            /*
             * update udp destination port at parser
             */
            /*
             * update udp destination port at encapsulation when UDP next protocol is IPV4
             */
            SHR_IF_ERR_EXIT(dnx_switch_control_udp_destination_port_configure(unit, type, arg));
            break;
        }
        case bcmSwitchHashIP4OuterField:
        case bcmSwitchHashIP4InnerField:
        case bcmSwitchHashIP6Field:
        case bcmSwitchHashL2OuterField:
        case bcmSwitchHashL2InnerField:
        case bcmSwitchHashL4Field:
        case bcmSwitchHashMPLSField0:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_load_balancing_hash_fields_masking_set(unit, type, arg));
            break;
        }
        case bcmSwitchHashForceL2Field:
        {
            if ((arg != TRUE) && (arg != FALSE))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid value %d provided to switch control type=%d.\n", arg, type);
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_load_balancing_hash_force_l2_set(unit, (uint32) arg));
            break;
        }
        case bcmSwitchBfdMyDipDestination:
        {
            SHR_IF_ERR_EXIT(dnx_bfd_my_dip_destination_set(unit, arg));
            break;
        }
        case bcmSwitchMplsAlternateMarkingSpecialLabel:
        {
            if (!dnx_data_mpls.general.feature_get(unit, dnx_data_mpls_general_support_alternate_marking))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Not supported bcmSwitchMplsAlternateMarkingSpecialLabel\n");
            }

            SHR_IF_ERR_EXIT(dnx_mpls_alternate_marking_special_label_set(unit, arg));
            break;
        }
        case bcmSwitchMplsFlowInstructionIndicatorSpecialLabel:
        {
            SHR_IF_ERR_EXIT(dnx_mpls_flow_instrunction_indicator_label_set(unit, arg));
            break;
        }
        case bcmSwitchGlobalTodMode:
        {
            if ((arg < 0x0) || (arg >= bcmSwitchTodModeCount))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid value %d provided to switch control type=%d.\n", arg, type);
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_global_tod_mode_set(unit, arg));
            break;
        }
        case bcmSwitchPFCDeadlockRecoveryAction:
        {
            if (arg < bcmSwitchPFCDeadlockActionTransmit || arg > bcmSwitchPFCDeadlockActionDrop)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid value %d provided to switch control type=%d.\n", arg, type);
            }
            SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.action.set(unit, arg));
            break;
        }
        case bcmSwitchControlOamBfdFailoverStateIgnore:
        {
            if (!dnx_data_device.general.feature_get(unit, dnx_data_device_general_protection_state_ignore))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Not supported bcmSwitchControlOamBfdFailoverStateIgnore\n");
            }
            if ((arg < 0x0) || (arg > 1))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid value %d provided to switch control type=%d.\n", arg, type);
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_oam_bfd_failover_state_ignore_set(unit, arg));
            break;
        }
        case bcmSwitchExactMatchInit:
        {
            if (!dnx_data_mdb.feature.feature_get(unit, dnx_data_mdb_feature_em_compare_init))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Not supported bcmSwitchExactMatchInit\n");
            }
            if ((arg != 1) && (arg != 2))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid value %d provided to switch control type=%d. - only 1 (verify disabled) or 2 (verify enabled) is valid\n",
                             arg, type);
            }
            else
            {
                int verify = (arg == 1) ? FALSE : TRUE;
                SHR_IF_ERR_EXIT(dnx_switch_control_mdb_exact_match_false_hit_set(unit, verify));
            }
            break;
        }
        case bcmSwitchRangeOperator:
        {
            if (arg < bcmSwitchRangeOperatorFirst && arg >= bcmSwitchRangeOperatorCount)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid value %d provided to switch control type=%d. value should be between [%d,%d]\n",
                             arg, type, bcmSwitchRangeOperatorFirst, bcmSwitchRangeOperatorCount);
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_range_operator_set(unit, arg));
            break;
        }
        case bcmSwitchSLLBDestinationNotFound:
        {
            if (dnx_data_l3.vip_ecmp.feature_get(unit, dnx_data_l3_vip_ecmp_supported))
            {
                SHR_IF_ERR_EXIT(dnx_switch_control_sllb_default_destination_set(unit, arg));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This BCM switch control type (%d) is not supported! \n", type);
            }
            break;
        }
        case bcmSwitchVIPEcmpTableSize:
        {
            if (dnx_data_l3.vip_ecmp.feature_get(unit, dnx_data_l3_vip_ecmp_supported))
            {
                SHR_IF_ERR_EXIT(dnx_switch_control_sllb_table_size_set(unit, arg));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This BCM switch control type (%d) is not supported! \n", type);
            }
            break;
        }
        case bcmSwitchVIPL3EgressIDMin:
        {
            if (dnx_data_l3.vip_ecmp.feature_get(unit, dnx_data_l3_vip_ecmp_supported))
            {
                SHR_IF_ERR_EXIT(dnx_switch_control_vip_l3_egress_id_min_set(unit, arg));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This BCM switch control type (%d) is not supported! \n", type);
            }
            break;
        }
        case bcmSwitchFlexeOamAlmCollectionTimerStep:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_oam_alarm_collection_timer_step_set(unit, arg));
            break;
        }
        case bcmSwitchFlexeOamAlmCollectionStepCount:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_oam_alarm_collection_step_count_set(unit, arg));
            break;
        }
        case bcmSwitchFlexeSarCellMode:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_sar_cell_mode_set(unit, arg));
            break;
        }
        case bcmSwitchIngParseL3L4IPv4:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_parse_udp_enable_set
                            (unit, dnxParseUdpNextHeaderIpv4, UTILEX_NUM2BOOL(arg)));
            break;
        }
        case bcmSwitchIngParseL3L4IPv6:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_parse_udp_enable_set
                            (unit, dnxParseUdpNextHeaderIpv6, UTILEX_NUM2BOOL(arg)));
            break;
        }
        case bcmSwitchMplsEvpnEntropyEnable:
        {
            if (dnx_data_mpls.general.feature_get(unit, dnx_data_mpls_general_mpls_term_till_bos))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmSwitchMplsEvpnEntropyEnable is not supported in current device\n");
            }
            SHR_IF_ERR_EXIT(dnx_mpls_dual_homing_fl_termination_enable_set(unit, arg));
            break;
        }
        case bcmSwitchL2LearnLimitCheckStatic:
        {
            rv = dnx_l2_learn_limit_check_static_set(unit, arg);
            SHR_IF_ERR_EXIT(rv);
            break;
        }
        case bcmSwitchL2ChangeFieldsEnable:
        {
            if (!dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_separate_fwd_learn_mact))
            {
                rv = dnx_l2_static_transplant_commit_flags_set(unit, arg ? DBAL_COMMIT_FORCE : DBAL_COMMIT);
                SHR_IF_ERR_EXIT(rv);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmSwitchL2ChangeFieldsEnable is not supported in current device\n");
            }
            break;
        }
        case bcmSwitchOamAdditionalGalSpecialLabel:
        {
            if (dnx_data_oam.oamp.feature_get(unit, dnx_data_oam_oamp_oamp_v2) == 0)
            {
                SHR_IF_ERR_EXIT(dnx_oam_oamp_v1_additional_gal_special_label_set(unit, arg));
            }
            break;
        }
        case bcmSwitchFlexe1588RxDestMacOui:
        case bcmSwitchFlexe1588RxDestMacNonOui:
        case bcmSwitchFlexe1588RxSrcMacOui:
        case bcmSwitchFlexe1588RxSrcMacNonOui:
        case bcmSwitchFlexe1588TxDestMacOui:
        case bcmSwitchFlexe1588TxDestMacNonOui:
        case bcmSwitchFlexe1588TxSrcMacOui:
        case bcmSwitchFlexe1588TxSrcMacNonOui:
        case bcmSwitchFlexe1588OverEthRxUnicastDestMacOui:
        case bcmSwitchFlexe1588OverEthRxUnicastDestMacNonOui:
        case bcmSwitchFlexe1588OverEthTxUnicastDestMacOui:
        case bcmSwitchFlexe1588OverEthTxUnicastDestMacNonOui:
        case bcmSwitchFlexe1588OverIpv4RxUnicastDestIpHigh:
        case bcmSwitchFlexe1588OverIpv4RxUnicastDestIpLow:
        case bcmSwitchFlexe1588OverIpv4TxUnicastDestIpHigh:
        case bcmSwitchFlexe1588OverIpv4TxUnicastDestIpLow:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_1588_pkt_header_set(unit, type, arg));
            break;
        }
        case bcmSwitchFlexeBasOamToExtProcessorEnable:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_bas_oam_to_ext_processor_set(unit, arg));
            break;
        }
        case bcmSwitchFlexeOhOamPktDestMacOui:
        case bcmSwitchFlexeOhOamPktDestMacNonOui:
        case bcmSwitchFlexeOhOamPktSrcMacOui:
        case bcmSwitchFlexeOhOamPktSrcMacNonOui:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_oh_oam_pkt_mac_set(unit, type, arg));
            break;
        }
        case bcmSwitchFlexeOamBasBipRecalculationEnable:
        case bcmSwitchFlexeOamBasPeriodMismatchTriggerLosAlarm:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_oam_switch_control_set(unit, type, arg));
            break;
        }
        case bcmSwitchMplsLastTermMode:
        {
            if ((arg != 0) && (arg != 1))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Invalid value %d provided to switch control type=%d. - only 0 or 1 is valid\n",
                             arg, type);
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_mpls_last_term_mode_set(unit, arg));
            break;
        }

        case bcmSwitchIngressVlanEditClassNull:
            SHR_IF_ERR_EXIT(dnx_switch_control_last_ivec_fhei_size_set(unit, arg));
            break;
        case bcmSwitchMplsSpecialLabelPerPortTerminateDisable:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_per_port_special_label_termination_disable_set(unit, arg));
            break;
        }
        case bcmSwitchWideDataExtKeyMode:
            SHR_IF_ERR_EXIT(dnx_switch_wide_data_ext_key_mode_set(unit, arg));
            break;

        case bcmSwitchTwampStatelessModeEnable:
        {
            SHR_IF_ERR_EXIT(dnx_oam_twamp_stateless_mode_set(unit, arg));
            break;
        }
        case bcmSwitchReflectorL2IntPriority:
        {
            SHR_IF_ERR_EXIT(dnx_switch_reflector_rcy_priority_set(unit, arg));
            break;
        }
        case bcmSwitchPfcRxSvtagEnable:
        {
            SHR_IF_ERR_EXIT(dnx_switch_svtag_pfc_flow_control_mapping_set(unit, arg));
            break;
        }

        default:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This BCM switch control type (%d) is not supported! \n", type);
        }
    }

    SHR_EXIT();

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Verify function for BCM-API bcm_dnx_switch_control_get
 */
static shr_error_e
dnx_switch_control_get_verify(
    int unit,
    bcm_switch_control_t type,
    int *arg)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(arg, _SHR_E_PARAM, "arg");

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Return the traverse mode of the flush machine. Normal or aggregate.
 *
 * \param [in] unit - unit id
 * \param [in] flush_mode - traverse mode bcmSwitchTableUpdateRuleAdd for aggregate or bcmSwitchTableUpdateNormal.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_switch_traverse_mode_get(
    int unit,
    int *flush_mode)
{
    int collect_mode;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_bulk_mode_get(unit, DBAL_ACCESS_METHOD_MDB, DBAL_BULK_MODULE_MDB_LEM_FLUSH, &collect_mode));

    if (collect_mode)
    {
        *flush_mode = bcmSwitchTableUpdateRuleAdd;
    }
    else
    {
        *flush_mode = bcmSwitchTableUpdateNormal;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get port-specific and device-wide operating modes.
 *
 * Use cases:
 *
 * 1.
 * Description
 * Parameters:
 * - type -
 * - arg -
 *
 * 728.
 * Meter - enable disable fairness mechanism (adding random number to the bucket level) for all
 *         meter databases (ingress/egress/global) and for CBL and EBL buckets.
 * Parameters:
 * - type - bcmSwitchPolicerFairness
 * - arg -  TRUE/FALSE to enable/disable the feature
 *
 * 780.
 * Return whether the limits on MACT are forced on CPU MACT additions.
 * Parameters:
 * - type - bcmSwitchL2LearnLimitToCpu
 * - arg -  '1' means limits are checked. '0' means limits are not forced for CPU add MACT entry.
 *
 * \param [in] unit - Relevant unit
 * \param [in] type - Configuration option taken from bcm_switch_control_t
 * \param [out] arg - Argument for the configuration
 *
 * \return
 *   int
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_control_get(
    int unit,
    bcm_switch_control_t type,
    int *arg)
{
    int rv = BCM_E_NONE;
    dnx_rx_trap_protocol_my_arp_ndp_config_t my_arp_ndp_config;
#ifdef BCM_WARM_BOOT_SUPPORT
    uint32 flags;
#endif
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED_SWITCH(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_switch_control_get_verify(unit, type, arg));

    switch (type)
    {
        case bcmSwitchECMPHashConfig:
        case bcmSwitchECMPSecondHierHashConfig:
        case bcmSwitchECMPThirdHierHashConfig:
        case bcmSwitchTrunkHashConfig:
        case bcmSwitchNwkHashConfig:
        {
            if (dnx_data_switch.load_balancing.feature_get(unit, dnx_data_switch_load_balancing_fwd_hashing_method) ==
                DNX_SWITCH_LB_FWD_HASH_METHOD_CRC_FUNCTION)
            {
                int index;
                dnx_switch_lb_tcam_key_t tcam_key;
                dnx_switch_lb_tcam_result_t tcam_result;
                dnx_switch_lb_valid_t tcam_valid;
                uint32 physical_client;

                index = 0;
                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_tcam_info_get
                                (unit, index, &tcam_key, &tcam_result, &tcam_valid));
                /*
                 * Convert logical client to physical so it can be read from tcam
                 */
                SHR_IF_ERR_EXIT(dnx_switch_lb_logical_client_to_physical
                                (unit, (bcm_switch_control_t) type, &physical_client));

                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_crc_function_hw_to_enum_get
                                (unit, tcam_result.client_x_crc_16_sel[physical_client],
                                 (bcm_switch_hash_config_t *) arg));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This type is not supported.\n");
            }
            break;
        }
        case bcmSwitchMplsStack0HashSeed:
        {
            dnx_switch_lb_general_seeds_t general_seeds;

            SHR_IF_ERR_EXIT(dnx_switch_load_balancing_general_seeds_get(unit, &general_seeds));
            *arg = (int) (general_seeds.mpls_stack_0);
            break;
        }
        case bcmSwitchMplsStack1HashSeed:
        {
            SHR_ERR_EXIT(BCM_E_UNAVAIL, "'bcmSwitchMplsStack1HashSeed' (%d) is, currently, unsupported", type);
            break;
        }
        case bcmSwitchIpv6NextProtocolEthernet:
        {
            SHR_IF_ERR_EXIT(dnx_ip_next_protocol_eth_configure_get(unit, arg));
            break;
        }
        case bcmSwitchParserHashSeed:
        {
            if (dnx_data_switch.
                load_balancing.feature_get(unit, dnx_data_switch_load_balancing_paser_seed_update_supported))
            {
                dnx_switch_lb_general_seeds_t general_seeds;
                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_general_seeds_get(unit, &general_seeds));
                *arg = (int) (general_seeds.parser);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The bcmSwitchParserHashSeed isn't supported in this device \n");
            }
            break;
        }
        case bcmSwitchTraverseMode:
        {
            SHR_IF_ERR_EXIT(dnx_switch_traverse_mode_get(unit, arg));
            break;
        }
        case bcmSwitchTraverseCommitDone:
        {
            SHR_IF_ERR_EXIT(dnx_l2_traverse_commit_done_get(unit, arg));
            break;
        }
        case bcmSwitchCrashRecoveryMode:
            SHR_ERR_EXIT(BCM_E_UNAVAIL, "Feature unavailable: crash recovery\n");
        case bcmSwitchControlAutoSync:
            rv = BCM_E_UNAVAIL;
            break;
        case bcmSwitchControlSync:
            break;
#ifdef BCM_WARM_BOOT_SUPPORT
        case bcmSwitchStableSelect:
            rv = soc_stable_get(unit, arg, &flags);
            break;
        case bcmSwitchStableSize:
            rv = soc_stable_size_get(unit, arg);
            break;
        case bcmSwitchStableUsed:
            rv = soc_stable_used_get(unit, arg);
            break;
        case bcmSwitchWarmBoot:
            (*arg) = sw_state_is_warm_boot(unit);
            rv = _SHR_E_NONE;
            break;
#else /* BCM_WARM_BOOT_SUPPORT */
        case bcmSwitchStableSelect:
        case bcmSwitchStableSize:
        case bcmSwitchStableUsed:
        case bcmSwitchWarmBoot:
            SHR_ERR_EXIT(BCM_E_UNAVAIL, "Feature unavailable: warmboot\n");
#endif
        case bcmSwitchL2LearnMode:
        {
            SHR_IF_ERR_EXIT(dnx_l2_learn_mode_get(unit, arg));
            break;
        }
        case bcmSwitchMactAgeRefreshMode:
        {
            if (!dnx_data_l2.feature.feature_get(unit, dnx_data_l2_feature_age_refresh_mode_support))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "age refresh mode configuration is not supported for this device");
            }
            SHR_IF_ERR_EXIT(mdb_em_mact_age_refresh_mode_get(unit, (uint32 *) arg));
            break;
        }
        case bcmSwitchL2LearnLimitToCpu:
        {
            rv = dnx_l2_learn_limit_to_cpu_get(unit, arg);
            SHR_IF_ERR_EXIT(rv);
            break;
        }
        case bcmSwitchL2StaticMoveToCpu:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmSwitchL2StaticMoveToCpu is not supported.\n");
        }
        case bcmSwitchL3UrpfDefaultRoute:
        {
            if (dnx_data_l3.feature.feature_get(unit, dnx_data_l3_feature_rpf_default_route_supported))
            {
                int is_uc = 1;
                rv = dnx_l3_rpf_default_route_get(unit, is_uc, arg);
                SHR_IF_ERR_EXIT(rv);

            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Not supported bcmSwitchL3UrpfDefaultRoute \n");
            }
            break;
        }
        case bcmSwitchMeterMef10dot3Enable:
            SHR_IF_ERR_EXIT(dnx_policer_mgmt_mef_10_3_get(unit, arg));
            break;
        case bcmSwitchL3McRpfDefaultRoute:
        {
            int is_uc = 0;
            rv = dnx_l3_rpf_default_route_get(unit, is_uc, arg);
            SHR_IF_ERR_EXIT(rv);
            break;
        }
        case bcmSwitchMplsPWControlWord:
        {
            SHR_IF_ERR_EXIT(dnx_mpls_cw_get(unit, arg));
            break;
        }
        /************************************************************************/
            /*
             * RCPU
             */
        /************************************************************************/
#if defined(BCM_RCPU_SUPPORT)
        case bcmSwitchRemoteCpuSchanEnable:
        case bcmSwitchRemoteCpuMatchLocalMac:
        case bcmSwitchRemoteCpuCmicEnable:
        case bcmSwitchRemoteCpuMatchVlan:
        {
            if (dnx_drv_soc_feature(unit, soc_feature_rcpu_1))
            {
                rv = _bcm_dnx_rcpu_switch_enable_get(unit, type, arg);
                SHR_IF_ERR_EXIT(rv);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Feature unavailable: soc_feature_rcpu_1\r\n");
            }
            break;
        }
        case bcmSwitchRemoteCpuLocalMacOui:
        case bcmSwitchRemoteCpuDestMacOui:
        {
            if (dnx_drv_soc_feature(unit, soc_feature_rcpu_1))
            {
                rv = _bcm_dnx_rcpu_switch_mac_hi_get(unit, type, arg);
                SHR_IF_ERR_EXIT(rv);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Feature unavailable: soc_feature_rcpu_1\r\n");
            }
            break;
        }
        case bcmSwitchRemoteCpuLocalMacNonOui:
        case bcmSwitchRemoteCpuDestMacNonOui:
        {
            if (dnx_drv_soc_feature(unit, soc_feature_rcpu_1))
            {
                rv = _bcm_dnx_rcpu_switch_mac_lo_get(unit, type, arg);
                SHR_IF_ERR_EXIT(rv);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Feature unavailable: soc_feature_rcpu_1\r\n");
            }
            break;
        }
        case bcmSwitchRemoteCpuEthertype:
        case bcmSwitchRemoteCpuVlan:
        case bcmSwitchRemoteCpuTpid:
        case bcmSwitchRemoteCpuSignature:
        {
            if (dnx_drv_soc_feature(unit, soc_feature_rcpu_1))
            {
                rv = _bcm_dnx_rcpu_switch_vlan_tpid_sig_get(unit, type, arg);
                SHR_IF_ERR_EXIT(rv);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Feature unavailable: soc_feature_rcpu_1\r\n");
            }
            break;
        }
#endif /* #if defined(BCM_RCPU_SUPPORT) */

        case bcmSwitchMcastTrunkIngressCommit:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Feature unsupported for get\n");
            break;
        }

        case bcmSwitchMcastTrunkEgressCommit:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Feature unsupported for get\n");
            break;
        }

        case bcmSwitchPolicerFairness:
        {
            SHR_IF_ERR_EXIT(dnx_policer_mgmt_fairness_get(unit, 0, (uint32 *) arg));
            break;
        }

        case bcmSwitchL2StationExtendedMode:
        {
            SHR_IF_ERR_EXIT(dnx_l2_station_multi_my_mac_exem_mode_get(unit, arg));
            break;
        }
        case bcmSwitchMplsPipeTunnelLabelExpSet:
        {
            SHR_ERR_EXIT(BCM_E_UNAVAIL,
                         "This configuration is redundant in current device. EXP in PIPE mode can be both SET and COPY according to mpls api flags configuration\n");
            break;
        }
        case bcmSwitchSynchronousPortClockSource:
        {
            SHR_IF_ERR_EXIT(dnx_synce_port_get(unit, 0, arg));
        }
            break;
        case bcmSwitchSynchronousPortClockSourceBkup:
        {
            SHR_IF_ERR_EXIT(dnx_synce_port_get(unit, 1, arg));
        }
            break;
        case bcmSwitchSynchronousPortClockSourceDivCtrl:
        {
            SHR_IF_ERR_EXIT(dnx_synce_divider_get(unit, 0, arg));
        }
            break;
        case bcmSwitchSynchronousPortClockSourceBkupDivCtrl:
        {
            SHR_IF_ERR_EXIT(dnx_synce_divider_get(unit, 1, arg));
        }
            break;
        /** Protocol traps additional switch control configuration */
        case bcmSwitchArpMyIp1:
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_arp_get(unit, &my_arp_ndp_config));
            *arg = my_arp_ndp_config.ip_1;
            break;
        case bcmSwitchArpMyIp2:
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_arp_get(unit, &my_arp_ndp_config));
            *arg = my_arp_ndp_config.ip_2;
            break;
        case bcmSwitchArpIgnoreDa:
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_arp_get(unit, &my_arp_ndp_config));
            *arg = my_arp_ndp_config.ignore_da;
            break;
        case bcmSwitchIcmpIgnoreDa:
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_icmp_ignore_da_hw_get(unit, arg));
            break;
        case bcmSwitchL3UrpfMode:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                         "bcmSwitchL3UrpfMode is not supported in DNX devices - global RPF mode is no longer supported, instead use per RIF option.\n");
            break;
        }
        case bcmSwitchL3McastL2:
        {
            uint8 fwd_type;
            SHR_IF_ERR_EXIT(switch_db.l3mcastl2_ipv4_fwd_type.get(unit, &fwd_type));
            *arg = fwd_type;
            break;
        }
        case bcmSwitchL3IP6McastL2:
        {
            uint8 fwd_type;
            SHR_IF_ERR_EXIT(switch_db.l3mcastl2_ipv6_fwd_type.get(unit, &fwd_type));
            *arg = fwd_type;
            break;
        }
        case bcmSwitchEtagEthertype:
        {
            uint16 tpid_value;
            SHR_IF_ERR_EXIT(dnx_port_sit_tag_swap_tpid_get(unit, DNX_TAG_SWAP_TPID_INDEX_DOT1BR, &tpid_value));
            *arg = tpid_value;
            break;
        }
        case bcmSwitchIngressRateLimitMpps:
        {
            SHR_IF_ERR_EXIT(dnx_cosq_ingress_receive_packet_rate_limit_get(unit, arg));
            break;
        }
        case bcmSwitchL3RoutedLearn:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_routed_learn_get(unit, arg));
            break;
        }
        case bcmSwitchTunnelRouteDisable:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_tunnel_route_disable_get(unit, arg));
            break;
        }
        case bcmSwitchL3VpbrTunnel:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_tunnel_termination_ipv4_vrf_reselect_enable_get(unit, arg));
            break;
        }
        case bcmSwitchEndToEndLatencyPerDestinationPort:
        {
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_per_port_get(unit, arg));
            break;
        }
        case bcmSwitchForwardLookupNotFoundTrap:
        {
            SHR_IF_ERR_EXIT(dnx_switch_fwd_not_found_trap_get(unit, arg));
            break;
        }
        case bcmSwitchFtmhEtherType:
        {
            /*
             * Set Ethertype for outgoing packets with FTMH forwarding header
             */
            if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_application_v1))
            {
                SHR_IF_ERR_EXIT(dnx_init_pp_egress_current_next_protocol_config_table_get(unit,
                                                                                          DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_INGRESS_SCTP_EGRESS_FTMH,
                                                                                          DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
                                                                                          arg));
            }
            break;
        }

        case bcmSwitchExternalTcamSync:
        {
            int device_locked;
            if (!dnx_kbp_device_enabled(unit))
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "KBP device is not enabled\n");
            }
            /** check if bcm_switch_control_set() was called - return 1 if it was, 0 if not*/
            *arg = 0;
            SHR_IF_ERR_EXIT(dnx_field_map_is_device_locked(unit, &device_locked));
            if (device_locked)
            {
                *arg = 1;
            }
            break;
        }
        case bcmSwitchL3RouteCache:
        {
            SHR_IF_ERR_EXIT(dbal_bulk_mode_get(unit, DBAL_ACCESS_METHOD_KBP, DBAL_BULK_MODULE_KBP_FWD, arg));
            break;
        }
        case bcmSwitchFieldCache:
        {
            SHR_IF_ERR_EXIT(dbal_bulk_mode_get(unit, DBAL_ACCESS_METHOD_KBP, DBAL_BULK_MODULE_KBP_ACL, arg));
            break;
        }

        case bcmSwitchUdpTunnelIPv4DstPort:
        case bcmSwitchUdpTunnelIPv6DstPort:
        case bcmSwitchUdpTunnelMplsDstPort:
        case bcmSwitchVxlanUdpDestPortSet:
        case bcmSwitchVxlanGpeUdpDestPortSet:
        case bcmSwitchGeneveUdpDestPortSet:
        {
            uint32 udp_dest_port;
            SHR_IF_ERR_EXIT(dnx_switch_control_udp_destination_port_get(unit, type, &udp_dest_port));
            *arg = (int) udp_dest_port;
            break;
        }
        case bcmSwitchHashIP4OuterField:
        case bcmSwitchHashIP4InnerField:
        case bcmSwitchHashIP6Field:
        case bcmSwitchHashL2OuterField:
        case bcmSwitchHashL2InnerField:
        case bcmSwitchHashL4Field:
        case bcmSwitchHashMPLSField0:

        {
            uint32 mask = 0;
            SHR_IF_ERR_EXIT(dnx_switch_control_load_balancing_hash_fields_masking_get(unit, type, &mask));
            *arg = (int) mask;
            break;
        }
        case bcmSwitchHashForceL2Field:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_load_balancing_hash_force_l2_get(unit, (uint32 *) arg));
            break;
        }
        case bcmSwitchSRV6EgressPSPEnable:
        {
            /** get SRv6 Egress to PSP mode */
            SHR_IF_ERR_EXIT(dnx_switch_srv6_modes_get(unit, bcmSwitchSRV6EgressPSPEnable, arg));
            break;
        }
        case bcmSwitchSRV6ReducedModeEnable:
        {
            /** get SRv6 Encapsulation to Reduced mode */
            SHR_IF_ERR_EXIT(dnx_switch_srv6_modes_get(unit, bcmSwitchSRV6ReducedModeEnable, arg));
            break;
        }
        case bcmSwitchSrv6GsidPrefixBits:
        {
            /** get SRv6 GSID Prefix mode */
            SHR_IF_ERR_EXIT(dnx_switch_srv6_modes_get(unit, bcmSwitchSrv6GsidPrefixBits, arg));
            break;
        }
        case bcmSwitchSrv6UsidPrefixBits:
        {
            /** get SRv6 GSID Prefix mode */
            SHR_IF_ERR_EXIT(dnx_switch_srv6_modes_get(unit, bcmSwitchSrv6UsidPrefixBits, arg));
            break;
        }
        case bcmSwitchBfdMyDipDestination:
        {
            SHR_IF_ERR_EXIT(dnx_bfd_my_dip_destination_get(unit, (uint32 *) arg));
            break;
        }
        case bcmSwitchMplsAlternateMarkingSpecialLabel:
        {
            if (!dnx_data_mpls.general.feature_get(unit, dnx_data_mpls_general_support_alternate_marking))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Not supported bcmSwitchMplsAlternateMarkingSpecialLabel\n");
            }

            SHR_IF_ERR_EXIT(dnx_mpls_alternate_marking_special_label_get(unit, (uint32 *) arg));
            break;
        }
        case bcmSwitchMplsFlowInstructionIndicatorSpecialLabel:
        {
            SHR_IF_ERR_EXIT(dnx_mpls_flow_instrunction_indicator_label_get(unit, (uint32 *) arg));
            break;
        }
        case bcmSwitchGlobalTodMode:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_global_tod_mode_get(unit, (bcm_switch_tod_mode_t *) arg));
            break;
        }
        case bcmSwitchPFCDeadlockRecoveryAction:
        {
            SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.action.get(unit, arg));
            break;
        }
        case bcmSwitchControlOamBfdFailoverStateIgnore:
        {
            if (!dnx_data_device.general.feature_get(unit, dnx_data_device_general_protection_state_ignore))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Not supported bcmSwitchControlOamBfdFailoverStateIgnore\n");
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_oam_bfd_failover_state_ignore_get(unit, arg));
            break;
        }
        case bcmSwitchExactMatchInit:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Feature unsupported for get\n");
            break;
        }
        case bcmSwitchRangeOperator:
        {
            bcm_switch_range_operator_t range_op = bcmSwitchRangeOperatorInvalid;
            SHR_IF_ERR_EXIT(dnx_switch_control_range_operator_get(unit, &range_op));
            *arg = range_op;
            break;
        }
        case bcmSwitchSLLBDestinationNotFound:
        {
            if (dnx_data_l3.vip_ecmp.feature_get(unit, dnx_data_l3_vip_ecmp_supported))
            {
                SHR_IF_ERR_EXIT(dnx_switch_control_sllb_default_destination_get(unit, arg));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This BCM switch control type (%d) is not supported! \n", type);
            }
            break;
        }
        case bcmSwitchVIPEcmpTableSize:
        {
            if (dnx_data_l3.vip_ecmp.feature_get(unit, dnx_data_l3_vip_ecmp_supported))
            {
                SHR_IF_ERR_EXIT(dnx_switch_control_sllb_table_size_get(unit, arg));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This BCM switch control type (%d) is not supported! \n", type);
            }
            break;
        }
        case bcmSwitchVIPL3EgressIDMin:
        {
            if (dnx_data_l3.vip_ecmp.feature_get(unit, dnx_data_l3_vip_ecmp_supported))
            {
                uint32 fec_id_min;
                SHR_IF_ERR_EXIT(dnx_l3_egress_ecmp_vip_fec_id_min_get(unit, &fec_id_min));
                *arg = (int) fec_id_min;
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This BCM switch control type (%d) is not supported! \n", type);
            }
            break;
        }
        case bcmSwitchVIPL3EgressIDMax:
        {
            if (dnx_data_l3.vip_ecmp.feature_get(unit, dnx_data_l3_vip_ecmp_supported))
            {
                uint32 fec_id_max;
                SHR_IF_ERR_EXIT(dnx_l3_egress_ecmp_vip_fec_id_max_get(unit, &fec_id_max));
                *arg = (int) fec_id_max;
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This BCM switch control type (%d) is not supported! \n", type);
            }
            break;
        }
        case bcmSwitchFlexeOamAlmCollectionTimerStep:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_oam_alarm_collection_timer_step_get(unit, arg));
            break;
        }
        case bcmSwitchFlexeOamAlmCollectionStepCount:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_oam_alarm_collection_step_count_get(unit, arg));
            break;
        }
        case bcmSwitchHashMPLSExcludeReservedLabel:
        {
            SHR_IF_ERR_EXIT(dnx_mpls_special_label_as_general_label_get(unit, 0, arg));
            break;
        }
        case bcmSwitchFlexeSarCellMode:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_sar_cell_mode_get(unit, (bcm_switch_flexe_sar_cell_mode_t *) arg));
            break;
        }
        case bcmSwitchIngParseL3L4IPv4:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_parse_udp_enable_get(unit, dnxParseUdpNextHeaderIpv4, arg));
            break;
        }
        case bcmSwitchIngParseL3L4IPv6:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_parse_udp_enable_get(unit, dnxParseUdpNextHeaderIpv6, arg));
            break;
        }
        case bcmSwitchMplsEvpnEntropyEnable:
        {
            if (dnx_data_mpls.general.feature_get(unit, dnx_data_mpls_general_mpls_term_till_bos))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmSwitchMplsEvpnEntropyEnable is not supported in current device\n");
            }
            SHR_IF_ERR_EXIT(dnx_mpls_dual_homing_fl_termination_enable_get(unit, arg));
            break;
        }
        case bcmSwitchL2LearnLimitCheckStatic:
        {
            SHR_IF_ERR_EXIT(dnx_l2_learn_limit_check_static_get(unit, arg));
            break;
        }
        case bcmSwitchL2ChangeFieldsEnable:
        {
            if (!dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_separate_fwd_learn_mact))
            {
                uint32 dbal_commit_flags = 0;
                SHR_IF_ERR_EXIT(dnx_l2_static_transplant_commit_flags_get(unit, &dbal_commit_flags));
                *arg = (dbal_commit_flags == DBAL_COMMIT_FORCE) ? 1 : 0;
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmSwitchL2ChangeFieldsEnable is not supported in current device\n");
            }
            break;
        }
        case bcmSwitchOamAdditionalGalSpecialLabel:
        {
            if (dnx_data_oam.oamp.feature_get(unit, dnx_data_oam_oamp_oamp_v2) == 0)
            {
                SHR_IF_ERR_EXIT(dnx_oam_oamp_v1_additional_gal_special_label_get(unit, arg));
            }
            break;
        }
        case bcmSwitchFlexe1588RxDestMacOui:
        case bcmSwitchFlexe1588RxDestMacNonOui:
        case bcmSwitchFlexe1588RxSrcMacOui:
        case bcmSwitchFlexe1588RxSrcMacNonOui:
        case bcmSwitchFlexe1588TxDestMacOui:
        case bcmSwitchFlexe1588TxDestMacNonOui:
        case bcmSwitchFlexe1588TxSrcMacOui:
        case bcmSwitchFlexe1588TxSrcMacNonOui:
        case bcmSwitchFlexe1588OverEthRxUnicastDestMacOui:
        case bcmSwitchFlexe1588OverEthRxUnicastDestMacNonOui:
        case bcmSwitchFlexe1588OverEthTxUnicastDestMacOui:
        case bcmSwitchFlexe1588OverEthTxUnicastDestMacNonOui:
        case bcmSwitchFlexe1588OverIpv4RxUnicastDestIpHigh:
        case bcmSwitchFlexe1588OverIpv4RxUnicastDestIpLow:
        case bcmSwitchFlexe1588OverIpv4TxUnicastDestIpHigh:
        case bcmSwitchFlexe1588OverIpv4TxUnicastDestIpLow:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_1588_pkt_header_get(unit, type, arg));
            break;
        }
        case bcmSwitchFlexeOhOamPktDestMacOui:
        case bcmSwitchFlexeOhOamPktDestMacNonOui:
        case bcmSwitchFlexeOhOamPktSrcMacOui:
        case bcmSwitchFlexeOhOamPktSrcMacNonOui:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_oh_oam_pkt_mac_get(unit, type, arg));
            break;
        }
        case bcmSwitchFlexeBasOamToExtProcessorEnable:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_bas_oam_to_ext_processor_get(unit, arg));
            break;
        }
        case bcmSwitchFlexeOamBasBipRecalculationEnable:
        case bcmSwitchFlexeOamBasPeriodMismatchTriggerLosAlarm:
        {
            SHR_IF_ERR_EXIT(dnx_flexe_oam_switch_control_get(unit, type, arg));
            break;
        }
        case bcmSwitchMplsLastTermMode:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_mpls_last_term_mode_get(unit, arg));
            break;
        }
        case bcmSwitchIngressVlanEditClassNull:
            SHR_IF_ERR_EXIT(dnx_switch_control_last_ivec_fhei_size_get(unit, arg));
            break;
        case bcmSwitchMplsSpecialLabelPerPortTerminateDisable:
        {
            SHR_IF_ERR_EXIT(dnx_switch_control_per_port_special_label_termination_disable_get(unit, arg));
            break;
        }
        case bcmSwitchWideDataExtKeyMode:
            SHR_IF_ERR_EXIT(dnx_switch_wide_data_ext_key_mode_get(unit,
                                                                  (bcm_switch_wide_data_extension_key_mode_t *) arg));
            break;
        case bcmSwitchTwampStatelessModeEnable:
        {
            SHR_IF_ERR_EXIT(dnx_oam_twamp_stateless_mode_get(unit, arg));
            break;
        }
        case bcmSwitchReflectorL2IntPriority:
        {
            SHR_IF_ERR_EXIT(dnx_switch_reflector_rcy_priority_get(unit, arg));
            break;
        }
        case bcmSwitchPfcRxSvtagEnable:
        {
            SHR_IF_ERR_EXIT(dnx_switch_svtag_pfc_flow_control_mapping_get(unit, arg));
            break;
        }

        default:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "This BCM switch control type (%d) is not supported! \n", type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Verify function for bcm_dnx_switch_network_group_config_set
*/
shr_error_e
dnx_switch_network_group_config_set_verify(
    int unit,
    bcm_switch_network_group_t source_network_group_id,
    bcm_switch_network_group_config_t * config)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify config pointer is not NULL:
     */
    SHR_NULL_CHECK(config, _SHR_E_PARAM, "config");

    /*
     * Verify source_network_group_id range:
     */
    SHR_IF_ERR_EXIT(dnx_switch_network_group_id_verify(unit, TRUE, source_network_group_id));

    /*
     * Verify dest_network_group_id range:
     */
    SHR_IF_ERR_EXIT(dnx_switch_network_group_id_verify(unit, FALSE, config->dest_network_group_id));

    /*
     * Verify that no flag other then BCM_SWITCH_NETWORK_GROUP_EGRESS_PRUNE_ENABLE is set:
     */
    if (config->config_flags & (~BCM_SWITCH_NETWORK_GROUP_EGRESS_PRUNE_ENABLE))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Error - config_flags = 0x%08X, Only BCM_SWITCH_NETWORK_GROUP_EGRESS_PRUNE_ENABLE (0x%08X) is supported!!!\n",
                     config->config_flags, BCM_SWITCH_NETWORK_GROUP_EGRESS_PRUNE_ENABLE);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Set Orientation-based filtering (Split-Horizon) between two orientations.
 *
 * \param [in] unit - Relevant unit
 * \param [in] source_network_group_id - incoming orientation id.
 * \param [in] config -pointer to structure containing
 *      dest_network_group_id - outgoing orientation id.
 *      config_flags - configuration flags.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_switch_network_group_config_set(
    int unit,
    bcm_switch_network_group_t source_network_group_id,
    bcm_switch_network_group_config_t * config)
{
    uint32 entry_handle_id;
    uint32 filter_value;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_switch_network_group_config_set_verify(unit, source_network_group_id, config));

    filter_value = (_SHR_IS_FLAG_SET(config->config_flags, BCM_SWITCH_NETWORK_GROUP_EGRESS_PRUNE_ENABLE)) ? 1 : 0;

    /** Update INGRESS_SPLIT_HORIZON_FILTER/SPLIT_HORIZON_FILTER */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_SPLIT_HORIZON_FILTER, &entry_handle_id));
    for (int idx = 0; idx < 2; idx++)
    {
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_ORIENTATION, source_network_group_id);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_ORIENTATION,
                                   config->dest_network_group_id);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SPLIT_HORIZON_FILTER_ENABLE, INST_SINGLE,
                                     filter_value);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        /** Update the INGRESS_SPLIT_HORIZON_FILTER table in case ingress MC pruning actions are supported. */
        if (!dnx_data_multicast.params.feature_get(unit, dnx_data_multicast_params_mc_pruning_actions_not_supported)
            && idx == 0)
        {
        }
        else
        {
            break;
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Verify function for bcm_dnx_switch_network_group_config_get
*/
shr_error_e
dnx_switch_network_group_config_get_verify(
    int unit,
    bcm_switch_network_group_t source_network_group_id,
    bcm_switch_network_group_config_t * config)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify config pointer is not NULL:
     */
    SHR_NULL_CHECK(config, _SHR_E_PARAM, "config");

    /*
     * Verify source_network_group_id range:
     */
    SHR_IF_ERR_EXIT(dnx_switch_network_group_id_verify(unit, TRUE, source_network_group_id));

    /*
     * Verify dest_network_group_id range:
     */
    SHR_IF_ERR_EXIT(dnx_switch_network_group_id_verify(unit, FALSE, config->dest_network_group_id));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Get the Orientation-based filtering (Split-Horizon) between two orientations.
 *
 * \param [in] unit - Relevant unit
 * \param [in] source_network_group_id - incoming orientation id.
 * \param [in,out] config -pointer to structure containing -
 *      [in] dest_network_group_id - outgoing orientation id.
 *      [out] config_flags - configuration flags.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_switch_network_group_config_get(
    int unit,
    bcm_switch_network_group_t source_network_group_id,
    bcm_switch_network_group_config_t * config)
{
    uint32 entry_handle_id;
    uint32 filter_value;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_switch_network_group_config_get_verify(unit, source_network_group_id, config));

    /*
     * Get Filter value from HW:
     */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_SPLIT_HORIZON_FILTER, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_ORIENTATION, source_network_group_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_ORIENTATION, config->dest_network_group_id);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_SPLIT_HORIZON_FILTER_ENABLE, INST_SINGLE, &filter_value));

    if (filter_value == 1)
    {
        config->config_flags |= BCM_SWITCH_NETWORK_GROUP_EGRESS_PRUNE_ENABLE;
    }
    else
    {
        config->config_flags &= ~BCM_SWITCH_NETWORK_GROUP_EGRESS_PRUNE_ENABLE;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

int
bcm_dnx_switch_rov_get(
    int unit,
    uint32 flags,
    uint32 *rov)
{
    uint32 entry_handle_id, cores_group;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(rov, _SHR_E_PARAM, "rov");
    cores_group = 0;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_BOND_AVS_STATUS, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_BLOCK_INDEX, cores_group);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_AVS_STATUS, INST_SINGLE, &rov[cores_group]);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*   API gets temperature info for PVT monitors
*   modes
* \par DIRECT INPUT:
*   \param [in] unit - unit ID
*   \param [in] temperature_max - Maximal number of acceptable temperature sensors
*   \param [out] temperature_array - Pointer to array to be loaded by this procedure. Each
*        element contains current temperature and peak temperature
*   \param [out] temperature_count  - the number of sensors (and, therefore, the number of valid
*        elements on temperature_array).
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   int -
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   *
* \see
*   * None
*/
int
bcm_dnx_switch_temperature_monitor_get(
    int unit,
    int temperature_max,
    bcm_switch_temperature_monitor_t * temperature_array,
    int *temperature_count)
{
    int nof_pvt_mon;
    int pvt_base, pvt_factor;
    uint32 entry_handle_id;
    uint16 current[DNX_DATA_MAX_PVT_GENERAL_NOF_PVT_MONITORS];
    uint16 peak[DNX_DATA_MAX_PVT_GENERAL_NOF_PVT_MONITORS];
    int i;
    uint16 current_min[DNX_DATA_MAX_PVT_GENERAL_NOF_PVT_MONITORS];
    uint16 current_max[DNX_DATA_MAX_PVT_GENERAL_NOF_PVT_MONITORS];
    uint16 current_tmp[DNX_DATA_MAX_PVT_GENERAL_NOF_PVT_MONITORS];
    soc_timeout_t to;
    int iter, locked = 0;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(temperature_array, _SHR_E_PARAM, "temperature_array");
    SHR_NULL_CHECK(temperature_count, _SHR_E_PARAM, "temperature_count");

    if (dnx_data_pvt.vtmon.feature_get(unit, dnx_data_pvt_vtmon_remote_temp_sensors_supported))
    {
    }
    else
    {
        nof_pvt_mon = dnx_data_pvt.general.nof_pvt_monitors_get(unit);
        pvt_base = dnx_data_pvt.general.pvt_base_get(unit);
        pvt_factor = dnx_data_pvt.general.pvt_factor_get(unit);

        if (temperature_max < nof_pvt_mon)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Array size should be equal to or larger than %d.\n", nof_pvt_mon);
        }

        if (dnx_data_pvt.general.feature_get(unit, dnx_data_pvt_general_pvt_lock_support))
        {
            SHR_IF_ERR_EXIT(dnx_pvt_mon_lock(unit, 1));
            locked = 1;
        }
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PVT_TEMPERATURE_MONITOR, &entry_handle_id));
        for (i = 0; i < nof_pvt_mon; i++)
        {
            /** check if value out of range */
            soc_timeout_init(&to, 100000, 0);
            while (1)
            {
                dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_PEAK_THERMAL_DATA, i, &peak[i]);
                dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_THERMAL_DATA, i, &current[i]);
                /** Performing the action */
                SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

                if (locked)
                {
                    /** PVTMON support lock mechanism, get temperature once */
                    break;
                }
                /** current and peak get first value */
                current_min[i] = current_max[i] = current[i];
                for (iter = 0; iter < 4; iter++)
                {
                    dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_THERMAL_DATA, i, &current_tmp[i]);
                    /** Performing the action */
                    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
                    if (current_tmp[i] < current_min[i])
                    {
                        current_min[i] = current_tmp[i];
                    }
                    if (current_tmp[i] > current_max[i])
                    {
                        current_max[i] = current_tmp[i];
                    }
                }

                /** different should be < 5 oC(50 * 0.1 oC)*/
                if ((current_max[i] - current_min[i]) * pvt_factor < 50 * 10000)
                {
                    /** get normal PVT value */
                    break;
                }
                if (soc_timeout_check(&to))
                {
                    SHR_IF_ERR_EXIT(_SHR_E_TIMEOUT);
                }
            }
        }

        for (i = 0; i < nof_pvt_mon; i++)
        {
            /*
             * curr [0.1 C] = (pvt_base - curr * pvt_factor)/10000
             */
            temperature_array[i].curr = (pvt_base - current[i] * pvt_factor) / 10000;
            /*
             * peak [0.1 C] = (pvt_base - curr * peak)/10000
             */
            temperature_array[i].peak = (pvt_base - peak[i] * pvt_factor) / 10000;
        }

        *temperature_count = nof_pvt_mon;

        if (locked)
        {
            dnx_pvt_mon_lock(unit, 0);
            locked = 0;
        }

        /*
         * Clear Peak
         */
        if (dnx_data_pvt.general.feature_get(unit, dnx_data_pvt_general_pvt_peak_clear_support))
        {
            SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_PVT_MON_ENABLE, entry_handle_id));
            for (i = 0; i < nof_pvt_mon; i++)
            {
                dbal_entry_value_field16_set(unit, entry_handle_id, DBAL_FIELD_PVT_MON_CONTROL_PEAK_CLEAR, i, 1);
            }
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            sal_usleep(1);

            SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_PVT_MON_ENABLE, entry_handle_id));
            for (i = 0; i < nof_pvt_mon; i++)
            {
                dbal_entry_value_field16_set(unit, entry_handle_id, DBAL_FIELD_PVT_MON_CONTROL_PEAK_CLEAR, i, 0);
            }
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }
    }

exit:
    if (locked)
    {
        dnx_pvt_mon_lock(unit, 0);
    }
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief Get l3 protocol group for multiple my mac (vrrp)
 *
 * \param [in] unit - Relevant unit
 * \param [out] group_members - combination (flags) of l3 protocols (can be either input or output).
 * \param [out] group_id - group ID (can be either input or output)
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_l3_protocol_group_get(
    int unit,
    uint32 *group_members,
    bcm_l3_protocol_group_id_t * group_id)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_IF_ERR_EXIT(dnx_l3_vrrp_protocol_group_get(unit, group_members, group_id));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief Set l3 protocol group for multiple my mac (vrrp)
 *
 * \param [in] unit - Relevant unit
 * \param [in] group_members - combination (flags) of l3 protocols.
 * \param [in] group_id - group ID to set
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_l3_protocol_group_set(
    int unit,
    uint32 group_members,
    bcm_l3_protocol_group_id_t group_id)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_IF_ERR_EXIT(dnx_l3_vrrp_protocol_group_set(unit, group_members, group_id));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/***************************************************************/
/***************************************************************/
#define DNX_SWITCH_LOCK_TAKE
#define DNX_SWITCH_LOCK_RELEASE
/*
 * Switch Event Function
 *
 */

/*
 * Function:
 *    bcm_dnx_switch_event_register
 * Description:
 *    Registers a call back function for switch critical events
 * Parameters:
 *    unit        - Device unit number
 *    cb          - The desired call back function to register for critical events.
 *    userdata    - Pointer to any user data to carry on.
 * Returns:
 *      _SHR_E_xxx
 * Notes:
 *
 *    Several call back functions could be registered, they all will be called upon
 *    critical event. If registered callback is called it is adviced to log the
 *    information and reset the chip.
 *    Same call back function with different userdata is allowed to be registered.
 */
int
bcm_dnx_switch_event_register(
    int unit,
    bcm_switch_event_cb_t cb,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NO_SUPPORT_BEGIN(unit);

    DNX_SWITCH_LOCK_TAKE;
    SHR_IF_ERR_EXIT(dnx_drv_soc_event_register(unit, cb, userdata));

exit:
    DNX_SWITCH_LOCK_RELEASE;
    DNX_ERR_RECOVERY_NO_SUPPORT_END(unit);
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *    bcm_dnx_switch_event_unregister
 * Description:
 *    Unregisters a call back function for switch critical events
 * Parameters:
 *    unit        - Device unit number
 *    cb          - The desired call back function to unregister for critical events.
 *    userdata    - Pointer to any user data associated with a call back function
 * Returns:
 *      _SHR_E_xxx
 * Notes:
 *
 *  If userdata = NULL then all matched call back functions will be unregistered,
 */
int
bcm_dnx_switch_event_unregister(
    int unit,
    bcm_switch_event_cb_t cb,
    void *userdata)
{
    int rc = _SHR_E_NONE;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NO_SUPPORT_BEGIN(unit);

    DNX_SWITCH_LOCK_TAKE;
    rc = dnx_drv_soc_event_unregister(unit, cb, userdata);
    SHR_IF_ERR_EXIT(rc);

exit:
    DNX_SWITCH_LOCK_RELEASE;
    DNX_ERR_RECOVERY_NO_SUPPORT_END(unit);
    SHR_FUNC_EXIT;
}

static int
dnx_switcht_event_blk_all_intr_enable_set(
    int unit,
    int intr_id,
    soc_interrupt_db_t * interrupts,
    int enable)
{
    int rc = _SHR_E_NONE;
    int blk, is_valid, intr_port, is_enable;
    soc_block_info_t *bi;
    uint32 old_intr_status[DNX_SWITCH_INTR_BLOCK_WIDTH];

    SHR_FUNC_INIT_VARS(unit);

    /*
     * backup old intr enable status
     */
    sal_memset(old_intr_status, 0, sizeof(old_intr_status));

    for (blk = 0;; blk++)
    {
        int *soc_block_type_p;
        uint8 *block_valid_p;

        SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_port_block_address_get(unit, TYPE, blk, &soc_block_type_p));
        if (*soc_block_type_p < 0)
        {
            break;
        }

        SHR_IF_ERR_EXIT(soc_info_uint8_address_get(unit, BLOCK_VALID, &block_valid_p));
        block_valid_p = &(block_valid_p[blk]);
        if (!(*block_valid_p))
        {
            continue;
        }

        SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_block_address_get(unit, blk, (void **) &bi));
        SHR_IF_ERR_EXIT(soc_interrupt_is_valid(unit, bi, &(interrupts[intr_id]), &is_valid));
        if (is_valid)
        {
            intr_port = soc_interrupt_get_intr_port_from_index(unit, intr_id, bi->number);
            SHR_IF_ERR_EXIT(soc_interrupt_is_enabled(unit, intr_port, &(interrupts[intr_id]), &is_enable));
            if (is_enable)
            {
                SHR_BITSET(old_intr_status, blk);
            }
        }
    }

    /*
     * Set per interrupt
     */

    for (blk = 0;; blk++)
    {
        int *soc_block_type_p;
        uint8 *block_valid_p;

        SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_port_block_address_get(unit, TYPE, blk, &soc_block_type_p));
        if (*soc_block_type_p < 0)
        {
            break;
        }

        SHR_IF_ERR_EXIT(soc_info_uint8_address_get(unit, BLOCK_VALID, &block_valid_p));
        block_valid_p = &(block_valid_p[blk]);
        if (!(*block_valid_p))
        {
            continue;
        }

        SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_block_address_get(unit, blk, (void **) &bi));
        SHR_IF_ERR_EXIT(soc_interrupt_is_valid(unit, bi, &(interrupts[intr_id]), &is_valid));
        if (is_valid)
        {
            intr_port = soc_interrupt_get_intr_port_from_index(unit, intr_id, bi->number);
            rc = soc_interrupt_is_enabled(unit, intr_port, &(interrupts[intr_id]), &is_enable);
            SHR_IF_ERR_EXIT(rc);
            if (enable)
            {
                rc = soc_dnx_interrupt_enable(unit, intr_id, intr_port, &(interrupts[intr_id]));
            }
            else
            {
                rc = soc_interrupt_disable(unit, intr_port, &(interrupts[intr_id]));
            }
            SHR_IF_ERR_EXIT(rc);
        }
    }

exit:
    if (rc != _SHR_E_NONE)
    {
        /*
         * error recorvery with saved intr status
         */

        for (blk = 0;; blk++)
        {
            int *soc_block_type_p;
            uint8 *block_valid_p;

            SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_port_block_address_get(unit, TYPE, blk, &soc_block_type_p));
            if (*soc_block_type_p < 0)
            {
                break;
            }

            SHR_IF_ERR_EXIT(soc_info_uint8_address_get(unit, BLOCK_VALID, &block_valid_p));
            block_valid_p = &(block_valid_p[blk]);
            if (!(*block_valid_p))
            {
                continue;
            }

            SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_block_address_get(unit, blk, (void **) &bi));
            rc = soc_interrupt_is_valid(unit, bi, &(interrupts[intr_id]), &is_valid);
            if ((rc == _SHR_E_NONE) && (is_valid))
            {
                intr_port = soc_interrupt_get_intr_port_from_index(unit, intr_id, bi->number);
                if (SHR_BITGET(old_intr_status, blk))
                {
                    rc = soc_dnx_interrupt_enable(unit, intr_id, intr_port, &(interrupts[intr_id]));
                }
                else
                {
                    rc = soc_interrupt_disable(unit, intr_port, &(interrupts[intr_id]));
                }
                SHR_IF_ERR_CONT(rc);
            }
        }
    }
    SHR_FUNC_EXIT;
}

#ifdef BCM_ACCESS_SUPPORT
static int
access_switch_event_intr_sw_state_storms_set(
    int unit,
    soc_interrupt_db_t * interrupts,
    int event_id,
    bcm_switch_event_control_action_t action,
    uint32 value)
{
    access_runtime_info_t *runtime_info = access_runtime_info_get(unit);        /* Access information for the device */
    const access_device_type_info_t *device_info = runtime_info->device_type_info;
    access_block_instance_num_t inst = 0, nof_instances;
    access_local_regmem_id_t local_reg;
    uint32 *switch_event_nominal_storm_p;
    SHR_FUNC_INIT_VARS(unit);
    if (event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
    {
        switch (action)
        {
            case bcmSwitchEventStormTimedCount:
            {
                SHR_IF_ERR_EXIT(access_interrupt_storm_timed_count_set_all(unit, value));
                break;
            }
            case bcmSwitchEventStormTimedPeriod:
            {
                SHR_IF_ERR_EXIT(access_interrupt_storm_timed_period_set_all(unit, value));
                break;
            }
            case bcmSwitchEventStormNominal:
            {
                /** Warm boot buffer updating */
                SHR_IF_ERR_EXIT(intr_db.storm_nominal.set(unit, value));
                SHR_IF_ERR_EXIT(soc_control_element_address_get
                                (unit, SWITCH_EVENT_NOMINAL_STORM, (void **) (&switch_event_nominal_storm_p)));
                *switch_event_nominal_storm_p = value;
                SHR_IF_ERR_EXIT(access_interrupt_storm_nominal_clear_all(unit));
                break;
            }
            default:
            {
                SHR_IF_ERR_EXIT(_SHR_E_PARAM);
            }
        }
    }
    else
    {
        local_reg = interrupts[event_id].reg;
        nof_instances = device_info->blocks[device_info->local_regs[local_reg].local_block_id].nof_instances;
        switch (action)
        {
            case bcmSwitchEventStormTimedCount:
            {
                SHR_IF_ERR_EXIT(intr_db.storm_timed_count.set(unit, event_id, value));
                for (inst = 0; inst < nof_instances; inst++)
                {
                    (interrupts[event_id].storm_detection_occurrences)[inst] = 0;
                }
                break;
            }
            case bcmSwitchEventStormTimedPeriod:
            {
                SHR_IF_ERR_EXIT(intr_db.storm_timed_period.set(unit, event_id, value));
                for (inst = 0; inst < nof_instances; inst++)
                {
                    (interrupts[event_id].storm_detection_start_time)[inst] = 0;
                }
                break;
            }
            case bcmSwitchEventStormNominal:
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid nominal storm detection parameter (event_id)");
                break;
            }
            default:
            {
                SHR_IF_ERR_EXIT(_SHR_E_PARAM);
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}
#endif

static int
dnx_switch_event_intr_sw_state_storms_set(
    int unit,
    soc_interrupt_db_t * interrupts,
    int event_id,
    bcm_switch_event_control_action_t action,
    uint32 value)
{
    int inter, nof_interrupts;
    int start_intr, end_intr;
    int blk;
    soc_block_info_t *bi = NULL;

    SHR_FUNC_INIT_VARS(unit);

#ifdef BCM_ACCESS_SUPPORT
    if (access_new_interrupt_available(unit))
    {
        return access_switch_event_intr_sw_state_storms_set(unit, interrupts, event_id, action, value);
    }
#endif
    SHR_IF_ERR_EXIT(soc_nof_interrupts(unit, &nof_interrupts));
    if (event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
    {
        start_intr = 0;
        end_intr = nof_interrupts - 1;
    }
    else
    {
        if ((event_id >= nof_interrupts) || (event_id < 0))
        {
            SHR_IF_ERR_EXIT(_SHR_E_PARAM);
        }
        start_intr = event_id;
        end_intr = event_id;
    }

    /*
     * update sw_state
     */
    if (action == bcmSwitchEventStormNominal)
    {
        uint32 *switch_event_nominal_storm_p;

        if (event_id != BCM_SWITCH_EVENT_CONTROL_ALL)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid nominal storm detection parameter (event_id)");
        }
        /*
         * Warm boot buffer updating
         */
        SHR_IF_ERR_EXIT(intr_db.storm_nominal.set(unit, value));
        SHR_IF_ERR_EXIT(soc_control_element_address_get
                        (unit, SWITCH_EVENT_NOMINAL_STORM, (void **) (&switch_event_nominal_storm_p)));
        *switch_event_nominal_storm_p = value;
    }
    else
    {
        for (inter = start_intr; inter <= end_intr; inter++)
        {
            if (action == bcmSwitchEventStormTimedCount)
            {
                SHR_IF_ERR_EXIT(intr_db.storm_timed_count.set(unit, inter, value));
            }
            else if (action == bcmSwitchEventStormTimedPeriod)
            {
                SHR_IF_ERR_EXIT(intr_db.storm_timed_period.set(unit, inter, value));
            }
            else
            {
                SHR_IF_ERR_EXIT(_SHR_E_PARAM);
            }
        }
    }

    /*
     * clear storm time status at intr DB
     */
    for (inter = start_intr; inter <= end_intr; inter++)
    {
        soc_reg_info_t *soc_reg_info_p;

        if (!dnx_drv_soc_reg_is_valid(unit, interrupts[inter].reg))
        {
            continue;
        }
        soc_reg_info_p = dnx_drv_reg_info_ptr_get(unit, (int) (interrupts[inter].reg));
        for (blk = 0;; blk++)
        {
            int *soc_block_type_p;
            uint8 *block_valid_p;

            SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_port_block_address_get(unit, TYPE, blk, &soc_block_type_p));
            if (*soc_block_type_p < 0)
            {
                break;
            }
            SHR_IF_ERR_EXIT(soc_info_uint8_address_get(unit, BLOCK_VALID, &block_valid_p));
            block_valid_p = &(block_valid_p[blk]);

            if (*block_valid_p && dnx_drv_soc_block_is_type(unit, blk, soc_reg_info_p->block))
            {

                SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_block_address_get(unit, blk, (void **) &bi));
                switch (action)
                {
                    case bcmSwitchEventStormTimedCount:
                    {
                        (interrupts[inter].storm_detection_occurrences)[bi->number] = 0x0;
                        break;
                    }
                    case bcmSwitchEventStormTimedPeriod:
                    {
                        (interrupts[inter].storm_detection_start_time)[bi->number] = 0;
                        break;
                    }
                    case bcmSwitchEventStormNominal:
                    {
                        (interrupts[inter].storm_nominal_count)[bi->number] = 0x0;
                        (interrupts[inter].storm_detection_occurrences)[bi->number] = 0x0;
                        break;
                    }
                    default:
                    {
                        SHR_IF_ERR_EXIT(_SHR_E_PARAM);
                    }
                }
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static int
dnx_switch_event_flags_value_update(
    int unit,
    bcm_switch_event_control_action_t action,
    uint32 value,
    uint32 *intr_flags)
{
    uint32 flags = *intr_flags;

    SHR_FUNC_INIT_VARS(unit);

    switch (action)
    {
        case bcmSwitchEventLog:
        {
            if (value == 0)
            {
                SHR_BITCLR(&flags, SOC_INTERRUPT_DB_FLAGS_PRINT_ENABLE);
            }
            else
            {
                SHR_BITSET(&flags, SOC_INTERRUPT_DB_FLAGS_PRINT_ENABLE);
            }
            break;
        }
        case bcmSwitchEventCorrActOverride:
        {
            /*
             * Value - 0 : Only bcm callback will be called for this interrupt.
             * Value - 1 : Only user callback will be called for this interrupt. At this mode
             *             BCM driver will only print the interrupt information for logging.
             * Value - 2 : User call back will be called immediately after bcm callback.
             */
            if (value == 2)
            {
                flags |= SOC_INTERRUPT_DB_FLAGS_BCM_AND_USR_CB;
            }
            else
            {
                flags &= ~SOC_INTERRUPT_DB_FLAGS_BCM_AND_USR_CB;
            }
            if (value == 0)
            {
                SHR_BITCLR(&flags, SOC_INTERRUPT_DB_FLAGS_CORR_ACT_OVERRIDE_ENABLE);
            }
            else
            {
                SHR_BITSET(&flags, SOC_INTERRUPT_DB_FLAGS_CORR_ACT_OVERRIDE_ENABLE);
            }
            break;
        }
        case bcmSwitchEventPriority:
        {
            if (value > SOC_INTERRUPT_DB_FLAGS_PRIORITY_MAX_VAL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Priority value is out of range");
            }
            SHR_BITCOPY_RANGE(&flags, SOC_INTERRUPT_DB_FLAGS_PRIORITY_BITS_LSB, &value, 0,
                              SOC_INTERRUPT_DB_FLAGS_PRIORITY_BITS_LEN);
            break;
        }
        case bcmSwitchEventUnmaskAndClearDisable:
        {
            if (value == 0)
            {
                SHR_BITCLR(&flags, SOC_INTERRUPT_DB_FLAGS_UNMASK_AND_CLEAR_DISABLE_BITS);
            }
            else
            {
                SHR_BITSET(&flags, SOC_INTERRUPT_DB_FLAGS_UNMASK_AND_CLEAR_DISABLE_BITS);
            }
            break;
        }
        case bcmSwitchEventForceUnmask:
        {
            if (value == 0)
            {
                SHR_BITCLR(&flags, SOC_INTERRUPT_DB_FLAGS_FORCE_UNMASK_BITS);
            }
            else
            {
                SHR_BITSET(&flags, SOC_INTERRUPT_DB_FLAGS_FORCE_UNMASK_BITS);
            }
            break;
        }
        default:
        {
            SHR_IF_ERR_EXIT(_SHR_E_PARAM);
        }
    }
    *intr_flags = flags;

exit:
    SHR_FUNC_EXIT;
}

static int
dnx_switch_event_intr_sw_state_flags_set(
    int unit,
    int event_id,
    bcm_switch_event_control_action_t action,
    uint32 value)
{
    int inter, nof_interrupts;
    int start_intr, end_intr;
    uint32 flags;

    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(soc_nof_interrupts(unit, &nof_interrupts));
    if (event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
    {
        start_intr = 0;
        end_intr = nof_interrupts - 1;
    }
    else
    {
        if ((event_id >= nof_interrupts) || (event_id < 0))
        {
            SHR_IF_ERR_EXIT(_SHR_E_PARAM);
        }
        start_intr = event_id;
        end_intr = event_id;
    }

    for (inter = start_intr; inter <= end_intr; inter++)
    {
        SHR_IF_ERR_EXIT(soc_interrupt_flags_get(unit, inter, &flags));
        SHR_IF_ERR_EXIT(dnx_switch_event_flags_value_update(unit, action, value, &flags));
        SHR_IF_ERR_EXIT(intr_db.flags.set(unit, inter, flags));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *    bcm_dnx_switch_event_control_set
 * Description:
 *    Set event control
 * Parameters:
 *    unit        - Device unit number
 *    type        - Event action.
 *    value       - Event value
 * Returns:
 *      _SHR_E_xxx
 */
int
bcm_dnx_switch_event_control_set(
    int unit,
    bcm_switch_event_t switch_event,
    bcm_switch_event_control_t type,
    uint32 value)
{
    int rc = _SHR_E_NONE, nof_interrupts;
    soc_interrupt_db_t *interrupts;
    int inter = 0;
    soc_block_info_t *bi;
    int bi_index = 0, inf_index = type.index, port;
    int is_valid;
    soc_block_types_t block_types;
    soc_interrupt_t **interrupts_info_p;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NO_SUPPORT_BEGIN(unit);
    DNX_SWITCH_LOCK_TAKE;

    if (switch_event != BCM_SWITCH_EVENT_DEVICE_INTERRUPT)
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "supports only interrupts event");
    }

    SHR_IF_ERR_EXIT(soc_control_element_address_get(unit, INTERRUPTS_INFO, (void **) (&interrupts_info_p)));
    if (*interrupts_info_p == NULL)
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "No interrupts for device");
    }
    interrupts = (*interrupts_info_p)->interrupt_db_info;
    if (NULL == interrupts)
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "No interrupts for device");
    }

    /*
     * verify interrupt id
     */
    rc = soc_nof_interrupts(unit, &nof_interrupts);
    SHR_IF_ERR_EXIT(rc);

    if (type.event_id != BCM_SWITCH_EVENT_CONTROL_ALL)
    {
        if (type.event_id >= nof_interrupts || type.event_id < 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid interrupt");
        }

#ifdef BCM_ACCESS_SUPPORT
        if (access_new_interrupt_available(unit))
        {
            access_runtime_info_t *runtime_info = access_runtime_info_get(unit);
            const access_device_type_info_t *device_info = runtime_info->device_type_info;
            access_local_regmem_id_t local_reg = interrupts[type.event_id].reg;
            if (ACCESS_INVALID_LOCAL_REGMEM_ID == local_reg)
            {
                SHR_ERR_EXIT(_SHR_E_INTERNAL, "Invalid interrupt register for the device");
            }
            /** Verify block index */
            if (type.index != BCM_CORE_ALL)
            {
                if ((type.index < 0) ||
                    (type.index >=
                     device_info->blocks[device_info->local_regs[local_reg].local_block_id].nof_instances))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported block instance");
                }
            }
        }
        else
#endif
        {
            /** verify block instance */
            if (!dnx_drv_soc_reg_is_valid(unit, interrupts[type.event_id].reg))
            {
                SHR_ERR_EXIT(_SHR_E_INTERNAL, "Invalid interrupt register for the device");
            }
            /** Verify block index */
            if (type.index != BCM_CORE_ALL)
            {
                soc_reg_info_t *soc_reg_info_p;

                soc_reg_info_p = dnx_drv_reg_info_ptr_get(unit, (int) (interrupts[type.event_id].reg));
                block_types = soc_reg_info_p->block;

                rc = dnx_drv_soc_is_valid_block_instance(unit, block_types, type.index, &is_valid);
                SHR_IF_ERR_EXIT(rc);
                if (!is_valid)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported block instance");
                }

                inf_index = soc_interrupt_get_block_index_from_port(unit, type.event_id, type.index);
                if (inf_index < 0)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported block instance");
                }
            }
        }
    }

    /*
     * switch case for all
     */
    switch (type.action)
    {
        case bcmSwitchEventMask:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                rc = soc_dnxc_interrupt_all_enable_set(unit, (value ? 0 : 1));
                SHR_IF_ERR_EXIT(rc);
            }
            else
            {
                /*
                 * Set per interrupt
                 */

#ifdef BCM_ACCESS_SUPPORT
                if (access_new_interrupt_available(unit))
                {
                    if (type.index == BCM_CORE_ALL)
                    {
                        rc = access_interrupt_enable_all_instances(unit, &interrupts[type.event_id], value ? 0 : 1);
                    }
                    else
                    {
                        rc = access_interrupt_update(unit, type.index, &interrupts[type.event_id], value ? 0 : 1);
                    }
                    SHR_IF_ERR_EXIT(rc);
                    break;
                }
#endif
                if (type.index == BCM_CORE_ALL)
                {
                    if (value)
                    {
                        rc = dnx_switcht_event_blk_all_intr_enable_set(unit, type.event_id, interrupts, 0);
                    }
                    else
                    {
                        rc = dnx_switcht_event_blk_all_intr_enable_set(unit, type.event_id, interrupts, 1);
                    }
                }
                else
                {
                    if (value)
                    {
                        rc = soc_interrupt_disable(unit, type.index, &(interrupts[type.event_id]));
                    }
                    else
                    {
                        rc = soc_dnx_interrupt_enable(unit, type.event_id, type.index, &(interrupts[type.event_id]));
                    }
                }
                SHR_IF_ERR_EXIT(rc);
            }
            break;
        }
        case bcmSwitchEventForce:
        {
#ifdef BCM_ACCESS_SUPPORT
            if (access_new_interrupt_available(unit))
            {
                if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
                {
                    rc = access_interrupt_force_all(unit, value ? 0 : 1);
                }
                else
                {
                    rc = access_interrupt_force(unit, type.index, &(interrupts[type.event_id]), value ? 0 : 1);
                }
                SHR_IF_ERR_EXIT(rc);
                break;
            }
#endif
            /** Set/clear per interrupt */
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                for (inter = 0; inter < nof_interrupts; inter++)
                {
                    for (bi_index = 0;; bi_index++)
                    {
                        int *soc_block_type_p;
                        uint8 *block_valid_p;

                        SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_port_block_address_get
                                        (unit, TYPE, bi_index, &soc_block_type_p));
                        if (*soc_block_type_p < 0)
                        {
                            break;
                        }

                        SHR_IF_ERR_EXIT(soc_info_uint8_address_get(unit, BLOCK_VALID, &block_valid_p));
                        block_valid_p = &(block_valid_p[bi_index]);
                        if (!*block_valid_p)
                        {
                            continue;
                        }

                        SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_block_address_get(unit, bi_index, (void **) &bi));
                        rc = soc_interrupt_is_valid(unit, bi, &(interrupts[inter]), &is_valid);
                        SHR_IF_ERR_EXIT(rc);
                        if (is_valid)
                        {
                            port = soc_interrupt_get_intr_port_from_index(unit, inter, bi->number);
                            SHR_IF_ERR_EXIT(soc_interrupt_force(unit, port, &(interrupts[inter]), 1 - value));
                        }
                    }
                }
            }
            else
            {
                 /* coverity[negative_returns:FALSE]  */
                rc = soc_interrupt_force(unit, type.index, &(interrupts[type.event_id]), 1 - value);
                SHR_IF_ERR_EXIT(rc);
            }
            break;
        }
        case bcmSwitchEventClear:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                if (value)
                {
                    rc = soc_interrupt_clear_all(unit, 0);
                    SHR_IF_ERR_EXIT(rc);
                }
                else
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid event clear parameter");
                }
            }
            else
            {
                /*
                 * Set per interrupt
                 */
                if (value)
                {
                    if (NULL == interrupts[type.event_id].interrupt_clear)
                    {
                        if (interrupts[type.event_id].vector_id == 0)
                        {
                            SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                                         "Interrupt not cleared, NULL pointer of interrupt_clear, no vector_id");
                        }
                        else
                        {
                            LOG_WARN(BSL_LS_BCM_SWITCH, (BSL_META_U(unit,
                                                                    "Warning: call to interrupt clear for vector pointer, nothing done\n")));
                        }
                    }
                    else
                    {
                        rc = interrupts[type.event_id].interrupt_clear(unit, type.index, type.event_id);
                        SHR_IF_ERR_EXIT(rc);
                    }
                }
                else
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid event clear parameter");
                }
            }
            break;
        }
        case bcmSwitchEventRead:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported event control");
            break;
        }
        case bcmSwitchEventStat:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                if (value)
                {
#ifdef BCM_ACCESS_SUPPORT
                    if (access_new_interrupt_available(unit))
                    {
                        SHR_IF_ERR_EXIT(access_interrupt_clear_stat_all(unit));
                    }
                    else
#endif
                        for (inter = 0; inter < nof_interrupts; inter++)
                        {
                            for (bi_index = 0;; bi_index++)
                            {
                                int *soc_block_type_p;
                                uint8 *block_valid_p;

                                SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_port_block_address_get
                                                (unit, TYPE, bi_index, &soc_block_type_p));
                                if (*soc_block_type_p < 0)
                                {
                                    break;
                                }

                                SHR_IF_ERR_EXIT(soc_info_uint8_address_get(unit, BLOCK_VALID, &block_valid_p));
                                block_valid_p = &(block_valid_p[bi_index]);
                                if (!*block_valid_p)
                                {
                                    continue;
                                }
                                SHR_IF_ERR_EXIT(dnx_drv_soc_block_info_block_address_get
                                                (unit, bi_index, (void **) &bi));
                                SHR_IF_ERR_EXIT(soc_interrupt_is_valid(unit, bi, &(interrupts[inter]), &is_valid));
                                if (is_valid)
                                {
                                    (interrupts[inter].statistics_count)[bi->number] = 0x0;
                                }
                            }
                        }
                }
                else
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid statistics parameter value");
                }
            }
            else
            {
                (interrupts[type.event_id].statistics_count)[inf_index] = 0x0;
            }
            break;
        }

        case bcmSwitchEventStormTimedCount:
        case bcmSwitchEventStormTimedPeriod:
        case bcmSwitchEventStormNominal:
        {
            rc = dnx_switch_event_intr_sw_state_storms_set(unit, interrupts, type.event_id, type.action, value);
            SHR_IF_ERR_EXIT(rc);
            break;
        }

        case bcmSwitchEventLog:
        case bcmSwitchEventCorrActOverride:
        case bcmSwitchEventPriority:
        case bcmSwitchEventUnmaskAndClearDisable:
        case bcmSwitchEventForceUnmask:
        {
            rc = dnx_switch_event_intr_sw_state_flags_set(unit, type.event_id, type.action, value);
            SHR_IF_ERR_EXIT(rc);
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported control");
            break;
        }
    }

exit:
    DNX_SWITCH_LOCK_RELEASE;
    DNX_ERR_RECOVERY_NO_SUPPORT_END(unit);
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *    bcm_dnx_switch_event_control_get
 * Description:
 *    Get event control
 * Parameters:
 *    unit        - Device unit number
 *  type        - Event action.
 *  value       - Event value
 * Returns:
 *      _SHR_E_xxx
 */
int
bcm_dnx_switch_event_control_get(
    int unit,
    bcm_switch_event_t switch_event,
    bcm_switch_event_control_t type,
    uint32 *value)
{
    int rc = _SHR_E_NONE, nof_interrupts;
    soc_interrupt_db_t *interrupts;
    int inter_get;
    int is_enable;
    soc_block_types_t block_types;
    int is_valid;
    int inf_index = type.index;
    soc_interrupt_t **interrupts_info_p;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NO_SUPPORT_BEGIN(unit);
    SHR_NULL_CHECK(value, _SHR_E_PARAM, "value");
    DNX_SWITCH_LOCK_TAKE;

    if (switch_event != BCM_SWITCH_EVENT_DEVICE_INTERRUPT)
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "supports only interrupts event");
    }
    SHR_IF_ERR_EXIT(soc_control_element_address_get(unit, INTERRUPTS_INFO, (void **) (&interrupts_info_p)));
    interrupts = (*interrupts_info_p)->interrupt_db_info;
    if (NULL == interrupts)
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "No interrupts for device");
    }

    rc = soc_nof_interrupts(unit, &nof_interrupts);
    SHR_IF_ERR_EXIT(rc);

    if (type.event_id != BCM_SWITCH_EVENT_CONTROL_ALL)
    {
        soc_reg_info_t *soc_reg_info_p;

        if (type.event_id >= nof_interrupts || type.event_id < 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid interrupt");
        }
#ifdef BCM_ACCESS_SUPPORT
        if (access_new_interrupt_available(unit))
        {
            access_runtime_info_t *runtime_info = access_runtime_info_get(unit);
            const access_device_type_info_t *device_info = runtime_info->device_type_info;
            access_local_regmem_id_t local_reg = interrupts[type.event_id].reg;
            if (ACCESS_INVALID_LOCAL_REGMEM_ID == local_reg)
            {
                SHR_ERR_EXIT(_SHR_E_INTERNAL, "Invalid interrupt register for the device");
            }
            /** Verify block index */
            if (type.index != BCM_CORE_ALL)
            {
                if ((type.index < 0) ||
                    (type.index >=
                     device_info->blocks[device_info->local_regs[local_reg].local_block_id].nof_instances))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported block instance");
                }
            }
        }
        else
#endif
        {
            /** verify block instance*/
            if (!dnx_drv_soc_reg_is_valid(unit, interrupts[type.event_id].reg))
            {
                SHR_ERR_EXIT(_SHR_E_INTERNAL, "Invalid interrupt register for the device");
            }

            soc_reg_info_p = dnx_drv_reg_info_ptr_get(unit, (int) (interrupts[type.event_id].reg));
            block_types = soc_reg_info_p->block;

            if (!dnx_drv_soc_block_in_list(unit, block_types, SOC_BLK_CLP)
                && !dnx_drv_soc_block_in_list(unit, block_types, SOC_BLK_XLP))
            {
                SHR_IF_ERR_EXIT(dnx_drv_soc_is_valid_block_instance(unit, block_types, type.index, &is_valid));
                if (!is_valid)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported block instance");
                }
            }

            inf_index = soc_interrupt_get_block_index_from_port(unit, type.event_id, type.index);
            if (inf_index < 0)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported block instance");
            }
        }
    }

    switch (type.action)
    {
        case bcmSwitchEventMask:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                rc = soc_dnxc_interrupt_all_enable_get(unit, &is_enable);
                SHR_IF_ERR_EXIT(rc);
                *value = (is_enable == 0);
            }
            else
            {
                /*
                 * Get per interrupt
                 */
                rc = soc_interrupt_is_enabled(unit, type.index, &(interrupts[type.event_id]), &is_enable);
                SHR_IF_ERR_EXIT(rc);
                *value = (is_enable == 0);
            }
            break;
        }
        case bcmSwitchEventForce:
        {
            /*
             * Set/clear per interrupt
             */
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid <controll all> event parameter for force option");
            }
            else
            {
                rc = soc_interrupt_force_get(unit, type.index, &(interrupts[type.event_id]), &is_enable);
                SHR_IF_ERR_EXIT(rc);
                *value = is_enable;
            }
            break;
        }
        case bcmSwitchEventClear:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                rc = soc_interrupt_is_all_clear(unit, (int *) value);
                SHR_IF_ERR_EXIT(rc);
            }
            else
            {
                /*
                 * Get per interrupt
                 */
                rc = soc_interrupt_get(unit, type.index, &(interrupts[type.event_id]), &inter_get);
                SHR_IF_ERR_EXIT(rc);
                *value = (inter_get == 0);
            }
            break;
        }
        case bcmSwitchEventRead:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid read parameter (event_id)");
            }
            else
            {
                {
                    /*
                     * Get per interrupt
                     */
                    rc = soc_interrupt_get(unit, type.index, &(interrupts[type.event_id]), &inter_get);
                    SHR_IF_ERR_EXIT(rc);
                    *value = (inter_get == 1);
                }
            }
            break;
        }
        case bcmSwitchEventStormTimedPeriod:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid Storm Timed Period parameter (event_id)");
            }
            else
            {
                /*
                 * Get per interrupt
                 */
                rc = soc_interrupt_storm_timed_period_get(unit, type.event_id, value);
                SHR_IF_ERR_EXIT(rc);
            }
            break;
        }
        case bcmSwitchEventStormTimedCount:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid Storm Timed Count parameter (event_id)");
            }
            else
            {
                /*
                 * Get per interrupt
                 */
                rc = soc_interrupt_storm_timed_count_get(unit, type.event_id, value);
                SHR_IF_ERR_EXIT(rc);
            }
            break;
        }
        case bcmSwitchEventStormNominal:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                uint32 *switch_event_nominal_storm_p;

                SHR_IF_ERR_EXIT(soc_control_element_address_get
                                (unit, SWITCH_EVENT_NOMINAL_STORM, (void **) (&switch_event_nominal_storm_p)));
                *value = *switch_event_nominal_storm_p;
            }
            else
            {
                /*
                 * Get per interrupt
                 */
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid nominal storm parameter (event_id)");
            }
            break;
        }
        case bcmSwitchEventStat:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid Statistics Control parameter (event_id)");
            }
            else
            {
                /*
                 * Get per interrupt
                 */
                *value = (interrupts[type.event_id].statistics_count)[inf_index];
            }
            break;
        }
        case bcmSwitchEventLog:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid Log Control parameter (event_id)");
            }
            else
            {
                uint32 flags;
                /*
                 * Get per interrupt
                 */
                rc = soc_interrupt_flags_get(unit, type.event_id, &flags);
                SHR_IF_ERR_EXIT(rc);
                *value = (SHR_BITGET(&flags, SOC_INTERRUPT_DB_FLAGS_PRINT_ENABLE) != 0) ? 0x1 : 0x0;
            }
            break;
        }
        case bcmSwitchEventCorrActOverride:
        {
            /*
             * Value - 0 : Only bcm callback will be called for this interrupt.
             * Value - 1 : Only user callback will be called for this interrupt. At this mode BCM driver will only print the interrupt information for logging.
             * Value - 2 : User call back will be called immediately after bcm callback.
             */
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid CorrActOveride Control parameter (event_id)");
            }
            else
            {
                /*
                 * Get per interrupt
                 */
                uint32 flags;

                rc = soc_interrupt_flags_get(unit, type.event_id, &flags);
                SHR_IF_ERR_EXIT(rc);

                if (flags & SOC_INTERRUPT_DB_FLAGS_BCM_AND_USR_CB)
                {
                    *value = 0x2;
                }
                else
                {
                    *value = (SHR_BITGET(&flags, SOC_INTERRUPT_DB_FLAGS_CORR_ACT_OVERRIDE_ENABLE) != 0) ? 0x1 : 0x0;
                }
            }
            break;
        }
        case bcmSwitchEventPriority:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid Event Priority Control parameter (event_id)");
            }
            else
            {
                uint32 flags;

                /*
                 * Get per interrupt
                 */
                rc = soc_interrupt_flags_get(unit, type.event_id, &flags);
                SHR_IF_ERR_EXIT(rc);
                *value = ((flags & SOC_INTERRUPT_DB_FLAGS_PRIORITY_MASK) >> SOC_INTERRUPT_DB_FLAGS_PRIORITY_BITS_LSB);
            }
            break;
        }
        case bcmSwitchEventUnmaskAndClearDisable:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid UnmaskAndClearDisable Control parameter (event_id)");
            }
            else
            {
                uint32 flags;

                /*
                 * Get per interrupt
                 */
                rc = soc_interrupt_flags_get(unit, type.event_id, &flags);
                SHR_IF_ERR_EXIT(rc);
                *value = (SHR_BITGET(&flags, SOC_INTERRUPT_DB_FLAGS_UNMASK_AND_CLEAR_DISABLE_BITS) != 0) ? 0x1 : 0x0;
            }
            break;
        }
        case bcmSwitchEventForceUnmask:
        {
            if (type.event_id == BCM_SWITCH_EVENT_CONTROL_ALL)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid ForceUnmask Control parameter (event_id)");
            }
            else
            {
                uint32 flags;
                /*
                 * Get per interrupt
                 */

                rc = soc_interrupt_flags_get(unit, type.event_id, &flags);
                SHR_IF_ERR_EXIT(rc);

                *value = (SHR_BITGET(&flags, SOC_INTERRUPT_DB_FLAGS_FORCE_UNMASK_BITS) != 0) ? 0x1 : 0x0;
            }
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported control");
            break;
        }
    }

exit:
    DNX_SWITCH_LOCK_RELEASE;
    DNX_ERR_RECOVERY_NO_SUPPORT_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Maps the Forwarding type(key.index) which will to the compressed forwarding type(value.value).
* \par DIRECT INPUT:
*   \param [in] unit   - unit Id
*   \param [in] key    - The key.index to be mapped(compressed)
*   \param [out] value - The value that the key was mapped to.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_switch_control_mtu_compressed_layer_type_get(
    int unit,
    bcm_switch_control_key_t key,
    bcm_switch_control_info_t * value)
{

    uint32 entry_handle_id;
    uint32 dnx_layer_type;
    uint8 get_val;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ETPP_TRAP_MTU_LAYER_TYPE_MAP, &entry_handle_id));

    SHR_IF_ERR_EXIT(dnx_field_map_layer_type_bcm_to_dnx(unit, key.index, &dnx_layer_type, NULL));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ENC_LAYER_TYPE, dnx_layer_type);

    /**
     * Get the Compressed Value
     */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_COMPRESSED, INST_SINGLE, &get_val);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
    value->value = get_val;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* \brief
*  Get MTU check enabler value per context. Currently only done for context ETPP_FORWARDING_WO_ETPS_POP
* \par DIRECT INPUT:
*   \param [in] unit  - unit Id
*   \param [in] key   - 0 (Currently not needed since don for single context)
*   \param [out] value - TRUE/FALSE.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_switch_control_mtu_context_enable_get(
    int unit,
    bcm_switch_control_key_t key,
    bcm_switch_control_info_t * value)
{
    uint32 entry_handle_id;
    uint8 get_val;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_MTU_CFG, &entry_handle_id));

    /*
     * Get the MTU context enabler
     */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_ETPP_FORWARDING_WO_ETPS_POP, INST_SINGLE, &get_val);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
    value->value = get_val;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Receive information whether the hitbit is enabled for tracking for the given table type
* \param [in] unit - unit ID
* \param [in] hitbit_table - The table type
* \param [out] value - Indication TRUE/FALSE whether the hitbit tracking is enabled.
* \return
*   \retval Zero if no error was detected
*   \retval Negative if error was detected. See \ref shr_error_e
*/
static shr_error_e
dnx_switch_control_hitbit_table_get(
    int unit,
    bcm_switch_l3_lpm_hitbit_tables_t hitbit_table,
    uint32 *value)
{
    dbal_tables_e table_id;
    SHR_FUNC_INIT_VARS(unit);

    switch (hitbit_table)
    {
        case bcmL3LpmHitbitTableIPv4UC:
            table_id = DBAL_TABLE_IPV4_UNICAST_PRIVATE_LPM_FORWARD;
            break;
        case bcmL3LpmHitbitTableIPv6UC:
            table_id = DBAL_TABLE_IPV6_UNICAST_PRIVATE_LPM_FORWARD;
            break;
        case bcmL3LpmHitbitTableIPv4MC:
            table_id = DBAL_TABLE_IPV4_MULTICAST_PRIVATE_LPM_FORWARD;
            break;
        case bcmL3LpmHitbitTableIPv6MC:
            table_id = DBAL_TABLE_IPV6_MULTICAST_PRIVATE_LPM_FORWARD;
            break;
        default:
            SHR_ERR_EXIT(BCM_E_PARAM,
                         "Not supported key index for bcmSwitchL3LpmHitbitEnable/bcmSwitchL3LpmHitbitDisable");
    }
    SHR_IF_ERR_EXIT(dbal_tables_indication_get(unit, table_id, DBAL_TABLE_IND_IS_HITBIT_EN, (uint32 *) value));
exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set the hitbit tracking for the given table type
* \param [in] unit - unit ID
* \param [in] hitbit_table - The table type
* \param [in] value - Indication TRUE/FALSE whether the hitbit tracking will be set to enabled/disabled.
* \return
*   \retval Zero if no error was detected
*   \retval Negative if error was detected. See \ref shr_error_e
*/
static shr_error_e
dnx_switch_control_hitbit_table_set(
    int unit,
    bcm_switch_l3_lpm_hitbit_tables_t hitbit_table,
    uint32 value)
{
    dbal_tables_e table_id_private;
    dbal_tables_e table_id_public = DBAL_TABLE_EMPTY;

    SHR_FUNC_INIT_VARS(unit);
    switch (hitbit_table)
    {
        case bcmL3LpmHitbitTableIPv4UC:
        {
            if (!kbp_mngr_ipv4_in_use(unit))
            {
                table_id_private = DBAL_TABLE_IPV4_UNICAST_PRIVATE_LPM_FORWARD;
                table_id_public = DBAL_TABLE_IPV4_UNICAST_PRIVATE_LPM_FORWARD_2;
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "hitbit enable is not supported for for KBP tables");
            }
            break;
        }
        case bcmL3LpmHitbitTableIPv6UC:
        {
            if (!kbp_mngr_ipv6_in_use(unit))
            {
                table_id_private = DBAL_TABLE_IPV6_UNICAST_PRIVATE_LPM_FORWARD;
                table_id_public = DBAL_TABLE_IPV6_UNICAST_PRIVATE_LPM_FORWARD_2;
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "hitbit enable is not supported for for KBP tables");
            }
            break;
        }
        case bcmL3LpmHitbitTableIPv4MC:
        {
            if (!kbp_mngr_ipv4_in_use(unit))
            {
                table_id_private = DBAL_TABLE_IPV4_MULTICAST_PRIVATE_LPM_FORWARD;
                table_id_public = DBAL_TABLE_IPV4_MULTICAST_PUBLIC_LPM_FORWARD;
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "hitbit enable is not supported for for KBP tables");
            }
            break;
        }
        case bcmL3LpmHitbitTableIPv6MC:
        {
            if (!kbp_mngr_ipv6_in_use(unit))
            {
                table_id_private = DBAL_TABLE_IPV6_MULTICAST_PRIVATE_LPM_FORWARD;
                /** IPv6 MC public table doesn't exists, so the variable is used to carry the DBAL table ID for the cascaded LPM table. */
                table_id_public = DBAL_TABLE_IPV6_MULTICAST_SOURCE_AND_INTERFACE;
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "hitbit enable is not supported for for KBP tables");
            }

            break;
        }
        default:
            SHR_ERR_EXIT(BCM_E_PARAM,
                         "Not supported key index for bcmSwitchL3LpmHitbitEnable/bcmSwitchL3LpmHitbitDisable");
    }
    SHR_IF_ERR_EXIT(dbal_tables_hitbit_enable(unit, table_id_private, value));
    SHR_IF_ERR_EXIT(dbal_tables_hitbit_enable(unit, table_id_public, value));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Maps the SCI(10b) to SCI_TRAP_PROFILE(2b) which is part of the MACSEC key construction for Trap action.
* \par DIRECT INPUT:
*   \param [in] unit  - unit Id
*   \param [in] index   - The index is the SCI
*   \param [in] value - The value is the SCI_TRAP_PROFILE.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_switch_macsec_sci_profile_set(
    int unit,
    int index,
    int value)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_SVTAG_SCI_TRAP_PROFILE_MAP, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SCI, index);

    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_SCI_TRAP_PROFILE, INST_SINGLE, value);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Gets the SCI_TRAP_PROFILE(2b) mapped to SCI(10b).
* \par DIRECT INPUT:
*   \param [in] unit  - unit Id
*   \param [in] index   - The index is the SCI
*   \param [out] value - The value is the SCI_TRAP_PROFILE.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_switch_macsec_sci_profile_get(
    int unit,
    int index,
    int *value)
{
    uint32 entry_handle_id;
    uint8 sci_profile;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_SVTAG_SCI_TRAP_PROFILE_MAP, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SCI, index);

    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_SCI_TRAP_PROFILE, INST_SINGLE, &sci_profile);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    *value = sci_profile;
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_switch_convert_svtag_error_code(
    int unit,
    uint32 bcm_data,
    uint32 *dnx_data)
{
    bcm_switch_svtag_err_code_t bcm_error_code;
    dbal_enum_value_field_macsec_error_code_e dnx_error_code;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * No verification needed - all done previously - this is strictly internal routine
     */
    bcm_error_code = (bcm_switch_svtag_err_code_t) (bcm_data);
    if (((int) bcm_error_code < 0) || (bcm_error_code >= bcmSwitchSvtagErrCodeCount))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Layer Type:%d is out of range\n", bcm_error_code);
    }
    switch (bcm_error_code)
    {
        case bcmSwitchSvtagErrCodeNone:
            dnx_error_code = DBAL_ENUM_FVAL_MACSEC_ERROR_CODE_NONE;
            break;
        case bcmSwitchSvtagErrCodeSpTcamMiss:
            dnx_error_code = DBAL_ENUM_FVAL_MACSEC_ERROR_CODE_SP_TCAM_MISS;
            break;
        case bcmSwitchSvtagErrCodeTagCntrlPortDisabledPkt:
            dnx_error_code = DBAL_ENUM_FVAL_MACSEC_ERROR_CODE_TAG_CONTROL_PORT_DISABLED_PKT;
            break;
        case bcmSwitchSvtagErrCodeUntagCtrlPortDisabledPkt:
            dnx_error_code = DBAL_ENUM_FVAL_MACSEC_ERROR_CODE_UNTAG_CONTROL_PORT_DISABLED_PKT;
            break;
        case bcmSwitchSvtagErrCodeIpv4ChecksumMismatchOrMplsBosNotFound:
            dnx_error_code = DBAL_ENUM_FVAL_MACSEC_ERROR_CODE_IPV4_CHECKSUM_MISMATCH_OR_MPLS_BOS_NOT_FOUND;
            break;
        case bcmSwitchSvtagErrCodeInvalidSectag:
            dnx_error_code = DBAL_ENUM_FVAL_MACSEC_ERROR_CODE_INVALID_SECTAG;
            break;
        case bcmSwitchSvtagErrCodeScTcamMiss:
            dnx_error_code = DBAL_ENUM_FVAL_MACSEC_ERROR_CODE_SC_TCAM_MISS;
            break;
        case bcmSwitchSvtagErrCodeNoSa:
            dnx_error_code = DBAL_ENUM_FVAL_MACSEC_ERROR_CODE_NO_SA;
            break;
        case bcmSwitchSvtagErrCodeReplayFailure:
            dnx_error_code = DBAL_ENUM_FVAL_MACSEC_ERROR_CODE_REPLAY_FAILURE;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Layer Type:\"%d\" is not supported.\n", bcm_error_code);
            break;
    }

    *(dbal_enum_value_field_layer_types_e *) dnx_data = dnx_error_code;

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Maps the ERR_CODE(8b) to ERR_CODE_TRAP_PROFILE(2b) which is part of the MACSEC key construction for Trap action.
* \par DIRECT INPUT:
*   \param [in] unit  - unit Id
*   \param [in] index - The index is the ERR_CODE
*   \param [in] value - The value is the ERR_CODE_TRAP_PROFILE.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_switch_macsec_err_code_profile_set(
    int unit,
    int index,
    int value)
{
    uint32 entry_handle_id, dbal_err_code;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_switch_convert_svtag_error_code(unit, index, &dbal_err_code));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_SVTAG_ERR_CODE_TRAP_PROFILE_MAP, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ERR_CODE, dbal_err_code);

    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_ERR_CODE_TRAP_PROFILE, INST_SINGLE, value);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Gets the ERR_CODE_TRAP_PROFILE(2b) mapped to ERR_CODE(10b).
* \par DIRECT INPUT:
*   \param [in] unit   - unit Id
*   \param [in] index  - The index is the ERR_CODE
*   \param [out] value - The value is the ERR_CODE_TRAP_PROFILE.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_switch_macsec_err_code_profile_get(
    int unit,
    int index,
    int *value)
{
    uint32 entry_handle_id, dbal_err_code;
    uint8 err_code_profile;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_switch_convert_svtag_error_code(unit, index, &dbal_err_code));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_SVTAG_ERR_CODE_TRAP_PROFILE_MAP, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ERR_CODE, dbal_err_code);

    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_ERR_CODE_TRAP_PROFILE, INST_SINGLE, &err_code_profile);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    *value = err_code_profile;
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

#if defined(INCLUDE_KBP)
/**
 * \brief
 *   Parses a bcm_switch_external_table_t to DBAL table ID
 * \param [in] unit - Relevant unit.
 * \param [in] app_table - The KBP table type.
 * \param [out] dbal_table_id - The returned DBAL table ID.
 * \param [out] is_opt - The returned optimized indication.
  \return
 *    \retval errors if unexpected behavior. See \ref shr_error_e
 *  \remark
 *    None
 *  \see
 *    shr_error_e
 */
static shr_error_e
dnx_switch_external_table_to_dbal_table_id(
    int unit,
    bcm_switch_external_table_t app_table,
    dbal_tables_e * dbal_table_id,
    uint8 *is_opt)
{
    SHR_FUNC_INIT_VARS(unit);

    switch (app_table)
    {
        case bcmSwitchExternalTableIp4Unicast:
        {
            *dbal_table_id = DBAL_TABLE_KBP_IPV4_UNICAST_PRIVATE_LPM_FORWARD;
            *is_opt = FALSE;
            break;
        }
        case bcmSwitchExternalTableIp4UnicastOptimized:
        {
            *dbal_table_id = DBAL_TABLE_KBP_IPV4_UNICAST_PRIVATE_LPM_FORWARD;
            *is_opt = TRUE;
            break;
        }
        case bcmSwitchExternalTableIp4Rpf:
        {
            *dbal_table_id = DBAL_TABLE_KBP_IPV4_UNICAST_PRIVATE_LPM_RPF;
            *is_opt = TRUE;
            break;
        }
        case bcmSwitchExternalTableIp4Multicast:
        {
            *dbal_table_id = DBAL_TABLE_KBP_IPV6_MULTICAST_TCAM_FORWARD;
            *is_opt = TRUE;
            break;
        }
        case bcmSwitchExternalTableIp6Unicast:
        {
            *dbal_table_id = DBAL_TABLE_KBP_IPV6_UNICAST_PRIVATE_LPM_FORWARD;
            *is_opt = FALSE;
            break;
        }
        case bcmSwitchExternalTableIp6UnicastOptimized:
        {
            *dbal_table_id = DBAL_TABLE_KBP_IPV6_UNICAST_PRIVATE_LPM_FORWARD;
            *is_opt = TRUE;
            break;
        }
        case bcmSwitchExternalTableIp6Rpf:
        {
            *dbal_table_id = DBAL_TABLE_KBP_IPV6_UNICAST_PRIVATE_LPM_RPF;
            *is_opt = TRUE;
            break;
        }
        case bcmSwitchExternalTableIp6Multicast:
        {
            *dbal_table_id = DBAL_TABLE_KBP_IPV6_MULTICAST_TCAM_FORWARD;
            *is_opt = TRUE;
            break;
        }
        case bcmSwitchExternalTableNat:
        {
            *dbal_table_id = DBAL_TABLE_KBP_NAT_EXTERNAL_TO_INTERNAL;
            *is_opt = FALSE;
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "The key.index(%d) value is illegal! For bcmSwitchExternalTableCapacity type, "
                         "valid values are defined in bcm_switch_external_table_t.\n", app_table);
        }
    }

exit:
    SHR_FUNC_EXIT;
}
#endif

/**
 *  See switch.h
 */
int
bcm_dnx_switch_control_indexed_get(
    int unit,
    bcm_switch_control_key_t key,
    bcm_switch_control_info_t * value)
{
    int svtag_trap_en;
    dnx_rx_trap_protocol_my_arp_ndp_config_t my_arp_ndp_config;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    SHR_NULL_CHECK(value, _SHR_E_PARAM, "value");

    svtag_trap_en = dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_svtag_trap_en);

    switch (key.type)
    {
        case bcmSwitchLinkLayerMtuFilter:
        {
            if (dnx_data_trap.
                etpp.feature_get(unit, dnx_data_trap_etpp_mtu_layer_to_compressed_layer_mapping_support) == 0)
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                             "The API with key.type = bcmSwitchLinkLayerMtuFilter is not supported on this device!\n");
            }

            SHR_IF_ERR_EXIT(dnx_switch_control_mtu_compressed_layer_type_get(unit, key, value));
            break;
        }
        case bcmSwitchForwardingLayerMtuFilter:
        {
            if (key.index != 0)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key index provided for bcmSwitchForwardingLayerMtuFilter is illegal! Only 0 is allowed\n");
            }

            SHR_IF_ERR_EXIT(dnx_switch_control_mtu_context_enable_get(unit, key, value));
            break;
        }
        case bcmSwitchHashSeed:
        {
            if (dnx_data_switch.load_balancing.feature_get(unit, dnx_data_switch_load_balancing_fwd_hashing_method) ==
                DNX_SWITCH_LB_FWD_HASH_METHOD_CRC_FUNCTION)
            {
                uint32 crc_function_hw_index;
                uint16 get_crc_seed;
                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_crc_function_enum_to_hw_get
                                (unit, (bcm_switch_hash_config_t) (key.index), &crc_function_hw_index));

                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_crc_seed_get(unit, crc_function_hw_index, &get_crc_seed));

                value->value = get_crc_seed;
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Getting CRC seed function is not supported on this device since load balancing key"
                             " calculation is done by SPN function! \n");
            }
            break;
        }
        case bcmSwitchLayerRecordModeSelection:
        {
            if (dnx_data_switch.
                load_balancing.feature_get(unit, dnx_data_switch_load_balancing_layer_record_mode_selection))
            {
                uint32 physical_client;
                dnx_switch_lb_lsms_crc_select_t lsms_crc_select;
                /*
                 * Convert logical client to physical so it can be read from tcam
                 */
                SHR_IF_ERR_EXIT(dnx_switch_lb_logical_client_to_physical
                                (unit, (bcm_switch_control_t) key.index, &physical_client));
                lsms_crc_select.lb_client = (uint8) physical_client;
                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_lsms_crc_select_get(unit, &lsms_crc_select));
                value->value = (uint32) (lsms_crc_select.lb_selection_bit_map);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Record mode selection is not supported on this device since all 32 bits are taken\n");
            }
            break;
        }
        case bcmSwitchL3LpmHitbitEnable:
        {
            if (dnx_data_mdb.kaps.feature_get(unit, dnx_data_mdb_kaps_hitbit_support))
            {
                SHR_IF_ERR_EXIT(dnx_switch_control_hitbit_table_get(unit, key.index, (uint32 *) &(value->value)));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Hitbit indication for the LPM is not supported on this device\n");
            }
            break;
        }
        case bcmSwitchModuleVerifyEnable:
        {
            uint8 module_verify = 0;
            SHR_IF_ERR_EXIT(switch_db.module_verification.get(unit, key.index, &module_verify));
            value->value = module_verify;
            break;
        }
        case bcmSwitchModuleErrorRecoveryEnable:
        {
            uint8 module_er = 0;
            SHR_IF_ERR_EXIT(switch_db.module_error_recovery.get(unit, key.index, &module_er));
            value->value = module_er;
            break;
        }
        case bcmSwitchMplsSpeculativeNibbleMap:
        {
            bcm_switch_mpls_next_protocol_t protocol;
            SHR_IF_ERR_EXIT(dnx_switch_load_balancing_nibble_speculation_get(unit, key.index, &protocol));
            value->value = (int) protocol;
            break;
        }
        case bcmSwitchSvtagSciProfile:
        {
            if (svtag_trap_en == 0)
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "The SVTAG APIs are not supported on this device !");
            }
            if (key.index >= dnx_data_trap.ingress.nof_scis_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The value supplied(%d) is too big ! "
                             "SCI value can be maximum 10b. \n", key.index);

            }
            SHR_IF_ERR_EXIT(dnx_switch_macsec_sci_profile_get(unit, key.index, &value->value));
            break;
        }
        case bcmSwitchSvtagErrCodeProfile:
        {
            if (svtag_trap_en == 0)
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "The SVTAG APIs are not supported on this device ! \n");
            }
            if (key.index >= dnx_data_trap.ingress.nof_error_codes_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The value supplied(%d) is too big ! "
                             "Error Code value can be maximum 8b. \n", key.index);

            }
            SHR_IF_ERR_EXIT(dnx_switch_macsec_err_code_profile_get(unit, key.index, &value->value));
            break;
        }
        case bcmSwitchNdpMyIp1:
        {
            if (key.index > 3)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The key.index(%d) value is illegal! Legal values 0-3. \n", key.index);
            }
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_ndp_get(unit, key.index, &my_arp_ndp_config));
            value->value = my_arp_ndp_config.ip_1;
            break;
        }
        case bcmSwitchNdpMyIp2:
        {
            if (key.index > 3)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The key.index(%d) value is illegal! Legal values 0-3. \n", key.index);
            }
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_ndp_get(unit, key.index, &my_arp_ndp_config));
            value->value = my_arp_ndp_config.ip_2;
            break;
        }
        case bcmSwitchL3TunnelCollapseDisable:
        {
            int val = 0;
            if (key.index < 0 || key.index >= bcmSwitchL3TunnelCount)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchL3TunnelCollapseDisable type.\n",
                             key.index);
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_l3_tunnel_disable_get(unit, key.index, &val));
            value->value = val;
            break;
        }
        case bcmSwitchRangeTypeSelect:
        {
            bcm_field_range_type_t range_type = bcmFieldRangeTypeFirst;
            if (key.index < 0 || key.index >= dnx_data_field.L4_Ops.nof_ext_types_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchRangeTypeSelect type, valid range is [0-%d].\n",
                             key.index, dnx_data_field.L4_Ops.nof_ext_types_get(unit) - 1);
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_range_type_get(unit, key.index, &range_type));
            value->value = range_type;
            break;
        }
        case bcmSwitchRangeResultMap:
        {
            bcm_switch_range_result_map_t range_result = bcmSwitchRangeResultMapInvalid;
            if (key.index < 0 || key.index >= dnx_data_field.L4_Ops.nof_ext_encoders_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchRangeResultMap type, valid range is [0-%d].\n",
                             key.index, dnx_data_field.L4_Ops.nof_ext_encoders_get(unit) - 1);
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_range_result_bmp_get(unit, key.index, &range_result));
            value->value = range_result;
            break;
        }
        case bcmSwitchExemScanPeriod:
        {
            uint32 scan_period_us = 0;

            if (key.index != 0 && key.index != 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchExemScanPeriod type, valid key.index values are: 0 (EXEM_3), 1 (EXEM_4).\n",
                             key.index);
            }

            /** Currently, EXEM_4 is not supported, only EXEM_3! */
            if (key.index == 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Error - key.index =1, bcmSwitchExemScanPeriod type: currently only EXEM_3 (0) is supported! EXEM_4 (1) is not supported!\n");
            }

            SHR_IF_ERR_EXIT(dnx_switch_control_exem_scan_period_get(unit, key.index, &scan_period_us));

            value->value = (int) scan_period_us;
            break;
        }
        case bcmSwitchExemFlushProfilePayloadOffset:
        {
            uint32 payload_offset = 0;

            if (key.index != 0 && key.index != 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchExemFlushProfilePayloadOffset type, valid key.index values are: 0 (EXEM_3), 1 (EXEM_4).\n",
                             key.index);
            }

            /** Currently, EXEM_4 is not supported, only EXEM_3! */
            if (key.index == 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Error - key.index =1, bcmSwitchExemFlushProfilePayloadOffset type: currently only EXEM_3 (0) is supported! EXEM_4 (1) is not supported!\n");
            }

            SHR_IF_ERR_EXIT(dnx_switch_control_exem_flush_profile_payload_offset_get(unit, key.index, &payload_offset));

            value->value = (int) payload_offset;
            break;
        }
#if defined(INCLUDE_KBP)
        case bcmSwitchExternalTableCapacity:
        {
            dbal_tables_e dbal_table_id;
            uint8 is_opt;
            if (!dnx_kbp_device_enabled(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "KBP device is not enabled\n");
            }
            SHR_IF_ERR_EXIT(dnx_switch_external_table_to_dbal_table_id(unit, key.index, &dbal_table_id, &is_opt));
            SHR_IF_ERR_EXIT(kbp_mngr_table_capacity_get(unit, dbal_table_id, is_opt, &value->value));
            break;
        }
#endif
        case bcmSwitchMplsSpecialLabelAutoTerminateDisable:
        {
            int enable = 0;
            SHR_IF_ERR_EXIT(dnx_mpls_special_label_as_general_label_get(unit, key.index, &enable));
            value->value = enable;
            break;
        }
#if defined(INCLUDE_KBP)
        case bcmSwitchExternalTablePropXlDb:
        {
            dbal_tables_e dbal_table_id;
            uint8 is_opt;

            if (!dnx_kbp_device_enabled(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "KBP device is not enabled\n");
            }
            if ((key.index != bcmSwitchExternalTableIp4Unicast) && (key.index != bcmSwitchExternalTableIp6Unicast))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchExternalTablePropXlDb type, "
                             "valid key index values are bcmSwitchExternalTableIp4Unicast and "
                             "bcmSwitchExternalTableIp6Unicast.\n", key.index);
            }

            SHR_IF_ERR_EXIT(dnx_switch_external_table_to_dbal_table_id(unit, key.index, &dbal_table_id, &is_opt));
            SHR_IF_ERR_EXIT(kbp_mngr_table_property_xl_db_get(unit, dbal_table_id, &value->value));
            break;
        }
#endif
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported control type: %d\r\n", key.type);
            break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Maps the Forwarding type(key.index) which will to the compressed forwarding type(value.value).
* \par DIRECT INPUT:
*   \param [in] unit  - unit Id
*   \param [in] key   - The key.index to be mapped(compressed)
*   \param [in] value - The value that the key will be mapped to.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_switch_control_mtu_compressed_layer_type_set(
    int unit,
    bcm_switch_control_key_t key,
    bcm_switch_control_info_t value)
{
    uint32 entry_handle_id;
    uint32 dnx_layer_type;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ETPP_TRAP_MTU_LAYER_TYPE_MAP, &entry_handle_id));

    SHR_IF_ERR_EXIT(dnx_field_map_layer_type_bcm_to_dnx(unit, key.index, &dnx_layer_type, NULL));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ENC_LAYER_TYPE, dnx_layer_type);

    /*
     * Set the Compressed Value
     */
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_COMPRESSED, INST_SINGLE, value.value);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Enables MTU check per context. Currently only done for context ETPP_FORWARDING_WO_ETPS_POP
* \par DIRECT INPUT:
*   \param [in] unit  - unit Id
*   \param [in] key   - 0 (Currently not needed since don for single context)
*   \param [in] value - TRUE/FALSE.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_switch_control_mtu_context_enable_set(
    int unit,
    bcm_switch_control_key_t key,
    bcm_switch_control_info_t value)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_MTU_CFG, &entry_handle_id));

    /*
     * Set the MTU context enabler
     */
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_ETPP_FORWARDING_WO_ETPS_POP, INST_SINGLE,
                                value.value);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 *  See switch.h
 */
int
bcm_dnx_switch_control_indexed_set(
    int unit,
    bcm_switch_control_key_t key,
    bcm_switch_control_info_t value)
{
    int svtag_trap_en;
    dnx_rx_trap_protocol_my_arp_ndp_config_t my_arp_ndp_config;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    DNX_SWITCH_LOCK_TAKE;

    svtag_trap_en = dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_svtag_trap_en);

    switch (key.type)
    {
        case bcmSwitchLinkLayerMtuFilter:
        {
            if (dnx_data_trap.
                etpp.feature_get(unit, dnx_data_trap_etpp_mtu_layer_to_compressed_layer_mapping_support) == 0)
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                             "The API with key.type = bcmSwitchLinkLayerMtuFilter is not supported on this device!\n");
            }
            else if (value.value >= DNX_RX_MTU_PORT_COMPRESSED_LAYER_TYPE)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The value supplied is too big %d! "
                             "Compressed Forward Layer Type must be between 1-6. \n", value.value);

            }

            SHR_IF_ERR_EXIT(dnx_switch_control_mtu_compressed_layer_type_set(unit, key, value));
            break;
        }
        case bcmSwitchForwardingLayerMtuFilter:
        {
            if (key.index != 0)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key index provided for bcmSwitchForwardingLayerMtuFilter is illegal! Only 0 is allowed\n");
            }

            if (value.value != FALSE && value.value != TRUE)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The value provided for bcmSwitchForwardingLayerMtuFilter is illegal! Only TRUE/FALSE are allowed\n");
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_mtu_context_enable_set(unit, key, value));
            break;
        }
        case bcmSwitchHashSeed:
        {
            if (dnx_data_switch.load_balancing.feature_get(unit, dnx_data_switch_load_balancing_fwd_hashing_method) ==
                DNX_SWITCH_LB_FWD_HASH_METHOD_CRC_FUNCTION)
            {
                uint32 max_crc_seed;
                uint32 crc_hw_function_index;

                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_crc_function_enum_to_hw_get
                                (unit, (bcm_switch_hash_config_t) (key.index), &crc_hw_function_index));

                /*
                 * Since we are shifting to 16 bits here, we need to also verify here, and not within
                 * the called procedure.
                 */
                max_crc_seed = dnx_data_switch.load_balancing.nof_seeds_per_crc_function_get(unit);
                if (value.value >= max_crc_seed)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 "\r\n"
                                 "Seed of crc function on input (%d) is larger than max allowed (%d).\r\n"
                                 "  This is illegal. Quit.\r\n", value.value, max_crc_seed - 1);
                }

                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_crc_seed_set
                                (unit, crc_hw_function_index, (uint16) (value.value)));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Setting CRC seed function is not supported on this device since load balancing key"
                             " calculation is done by SPN function! \n");
            }
            break;
        }
        case bcmSwitchLayerRecordModeSelection:
        {
            if (dnx_data_switch.
                load_balancing.feature_get(unit, dnx_data_switch_load_balancing_layer_record_mode_selection))
            {
                uint32 physical_client;
                dnx_switch_lb_lsms_crc_select_t lsms_crc_select;

                /*
                 * Convert logical client to physical so it can be loaded into tcam
                 */
                SHR_IF_ERR_EXIT(dnx_switch_lb_logical_client_to_physical
                                (unit, (bcm_switch_control_t) key.index, &physical_client));
                lsms_crc_select.lb_client = (uint8) physical_client;
                lsms_crc_select.lb_selection_bit_map = (uint16) (value.value);
                SHR_IF_ERR_EXIT(dnx_switch_load_balancing_lsms_crc_select_set(unit, &lsms_crc_select));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Record mode selection is not supported on this device since all 32 bits are taken\n");
            }
            break;
        }
        case bcmSwitchL3LpmHitbitEnable:
        {
            if (dnx_data_mdb.kaps.feature_get(unit, dnx_data_mdb_kaps_hitbit_support))
            {
                SHR_IF_ERR_EXIT(dnx_switch_control_hitbit_table_set(unit, key.index, (uint32) value.value));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Hitbit indication for the LPM is not supported on this device\n");
            }
            break;
        }
        case bcmSwitchModuleVerifyEnable:
        {
            uint8 module_verify = value.value;
            SHR_IF_ERR_EXIT(switch_db.module_verification.set(unit, key.index, module_verify));
            break;
        }
        case bcmSwitchModuleErrorRecoveryEnable:
        {
            uint8 module_er = value.value;
            SHR_IF_ERR_EXIT(switch_db.module_error_recovery.set(unit, key.index, module_er));
            break;
        }
        case bcmSwitchMplsSpeculativeNibbleMap:
        {
            SHR_IF_ERR_EXIT(dnx_switch_load_balancing_nibble_speculation_set
                            (unit, key.index, (bcm_switch_mpls_next_protocol_t) value.value));
            break;
        }
        case bcmSwitchSvtagSciProfile:
        {
            if (svtag_trap_en == 0)
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "The SVTAG APIs are not supported on this device !");
            }
            if (key.index >= dnx_data_trap.ingress.nof_scis_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The value supplied(%d) is too big ! "
                             "SCI value can be maximum 10b. \n", key.index);

            }
            if (value.value >= dnx_data_trap.ingress.nof_sci_profiles_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The value supplied is too big %d! "
                             "SCI Profile value can be maximum 2b. \n", value.value);

            }
            SHR_IF_ERR_EXIT(dnx_switch_macsec_sci_profile_set(unit, key.index, value.value));
            break;
        }
        case bcmSwitchSvtagErrCodeProfile:
        {
            if (svtag_trap_en == 0)
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "The SVTAG APIs are not supported on this device ! \n");
            }
            if (key.index >= dnx_data_trap.ingress.nof_error_codes_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The value supplied(%d) is too big ! "
                             "Error Code value can be maximum 8b. \n", key.index);

            }
            if (value.value >= dnx_data_trap.ingress.nof_error_code_profiles_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The value supplied is too big %d! "
                             "Error Code Profile value can be maximum 2b. \n", value.value);

            }
            SHR_IF_ERR_EXIT(dnx_switch_macsec_err_code_profile_set(unit, key.index, value.value));
            break;
        }
        case bcmSwitchNdpMyIp1:
        {
            if (key.index > 3)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The key.index(%d) value is illegal! Legal values 0-3. \n", key.index);
            }
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_ndp_get(unit, key.index, &my_arp_ndp_config));
            my_arp_ndp_config.ip_1 = value.value;
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_ndp_set(unit, key.index, &my_arp_ndp_config));
            break;
        }
        case bcmSwitchNdpMyIp2:
        {
            if (key.index > 3)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "The key.index(%d) value is illegal! Legal values 0-3. \n", key.index);
            }
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_ndp_get(unit, key.index, &my_arp_ndp_config));
            my_arp_ndp_config.ip_2 = value.value;
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_my_ndp_set(unit, key.index, &my_arp_ndp_config));
            break;
        }
        case bcmSwitchL3TunnelCollapseDisable:
        {
            if (key.index < 0 || key.index >= bcmSwitchL3TunnelCount)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchL3TunnelCollapseDisable type.\n",
                             key.index);
            }
            if (value.value != FALSE && value.value != TRUE)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The value provided for bcmSwitchL3TunnelCollapseDisable is illegal! Only TRUE/FALSE are allowed");
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_l3_tunnel_disable_set(unit, key.index, value.value));
            break;
        }
        case bcmSwitchRangeTypeSelect:
        {
            if (key.index < 0 || key.index >= dnx_data_field.L4_Ops.nof_ext_types_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchRangeTypeSelect type, valid range is [0-%d].\n",
                             key.index, dnx_data_field.L4_Ops.nof_ext_types_get(unit) - 1);
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_range_type_set(unit, key.index, value.value));
            break;
        }
        case bcmSwitchRangeResultMap:
        {
            if (key.index < 0 || key.index >= dnx_data_field.L4_Ops.nof_ext_encoders_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchRangeResultMap type, valid range is [0-%d].\n",
                             key.index, dnx_data_field.L4_Ops.nof_ext_encoders_get(unit) - 1);
            }
            if (value.value < bcmSwitchRangeResultMapFirst && value.value >= bcmSwitchRangeResultMapCount)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The value provided for bcmSwitchRangeResultMap is illegal! Should be between [%d,%d]",
                             bcmSwitchRangeResultMapFirst, bcmSwitchRangeResultMapCount - 1);
            }
            SHR_IF_ERR_EXIT(dnx_switch_control_range_result_bmp_set(unit, key.index, value.value));
            break;
        }
        case bcmSwitchExemScanPeriod:
        {
            if (key.index != 0 && key.index != 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchExemScanPeriod type, valid key.index values are: 0 (EXEM_3), 1 (EXEM_4).\n",
                             key.index);
            }

            /** Currently, EXEM_4 is not supported, only EXEM_3! */
            if (key.index == 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Error - key.index =1, bcmSwitchExemScanPeriod type: currently only EXEM_3 (0) is supported! EXEM_4 (1) is not supported!\n");
            }

            SHR_IF_ERR_EXIT(dnx_switch_control_exem_scan_period_set(unit, key.index, (uint32) value.value));
            break;
        }
        case bcmSwitchExemFlushProfilePayloadOffset:
        {
            if (key.index != 0 && key.index != 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchExemFlushProfilePayloadOffset type, valid key.index values are: 0 (EXEM_3), 1 (EXEM_4).\n",
                             key.index);
            }

            /** Currently, EXEM_4 is not supported, only EXEM_3! */
            if (key.index == 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Error - key.index =1, bcmSwitchExemFlushProfilePayloadOffset type: currently only EXEM_3 (0) is supported! EXEM_4 (1) is not supported!\n");
            }

            SHR_IF_ERR_EXIT(dnx_switch_control_exem_flush_profile_payload_offset_set
                            (unit, key.index, (uint32) value.value));
            break;
        }
#if defined(INCLUDE_KBP)
        case bcmSwitchExternalTableCapacity:
        {
            dbal_tables_e dbal_table_id;
            uint8 is_opt;
            int device_locked;

            if (!dnx_kbp_device_enabled(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "KBP device is not enabled\n");
            }

            SHR_IF_ERR_EXIT(dnx_field_map_is_device_locked(unit, &device_locked));
            if (device_locked)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG,
                             "KBP sync is already performed. Tables capacities are already configured and cannot be set\n");
            }

            SHR_IF_ERR_EXIT(dnx_switch_external_table_to_dbal_table_id(unit, key.index, &dbal_table_id, &is_opt));
            SHR_IF_ERR_EXIT(kbp_mngr_table_capacity_set(unit, dbal_table_id, is_opt, value.value));
            break;
        }
#endif
        case bcmSwitchMplsSpecialLabelAutoTerminateDisable:
        {
            SHR_IF_ERR_EXIT(dnx_mpls_special_label_as_general_label_set(unit, key.index, value.value));
            break;
        }
#if defined(INCLUDE_KBP)
        case bcmSwitchExternalTablePropXlDb:
        {
            dbal_tables_e dbal_table_id;
            uint8 is_opt;
            int device_locked;

            if (!dnx_kbp_device_enabled(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "KBP device is not enabled\n");
            }

            SHR_IF_ERR_EXIT(dnx_field_map_is_device_locked(unit, &device_locked));
            if (device_locked)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG,
                             "KBP sync is already performed. Tables XL DB property are already configured and cannot be changed\n");
            }
            if ((key.index != bcmSwitchExternalTableIp4Unicast) && (key.index != bcmSwitchExternalTableIp6Unicast))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The key.index(%d) value is illegal! For bcmSwitchExternalTablePropXlDb type, "
                             "valid key index values are bcmSwitchExternalTableIp4Unicast and "
                             "bcmSwitchExternalTableIp6Unicast.\n", key.index);
            }
            if ((value.value != 0) && (value.value != 1))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The value(%d) is illegal! For bcmSwitchExternalTablePropXlDb type, "
                             "valid values are 0 and 1.\n", value.value);
            }

            SHR_IF_ERR_EXIT(dnx_switch_external_table_to_dbal_table_id(unit, key.index, &dbal_table_id, &is_opt));
            SHR_IF_ERR_EXIT(kbp_mngr_table_property_xl_db_set(unit, dbal_table_id, value.value));
            break;
        }
#endif
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported control type: %d\r\n", key.type);
            break;
        }
    }

exit:
    DNX_SWITCH_LOCK_RELEASE;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  re-init the dram, after power down and power up was made.
*
* \param [in] unit  - unit Id
* \param [in] flags - currently not in use
*
* \return
*   shr_error_e
*
* \remark
*   should be called part of temperature monitor procedure.
* \see
*   * None
*/
int
bcm_dnx_switch_dram_init(
    int unit,
    uint32 flags)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    SHR_IF_ERR_EXIT(dnx_dram_reinit(unit, flags));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - dram power down callback registration.
 *
 * \param [in] unit - unit number
 * \param [in] flags - NONE
 * \param [in] callback - pointer to callback function
 * \param [in] userdata - pointer to the user data. NULL if not exist.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_dram_power_down_cb_register(
    int unit,
    uint32 flags,
    bcm_switch_dram_power_down_callback_t callback,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    SHR_IF_ERR_EXIT(dnx_dram_power_down_cb_register(unit, flags, callback, userdata));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - dram power down callback un-registration.
 *
 * \param [in] unit - unit number
 * \param [in] callback - pointer to callback function
 * \param [in] userdata - pointer to the user data. NULL if not exist.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_dram_power_down_cb_unregister(
    int unit,
    bcm_switch_dram_power_down_callback_t callback,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    SHR_IF_ERR_EXIT(dnx_dram_power_down_cb_unregister(unit, callback, userdata));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - power dowm dram procedure when temperature exceed the "powe down" threshold.
 *
 * \param [in] unit - unit number
 * \param [in] flags - API flags (currently NONE)
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   This functionality should be used when Soc property: dram_temperature_monitor_enable=FALSE
 * \see
 *   * None
 */
int
bcm_dnx_switch_dram_power_down(
    int unit,
    uint32 flags)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    SHR_IF_ERR_EXIT(dnx_dram_power_down(unit, flags));
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - enable or disable traffic into DRAM. once the temperature exceed a threshold, user should disable traffic to DRAM.
 *   When temperature reduce below threshold, it should enable it back.
 *
 * \param [in] unit - unit number
 * \param [in] flags - API flags (currently NONE)
 * \param [in] enable - true for enable traffic into DRAM, false for disable
 * \return
 *   shr_error_e
 *
 * \remark
 *   This functionality should be used when Soc property: dram_temperature_monitor_enable=FALSE
 * \see
 *   * None
 */
int
bcm_dnx_switch_dram_traffic_enable_set(
    int unit,
    uint32 flags,
    uint32 enable)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    SHR_IF_ERR_EXIT(dnx_dram_traffic_enable_set(unit, flags, enable));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_switch_thermo_sensor_read_verify(
    int unit,
    bcm_switch_thermo_sensor_type_t sensor_type,
    int interface_id,
    bcm_switch_thermo_sensor_t * sensor_data)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(sensor_data, _SHR_E_PARAM, "sensor_data");
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - read from HW the thermo sensors
 *
 * \param [in] unit - unit number
 * \param [in] sensor_type - Thermo sensors enum. use bcmSwitchThermoSensorDram for reading dram temp
 * \param [in] interface_id - interface is
 * \param [out] sensor_data - output data
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_thermo_sensor_read(
    int unit,
    bcm_switch_thermo_sensor_type_t sensor_type,
    int interface_id,
    bcm_switch_thermo_sensor_t * sensor_data)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    SHR_INVOKE_VERIFY_DNXC(dnx_switch_thermo_sensor_read_verify(unit, sensor_type, interface_id, sensor_data));
    switch (sensor_type)
    {
        case bcmSwitchThermoSensorDram:
        {
            SHR_IF_ERR_EXIT(dnx_dram_thermo_sensor_read(unit, interface_id, sensor_data));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported sensor_type");
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_switch_kbp_info_get_verify(
    int unit,
    bcm_core_t core,
    bcm_switch_kbp_info_t * kbp_info)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(kbp_info, _SHR_E_PARAM, "kbp_info");

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - get from DNX driver the KBP device pointer
 *
 * \param [in] unit - unit number
 * \param [in] core - not in used
 * \param [out] kbp_info - pointer to kbp device_pointer
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_kbp_info_get(
    int unit,
    bcm_core_t core,
    bcm_switch_kbp_info_t * kbp_info)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_switch_kbp_info_get_verify(unit, core, kbp_info));
#if defined(INCLUDE_KBP)
    SHR_IF_ERR_EXIT(dnx_kbp_info_get(unit, DNX_KBP_INST_MASTER, kbp_info));
#else
    kbp_info->device_p = NULL;
#endif

exit:
#ifdef BCM_WARM_BOOT_SUPPORT
    dnxc_wb_test_mode_skip_wb_sequence(unit);
#endif /* BCM_WARM_BOOT_SUPPORT */
    SHR_FUNC_EXIT;
}

/**
* \brief - verification for API bcm_switch_hard_reset_cb_register/bcm_switch_hard_reset_cb_unregister
*
* \param [in] unit - unit number
* \param [in] callback - pointer to callback function
* \param [in] userdata - pointer to the user data. NULL if not exist.
*
* \return
*   shr_error_e
*
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_hard_reset_cb_verify(
    int unit,
    bcm_switch_hard_reset_callback_t callback,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(callback, _SHR_E_PARAM, "callback");
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - device hard reset callback registration.
 *
 * \param [in] unit - unit number
 * \param [in] flags - NONE
 * \param [in] callback - pointer to callback function
 * \param [in] userdata - pointer to the user data. NULL if doesn't exist.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_hard_reset_cb_register(
    int unit,
    uint32 flags,
    bcm_switch_hard_reset_callback_t callback,
    void *userdata)
{
    bcm_switch_hard_reset_callback_t check_callback = NULL;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_hard_reset_cb_verify(unit, callback, userdata));
    SHR_IF_ERR_EXIT(dnx_hard_reset_db.hard_reset_callback.callback.get(unit, &check_callback));
    if (!sw_state_is_warm_boot(unit) && check_callback != NULL)
    {
        SHR_ERR_EXIT(_SHR_E_EXISTS, "Hard reset callback function already registered.\n");
    }

    SHR_IF_ERR_EXIT(dnxc_ha_tmp_allow_access_enable(unit, UTILEX_SEQ_ALLOW_SW_STATE));
    SHR_IF_ERR_EXIT(dnx_hard_reset_db.hard_reset_callback.callback.set(unit, callback));
    SHR_IF_ERR_EXIT(dnx_hard_reset_db.hard_reset_callback.
                    userdata.set(unit, (dnx_hard_reset_callback_userdata_t) userdata));
    SHR_IF_ERR_EXIT(dnxc_ha_tmp_allow_access_disable(unit, UTILEX_SEQ_ALLOW_SW_STATE));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - device hard reset callback un-registration.
 *
 * \param [in] unit - unit number
 * \param [in] callback - pointer to callback function
 * \param [in] userdata - pointer to the user data. NULL if doesn't exist.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_hard_reset_cb_unregister(
    int unit,
    bcm_switch_hard_reset_callback_t callback,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_hard_reset_cb_verify(unit, callback, userdata));
    SHR_IF_ERR_EXIT(dnx_hard_reset_db.hard_reset_callback.callback.set(unit, NULL));
    SHR_IF_ERR_EXIT(dnx_hard_reset_db.hard_reset_callback.userdata.set(unit, NULL));

exit:
    SHR_FUNC_EXIT;
}
/**
 * \brief - return the FEC IDs allocation range.
 *
 * \param [in] unit - unit number
 * \param [in,out] fec_config - structure that holds the following
 *          -  flags - uses BCM_SWITCH_FEC_PROPERTY_XXX to determine the requested hierarchy and direction
 *          -  start - the first FEC ID in the range
 *          -  end   - the last FEC ID in the range
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_fec_property_get(
    int unit,
    bcm_switch_fec_property_config_t * fec_config)
{
    uint32 range_start;
    uint32 range_size;
    uint32 fec_property_hierarchy_flags = 0;
    int hierarchy;
    int direction = DNX_L3_FEC_DIRECTION_NA;
    mdb_physical_table_e fec_db;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_NULL_CHECK(fec_config, _SHR_E_PARAM, "bcm_switch_fec_property_config_t");
    if (!fec_config->flags
        || _SHR_IS_FLAG_SET(fec_config->flags, ~dnx_data_l3.fec.fec_property_supported_flags_get(unit)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The provided flags 0x%x are either empty or unsupported\r\n", fec_config->flags);
    }

    fec_property_hierarchy_flags = (fec_config->flags & DNX_SWITCH_FEC_PROPERTY_HIERARCHY_FLAGS_MASK);
    if (fec_property_hierarchy_flags != 0)
    {
        if (fec_property_hierarchy_flags != BCM_SWITCH_FEC_PROPERTY_1ST_HIERARCHY
            && fec_property_hierarchy_flags != BCM_SWITCH_FEC_PROPERTY_2ND_HIERARCHY
            && fec_property_hierarchy_flags != BCM_SWITCH_FEC_PROPERTY_3RD_HIERARCHY)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Only one of the flags BCM_SWITCH_FEC_PROPERTY_1ST_HIERARCHY, BCM_SWITCH_FEC_PROPERTY_2ND_HIERARCHY or BCM_SWITCH_FEC_PROPERTY_3RD_HIERARCHY must be set\n");
        }
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "One of the flags BCM_SWITCH_FEC_PROPERTY_1ST_HIERARCHY, BCM_SWITCH_FEC_PROPERTY_2ND_HIERARCHY or BCM_SWITCH_FEC_PROPERTY_3RD_HIERARCHY must be set\n");
    }

    if (_SHR_IS_FLAG_SET(fec_config->flags, BCM_SWITCH_FEC_PROPERTY_1ST_HIERARCHY))
    {
        hierarchy = DBAL_ENUM_FVAL_HIERARCHY_LEVEL_HIERARCHY_LEVEL_1;
    }
    else if (_SHR_IS_FLAG_SET(fec_config->flags, BCM_SWITCH_FEC_PROPERTY_2ND_HIERARCHY))
    {
        hierarchy = DBAL_ENUM_FVAL_HIERARCHY_LEVEL_HIERARCHY_LEVEL_2;
    }
    else
    {
        hierarchy = DBAL_ENUM_FVAL_HIERARCHY_LEVEL_HIERARCHY_LEVEL_3;
    }

    SHR_IF_ERR_EXIT(algo_l3_db.fec_db_info.fec_db.get(unit, direction, hierarchy, &fec_db));
    SHR_IF_ERR_EXIT(mdb_init_fec_ranges_allocation_info_get(unit, fec_db, &range_start, &range_size));
    /** In case the range starts from 0, return the first valid FEC ID using dnx data */
    if (range_start == 0)
    {
        range_start = dnx_data_l3.fec.first_valid_fec_ecmp_id_get(unit);
        range_size -= dnx_data_l3.fec.first_valid_fec_ecmp_id_get(unit);
    }
    fec_config->start = range_start;
    fec_config->end = range_start + range_size - 1;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - return the utilization for a specific resource
 *          the "free" field in the utilization output is
 *          represented as worst case and not average case.
 *
 * \param [in] unit -  Unit-ID
 * \param [in] resource - pointer for a structure that describes
 *        the resource to query
 * \param [out] utilization - The utilization (max,used,free)
 *        for the resource.
 * \return
 *   shr_error_e
 * \remarks
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_resource_utilization_get(
    int unit,
    bcm_switch_resource_utilization_query_t * resource,
    bcm_switch_resource_utilization_t * utilization)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (resource->type)
    {
        case bcmResourceTypeEM:
        {
            /*
             * Translate from id to MDB EM table
             * Retrieve the largest supported (valid vmv) entry size
             * Return the guaranteed number of entries for that entry size
             */
            if ((resource->id >= dnx_data_mdb.global.utilization_api_nof_dbs_get(unit))
                ||(dnx_data_mdb.em.em_utilization_api_db_translation_get(unit, resource->id)->dbal_id ==
                   DBAL_NOF_PHYSICAL_TABLES))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid resource_id input (%d) for resource_type (%d)\r\n", resource->id,
                             resource->type);
            }

            SHR_IF_ERR_EXIT(mdb_em_get_min_remaining_entry_count
                            (unit, dnx_data_mdb.em.em_utilization_api_db_translation_get(unit, resource->id)->dbal_id,
                             (int *) &utilization->guaranteed_free));

            break;
        }
        case bcmResourceTypeLPM:
        {
            /*
             * Translate from id to KAPS table and ipv4/6
             * Retrieve estimate and multiply it by a safety margin to receive the guaranteed_free
             *
             * id = 0: KAPS_1 ipv4
             * id = 1: KAPS_1 ipv6
             * id = 2: KAPS_2 ipv4
             * id = 3: KAPS_2 ipv6
             */
            dbal_physical_tables_e dbal_physical_table_id;
            int ipv4_capacity, ipv6_capacity;
            int requested_capacity;
            int num_entries;
            int num_entries_iter;
            int capacity_estimate;

            if ((resource->id / MDB_LPM_DBS_IN_PAIR) < dnx_data_mdb.kaps.nof_dbs_get(unit))
            {
                dbal_physical_table_id =
                    dnx_data_mdb.kaps.db_info_get(unit, (resource->id / MDB_LPM_DBS_IN_PAIR))->dbal_id;
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid resource_id input (%d) for resource_type (%d)\r\n", resource->id,
                             resource->type);
            }

            SHR_IF_ERR_EXIT(mdb_lpm_get_ip_capacity
                            (unit, dbal_physical_table_id, 0, NULL, &ipv4_capacity, &ipv6_capacity));

            if (resource->id % MDB_LPM_DBS_IN_PAIR == 0)
            {
                requested_capacity = ipv4_capacity;
            }
            else
            {
                requested_capacity = ipv6_capacity;
            }

            /*
             * Retrieve the current number of entries
             * The capacity_estimate returned by this function does not fit the requirements of guaranteed entries
             */
            SHR_IF_ERR_EXIT(mdb_lpm_get_current_capacity
                            (unit, dbal_physical_table_id, &num_entries, &num_entries_iter, &capacity_estimate));

            /*
             * Assume all current entries are of the requested type, i.e. worst case
             * Reduce requested_capacity by the proportion of utilized IPv6 entries
             */
            if (ipv6_capacity > num_entries)
            {
                /*
                 * The capacity returned is an estimate, allow for a 20% safety margin
                 */
                utilization->guaranteed_free = (requested_capacity - num_entries) * 0.8;
            }
            else
            {
                utilization->guaranteed_free = 0;
            }

            break;
        }
        case bcmResourceTypeDirect:
        {
            if ((resource->id >= dnx_data_mdb.global.utilization_api_nof_dbs_get(unit))
                ||(dnx_data_mdb.direct.direct_utilization_api_db_translation_get(unit, resource->id)->dbal_id ==
                   DBAL_NOF_PHYSICAL_TABLES))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid resource_id input (%d) for resource_type (%d)\r\n", resource->id,
                             resource->type);
            }

            SHR_IF_ERR_EXIT(mdb_db_infos.capacity.get(unit,
                                                      dnx_data_mdb.direct.
                                                      direct_utilization_api_db_translation_get(unit,
                                                                                                resource->id)->dbal_id,
                                                      (int *) &utilization->guaranteed_free));
            break;
        }
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid resource_type input (%d)\r\n", resource->type);

    }

    SHR_EXIT();

exit:
    SHR_FUNC_EXIT;
}

/**
 * See switch.h
 */
int
dnx_switch_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(switch_db.init(unit));
exit:
    SHR_FUNC_EXIT;
}

/**
 * See switch.h
 */
int
dnx_switch_pp_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_switch_load_balancing_module_init(unit));

    if (dnx_data_switch.svtag.supported_get(unit))
    {
        SHR_IF_ERR_EXIT(dnx_switch_svtag_init(unit));
    }
    SHR_IF_ERR_EXIT(dnx_switch_wide_data_init(unit));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Verify function for BCM-API bcm_dnx_switch_lif_hit_get
 */
static shr_error_e
dnx_switch_lif_hit_get_verify(
    int unit,
    bcm_switch_lif_hit_t * lif_hit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(lif_hit, _SHR_E_PARAM, "lif_hit");

    if (!_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_INGRESS) &&
        !_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_EGRESS))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "flags BCM_SWITCH_LIF_HIT_INGRESS or BCM_SWITCH_LIF_HIT_EGRESS must be set.\r\n");
    }
    if (_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_INGRESS) &&
        _SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_EGRESS))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "flags BCM_SWITCH_LIF_HIT_INGRESS and BCM_SWITCH_LIF_HIT_EGRESS can't be all set.\r\n");
    }

    if (_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_L3_INTF))
    {
        if (!BCM_L3_ITF_TYPE_IS_LIF(lif_hit->l3_intf) && !BCM_L3_ITF_TYPE_IS_RIF(lif_hit->l3_intf))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "l3_intf(%x) must be of type LIF or RIF.\r\n", lif_hit->l3_intf);
        }
    }

    if (!_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_GET) &&
        !_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_CLEAR))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "flags BCM_SWITCH_LIF_HIT_GET or BCM_SWITCH_LIF_HIT_CLEAR must be set.\r\n");
    }
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Get the LIF hit values with the given L3 interface or Gport.
 *     \param [in] unit - Relevant unit.
 *     \param [inout] lif_hit - pointer to lif hit.
 * \return
 *     \retval Negative in case of an error. When entry is not
 *             found, will return an error.
 *     \retval Zero in case of NO ERROR
 */
int
bcm_dnx_switch_lif_hit_get(
    int unit,
    bcm_switch_lif_hit_t * lif_hit)
{
    int is_ingress, is_egress;
    bcm_gport_t gport = 0;
    bcm_if_t l3_intf = 0;
    uint32 lif_flags;
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    dbal_tables_e table_id;
    uint32 entry_handle_id;
    uint32 attr_type = DBAL_ENTRY_ATTR_FLAG_HIT_PRIMARY | DBAL_ENTRY_ATTR_FLAG_HIT_SECONDARY;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    /** Verification of input parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_switch_lif_hit_get_verify(unit, lif_hit));

    is_ingress = _SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_INGRESS) ? TRUE : FALSE;
    is_egress = _SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_EGRESS) ? TRUE : FALSE;

    /*
     * Get the l3_intf or gport from lif_hit
     */
    if (_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_L3_INTF))
    {
        if (BCM_L3_ITF_TYPE_IS_RIF(lif_hit->l3_intf))
        {
            l3_intf = BCM_L3_ITF_VAL_GET(lif_hit->l3_intf);
        }
        else if (BCM_L3_ITF_TYPE_IS_LIF(lif_hit->l3_intf))
        {
            BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(gport, lif_hit->l3_intf);
        }
    }
    else
    {
        gport = lif_hit->gport;
    }

    /*
     * Get the attr_type from flags
     */
    if (_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_GET))
    {
        attr_type |= DBAL_ENTRY_ATTR_FLAG_HIT_GET;
    }
    if (_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_CLEAR))
    {
        attr_type |= DBAL_ENTRY_ATTR_FLAG_HIT_CLEAR;
    }

    if (is_ingress)
    {
        if (_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_L3_INTF) && BCM_L3_ITF_TYPE_IS_RIF(lif_hit->l3_intf))
        {
            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ING_VSI_INFO_DB, &entry_handle_id));
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_VSI, l3_intf);
            SHR_IF_ERR_EXIT(dbal_entry_attribute_request(unit, entry_handle_id, DBAL_ENTRY_ATTR_HITBIT, attr_type));
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
            SHR_IF_ERR_EXIT(dbal_entry_attribute_get(unit, entry_handle_id, DBAL_ENTRY_ATTR_HITBIT, &lif_hit->val));
        }
        else
        {
            /*
             * Get local lif
             */
            lif_flags = DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_INGRESS |
                DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_INGRESS;
            SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, gport, lif_flags, &gport_hw_resources));
            /** Get table handle */
            table_id = gport_hw_resources.inlif_dbal_table_id;
            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF, gport_hw_resources.local_in_lif);
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE,
                                         gport_hw_resources.inlif_dbal_result_type);
            SHR_IF_ERR_EXIT(dbal_entry_attribute_request(unit, entry_handle_id, DBAL_ENTRY_ATTR_HITBIT, attr_type));
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
            SHR_IF_ERR_EXIT(dbal_entry_attribute_get(unit, entry_handle_id, DBAL_ENTRY_ATTR_HITBIT, &lif_hit->val));
        }
    }

    if (is_egress)
    {
        if (_SHR_IS_FLAG_SET(lif_hit->flags, BCM_SWITCH_LIF_HIT_L3_INTF) && BCM_L3_ITF_TYPE_IS_RIF(lif_hit->l3_intf))
        {
            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGR_VSI_INFO_DB, &entry_handle_id));
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_VSI, l3_intf);
            SHR_IF_ERR_EXIT(dbal_entry_attribute_request(unit, entry_handle_id, DBAL_ENTRY_ATTR_HITBIT, attr_type));
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
            SHR_IF_ERR_EXIT(dbal_entry_attribute_get(unit, entry_handle_id, DBAL_ENTRY_ATTR_HITBIT, &lif_hit->val));
        }
        else
        {
            /*
             * Get local lif
             */
            lif_flags = DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS |
                DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_EGRESS;
            SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, gport, lif_flags, &gport_hw_resources));
            /** Get table handle */
            table_id = gport_hw_resources.outlif_dbal_table_id;
            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF, gport_hw_resources.local_out_lif);
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE,
                                         gport_hw_resources.outlif_dbal_result_type);
            SHR_IF_ERR_EXIT(dbal_entry_attribute_request(unit, entry_handle_id, DBAL_ENTRY_ATTR_HITBIT, attr_type));
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
            SHR_IF_ERR_EXIT(dbal_entry_attribute_get(unit, entry_handle_id, DBAL_ENTRY_ATTR_HITBIT, &lif_hit->val));
        }
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 *  See switch.h
 */
shr_error_e
dnx_switch_interrupt_handles_corrective_action_invalid_destination(
    int unit,
    int block_instance,
    char *msg)
{
    uint32 entry_handle_id;
    uint32 is_destination_invalid = 0, invalid_destination = 0, invalid_destination_source = 0;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(msg, _SHR_E_PARAM, "msg");
    msg[0] = '\0';
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INVALID_DESTINATION, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, block_instance);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_IS_DESTINATION_INVALID, INST_SINGLE, &is_destination_invalid));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_INVALID_DESTINATION, INST_SINGLE, &invalid_destination));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_INVALID_DESTINATION_SOURCE, INST_SINGLE,
                     &invalid_destination_source));

    sal_snprintf(msg, DNXC_INTERRUPT_SPECIAL_MSG_SIZE - 1,
                 "IPPD invalid destination passed to ingress, block %d, is_destination_invalid: %d, invalid_destination: %d, invalid_destination_source: %d",
                 block_instance, is_destination_invalid, invalid_destination, invalid_destination_source);
    /** corrective action, log move invalid destination failure */
    LOG_ERROR(BSL_LS_SOC_INTR, (BSL_META_U(unit, "%s\n"), msg));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Create outlif profile group
 *
 * \param [in] unit - Unit ID
 * \param [in] flags - Flags
 * \param [in] outlif_profile_group - Outlif profile group
 * \param [out] outlif_profile_group_info - Outlif profile group information according to bcm_switch_outlif_profile_group_t
 *
 * \return
 *   shr_error_e - Error type
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_outlif_profile_group_create(
    int unit,
    uint32 flags,
    int *outlif_profile_group,
    bcm_switch_outlif_profile_group_t * outlif_profile_group_info)
{
    return BCM_E_UNAVAIL;
}

/**
 * \brief - Verify function for bcm_dnx_switch_outlif_profile_group_get
 *
 * \param [in] unit - Unit ID
 * \param [in] flags - Flags
 * \param [in] outlif_profile_group - Outlif profile group
 * \param [out] outlif_profile_group_info - Outlif profile group information according to bcm_switch_outlif_profile_group_t
 *
 * \return
 *   shr_error_e - Error type
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_switch_outlif_profile_group_get(
    int unit,
    uint32 flags,
    int outlif_profile_group,
    bcm_switch_outlif_profile_group_t * outlif_profile_group_info)
{
    return BCM_E_UNAVAIL;
}

/**
 *  See switch.h
 */
int
bcm_dnx_switch_outlif_profile_group_destroy(
    int unit,
    int outlif_profile_group)
{
    return BCM_E_UNAVAIL;
}
/* at the end of file */
#undef BSL_LOG_MODULE

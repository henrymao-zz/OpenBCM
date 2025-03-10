/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * File:        hashing.c
 * Purpose:     TH-Hash calcualtions for trunk and ECMP packets.
 */

#include <shared/bsl.h>

#include <soc/drv.h>
#include <soc/hash.h>
#include <bcm/switch.h>
#include <bcm/error.h>

#include <bcm_int/esw_dispatch.h>
#include <bcm_int/esw/firebolt.h>
#include <bcm_int/esw/port.h>
#include <bcm_int/esw/stack.h>
#include <bcm_int/esw/switch.h>
#include <bcm_int/esw/tomahawk.h>

typedef struct bcm_rtag7_base_hash_s {
    uint32 rtag7_hash16_value_a_0;      /* hash a0 result */
    uint32 rtag7_hash16_value_a_1;      /* hash a1 result */
    uint32 rtag7_hash16_value_b_0;      /* hash b0 result */
    uint32 rtag7_hash16_value_b_1;      /* hash b1 result */
    uint32 rtag7_macro_flow_id;         /* hash micro flow result */
    uint32 rtag7_port_lbn;              /* port LBN value from the port table*/
    uint32 rtag7_lbid_hash;             /* LBID hash calculation*/
    bcm_port_t dev_src_port;            /* Local source port */
    bcm_port_t src_port;                /* System source port */
    bcm_module_t src_modid;             /* System source modid */
    uint8 is_nonuc;                     /* Non-unicast */
    uint8 hash_a_valid;                 /* Hash A result use valid input */
    uint8 hash_b_valid;                 /* Hash B result use valid input */
    uint8 lbid_hash_valid;              /* LBID Hash value is valid */
} bcm_rtag7_base_hash_t;

#define   ETHERTYPE_IPV6 0x86dd /* ipv6 ethertype */
#define   ETHERTYPE_IPV4 0x0800 /* ipv4 ethertype */
#define   ETHERTYPE_MIN  0x0600 /* minimum ethertype for hashing */

#define   IP_PROT_TCP 0x6  /* TCP protocol number */
#define   IP_PROT_UDP 0x11 /* TCP protocol number */

#define MODE_REG_HASH     0
#define MODE_RES_HASH     1
#define MODE_RANDOM       2
#define MODE_ROUND_ROBIN  3

#define RTAG7_L2_ONLY         0x0
#define RTAG7_UNKNOWN_HIGIG   0x1
#define RTAG7_MPLS            0x2
#define RTAG7_MIM             0x3
#define RTAG7_IPV4            0x4
#define RTAG7_IPV6            0x5
#define RTAG7_FCOE            0x6
#define RTAG7_TRILL           0x7

#define ENHANCED_HASHING_CONTROLRH_FLOWSET_TABLE_CONFIG_ENCODING_HALF_AND_HALF 0
#define ENHANCED_HASHING_CONTROLRH_FLOWSET_TABLE_CONFIG_ENCODING_ALL_ECMP      1
#define ENHANCED_HASHING_CONTROLRH_FLOWSET_TABLE_CONFIG_ENCODING_ALL_LAG       2

#define RH_LAG_FLOWSET_MOD_ID_SHIFT_VAL 7

#define HASH_VALUE_64_COMPUTE(subfield,offset,width) do { \
        uint64 sf; \
        COMPILER_64_ZERO(sf); \
        COMPILER_64_ADD_64(sf, subfield); \
        COMPILER_64_SHR(subfield, offset); \
        COMPILER_64_SHL(sf, (width - offset)); \
        COMPILER_64_OR(subfield, sf); \
    } while(0)

#define HASH_VALUE_32_COMPUTE(hash_value_32, hash_value_64) do { \
        COMPILER_64_TO_32_LO(hash_value_32, hash_value_64); \
    } while(0)


/*
 * Function:
 *          main_th_do_rtag7_hashing
 * Description:
 *          read hash control register values and
 *          set hash_res' fields
 * Parameters:
 *          unit - StrataSwitch PCI device unit number (driver internal).
 *          pkt_info - ptr to data that has packet information
 *          hash_res - internal data where hashing informaiton is stored
 * Returns:
 *      BCM_E_xxxx
 */
STATIC int
main_th_do_rtag7_hashing(int unit,
                       bcm_switch_pkt_info_t *pkt_info,
                       bcm_rtag7_base_hash_t *hash_res)
{
    /* regular var declaration */
    uint32      hash_src_port;
    uint32      hash_src_modid;
    uint32      rtag7_a_sel;
    bcm_ip_t            sip_a;       /* Source IPv4 address. */
    bcm_ip_t            dip_a;       /* Destination IPv4 address. */
    uint32      rtag7_b_sel;
    bcm_ip_t            sip_b;       /* Source IPv4 address. */
    bcm_ip_t            dip_b;       /* Destination IPv4 address. */
    uint32      hash_field_bmap_a;   /* block A chosen bitmap*/
    uint32      hash_field_bmap_b;   /* block B chosen bitmap*/
    uint32 hash_word[7];
    uint32 hash[13];
    int    elem, elem_bit;
    uint32 hash_element_valid_bits;
    int    sip_valid = FALSE, dip_valid = FALSE;
    uint32 macro_flow_id;

    uint32 hash_crc16_bisync;
    uint32 hash_crc16_ccitt;
    uint32 hash_crc32;
    uint32 hash_crc32_ethernet;
    uint32 hash_crc32_koopman;
    uint32 hash_xor16;
    uint32 hash_xor8;
    uint32 hash_xor4;
    uint32 hash_xor2;
    uint32 hash_xor1;
    uint32 xor32;

    /* register var declaration */
    uint8 rtag7_disable_hash_ipv4_a;
    uint8 rtag7_disable_hash_ipv6_a;
    uint8 rtag7_disable_hash_ipv4_b;
    uint8 rtag7_disable_hash_ipv6_b;
    uint8 rtag7_ipv6_addr_use_lsb_a;
    uint8 rtag7_ipv6_addr_use_lsb_b;
    uint8 rtag7_pre_processing_enable_a;
    uint8 rtag7_pre_processing_enable_b;
    uint8 rtag7_en_flow_label_ipv6_a;
    uint8 rtag7_en_flow_label_ipv6_b;
    uint8 rtag7_en_bin_12_overlay_a;
    uint8 rtag7_en_bin_12_overlay_b;
    uint32 rtag7_hash_seed_a;
    uint32 rtag7_hash_seed_b;
    uint32 rtag7_hash_a0_function_select;
    uint32 rtag7_hash_a1_function_select;
    uint32 rtag7_hash_b0_function_select;
    uint32 rtag7_hash_b1_function_select;
    uint32 rtag7_macro_flow_hash_function_select;
    uint8 rtag7_macro_flow_hash_byte_sel;

    uint64 rtag7_hash_control, rtag7_hash_control_3_64;
    uint32 rtag7_hash_control_2, rtag7_hash_control_3;
    uint32 rtag7_hash_seed_a_reg, rtag7_hash_seed_b_reg;
    soc_reg_t sc_reg;
    soc_field_t sc_field;
    uint32 sc_val;
    int symmetric_hash_control_mask = 0;
    int symmetric_hash_need_swap_ip6 = 0;
    int symmetric_hash_need_swap_ip4 = 0;

    /* read RTAG7 hash control register values */
    SOC_IF_ERROR_RETURN
        (READ_RTAG7_HASH_CONTROLr(unit, &rtag7_hash_control));
    SOC_IF_ERROR_RETURN
        (READ_RTAG7_HASH_CONTROL_2r(unit, &rtag7_hash_control_2));
    if (SOC_IS_TOMAHAWK2(unit) || SOC_IS_TOMAHAWK3(unit)) {
        SOC_IF_ERROR_RETURN
            (READ_RTAG7_HASH_CONTROL_3_64r(unit, &rtag7_hash_control_3_64));
    } else {
        SOC_IF_ERROR_RETURN
            (READ_RTAG7_HASH_CONTROL_3r(unit, &rtag7_hash_control_3));
    }
    SOC_IF_ERROR_RETURN
        (READ_RTAG7_HASH_SEED_Ar(unit, &rtag7_hash_seed_a_reg));
    SOC_IF_ERROR_RETURN
        (READ_RTAG7_HASH_SEED_Br(unit, &rtag7_hash_seed_b_reg));

    /* read RTAG7 fields from hash control registers */
    rtag7_disable_hash_ipv4_a =
        soc_reg64_field32_get(unit, RTAG7_HASH_CONTROLr, rtag7_hash_control,
                          DISABLE_HASH_IPV4_Af);
    rtag7_disable_hash_ipv6_a =
        soc_reg64_field32_get(unit, RTAG7_HASH_CONTROLr, rtag7_hash_control,
                          DISABLE_HASH_IPV6_Af);
    rtag7_disable_hash_ipv4_b =
        soc_reg64_field32_get(unit, RTAG7_HASH_CONTROLr, rtag7_hash_control,
                          DISABLE_HASH_IPV4_Bf);
    rtag7_disable_hash_ipv6_b =
        soc_reg64_field32_get(unit, RTAG7_HASH_CONTROLr, rtag7_hash_control,
                          DISABLE_HASH_IPV6_Bf);
    rtag7_ipv6_addr_use_lsb_a =
        soc_reg64_field32_get(unit, RTAG7_HASH_CONTROLr, rtag7_hash_control,
                          IPV6_COLLAPSED_ADDR_SELECT_Af);
    rtag7_ipv6_addr_use_lsb_b =
        soc_reg64_field32_get(unit, RTAG7_HASH_CONTROLr, rtag7_hash_control,
                          IPV6_COLLAPSED_ADDR_SELECT_Bf);

    /* read RTAG7 fields from hash control3 registers */
    if (SOC_IS_TOMAHAWK2(unit) || SOC_IS_TOMAHAWK3(unit)) {
        rtag7_pre_processing_enable_a =
            soc_reg64_field32_get(unit, RTAG7_HASH_CONTROL_3_64r, rtag7_hash_control_3_64,
                              HASH_PRE_PROCESSING_ENABLE_Af);
        rtag7_pre_processing_enable_b =
            soc_reg64_field32_get(unit, RTAG7_HASH_CONTROL_3_64r, rtag7_hash_control_3_64,
                              HASH_PRE_PROCESSING_ENABLE_Bf);
        rtag7_hash_a0_function_select =
            soc_reg64_field32_get(unit, RTAG7_HASH_CONTROL_3_64r, rtag7_hash_control_3_64,
                              HASH_A0_FUNCTION_SELECTf);
        rtag7_hash_a1_function_select =
            soc_reg64_field32_get(unit, RTAG7_HASH_CONTROL_3_64r, rtag7_hash_control_3_64,
                              HASH_A1_FUNCTION_SELECTf);
        rtag7_hash_b0_function_select =
            soc_reg64_field32_get(unit, RTAG7_HASH_CONTROL_3_64r, rtag7_hash_control_3_64,
                              HASH_B0_FUNCTION_SELECTf);
        rtag7_hash_b1_function_select =
            soc_reg64_field32_get(unit, RTAG7_HASH_CONTROL_3_64r, rtag7_hash_control_3_64,
                              HASH_B1_FUNCTION_SELECTf);
    } else {
        rtag7_pre_processing_enable_a =
            soc_reg_field_get(unit, RTAG7_HASH_CONTROL_3r, rtag7_hash_control_3,
                              HASH_PRE_PROCESSING_ENABLE_Af);
        rtag7_pre_processing_enable_b =
            soc_reg_field_get(unit, RTAG7_HASH_CONTROL_3r, rtag7_hash_control_3,
                              HASH_PRE_PROCESSING_ENABLE_Bf);
        rtag7_hash_a0_function_select =
            soc_reg_field_get(unit, RTAG7_HASH_CONTROL_3r, rtag7_hash_control_3,
                              HASH_A0_FUNCTION_SELECTf);
        rtag7_hash_a1_function_select =
            soc_reg_field_get(unit, RTAG7_HASH_CONTROL_3r, rtag7_hash_control_3,
                              HASH_A1_FUNCTION_SELECTf);
        rtag7_hash_b0_function_select =
            soc_reg_field_get(unit, RTAG7_HASH_CONTROL_3r, rtag7_hash_control_3,
                              HASH_B0_FUNCTION_SELECTf);
        rtag7_hash_b1_function_select =
            soc_reg_field_get(unit, RTAG7_HASH_CONTROL_3r, rtag7_hash_control_3,
                              HASH_B1_FUNCTION_SELECTf);
    }

    /* read RTAG7 fields from hash control2 registers */
    rtag7_en_flow_label_ipv6_a =
        soc_reg_field_get(unit, RTAG7_HASH_CONTROL_2r, rtag7_hash_control_2,
                          ENABLE_FLOW_LABEL_IPV6_Af);
    rtag7_en_flow_label_ipv6_b =
        soc_reg_field_get(unit, RTAG7_HASH_CONTROL_2r, rtag7_hash_control_2,
                          ENABLE_FLOW_LABEL_IPV6_Bf);
    rtag7_en_bin_12_overlay_a =
        soc_reg_field_get(unit, RTAG7_HASH_CONTROL_2r, rtag7_hash_control_2,
                          ENABLE_BIN_12_OVERLAY_Af);
    rtag7_en_bin_12_overlay_b =
        soc_reg_field_get(unit, RTAG7_HASH_CONTROL_2r, rtag7_hash_control_2,
                          ENABLE_BIN_12_OVERLAY_Bf);
    rtag7_macro_flow_hash_function_select =
        soc_reg_field_get(unit, RTAG7_HASH_CONTROL_2r, rtag7_hash_control_2,
                          MACRO_FLOW_HASH_FUNC_SELf);
    rtag7_macro_flow_hash_byte_sel =
        soc_reg_field_get(unit, RTAG7_HASH_CONTROL_2r, rtag7_hash_control_2,
                          MACRO_FLOW_HASH_BYTE_SELf);

    /* read RTAG7 fields from hash seed registers */
    rtag7_hash_seed_a =
        soc_reg_field_get(unit, RTAG7_HASH_SEED_Ar, rtag7_hash_seed_a_reg,
                          HASH_SEED_Af);
    rtag7_hash_seed_b =
        soc_reg_field_get(unit, RTAG7_HASH_SEED_Br, rtag7_hash_seed_b_reg,
                          HASH_SEED_Bf);
    if (BCM_SUCCESS(bcm_esw_switch_control_get(unit,
            bcmSwitchSymmetricHashControl, &symmetric_hash_control_mask))) {
        if (symmetric_hash_control_mask &
            (BCM_SYMMETRIC_HASH_0_IP6_ENABLE | BCM_SYMMETRIC_HASH_1_IP6_ENABLE)) {
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_IPV6) &&
                _BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_IPV6) &&
                (sal_memcmp(pkt_info->sip6, pkt_info->dip6, BCM_IP6_ADDRLEN) < 0)) {
                symmetric_hash_need_swap_ip6 = 1;
            }
        }
        if (symmetric_hash_control_mask &
            (BCM_SYMMETRIC_HASH_0_IP4_ENABLE | BCM_SYMMETRIC_HASH_1_IP4_ENABLE)) {
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_IP) &&
                _BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_IP) &&
                (pkt_info->sip < pkt_info->dip)) {
                symmetric_hash_need_swap_ip4 = 1;
            }
        }
    }
    /* RTAG7 tables */
    /* the first step is to choose the paket type and to fold the ipv6
     * addresses in case of IPv6 packet*/

    /* option A ip folding for rtag 7 */
    if ((_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, ETHERTYPE) &&
         (pkt_info->ethertype == ETHERTYPE_IPV6)) &&
               (rtag7_disable_hash_ipv6_a == 0)) {

        rtag7_a_sel = RTAG7_IPV6;

        /* This section will fold the Ipv6 address to single 32 bit address
         * by using of of the methose LSB or xor */
        if (rtag7_ipv6_addr_use_lsb_a) {
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_IPV6)) {
                sip_a = (pkt_info->sip6[12] << 24) |
                    (pkt_info->sip6[13] << 16) |
                    (pkt_info->sip6[14] << 8) |
                    (pkt_info->sip6[15]);
                sip_valid = TRUE;
            } else {
                sip_a = 0;
            }
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_IPV6)) {
                dip_a = (pkt_info->dip6[12] << 24) |
                    (pkt_info->dip6[13] << 16) |
                    (pkt_info->dip6[14] << 8) |
                    (pkt_info->dip6[15]);
                dip_valid = TRUE;
            } else {
                dip_a = 0;
            }
        } else {
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_IPV6)) {
                sip_a =
                    ((pkt_info->sip6[12] << 24) |
                     (pkt_info->sip6[13] << 16) |
                     (pkt_info->sip6[14] << 8) |
                     (pkt_info->sip6[15])) ^
                    ((pkt_info->sip6[8] << 24) |
                     (pkt_info->sip6[9] << 16) |
                     (pkt_info->sip6[10] << 8) |
                     (pkt_info->sip6[11])) ^
                    ((pkt_info->sip6[4] << 24) |
                     (pkt_info->sip6[5] << 16) |
                     (pkt_info->sip6[6] << 8) |
                     (pkt_info->sip6[7])) ^
                    ((pkt_info->sip6[0] << 24) |
                     (pkt_info->sip6[1] << 16) |
                     (pkt_info->sip6[2] << 8) |
                     (pkt_info->sip6[3]));
                sip_valid = TRUE;
            } else {
                sip_a = 0;
            }

            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_IPV6)) {
                dip_a =
                    ((pkt_info->dip6[12] << 24) |
                     (pkt_info->dip6[13] << 16) |
                     (pkt_info->dip6[14] << 8) |
                     (pkt_info->dip6[15])) ^
                    ((pkt_info->dip6[8] << 24) |
                     (pkt_info->dip6[9] << 16) |
                     (pkt_info->dip6[10] << 8) |
                     (pkt_info->dip6[11])) ^
                    ((pkt_info->dip6[4] << 24) |
                     (pkt_info->dip6[5] << 16) |
                     (pkt_info->dip6[6] << 8) |
                     (pkt_info->dip6[7])) ^
                    ((pkt_info->dip6[0] << 24) |
                     (pkt_info->dip6[1] << 16) |
                     (pkt_info->dip6[2] << 8) |
                     (pkt_info->dip6[3]));
                dip_valid = TRUE;
            } else {
                dip_a = 0;
            }
        }
    } else if ((_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, ETHERTYPE) &&
                (pkt_info->ethertype == ETHERTYPE_IPV4)) &&
               (rtag7_disable_hash_ipv4_a == 0)) {

        rtag7_a_sel = RTAG7_IPV4;

        /* only one IPv4 hdr */
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_IP)) {
            sip_a = pkt_info->sip;
            sip_valid = TRUE;
        } else {
            sip_a = 0;
        }
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_IP)) {
            dip_a = pkt_info->dip;
            dip_valid = TRUE;
        } else {
            dip_a = 0;
        }
    } else {
        rtag7_a_sel = RTAG7_L2_ONLY;
        sip_a = dip_a = 0;
    }

    /* End of option A ip folding for rtag 7 */

    /* option B ip folding for rtag 7 */
    if ((_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, ETHERTYPE) &&
         (pkt_info->ethertype == ETHERTYPE_IPV6)) &&
               (rtag7_disable_hash_ipv6_b == 0)) {

        rtag7_b_sel = RTAG7_IPV6;

        /* This section will fold the Ipv6 address to single 32 bit address
         * by using of of the methose LSB or xor */
        if (rtag7_ipv6_addr_use_lsb_b) {
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_IPV6)) {
                sip_b = (pkt_info->sip6[12] << 24) |
                    (pkt_info->sip6[13] << 16) |
                    (pkt_info->sip6[14] << 8) |
                    (pkt_info->sip6[15]);
                sip_valid = TRUE;
            } else {
                sip_b = 0;
            }
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_IPV6)) {
                dip_b = (pkt_info->dip6[12] << 24) |
                    (pkt_info->dip6[13] << 16) |
                    (pkt_info->dip6[14] << 8) |
                    (pkt_info->dip6[15]);
                dip_valid = TRUE;
            } else {
                dip_b = 0;
            }
        } else {
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_IPV6)) {
                sip_b =
                    ((pkt_info->sip6[12] << 24) |
                     (pkt_info->sip6[13] << 16) |
                     (pkt_info->sip6[14] << 8) |
                     (pkt_info->sip6[15])) ^
                    ((pkt_info->sip6[8] << 24) |
                     (pkt_info->sip6[9] << 16) |
                     (pkt_info->sip6[10] << 8) |
                     (pkt_info->sip6[11])) ^
                    ((pkt_info->sip6[4] << 24) |
                     (pkt_info->sip6[5] << 16) |
                     (pkt_info->sip6[6] << 8) |
                     (pkt_info->sip6[7])) ^
                    ((pkt_info->sip6[0] << 24) |
                     (pkt_info->sip6[1] << 16) |
                     (pkt_info->sip6[2] << 8) |
                     (pkt_info->sip6[3]));
                sip_valid = TRUE;
            } else {
                sip_b = 0;
            }

            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_IPV6)) {
                dip_b =
                    ((pkt_info->dip6[12] << 24) |
                     (pkt_info->dip6[13] << 16) |
                     (pkt_info->dip6[14] << 8) |
                     (pkt_info->dip6[15])) ^
                    ((pkt_info->dip6[8] << 24) |
                     (pkt_info->dip6[9] << 16) |
                     (pkt_info->dip6[10] << 8) |
                     (pkt_info->dip6[11])) ^
                    ((pkt_info->dip6[4] << 24) |
                     (pkt_info->dip6[5] << 16) |
                     (pkt_info->dip6[6] << 8) |
                     (pkt_info->dip6[7])) ^
                    ((pkt_info->dip6[0] << 24) |
                     (pkt_info->dip6[1] << 16) |
                     (pkt_info->dip6[2] << 8) |
                     (pkt_info->dip6[3]));
                dip_valid = TRUE;
            } else {
                dip_b = 0;
            }
        }
    } else if ((_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, ETHERTYPE) &&
                (pkt_info->ethertype == ETHERTYPE_IPV4)) &&
               (rtag7_disable_hash_ipv4_b == 0)) {

        rtag7_b_sel = RTAG7_IPV4;

        /* only one IPv4 hdr */
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_IP)) {
            sip_b = pkt_info->sip;
            sip_valid = TRUE;
        } else {
            sip_b = 0;
        }
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_IP)) {
            dip_b = pkt_info->dip;
            dip_valid = TRUE;
        } else {
            dip_b = 0;
        }
    } else {
        rtag7_b_sel = RTAG7_L2_ONLY;
        sip_b = dip_b = 0;
    }
    /* End of option B ip folding for rtag 7 */

    /*
     * =============
     * RTAG7 HASHING
     * =============
     */

    /* The inputs to the RTAG7 hash function were reduced in the begining
     * of this function.
     * This logic takes the hash inputs and computes both A and B RTAG7
     * hash values.
     */

    /* Change source modid/port to PORT32 space for hashing */
    hash_src_port  = hash_res->src_port;
    hash_src_modid = hash_res->src_modid;

    /* Only if the packet was sourced by this chip, make sure to use
     * PORT32 space modid and port if dual modid is enabled
     * Need to do this because of front panel ports.
     */

    /* initialize the variables */
    sal_memset(hash,0x0,(sizeof(uint32))*13);
    sal_memset(hash_word,0x0,(sizeof(uint32))*7);

    hash_crc16_bisync = 0;
    hash_crc16_ccitt = 0;
    hash_crc32      = 0;
    hash_xor16      = 0;
    hash_xor8       = 0;
    hash_xor4       = 0;
    hash_xor2       = 0;
    hash_xor1       = 0;
    xor32           = 0;

    hash[12] = 0;
    hash[3] = hash_src_port;
    hash[2] = hash_src_modid & 0xff;
    hash[1] = 0;
    hash[0] = 0;

    hash_element_valid_bits = 0x1fff; /* Init to valid fields above */

    /* option A hash calculation for rtag 7 */

    if ((rtag7_a_sel == RTAG7_IPV6) || (rtag7_a_sel == RTAG7_IPV4)) {

        if (sip_valid) {
            hash[11] = (sip_a >> 16) & 0xffff;
            hash[10] =  sip_a & 0xffff;
        } else {
            hash_element_valid_bits &= ~0xc00;
        }
        if (dip_valid) {
            hash[9]  = (dip_a >> 16) & 0xffff;
            hash[8]  =  dip_a & 0xffff;
        } else {
            hash_element_valid_bits &= ~0x300;
        }

        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, VLAN)) {
            hash[7]  = pkt_info->vid & 0xfff;
        } else {
            hash_element_valid_bits &= ~0x80;
        }
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_L4_PORT)) {
            hash[6]  = pkt_info->src_l4_port;
        } else {
            hash_element_valid_bits &= ~0x40;
        }
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_L4_PORT)) {
            hash[5]  = pkt_info->dst_l4_port;
        } else {
            hash_element_valid_bits &= ~0x20;
        }
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, PROTOCOL)) {
            hash[4]  = pkt_info->protocol;
        } else {
            hash_element_valid_bits &= ~0x10;
        }

        /* Symmetric hash swap src/dst ipaddr/l4_port for option A */
        if (((rtag7_a_sel == RTAG7_IPV6) &&
            symmetric_hash_need_swap_ip6 &&
            (symmetric_hash_control_mask & BCM_SYMMETRIC_HASH_0_IP6_ENABLE))
            ||
            ((rtag7_a_sel == RTAG7_IPV4) &&
            symmetric_hash_need_swap_ip4 &&
            (symmetric_hash_control_mask & BCM_SYMMETRIC_HASH_0_IP4_ENABLE))) {

            uint32 temp;
            temp = hash[11]; hash[11] = hash[9]; hash[9] = temp;
            temp = hash[10]; hash[10] = hash[8]; hash[8] = temp;
            temp = hash[6]; hash[6] = hash[5]; hash[5] = temp;
            LOG_VERBOSE(BSL_LS_BCM_COMMON,
                        (BSL_META_U(unit,
                                    "Symmetric hash swap for hash A calculation.\n")));
        }

        if ((rtag7_a_sel == RTAG7_IPV6) && rtag7_en_flow_label_ipv6_a) {
            LOG_VERBOSE(BSL_LS_BCM_COMMON,
                        (BSL_META_U(unit,
                                    "Hash calculation: The system is set to use ipv6 flow label"
                                     " and the code can't get this info\n")));
        }

        if (rtag7_a_sel == RTAG7_IPV4) {  /* Use IPv4 BITMAPs */
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, PROTOCOL) &&
                ((pkt_info->protocol == IP_PROT_TCP) ||
                (pkt_info->protocol == IP_PROT_UDP))) {
                if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_L4_PORT) &&
                    _BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_L4_PORT) &&
                    (pkt_info->src_l4_port == pkt_info->dst_l4_port)) {
                    sc_reg = RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_1r;
                    sc_field = IPV4_TCP_UDP_SRC_EQ_DST_FIELD_BITMAP_Af;
                    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                                (BSL_META_U(unit,
                                            "Hash calculation: Bitmap is block A IPv4 TCP=UDP\n")));
                } else {
                    sc_reg = RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_2r;
                    sc_field = IPV4_TCP_UDP_FIELD_BITMAP_Af;
                    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                                (BSL_META_U(unit,
                                            "Hash calculation: Bitmap is block A IPv4 L4 tcp/udp\n")));
                }
            } else {
                sc_reg = RTAG7_HASH_FIELD_BMAP_1r;
                sc_field = IPV4_FIELD_BITMAP_Af;
                LOG_VERBOSE(BSL_LS_BCM_COMMON,
                            (BSL_META_U(unit,
                                        "Hash calculation: Bitmap is block A IPv4 \n")));
            }

        } else { /* Use IPv6 BITMAPs */
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, PROTOCOL) &&
                ((pkt_info->protocol == IP_PROT_TCP) ||
                (pkt_info->protocol == IP_PROT_UDP))) {
                if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_L4_PORT) &&
                    _BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_L4_PORT) &&
                    (pkt_info->src_l4_port == pkt_info->dst_l4_port)) {
                    sc_reg = RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_1r;
                    sc_field = IPV6_TCP_UDP_SRC_EQ_DST_FIELD_BITMAP_Af;
                    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                                (BSL_META_U(unit,
                                            "Hash calculation: Bitmap is block A IPv6 TCP=UDP\n")));
                } else {
                    sc_reg = RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_2r;
                    sc_field = IPV6_TCP_UDP_FIELD_BITMAP_Af;
                    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                                (BSL_META_U(unit,
                                            "Hash calculation: Bitmap is block A IPv6 L4 tcp/udp\n")));
                }
            } else {
                sc_reg = RTAG7_HASH_FIELD_BMAP_2r;
                sc_field = IPV6_FIELD_BITMAP_Af;
                LOG_VERBOSE(BSL_LS_BCM_COMMON,
                            (BSL_META_U(unit,
                                        "Hash calculation: Bitmap is block A IPv6 \n")));
            }
        }
    } else { /* Catch-all for RTAG7_L2_ONLY */
        /* L2 only hash key */
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_MAC)) {
            hash[11] = (pkt_info->src_mac[0] << 8) | pkt_info->src_mac[1];
            hash[10] = (pkt_info->src_mac[2] << 8) | pkt_info->src_mac[3];
            hash[9] = (pkt_info->src_mac[4] << 8) | pkt_info->src_mac[5];
        } else {
            hash_element_valid_bits &= ~0xe00;
        }
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_MAC)) {
            hash[8] = (pkt_info->dst_mac[0] << 8) | pkt_info->dst_mac[1];
            hash[7] = (pkt_info->dst_mac[2] << 8) | pkt_info->dst_mac[3];
            hash[6] = (pkt_info->dst_mac[4] << 8) | pkt_info->dst_mac[5];
        } else {
            hash_element_valid_bits &= ~0x1c0;
        }

        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, ETHERTYPE)) {
            hash[5] = (pkt_info->ethertype >= ETHERTYPE_MIN) ?
                pkt_info->ethertype : 0;
        } else {
            hash_element_valid_bits &= ~0x20;
        }

        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, VLAN)) {
            hash[4] = pkt_info->vid & 0xfff;
        } else {
            hash_element_valid_bits &= ~0x10;
        }

        sc_reg = RTAG7_HASH_FIELD_BMAP_3r;
        sc_field = L2_FIELD_BITMAP_Af;
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "Hash calculation: Bitmap is block A L2\n")));
    }

    BCM_IF_ERROR_RETURN
        (soc_reg32_get(unit, sc_reg, REG_PORT_ANY, 0, &sc_val));
    hash_field_bmap_a = soc_reg_field_get(unit, sc_reg, sc_val, sc_field);

    /* Pre-Processing */

    if (rtag7_pre_processing_enable_a) {

        hash[12] = hash[12] ^ (hash[12] >> 3) ^ (hash[12] << 2);
        hash[11] = hash[11] ^ (hash[11] >> 3) ^ (hash[11] << 2);
        hash[10] = hash[10] ^ (hash[10] >> 3) ^ (hash[10] << 2);
        hash[9] = hash[9] ^ (hash[9] >> 3) ^ (hash[9] << 2);
        hash[8] = hash[8] ^ (hash[8] >> 3) ^ (hash[8] << 2);
        hash[7] = hash[7] ^ (hash[7] >> 3) ^ (hash[7] << 2);
        hash[6] = hash[6] ^ (hash[6] >> 3) ^ (hash[6] << 2);
        hash[5] = hash[5] ^ (hash[5] >> 3) ^ (hash[5] << 2);
        hash[4] = hash[4] ^ (hash[4] >> 3) ^ (hash[4] << 2);
        hash[3] = hash[3] ^ (hash[3] >> 3) ^ (hash[3] << 2);
        hash[2] = hash[2] ^ (hash[2] >> 3) ^ (hash[2] << 2);
        hash[1] = hash[1] ^ (hash[1] >> 3) ^ (hash[1] << 2);
        hash[0] = hash[0] ^ (hash[0] >> 3) ^ (hash[0] << 2);
    }

    if (((hash_field_bmap_a >> 12) & 0x1) == 0) {
        hash[12] = 0;
    }

    if (rtag7_en_bin_12_overlay_a) {
        hash_word[6] = (rtag7_hash_seed_a & 0xffff0000) | (hash[12] & 0xffff);
    } else {
        hash_word[6] = rtag7_hash_seed_a;
    }

    hash_res->hash_a_valid = TRUE;
    for (elem = 11; elem >= 0; elem--) {
        elem_bit = 1 << elem;
        if (0 != (hash_field_bmap_a & elem_bit)) {
            if (0 != (hash_element_valid_bits & elem_bit)) {
                hash_word[elem/2] |=
                    ((hash[elem] & 0xffff) << (16 * (elem % 2)));
            } else {
                hash_res->hash_a_valid = FALSE;
                break;
            }
        }
    }

    /*Calculation*/
    xor32 = hash_word[6] ^ hash_word[5] ^ hash_word[4] ^ hash_word[3] ^
        hash_word[2] ^ hash_word[1] ^ hash_word[0];

    hash_xor16 = (xor32 & 0xffff) ^ ((xor32 >> 16) & 0xffff);
    hash_xor8 = (hash_xor16 & 0xff) ^ ((hash_xor16 >> 8) & 0xff);
    hash_xor4 = (hash_xor8 & 0xf) ^ ((hash_xor8 >> 4) & 0xf);
    hash_xor2 = (hash_xor4 & 0x3) ^ ((hash_xor4 >> 2) & 0x3);
    hash_xor1 = (hash_xor2 & 0x1) ^ ((hash_xor2 >> 1) & 0x1);

    hash_crc16_bisync = _shr_crc16_draco_array(hash_word, 28);
    hash_crc16_ccitt =  _shr_crc16_ccitt_array(hash_word, 28);
    hash_crc32 =        _shr_crc32_castagnoli_array(hash_word, 28);
    hash_crc32_ethernet = _shr_crc32_ethernet_array(hash_word, 28);
    hash_crc32_koopman = _shr_crc32_koopman_array(hash_word, 28);

    switch (rtag7_hash_a0_function_select) {
    case 0: /* reserved */
        hash_res->rtag7_hash16_value_a_0 = 0;
        break;
    case 1: /* reserved */
        hash_res->rtag7_hash16_value_a_0 = 0;
        break;
    case 2: /* reserved */
        hash_res->rtag7_hash16_value_a_0 = 0;
        break;
    case 3: /* CRC16 BISYNC */
        hash_res->rtag7_hash16_value_a_0 = hash_crc16_bisync;
        break;
    case 4: /* CRC16_XOR1 */
        hash_res->rtag7_hash16_value_a_0 = hash_xor1 & 0x1;
        hash_res->rtag7_hash16_value_a_0 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 5: /* CRC16_XOR2 */
        hash_res->rtag7_hash16_value_a_0 = hash_xor2 & 0x3;
        hash_res->rtag7_hash16_value_a_0 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 6: /* CRC16_XOR4 */
        hash_res->rtag7_hash16_value_a_0 = hash_xor4 & 0xf;
        hash_res->rtag7_hash16_value_a_0 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 7: /* CRC16_XOR8 */
        hash_res->rtag7_hash16_value_a_0 = hash_xor8 & 0xff;
        hash_res->rtag7_hash16_value_a_0 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 8: /* XOR16 */
        hash_res->rtag7_hash16_value_a_0 = hash_xor16;
        break;
    case 9: /* CRC16_CCITT */
        hash_res->rtag7_hash16_value_a_0 = hash_crc16_ccitt;
        break;
    case 10: /* CRC32_LO */
        hash_res->rtag7_hash16_value_a_0 = hash_crc32 & 0xffff;
        break;
    case 11: /* CRC32_HI */
        hash_res->rtag7_hash16_value_a_0 = (hash_crc32 >> 16) & 0xffff;
        break;
    case 12: /* CRC32_Ethernet_LO */
        hash_res->rtag7_hash16_value_a_0 = hash_crc32_ethernet & 0xffff;
        break;
    case 13: /* CRC32_Ethernet_HI */
        hash_res->rtag7_hash16_value_a_0 = (hash_crc32_ethernet >> 16) & 0xffff;
        break;
    case 14: /* CRC32_Koopman_LO */
        hash_res->rtag7_hash16_value_a_0 = hash_crc32_koopman & 0xffff;
        break;
    case 15: /* CRC32_Koopman_HI */
        hash_res->rtag7_hash16_value_a_0 = (hash_crc32_koopman >> 16) & 0xffff;
        break;
    default: /* reserved */
        hash_res->rtag7_hash16_value_a_0 = 0;
        break;
    }

    switch (rtag7_hash_a1_function_select) {
    case 0: /* reserved */
        hash_res->rtag7_hash16_value_a_1 = 0;
        break;
    case 1: /* reserved */
        hash_res->rtag7_hash16_value_a_1 = 0;
        break;
    case 2: /* reserved */
        hash_res->rtag7_hash16_value_a_1 = 0;
        break;
    case 3: /* CRC16 BISYNC */
        hash_res->rtag7_hash16_value_a_1 = hash_crc16_bisync;
        break;
    case 4: /* CRC16_XOR1 */
        hash_res->rtag7_hash16_value_a_1 = hash_xor1 & 0x1;
        hash_res->rtag7_hash16_value_a_1 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 5: /* CRC16_XOR2 */
        hash_res->rtag7_hash16_value_a_1 = hash_xor2 & 0x3;
        hash_res->rtag7_hash16_value_a_1 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 6: /* CRC16_XOR4 */
        hash_res->rtag7_hash16_value_a_1 = hash_xor4 & 0xf;
        hash_res->rtag7_hash16_value_a_1 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 7: /* CRC16_XOR8 */
        hash_res->rtag7_hash16_value_a_1 = hash_xor8 & 0xff;
        hash_res->rtag7_hash16_value_a_1 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 8: /* XOR16 */
        hash_res->rtag7_hash16_value_a_1 = hash_xor16;
        break;
    case 9: /* CRC16_CCITT */
        hash_res->rtag7_hash16_value_a_1 = hash_crc16_ccitt;
        break;
    case 10: /* CRC32_LO */
        hash_res->rtag7_hash16_value_a_1 = hash_crc32 & 0xffff;
        break;
    case 11: /* CRC32_HI */
        hash_res->rtag7_hash16_value_a_1 = (hash_crc32 >> 16) & 0xffff;
        break;
    case 12: /* CRC32_Ethernet_LO */
        hash_res->rtag7_hash16_value_a_1 = hash_crc32_ethernet & 0xffff;
        break;
    case 13: /* CRC32_Ethernet_HI */
        hash_res->rtag7_hash16_value_a_1 = (hash_crc32_ethernet >> 16) & 0xffff;
        break;
    case 14: /* CRC32_Koopman_LO */
        hash_res->rtag7_hash16_value_a_1 = hash_crc32_koopman & 0xffff;
        break;
    case 15: /* CRC32_Koopman_HI */
        hash_res->rtag7_hash16_value_a_1 = (hash_crc32_koopman >> 16) & 0xffff;
        break;
    default: /* reserved */
        hash_res->rtag7_hash16_value_a_1 = 0;
        break;
    }

    /* End of option A hash calculation for rtag 7 */

    /* Generation of Macro Flow Based HASH Select */
    /* This is used for Macro flow based Hash function selection for all consumers of RTAG7 HASH */
    /* Macro flow based hash function selection improves distribution among members */
    /* Refer Each application (ECMP, LAG, HG-TRUNK) on how this is being used */
    switch (rtag7_macro_flow_hash_function_select) {
    case 0: /* reserved */
        macro_flow_id = 0;
        break;
    case 1: /* reserved */
        macro_flow_id = 0;
        break;
    case 2: /* reserved */
        macro_flow_id = 0;
        break;
    case 3: /* CRC16 BISYNC */
        macro_flow_id = hash_crc16_bisync;
        break;
    case 4: /* CRC16_XOR1 */
        macro_flow_id = hash_xor1 & 0x1;
        macro_flow_id |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 5: /* CRC16_XOR2 */
        macro_flow_id = hash_xor2 & 0x3;
        macro_flow_id |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 6: /* CRC16_XOR4 */
        macro_flow_id = hash_xor4 & 0xf;
        macro_flow_id |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 7: /* CRC16_XOR8 */
        macro_flow_id = hash_xor8 & 0xff;
        macro_flow_id |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 8: /* XOR16 */
        macro_flow_id = hash_xor16;
        break;
    case 9: /* CRC16_CCITT */
        macro_flow_id = hash_crc16_ccitt;
        break;
    case 10: /* CRC32_LO */
        macro_flow_id = hash_crc32 & 0xffff;
        break;
    case 11: /* CRC32_HI */
        macro_flow_id = (hash_crc32 >> 16) & 0xffff;
        break;
    case 12: /* CRC32_Ethernet_LO */
        macro_flow_id = hash_crc32_ethernet & 0xffff;
        break;
    case 13: /* CRC32_Ethernet_HI */
        macro_flow_id = (hash_crc32_ethernet >> 16) & 0xffff;
        break;
    case 14: /* CRC32_Koopman_LO */
        macro_flow_id = hash_crc32_koopman & 0xffff;
        break;
    case 15: /* CRC32_Koopman_HI */
        macro_flow_id = (hash_crc32_koopman >> 16) & 0xffff;
        break;
    default: /* reserved */
        macro_flow_id = 0;
        break;
    }
    hash_res->rtag7_macro_flow_id = (rtag7_macro_flow_hash_byte_sel) ?
        ((macro_flow_id >> 8) & 0xff) : (macro_flow_id & 0xff);

    /* option B hash calculation for rtag 7 */

    /* initialize the variables */
    sal_memset(hash,0x0,(sizeof(uint32))*13);
    sal_memset(hash_word,0x0,(sizeof(uint32))*7);

    hash_crc16_bisync = 0;
    hash_crc16_ccitt = 0;
    hash_crc32      = 0;
    hash_xor16      = 0;
    hash_xor8       = 0;
    hash_xor4       = 0;
    hash_xor2       = 0;
    hash_xor1       = 0;
    xor32           = 0;

    hash[12] = 0;
    hash[3] = hash_src_port;
    hash[2] = hash_src_modid & 0xff;
    hash[1] = 0;
    hash[0] = 0;

    hash_element_valid_bits = 0x1fff; /* Init to valid fields above */

    /* option B hash calculation for rtag 7 */

    if ((rtag7_b_sel == RTAG7_IPV6) || (rtag7_b_sel == RTAG7_IPV4)) {
        if (sip_valid) {
            hash[11] = (sip_b >> 16) & 0xffff;
            hash[10] =  sip_b & 0xffff;
        } else {
            hash_element_valid_bits &= ~0xc00;
        }
        if (dip_valid) {
            hash[9]  = (dip_b >> 16) & 0xffff;
            hash[8]  =  dip_b & 0xffff;
        } else {
            hash_element_valid_bits &= ~0x300;
        }

        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, VLAN)) {
            hash[7]  = pkt_info->vid & 0xfff;
        } else {
            hash_element_valid_bits &= ~0x80;
        }
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_L4_PORT)) {
            hash[6]  = pkt_info->src_l4_port;
        } else {
            hash_element_valid_bits &= ~0x40;
        }
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_L4_PORT)) {
            hash[5]  = pkt_info->dst_l4_port;
        } else {
            hash_element_valid_bits &= ~0x20;
        }
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, PROTOCOL)) {
            hash[4]  = pkt_info->protocol;
        } else {
            hash_element_valid_bits &= ~0x10;
        }

        /* Symmetric hash swap src/dst ipaddr/l4_port for option B */
        if (((rtag7_b_sel == RTAG7_IPV6) &&
            symmetric_hash_need_swap_ip6 &&
            (symmetric_hash_control_mask & BCM_SYMMETRIC_HASH_1_IP6_ENABLE))
            ||
            ((rtag7_b_sel == RTAG7_IPV4) &&
            symmetric_hash_need_swap_ip4 &&
            (symmetric_hash_control_mask & BCM_SYMMETRIC_HASH_1_IP4_ENABLE))) {

            uint32 temp;
            temp = hash[11]; hash[11] = hash[9]; hash[9] = temp;
            temp = hash[10]; hash[10] = hash[8]; hash[8] = temp;
            temp = hash[6]; hash[6] = hash[5]; hash[5] = temp;
            LOG_VERBOSE(BSL_LS_BCM_COMMON,
                        (BSL_META_U(unit,
                                    "Symmetric hash swap for hash B calculation.\n")));
        }

        if ((rtag7_b_sel == RTAG7_IPV6) && rtag7_en_flow_label_ipv6_b) {
            LOG_VERBOSE(BSL_LS_BCM_COMMON,
                        (BSL_META_U(unit,
                                    "Hash calculation: The system is set to use ipv6 flow label"
                                     " and the code can't get this info\n")));
        }

        if (rtag7_b_sel == RTAG7_IPV4) {  /* Use IPv4 BITMAPs */
            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, PROTOCOL) &&
                ((pkt_info->protocol == IP_PROT_TCP) ||
                (pkt_info->protocol == IP_PROT_UDP))) {
                if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_L4_PORT) &&
                    _BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_L4_PORT) &&
                    (pkt_info->src_l4_port == pkt_info->dst_l4_port)) {
                    sc_reg = RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_1r;
                    sc_field = IPV4_TCP_UDP_SRC_EQ_DST_FIELD_BITMAP_Bf;
                    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                                (BSL_META_U(unit,
                                            "Hash calculation: Bitmap is block B IPv4 TCP=UDP\n")));
                } else {
                    sc_reg = RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_2r;
                    sc_field = IPV4_TCP_UDP_FIELD_BITMAP_Bf;
                    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                                (BSL_META_U(unit,
                                            "Hash calculation: Bitmap is block B IPv4 L4 tcp/udp\n")));
                }
            } else {
                sc_reg = RTAG7_HASH_FIELD_BMAP_1r;
                sc_field = IPV4_FIELD_BITMAP_Bf;
                LOG_VERBOSE(BSL_LS_BCM_COMMON,
                            (BSL_META_U(unit,
                                        "Hash calculation: Bitmap is block B IPv4\n")));
            }

        } else { /* Use IPv6 BITMAPs */

            if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, PROTOCOL) &&
                ((pkt_info->protocol == IP_PROT_TCP) ||
                (pkt_info->protocol == IP_PROT_UDP))) {
                if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_L4_PORT) &&
                    _BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_L4_PORT) &&
                    (pkt_info->src_l4_port == pkt_info->dst_l4_port)) {
                    sc_reg = RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_1r;
                    sc_field = IPV6_TCP_UDP_SRC_EQ_DST_FIELD_BITMAP_Bf;
                    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                                (BSL_META_U(unit,
                                            "Hash calculation: Bitmap is block B IPv6 TCP=UDP\n")));
                } else {
                    sc_reg = RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_2r;
                    sc_field = IPV6_TCP_UDP_FIELD_BITMAP_Bf;
                    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                                (BSL_META_U(unit,
                                            "Hash calculation: Bitmap is block B IPv6 TCP=UDP\n")));
                }
            } else {
                sc_reg = RTAG7_HASH_FIELD_BMAP_2r;
                sc_field = IPV6_FIELD_BITMAP_Bf;
                LOG_VERBOSE(BSL_LS_BCM_COMMON,
                            (BSL_META_U(unit,
                                        "Hash calculation: Bitmap is block B IPv6\n")));
            }
        }
    } else { /* Catch-all for RTAG7_L2_ONLY */

        /* L2 only hash key */
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_MAC)) {
            hash[11] = (pkt_info->src_mac[0] << 8) | pkt_info->src_mac[1];
            hash[10] = (pkt_info->src_mac[2] << 8) | pkt_info->src_mac[3];
            hash[9] = (pkt_info->src_mac[4] << 8) | pkt_info->src_mac[5];
        } else {
            hash_element_valid_bits &= ~0xe00;
        }
        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, DST_MAC)) {
            hash[8] = (pkt_info->dst_mac[0] << 8) | pkt_info->dst_mac[1];
            hash[7] = (pkt_info->dst_mac[2] << 8) | pkt_info->dst_mac[3];
            hash[6] = (pkt_info->dst_mac[4] << 8) | pkt_info->dst_mac[5];
        } else {
            hash_element_valid_bits &= ~0x1c0;
        }

        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, ETHERTYPE)) {
            hash[5] = (pkt_info->ethertype >= ETHERTYPE_MIN) ?
                pkt_info->ethertype : 0;
        } else {
            hash_element_valid_bits &= ~0x20;
        }

        if (_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, VLAN)) {
            hash[4] = pkt_info->vid & 0xfff;
        } else {
            hash_element_valid_bits &= ~0x10;
        }

        sc_reg = RTAG7_HASH_FIELD_BMAP_3r;
        sc_field = L2_FIELD_BITMAP_Bf;
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "Hash calculation: Bitmap is block B L2\n")));
    }

    BCM_IF_ERROR_RETURN
        (soc_reg32_get(unit, sc_reg, REG_PORT_ANY, 0, &sc_val));
    hash_field_bmap_b = soc_reg_field_get(unit, sc_reg, sc_val, sc_field);
    /* Pre-Processing */

    if (rtag7_pre_processing_enable_b) {

        hash[12] = hash[12] ^ (hash[12] >> 3) ^ (hash[12] << 2);
        hash[11] = hash[11] ^ (hash[11] >> 3) ^ (hash[11] << 2);
        hash[10] = hash[10] ^ (hash[10] >> 3) ^ (hash[10] << 2);
        hash[9] = hash[9] ^ (hash[9] >> 3) ^ (hash[9] << 2);
        hash[8] = hash[8] ^ (hash[8] >> 3) ^ (hash[8] << 2);
        hash[7] = hash[7] ^ (hash[7] >> 3) ^ (hash[7] << 2);
        hash[6] = hash[6] ^ (hash[6] >> 3) ^ (hash[6] << 2);
        hash[5] = hash[5] ^ (hash[5] >> 3) ^ (hash[5] << 2);
        hash[4] = hash[4] ^ (hash[4] >> 3) ^ (hash[4] << 2);
        hash[3] = hash[3] ^ (hash[3] >> 3) ^ (hash[3] << 2);
        hash[2] = hash[2] ^ (hash[2] >> 3) ^ (hash[2] << 2);
        hash[1] = hash[1] ^ (hash[1] >> 3) ^ (hash[1] << 2);
        hash[0] = hash[0] ^ (hash[0] >> 3) ^ (hash[0] << 2);

    }

    if (((hash_field_bmap_b >> 12) & 0x1) == 0) {
        hash[12] = 0;
    }

    if (rtag7_en_bin_12_overlay_b) {
        hash_word[6] = (rtag7_hash_seed_b & 0xffff0000) | (hash[12] & 0xffff);
    } else {
        hash_word[6] = rtag7_hash_seed_b;
    }

    hash_res->hash_b_valid = TRUE;
    for (elem = 11; elem >= 0; elem--) {
        elem_bit = 1 << elem;
        if (0 != (hash_field_bmap_b & elem_bit)) {
            if (0 != (hash_element_valid_bits & elem_bit)) {
                hash_word[elem/2] |=
                    ((hash[elem] & 0xffff) << (16 * (elem % 2)));
            } else {
                hash_res->hash_b_valid = FALSE;
                break;
            }
        }
    }

    xor32 = hash_word[6] ^ hash_word[5] ^ hash_word[4] ^ hash_word[3] ^ hash_word[2] ^ hash_word[1] ^ hash_word[0];
    hash_xor16 = (xor32 & 0xffff) ^ ((xor32 >> 16) & 0xffff);
    hash_xor8 = (hash_xor16 & 0xff) ^ ((hash_xor16 >> 8) & 0xff);
    hash_xor4 = (hash_xor8 & 0xf) ^ ((hash_xor8 >> 4) & 0xf);
    hash_xor2 = (hash_xor4 & 0x3) ^ ((hash_xor4 >> 2) & 0x3);
    hash_xor1 = (hash_xor2 & 0x1) ^ ((hash_xor2 >> 1) & 0x1);

    hash_crc16_bisync = _shr_crc16_draco_array(hash_word, 28);
    hash_crc16_ccitt =  _shr_crc16_ccitt_array(hash_word, 28);
    hash_crc32 =        _shr_crc32_castagnoli_array(hash_word, 28);
    hash_crc32_ethernet = _shr_crc32_ethernet_array(hash_word, 28);
    hash_crc32_koopman = _shr_crc32_koopman_array(hash_word, 28);

    switch (rtag7_hash_b0_function_select) {
    case 0: /* reserved */
        hash_res->rtag7_hash16_value_b_0 = 0;
        break;
    case 1: /* reserved */
        hash_res->rtag7_hash16_value_b_0 = 0;
        break;
    case 2: /* reserved */
        hash_res->rtag7_hash16_value_b_0 = 0;
        break;
    case 3: /* CRC16 BISYNC */
        hash_res->rtag7_hash16_value_b_0 = hash_crc16_bisync;
        break;
    case 4: /* CRC16_XOR1 */
        hash_res->rtag7_hash16_value_b_0 = hash_xor1 & 0x1;
        hash_res->rtag7_hash16_value_b_0 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 5: /* CRC16_XOR2 */
        hash_res->rtag7_hash16_value_b_0 = hash_xor2 & 0x3;
        hash_res->rtag7_hash16_value_b_0 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 6: /* CRC16_XOR4 */
        hash_res->rtag7_hash16_value_b_0 = hash_xor4 & 0xf;
        hash_res->rtag7_hash16_value_b_0 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 7: /* CRC16_XOR8 */
        hash_res->rtag7_hash16_value_b_0 = hash_xor8 & 0xff;
        hash_res->rtag7_hash16_value_b_0 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 8: /* XOR16 */
        hash_res->rtag7_hash16_value_b_0 = hash_xor16;
        break;
    case 9: /* CRC16_CCITT */
        hash_res->rtag7_hash16_value_b_0 = hash_crc16_ccitt;
        break;
    case 10: /* CRC32_LO */
        hash_res->rtag7_hash16_value_b_0 = hash_crc32 & 0xffff;
        break;
    case 11: /* CRC32_HI */
        hash_res->rtag7_hash16_value_b_0 = (hash_crc32 >> 16) & 0xffff;
        break;
    case 12: /* CRC32_Ethernet_LO */
        hash_res->rtag7_hash16_value_b_0 = hash_crc32_ethernet & 0xffff;
        break;
    case 13: /* CRC32_Ethernet_HI */
        hash_res->rtag7_hash16_value_b_0 = (hash_crc32_ethernet >> 16) & 0xffff;
        break;
    case 14: /* CRC32_Koopman_LO */
        hash_res->rtag7_hash16_value_b_0 = hash_crc32_koopman & 0xffff;
        break;
    case 15: /* CRC32_Koopman_HI */
        hash_res->rtag7_hash16_value_b_0 = (hash_crc32_koopman >> 16) & 0xffff;
        break;
    default: /* reserved */
        hash_res->rtag7_hash16_value_b_0 = 0;
        break;
    }

    switch (rtag7_hash_b1_function_select) {
    case 0: /* reserved */
        hash_res->rtag7_hash16_value_b_1 = 0;
        break;
    case 1: /* reserved */
        hash_res->rtag7_hash16_value_b_1 = 0;
        break;
    case 2: /* reserved */
        hash_res->rtag7_hash16_value_b_1 = 0;
        break;
    case 3: /* CRC16 BISYNC */
        hash_res->rtag7_hash16_value_b_1 = hash_crc16_bisync;
        break;
    case 4: /* CRC16_XOR1 */
        hash_res->rtag7_hash16_value_b_1 = hash_xor1 & 0x1;
        hash_res->rtag7_hash16_value_b_1 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 5: /* CRC16_XOR2 */
        hash_res->rtag7_hash16_value_b_1 = hash_xor2 & 0x3;
        hash_res->rtag7_hash16_value_b_1 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 6: /* CRC16_XOR4 */
        hash_res->rtag7_hash16_value_b_1 = hash_xor4 & 0xf;
        hash_res->rtag7_hash16_value_b_1 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 7: /* CRC16_XOR8 */
        hash_res->rtag7_hash16_value_b_1 = hash_xor8 & 0xff;
        hash_res->rtag7_hash16_value_b_1 |= (((hash_crc16_bisync >> 8) & 0xff) << 8);
        break;
    case 8: /* XOR16 */
        hash_res->rtag7_hash16_value_b_1 = hash_xor16;
        break;
    case 9: /* CRC16_CCITT */
        hash_res->rtag7_hash16_value_b_1 = hash_crc16_ccitt;
        break;
    case 10: /* CRC32_LO */
        hash_res->rtag7_hash16_value_b_1 = hash_crc32 & 0xffff;
        break;
    case 11: /* CRC32_HI */
        hash_res->rtag7_hash16_value_b_1 = (hash_crc32 >> 16) & 0xffff;
        break;
    case 12: /* CRC32_Ethernet_LO */
        hash_res->rtag7_hash16_value_b_1 = hash_crc32_ethernet & 0xffff;
        break;
    case 13: /* CRC32_Ethernet_HI */
        hash_res->rtag7_hash16_value_b_1 = (hash_crc32_ethernet >> 16) & 0xffff;
        break;
    case 14: /* CRC32_Koopman_LO */
        hash_res->rtag7_hash16_value_b_1 = hash_crc32_koopman & 0xffff;
        break;
    case 15: /* CRC32_Koopman_HI */
        hash_res->rtag7_hash16_value_b_1 = (hash_crc32_koopman >> 16) & 0xffff;
        break;
    default: /* reserved */
        hash_res->rtag7_hash16_value_b_1 = 0;
        break;
    }

    /* End of option B hash calculation for rtag 7 */
    return BCM_E_NONE;
}

/*
 * Function:
 *          select_th_hash_subfield
 * Description:
 *          read hashing values of hash A0,A1,B0,B1,LBID
 *          from sub_sel_block pointed by hash_sub_sel
 * Parameters:
 *          concat - tell whether is in concatenated mode or not
 *          hash_sub_sel - tell which hash sub to choose
 *          seleted_subfiled - saves subfield value
 *          hash_Base - internal data where hashing informaiton is stored
 * Returns:
 *      BCM_E_xxxx
 * Note: if hash_sub_sel and hash_Base->hash_x_valid mismatches,
 *       it will return BCM_E_PARAM
 */
STATIC int
select_th_hash_subfield(uint32 concat, int hash_sub_sel, uint64 *selected_subfield,
                     bcm_rtag7_base_hash_t *hash_Base)
{
    int rv = BCM_E_NONE;

    switch (hash_sub_sel) {
        case 0: /* select pkt hash A */
            if (concat) {
                COMPILER_64_SET(*selected_subfield,
                    (hash_Base->rtag7_hash16_value_b_1 << 16 | hash_Base->rtag7_hash16_value_b_0),
                    (hash_Base->rtag7_hash16_value_a_1 << 16 | hash_Base->rtag7_hash16_value_a_0));
                if (!hash_Base->hash_a_valid || !hash_Base->hash_b_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
            } else {
                COMPILER_64_SET(*selected_subfield, 0, hash_Base->rtag7_hash16_value_a_0);
                if (!hash_Base->hash_a_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
            }
            break;

        case 1: /* select pkt hash B */
            if (concat) {
                COMPILER_64_SET(*selected_subfield, 0, hash_Base->rtag7_port_lbn);
            } else {
                COMPILER_64_SET(*selected_subfield, 0, hash_Base->rtag7_hash16_value_b_0);
                if (!hash_Base->hash_b_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
            }
            break;

        case 2: /* select port LBN */
            COMPILER_64_SET(*selected_subfield, 0, hash_Base->rtag7_port_lbn);
            break;

        case 3: /* select destination port id or hash A */
            if (concat) {
                COMPILER_64_SET(*selected_subfield, 0, hash_Base->rtag7_port_lbn);
            } else {
                COMPILER_64_SET(*selected_subfield, 0, hash_Base->rtag7_hash16_value_a_0);
                if (!hash_Base->hash_a_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
            }
            break;

        case 4: /* select LBID from module header or from SW1 stage */
            COMPILER_64_SET(*selected_subfield, 0, hash_Base->rtag7_lbid_hash);
            if (!hash_Base->lbid_hash_valid) {
                /* LBID setting isn't RTAG7 */
                rv = BCM_E_CONFIG;
            }
            break;

        case 5: /* select LBID from SW1 stage */
            COMPILER_64_SET(*selected_subfield, 0, hash_Base->rtag7_lbid_hash);
            if (!hash_Base->lbid_hash_valid) {
                /* LBID setting isn't RTAG7 */
                rv = BCM_E_CONFIG;
            }
            break;

        case 6:
            if (concat) {
                COMPILER_64_ZERO(*selected_subfield);
            } else {
                COMPILER_64_SET(*selected_subfield, 0, hash_Base->rtag7_hash16_value_a_1);
                if (!hash_Base->hash_a_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
            }
            break;

        case 7:
            if (concat) {
                COMPILER_64_ZERO(*selected_subfield);
            } else {
                COMPILER_64_SET(*selected_subfield, 0, hash_Base->rtag7_hash16_value_b_1);
                if (!hash_Base->hash_b_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
            }
            break;

        default:
            return BCM_E_PARAM;
    }
    return rv;
}

/*
 * Function:
 *          main_th_compute_lbid
 * Description:
 *     get lbid value that is used in hashing calculation
 *     if flow hash is used, get SUB_SEL_LBID_OR_ENTROPY_LABELf and
 *        OFFSET_LBID_OR_ENTROPY_LABELf from RTAG7_FLOW_BASED_HASHm
 *     if flow hash is not used, get SUB_SEL_LBID_(non)UCf and
 *        OFFSET_LBID_(non)UCf from RTAG7_PORT_BASED_HASHm
 * Parameters:
 *          unit - StrataSwitch PCI device unit number (driver internal).
 *          hash_Base - internal data that lbid_hash_value is stored
 * Returns:
 *      BCM_E_xxxx
 * Note: bcmSwitchLoadBalanceHashSelect must be set to 7
 *   and bcmSwitchLoadBalanceHashSet0UnicastOffset must be set properly.
 *       if lbid_hash_sub_sel and hash_Base->hash_x_valid mismatches,
 *       then lbid_hash_val saved in hash_Base will be 0
 *
 */
STATIC int
main_th_compute_lbid(int unit, bcm_rtag7_base_hash_t *hash_Base)
{
    /*regular var declaration*/
    uint32 lbid_hash_sub_sel;
    uint32 lbid_hash_offset;
    uint32 lbid_hash_value = 0;

    /*register var declaration*/
    int lbid_rtag = 0;
    uint64 ing_hash_config_reg;
    int    rv = BCM_E_NONE;
    uint32 rtag7_hash_sel;
    uint32 port_based_hash_index;
    rtag7_port_based_hash_entry_t
           port_based_hash_entry;
    rtag7_flow_based_hash_entry_t
            flow_based_hash_entry;
    uint8   loadbalance_use_flow_hash_uc = 0;
    uint8   loadbalance_use_flow_hash_nonuc = 0;

    /* get the lbid rtag value */
    if (SOC_REG_FIELD_VALID(unit, ING_CONFIG_64r, LBID_RTAGf)) {
        rv = READ_ING_CONFIG_64r(unit, &ing_hash_config_reg);
        if (BCM_SUCCESS(rv)) {
            lbid_rtag = soc_reg64_field32_get(unit, ING_CONFIG_64r,
                               ing_hash_config_reg, LBID_RTAGf);
        } else {
            LOG_VERBOSE(BSL_LS_BCM_COMMON,
                        (BSL_META_U(unit,
                                    "compute_lbid fail, lbid_rtag=0\n")));
            lbid_rtag =0;
        }
    } else {
        rv = (BCM_E_UNAVAIL);
    }

    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "lbid_rtag = %d\n"),
                 lbid_rtag));
    /* ******************* LBID computation ************************* */

    if (lbid_rtag == 7) {
        /* check if flow hash is used for UC*/
        SOC_IF_ERROR_RETURN
            (READ_RTAG7_HASH_SELr(unit, &rtag7_hash_sel));
        if (soc_reg_field_valid(unit, RTAG7_HASH_SELr, USE_FLOW_SEL_LBID_UCf)) {
             loadbalance_use_flow_hash_uc =
                soc_reg_field_get(unit, RTAG7_HASH_SELr,
                              rtag7_hash_sel, USE_FLOW_SEL_LBID_UCf);
        } else {
            loadbalance_use_flow_hash_uc = 0;
        }

        /* check if flow hash is used for NONUC*/
        SOC_IF_ERROR_RETURN
            (READ_RTAG7_HASH_SELr(unit, &rtag7_hash_sel));
        if (soc_reg_field_valid(unit, RTAG7_HASH_SELr, USE_FLOW_SEL_LBID_NONUCf)) {
            loadbalance_use_flow_hash_nonuc =
                soc_reg_field_get(unit, RTAG7_HASH_SELr,
                              rtag7_hash_sel, USE_FLOW_SEL_LBID_NONUCf);
        } else {
            loadbalance_use_flow_hash_nonuc = 0;
        }

        /* RTAG7 hash computation */
        if ((loadbalance_use_flow_hash_nonuc&& (hash_Base->is_nonuc == 0)) ||
            (loadbalance_use_flow_hash_uc && (hash_Base->is_nonuc != 0))) {
            SOC_IF_ERROR_RETURN(
                READ_RTAG7_FLOW_BASED_HASHm(unit, MEM_BLOCK_ANY,
                        (hash_Base->rtag7_macro_flow_id & 0xff),
                         &flow_based_hash_entry));

            /* in RTAG7_FLOW_BASED_HASHm, using same selection for
               UC and NONUC */
            lbid_hash_sub_sel = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                           &flow_based_hash_entry, SUB_SEL_LBID_OR_ENTROPY_LABELf);
            lbid_hash_offset  = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                           &flow_based_hash_entry, OFFSET_LBID_OR_ENTROPY_LABELf);
        } else if (SOC_MEM_IS_VALID(unit, RTAG7_PORT_BASED_HASHm)) {
            if (hash_Base->dev_src_port < 0) {
                int field_count = 0;
                soc_field_t fields[2];
                uint32 values[2];
                bcm_gport_t gport;

                BCM_GPORT_PROXY_SET(gport,
                    hash_Base->src_modid, hash_Base->src_port);

                if (hash_Base->is_nonuc) {
                    fields[0] = SUB_SEL_LBID_NONUCf;
                    field_count++;
                    fields[1] = OFFSET_LBID_NONUCf;
                    field_count++;
                } else {
                    fields[0] = SUB_SEL_LBID_UCf ;
                    field_count++;
                    fields[1] = OFFSET_LBID_UCf;
                    field_count++;
                }
                PORT_LOCK(unit);
                rv = bcm_esw_port_lport_fields_get(unit, gport,
                                                   LPORT_PROFILE_RTAG7_TAB,
                                                   field_count, fields, values);
                PORT_UNLOCK(unit);
                if (BCM_FAILURE(rv)) {
                    return rv;
                }
                lbid_hash_sub_sel = values[0];
                lbid_hash_offset  = values[1];
            } else {
                port_based_hash_index = hash_Base->dev_src_port +
                                        soc_mem_index_count(unit, LPORT_TABm);
                SOC_IF_ERROR_RETURN(
                    READ_RTAG7_PORT_BASED_HASHm(unit, MEM_BLOCK_ANY,
                                port_based_hash_index, &port_based_hash_entry));
                if (hash_Base->is_nonuc) {
                    lbid_hash_sub_sel = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                        &port_based_hash_entry, SUB_SEL_LBID_NONUCf);
                    lbid_hash_offset  = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                        &port_based_hash_entry, OFFSET_LBID_NONUCf);
                } else {
                    lbid_hash_sub_sel = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                        &port_based_hash_entry, SUB_SEL_LBID_UCf);
                    lbid_hash_offset  = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                        &port_based_hash_entry, OFFSET_LBID_UCf);
                }
            }
        } else {
            lbid_hash_sub_sel = 0;
            lbid_hash_offset  = 0;
        }

        switch (lbid_hash_sub_sel) {
            case 0: /* use pkt hash A */
                lbid_hash_value = hash_Base->rtag7_hash16_value_a_0;
                if (!hash_Base->hash_a_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
                break;
            case 1: /* use pkt hash B */
                lbid_hash_value = hash_Base->rtag7_hash16_value_b_0;
                if (!hash_Base->hash_b_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
                break;
            case 2: /* Use LBN */
                lbid_hash_value = hash_Base->rtag7_port_lbn;
                break;
            case 3: /* Use Destination PORTID or hash A */
                lbid_hash_value = hash_Base->rtag7_hash16_value_a_0;
                if (!hash_Base->hash_a_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
                break;
            case 4: /* Use LBID */
                /* Higig lookup use mh_higig2_lbid */
                lbid_hash_value = 0;
                break;
            case 5:
                lbid_hash_value = 0;
                break;
            case 6:
                lbid_hash_value = hash_Base->rtag7_hash16_value_a_1;
                if (!hash_Base->hash_a_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
                break;
            case 7:
                lbid_hash_value = hash_Base->rtag7_hash16_value_b_1;
                if (!hash_Base->hash_b_valid) {
                    /* Missing paramter in input */
                    rv = BCM_E_PARAM;
                }
                break;
        }
        /*
         * set up the hash value so that the LSB bits are
         * barrel shifted in case offset > 8.
         */
        lbid_hash_value |= ((lbid_hash_value & 0xffff) << 16);

        /* Only UC hash offsets apply to ECMP */
        lbid_hash_value = (lbid_hash_value >> lbid_hash_offset);

        hash_Base->rtag7_lbid_hash = (lbid_hash_value & 0xff);
        hash_Base->lbid_hash_valid = TRUE;
    } else { /* LBID rtag is 0-6 */
        /* this function not support the rtag 0-6 */
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "Hash calculation: This function doesn't support rtag 0 6"
                                 " pls change register ING_CONFIG.LBID_RTAG to value 7\n")));
        hash_Base->rtag7_lbid_hash = 0;
        hash_Base->lbid_hash_valid = FALSE;
    }
    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "lbid_hash_val=%d, valid=%d\n"),
                 hash_Base->rtag7_lbid_hash, hash_Base->lbid_hash_valid));

    return rv;
    /* ******************* END of LBID computation ************************* */
}

#ifdef INCLUDE_L3
/*
 * Function:
 *          compute_th_ecmp_hash
 * Description:
 *     get ecmp hash value using SUB_SEL_ECMPf and OFFSET_ECMPf
 *     if flow hash is used, get subsel and offset from RTAG7_FLOW_BASED_HASHm
 *     if flow hash is not used, get subsel and offset from RTAG7_PORT_BASED_HASHm
 * Parameters:
 *          unit - StrataSwitch PCI device unit number (driver internal).
 *          hash_Base - internal data where ecmp hash value is stored.
 *          hash_value - hash result.
 *          hie_ecmp_mode - 1: Hierarchical Ecmp mode.
 * Returns:
 *      BCM_E_xxxx
 *
 */
STATIC int
compute_th_ecmp_hash(int unit, bcm_rtag7_base_hash_t *hash_Base,
                               uint32 *hash_value, int hie_ecmp_mode)
{
    /*regular var declaration*/
    uint32 hash_sub_sel, hash_sub_sel_level2 = 0;
    uint32 hash_offset, hash_offset_level2 = 0;
    uint64 hash_subfield;
    uint32 hash_subfield_width;
    uint8  rtag7_ecmp_use_macro_flow_hash;
    uint8  ecmp_hash_use_rtag7;
    uint32 rtag7_hash_sel;
    uint32 hash_control;
    uint32 concat, concat_level2 = 0;
    uint32 port_based_hash_index;
    int rv = BCM_E_NONE;

    rtag7_port_based_hash_entry_t port_based_hash_entry;
    rtag7_flow_based_hash_entry_t flow_based_hash_entry;
    soc_field_t fields[] = {
        SUB_SEL_ECMPf, OFFSET_ECMPf,
        CONCATENATE_HASH_FIELDS_ECMPf,
        SUB_SEL_ECMP_LEVEL2f, OFFSET_ECMP_LEVEL2f,
        CONCATENATE_HASH_FIELDS_ECMP_LEVEL2f
    };
    /* Select between non-RTAG7 hash value and RTAG7 hash value */
    SOC_IF_ERROR_RETURN
        (READ_HASH_CONTROLr(unit, &hash_control));
    ecmp_hash_use_rtag7 =
        soc_reg_field_get(unit, HASH_CONTROLr, hash_control,
                          ECMP_HASH_USE_RTAG7f);

    if (ecmp_hash_use_rtag7 == 0) {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "ECMP Hash calculation:  non rtag7 calc not supported\n")));
        *hash_value =  0;
        return BCM_E_NONE;
    }

    /* check if flow hash is used*/
    SOC_IF_ERROR_RETURN
        (READ_RTAG7_HASH_SELr(unit, &rtag7_hash_sel));
    if (soc_reg_field_valid(unit, RTAG7_HASH_SELr, USE_FLOW_SEL_ECMPf)) {
        rtag7_ecmp_use_macro_flow_hash =
            soc_reg_field_get(unit, RTAG7_HASH_SELr,
                              rtag7_hash_sel, USE_FLOW_SEL_ECMPf);
    } else {
        rtag7_ecmp_use_macro_flow_hash = 0;
    }

    /* RTAG7 hash computation */
    if (rtag7_ecmp_use_macro_flow_hash) {
        SOC_IF_ERROR_RETURN(
            READ_RTAG7_FLOW_BASED_HASHm(unit, MEM_BLOCK_ANY,
                    (hash_Base->rtag7_macro_flow_id & 0xff),
                     &flow_based_hash_entry));

        /* Generating RTAG7 Macro Flow Based Hash Subsel and Offset for use in RSEL1 Stage */
        /* For future designs this logic can be placed in RSEL1 */
        hash_sub_sel = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                           &flow_based_hash_entry, fields[0]);
        hash_offset = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                           &flow_based_hash_entry, fields[1]);
        concat = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                           &flow_based_hash_entry, fields[2]);
        if (hie_ecmp_mode) {
            hash_sub_sel_level2 = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                           &flow_based_hash_entry, fields[3]);
            hash_offset_level2 = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                           &flow_based_hash_entry, fields[4]);
            concat_level2 = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                           &flow_based_hash_entry, fields[5]);
        }
    } else if (SOC_MEM_IS_VALID(unit, RTAG7_PORT_BASED_HASHm)) {
        if (hash_Base->dev_src_port < 0) {
            uint32 values[6];
            bcm_gport_t gport;

            BCM_GPORT_PROXY_SET(gport,
                hash_Base->src_modid, hash_Base->src_port);
            PORT_LOCK(unit);
            rv = bcm_esw_port_lport_fields_get(unit, gport,
                                               LPORT_PROFILE_RTAG7_TAB,
                                               6, fields, values);
            PORT_UNLOCK(unit);
            if (BCM_FAILURE(rv)) {
                return rv;
            }
            hash_sub_sel = values[0];
            hash_offset = values[1];
            concat = values[2];
            if (hie_ecmp_mode) {
                hash_sub_sel_level2 = values[3];
                hash_offset_level2 = values[4];
                concat_level2 = values[5];
            }

        } else {
            port_based_hash_index = hash_Base->dev_src_port +
                                    soc_mem_index_count(unit, LPORT_TABm);

            SOC_IF_ERROR_RETURN(
                READ_RTAG7_PORT_BASED_HASHm(unit, MEM_BLOCK_ANY,
                            port_based_hash_index, &port_based_hash_entry));

            hash_sub_sel = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, fields[0]);
            hash_offset = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, fields[1]);
            concat = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, fields[2]);
            if (hie_ecmp_mode) {
                hash_sub_sel_level2 = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                        &port_based_hash_entry, fields[3]);
                hash_offset_level2 = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                        &port_based_hash_entry, fields[4]);
                concat_level2 = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                        &port_based_hash_entry, fields[5]);
            }
        }
    } else {
        hash_sub_sel =  hash_sub_sel_level2 = 0;
        hash_offset = hash_offset_level2 = 0;
        concat = concat_level2 = 0;
    }
    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "ecmp hash_seb_sel=%d, hash_offset=%d, concat=%d\n"),
                 hash_sub_sel, hash_offset, concat));
    if (hie_ecmp_mode == 1) {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "ecmp hash_seb_sel_level2=%d, hash_offset_level2=%d,"
                                 "concat_level2=%d\n"),
                     hash_sub_sel_level2, hash_offset_level2, concat_level2));
  }
    BCM_IF_ERROR_RETURN
        (select_th_hash_subfield(concat, hash_sub_sel, &hash_subfield, hash_Base));

    hash_subfield_width = concat ? 64 : 16;
    hash_offset = concat ? hash_offset : (hash_offset & 0xf);

    /* Barrel shift the hash subfield, then take the LSB 16 bits */
    HASH_VALUE_64_COMPUTE(hash_subfield, hash_offset, hash_subfield_width);
    HASH_VALUE_32_COMPUTE(hash_value[0], hash_subfield);
    if (hie_ecmp_mode) {
        BCM_IF_ERROR_RETURN
            (select_th_hash_subfield(concat_level2, hash_sub_sel_level2,
                                      &hash_subfield, hash_Base));
        hash_subfield_width = concat_level2 ? 64 : 16;
        hash_offset = concat_level2 ? hash_offset_level2 : (hash_offset_level2 & 0xf);

        /* Barrel shift the hash subfield, then take the LSB 16 bits */
        HASH_VALUE_64_COMPUTE(hash_subfield, hash_offset_level2, hash_subfield_width);
        HASH_VALUE_32_COMPUTE(hash_value[1], hash_subfield);
    }
    if (hie_ecmp_mode || soc_feature(unit, soc_feature_fast_ecmp)) {
        hash_value[0] &= 0x1fff;
        hash_value[1] &= 0x1fff;
    } else {
        hash_value[0] &= 0xffff;
        hash_value[1] &= 0xffff;
    }
    return BCM_E_NONE;
    /* ***************** END of ECMP HASH CALCULATIONS.  ************************ */
}

/*
 * Function:
 *          compute_th_ecmp_rh_hash
 * Description:
 *     get ecmp rh hash value using SUB_SEL_RH_ECMPf and OFFSET_RH_ECMPf
 *     if flow hash is used, get subsel and offset from RTAG7_FLOW_BASED_HASHm
 *     if flow hash is not used, get subsel and offset from RTAG7_PORT_BASED_HASHm
 * Parameters:
 *          unit - StrataSwitch PCI device unit number (driver internal).
 *          hash_Base - internal data where rh ecmp hash value is stored
 * Returns:
 *      BCM_E_xxxx
 *
 */
STATIC int
compute_th_ecmp_rh_hash(int unit, bcm_rtag7_base_hash_t *hash_Base,
                                   uint32 *hash_value)
{
    /*regular var declaration*/
    uint32 hash_sub_sel;
    uint32 hash_offset;
    uint64 hash_subfield;
    uint32 hash_subfield_width;
    uint8  rtag7_ecmp_use_macro_flow_hash;
    uint8  ecmp_hash_use_rtag7;
    uint32 rtag7_hash_sel;
    uint32 hash_control;
    uint32 concat;
    rtag7_flow_based_hash_entry_t flow_based_hash_entry;
    rtag7_port_based_hash_entry_t port_based_hash_entry;
    uint32 port_based_hash_index;
    int rv = BCM_E_NONE;
    /* Select between non-RTAG7 hash value and RTAG7 hash value */
    SOC_IF_ERROR_RETURN
        (READ_HASH_CONTROLr(unit, &hash_control));
    ecmp_hash_use_rtag7 =
        soc_reg_field_get(unit, HASH_CONTROLr, hash_control,
                          ECMP_HASH_USE_RTAG7f);

    if (ecmp_hash_use_rtag7 == 0) {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "ECMP RH Hash calculation:  non rtag7 calc not supported\n")));
        hash_value[0] = hash_value[1] = 0;
        return BCM_E_NONE;
    }

    /* check if is uses flow hash */
    SOC_IF_ERROR_RETURN
        (READ_RTAG7_HASH_SELr(unit, &rtag7_hash_sel));
    if (soc_reg_field_valid(unit, RTAG7_HASH_SELr, USE_FLOW_SEL_RH_ECMPf)) {
        rtag7_ecmp_use_macro_flow_hash =
            soc_reg_field_get(unit, RTAG7_HASH_SELr,
                              rtag7_hash_sel, USE_FLOW_SEL_RH_ECMPf);
    } else {
        /* A0 bincomp value */
        rtag7_ecmp_use_macro_flow_hash = 0;
    }
    /* RTAG7 hash computation */
    if (rtag7_ecmp_use_macro_flow_hash) {
        SOC_IF_ERROR_RETURN(
            READ_RTAG7_FLOW_BASED_HASHm(unit, MEM_BLOCK_ANY,
                    (hash_Base->rtag7_macro_flow_id & 0xff),
                     &flow_based_hash_entry));

        /* Generating RTAG7 Macro Flow Based Hash Subsel and Offset for use in RSEL1 Stage */
        /* For future designs this logic can be placed in RSEL1 */
        hash_sub_sel = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                          &flow_based_hash_entry, SUB_SEL_ECMPf);
        hash_offset = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                   &flow_based_hash_entry, OFFSET_ECMPf);
        concat = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                     &flow_based_hash_entry, CONCATENATE_HASH_FIELDS_ECMPf);
    } else if (SOC_MEM_IS_VALID(unit, RTAG7_PORT_BASED_HASHm)) {
        if (hash_Base->dev_src_port < 0) {
            int field_count = 0;
            soc_field_t fields[3];
            uint32 values[3];
            bcm_gport_t gport;

            BCM_GPORT_PROXY_SET(gport,
                hash_Base->src_modid, hash_Base->src_port);

            fields[0] = SUB_SEL_RH_ECMPf;
            field_count++;
            fields[1] = OFFSET_RH_ECMPf;
            field_count++;
            fields[2] = CONCATENATE_HASH_FIELDS_RH_ECMPf;
            field_count++;
            PORT_LOCK(unit);
            rv = bcm_esw_port_lport_fields_get(unit, gport,
                                               LPORT_PROFILE_RTAG7_TAB,
                                               field_count, fields, values);
            PORT_UNLOCK(unit);
            if (BCM_FAILURE(rv)) {
                return rv;
            }
            hash_sub_sel = values[0];
            hash_offset  = values[1];
            concat       = values[2];
        } else {
            port_based_hash_index = hash_Base->dev_src_port +
                                    soc_mem_index_count(unit, LPORT_TABm);

            SOC_IF_ERROR_RETURN(
                READ_RTAG7_PORT_BASED_HASHm(unit, MEM_BLOCK_ANY,
                            port_based_hash_index, &port_based_hash_entry));

            hash_sub_sel = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, SUB_SEL_RH_ECMPf);
            hash_offset  = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, OFFSET_RH_ECMPf);
            concat       = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, CONCATENATE_HASH_FIELDS_RH_ECMPf);
        }
    } else {
        hash_sub_sel = 0;
        hash_offset  = 0;
        concat       = 0;
    }
    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "ecmp rh hash_seb_sel=%d, hash_offset=%d, concat=%d\n"),
                 hash_sub_sel, hash_offset, concat));

    BCM_IF_ERROR_RETURN
        (select_th_hash_subfield(concat, hash_sub_sel, &hash_subfield, hash_Base));

    hash_subfield_width = concat ? 64 : 16;
    hash_offset = concat ? hash_offset : (hash_offset & 0xf);

    /* Barrel shift the hash subfield, then take the LSB 16 bits */
    HASH_VALUE_64_COMPUTE(hash_subfield, hash_offset, hash_subfield_width);
    HASH_VALUE_32_COMPUTE(hash_value[0], hash_subfield);
    hash_value[0] &= 0xffff;
    return BCM_E_NONE;
    /* ***************** END of ECMP RH HASH CALCULATIONS.  ************************ */
}
#endif /* INCLUDE_L3 */

/*
 * Function:
 *          compute_th_rtag7_hash_trunk
 * Description:
 *     get LAG hash value from RTAG7_PORT_BASED_HASHm
 *     if unicast, SUB_SEL_TRUNK_UCf and OFFSET_TRUNK_UCf are used
 *     if not unicast, SUB_SEL_TRUNK_NONUCf and OFFSET_TRUNK_NONUCf
 *     if flow hash is used, get subsel and offset from RTAG7_FLOW_BASED_HASH
 * Parameters:
 *          unit - StrataSwitch PCI device unit number (driver internal).
 *          hash_Base - internal data where trunk hash value is storead
 *          hash_value- result param
 * Returns:
 *      BCM_E_xxxx
 *
 */
STATIC int
compute_th_rtag7_hash_trunk(int unit , bcm_rtag7_base_hash_t *hash_Base,
                         uint32 *hash_value)
{
    uint32 hash_sub_sel;
    uint32 hash_offset;
    uint32 rtag7_hash_sel;
    uint32 port_based_hash_index;
    uint64 hash_subfield;
    uint32 hash_subfield_width;
    uint32 offset_shift = 0;
    uint32 concat;
    uint8  rtag7_trunk_use_macro_flow_hash_uc    = 0;
    uint8  rtag7_trunk_use_macro_flow_hash_nonuc = 0;
    rtag7_port_based_hash_entry_t port_based_hash_entry;
    rtag7_flow_based_hash_entry_t flow_based_hash_entry;
    uint32 hash_control;
    uint32 nuc_trunk_hash_use_rtag7;
    int rv = BCM_E_NONE;

    /* check if flow hash is used for UC*/
    SOC_IF_ERROR_RETURN
        (READ_RTAG7_HASH_SELr(unit, &rtag7_hash_sel));
    if (soc_reg_field_valid(unit, RTAG7_HASH_SELr, USE_FLOW_SEL_TRUNK_UCf)) {
        rtag7_trunk_use_macro_flow_hash_uc =
            soc_reg_field_get(unit, RTAG7_HASH_SELr,
                              rtag7_hash_sel, USE_FLOW_SEL_TRUNK_UCf);
    } else {
        rtag7_trunk_use_macro_flow_hash_uc = 0;
    }

    /* check if flow hash is used for NONUC*/
    SOC_IF_ERROR_RETURN
        (READ_RTAG7_HASH_SELr(unit, &rtag7_hash_sel));
    if (soc_reg_field_valid(unit, RTAG7_HASH_SELr, USE_FLOW_SEL_TRUNK_NONUCf)) {
        rtag7_trunk_use_macro_flow_hash_nonuc =
            soc_reg_field_get(unit, RTAG7_HASH_SELr,
                              rtag7_hash_sel, USE_FLOW_SEL_TRUNK_NONUCf);
    } else {
        rtag7_trunk_use_macro_flow_hash_nonuc = 0;
    }

    /* RTAG7 hash computation */
    if ((rtag7_trunk_use_macro_flow_hash_nonuc && (hash_Base->is_nonuc == 0)) ||
        (rtag7_trunk_use_macro_flow_hash_uc && (hash_Base->is_nonuc != 0))) {
        SOC_IF_ERROR_RETURN(
            READ_RTAG7_FLOW_BASED_HASHm(unit, MEM_BLOCK_ANY,
                    (hash_Base->rtag7_macro_flow_id & 0xff),
                     &flow_based_hash_entry));

        /* in RTAG7_FLOW_BASED_HASHm, using same selection for
           UC and NONUC */
        hash_sub_sel = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                       &flow_based_hash_entry, SUB_SEL_TRUNKf);
        hash_offset  = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                       &flow_based_hash_entry, OFFSET_TRUNKf);
        concat       = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                       &flow_based_hash_entry, CONCATENATE_HASH_FIELDS_TRUNKf);
        offset_shift = 0xffff;
    } else if (SOC_MEM_IS_VALID(unit, RTAG7_PORT_BASED_HASHm)) {
        if (hash_Base->dev_src_port < 0) {
            int field_count = 0;
            soc_field_t fields[3];
            uint32 values[3];
            bcm_gport_t gport;

            BCM_GPORT_PROXY_SET(gport,
                hash_Base->src_modid, hash_Base->src_port);

            if (hash_Base->is_nonuc) {
                fields[0] = SUB_SEL_TRUNK_NONUCf;
                field_count++;
                fields[1] = OFFSET_TRUNK_NONUCf;
                field_count++;
                fields[2] = CONCATENATE_HASH_FIELDS_TRUNK_NONUCf;
                field_count++;
                offset_shift = 0xff;
            } else {
                fields[0] = SUB_SEL_TRUNK_UCf;
                field_count++;
                fields[1] = OFFSET_TRUNK_UCf;
                field_count++;
                fields[2] = CONCATENATE_HASH_FIELDS_TRUNK_UCf;
                field_count++;
                offset_shift = 0x3ff;
            }
            PORT_LOCK(unit);
            rv = bcm_esw_port_lport_fields_get(unit, gport,
                                               LPORT_PROFILE_RTAG7_TAB,
                                               field_count, fields, values);
            PORT_UNLOCK(unit);
            if (BCM_FAILURE(rv)) {
                return rv;
            }
            hash_sub_sel = values[0];
            hash_offset  = values[1];
            concat       = values[2];
        } else {
            port_based_hash_index = hash_Base->dev_src_port +
                                    soc_mem_index_count(unit, LPORT_TABm);
            SOC_IF_ERROR_RETURN(
                READ_RTAG7_PORT_BASED_HASHm(unit, MEM_BLOCK_ANY,
                            port_based_hash_index, &port_based_hash_entry));
            if (hash_Base->is_nonuc) {
                hash_sub_sel = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, SUB_SEL_TRUNK_NONUCf);
                hash_offset  = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, OFFSET_TRUNK_NONUCf);
                concat       = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, CONCATENATE_HASH_FIELDS_TRUNK_NONUCf);
                offset_shift = 0xff;
            } else {
                hash_sub_sel = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, SUB_SEL_TRUNK_UCf);
                hash_offset  = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, OFFSET_TRUNK_UCf);
                concat       = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, CONCATENATE_HASH_FIELDS_TRUNK_UCf);
                offset_shift = 0x3ff;
            }
        }
    } else {
        hash_sub_sel = 0;
        hash_offset  = 0;
        concat       = 0;
    }

    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "Trunk hash_seb_sel=%d, hash_offset=%d, concat=%d\n"),
                 hash_sub_sel, hash_offset, concat));

    BCM_IF_ERROR_RETURN
        (select_th_hash_subfield(concat, hash_sub_sel, &hash_subfield, hash_Base));

    hash_subfield_width = concat ? 64 : 16;
    hash_offset = concat ? hash_offset : (hash_offset & 0xf);

    /* Barrel shift the hash subfield, then take the LSB 10 bits for UC and 8 bits for nonUC */
    HASH_VALUE_64_COMPUTE(hash_subfield, hash_offset, hash_subfield_width);
    HASH_VALUE_32_COMPUTE(*hash_value, hash_subfield);
    *hash_value &= offset_shift;

    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "Trunk hash_value=%d\n"),
                 *hash_value));

    BCM_IF_ERROR_RETURN
        (READ_HASH_CONTROLr(unit, &hash_control));
    nuc_trunk_hash_use_rtag7 =
        soc_reg_field_get(unit, HASH_CONTROLr, hash_control,
                          NON_UC_TRUNK_HASH_USE_RTAG7f);

    if (hash_Base->is_nonuc && nuc_trunk_hash_use_rtag7 == 0) {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "NonUC trunk Hash calculation:  non rtag7 calc not supported\n")));
        *hash_value = 0;
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *          compute_th_rtag7_hash_hg_trunk
 * Description:
 *     get HGT hash value from RTAG7_PORT_BASED_HASHm
 *     if unicast, SUB_SEL_TRUNK_UCf and OFFSET_TRUNK_UCf are used
 *     if not unicast, SUB_SEL_TRUNK_NONUCf and OFFSET_TRUNK_NONUCf
 *     if flow hash is used, get subsel and offset from RTAG7_FLOW_BASED_HASH
 * Parameters:
 *          unit - StrataSwitch PCI device unit number (driver internal).
 *          hash_Base - internal data where trunk hash value is storead
 *          hash_value- result param
 * Returns:
 *      BCM_E_xxxx
 *
 */
STATIC int
compute_th_rtag7_hash_hg_trunk(int unit , bcm_rtag7_base_hash_t *hash_Base,
                         uint32 *hash_value)
{
    uint32 hash_sub_sel;
    uint32 hash_offset;
    uint32 rtag7_hash_sel;
    uint32 port_based_hash_index;
    uint64 hash_subfield;
    uint32 hash_subfield_width;
    uint32 offset_shift = 0;
    uint32 concat;
    uint8  rtag7_hgt_use_macro_flow_hash_uc    = 0;
    uint8  rtag7_hgt_use_macro_flow_hash_nonuc = 0;
    rtag7_port_based_hash_entry_t port_based_hash_entry;
    rtag7_flow_based_hash_entry_t flow_based_hash_entry;
    int rv = BCM_E_NONE;
    /* check if flow hash is used for UC*/
    SOC_IF_ERROR_RETURN
        (READ_RTAG7_HASH_SELr(unit, &rtag7_hash_sel));
    if (soc_reg_field_valid(unit, RTAG7_HASH_SELr, USE_FLOW_SEL_HG_TRUNK_UCf)) {
        rtag7_hgt_use_macro_flow_hash_uc =
            soc_reg_field_get(unit, RTAG7_HASH_SELr,
                              rtag7_hash_sel, USE_FLOW_SEL_HG_TRUNK_UCf);
    } else {
        rtag7_hgt_use_macro_flow_hash_uc = 0;
    }

    /* check if flow hash is used for NONUC*/
    if (soc_reg_field_valid(unit, RTAG7_HASH_SELr, USE_FLOW_SEL_HG_TRUNK_NONUCf)) {
        rtag7_hgt_use_macro_flow_hash_nonuc =
            soc_reg_field_get(unit, RTAG7_HASH_SELr,
                              rtag7_hash_sel, USE_FLOW_SEL_HG_TRUNK_NONUCf);
    } else {
        rtag7_hgt_use_macro_flow_hash_nonuc = 0;
    }

    /* RTAG7 hash computation */
    if ((rtag7_hgt_use_macro_flow_hash_nonuc && (hash_Base->is_nonuc == 0)) ||
        (rtag7_hgt_use_macro_flow_hash_uc && (hash_Base->is_nonuc != 0))) {
        SOC_IF_ERROR_RETURN(
            READ_RTAG7_FLOW_BASED_HASHm(unit, MEM_BLOCK_ANY,
                    (hash_Base->rtag7_macro_flow_id & 0xff),
                     &flow_based_hash_entry));

        /* in RTAG7_FLOW_BASED_HASHm, using same selection for
           UC and NONUC */
        hash_sub_sel = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                       &flow_based_hash_entry, SUB_SEL_HG_TRUNKf);
        hash_offset  = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                       &flow_based_hash_entry, OFFSET_HG_TRUNKf);
        concat       = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                       &flow_based_hash_entry, CONCATENATE_HASH_FIELDS_HG_TRUNKf);
        offset_shift = 0xffff;
    } else if (SOC_MEM_IS_VALID(unit, RTAG7_PORT_BASED_HASHm)) {
        if (hash_Base->dev_src_port < 0) {
            int field_count = 0;
            soc_field_t fields[3];
            uint32 values[3];
            bcm_gport_t gport;

            BCM_GPORT_PROXY_SET(gport,
                hash_Base->src_modid, hash_Base->src_port);

            if (hash_Base->is_nonuc) {
                fields[0] = SUB_SEL_HG_TRUNK_NONUCf;
                field_count++;
                fields[1] = OFFSET_HG_TRUNK_NONUCf;
                field_count++;
                fields[2] = CONCATENATE_HASH_FIELDS_HG_TRUNK_NONUCf;
                field_count++;
                offset_shift = 0xff;
            } else {
                fields[0] = SUB_SEL_HG_TRUNK_UCf;
                field_count++;
                fields[1] = OFFSET_HG_TRUNK_UCf;
                field_count++;
                fields[2] = CONCATENATE_HASH_FIELDS_HG_TRUNK_UCf;
                field_count++;
                offset_shift = 0x3ff;
            }
            PORT_LOCK(unit);
            rv = bcm_esw_port_lport_fields_get(unit, gport,
                                               LPORT_PROFILE_RTAG7_TAB,
                                               field_count, fields, values);
            PORT_UNLOCK(unit);
            if (BCM_FAILURE(rv)) {
                return rv;
            }
            hash_sub_sel = values[0];
            hash_offset  = values[1];
            concat       = values[2];
        } else {
            port_based_hash_index = hash_Base->dev_src_port +
                                    soc_mem_index_count(unit, LPORT_TABm);
            SOC_IF_ERROR_RETURN(
                READ_RTAG7_PORT_BASED_HASHm(unit, MEM_BLOCK_ANY,
                            port_based_hash_index, &port_based_hash_entry));
            if (hash_Base->is_nonuc) {
                hash_sub_sel = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, SUB_SEL_HG_TRUNK_NONUCf);
                hash_offset  = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, OFFSET_HG_TRUNK_NONUCf);
                concat       = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, CONCATENATE_HASH_FIELDS_HG_TRUNK_NONUCf);
                offset_shift = 0xff;
            } else {
                hash_sub_sel = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, SUB_SEL_HG_TRUNK_UCf);
                hash_offset  = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, OFFSET_HG_TRUNK_UCf);
                concat       = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                    &port_based_hash_entry, CONCATENATE_HASH_FIELDS_HG_TRUNK_UCf);
                offset_shift = 0x3ff;
            }
        }
    } else {
        hash_sub_sel = 0;
        hash_offset  = 0;
        concat       = 0;
    }

    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "Trunk hash_seb_sel=%d, hash_offset=%d, concat=%d\n"),
                 hash_sub_sel, hash_offset, concat));

    BCM_IF_ERROR_RETURN
        (select_th_hash_subfield(concat, hash_sub_sel, &hash_subfield, hash_Base));

    hash_subfield_width = concat ? 64 : 16;
    hash_offset = concat ? hash_offset : (hash_offset & 0xf);

    /* Barrel shift the hash subfield, then take the LSB 10 bits for UC and 8 bits for nonUC */
    HASH_VALUE_64_COMPUTE(hash_subfield, hash_offset, hash_subfield_width);
    HASH_VALUE_32_COMPUTE(*hash_value, hash_subfield);
    *hash_value &= offset_shift;

    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "HG Trunk hash_value=%d\n"),
                 *hash_value));

    return BCM_E_NONE;
}


/*
 * Function:
 *          compute_th_rtag7_vxlan
 * Description: compute entropy value of vxlan packet
 * Parameters:
 *          unit - StrataSwitch PCI device unit number (driver internal).
 *          hash_Base - internal data where trunk hash value is storead
 *          hash_value- result param
 * Returns:
 *      BCM_E_xxxx
 *
 */
STATIC int
compute_th_rtag7_vxlan(int unit , bcm_rtag7_base_hash_t *hash_Base,
                                   uint32 *hash_value)
{
    uint32 hash_sub_sel;
    uint32 hash_offset;
    uint32 rtag7_hash_sel;
    uint32 port_based_hash_index;
    uint64 hash_subfield;
    uint32 hash_subfield_width;
    uint32 offset_shift = 0xffff;
    uint32 concat;
    uint8  rtag7_vxlan_use_flow_sel_entropy_label = 0;
    rtag7_port_based_hash_entry_t port_based_hash_entry;
    rtag7_flow_based_hash_entry_t flow_based_hash_entry;

    /* check if vxlan use RTAG7_FLOW_BASED_HASH
       else use RTAG7_PORT_BASED_HASH selection for ENTROPY_LABEL*/
    SOC_IF_ERROR_RETURN
        (READ_RTAG7_HASH_SELr(unit, &rtag7_hash_sel));
    if (soc_reg_field_valid(unit, RTAG7_HASH_SELr, USE_FLOW_SEL_ENTROPY_LABELf)) {
        rtag7_vxlan_use_flow_sel_entropy_label =
            soc_reg_field_get(unit, RTAG7_HASH_SELr,
                              rtag7_hash_sel, USE_FLOW_SEL_ENTROPY_LABELf);
    } else {
        rtag7_vxlan_use_flow_sel_entropy_label = 0;
    }

    /* RTAG7 hash computation */
    if (rtag7_vxlan_use_flow_sel_entropy_label) {
        /* read flow_based_hash table and set hash_sub_sel, offset, and concat value */
        SOC_IF_ERROR_RETURN(
            READ_RTAG7_FLOW_BASED_HASHm(unit, MEM_BLOCK_ANY,
                    (hash_Base->rtag7_macro_flow_id & 0xff),
                     &flow_based_hash_entry));
        hash_sub_sel = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                       &flow_based_hash_entry, SUB_SEL_LBID_OR_ENTROPY_LABELf);
        hash_offset  = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                       &flow_based_hash_entry, OFFSET_LBID_OR_ENTROPY_LABELf);
        concat       = soc_RTAG7_FLOW_BASED_HASHm_field32_get(unit,
                                       &flow_based_hash_entry, CONCATENATE_HASH_FIELDS_LBID_OR_ENTROPY_LABELf);
    } else if (SOC_MEM_IS_VALID(unit, RTAG7_PORT_BASED_HASHm)) {
        /* read port_based_hash table and set hash_sub_sel, offset, and concat value */
        port_based_hash_index = hash_Base->dev_src_port +
                                soc_mem_index_count(unit, LPORT_TABm);
        SOC_IF_ERROR_RETURN(
            READ_RTAG7_PORT_BASED_HASHm(unit, MEM_BLOCK_ANY,
                        port_based_hash_index, &port_based_hash_entry));
            hash_sub_sel = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                &port_based_hash_entry, SUB_SEL_ENTROPY_LABELf);
            hash_offset  = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                &port_based_hash_entry, OFFSET_ENTROPY_LABELf);
            concat       = soc_RTAG7_PORT_BASED_HASHm_field32_get(unit,
                                &port_based_hash_entry, CONCATENATE_HASH_FIELDS_ENTROPY_LABELf);
    } else {
        hash_sub_sel = 0;
        hash_offset  = 0;
        concat       = 0;
    }

    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "vxlan hash_seb_sel=%d, hash_offset=%d, concat=%d\n"),
                 hash_sub_sel, hash_offset, concat));
    BCM_IF_ERROR_RETURN
        (select_th_hash_subfield(concat, hash_sub_sel, &hash_subfield, hash_Base));

    hash_subfield_width = concat ? 64 : 16;
    hash_offset = concat ? hash_offset : (hash_offset & 0xf);

    /* Barrel shift the hash subfield, then take the LSB 10 bits for UC and 8 bits for nonUC */
    HASH_VALUE_64_COMPUTE(hash_subfield, hash_offset, hash_subfield_width);
    HASH_VALUE_32_COMPUTE(*hash_value, hash_subfield);
    *hash_value &= offset_shift;
    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "vxlan hash_value=%d\n"),
                 *hash_value));

    return BCM_E_NONE;
}

#ifdef INCLUDE_L3
/* calcualte resilient hashing value for ECMP*/
int perform_th_rh(int unit,uint32 flow_set_base, uint8 flow_set_size,
                       uint32 *rtag7_hash, uint32 *ecmp_offset)
{
    uint32 flow_set_index = 0;
    if ((flow_set_size > 5) && (flow_set_size < 15)) {
        flow_set_index = rtag7_hash[0] & ((1 << flow_set_size) - 1);
    } else {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "Member count %d is not in the correct range\n"),
                     flow_set_size));
        flow_set_index = 0;
    }
    *ecmp_offset = flow_set_index;
    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "Ecmp offset *ecmp_offset=%d\n"),
                 *ecmp_offset));
    return BCM_E_NONE;
}
STATIC int
get_th_ecmp_lb_mode(int unit, int ecmp_group, int *ecmp_lb_mode)
{
    ecmp_count_entry_t ecmp_group_entry;
    BCM_IF_ERROR_RETURN
        (READ_L3_ECMP_COUNTm(unit, MEM_BLOCK_ANY,
                             ecmp_group, &ecmp_group_entry));
    *ecmp_lb_mode = soc_L3_ECMP_COUNTm_field32_get(unit, &ecmp_group_entry,
                                                   LB_MODEf);
    return BCM_E_NONE;

}
STATIC int
get_th_hash_ecmp_level2(int unit, int ecmp_group, uint32 *hash_value,
                                 uint32 ecmp_mask, bcm_if_t *nh_id)
{
    ecmp_count_entry_t ecmp_group_entry;
    ecmp_entry_t ecmp_entry;

    uint32 ecmp_ptr;
    uint32 ecmp_member_count;
    uint32 ecmp_index;
    uint32 ecmp_offset;

    SOC_IF_ERROR_RETURN
        (READ_L3_ECMP_COUNTm(unit, MEM_BLOCK_ANY, ecmp_group, &ecmp_group_entry));

    ecmp_ptr = soc_L3_ECMP_COUNTm_field32_get(unit, &ecmp_group_entry,
                                              BASE_PTRf);
    ecmp_member_count = soc_L3_ECMP_COUNTm_field32_get(unit, &ecmp_group_entry,
                                              MEMBER_COUNTf);

    ecmp_offset = ((hash_value[1] & ecmp_mask) % (ecmp_member_count + 1)) & 0x3FF;
    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "\tECMP offset 0x%08x, ptr 0x%x\n"),
                 ecmp_offset, ecmp_ptr));
    ecmp_index = (ecmp_ptr + ecmp_offset) & 0x3fff;
    SOC_IF_ERROR_RETURN
        (READ_L3_ECMPm(unit, MEM_BLOCK_ANY, ecmp_index, &ecmp_entry));

    *nh_id = soc_L3_ECMPm_field32_get(unit, &ecmp_entry,
                                 NEXT_HOP_INDEXf) & 0xefff;
    return BCM_E_NONE;
}

/*
 * Function:
 *          get_th_hash_ecmp
 * Description:
 *     compute ecmp destination among multipath interfaces
 * Parameters:
 *  unit - StrataSwitch PCI device unit number (driver internal).
 *  ecmp_group - multipath id
 *  hash_index - hash value calculated from compute_th_ecmp_hash
 *  hash_rh_index -  hash value calculated from compute_th_ecmp_rh_hash
 *  nh_id - where egress l3 interface id is stored
 *  ecmp_rh_enable - flag indicating if rh is enable for this hashing calculation
 *  hie_ecmp_mode - 1: Hierarchical ECMP mode
 *
 * Returns:
 *      BCM_E_xxxx
 *
 */
STATIC int
get_th_hash_ecmp(int unit, int ecmp_group, uint32 *hash_index, uint32 *hash_rh_index, bcm_if_t *nh_id,
                  uint8 ecmp_rh_enable, int hie_ecmp_mode)
{
    uint32 ecmp_hash_field_upper_bits_count;
    ecmp_count_entry_t ecmp_group_entry;
    ecmp_entry_t ecmp_entry;
    uint32 ecmp_base_ptr = 0;
    uint32 ecmp_member_count = 0;
    uint32 ecmp_flag = 0;

    uint32 hash_control;
    uint32 ecmp_mask;
    uint32 ecmp_offset;
    uint32 ecmp_index;
    uint32 nhop_ecmp_group;
      /*register read*/
    if (SOC_REG_FIELD_VALID(unit, HASH_CONTROLr,
                            ECMP_HASH_FIELD_UPPER_BITS_COUNTf)) {
        SOC_IF_ERROR_RETURN
            (READ_HASH_CONTROLr(unit, &hash_control));
        ecmp_hash_field_upper_bits_count =
            soc_reg_field_get(unit, HASH_CONTROLr, hash_control,
                              ECMP_HASH_FIELD_UPPER_BITS_COUNTf);
    } else {
        ecmp_hash_field_upper_bits_count = 0x6; /* A0 bincomp value */
    }
    switch (ecmp_hash_field_upper_bits_count) {
    case 0:
        ecmp_mask = 0x3ff;
        break;
    case 1:
        ecmp_mask = 0x7ff;
        break;
    case 2:
        ecmp_mask = 0xfff;
        break;
    case 3:
        ecmp_mask = 0x1fff;
        break;
    case 4:
        ecmp_mask = 0x3fff;
        break;
    case 5:
        ecmp_mask = 0x7fff;
        break;
    case 6:
        ecmp_mask = 0xffff;
        break;
    default:
        ecmp_mask = 0xffff;
        break;
    }

    SOC_IF_ERROR_RETURN
        (READ_L3_ECMP_COUNTm(unit, MEM_BLOCK_ANY, ecmp_group, &ecmp_group_entry));
    ecmp_base_ptr = soc_L3_ECMP_COUNTm_field32_get(unit, &ecmp_group_entry, BASE_PTRf);
    ecmp_member_count = soc_L3_ECMP_COUNTm_field32_get(unit, &ecmp_group_entry, MEMBER_COUNTf);

    if (ecmp_rh_enable) {
        perform_th_rh(unit, ecmp_base_ptr, ecmp_member_count, hash_rh_index, &ecmp_offset);
        ecmp_index = (ecmp_base_ptr + ecmp_offset) & 0xfff;
        SOC_IF_ERROR_RETURN
            (READ_L3_ECMPm(unit, MEM_BLOCK_ANY, ecmp_index, &ecmp_entry));
        ecmp_flag = soc_L3_ECMPm_field32_get(unit, &ecmp_entry, ECMP_FLAGf);
        nhop_ecmp_group = soc_L3_ECMPm_field32_get(unit, &ecmp_entry, NHOP_ECMP_GROUPf);
        if (ecmp_flag == 0) {
            *nh_id = nhop_ecmp_group & 0xefff;
        } else {
            if (!hie_ecmp_mode) {
                return BCM_E_PARAM;
            }
            SOC_IF_ERROR_RETURN(
                get_th_hash_ecmp_level2(unit, nhop_ecmp_group, hash_rh_index, ecmp_mask, nh_id));
        }
    } else {
        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         * A ECMP_COUNT value of 0 implies 1 entry
         * a value of 1 implies 2 entries etc...
         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         */
        ecmp_offset = ((hash_index[0] & ecmp_mask) % (ecmp_member_count + 1)) & 0x3FF;
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tECMP offset 0x%08x, ptr 0x%x\n"),
                     ecmp_offset, ecmp_base_ptr));
        ecmp_index = (ecmp_base_ptr + ecmp_offset) & 0xfff;
        SOC_IF_ERROR_RETURN
            (READ_L3_ECMPm(unit, MEM_BLOCK_ANY, ecmp_index, &ecmp_entry));
        ecmp_flag = soc_L3_ECMPm_field32_get(unit, &ecmp_entry, ECMP_FLAGf);
        nhop_ecmp_group = soc_L3_ECMPm_field32_get(unit, &ecmp_entry, NHOP_ECMP_GROUPf);

        if (ecmp_flag == 0) {
            *nh_id = nhop_ecmp_group & 0xefff;
        } else {
            if (!hie_ecmp_mode) {
                return BCM_E_PARAM;
            }
            SOC_IF_ERROR_RETURN(
                get_th_hash_ecmp_level2(unit, nhop_ecmp_group, hash_index, ecmp_mask, nh_id));
        }
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tECMP next hop HW index 0x%08x\n"),
                     *nh_id));
    }

    return BCM_E_NONE;
}
#endif /* INCLUDE_L3 */

/*
 * Function:
 *          get_th_hash_trunk
 * Description:
 *     compute destination trunk member port
 * Parameters:
 *  unit - StrataSwitch PCI device unit number (driver internal).
 *  ecmp_group - multipath id
 *  tgid - trunk port id
 *  hash_index - hash value calculated from compute_th_rtag7_hash_trunk
 *  dst_tgid - where egress member port id is stored
 *  hash_rh_value - flag indicating if rh is enable for this hashing calculation
 *
 * Returns:
 *      BCM_E_xxxx
 *
 */
STATIC int
get_th_hash_trunk(int unit, int tgid, uint32 hash_index,
                bcm_gport_t *dst_tgid)
{
    uint32 trunk_base = 0;
    uint32 trunk_group_size;
    uint32 rtag;
    uint32 trunk_index;
    uint32 trunk_member_table_index;
    bcm_module_t mod_id;
    bcm_port_t port_id;
    int mod_is_local;
    trunk_member_entry_t trunk_member_entry;
    trunk_group_entry_t  tg_entry;
    _bcm_gport_dest_t   dest;
    soc_field_t      _xgs_fast_portf[8] = {
        PORT_NUM_0f, PORT_NUM_1f, PORT_NUM_2f, PORT_NUM_3f,
        PORT_NUM_4f, PORT_NUM_5f, PORT_NUM_6f, PORT_NUM_7f
    };
    soc_field_t      _xgs_fast_modulef[8] = {
        MODULE_ID_0f, MODULE_ID_1f, MODULE_ID_2f, MODULE_ID_3f,
        MODULE_ID_4f, MODULE_ID_5f, MODULE_ID_6f, MODULE_ID_7f
    };

    if (soc_feature(unit, soc_feature_fastlag)) {
        BCM_IF_ERROR_RETURN
            (READ_FAST_TRUNK_GROUPm(unit, MEM_BLOCK_ANY, tgid, &tg_entry));
        trunk_group_size = soc_FAST_TRUNK_GROUPm_field32_get(unit, &tg_entry, TG_SIZEf);
        rtag = soc_FAST_TRUNK_GROUPm_field32_get(unit, &tg_entry, RTAGf);

    } else {
        BCM_IF_ERROR_RETURN
            (READ_TRUNK_GROUPm(unit, MEM_BLOCK_ANY, tgid, &tg_entry));
        trunk_base = soc_TRUNK_GROUPm_field32_get(unit, &tg_entry, BASE_PTRf);
        trunk_group_size = soc_TRUNK_GROUPm_field32_get(unit, &tg_entry, TG_SIZEf);
        rtag = soc_TRUNK_GROUPm_field32_get(unit, &tg_entry, RTAGf);
    }

    if (rtag != 7){
         LOG_VERBOSE(BSL_LS_BCM_COMMON,
                     (BSL_META_U(unit,
                                 "Hash calculation: uport only RTAG7 calc no support for rtag %d\n"),
                      rtag));
    }

    trunk_index = hash_index % (trunk_group_size + 1);
    if (soc_feature(unit, soc_feature_fastlag)) {
        mod_id  = soc_FAST_TRUNK_GROUPm_field32_get(unit, &tg_entry,
                                                _xgs_fast_modulef[trunk_index]);
        port_id = soc_FAST_TRUNK_GROUPm_field32_get(unit, &tg_entry,
                                                _xgs_fast_portf[trunk_index]);
    } else {
        trunk_member_table_index = (trunk_base + trunk_index) & 0x7ff;
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                            "\tTrunk HW index 0x%08x\n"),
                    trunk_index));
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                            "\tTrunk group size 0x%08x\n"),
                    trunk_group_size));

        BCM_IF_ERROR_RETURN
            (READ_TRUNK_MEMBERm(unit, MEM_BLOCK_ANY, trunk_member_table_index,
                                        &trunk_member_entry));
        mod_id  = soc_TRUNK_MEMBERm_field32_get(unit, &trunk_member_entry,
                                        MODULE_IDf);
        port_id = soc_TRUNK_MEMBERm_field32_get(unit, &trunk_member_entry,
                                        PORT_NUMf);
    }

    BCM_IF_ERROR_RETURN
        (_bcm_esw_stk_modmap_map(unit, BCM_STK_MODMAP_GET, mod_id, port_id,
                                        &(dest.modid), &(dest.port)));
    dest.gport_type = _SHR_GPORT_TYPE_MODPORT;

    BCM_IF_ERROR_RETURN
        (_bcm_esw_modid_is_local(unit, dest.modid,
                                 &mod_is_local));
    if (mod_is_local) {
        if (IS_ST_PORT(unit, port_id)) {
            dest.port = port_id;
            dest.gport_type = _SHR_GPORT_TYPE_DEVPORT;
        }
    }

    BCM_IF_ERROR_RETURN(_bcm_esw_gport_construct(unit, &dest, dst_tgid));

    return BCM_E_NONE;
}

/*
 * Function:
 *     get_th_hash_trunk_nuc
 * Description:
 *     Compute non-unicast destination trunk member port
 * Parameters:
 *  unit - StrataSwitch PCI device unit number (driver internal).
 *  tgid - Trunk group id
 *  fwd_reason - Flow foward reason. unicast, ipmc, l2mc, broadcast, dlf.
 *  hash_index - Hash value calculated based on RTAG7
 *  dst_gport  - Where egress member port id is stored
 *
 * Returns:
 *      BCM_E_xxxx
 *
 */
STATIC int
get_th_hash_trunk_nuc(int unit, int tgid,
                   bcm_switch_pkt_hash_info_fwd_reason_t fwd_reason,
                   uint32 hash_index, bcm_gport_t *dst_gport)
{
    int nuc_type, nuc_tbm_index;
    int modid, port;
    bcm_pbmp_t local_pbmp, block_mask_pbmp;
    trunk_bitmap_entry_t trunk_bitmap_entry;
    nonucast_trunk_block_mask_entry_t mask_entry;
    uint32 disable_flags = BCM_TRUNK_MEMBER_EGRESS_DISABLE;

    switch(fwd_reason) {
        case bcmSwitchPktHashInfoFwdReasonIpmc:
            nuc_type = TRUNK_BLOCK_MASK_TYPE_IPMC;
            disable_flags |= BCM_TRUNK_MEMBER_IPMC_EGRESS_DISABLE;
            break;
        case bcmSwitchPktHashInfoFwdReasonL2mc:
            nuc_type = TRUNK_BLOCK_MASK_TYPE_L2MC;
            disable_flags |= BCM_TRUNK_MEMBER_L2MC_EGRESS_DISABLE;
            break;
        case bcmSwitchPktHashInfoFwdReasonBcast:
            nuc_type = TRUNK_BLOCK_MASK_TYPE_BCAST;
            disable_flags |= BCM_TRUNK_MEMBER_BCAST_EGRESS_DISABLE;
            break;
        case bcmSwitchPktHashInfoFwdReasonDlf:
            nuc_type = TRUNK_BLOCK_MASK_TYPE_DLF;
            disable_flags |= BCM_TRUNK_MEMBER_DLF_EGRESS_DISABLE;
            break;
        default:
            return BCM_E_PARAM;
    }
    nuc_tbm_index = (nuc_type << 8) | (hash_index & 0xff);

    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "Nonuc-trunk table index = %d\n"),
                 nuc_tbm_index));

    BCM_IF_ERROR_RETURN(
        READ_NONUCAST_TRUNK_BLOCK_MASKm(unit, MEM_BLOCK_ANY,
                                        nuc_tbm_index, &mask_entry));
    soc_mem_pbmp_field_get(unit, NONUCAST_TRUNK_BLOCK_MASKm, &mask_entry,
                           BLOCK_MASKf, &block_mask_pbmp);
    BCM_IF_ERROR_RETURN(
        READ_TRUNK_BITMAPm(unit, MEM_BLOCK_ANY, tgid, &trunk_bitmap_entry));
    soc_mem_pbmp_field_get(unit, TRUNK_BITMAPm, &trunk_bitmap_entry,
                           TRUNK_BITMAPf, &local_pbmp);

    BCM_PBMP_REMOVE(local_pbmp, block_mask_pbmp);

    if (BCM_PBMP_IS_NULL(local_pbmp)) {
        /* this means that member is not on local device, try SW prediction */
        bcm_trunk_member_t *member_array = NULL;
        int member_count;
        bcm_gport_t *port_array = NULL;
        int port_count, port_index = BCM_TRUNK_UNSPEC_INDEX;
        int region_size, i, all_local, rv;
        bcm_trunk_info_t trunk_info;

        bcm_trunk_info_t_init(&trunk_info);

        member_array = sal_alloc(BCM_TRUNK_MAX_PORTCNT * sizeof(bcm_trunk_member_t),
                                 "trunk_array");
        if (member_array == NULL) {
            return BCM_E_MEMORY;
        }
        rv = bcm_esw_trunk_get(unit, tgid, &trunk_info, BCM_TRUNK_MAX_PORTCNT,
                               member_array, &member_count);
        if (BCM_FAILURE(rv)) {
            sal_free(member_array);
            return rv;
        }

        /* coverity[dead_error_condition] */
        switch(fwd_reason) {
            case bcmSwitchPktHashInfoFwdReasonIpmc:
                port_index = trunk_info.ipmc_index;
                break;
            case bcmSwitchPktHashInfoFwdReasonL2mc:
                port_index = trunk_info.mc_index;
                break;
            case bcmSwitchPktHashInfoFwdReasonBcast:
            case bcmSwitchPktHashInfoFwdReasonDlf:
                port_index = trunk_info.dlf_index;
                break;
            default:
                sal_free(member_array);
                return BCM_E_PARAM;
        }

        if (port_index != BCM_TRUNK_UNSPEC_INDEX) {
            if (port_index >= member_count) {
                *dst_gport = -1;
                sal_free(member_array);
                return BCM_E_NOT_FOUND;
            }
            *dst_gport = member_array[port_index].gport;
        } else {
            port_array = sal_alloc(member_count * sizeof(bcm_gport_t),
                                   "port_array");
            if (port_array == NULL) {
                sal_free(member_array);
                return BCM_E_MEMORY;
            }
            port_count = 0;
            all_local = TRUE;
            for (i = 0; i < member_count; i++) {
                if (member_array[i].flags & disable_flags) {
                    continue;
                }
                port = member_array[i].gport;
                port_array[port_count++] = port;
                if (all_local) {
                    if (BCM_FAILURE(bcm_esw_port_local_get(unit, port,
                                                            &port))) {
                        all_local = FALSE;
                    }
                }
            }
            /* All ports are disabled */
            if (port_count == 0) {
                *dst_gport = -1;
                sal_free(port_array);
                sal_free(member_array);
                return BCM_E_NOT_FOUND;
            }
            if (all_local || port_count > BCM_SWITCH_TRUNK_MAX_PORTCNT) {
                region_size = soc_mem_index_count(unit, NONUCAST_TRUNK_BLOCK_MASKm) / 4;
            } else {
                region_size = BCM_XGS3_TRUNK_MAX_PORTCNT;
            }
            port_index = (nuc_tbm_index % region_size) % port_count;
            *dst_gport = port_array[port_index];
            sal_free(port_array);
            sal_free(member_array);
        }
    } else {
        _bcm_gport_dest_t   dest;

        /*Each index only has one egress port */
        BCM_PBMP_ITER(local_pbmp, port) {
            break;
        }

        if (port == BCM_PBMP_PORT_MAX) {
            /* If not found in iteration, return not found. It never be here */
            *dst_gport = -1;
            return BCM_E_NOT_FOUND;
        }
        BCM_IF_ERROR_RETURN(bcm_esw_stk_my_modid_get(unit, &modid));

        BCM_IF_ERROR_RETURN
            (_bcm_esw_stk_modmap_map(unit, BCM_STK_MODMAP_GET, modid, port,
                                            &(dest.modid), &(dest.port)));
        if (IS_ST_PORT(unit, port)) {
            dest.port = port;
            dest.gport_type = _SHR_GPORT_TYPE_DEVPORT;
        } else {
            dest.gport_type = _SHR_GPORT_TYPE_MODPORT;
        }

        BCM_IF_ERROR_RETURN(_bcm_esw_gport_construct(unit, &dest, dst_gport));
    }

    return BCM_E_NONE;
}

STATIC int
get_th_hash_hg_trunk(int unit, int hgtid, uint32 hash_index,
                bcm_gport_t *dst_tgid)
{
    /* Low and balanced latency mode don't support HG trunk */
    uint32 trunk_base;
    uint32 trunk_group_size;
    uint32 rtag;
    uint32 trunk_index;
    uint32 trunk_member_table_index;
    bcm_module_t mod_id;
    bcm_port_t port_id;
    hg_trunk_member_entry_t hg_trunk_member_entry;
    hg_trunk_group_entry_t  hg_tg_entry;
    _bcm_gport_dest_t   dest;

    BCM_IF_ERROR_RETURN
        (READ_HG_TRUNK_GROUPm(unit, MEM_BLOCK_ANY, hgtid, &hg_tg_entry));

    trunk_base           = soc_HG_TRUNK_GROUPm_field32_get(unit, &hg_tg_entry, BASE_PTRf);
    trunk_group_size     = soc_HG_TRUNK_GROUPm_field32_get(unit, &hg_tg_entry, TG_SIZEf);
    rtag                 = soc_HG_TRUNK_GROUPm_field32_get(unit, &hg_tg_entry, RTAGf);

    if (rtag != 7) {
         LOG_VERBOSE(BSL_LS_BCM_COMMON,
                     (BSL_META_U(unit,
                                 "Hash calculation: uport only RTAG7 calc no support for rtag %d\n"),
                      rtag));
    }

    trunk_index = hash_index % (trunk_group_size + 1);
    trunk_member_table_index = (trunk_base + trunk_index) & 0xff;
    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "\tHG Trunk HW index 0x%08x\n"),
                 trunk_index));
    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "\tHG Trunk group size 0x%08x\n"),
                 trunk_group_size));
    BCM_IF_ERROR_RETURN
        (READ_HG_TRUNK_MEMBERm(unit, MEM_BLOCK_ANY, trunk_member_table_index,
                                    &hg_trunk_member_entry));
    port_id = soc_HG_TRUNK_MEMBERm_field32_get(unit, &hg_trunk_member_entry,
                                    PORT_NUMf);
    if (BCM_FAILURE(bcm_esw_stk_my_modid_get(unit, &mod_id))) {
        mod_id = 0;
    }
    BCM_IF_ERROR_RETURN
        (_bcm_esw_stk_modmap_map(unit, BCM_STK_MODMAP_GET, mod_id, port_id,
                                        &(dest.modid), &(dest.port)));
    dest.gport_type = _SHR_GPORT_TYPE_DEVPORT;
    BCM_IF_ERROR_RETURN(_bcm_esw_gport_construct(unit, &dest, dst_tgid));

    return BCM_E_NONE;
}

/*
 * Function:
 *          _bcm_th_switch_pkt_info_hash_get
 * Description:
 *          main th hash get function
 *
 * Parameters
 *  unit - StrataSwitch PCI device unit number (driver internal).
 *  pkt_info - struct that carries packet's l2, l3, and l4 information
 *  dst_gport - hashing resolved trunk member port as a return val
 *  dst_intf  - hashing resolved ecmp  member port as a return val
 *              or entropy label of vxlan as a return val
 * Returns:
 *      BCM_E_xxxx
 *
 */
int
_bcm_th_switch_pkt_info_hash_get(int unit,
                                   bcm_switch_pkt_info_t *pkt_info,
                                   bcm_gport_t *dst_gport,
                                   bcm_if_t *dst_intf)
{
    bcm_rtag7_base_hash_t hash_res;
    int pc_out, mod_is_local;
    bcm_gport_t     port;
    bcm_trunk_t     tid;
    int             id;
    int             rc;

    if (pkt_info == NULL) {
        return BCM_E_PARAM;
    }

    if (!_BCM_SWITCH_PKT_INFO_FLAG_TEST(pkt_info, SRC_GPORT)) {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "Hash calculation: source gport value missing\n")));
        return BCM_E_PARAM;
    }

    rc = _bcm_esw_gport_resolve(unit, pkt_info->src_gport,
                                &(hash_res.src_modid),
                                &(hash_res.src_port),
                                &tid, &id);
    if (rc != BCM_E_NONE) {
        return rc;
    }

    if ((-1 != id) || (-1 != tid)) {
        /* Must be single system port */
        return BCM_E_PORT;
    }

    /* If dual module mode enable, mod/port should be in PORT32 format */
    BCM_IF_ERROR_RETURN
        (_bcm_esw_stk_modmap_map(unit, BCM_STK_MODMAP_GET,
                                 hash_res.src_modid, hash_res.src_port,
                                 &hash_res.src_modid, &hash_res.src_port));
    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "src_gport=0x%x, src_modid = %d, src_port=%d\n"),
                pkt_info->src_gport, hash_res.src_modid, hash_res.src_port));

    /* Load balancing retrieval */
    BCM_IF_ERROR_RETURN(
        _bcm_esw_modid_is_local(unit, hash_res.src_modid, &mod_is_local));
    if (mod_is_local) {
        BCM_IF_ERROR_RETURN
            (bcm_esw_port_local_get(unit, pkt_info->src_gport, &port));
        hash_res.dev_src_port = port;
    } else {
        hash_res.dev_src_port = -1;
        if (BCM_GPORT_IS_PROXY(pkt_info->src_gport)) {
            port = pkt_info->src_gport;
        } else {
            BCM_GPORT_PROXY_SET(port,
                hash_res.src_modid, hash_res.src_port);
        }
    }
    BCM_IF_ERROR_RETURN
        (bcm_esw_port_control_get(unit, port,
                                  bcmPortControlLoadBalancingNumber,
                                  &pc_out));
    hash_res.rtag7_port_lbn = pc_out;

    /* check if the foward reason of packet is all non-uc packet or bit 40 in the mac DA is one. */
    hash_res.is_nonuc = pkt_info->fwd_reason || BCM_MAC_IS_MCAST(pkt_info->dst_mac);

    BCM_IF_ERROR_RETURN
        (main_th_do_rtag7_hashing(unit, pkt_info, &hash_res));
    BCM_IF_ERROR_RETURN
        (main_th_compute_lbid(unit, &hash_res));

    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "Hash status: \n")));
    if (hash_res.hash_a_valid) {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tRTAG7 A0 0x%08x\n"),
                     hash_res.rtag7_hash16_value_a_0));
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tRTAG7 A1 0x%08x\n"),
                     hash_res.rtag7_hash16_value_a_1));
    } else {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tRTAG7 A hashes invalid due to missing packet info\n")));
    }
    if (hash_res.hash_b_valid) {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tRTAG7 B0 0x%08x\n"),
                     hash_res.rtag7_hash16_value_b_0));
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tRTAG7 B1 0x%08x\n"),
                     hash_res.rtag7_hash16_value_b_1));
    } else {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tRTAG7 B hashes invalid due to missing packet info\n")));
    }
    LOG_VERBOSE(BSL_LS_BCM_COMMON,
                (BSL_META_U(unit,
                            "\tRTAG7 LBN 0x%08x\n"),
                 hash_res.rtag7_port_lbn));
    if (hash_res.lbid_hash_valid){
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tRTAG7 LBID 0x%08x\n"),
                     hash_res.rtag7_lbid_hash));
    } else {
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tRTAG7 LBID not valid due to non-RTAG7 configuration\n")));
    }
#ifdef INCLUDE_L3
    if (0 != (pkt_info->flags & BCM_SWITCH_PKT_INFO_HASH_MULTIPATH)) {
        bcm_if_t        nh_id;
        uint8           ecmp_rh_enable;
        int             ecmp_lb_mode;
        int             hie_ecmp_mode = 0;
        uint32          temp_hash_val[2] = {0};
        uint32          hash_value[2] = {0};
        uint32          hash_rh_value[2] = {0};
        nh_id = 0;

        if (dst_intf == NULL) {
            return BCM_E_PARAM;
        }
        BCM_IF_ERROR_RETURN(
            get_th_ecmp_lb_mode(unit, pkt_info->mpintf - BCM_XGS3_MPATH_EGRESS_IDX_MIN(unit),
                                &ecmp_lb_mode));
        if ((ecmp_lb_mode == MODE_RANDOM) || (ecmp_lb_mode == MODE_ROUND_ROBIN)) {
            return BCM_E_UNAVAIL;
        }
        /* use soc_feature_fast_ecmp can decide it works in balanced mode */
        if (soc_feature(unit, soc_feature_hierarchical_ecmp) &&
            (BCM_XGS3_L3_TBL(unit, ecmp_info).ecmp_mode ==
             TH_ECMP_MODE_HIERARCHICAL)) {
            hie_ecmp_mode = 1;
        }
        if (ecmp_lb_mode == MODE_RES_HASH) {
            ecmp_rh_enable = TRUE;
            hash_value[0] = hash_value[1] = 0;
            rc = compute_th_ecmp_rh_hash(unit, &hash_res, hash_rh_value);
            if (rc != BCM_E_NONE) {
                return rc;
            }
            LOG_VERBOSE(BSL_LS_BCM_COMMON,
                        (BSL_META_U(unit,
                                    "\tECMP Hash rh value 0x%08x\n"),
                         hash_rh_value[0]));
            /* The 2nd level doesn't support RH hashing */
            if (hie_ecmp_mode) {
                rc = compute_th_ecmp_hash(unit, &hash_res, temp_hash_val, 1);
                if (rc != BCM_E_NONE) {
                    return rc;
                }
                hash_rh_value[1] = temp_hash_val[1];
                LOG_VERBOSE(BSL_LS_BCM_COMMON,
                            (BSL_META_U(unit,
                                        "\tECMP Level2 Hash rh value 0x%08x\n"),
                             hash_rh_value[1]));

            }
        } else {
            ecmp_rh_enable = FALSE;
            hash_rh_value[0] = hash_rh_value[1] = 0;
            rc = compute_th_ecmp_hash(unit, &hash_res, hash_value, hie_ecmp_mode);
            if (rc != BCM_E_NONE) {
                return rc;
            }
            LOG_VERBOSE(BSL_LS_BCM_COMMON,
                        (BSL_META_U(unit,
                                    "\tECMP Hash value 0x%08x\n"),
                         hash_value[0]));
            if (hie_ecmp_mode) {
                LOG_VERBOSE(BSL_LS_BCM_COMMON,
                            (BSL_META_U(unit,
                                        "\tECMP Level2 Hash value 0x%08x\n"),
                             hash_value[1]));
            }
        }
        rc = get_th_hash_ecmp(unit,
                              pkt_info->mpintf - BCM_XGS3_MPATH_EGRESS_IDX_MIN(unit),
                              hash_value, hash_rh_value, &nh_id,
                              ecmp_rh_enable, hie_ecmp_mode);
        /* Convert to egress object format */
        *dst_intf = nh_id + BCM_XGS3_EGRESS_IDX_MIN(unit);
    } else
#endif /* INCLUDE_L3 */
    if (0 != (pkt_info->flags & BCM_SWITCH_PKT_INFO_HASH_TRUNK)) {
        int member_count;
        bcm_trunk_t trunk;
        bcm_trunk_chip_info_t   ti;
        uint32          hash_value;
        if (dst_gport == NULL) {
            return BCM_E_PARAM;
        }

        trunk = BCM_TRUNK_INVALID;
        if (!BCM_GPORT_IS_TRUNK(pkt_info->trunk_gport)) {
            return BCM_E_PORT;
        }
        trunk = BCM_GPORT_TRUNK_GET(pkt_info->trunk_gport);
        BCM_IF_ERROR_RETURN
            (bcm_esw_trunk_get(unit, trunk, NULL, 0, NULL, &member_count));
        if (0 == member_count) {
            /* Return failure for no trunk members */
            return BCM_E_FAIL;
        }
        BCM_IF_ERROR_RETURN(bcm_esw_trunk_chip_info_get(unit, &ti));
        if (trunk >= ti.trunk_id_min && trunk <= ti.trunk_id_max) {
            rc = compute_th_rtag7_hash_trunk(unit, &hash_res, &hash_value);
            if (rc != BCM_E_NONE) {
                return rc;
            }
            LOG_VERBOSE(BSL_LS_BCM_COMMON,
                        (BSL_META_U(unit,
                                    "\tTrunk Hash value 0x%08x\n"),
                         hash_value));

            if (hash_res.is_nonuc) {
                BCM_IF_ERROR_RETURN
                    (get_th_hash_trunk_nuc(unit, trunk, pkt_info->fwd_reason,
                                hash_value, dst_gport));
            } else {
                BCM_IF_ERROR_RETURN
                    (get_th_hash_trunk(unit, trunk,
                                        hash_value, dst_gport));
            }
        } else if (trunk >= ti.trunk_fabric_id_min && trunk <= ti.trunk_fabric_id_max) {
            rc = compute_th_rtag7_hash_hg_trunk(unit, &hash_res, &hash_value);
            if (rc != BCM_E_NONE) {
                return rc;
            }
            LOG_VERBOSE(BSL_LS_BCM_COMMON,
                        (BSL_META_U(unit,
                                    "\tHG-Trunk Hash value 0x%08x\n"),
                         hash_value));

            BCM_IF_ERROR_RETURN
                (get_th_hash_hg_trunk(unit, trunk - ti.trunk_fabric_id_min,
                                    hash_value, dst_gport));

        }
    } else if (pkt_info->flags & BCM_SWITCH_PKT_INFO_HASH_UDP_SOURCE_PORT) {
        /* vxlan hashing resolution */
        uint32 hash_value;
        rc = compute_th_rtag7_vxlan(unit, &hash_res, &hash_value);
        if (rc != BCM_E_NONE) {
            return rc;
        }
        LOG_VERBOSE(BSL_LS_BCM_COMMON,
                    (BSL_META_U(unit,
                                "\tVXlan Hash value 0x%08x\n"),
                     hash_value));
        *dst_intf = hash_value;
    } else if (pkt_info->flags & BCM_SWITCH_PKT_INFO_HASH_LBID) {
        /* LBID hashing resolution */
        if (dst_intf == NULL || hash_res.lbid_hash_valid == 0) {
            return BCM_E_FAIL;
        } else {
            *dst_intf = hash_res.rtag7_lbid_hash;
        }
    } else {
        return BCM_E_PARAM;
    }
    return BCM_E_NONE;
}



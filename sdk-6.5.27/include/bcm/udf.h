/*
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

#ifndef __BCM_UDF_H__
#define __BCM_UDF_H__

#include <bcm/types.h>
#include <bcm/field.h>

/* Options to control UDF allocation */
#define BCM_UDF_CREATE_O_NONE           (0)        /* Default. */
#define BCM_UDF_CREATE_O_WITHID         (1 << 0)   /* Use input UDF ID instead
                                                      of allocating one. */
#define BCM_UDF_CREATE_O_REPLACE        (1 << 1)   /* Replace/Update existing
                                                      UDF object. */
#define BCM_UDF_CREATE_O_FLEXHASH       (1 << 2)   /* UDF allocation will be
                                                      adjusted for use by flex
                                                      hashing feature. */
#define BCM_UDF_CREATE_O_FIELD_INGRESS  (1 << 3)   /* UDF allocation will be
                                                      adjusted for use by
                                                      Ingress stage FP. */
#define BCM_UDF_CREATE_O_FIELD_LOOKUP   (1 << 4)   /* UDF allocation will be
                                                      adjusted for use by Lookup
                                                      stage FP. */
#define BCM_UDF_CREATE_O_SHARED_HWID    (1 << 5)   /* Use same hardware
                                                      resources as 'shared_udf' */
#define BCM_UDF_CREATE_O_POLICER_GROUP  (1 << 6)   /* UDF allocation will be
                                                      adjusted for use by global
                                                      (service) meter. */
#define BCM_UDF_CREATE_O_UDFHASH        (1 << 7)   /* UDF allocation will be
                                                      adjusted for use by udf
                                                      hashing feature. */
#define BCM_UDF_CREATE_O_RANGE_CHECK    (1 << 8)   /* UDF allocation will be
                                                      adjusted for use by Range
                                                      checker. */
#define BCM_UDF_CREATE_O_FLEX_COUNTER   (1 << 9)   /* UDF allocation will be
                                                      adjusted for use by
                                                      Flexible Counter. */

/* UDF Packet Format Options */
#define BCM_UDF_PKT_FORMAT_CREATE_O_NONE    0          /* Default. */
#define BCM_UDF_PKT_FORMAT_CREATE_O_WITHID  (1 << 0)   /* Create packet format
                                                          with given ID */
#define BCM_UDF_PKT_FORMAT_CREATE_O_REPLACE (1 << 1)   /* Update existing packet
                                                          format */

/* Packet format options */
typedef uint32 bcm_udf_pkt_format_options_t;

/* Flags to be used with bcm_udf_t.flags */
#define BCM_UDF_F_ADJUST_IP4_OPTIONS    (1 << 1)   /* Adjust offset accounting
                                                      IP4 options */
#define BCM_UDF_F_ADJUST_IP6_OPTIONS    (1 << 2)   /* Adjust offset accounting
                                                      IP6 Extension Headers */

/* Base header the switch can parse. */
typedef enum bcm_udf_layer_e {
    bcmUdfLayerL2Header = 1,            /* Start of L2 header in the Packet */
    bcmUdfLayerL3OuterHeader = 2,       /* Start of outer L3 header in the
                                           packet */
    bcmUdfLayerL3InnerHeader = 3,       /* Start of inner L3 header in the
                                           packet */
    bcmUdfLayerL4OuterHeader = 4,       /* Start of outer L4 header in the
                                           packet */
    bcmUdfLayerL4InnerHeader = 5,       /* Start of outer L4 header in the
                                           packet */
    bcmUdfLayerHigigHeader = 6,         /* Start of HiGig header in the packet */
    bcmUdfLayerHigig2Header = 7,        /* Start of HiGig2 header in the packet */
    bcmUdfLayerTunnelHeader = 8,        /* Start of outermost tunnel header in
                                           the Packet */
    bcmUdfLayerTunnelPayload = 9,       /* Start of outermost tunnel payload in
                                           the Packet */
    bcmUdfLayerUserPayload = 10,        /* Start of application payload in the
                                           Packet. */
    bcmUdfLayerIpSecondExtensionHeader = 11, /* Start of second IP extension header
                                           for packet with 2 or more extension
                                           header. */
    bcmUdfLayerCount                    /* Unused. Always last in the list */
} bcm_udf_layer_t;

#define BCM_UDF_LAYER \
{ \
    "", \
    "L2Header", \
    "L3OuterHeader", \
    "L3InnerHeader", \
    "L4OuterHeader", \
    "L4InnerHeader", \
    "HigigHeader", \
    "Higig2Header", \
    "TunnelHeader", \
    "TunnelPayload", \
    "UserPayload", \
    "IpSecondExtensionHeader"  \
}

/* UDF structure. */
typedef struct bcm_udf_s {
    uint32 flags;           /* See BCM_UDF_F_XXX */
    bcm_udf_layer_t layer;  /* UDF base offset. bcmUdfLayerXxx */
    int start;              /* Relative offset in bits (from the 'layer') in the
                               packet */
    uint32 width;           /* width of data in bits to extract */
    bcm_pbmp_t ports;       /* ports (must belong to a single pipe) associate
                               with the udf_offset: used only in PipeLocal
                               operation supported devices */
} bcm_udf_t;

/* UDF allocation hints. */
typedef struct bcm_udf_alloc_hints_s {
    uint32 flags;               /* See BCM_UDF_CREATE_O_xxx */
    bcm_udf_id_t shared_udf;    /* Used when BCM_UDF_CREATE_O_SHARED_HWID is set */
    bcm_field_qset_t qset;      /* Field group qset for optimal H/W resource
                                   allocation */
} bcm_udf_alloc_hints_t;

/* Packet format based UDF specification structure. */
typedef struct bcm_udf_pkt_format_info_s {
    int prio;                           /* Priority of the UDF */
    bcm_ethertype_t ethertype;          /* EtherType in the packet */
    bcm_ethertype_t ethertype_mask;     /* EtherType Mask */
    uint8 ip_protocol;                  /* IP protocol field in the packet */
    uint8 ip_protocol_mask;             /* IP protocol Mask */
    uint16 l2;                          /* L2 packet format.
                                           (BCM_PKT_FORMAT_L2_XXX) */
    uint16 vlan_tag;                    /* Vlan tag format.
                                           (BCM_PKT_FORMAT_VLAN_XXX) */
    uint16 outer_ip;                    /* Outer IP header type.
                                           (BCM_PKT_FORMAT_IP_XXX) */
    uint16 inner_ip;                    /* Inner IP header type.
                                           (BCM_PKT_FORMAT_IP_XXX) */
    uint16 tunnel;                      /* Tunnel type.
                                           (BCM_PKT_FORMAT_TUNNEL_XXX) */
    uint16 mpls;                        /* Mpls labels.
                                           (BCM_PKT_FORMAT_MPLS_XXX) */
    uint16 fibre_chan_outer;            /* Fibre Channel outer header type.
                                           (BCM_PKT_FORMAT_FIBRE_CHAN_XXX) */
    uint16 fibre_chan_inner;            /* Fibre Channel inner header
                                           type.(BCM_PKT_FORMAT_FIBRE_CHAN_XXX) */
    uint16 higig;                       /* HIGIG packet
                                           format.(BCM_PKT_FORMAT_HIGIG_XXX) */
    uint16 vntag;                       /* NIV packet
                                           format.(BCM_PKT_FORMAT_VNTAG_XXX) */
    uint16 etag;                        /* Extender tag packet
                                           format.(BCM_PKT_FORMAT_ETAG_XXX) */
    uint16 cntag;                       /* CNTAG packet
                                           format.(BCM_PKT_FORMAT_CNTAG_XXX) */
    uint16 icnm;                        /* ICNM packet
                                           format.(BCM_PKT_FORMAT_ICNM_XXX) */
    uint16 subport_tag;                 /* SUBPORT_TAG packet format.
                                           (BCM_PKT_FORMAT_SUBPORT_TAG_XXX) */
    int class_id;                       /* id used by the IFP Key Selection
                                           Mechanism. Range 0~255 */
    uint16 inner_protocol;              /* Inner protocol field in the packet.
                                           Inner_ip should be set to
                                           BCM_PKT_FORMAT_IP_NONE to make this
                                           take effect. IP-IN-IP type GRE should
                                           take original API sequence. */
    uint16 inner_protocol_mask;         /* Inner protocol mask. */
    uint32 l4_dst_port;                 /* TCP or UDP Destination Port number. */
    uint32 l4_dst_port_mask;            /* TCP or UDP Destination Port number
                                           mask. */
    uint8 opaque_tag_type;              /* Tag type field in the opaque tag. */
    uint8 opaque_tag_type_mask;         /* Mask for tag type field in the opaque
                                           tag. */
    uint8 int_pkt;                      /* Inband Telemetry packet indicator. */
    uint8 src_port;                     /* Logical Source Port number. */
    uint8 src_port_mask;                /* Logical Source Port number mask. */
    uint8 lb_pkt_type;                  /* Loopback Packet Type.
                                           (BCM_PKT_FORMAT_LB_TYPE_XXX) */
    uint16 first_2bytes_after_mpls_bos; /* First 2 bytes after BOS in an mpls
                                           packet. */
    uint16 first_2bytes_after_mpls_bos_mask; /* Mask for first 2 bytes after BOS in
                                           an mpls packet. */
    uint8 outer_ifa;                    /* Outer IFA header
                                           (BCM_PKT_FORMAT_IFA_XXX) */
    uint8 inner_ifa;                    /* Inner IFA header
                                           (BCM_PKT_FORMAT_IFA_XXX) */
    uint16 ip_gre_first_2bytes;         /* First 2 bytes after L3 when packet is
                                           first fragment in IP-GRE packets. */
    uint16 ip_gre_first_2bytes_mask;    /* Mask of first 2 bytes after L3 when
                                           packet is first fragment in IP-GRE
                                           packets. */
    uint8 dcn_pkt;                      /* DCN packet */
    uint8 dcn_pkt_mask;                 /* Mask of DCN packet */
    uint8 byte_after_bos_label;         /* Byte after BOS Label */
    uint8 byte_after_bos_label_mask;    /* Mask of Byte after BOS Label */
    uint8 dcn_shim_extn_byte;           /* DCN SHIM Extension Byte */
    uint8 dcn_shim_extn_byte_mask;      /* Mask of DCN SHIM Extension Byte */
    uint8 dcn_shim_flags;               /* DCN SHIM Flags */
    uint8 dcn_shim_flags_mask;          /* Mask of DCN SHIM Flags */
    int gsh_header_type;                /* GSH Header Type */
    int module_header_type;             /* Module Header Type */
    uint8 svtag_present;                /* SVTAG present */
    uint8 svtag_present_mask;           /* Mask of SVTAG present */
} bcm_udf_pkt_format_info_t;

/* Maxmium bytes of UDF Hash */
#define BCM_UDF_HASH_MAX_LENGTH 4          

/* UDF hashing configuration. */
typedef struct bcm_udf_hash_config_s {
    uint32 flags;                       /* Reserved for future usage. Must be
                                           zero today. */
    bcm_udf_id_t udf_id;                /* UDF object id */
    int mask_length;                    /* Length of mask bytes. Must equal to
                                           the width of the UDF object. */
    uint8 hash_mask[BCM_UDF_HASH_MAX_LENGTH]; /* Array of mask fields. Index 0 is MSB
                                           of mask. */
} bcm_udf_hash_config_t;

/* UDF hashing engine selection. */
#define BCM_UDF_HASH_CONFIG_ENGINE_0    0x00000001 /* UDF is used by hash engine
                                                      0. */
#define BCM_UDF_HASH_CONFIG_ENGINE_1    0x00000002 /* UDF is used by hash engine
                                                      1. */

/* Options to control UDF hashing adding. */
#define BCM_UDF_HASH_ADD_O_NONE     0          /* Default, add new entry to
                                                  list. */
#define BCM_UDF_HASH_ADD_O_REPLACE  (1 << 0)   /* Modify the entry which is
                                                  already in list */

/* Initializes the UDF structure */
extern void bcm_udf_t_init(
    bcm_udf_t *udf_info);

/* Initializes the UDF alloc hints structure */
extern void bcm_udf_alloc_hints_t_init(
    bcm_udf_alloc_hints_t *udf_hints);

/* Initialize the UDF packet format structure */
extern void bcm_udf_pkt_format_info_t_init(
    bcm_udf_pkt_format_info_t *pkt_format);

/* Initialize the UDF hashing configuration structure */
extern void bcm_udf_hash_config_t_init(
    bcm_udf_hash_config_t *info);

#ifndef BCM_HIDE_DISPATCHABLE

/* Initialize UDF module */
extern int bcm_udf_init(
    int unit);

/* Detach UDF module */
extern int bcm_udf_detach(
    int unit);

/* Creates a UDF object */
extern int bcm_udf_create(
    int unit, 
    bcm_udf_alloc_hints_t *hints, 
    bcm_udf_t *udf_info, 
    bcm_udf_id_t *udf_id);

/* Fetches the UDF object created in the system */
extern int bcm_udf_get(
    int unit, 
    bcm_udf_id_t udf_id, 
    bcm_udf_t *udf_info);

/* Fetches all existing UDF ids */
extern int bcm_udf_get_all(
    int unit, 
    int max, 
    bcm_udf_id_t *udf_id_list, 
    int *actual);

/* Destroys the UDF object */
extern int bcm_udf_destroy(
    int unit, 
    bcm_udf_id_t udf_id);

/* Create a packet format entry */
extern int bcm_udf_pkt_format_create(
    int unit, 
    bcm_udf_pkt_format_options_t options, 
    bcm_udf_pkt_format_info_t *pkt_format, 
    bcm_udf_pkt_format_id_t *pkt_format_id);

/* Retrieve packet format info given the packet format Id */
extern int bcm_udf_pkt_format_info_get(
    int unit, 
    bcm_udf_pkt_format_id_t pkt_format_id, 
    bcm_udf_pkt_format_info_t *pkt_format);

/* Destroy existing packet format entry */
extern int bcm_udf_pkt_format_destroy(
    int unit, 
    bcm_udf_pkt_format_id_t pkt_format_id);

/* Adds packet format entry to UDF object */
extern int bcm_udf_pkt_format_add(
    int unit, 
    bcm_udf_id_t udf_id, 
    bcm_udf_pkt_format_id_t pkt_format_id);

/* Deletes packet format spec associated with the UDF */
extern int bcm_udf_pkt_format_get(
    int unit, 
    bcm_udf_pkt_format_id_t pkt_format_id, 
    int max, 
    bcm_udf_id_t *udf_id_list, 
    int *actual);

/* Deletes packet format spec associated with the UDF */
extern int bcm_udf_pkt_format_delete(
    int unit, 
    bcm_udf_id_t udf_id, 
    bcm_udf_pkt_format_id_t pkt_format_id);

/* Retrieves the user defined format specification configuration from UDF */
extern int bcm_udf_pkt_format_get_all(
    int unit, 
    bcm_udf_id_t udf_id, 
    int max, 
    bcm_udf_pkt_format_id_t *pkt_format_id_list, 
    int *actual);

/* Deletes all packet format specs associated with the UDF */
extern int bcm_udf_pkt_format_delete_all(
    int unit, 
    bcm_udf_id_t udf_id);

/* Add UDF id into UDF hashing list */
extern int bcm_udf_hash_config_add(
    int unit, 
    uint32 options, 
    bcm_udf_hash_config_t *config);

/* Delete UDF id from UDF hashing list */
extern int bcm_udf_hash_config_delete(
    int unit, 
    bcm_udf_hash_config_t *config);

/* Delete all UDF id from UDF hashing list */
extern int bcm_udf_hash_config_delete_all(
    int unit);

/* Get UDF hashing configuration of a certain id */
extern int bcm_udf_hash_config_get(
    int unit, 
    bcm_udf_hash_config_t *config);

/* Get all added UDF ids from list */
extern int bcm_udf_hash_config_get_all(
    int unit, 
    int max, 
    bcm_udf_hash_config_t *config_list, 
    int *actual);

#endif /* BCM_HIDE_DISPATCHABLE */

/* 
 * List of UDF operational modes supported: used only in PipeLocal
 * operation supported devices
 */
typedef enum bcm_udf_oper_mode_e {
    bcmUdfOperModeGlobal = 0,       /* UDF Operational Global Mode Value. */
    bcmUdfOperModePipeLocal = 1,    /* UDF Operational Pipe Local Mode Value. */
    bcmUdfOperModeCount = 2         /* Always last. Not a usable value. */
} bcm_udf_oper_mode_t;

#define BCM_UDF_OPER_MODE_STRINGS \
{ \
    "Global", \
    "PipeLocal"  \
}

#ifndef BCM_HIDE_DISPATCHABLE

/* Set UDF operation mode */
extern int bcm_udf_oper_mode_set(
    int unit, 
    bcm_udf_oper_mode_t mode);

/* get UDF operation mode */
extern int bcm_udf_oper_mode_get(
    int unit, 
    bcm_udf_oper_mode_t *mode);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Base header the switch can parse. */
typedef enum bcm_udf_abstract_pkt_format_e {
    bcmUdfAbstractPktFormatLlc = 0,     /* Abstract from the start of LLC
                                           Header. */
    bcmUdfAbstractPktFormatInnerLlc = 1, /* Abstract from the start of Inner LLC
                                           Header. */
    bcmUdfAbstractPktFormatUnknownL3 = 2, /* Abstract from the start of unknown
                                           EtherType. */
    bcmUdfAbstractPktFormatInnerUnknownL3 = 3, /* Abstract from the start of inner
                                           unknown EtherType. */
    bcmUdfAbstractPktFormatKnownNonIp = 4, /* Abstract from the start of known
                                           non-ip EtherType (other than Known
                                           IPv4/6 and FCoE/Mim/MPLS tunnels). */
    bcmUdfAbstractPktFormatInnerKnownNonIp = 5, /* Abstract from the start of inner
                                           Known non-ip EtherType (other than
                                           Known IPv4/6 and FCoE/Mim/MPLS
                                           tunnels). */
    bcmUdfAbstractPktFormatKnownL3Mim = 6, /* Abstract from the start of MiM
                                           Header. */
    bcmUdfAbstractPktFormatKnownL3FcoeStdEncap = 7, /* Abstract from the start of FCoE with
                                           Standard or Encapsulation Header. */
    bcmUdfAbstractPktFormatKnownL3FcoeVftIfr = 8, /* Abstract from the start of FCoE with
                                           Virtual Fabric Tag (VFT) or Inter
                                           Fabric Routing (IFR) Header. */
    bcmUdfAbstractPktFormatKnownL3MplsOneLabel = 9, /* Abstract from the start of MPLS
                                           Header with one label. */
    bcmUdfAbstractPktFormatKnownL3MplsTwoLabel = 10, /* Abstract from the start of MPLS
                                           Header with two labels. */
    bcmUdfAbstractPktFormatKnownL3MplsThreeLabel = 11, /* Abstract from the start of MPLS
                                           Header with three labels. */
    bcmUdfAbstractPktFormatKnownL3MplsFourLabel = 12, /* Abstract from the start of MPLS
                                           Header with four labels. */
    bcmUdfAbstractPktFormatKnownL3MplsMoreThanFourLabel = 13, /* Abstract from the start of MPLS
                                           Header with more than four labels. */
    bcmUdfAbstractPktFormatUnknownL4 = 14, /* Abstract from the start of unknown L4
                                           Header. */
    bcmUdfAbstractPktFormatInnerUnknownL4 = 15, /* Abstract from the start of Inner
                                           unknown L4 Header. */
    bcmUdfAbstractPktFormatUdpUnknownL5 = 16, /* Abstract from the start of unknown L5
                                           after UDP Header. */
    bcmUdfAbstractPktFormatInnerUdpUnknownL5 = 17, /* Abstract from the start of Inner
                                           unknown L5 after UDP Header. */
    bcmUdfAbstractPktFormatUdpGpeGeneve = 18, /* Abstract from the start of known L5
                                           Geneve header after UDP. */
    bcmUdfAbstractPktFormatUdpBfd = 19, /* Abstract from the start of known L5
                                           BFD header after UDP. */
    bcmUdfAbstractPktFormatInnerUdpBfd = 20, /* Abstract from the start of inner
                                           known L5 BFD header after UDP. */
    bcmUdfAbstractPktFormatUdpVxlan = 21, /* Abstract from the start of known L5
                                           VXLAN header after UDP. */
    bcmUdfAbstractPktFormatUdp1588 = 22, /* Abstract from the start of known L5
                                           1588 header after UDP. */
    bcmUdfAbstractPktFormatTcpUnknownL5 = 23, /* Abstract from the start of unknown L5
                                           header after TCP. */
    bcmUdfAbstractPktFormatInnerTcpUnknownL5 = 24, /* Abstract from the start of inner
                                           unknown L5 header after TCP. */
    bcmUdfAbstractPktFormatSctpUnknownL5 = 25, /* Abstract from the start of unknown L5
                                           header after SCTP. */
    bcmUdfAbstractPktFormatInnerSctpUnknownL5 = 26, /* Abstract from the start of Inner
                                           unknown L5 header after SCTP. */
    bcmUdfAbstractPktFormatGreWithoutKey = 27, /* Abstract from the start of L4 header
                                           for GRE packets without key flag set
                                           (C=0/1, R=0/1 and K=0). */
    bcmUdfAbstractPktFormatGreWithKey = 28, /* Abstract from the start L4 header for
                                           GRE packets with key flag set (C=1,
                                           R=0/1 and K=1). */
    bcmUdfAbstractPktFormatGreWithoutChecksumRouting = 29, /* Abstract from the start of L4 header
                                           for GRE packets (with flags C=0, R=0
                                           and K=1). */
    bcmUdfAbstractPktFormatL2GreWithoutChecksumRouting = 30, /* Abstract from the start of L4 header
                                           for L2-GRE packets (with flags C=0,
                                           R=0, K=1). */
    bcmUdfAbstractPktFormatL2GreWithoutRouting = 31, /* Abstract from the start of L4 header
                                           for L2-GRE packets (with flags R=0,
                                           C=1, K=1). */
    bcmUdfAbstractPktFormatAchNonIp = 32, /* Abstract from the start of ACH Header
                                           for a NonIp packet. */
    bcmUdfAbstractPktFormatUdpINT = 33, /* Abstract from the start of UDP header
                                           to match on port based INT
                                           (Inband-Telemetry) header payload. */
    bcmUdfAbstractPktFormatTcpUnknownL5WithIpExtnHdr = 34, /* Abstract from the start of TCP header
                                           for unknown L5 packet. */
    bcmUdfAbstractPktFormatL3GreUnknownPayload = 35, /* Abstract from the start of L3 GRE
                                           header for unknown GRE type packets. */
    bcmUdfAbstractPktFormatGreWithKeyRouting = 36, /* Abstract from the start of L4 header
                                           for GRE packets (with key and routing
                                           flag set K=1, R=1, C=0/1). */
    bcmUdfAbstractPktFormatL2GreWithKeyRouting = 37, /* Abstract from the start of L4 header
                                           for L2-GRE packets (with flags K=1,
                                           R=1, C=0/1). */
    bcmUdfAbstractPktFormatInnerUdp1588 = 38, /* Abstract from the start of inner
                                           known L5 1588 header after UDP. */
    bcmUdfAbstractPktFormatTcpINT = 39, /* Abstract from the start of TCP header
                                           to match on INT (Inband-Telemetry)
                                           header payload. */
    bcmUdfAbstractPktFormatKnownL3FcoeUnknownRctl = 40, /* Abstract from the start of FCoE with
                                           Unknown R_CTL. */
    bcmUdfAbstractPktFormatHiGigPpd0 = 41, /* Abstract from the start of HiGig
                                           System Header. */
    bcmUdfAbstractPktFormatHiGigPpd0EHType0 = 42, /* Abstract from the start of HiGig
                                           System Header. */
    bcmUdfAbstractPktFormatHiGigPpd0EHType1 = 43, /* Abstract from the start of HiGig
                                           System Header. */
    bcmUdfAbstractPktFormatHiGigPpd0EHType2 = 44, /* Abstract from the start of HiGig
                                           System Header. */
    bcmUdfAbstractPktFormatHiGigPpd2 = 45, /* Abstract from the start of HiGig
                                           System Header. */
    bcmUdfAbstractPktFormatHiGigPpd2EHType0 = 46, /* Abstract from the start of HiGig
                                           System Header. */
    bcmUdfAbstractPktFormatHiGigPpd2EHType1 = 47, /* Abstract from the start of HiGig
                                           System Header. */
    bcmUdfAbstractPktFormatHiGigPpd2EHType2 = 48, /* Abstract from the start of HiGig
                                           System Header. */
    bcmUdfAbstractPktFormatGpeIOAM = 49, /* Abstract from the start of GPE IOAM. */
    bcmUdfAbstractPktFormatKnownMplsMcast = 50, /* Abstract from the start of MPLS
                                           Multicast header. */
    bcmUdfAbstractPktFormatLoopbackHdrType0 = 51, /* Abstract from the start of Loopback
                                           Type 0 System Header. */
    bcmUdfAbstractPktFormatLoopbackHdrType1 = 52, /* Abstract from the start of Loopback
                                           Type 1 System Header. */
    bcmUdfAbstractPktFormatL3Ipv4Fragmented = 53, /* Abstract from the start of L3 for
                                           IPv4 Fragmented packets (that is,
                                           non-zero fragmented offset) without
                                           IP options. */
    bcmUdfAbstractPktFormatL3Ipv4FragmentedWithOptions = 54, /* Abstract from the start of L3 for
                                           IPv4 Fragmented packets with IP
                                           options (that is, non-zero fragmented
                                           offset). */
    bcmUdfAbstractPktFormatL3Ipv4WithoutOptions = 55, /* Abstract from the start of L3 for
                                           IPv4 packets without IP options. */
    bcmUdfAbstractPktFormatL3Ipv4WithOptions = 56, /* Abstract from the start of L3 for
                                           IPv4 packets with IP options. */
    bcmUdfAbstractPktFormatL3Ipv6 = 57, /* Abstract from the start of L3 for
                                           IPv6 packet. */
    bcmUdfAbstractPktFormatL2 = 58,     /* Abstract from the start of L2 header. */
    bcmUdfAbstractPktFormatL2Untagged = 59, /* Abstract from the start of untagged
                                           VLAN */
    bcmUdfAbstractPktFormatL2OuterVlanTag = 60, /* Abstract from the start of outer VLAN
                                           tag. */
    bcmUdfAbstractPktFormatL2InnerVlanTag = 61, /* Abstract from the start of inner VLAN
                                           tag. */
    bcmUdfAbstractPktFormatL2DoubleVlanTag = 62, /* Abstract from the start of double
                                           VLAN tag. */
    bcmUdfAbstractPktFormatL2GbpTag = 63, /* Abstract from the start of GBP tag
                                           (without VLAN tag). */
    bcmUdfAbstractPktFormatL2OuterVlanWithGbpTag = 64, /* Abstract from the start of outer vlan
                                           and GBP tag. */
    bcmUdfAbstractPktFormatL2InnerVlanWithGbpTag = 65, /* Abstract from the start of inner vlan
                                           and GBP tag. */
    bcmUdfAbstractPktFormatL2DoubleVlanWithGbpTag = 66, /* Abstract from the start of double
                                           vlan and GBP tag. */
    bcmUdfAbstractPktFormatL2Vntag = 67, /* Abstract from the start of VNTAG
                                           (without vlan tag). */
    bcmUdfAbstractPktFormatL2OuterVlanWithVntag = 68, /* Abstract from the start of outer vlan
                                           tag and VNTAG. */
    bcmUdfAbstractPktFormatL2InnerVlanWithVntag = 69, /* Abstract from the start of inner vlan
                                           tag and VNTAG. */
    bcmUdfAbstractPktFormatL2DoubleVlanWithVntag = 70, /* Abstract from the start of double
                                           vlan tag and VNTAG. */
    bcmUdfAbstractPktFormatL2Etag = 71, /* Abstract from the start of ETAG
                                           (without vlan tag). */
    bcmUdfAbstractPktFormatL2OuterVlanEtag = 72, /* Abstract from the start of outer vlan
                                           tag and ETAG. */
    bcmUdfAbstractPktFormatL2InnerVlanEtag = 73, /* Abstract from the start of inner vlan
                                           tag and ETAG. */
    bcmUdfAbstractPktFormatL2DoubleVlanEtag = 74, /* Abstract from the start of double
                                           vlan tag and ETAG. */
    bcmUdfAbstractPktFormatInnerL3Ipv4 = 75, /* Abstract from the start of Inner L3
                                           IPv4 header. */
    bcmUdfAbstractPktFormatInnerL3Ipv4Fragmented = 76, /* Abstract from the start of Inner L3
                                           IPv4 header with non-zero fragment
                                           offset. */
    bcmUdfAbstractPktFormatInnerL3Ipv6 = 77, /* Abstract from the start of Inner L3
                                           IPv6 header. */
    bcmUdfAbstractPktFormatInnerL2Untagged = 78, /* Abstract from the start of inner
                                           untagged VLAN. */
    bcmUdfAbstractPktFormatInnerL2OuterVlanTag = 79, /* Abstract from the start of inner L2
                                           outer VLAN tag. */
    bcmUdfAbstractPktFormatInnerL2InnerVlanTag = 80, /* Abstract from the start of inner L2
                                           inner VLAN tag. */
    bcmUdfAbstractPktFormatInnerL2DoubleVlanTag = 81, /* Abstract from the start of inner L2
                                           Double VLAN tag. */
    bcmUdfAbstractPktFormatInnerL2GbpTag = 82, /* Abstract from the start of inner GBP
                                           tag (without VLAN tag). */
    bcmUdfAbstractPktFormatInnerL2OuterVlanWithGbpTag = 83, /* Abstract from the start of inner L2
                                           outer vlan and GBP tag. */
    bcmUdfAbstractPktFormatInnerL2InnerVlanWithGbpTag = 84, /* Abstract from the start of inner L2
                                           inner vlan and GBP tag. */
    bcmUdfAbstractPktFormatInnerL2DoubleVlanWithGbpTag = 85, /* Abstract from the start of Inner
                                           double vlan and GBP tag. */
    bcmUdfAbstractPktFormatUnknownL3CustomEtherType1 = 86, /* Abstract from the start of L3 unknown
                                           custom EtherType 1. */
    bcmUdfAbstractPktFormatUnknownL3CustomEtherType2 = 87, /* Abstract from the start of L3 unknown
                                           custom EtherType 2. */
    bcmUdfAbstractPktFormatUnknownL3CustomIpProtocol1 = 88, /* Abstract from the start of L4 unknown
                                           custom IP Protocol 1. */
    bcmUdfAbstractPktFormatUnknownL3CustomIpProtocol2 = 89, /* Abstract from the start of  L4
                                           unknown custom IP Protocol 2. */
    bcmUdfAbstractPktFormatUnknownL3CustomUdpDstPort1 = 90, /* Abstract from the start of L4 unknown
                                           custom UDP destination port 1. */
    bcmUdfAbstractPktFormatUnknownL3CustomUdpDstPort2 = 91, /* Abstract from the start of L4 unknown
                                           custom UDP destination port 2. */
    bcmUdfAbstractPktFormatInnerUnknownL3CustomEtherType1 = 92, /* Abstract from the start of inner L3
                                           unknown custom EtherType 1. */
    bcmUdfAbstractPktFormatInnerUnknownL3CustomEtherType2 = 93, /* Abstract from the start of inner L3
                                           unknown custom EtherType 2. */
    bcmUdfAbstractPktFormatInnerUnknownL3CustomIpProtocol1 = 94, /* Abstract from the start of inner L4
                                           unknown custom IP Protocol 1. */
    bcmUdfAbstractPktFormatInnerUnknownL3CustomIpProtocol2 = 95, /* Abstract from the start of inner L4
                                           unknown custom IP Protocol 2. */
    bcmUdfAbstractPktFormatInnerUnknownL3CustomUdpDstPort1 = 96, /* Abstract from the start of inner L4
                                           unknown custom UDP destination port
                                           1. */
    bcmUdfAbstractPktFormatInnerUnknownL3CustomUdpDstPort2 = 97, /* Abstract from the start of inner L4
                                           unknown custom UDP destination port
                                           2. */
    bcmUdfAbstractPktFormatUdpProbeBasedINT = 98, /* Abstract from the start of UDP header
                                           to match on probe based INT
                                           (Inband-Telemetry) header payload. */
    bcmUdfAbstractPktFormatMacsecDecrypt = 99, /* Abstract from the start of incoming
                                           MACSEC decrypted packet. */
    bcmUdfAbstractPktFormatGpeIOAMEdgeToEdge = 100, /* Abstract from the start of GPE header
                                           with IOAM type as E2E (Edge to Edge). */
    bcmUdfAbstractPktFormatUdpVxlanWithoutExtnHdr = 101, /* Start of UDP Header Without Extension
                                           header. */
    bcmUdfAbstractPktFormatUdp1588WithoutExtnHdr = 102, /* Start of UDP Header Without Extension
                                           header. */
    bcmUdfAbstractPktFormatUdpBfdWithoutExtnHdr = 103, /* Start of UDP Header Without Extension
                                           header. */
    bcmUdfAbstractPktFormatUdpProbeBasedINTWithoutExtnHdr = 104, /* Abstract from the start of UDP header
                                           to match on probe based INT
                                           (Inband-Telemetry) without extension
                                           header payload */
    bcmUdfAbstractPktFormatUdpINTWithoutExtnHdr = 105, /* Start of L4 UDP header for INT
                                           (Inband-Telemetry) packet without
                                           extension header. */
    bcmUdfAbstractPktFormatInnerTcpUnknownL5WithoutExtnHdr = 106, /* To extract Unknown L5 payload fields
                                           without extension header, the base
                                           start offset should be the first byte
                                           of inner TCP Header. */
    bcmUdfAbstractPktFormatUdpUnknownL5WithoutExtnHdr = 107, /* To extract Unknown L5 payload fields,
                                           the base start offset should be the
                                           first byte of UDP Header without
                                           extension header. */
    bcmUdfAbstractPktFormatInnerUdpBfdWithoutExtnHdr = 108, /* Start of Inner UDP Header Without
                                           Extension header. */
    bcmUdfAbstractPktFormatL2Cntag = 109, /* Start of L2 Cntag */
    bcmUdfAbstractPktFormatArp = 110,   /* Start of ARP */
    bcmUdfAbstractPktFormatIpv6HdrAuthExt1 = 111, /* Start of IPv6 Authentication first
                                           extension header */
    bcmUdfAbstractPktFormatIpv6HdrAuthExt2 = 112, /* Start of IPv6 Authentication second
                                           extension header */
    bcmUdfAbstractPktFormatL2EtherType = 113, /* Start of L2 Ethertype */
    bcmUdfAbstractPktFormatL3Ipv6HdrFragExt1 = 114, /* Start of L3 IPV4 Fragmented first
                                           extension header */
    bcmUdfAbstractPktFormatL3Ipv6HdrFragExt2 = 115, /* Start of L3 IPV4 Fragmented second
                                           extension header */
    bcmUdfAbstractPktFormatGpe = 116,   /* Start of GPE header */
    bcmUdfAbstractPktFormatGre = 117,   /* Start of Gre Header */
    bcmUdfAbstractPktFormatGreWithChecksum = 118, /* Start of Gre Header with Checksum
                                           flag */
    bcmUdfAbstractPktFormatGreWithSequence = 119, /* Start of GRE Header with Sequence
                                           flag */
    bcmUdfAbstractPktFormatIcmp = 120,  /* Start of ICMP header */
    bcmUdfAbstractPktFormatIgmp = 121,  /* Start of IGMP header */
    bcmUdfAbstractPktFormatL3Ipv4 = 122, /* Start of L3 IPv4 Header */
    bcmUdfAbstractPktFormatMplsAch = 123, /* Start of MPLS Ach */
    bcmUdfAbstractPktFormatMplsCw = 124, /* Start of MPLS Control word */
    bcmUdfAbstractPktFormatKnownL3MplsFiveLabel = 125, /* Start of Mpls with five labels */
    bcmUdfAbstractPktFormatKnownL3MplsSixLabel = 126, /* Start of Mpls with six labels */
    bcmUdfAbstractPktFormatKnownL3MplsSevenLabel = 127, /* Start of Mpls with seven labels */
    bcmUdfAbstractPktFormatRarp = 128,  /* Start of RARP */
    bcmUdfAbstractPktFormatL3RoutExt1 = 129, /* Start of L3 Route First Extension
                                           Header */
    bcmUdfAbstractPktFormatL3RoutExt2 = 130, /* Start of fL3 Route Second Extension
                                           Header */
    bcmUdfAbstractPktFormatL4Tcp = 131, /* Start of L4 TCP header */
    bcmUdfAbstractPktFormatL4Udp = 132, /* Start of L4 UDF header */
    bcmUdfAbstractPktFormatUnknownL5 = 133, /* Start of Unknown L5 header */
    bcmUdfAbstractPktFormatInnerL2Cntag = 134, /* Start of Inner L2 CNTAG */
    bcmUdfAbstractPktFormatInnerL2Etag = 135, /* Start of Inner L2 Etag */
    bcmUdfAbstractPktFormatInnerL2 = 136, /* Start of Inner L2 Header */
    bcmUdfAbstractPktFormatInnerL2Vntag = 137, /* Start of Inner L2 VNTAG */
    bcmUdfAbstractPktFormatInnerArp = 138, /* Start of Inner ARP */
    bcmUdfAbstractPktFormatInnerIpv6HdrAuthExt1 = 139, /* Start of first byte of Inner IPv6
                                           Authentication First Extension Header */
    bcmUdfAbstractPktFormatInnerIpv6HdrAuthExt2 = 140, /* Start of first byte of Inner IPv6
                                           Authentication Second Extension
                                           Header */
    bcmUdfAbstractPktFormatInnerL2EtherType = 141, /* Start of first byte of Inner L2
                                           Ethertype */
    bcmUdfAbstractPktFormatInnerL3Ipv6HdrFragExt1 = 142, /* Start of first byte of Inner L3 IPv6
                                           fragmentation first extension header */
    bcmUdfAbstractPktFormatInnerL3Ipv6HdrFragExt2 = 143, /* Start of first byte of Inner L3 IPv6
                                           fragmentation second extension header */
    bcmUdfAbstractPktFormatInnerIcmp = 144, /* Start of first byte of Inner ICMP */
    bcmUdfAbstractPktFormatInnerIgmp = 145, /* Start of first byte of Inner IGMP */
    bcmUdfAbstractPktFormatInnerRarp = 146, /* Start of Inner RARP */
    bcmUdfAbstractPktFormatInnerL4Tcp = 147, /* Start of Inner L4 TCP header */
    bcmUdfAbstractPktFormatInnerL4Udp = 148, /* Start of Inner L4 UDP header */
    bcmUdfAbstractPktFormatInnerUnknownL5 = 149, /* Start of Inner Unknown L5 header */
    bcmUdfAbstractPktFormatIfaUdp = 150, /* Start of UDP IFA header */
    bcmUdfAbstractPktFormatIfaTcp = 151, /* Start of TCP IFA header */
    bcmUdfAbstractPktFormatNshOverL2 = 152, /* Start of NSH header */
    bcmUdfAbstractPktFormatCesBackplane = 153, /* Start of L2 header for the packets
                                           received of CES backplane port */
    bcmUdfAbstractPktFormatLoopbackType1WithDropIndication = 154, /* Start of system header for Type 1
                                           Loopback header with drop indication */
    bcmUdfAbstractPktFormatGreHdrOfFourBytes = 155, /* Start of L4 header for GRE packets
                                           with 4 bytes header size */
    bcmUdfAbstractPktFormatGreHdrOfEightBytes = 156, /* Start of L4 header for GRE packets
                                           with 8 bytes header size */
    bcmUdfAbstractPktFormatGreHdrOfTwelveBytes = 157, /* Start of L4 header for GRE packets
                                           with 12 bytes header size */
    bcmUdfAbstractPktFormatGreHdrOfSixteenBytes = 158, /* Start of L4 header for GRE packets
                                           with 16 bytes header size */
    bcmUdfAbstractPktFormatGreHdrOfTwentyBytes = 159, /* Start of L4 header for GRE packets
                                           with 20 bytes header size */
    bcmUdfAbstractPktFormatL2GreHdrOfFourBytes = 160, /* Start of L4 header for L2-GRE packets
                                           with 4 bytes header size */
    bcmUdfAbstractPktFormatL2GreHdrOfEightBytes = 161, /* Start of L4 header for L2-GRE packets
                                           with 8 bytes header size */
    bcmUdfAbstractPktFormatL2GreHdrOfTwelveBytes = 162, /* Start of L4 header for L2-GRE packets
                                           with 12 bytes header size */
    bcmUdfAbstractPktFormatL2GreHdrOfSixteenBytes = 163, /* Start of L4 header for L2-GRE packets
                                           with 16 bytes header size */
    bcmUdfAbstractPktFormatL2GreHdrOfTwentyBytes = 164, /* Start of L4 header for L2-GRE packets
                                           with 20 bytes header size */
    bcmUdfAbstractPktFormatInnerUdpUnknownL5WithoutExtnHdr = 165, /* To extract Unknown L5 payload fields,
                                           the base start offset should be the
                                           first byte of Inner UDP Header
                                           without extension header. */
    bcmUdfAbstractPktFormatInnerUdp1588WithoutExtnHdr = 166, /* Start of inner UDP Header Without
                                           Extension header. */
    bcmUdfAbstractPktFormatL2Svtag = 167, /* Start of L2 svtag. */
    bcmUdfAbstractPktFormatRecircleHdr = 168, /* Start of EP NIH header. */
    bcmUdfAbstractPktFormatHiGig3 = 169, /* Start of HiGig3 header. */
    bcmUdfAbstractPktFormatIfaHeader = 170, /* Start of IFA header */
    bcmUdfAbstractPktFormatIfaMetadata = 171, /* Start of IFA Metadata */
    bcmUdfAbstractPktFormatL2Rspan = 172, /* Start of L2 RSPAN */
    bcmUdfAbstractPktFormatInnerL2Rspan = 173, /* Start of Inner L2 RSPAN */
    bcmUdfAbstractPktFormatGtp8Byte = 174, /* Start of 8-Byte GPRS Tunnel Protocol
                                           (GTP) */
    bcmUdfAbstractPktFormatGtp12Byte = 175, /* Start of 12-Byte GPRS Tunnel Protocol
                                           (GTP) */
    bcmUdfAbstractPktFormatIpv6WithSRv6 = 176, /* Extract from the start of L3 for IPv6
                                           traffic if SRv6 is enabled */
    bcmUdfAbstractPktFormatKnownL3Ipv6SRH = 177, /* Extract from start of SRH header for
                                           Known L3 SRv6 packet */
    bcmUdfAbstractPktFormatL2InIpv6 = 178, /* Extract from start of L2 for packets
                                           with L2 in IPv6 if SRV6 is enabled. */
    bcmUdfAbstractPktFormatLastCount = 179 /* Unused. Always last in the list */
} bcm_udf_abstract_pkt_format_t;

#define BCM_UDF_ABSTRACT_PKT_FORMAT \
{ \
    "Llc", \
    "InnerLlc", \
    "UnknownL3", \
    "InnerUnknownL3", \
    "KnownNonIp", \
    "InnerKnownNonIp", \
    "KnownL3Mim", \
    "KnownL3FcoeStdEncap", \
    "KnownL3FcoeVftIfr", \
    "KnownL3MplsOneLabel", \
    "KnownL3MplsTwoLabel", \
    "KnownL3MplsThreeLabel", \
    "KnownL3MplsFourLabel", \
    "KnownL3MplsMoreThanFourLabel", \
    "UnknownL4", \
    "InnerUnknownL4", \
    "UdpUnknownL5", \
    "InnerUdpUnknownL5", \
    "UdpGpeGeneve", \
    "UdpBfd", \
    "InnerUdpBfd", \
    "UdpVxlan", \
    "Udp1588", \
    "TcpUnknownL5", \
    "InnerTcpUnknownL5", \
    "SctpUnknownL5", \
    "InnerSctpUnknownL5", \
    "GreWithoutKey", \
    "GreWithKey", \
    "GreWithoutChecksumRouting", \
    "L2GreWithoutChecksumRouting", \
    "L2GreWithoutRouting", \
    "AchNonIp", \
    "UdpINT", \
    "TcpUnknownL5WithIpExtnHdr", \
    "L3GreUnknownPayload", \
    "GreWithKeyRouting", \
    "L2GreWithKeyRouting", \
    "InnerUdp1588", \
    "TcpINT", \
    "KnownL3FcoeUnknownRctl", \
    "HiGigPpd0", \
    "HiGigPpd0EHType0", \
    "HiGigPpd0EHType1", \
    "HiGigPpd0EHType2", \
    "HiGigPpd2", \
    "HiGigPpd2EHType0", \
    "HiGigPpd2EHType1", \
    "HiGigPpd2EHType2", \
    "GpeIOAM", \
    "KnownMplsMcast", \
    "LoopbackHdrType0", \
    "LoopbackHdrType1", \
    "L3Ipv4Fragmented", \
    "L3Ipv4FragmentedWithOptions", \
    "L3Ipv4WithoutOptions", \
    "L3Ipv4WithOptions", \
    "L3Ipv6", \
    "L2", \
    "L2Untagged", \
    "L2OuterVlanTag", \
    "L2InnerVlanTag", \
    "L2DoubleVlanTag", \
    "L2GbpTag", \
    "L2OuterVlanWithGbpTag", \
    "L2InnerVlanWithGbpTag", \
    "L2DoubleVlanWithGbpTag", \
    "L2Vntag", \
    "L2OuterVlanWithVntag", \
    "L2InnerVlanWithVntag", \
    "L2DoubleVlanWithVntag", \
    "L2Etag", \
    "L2OuterVlanEtag", \
    "L2InnerVlanEtag", \
    "L2DoubleVlanEtag", \
    "InnerL3Ipv4", \
    "InnerL3Ipv4Fragmented", \
    "InnerL3Ipv6", \
    "InnerL2Untagged", \
    "InnerL2OuterVlanTag", \
    "InnerL2InnerVlanTag", \
    "InnerL2DoubleVlanTag", \
    "InnerL2GbpTag", \
    "InnerL2OuterVlanWithGbpTag", \
    "InnerL2InnerVlanWithGbpTag", \
    "InnerL2DoubleVlanWithGbpTag", \
    "UnknownL3CustomEtherType1", \
    "UnknownL3CustomEtherType2", \
    "UnknownL3CustomIpProtocol1", \
    "UnknownL3CustomIpProtocol2", \
    "UnknownL3CustomUdpDstPort1", \
    "UnknownL3CustomUdpDstPort2", \
    "InnerUnknownL3CustomEtherType1", \
    "InnerUnknownL3CustomEtherType2", \
    "InnerUnknownL3CustomIpProtocol1", \
    "InnerUnknownL3CustomIpProtocol2", \
    "InnerUnknownL3CustomUdpDstPort1", \
    "InnerUnknownL3CustomUdpDstPort2", \
    "UdpProbeBasedINT", \
    "MacsecDecrypt", \
    "GpeIOAMEdgeToEdge", \
    "UdpVxlanWithoutExtnHdr", \
    "Udp1588WithoutExtnHdr", \
    "UdpBfdWithoutExtnHdr", \
    "UdpProbeBasedINTWithoutExtnHdr", \
    "UdpINTWithoutExtnHdr", \
    "InnerTcpUnknownL5WithoutExtnHdr", \
    "UdpUnknownL5WithoutExtnHdr", \
    "InnerUdpBfdWithoutExtnHdr", \
    "L2Cntag", \
    "Arp", \
    "Ipv6HdrAuthExt1", \
    "Ipv6HdrAuthExt2", \
    "L2EtherType", \
    "L3Ipv6HdrFragExt1", \
    "L3Ipv6HdrFragExt2", \
    "Gpe", \
    "Gre", \
    "GreWithChecksum", \
    "GreWithSequence", \
    "Icmp", \
    "Igmp", \
    "L3Ipv4", \
    "MplsAch", \
    "MplsCw", \
    "KnownL3MplsFiveLabel", \
    "KnownL3MplsSixLabel", \
    "KnownL3MplsSevenLabel", \
    "Rarp", \
    "L3RoutExt1", \
    "L3RoutExt2", \
    "L4Tcp", \
    "L4Udp", \
    "UnknownL5", \
    "InnerL2Cntag", \
    "InnerL2Etag", \
    "InnerL2", \
    "InnerL2Vntag", \
    "InnerArp", \
    "InnerIpv6HdrAuthExt1", \
    "InnerIpv6HdrAuthExt2", \
    "InnerL2EtherType", \
    "InnerL3Ipv6HdrFragExt1", \
    "InnerL3Ipv6HdrFragExt2", \
    "InnerIcmp", \
    "InnerIgmp", \
    "InnerRarp", \
    "InnerL4Tcp", \
    "InnerL4Udp", \
    "InnerUnknownL5", \
    "IfaUdp", \
    "IfaTcp", \
    "NshOverL2", \
    "CesBackplane", \
    "LoopbackType1WithDropIndication", \
    "GreHdrOfFourBytes", \
    "GreHdrOfEightBytes", \
    "GreHdrOfTwelveBytes", \
    "GreHdrOfSixteenBytes", \
    "GreHdrOfTwentyBytes", \
    "L2GreHdrOfFourBytes", \
    "L2GreHdrOfEightBytes", \
    "L2GreHdrOfTwelveBytes", \
    "L2GreHdrOfSixteenBytes", \
    "L2GreHdrOfTwentyBytes", \
    "InnerUdpUnknownL5WithoutExtnHdr", \
    "InnerUdp1588WithoutExtnHdr", \
    "L2Svtag", \
    "RecircleHdr", \
    "HiGig3", \
    "IfaHeader", \
    "IfaMetadata", \
    "L2Rspan", \
    "InnerL2Rspan", \
    "Gtp8Byte", \
    "Gtp12Byte", \
    "Ipv6WithSRv6", \
    "KnownL3Ipv6SRH", \
    "L2InIpv6"  \
}

/* Base header the switch can parse. */
typedef enum bcm_udf_tunnel_type_e {
    bcmUdfTunnelTypeGeneveOuterIpv4 = 0, /* Tunnel Type GENEVE Outer IPv4 */
    bcmUdfTunnelTypeGeneveOuterIpv6 = 1, /* Tunnel Type GENEVE Outer IPv6 */
    bcmUdfTunnelTypeGpeOuterIpv4 = 2,   /* Tunnel Type GPE Outer IPv4 */
    bcmUdfTunnelTypeGpeOuterIpv6 = 3,   /* Tunnel Type GPE Outer IPv6 */
    bcmUdfTunnelTypeIpInIpGreWithOuterIPv4 = 4, /* Tunnel Type IP-IN-IP GRE with Outer
                                           IPv4 */
    bcmUdfTunnelTypeIpInIpGreWithOuterIPv6 = 5, /* Tunnel Type IP-IN-IP GRE with Outer
                                           IPv6 */
    bcmUdfTunnelTypeIpInIpWithOuterIpv4 = 6, /* Tunnel Type GRE with Outer IPv4 */
    bcmUdfTunnelTypeIpInIpWithOuterIpv6 = 7, /* Tunnel Type GRE with Outer IPv6 */
    bcmUdfTunnelTypeL2Gre = 8,          /* Tunnel Type L2 GRE */
    bcmUdfTunnelTypeMim = 9,            /* Tunnel Type MiM */
    bcmUdfTunnelTypeMpls = 10,          /* Tunnel Type MPLS */
    bcmUdfTunnelTypeMplsOverGre = 11,   /* Tunnel Type MPLS Over GRE */
    bcmUdfTunnelTypeVxlanOuterIpv4 = 13, /* Tunnel Type Vxlan Outer IPv4 */
    bcmUdfTunnelTypeVxlanOuterIpv6 = 14, /* Tunnel Type Vxlan Outer IPv6 */
    bcmUdfTunnelTypeLastCount = 15      /* Always last. Not to be used */
} bcm_udf_tunnel_type_t;

#define BCM_UDF_TUNNEL_TYPE \
{ \
    "GeneveOuterIpv4", \
    "GeneveOuterIpv6", \
    "GpeOuterIpv4", \
    "GpeOuterIpv6", \
    "IpInIpGreWithOuterIPv4", \
    "IpInIpGreWithOuterIPv6", \
    "IpInIpWithOuterIpv4", \
    "IpInIpWithOuterIpv6", \
    "L2Gre", \
    "Mim", \
    "Mpls", \
    "MplsOverGre", \
    "", \
    "VxlanOuterIpv4", \
    "VxlanOuterIpv6", \
    "LastCount"  \
}

/* UDF tunnel term flow types. */
typedef enum bcm_udf_tunnel_term_flow_type_e {
    bcmUdfTunnelTermFlowTypeMimWithIpPayload = 0, /* MiM with IP Payload. */
    bcmUdfTunnelTermFlowTypeMimWithoutIpPayload = 1, /* MiM without IP Payload. */
    bcmUdfTunnelTermFlowTypeL2MplsWithIpPayload = 2, /* L2 MPLS with IP Payload. */
    bcmUdfTunnelTermFlowTypeL2MplsWithoutIpPayload = 3, /* L2 MPLS without IP Payload. */
    bcmUdfTunnelTermFlowTypeL2GreWithIpPayload = 4, /* L2 GRE with IP Payload. */
    bcmUdfTunnelTermFlowTypeL2GreWithoutIpPayload = 5, /* L2 GRE without IP Payload. */
    bcmUdfTunnelTermFlowTypeVxlanWithIpPayload = 6, /* VxLAN with IP Payload. */
    bcmUdfTunnelTermFlowTypeVxlanWithoutIpPayload = 7, /* VxLAN without IP Payload. */
    bcmUdfTunnelTermFlowTypeL3Mpls = 8, /* L3 MPLS. */
    bcmUdfTunnelTermFlowTypeL3Tunnel = 9, /* L3 Tunnel. */
    bcmUdfTunnelTermFlowTypeL3GpeGeneve = 10, /* L3 Gpe Geneve. */
    bcmUdfTunnelTermFlowTypeL2WithIpPayload = 11, /* L2 with IP Payload. */
    bcmUdfTunnelTermFlowTypeL2WithoutIpPayload = 12, /* L2 without IP Payload. */
    bcmUdfTunnelTermFlowTypeUnterminated = 13, /* Unterminated flows like Transit and
                                           Nontunnel. */
    bcmUdfTunnelTermFlowTypeLastCount = 14 /* Unused. Always last in the list */
} bcm_udf_tunnel_term_flow_type_t;

#define BCM_UDF_TUNNEL_TERM_FLOW_TYPE \
{ \
    "MimWithIpPayload", \
    "MimWithoutIpPayload", \
    "L2MplsWithIpPayload", \
    "L2MplsWithoutIpPayload", \
    "L2GreWithIpPayload", \
    "L2GreWithoutIpPayload", \
    "VxlanWithIpPayload", \
    "VxlanWithoutIpPayload", \
    "L3Mpls", \
    "L3Tunnel", \
    "L3GpeGeneve", \
    "L2WithIpPayload", \
    "L2WithoutIpPayload", \
    "Unterminated"  \
}

/* Tunnel termination of UDF tunnel flow types. */
typedef enum bcm_udf_tunnel_flow_type_e {
    bcmUdfTunnelFlowTypeTermMimWithIpPayload = 0, /* Tunnel termination of MiM with IP
                                           Payload. */
    bcmUdfTunnelFlowTypeTermMimWithoutIpPayload = 1, /* Tunnel termination of MiM without IP
                                           Payload. */
    bcmUdfTunnelFlowTypeTermL2MplsWithIpPayload = 2, /* Tunnel termination of L2 MPLS with IP
                                           Payload. */
    bcmUdfTunnelFlowTypeTermL2MplsWithoutIpPayload = 3, /* Tunnel termination of L2 MPLS without
                                           IP Payload. */
    bcmUdfTunnelFlowTypeTermL2GreWithIpPayload = 4, /* Tunnel termination of L2 GRE with IP
                                           Payload. */
    bcmUdfTunnelFlowTypeTermL2GreWithoutIpPayload = 5, /* Tunnel termination of L2 GRE without
                                           IP Payload. */
    bcmUdfTunnelFlowTypeTermVxlanWithIpPayload = 6, /* Tunnel termination of VxLAN with IP
                                           Payload. */
    bcmUdfTunnelFlowTypeTermVxlanWithoutIpPayload = 7, /* Tunnel termination of VxLAN without
                                           IP Payload. */
    bcmUdfTunnelFlowTypeTermL3Mpls = 8, /* Tunnel termination of L3 MPLS. */
    bcmUdfTunnelFlowTypeTermL3Tunnel = 9, /* Tunnel termination of L3 Tunnel. */
    bcmUdfTunnelFlowTypeTermL3GpeGeneve = 10, /* Tunnel termination of L3 Gpe Geneve. */
    bcmUdfTunnelFlowTypeTermL2WithIpPayload = 11, /* Tunnel termination of L2 with IP
                                           Payload. */
    bcmUdfTunnelFlowTypeTermL2WithoutIpPayload = 12, /* Tunnel termination of L2 without IP
                                           Payload. */
    bcmUdfTunnelFlowTypeIpInIpAndNonTunnel = 13, /* IP IN IP tunnel transit flow and Non
                                           Tunnel flows. */
    bcmUdfTunnelFlowTypeTransitMim = 14, /* MiM tunnel transit flow. */
    bcmUdfTunnelFlowTypeTransitMpls = 15, /* MPLS tunnel transit flow. */
    bcmUdfTunnelFlowTypeTransitVxlan = 16, /* VxLAN tunnel transit flow. */
    bcmUdfTunnelFlowTypeTransitL2Gre = 17, /* L2 GRE tunnel transit flow. */
    bcmUdfTunnelFlowTypeTermL2SRv6WithIpPayload = 18, /* Tunnel termination of L2 SRv6 with IP
                                           Payload. */
    bcmUdfTunnelFlowTypeTermL2SRv6WithoutIpPayload = 19, /* Tunnel termination of L2 SRv6 without
                                           IP Payload. */
    bcmUdfTunnelFlowTypeTermL3SRv6 = 20, /* Tunnel termination of L3 SRv6. */
    bcmUdfTunnelFlowTypeTransitSRv6 = 21, /* Transit flow of tunnel SRv6 . */
    bcmUdfTunnelFlowTypeTransitL2InIpv6 = 22, /* Transit flow of IPv6 with L2 header
                                           in payload. */
    bcmUdfTunnelFlowTypeTunnelTermL2InIpv6WithoutIpPayload = 23, /* Tunnel termination flow of IPv6 with
                                           L2 header in payload without IP
                                           payload. */
    bcmUdfTunnelFlowTypeTunnelTermL2InIpv6WithIpPayload = 24, /* Tunnel termination flow of IPv6 with
                                           L2 header in payload with IP payload. */
    bcmUdfTunnelFlowTypeLastCount = 25  /* Unused. Always last in the list */
} bcm_udf_tunnel_flow_type_t;

#define BCM_UDF_TUNNEL_FLOW_TYPE \
{ \
    "TermMimWithIpPayload", \
    "TermMimWithoutIpPayload", \
    "TermL2MplsWithIpPayload", \
    "TermL2MplsWithoutIpPayload", \
    "TermL2GreWithIpPayload", \
    "TermL2GreWithoutIpPayload", \
    "TermVxlanWithIpPayload", \
    "TermVxlanWithoutIpPayload", \
    "TermL3Mpls", \
    "TermL3Tunnel", \
    "TermL3GpeGeneve", \
    "TermL2WithIpPayload", \
    "TermL2WithoutIpPayload", \
    "IpInIpAndNonTunnel", \
    "TransitMim", \
    "TransitMpls", \
    "TransitVxlan", \
    "TransitL2Gre", \
    "TermL2SRv6WithIpPayload", \
    "TermL2SRv6WithoutIpPayload", \
    "TermL3SRv6", \
    "TransitSRv6", \
    "TransitL2InIpv6", \
    "TunnelTermL2InIpv6WithoutIpPayload", \
    "TunnelTermL2InIpv6WithIpPayload"  \
}

/* UDF Chunk Information Structure. */
typedef struct bcm_udf_chunk_info_s {
    int offset;                         /* Relative offset in bits (Starts from
                                           base offset of given abstract packet
                                           format) in the packet */
    uint32 width;                       /* width of data in bits to extract */
    uint32 chunk_bmap;                  /* Chunk bitmap (Each bit in the bitmap
                                           represents 1 chunk (2 bytes) */
    bcm_udf_abstract_pkt_format_t abstract_pkt_format; /* Abstract Packet Format (one of the
                                           format from
                                           'bcm_udf_abstract_pkt_format_t') */
} bcm_udf_chunk_info_t;

/* Initializes the UDF Chunk Info structure */
extern void bcm_udf_chunk_info_t_init(
    bcm_udf_chunk_info_t *udf_chunk_info);

/* Pkt Base offset. */
typedef enum bcm_udf_pkt_base_offset_e {
    bcmUdfPktBaseOffsetStartOfOuterL2 = 0, /* Base offset from the start of Outer
                                           L2 Header. */
    bcmUdfPktBaseOffsetStartOfOuterLlc = 1, /* Base offset from the start of Outer
                                           LLC Header. */
    bcmUdfPktBaseOffsetStartOfTunnel = 2, /* Base offset from the start of Tunnel
                                           Header. */
    bcmUdfPktBaseOffsetStartOfOuterL3 = 3, /* Base offset from the start of Outer
                                           L3 Header. */
    bcmUdfPktBaseOffsetStartOfOuterL4 = 4, /* Base offset from the start of Outer
                                           L4 Header. */
    bcmUdfPktBaseOffsetStartOfOuterL5 = 5, /* Base offset from the start of Outer
                                           L5 Header. */
    bcmUdfPktBaseOffsetStartOfInnerL2 = 6, /* Base offset from the start of Inner
                                           L2 Header. */
    bcmUdfPktBaseOffsetStartOfInnerLlc = 7, /* Base offset from the start of Inner
                                           LLC Header. */
    bcmUdfPktBaseOffsetStartOfInnerL3 = 8, /* Base offset from the start of Inner
                                           L3 Header. */
    bcmUdfPktBaseOffsetStartOfInnerL4 = 9, /* Base offset from the start of Inner
                                           L4 Header. */
    bcmUdfPktBaseOffsetStartOfInnerL5 = 10, /* Base offset from the start of Inner
                                           L5 Header. */
    bcmUdfPktBaseOffsetStartOfSystemHeader = 11, /* Base offset from the start of system
                                           header (HiGig or Loopback). */
    bcmUdfPktBaseOffsetStartOf14bytesAfterOuterL2 = 12, /* Base offset from the start of 14
                                           bytes after Outer L2 Header. (For
                                           example: In-case of L2 Single tagged
                                           packet, it is start of 802.1p
                                           priority field after TPID.) */
    bcmUdfPktBaseOffsetStartOf12bytesAfterInnerL2 = 13, /* Base offset from the start of 12
                                           bytes after Outer L2 Header. */
    bcmUdfPktBaseOffsetStartOfGpe = 14, /* Base offset from the start of GPE
                                           Header. */
    bcmUdfPktBaseOffsetStartOfIfa = 15, /* Base offset from the start of IFA
                                           Header. */
    bcmUdfPktBaseOffsetStartOfNsh = 16, /* Base offset from the start of NSH
                                           Header. */
    bcmUdfPktBaseOffsetStartOf12bytesAfterOuterL2 = 17, /* Base offset from the start of 12
                                           bytes after Outer L2 Header. (For
                                           example: In-case of L2 Single tagged
                                           packet, it is start of 802.1p
                                           priority field after TPID.) */
    bcmUdfPktBaseOffsetStartOfSrh = 18, /* Base offset from the start of SRH
                                           Header. */
    bcmUdfPktBaseOffsetStartOfPayloadL2 = 19, /* Base offset from the start of L2
                                           header in the payload. */
    bcmUdfPktBaseOffsetLastCount = 20   /* Unused. Always last in the list */
} bcm_udf_pkt_base_offset_t;

#define BCM_UDF_PKT_BASE_OFFSET \
{ \
    "StartOfOuterL2", \
    "StartOfOuterLlc", \
    "StartOfTunnel", \
    "StartOfOuterL3", \
    "StartOfOuterL4", \
    "StartOfOuterL5", \
    "StartOfInnerL2", \
    "StartOfInnerLlc", \
    "StartOfInnerL3", \
    "StartOfInnerL4", \
    "StartOfInnerL5", \
    "StartOfSystemHeader", \
    "StartOf14bytesAfterOuterL2", \
    "StartOf12bytesAfterInnerL2", \
    "StartOfGpe", \
    "StartOfIfa", \
    "StartOfNsh", \
    "StartOf12bytesAfterOuterL2", \
    "StartOfSrh", \
    "StartOfPayloadL2"  \
}

/* UDF Abstract Packet Format Information Structure. */
typedef struct bcm_udf_abstract_pkt_format_info_s {
    bcm_udf_pkt_base_offset_t base_offset; /* Relative offset of
                                           'bcmUdfPktBaseOffsetXX' type (from
                                           'bcm_udf_pkt_base_offset_t') */
    uint32 num_chunks_max;              /* Maximum number of chunks supported by
                                           the abstract packet format */
    uint32 chunk_bmap_used;             /* Bitmap of Chunks already used by the
                                           abstract packet format */
    uint32 unavail_chunk_bmap;          /* Bitmap of Chunks unavailable/reserved */
    uint32 offset_max;                  /* Maximum offset */
} bcm_udf_abstract_pkt_format_info_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* API to retrieve Abstract packet format information. */
extern int bcm_udf_abstract_pkt_format_info_get(
    int unit, 
    bcm_udf_abstract_pkt_format_t abstract_pkt_format, 
    bcm_udf_abstract_pkt_format_info_t *pkt_format_info);

/* Create UDF object */
extern int bcm_udf_chunk_create(
    int unit, 
    bcm_udf_alloc_hints_t *hints, 
    bcm_udf_chunk_info_t *udf_chunk_info, 
    bcm_udf_id_t *udf_id);

/* Get a UDF object information. */
extern int bcm_udf_chunk_info_get(
    int unit, 
    bcm_udf_id_t udf_id, 
    bcm_udf_chunk_info_t *udf_chunk_info);

/* 
 * API to retrieve the list of UDF Objects associated with a given
 * abstract
 * packet format
 */
extern int bcm_udf_abstract_pkt_format_object_list_get(
    int unit, 
    bcm_udf_abstract_pkt_format_t abstract_pkt_format, 
    int max, 
    bcm_udf_id_t *udf_id_list, 
    int *actual);

/* API to retrieve the chunk information supported for Range Checker. */
extern int bcm_udf_range_checker_chunk_info_get(
    int unit, 
    uint8 *num_chunks, 
    uint32 *chunk_bmap);

/* 
 * API to assign the chunk bitmaps to the tunnel termination flows.
 * The non-zero bits assigned to the chunk bitmap are applicable to
 * extract the information from the tunnel header and zero bits are
 * applicable to tunnel payload for a given termination flow.
 */
extern int bcm_udf_flow_based_chunk_arrange_set(
    int unit, 
    bcm_udf_tunnel_term_flow_type_t flow_type, 
    uint32 chunk_bmap);

/* 
 * API to retrieve the chunk bitmaps information for a given tunnel
 * termination flow.
 */
extern int bcm_udf_flow_based_chunk_arrange_get(
    int unit, 
    bcm_udf_tunnel_term_flow_type_t flow_type, 
    uint32 *chunk_bmap);

/* 
 * API to assign the chunk bitmaps to the tunnel flows.
 * The non-zero bits assigned to the chunk bitmap are applicable to
 * extract the information from the tunnel header and zero bits are
 * applicable to tunnel payload for a given tunnel flow.
 */
extern int bcm_udf_tunnel_flow_based_chunk_arrange_set(
    int unit, 
    bcm_udf_tunnel_flow_type_t flow_type, 
    uint32 chunk_bmap);

/* API to retrieve the chunk bitmaps information for a given tunnel flow. */
extern int bcm_udf_tunnel_flow_based_chunk_arrange_get(
    int unit, 
    bcm_udf_tunnel_flow_type_t flow_type, 
    uint32 *chunk_bmap);

#endif /* BCM_HIDE_DISPATCHABLE */

#define BCM_UDF_CHUNKS_MAX      32         

/* Array of bits to define the UDF chunk bitmap. */
typedef struct bcm_udf_cbmp_s {
    SHR_BITDCL w[_SHR_BITDCLSIZE(BCM_UDF_CHUNKS_MAX)]; 
} bcm_udf_cbmp_t;

/* UDF Chunk bitmap INIT operation */
#define BCM_UDF_CBMP_CHUNK_INIT(cbmp)  \
    sal_memset(&(cbmp), 0x0, sizeof(bcm_udf_cbmp_t)) 

/* UDF Chunk Add operation */
#define BCM_UDF_CBMP_CHUNK_ADD(cbmp, chunk)  SHR_BITSET(((cbmp).w), (chunk)) 

/* UDF Chunk Remove operation */
#define BCM_UDF_CBMP_CHUNK_REMOVE(cbmp, chunk)  SHR_BITCLR(((cbmp).w), (chunk)) 

/* UDF Chunk Test operation */
#define BCM_UDF_CBMP_CHUNK_TEST(cbmp, chunk)  SHR_BITGET(((cbmp).w), (chunk)) 

/* UDF Multi Chunk Information Structure. */
typedef struct bcm_udf_multi_chunk_info_s {
    int offset;                         /* Relative offset in bits (Starts from
                                           base offset of given abstract packet
                                           format) in the packet */
    uint32 width;                       /* width of data in bits to extract */
    bcm_udf_cbmp_t one_byte_chunk_bmap; /* Chunk bitmap (Each bit in the bitmap
                                           represents 1 chunk of 1 byte each */
    bcm_udf_cbmp_t two_byte_chunk_bmap; /* Chunk bitmap (Each bit in the bitmap
                                           represents 1 chunk of 2 bytes each */
    bcm_udf_cbmp_t four_byte_chunk_bmap; /* Chunk bitmap (Each bit in the bitmap
                                           represents 1 chunk of 4 bytes each */
    bcm_udf_abstract_pkt_format_t abstract_pkt_format; /* Abstract Packet Format (one of the
                                           format from
                                           'bcm_udf_abstract_pkt_format_t') */
} bcm_udf_multi_chunk_info_t;

/* Initializes the UDF Chunk Info structure */
extern void bcm_udf_multi_chunk_info_t_init(
    bcm_udf_multi_chunk_info_t *udf_multi_chunk_info);

#ifndef BCM_HIDE_DISPATCHABLE

/* Creates a UDF object */
extern int bcm_udf_multi_chunk_create(
    int unit, 
    bcm_udf_alloc_hints_t *hints, 
    bcm_udf_multi_chunk_info_t *info, 
    bcm_udf_id_t *udf_id);

/* Get a UDF object information. */
extern int bcm_udf_multi_chunk_info_get(
    int unit, 
    bcm_udf_id_t udf_id, 
    bcm_udf_multi_chunk_info_t *info);

#endif /* BCM_HIDE_DISPATCHABLE */

/* UDF Multi Abstract Packet Format Information Structure. */
typedef struct bcm_udf_multi_abstract_pkt_format_info_s {
    bcm_udf_pkt_base_offset_t base_offset; /* Not supported. The base offset is
                                           based on the flow applicable to the
                                           abstract packet format (as name
                                           suggested). */
    uint32 num_chunks_max;              /* Maximum number of chunks supported by
                                           the abstract packet format */
    bcm_udf_cbmp_t chunk_4b_bmap_avail; /* Available 4-byte Chunk bitmap. */
    bcm_udf_cbmp_t chunk_2b_bmap_avail; /* Available 2-byte Chunk bitmap. */
    bcm_udf_cbmp_t chunk_1b_bmap_avail; /* Available 1-byte Chunk bitmap. */
    uint32 num_chunks_available;        /* Indicates the dynamic state of the
                                           available free chunks. */
} bcm_udf_multi_abstract_pkt_format_info_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* Retrieve multi packet format info for a given abstract packet format */
extern int bcm_udf_multi_abstract_pkt_format_info_get(
    int unit, 
    bcm_udf_abstract_pkt_format_t abstr_pkt_fmt, 
    bcm_udf_multi_abstract_pkt_format_info_t *pkt_fmt_info);

/* Retrieve UDF supported abstract packet formats */
extern int bcm_udf_abstract_pkt_format_supported_list_get(
    int unit, 
    int max, 
    bcm_udf_abstract_pkt_format_t *abstr_pkt_fmt_list, 
    int *actual);

#endif /* BCM_HIDE_DISPATCHABLE */

/* 
 * Enumerations for tunnel header IEU (Internal entropy Used) policy for
 * Hash computation.
 */
typedef enum bcm_udf_hash_tunnel_hdr_ieu_policy_e {
    bcmUdfHashTunnelHdrIeuPolicyUseNone = 0, /* Do not use for hit in UDF for hash 
                                           computation. */
    bcmUdfHashTunnelHdrIeuPolicyUseOuter = 1, /* Use outer header fields for hash
                                           computation when UDF is hit. */
    bcmUdfHashTunnelHdrIeuPolicyUseInner = 2, /* Use inner header fields for hash
                                           computation when UDF is hit. */
    bcmUdfHashTunnelHdrIeuPolicyCount = 3 /* Unused. Always last in the list */
} bcm_udf_hash_tunnel_hdr_ieu_policy_t;

#define BCM_UDF_HASH_TUNNEL_HDR_IEU_POLICY \
{ \
    "UseNone", \
    "UseOuter", \
    "UseInner"  \
}

/* Enumerations for Packet format actions. */
typedef enum bcm_udf_pkt_format_action_e {
    bcmUdfPktFormatActionClassId = 0,   /* Apply Class Id. */
    bcmUdfPktFormatActionSkipOuterL4IfaMetadata = 1, /* Skip L4 header Outer IFA metadata
                                           header and metadata while calculating
                                           final offset. This action is
                                           applicable when associated UDF has
                                           layer set to L4 or tunnel payload. */
    bcmUdfPktFormatActionHashTunnelHdrIeuPolicy = 2, /* Set hash tunnel header IEU (internal
                                           entropy used) Policy for hash
                                           computation. */
    bcmUdfPktFormatActionCount = 3      /* Unused. Always last in the list */
} bcm_udf_pkt_format_action_t;

#define BCM_UDF_PKT_FORMAT_ACTION \
{ \
    "ClassId", \
    "SkipOuterL4IfaMetadata", \
    "HashTunnelHdrIeuPolicy"  \
}

#ifndef BCM_HIDE_DISPATCHABLE

/* Associated action to the packet format Id */
extern int bcm_udf_pkt_format_action_set(
    int unit, 
    bcm_udf_pkt_format_id_t pkt_format_id, 
    bcm_udf_pkt_format_action_t action, 
    int arg);

/* Get associated action to the packet format Id */
extern int bcm_udf_pkt_format_action_get(
    int unit, 
    bcm_udf_pkt_format_id_t pkt_format_id, 
    bcm_udf_pkt_format_action_t action, 
    int *arg);

/* Get UDF maximum offset for given tunnel type */
extern int bcm_udf_tunnel_type_offset_max_get(
    int unit, 
    bcm_udf_tunnel_type_t tunnel_type, 
    uint32 *offset_max);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Multi UDF flow types. */
typedef enum bcm_udf_multi_flow_type_e {
    bcmUdfMultiFlowTypeL2TunnelTerm = 0, /* L2 Tunnel termination flow to extract
                                           from tunnel header. */
    bcmUdfMultiFlowTypeL2TunnelTransit = 1, /* L2 Tunnel transit flow to extract
                                           from tunnel payload. */
    bcmUdfMultiFlowTypeL3TunnelTerm = 2, /* L3 Tunnel termination flow to extract
                                           from tunnel header. */
    bcmUdfMultiFlowTypeL3TunnelTransit = 3, /* L3 Tunnel transit flow to extract
                                           from tunnel payload. */
    bcmUdfMultiFlowTypeNonTunnel = 4,   /* Non Tunnel flow. */
    bcmUdfMultiFlowTypeLastCount = 5    /* Unused. Always last in the list */
} bcm_udf_multi_flow_type_t;

#define BCM_UDF_MULTI_FLOW_TYPE \
{ \
    "L2TunnelTerm", \
    "L2TunnelTransit", \
    "L3TunnelTerm", \
    "L3TunnelTransit", \
    "NonTunnel"  \
}

/* UDF Multi Flow based extraction info structure. */
typedef struct bcm_udf_multi_flow_based_extraction_info_s {
    bcm_udf_multi_flow_type_t flow_type; /* Flow type */
    bcm_udf_cbmp_t one_byte_chunk_bmap; /* Chunk bitmap (Each bit in the bitmap
                                           represents 1 chunk of 1 byte each */
    bcm_udf_cbmp_t two_byte_chunk_bmap; /* Chunk bitmap (Each bit in the bitmap
                                           represents 1 chunk of 2 bytes each */
    bcm_udf_cbmp_t four_byte_chunk_bmap; /* Chunk bitmap (Each bit in the bitmap
                                           represents 1 chunk of 4 bytes each */
} bcm_udf_multi_flow_based_extraction_info_t;

/* Initializes the UDF Multi Flow based extraction info structure. */
extern void bcm_udf_multi_flow_based_extraction_info_t_init(
    bcm_udf_multi_flow_based_extraction_info_t *udf_multi_flow_based_extraction_info);

#ifndef BCM_HIDE_DISPATCHABLE

/* 
 * API to program the extraction info to the tunnel flows.
 * The non-zero bits assigned to the chunk bitmap are applicable to
 * extract the information from the tunnel header or from the tunnel
 * payload
 * based on the given flow type.
 */
extern int bcm_udf_multi_flow_based_extraction_set(
    int unit, 
    bcm_udf_multi_flow_based_extraction_info_t *extrn_info);

/* API to retrieve the chunk info for a given flow. */
extern int bcm_udf_multi_flow_based_extraction_get(
    int unit, 
    bcm_udf_multi_flow_based_extraction_info_t *extrn_info);

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_UDF_H__ */

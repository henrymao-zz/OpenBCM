/*
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

#ifndef __BCM_BFD_H__
#define __BCM_BFD_H__

#if defined(INCLUDE_BFD)

#include <shared/bfd.h>
#include <bcm/mpls.h>
#include <bcm/oam.h>

/* Miscellaneous BFD defines. */
#define BCM_BFD_ENDPOINT_INVALID            -1         /* Invalid BFD endpoint
                                                          ID. */
#define BCM_BFD_ENDPOINT_DEFAULT0           -3         /* BFD default endpoint. */
#define BCM_BFD_ENDPOINT_DEFAULT1           -4         /* BFD default endpoint. */
#define BCM_BFD_ENDPOINT_DEFAULT2           -5         /* BFD default endpoint. */
#define BCM_BFD_ENDPOINT_DEFAULT3           -6         /* BFD default endpoint. */
#define BCM_BFD_INTPRI_MAX                  16         /* Internal priority max
                                                          value. */
#define BCM_BFD_ENDPOINT_MAX_MEP_ID_LENGTH  _SHR_BFD_ENDPOINT_MAX_MEP_ID_LENGTH /* MPLS-TP MEP_ID maximum
                                                          length. */

/* BFD endpoint flags. */
#define BCM_BFD_ENDPOINT_UPDATE             0x0001     /* Update an existing BFD
                                                          endpoint. */
#define BCM_BFD_ENDPOINT_WITH_ID            0x0002     /* Use the specified
                                                          endpoint ID. */
#define BCM_BFD_ENDPOINT_PASSIVE            0x0004     /* Specifies endpoint
                                                          takes passive role. */
#define BCM_BFD_ENDPOINT_DEMAND             0x0008     /* Specifies local
                                                          endpoint is in demand
                                                          mode. */
#define BCM_BFD_ENDPOINT_ENCAP_SET          0x0010     /* Update encapsulation
                                                          on existing BFD
                                                          endpoint. */
#define BCM_BFD_ENDPOINT_PWE_RAW            0x0020     /* Use MPLS PWE RAW mode.
                                                          Valid only for PWE
                                                          Tunnel types. */
#define BCM_BFD_ENDPOINT_PWE_ACH            0x0040     /* Use MPLS Associated
                                                          Channel Header.  Valid
                                                          only for PWE Tunnel
                                                          types. */
#define BCM_BFD_ENDPOINT_IPV6               0x0080     /* Use IPv6
                                                          encapsulation. */
#define BCM_BFD_ENDPOINT_MULTIHOP           0x0100     /* BFD IP/UDP multihop
                                                          endpoint. */
#define BCM_BFD_ENDPOINT_MPLS_TP_AIS_LDI    0x0200     /* Set MPLS-TP AIS LDI. 
                                                          Valid only for MPLS-TP
                                                          Tunnel types. */
#define BCM_BFD_ENDPOINT_MPLS_TP_LKR        0x0400     /* MPLS-TP Locked Report
                                                          (LKR). Valid only for
                                                          MPLS-TP Tunnel types. */
#define BCM_BFD_ENDPOINT_KEY_TYPE_USE_YOUR_DISC 0x0800     /* Resolve BFD session ID
                                                          from your
                                                          discriminator.(Instead
                                                          of MPLS label) */
#define BCM_BFD_ENDPOINT_MPLS_IP_DEST_RANDOM 0x1000     /* Randomize outgoing IP
                                                          dest addr. Valid only
                                                          for MPLS/PWE Tunnel
                                                          types. */
#define BCM_BFD_ENDPOINT_MPLS_TP_POLL_SEQUENCE_ENABLE 0x2000     /* Enable poll sequence
                                                          for MPLS-TP
                                                          encapsulations.  Valid
                                                          only for MPLS-TP
                                                          Tunnel types. */
#define BCM_BFD_ENDPOINT_SHA1_SEQUENCE_INCR 0x4000     /* Increment sequence
                                                          number.  Valid for
                                                          SHA1 authentication
                                                          only. */
#define BCM_BFD_ENDPOINT_IN_HW              0x8000     /* Process the endpint in
                                                          HW. */
#define BCM_BFD_ENDPOINT_STACK              0x10000    /* Endpoint is managed by
                                                          other unit in the
                                                          stack. */
#define BCM_BFD_ENDPOINT_REMOTE_EVENT_DISABLE 0x20000    /* Do not generate
                                                          events. */
#define BCM_BFD_ENDPOINT_RDI_AUTO_UPDATE    0x40000    /* Auto update defect
                                                          state on timeout event */
#define BCM_BFD_ENDPOINT_RX_REMOTE_EVENT_DISABLE 0x80000    /* Do not generate events
                                                          for RX packets. */
#define BCM_BFD_ENDPOINT_RX_RDI_AUTO_UPDATE 0x100000   /* Auto update defect
                                                          state on timeout event
                                                          for RX packets */
#define BCM_BFD_ENDPOINT_RDI_ON_LOC         0x200000   /* MEP RDI update LOC
                                                          enable - update local
                                                          MEP RDI in case of
                                                          LOC. */
#define BCM_BFD_ENDPOINT_RDI_CLEAR_ON_LOC_CLEAR 0x400000   /* MEP RDI update LOC
                                                          clean enable - update
                                                          local MEP RDI in case
                                                          of LOC clear (time-in)
                                                          event detected. */
#define BCM_BFD_ENDPOINT_REMOTE_WITH_ID     0x800000   /* Use the specified
                                                          remote endpoint ID. */
#define BCM_BFD_ENDPOINT_REMOTE_UPDATE_STATE_DISABLE 0x1000000  /* Disable updating RMEP
                                                          DB. */
#define BCM_BFD_ENDPOINT_HW_ACCELERATION_SET 0x2000000  /* Configure only HW
                                                          accelerator
                                                          properties. */
#define BCM_BFD_ECHO                        0x4000000  /* Create BFD echo
                                                          session. */
#define BCM_BFD_ENDPOINT_EXPLICIT_DETECTION_TIME 0x8000000  /* BFD Detection Time is
                                                          set explicitly. */
#define BCM_BFD_ENDPOINT_USE_PKT_VLAN_ID    0x10000000 /* Use to configure the
                                                          User provided Vlan ID. */
#define BCM_BFD_ENDPOINT_MICRO_BFD          0x20000000 /* Use to configure micro
                                                          BFD session. */
#define BCM_BFD_ENDPOINT_ADMIN_DOWN_PKT_ON_ENDPOINT_DEL 0x40000000 /* Trasmit ADMIN_DOWN
                                                          packet on session
                                                          deletion. */
#define BCM_BFD_ENDPOINT_STANDBY_SSO_UPDATE 0x80000000 /* Standby endpoint
                                                          update for Statefull
                                                          Switchover. */

/* Additional BFD endpoint flags. */
#define BCM_BFD_ENDPOINT_FLAGS2_SEAMLESS_BFD_INITIATOR (1<<0)     /* Create/update Seamless
                                                          BFD initiator
                                                          endpoint. */
#define BCM_BFD_ENDPOINT_FLAGS2_SEAMLESS_BFD_REFLECTOR (1<<1)     /* Create/update Seamless
                                                          BFD initiator
                                                          endpoint. */
#define BCM_BFD_ENDPOINT_FLAGS2_USE_MY_DIP_DESTINATION (1<<2)     /* Verify DIP through
                                                          my-DIP-Destination. */
#define BCM_BFD_ENDPOINT_FLAGS2_TX_STATISTICS (1<<3)     /* Enable OAMP Tx
                                                          statistics. */
#define BCM_BFD_ENDPOINT_FLAGS2_RX_STATISTICS (1<<4)     /* Enable OAMP Rx
                                                          statistics. */
#define BCM_BFD_ENDPOINT_FLAGS2_PUNT_NEXT_GOOD_PACKET (1<<5)     /* Write-only flag.
                                                          Specifies if the next
                                                          received good packet
                                                          should be punted to
                                                          the CPU */
#define BCM_BFD_ENDPOINT_FLAGS2_ENTROPY_LABEL (1<<6)     /* Set Entropy Label
                                                          (without EL indicator
                                                          label). Specifies to
                                                          validate and insert
                                                          user-defined
                                                          Entropy(FAT) Label
                                                          (defined in mpls_hdr)
                                                          in VCCV BFD frames */
#define BCM_BFD_ENDPOINT_FLAGS2_SINGLE_HOP_WITH_RANDOM_DIP (1<<7)     /* Use random destination
                                                          IP address in 127/8
                                                          range for Single-Hop
                                                          BFD endpoint. */
#define BCM_BFD_ENDPOINT_FLAGS2_MPLS_TP_RESET_REMOTE_DESCR (1<<8)     /* Reset remote Disc to 0
                                                          upon detection timeout
                                                          for BFD MPLS_TP in
                                                          coordinated mode,
                                                          active device. */
#define BCM_BFD_ENDPOINT_FLAGS2_RX_PKT_COPY2CPU_ON_STATE_CHANGE (1<<9)     /* Enable BFD Rx packet
                                                          copy to cpu during
                                                          state change, if clear
                                                          disable the feature. */
#define BCM_BFD_ENDPOINT_FLAGS2_APPLY_JITTER (1<<10)    /* Set BFD endpoint in
                                                          jitter mode. */

/* Remote status flags. */
#define BCM_BFD_ENDPOINT_REMOTE_DEMAND      0x0001     /* Remote endpoint is in
                                                          demand mode. */
#define BCM_BFD_ENDPOINT_REMOTE_RX_AUTH_SEQ_KNOWN 0x002      /* Rx Authentication
                                                          Sequence ID is known. 
                                                          Valid for SHA1
                                                          authentication only. */

/* BFD packet statistic options. */
#define BCM_BFD_ENDPOINT_STAT_CLEAR 0x0001     /* Clear statistics. */
#define BCM_BFD_ENDPOINT_STAT_64BIT 0x0002     /* Get 64bit statistics. */

/* Simple Password authentication data. */
#define BCM_BFD_SIMPLE_PASSWORD_KEY_LENGTH_MAX _SHR_BFD_AUTH_SIMPLE_PASSWORD_KEY_LENGTH 

/* BFD endpoint local control flags. */
#define BCM_BFD_ENDPOINT_LOCAL_FLAGS_M  0x00000001 /* Multipoint control flag. */
#define BCM_BFD_ENDPOINT_LOCAL_FLAGS_D  0x00000002 /* Demand Control Flag. */
#define BCM_BFD_ENDPOINT_LOCAL_FLAGS_A  0x00000004 /* Authentication Control
                                                      Flag. */
#define BCM_BFD_ENDPOINT_LOCAL_FLAGS_C  0x00000008 /* Control Plane Independent
                                                      Control Flag. */
#define BCM_BFD_ENDPOINT_LOCAL_FLAGS_F  0x00000010 /* Final Bit Control Flag. */
#define BCM_BFD_ENDPOINT_LOCAL_FLAGS_P  0x00000020 /* Poll Bit Control Flag. */

/* BFD Status flags. */
#define BCM_BFD_STATUS_LOCAL_ADMIN_DOWN     0x00000001 /* BFD Local State Admin. */
#define BCM_BFD_STATUS_LOCAL_DOWN           0x00000002 /* BFD Local State Down. */
#define BCM_BFD_STATUS_LOCAL_INIT           0x00000004 /* BFD Local State Init. */
#define BCM_BFD_STATUS_LOCAL_UP             0x00000008 /* BFD Local State Up. */
#define BCM_BFD_STATUS_REMOTE_ADMIN_DOWN    0x00000010 /* BFD Remote State
                                                          Admin. */
#define BCM_BFD_STATUS_REMOTE_DOWN          0x00000020 /* BFD Remote State Down. */
#define BCM_BFD_STATUS_REMOTE_INIT          0x00000040 /* BFD Remote State Init. */
#define BCM_BFD_STATUS_REMOTE_UP            0x00000080 /* BFD Remote State Up. */
#define BCM_BFD_STATUS_LOCAL_DIAG_CODE_NONE 0x00000100 /* BFD Local Diag None. */
#define BCM_BFD_STATUS_LOCAL_DIAG_CODE_CTRL_DETECT_TIME_EXPIRED 0x00000200 /* BFD Local Diag Detect
                                                          Time Expired. */
#define BCM_BFD_STATUS_LOCAL_DIAG_CODE_ECHO_FAILED 0x00000400 /* BFD Local Diag Echo
                                                          Failed. */
#define BCM_BFD_STATUS_LOCAL_DIAG_CODE_NEIGHBOR_SIGNALED_SESSION_DOWN 0x00000800 /* BFD Neighbor Signaled
                                                          Session Down. */
#define BCM_BFD_STATUS_LOCAL_DIAG_CODE_FORWARDING_PLANE_RESET 0x00001000 /* Local diag Forwarding
                                                          Plane Reset. */
#define BCM_BFD_STATUS_LOCAL_DIAG_CODE_PATH_DOWN 0x00002000 /* Local diag Path Down. */
#define BCM_BFD_STATUS_LOCAL_DIAG_CODE_CONCATENATED_PATH_DOWN 0x00004000 /* Local Diag
                                                          Concatenated Path
                                                          Down. */
#define BCM_BFD_STATUS_LOCAL_DIAG_CODE_ADMIN_DOWN 0x00008000 /* Local Diag
                                                          Administratively Down. */
#define BCM_BFD_STATUS_LOCAL_DIAG_CODE_REVERSE_CONCATENATED_PATH_DOWN 0x00010000 /* Local Diag Reverse
                                                          Concatenated Path
                                                          Down. */
#define BCM_BFD_STATUS_LOCAL_DIAG_CODE_MIS_CONNECTIVITY_DEFECT 0x00020000 /* Local Diag Mis conn
                                                          Defect. */

/* BFD fault flags. */
#define BCM_BFD_ENDPOINT_REMOTE_LOC 0x00000001 /* BFD endpoint time out */

typedef struct bcm_bfd_auth_simple_password_s {
    uint8 length; 
    uint8 password[BCM_BFD_SIMPLE_PASSWORD_KEY_LENGTH_MAX]; 
} bcm_bfd_auth_simple_password_t;

/* SHA1 authentication data. */
#define BCM_BFD_AUTH_SHA1_KEY_LENGTH    _SHR_BFD_AUTH_SHA1_KEY_LENGTH 

typedef struct bcm_bfd_auth_sha1_s {
    uint8 enable; 
    uint32 sequence; 
    uint8 key[BCM_BFD_AUTH_SHA1_KEY_LENGTH]; 
} bcm_bfd_auth_sha1_t;

/* BFD Session States. */
typedef enum bcm_bfd_state_e {
    bcmBFDStateAdminDown = _SHR_BFD_SESSION_STATE_ADMIN_DOWN, 
    bcmBFDStateDown = _SHR_BFD_SESSION_STATE_DOWN, 
    bcmBFDStateInit = _SHR_BFD_SESSION_STATE_INIT, 
    bcmBFDStateUp = _SHR_BFD_SESSION_STATE_UP, 
    bcmBFDStateCount = _SHR_BFD_SESSION_STATE_COUNT 
} bcm_bfd_state_t;

/* BFD Diagnostic Codes. */
typedef enum bcm_bfd_diag_code_e {
    bcmBFDDiagCodeNone = _SHR_BFD_DIAG_CODE_NONE, 
    bcmBFDDiagCodeCtrlDetectTimeExpired = _SHR_BFD_DIAG_CODE_CTRL_DETECT_TIME_EXPIRED, 
    bcmBFDDiagCodeEchoFailed = _SHR_BFD_DIAG_CODE_ECHO_FAILED, 
    bcmBFDDiagCodeNeighbourSignalledDown = _SHR_BFD_DIAG_CODE_NEIGHBOR_SIGNALED_SESSION_DOWN, 
    bcmBFDDiagCodeForwardingPlaneReset = _SHR_BFD_DIAG_CODE_FORWARDING_PLANE_RESET, 
    bcmBFDDiagCodePathDown = _SHR_BFD_DIAG_CODE_PATH_DOWN, 
    bcmBFDDiagCodeConcatPathDown = _SHR_BFD_DIAG_CODE_CONCATENATED_PATH_DOWN, 
    bcmBFDDiagCodeAdminDown = _SHR_BFD_DIAG_CODE_ADMIN_DOWN, 
    bcmBFDDiagCodeRevConcatPathDown = _SHR_BFD_DIAG_CODE_REVERSE_CONCATENATED_PATH_DOWN, 
    bcmBFDDiagCodeMisConnectivityDefect = _SHR_BFD_DIAG_CODE_MIS_CONNECTIVITY_DEFECT, 
    bcmBFDDiagCodeCount = _SHR_BFD_DIAG_CODE_COUNT 
} bcm_bfd_diag_code_t;

/* BFD Authentication Types. */
typedef enum bcm_bfd_auth_type_e {
    bcmBFDAuthTypeNone = _SHR_BFD_AUTH_TYPE_NONE, 
    bcmBFDAuthTypeSimplePassword = _SHR_BFD_AUTH_TYPE_SIMPLE_PASSWORD, 
    bcmBFDAuthTypeKeyedMD5 = _SHR_BFD_AUTH_TYPE_KEYED_MD5, 
    bcmBFDAuthTypeMeticulousKeyedMD5 = _SHR_BFD_AUTH_TYPE_METICULOUS_KEYED_MD5, 
    bcmBFDAuthTypeKeyedSHA1 = _SHR_BFD_AUTH_TYPE_KEYED_SHA1, 
    bcmBFDAuthTypeMeticulousKeyedSHA1 = _SHR_BFD_AUTH_TYPE_METICULOUS_KEYED_SHA1, 
    bcmBFDAuthTypeCount = _SHR_BFD_AUTH_TYPE_COUNT 
} bcm_bfd_auth_type_t;

/* BFD tunnel types. */
typedef enum bcm_bfd_tunnel_type_e {
    bcmBFDTunnelTypeUdp = 0,            /* BFD over IPv4/v6. */
    bcmBFDTunnelTypeIp4in4 = 1,         /* BFD over IPv4-in-IPv4 tunnel. */
    bcmBFDTunnelTypeIp6in4 = 2,         /* BFD over IPv6-in-IPv4 tunnel. */
    bcmBFDTunnelTypeIp4in6 = 3,         /* BFD over IPv4-in-IPv6 tunnel. */
    bcmBFDTunnelTypeIp6in6 = 4,         /* BFD over IPv6-in-IPv6 tunnel. */
    bcmBFDTunnelTypeGRE = 5,            /* BFD over GRE IPv4-in-IPv4 tunnel. */
    bcmBFDTunnelTypeGre4In4 = bcmBFDTunnelTypeGRE, /* BFD over GRE IPv4-in-IPv4 tunnel. */
    bcmBFDTunnelTypeMpls = 6,           /* BFD over MPLS LSP. */
    bcmBFDTunnelTypePweControlWord = 7, /* BFD over PW with CW. */
    bcmBFDTunnelTypePweRouterAlert = 8, /* BFD over PW with Router Alert. */
    bcmBFDTunnelTypePweTtl = 9,         /* BFD over PW with TTL=1. */
    bcmBFDTunnelTypeMplsTpCc = 10,      /* BFD for MPLS-TP proactive CC. */
    bcmBFDTunnelTypeMplsTpCcCv = 11,    /* BFD for MPLS-TP proactive CC&CV. */
    bcmBFDTunnelTypeGre6In4 = 12,       /* BFD over GRE IPv6-in-IPv4 tunnel. */
    bcmBFDTunnelTypeGre4In6 = 13,       /* BFD over GRE IPv4-in-IPv6 tunnel. */
    bcmBFDTunnelTypeGre6In6 = 14,       /* BFD over GRE IPv6-in-IPv6 tunnel. */
    bcmBFDTunnelTypePweGal = 15,        /* BFD over PW with GAL, GACH. */
    bcmBFDTunnelTypeMplsPhp = 16,       /* BFD over MPLS LSP and PHP. */
    bcmBFDTunnelTypeVxlanIPv4InIPv4 = 17, /* BFD over VxLAN IPv4-in-IPv4 tunnel. */
    bcmBFDTunnelTypeVxlanIPv4InIPv6 = 18, /* BFD over VxLAN IPv4-in-IPv6 tunnel. */
    bcmBFDTunnelTypeVxlanIPv6InIPv4 = 19, /* BFD over VxLAN IPv6-in-IPv4 tunnel. */
    bcmBFDTunnelTypeVxlanIPv6InIPv6 = 20, /* BFD over VxLAN IPv6-in-IPv6 tunnel. */
    bcmBFDTunnelTypeCount = 21 
} bcm_bfd_tunnel_type_t;

/* BFD endpoint ID type. */
typedef int bcm_bfd_endpoint_t;

/* BFD endpoint object. */
typedef struct bcm_bfd_endpoint_info_s {
    uint32 flags;                       /* Control flags. */
    bcm_bfd_endpoint_t id;              /* Endpoint identifier. */
    bcm_bfd_endpoint_t remote_id;       /* Remote endpoint identifier. */
    bcm_bfd_tunnel_type_t type;         /* Type of BFD encapsulation. */
    bcm_gport_t gport;                  /* Gport identifier. In case of VxLAN,
                                           Tunnel ID */
    bcm_gport_t tx_gport;               /* TX gport associated with this
                                           endpoint. */
    bcm_gport_t remote_gport;           /* Gport identifier of trapping
                                           destination: OAMP or CPU, local or
                                           remote. */
    int bfd_period;                     /* For local endpoints, this is the BFD
                                           transmission period in ms. */
    bcm_vpn_t vpn;                      /* VPN. */
    uint8 vlan_pri;                     /* VLAN tag priority. */
    uint8 inner_vlan_pri;               /* Inner VLAN tag priority. */
    bcm_vrf_t vrf_id;                   /* Vrf identifier. */
    bcm_mac_t dst_mac;                  /* Destination MAC. In case of VxLAN,
                                           Inner/Overlay Destination MAC. */
    bcm_mac_t src_mac;                  /* Source MAC. In case of VxLAN,
                                           Inner/Overlay Source MAC. */
    bcm_vlan_t pkt_inner_vlan_id;       /* TX Packet inner Vlan Id. In case of
                                           VxLAN, Inner/Overlay Inner VLAN Id
                                           and priority. */
    bcm_ip_t dst_ip_addr;               /* Destination IPv4 address. In case of
                                           VxLAN, Inner/Overlay Destination IPv4
                                           address. */
    bcm_ip6_t dst_ip6_addr;             /* Destination IPv6 address. In case of
                                           VxLAN, Inner/Overlay Destination IPv6
                                           address. */
    bcm_ip_t src_ip_addr;               /* Source IPv4 address. In case of
                                           VxLAN, Inner/Overlay Source IPv4
                                           address. */
    bcm_ip6_t src_ip6_addr;             /* Source IPv6 address. In case of
                                           VxLAN, Inner/Overlay Source IPv6
                                           address. */
    uint8 ip_tos;                       /* IPv4 Tos / IPv6 Traffic Class. In
                                           case of VxLAN, Inner/Overlay IPv4 Tos
                                           / IPv6 Traffic Class. */
    uint8 ip_ttl;                       /* IPv4 TTL / IPv6 Hop Count. In case of
                                           VxLAN, Inner/Overlay IPv4 TTL / IPv6
                                           Hop Count. */
    bcm_ip_t inner_dst_ip_addr;         /* Inner destination IPv4 address. */
    bcm_ip6_t inner_dst_ip6_addr;       /* Inner destination IPv6 address. */
    bcm_ip_t inner_src_ip_addr;         /* Inner source IPv4 address. */
    bcm_ip6_t inner_src_ip6_addr;       /* Inner source IPv6 address. */
    uint8 inner_ip_tos;                 /* Inner IPv4 Tos / IPv6 Traffic Class. */
    uint8 inner_ip_ttl;                 /* Inner IPv4 TTL / IPv6 Hop Count. */
    uint32 udp_src_port;                /* UDP source port for Ipv4, Ipv6. */
    bcm_mpls_label_t label;             /* Incoming inner label. */
    bcm_mpls_label_t mpls_hdr;          /* MPLS Header. */
    bcm_mpls_egress_label_t egress_label; /* The MPLS outgoing label information. */
    bcm_if_t egress_if;                 /* Egress interface. */
    uint8 mep_id[BCM_BFD_ENDPOINT_MAX_MEP_ID_LENGTH]; /* MPLS-TP CC/CV TLV and Source MEP ID. */
    uint8 mep_id_length;                /* Length of MPLS-TP CC/CV TLV and
                                           MEP-ID. */
    bcm_cos_t int_pri;                  /* Egress queuing for outgoing BFD to
                                           remote. */
    uint8 cpu_qid;                      /* CPU queue for BFD. */
    bcm_bfd_state_t local_state;        /* Local session state. */
    uint32 local_discr;                 /* Local discriminator. */
    bcm_bfd_diag_code_t local_diag;     /* Local diagnostic code. */
    uint32 local_flags;                 /* Flags combination on outgoing frames. */
    uint32 local_min_tx;                /* Desired local min tx interval. */
    uint32 local_min_rx;                /* Required local rx interval. */
    uint32 local_min_echo;              /* Local minimum echo interval. */
    uint8 local_detect_mult;            /* Local detection interval multiplier. */
    bcm_bfd_auth_type_t auth;           /* Authentication type. */
    uint32 auth_index;                  /* Authentication index. */
    uint32 tx_auth_seq;                 /* Tx authentication sequence id. */
    uint32 rx_auth_seq;                 /* Rx authentication sequence id. */
    uint32 remote_flags;                /* Remote flags. */
    bcm_bfd_state_t remote_state;       /* Remote session state. */
    uint32 remote_discr;                /* Remote discriminator. */
    bcm_bfd_diag_code_t remote_diag;    /* Remote diagnostic code. */
    uint32 remote_min_tx;               /* Desired remote min tx interval. */
    uint32 remote_min_rx;               /* Required remote rx interval. */
    uint32 remote_min_echo;             /* Remote minimum echo interval. */
    uint8 remote_detect_mult;           /* Remote detection interval multiplier. */
    int sampling_ratio;                 /* 0 - No packets sampled to the CPU.
                                           1-8 - Count of packets (with events)
                                           that need to arrive before one is
                                           sampled to the CPU. */
    uint8 loc_clear_threshold;          /* Number of packets required to reset
                                           the Loss-of-Continuity status per
                                           endpoint. */
    uint32 ip_subnet_length;            /* The subnet length for incoming packet
                                           validity check. Value 0 indicates no
                                           check is performed, positive values
                                           indicate the amount of MSBs to be
                                           compared. */
    uint8 remote_mep_id[BCM_BFD_ENDPOINT_MAX_MEP_ID_LENGTH]; /* MPLS-TP CC/CV TLV and Remote MEP ID. */
    uint8 remote_mep_id_length;         /* Length of MPLS-TP CC/CV TLV and
                                           REMOTE MEP-ID. */
    uint8 mis_conn_mep_id[BCM_BFD_ENDPOINT_MAX_MEP_ID_LENGTH]; /* MPLS-TP CC/CV TLV and Mis
                                           connectivity MEP ID. */
    uint8 mis_conn_mep_id_length;       /* Length of MPLS-TP CC/CV TLV and Mis
                                           connectivity MEP-ID. */
    uint32 bfd_detection_time;          /* Optional: BFD Detection Time, in
                                           microseconds. */
    bcm_vlan_t pkt_vlan_id;             /* TX Packet Vlan Id. In case of VxLAN,
                                           Inner/Overlay VLAN Id and priority. */
    bcm_vlan_t rx_pkt_vlan_id;          /* RX Packet Vlan Id. */
    bcm_mpls_label_t gal_label;         /* MPLS GAL label. */
    uint32 faults;                      /* Fault flags. */
    uint32 flags2;                      /* Second set of control flags. */
    int ipv6_extra_data_index;          /* Pointer to first extended data entry */
    int punt_good_packet_period;        /* BFD good packets sampling period.
                                           Every punt_good_packet_period
                                           milliseconds, a single packet is
                                           punted to the CPU */
    uint8 bfd_period_cluster;           /* Tx period group. All MEPs in a group
                                           must be created with the same Tx
                                           period. Modifying the Tx period in
                                           one MEP affects the others. */
    uint32 vxlan_vnid;                  /* VxLAN Network Identifier. */
    uint16 vlan_tpid;                   /* Vlan Tag Protocol Identifier. In case
                                           of VxLAN, Inner/Overlay Vlan Tag
                                           Protocol Identifier. */
    uint16 inner_vlan_tpid;             /* Inner Vlan Tag Protocol Identifier.
                                           In case of VxLAN, Inner/Overlay inner
                                           Vlan Tag Protocol Identifier. */
    int injected_network_qos;           /* QoS of the injected network packets. */
    bcm_oam_profile_t profile_id;       /* BFD action profile for BFD types with
                                           classification by LIF. */
    uint8 injected_core_id;             /* Which core to inject BFD packets. */
} bcm_bfd_endpoint_info_t;

/* BFD event types. */
typedef enum bcm_bfd_event_type_e {
    bcmBFDEventStateChange = 0, 
    bcmBFDEventRemoteStateDiag = 1, 
    bcmBFDEventSessionDiscriminatorChange = 2, 
    bcmBFDEventAuthenticationChange = 3, 
    bcmBFDEventParameterChange = 4, 
    bcmBFDEventSessionError = 5, 
    bcmBFDEventEndpointRemote = 6, 
    bcmBFDEventEndpointRemoteUp = 7, 
    bcmBFDEventEndpointTimeout = 8, 
    bcmBFDEventEndpointTimein = 9, 
    bcmBFDEventEndpointTimeoutEarly = 10, 
    bcmBFDEventEndpointFlagsChange = 11, 
    bcmBFDEventEndpointRemotePollBitSet = 12, 
    bcmBFDEventEndpointRemoteFinalBitSet = 13, 
    bcmBFDEventEndpointLocalSessionStateAdminDown = 14, 
    bcmBFDEventEndpointLocalSessionStateDown = 15, 
    bcmBFDEventEndpointLocalSessionStateInit = 16, 
    bcmBFDEventEndpointLocalSessionStateUp = 17, 
    bcmBFDEventEndpointMisConnectivityDefect = 18, /* Misconnectivity Defect Detected */
    bcmBFDEventEndpointMisConnectivityDefectClear = 19, /* Misconnectivity Defect Cleared */
    bcmBFDEventEndpoinUnExpectedMeg = 20, /* UnExpectedMeg Defect Detected */
    bcmBFDEventEndpoinUnExpectedMegClear = 21, /* UnExpectedMeg Defect Cleared */
    bcmBFDEventCount = 22 
} bcm_bfd_event_type_t;

/* BFD ACH Channel Types for MPLS-TP. */
typedef enum bcm_bfd_ach_channel_type_e {
    bcmBFDAchChannelTypeUserDefined = 1, 
    bcmBFDAchChannelTypeCount = 2 
} bcm_bfd_ach_channel_type_t;

typedef struct bcm_bfd_event_types_s {
    SHR_BITDCL w[_SHR_BITDCLSIZE(bcmBFDEventCount)]; 
} bcm_bfd_event_types_t;

#define BCM_BFD_EVENT_TYPE_SET(_event_types, _event_type)  SHR_BITSET((_event_types).w, (_event_type)) 

#define BCM_BFD_EVENT_TYPE_GET(_event_types, _event_type)  SHR_BITGET((_event_types).w, (_event_type)) 

#define BCM_BFD_EVENT_TYPE_CLEAR(_event_types, _event_type)  SHR_BITCLR((_event_types).w, (_event_type)) 

#define BCM_BFD_EVENT_TYPE_SET_ALL(_event_types)  SHR_BITSET_RANGE((_event_types).w, 0, bcmBFDEventCount) 

#define BCM_BFD_EVENT_TYPE_CLEAR_ALL(_event_types)  SHR_BITCLR_RANGE((_event_types).w, 0, bcmBFDEventCount) 

/* BFD endpoint statistics. */
typedef struct bcm_bfd_endpoint_stat_s {
    uint32 packets_in;              /* Total packets in. */
    uint32 packets_out;             /* Total packets out. */
    uint32 packets_drop;            /* Total packets drop. */
    uint32 packets_auth_drop;       /* Packets drop due to authentication
                                       failure. */
    uint64 packets_in_64;           /* Total packets in 64bit count. */
    uint64 packets_out_64;          /* Total packets out 64bit count. */
    uint64 packets_drop_64;         /* Total packets drop 64bit count. */
    uint64 packets_auth_drop_64;    /* Packets drop due to authentication
                                       failure 64bit count. */
    uint64 packets_echo_reply;      /* Total number of echo reply packets
                                       processed. */
} bcm_bfd_endpoint_stat_t;

/* BFD Session and Diag status of each endpoint along with endpoint id. */
typedef struct bcm_bfd_status_s {
    bcm_bfd_endpoint_t endpoint_id; /* Endpoint identifier. */
    uint32 session_status;          /* Session State and diag flags. */
} bcm_bfd_status_t;

/* Incoming bfd packets discarded statistics. */
typedef struct bcm_bfd_discard_stat_s {
    uint32 bfd_ver_err;                 /* Invalid BFD Version. */
    uint32 bfd_len_err;                 /* BFD Length Error. */
    uint32 bfd_detect_mult;             /* BFD detect multiplier Zero. */
    uint32 bfd_my_disc;                 /* BFD My discriminator Zero. */
    uint32 bfd_p_f_bit;                 /* BFD poll and final bits set. */
    uint32 bfd_m_bit;                   /* BFD M bit not equal to zero. */
    uint32 bfd_auth_type_mismatch;      /* BFD auth type mismatch. */
    uint32 bfd_auth_simple_err;         /* BFD auth simple password Error. */
    uint32 bfd_auth_m_sha1_err;         /* BFD auth SHA1 error. */
    uint32 bfd_sess_mismatch;           /* BFD Session mismatch. */
    uint32 bfd_mpls_fm_len_err;         /* BFD MPLS FM Packet received smaller
                                           than expected. */
    uint32 bfd_mpls_fm_type_err;        /* BFD MPLS FM type received
                                           unsupported. */
    uint32 bfd_echo_ipv4_mismatch;      /* BFD IPv4 echo pkt received with
                                           src/dst ip not equal. */
    uint32 bfd_echo_ipv6_mismatch;      /* BFD IPv6 echo pkt received with
                                           src/dst ip not equal. */
    uint32 bfd_ip_hdr_ver_err;          /* BFD IP packet received with invalid
                                           version. */
    uint32 bfd_mpls_no_label;           /* BFD MPLS packet received with no
                                           labels. */
    uint32 bfd_gal_additional_label_miss; /* BFD MPLS packet received with only
                                           one label and BOS as GAL. */
    uint32 bfd_unknown_ach_type;        /* BFD MPLS pkt received with unknown
                                           ACH type. */
    uint32 bfd_vxlan_i_flag_err;        /* BFD VXLAN pkt received with I flag
                                           not set. */
    uint32 bfd_ip_ttl_err;              /* BFD VXLAN pkt received with wrong TTL
                                           value. */
    uint32 bfd_unsupported_echo_encap_err; /* BFD VXLAN echo packet received which
                                           is not supported. */
    uint32 bfd_unsupported_ethertype_err; /* BFD packet received with unsupported
                                           ether type. */
    uint32 bfd_ether_type_len_err;      /* BFD pkt received with insufficient L2
                                           header length. */
    uint32 bfd_offset_err;              /* BFD packet received with unsupported
                                           offset type. */
    uint32 bfd_malformed_pkt_err;       /* BFD special type pkt received with
                                           nonzero discriminator for other than
                                           MPLS TP CC & CV type. */
    uint32 bfd_malformed_ipv4_pkt_err;  /* BFD pkt received with IPv4 ether
                                           type, but invalid
                                           TTL/Protocol/Src/Dst IP address. */
    uint32 bfd_malformed_ipv6_pkt_err;  /* BFD pkt received with IPv6 ether
                                           type, but invalid
                                           HopLimit/Protocol/Src/Dst IP address. */
    uint32 bfd_malformed_mpls_pkt_err;  /* BFD pkt received with MPLS ether
                                           type, but invalid TTL/Label. */
    uint32 bfd_sess_id_config_err;      /* BFD packet received with session id
                                           wrongly configured. */
    uint32 bfd_session_not_enabled;     /* BFD packet received with session no
                                           longer enabled. */
    uint32 bfd_your_disc_zero;          /* BFD Packet received with your
                                           discrimnator zero for session states
                                           INIT or UP. */
    uint32 bfd_your_disc_mismatch;      /* BFD packet received for a session
                                           with your discriminator mismatch with
                                           local discriminator. */
    uint32 bfd_my_disc_mismatch;        /* BFD packet received for a session
                                           with my discriminator mismatch with
                                           remote discriminator. */
    uint32 bfd_pkts_discarded_admin_down; /* BFD packet received for a session in
                                           ADMIN DOWN state. */
    uint32 bfd_echo_your_disc_zero;     /* BFD Echo packet received with zero
                                           your discriminator. */
    uint32 bfd_echo_your_disc_err;      /* BFD Echo packet received for a
                                           session with your discriminator
                                           mismatch with local discriminator. */
    uint32 bfd_mpls_fm_sess_mismatch;   /* BFD MPLS FM pkt received for non
                                           CC/CC_CV session. */
    uint32 bfd_non_cc_cv_err;           /* BFD packet received for a CC_CV
                                           session, but its not of MPLS TP CC/CV
                                           type. */
} bcm_bfd_discard_stat_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* Get 64-bit/32-bit BFD endpoint stats */
extern int bcm_bfd_endpoint_stat_get(
    int unit, 
    bcm_bfd_endpoint_t endpoint, 
    bcm_bfd_endpoint_stat_t *ctr_info, 
    uint32 options);

/* 
 * User should call this API - once to retrieve endpoint count
 * and again to retrieve the actual endpoint status.
 */
extern int bcm_bfd_status_multi_get(
    int unit, 
    int max_endpoints, 
    bcm_bfd_status_t *status_arr, 
    int *count);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Callback function type for BFD event handling. */
typedef int (*bcm_bfd_event_cb)(
    int unit, 
    uint32 flags, 
    bcm_bfd_event_types_t events, 
    bcm_bfd_endpoint_t endpoint, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Initialize the BFD subsystem */
extern int bcm_bfd_init(
    int unit);

/* Shut down the BFD subsystem. */
extern int bcm_bfd_detach(
    int unit);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Initialize a BFD endpoint information structure. */
extern void bcm_bfd_endpoint_info_t_init(
    bcm_bfd_endpoint_info_t *endpoint_info);

#ifndef BCM_HIDE_DISPATCHABLE

/* Create or update an BFD endpoint object */
extern int bcm_bfd_endpoint_create(
    int unit, 
    bcm_bfd_endpoint_info_t *endpoint_info);

/* Get an BFD endpoint object. */
extern int bcm_bfd_endpoint_get(
    int unit, 
    bcm_bfd_endpoint_t endpoint, 
    bcm_bfd_endpoint_info_t *endpoint_info);

/* Start the Transmission of BFD PDUs. */
extern int bcm_bfd_tx_start(
    int unit);

/* Stop the Transmission of BFD PDUs. */
extern int bcm_bfd_tx_stop(
    int unit);

/* Destroy an BFD endpoint object */
extern int bcm_bfd_endpoint_destroy(
    int unit, 
    bcm_bfd_endpoint_t endpoint);

/* Destroy all BFD endpoint objects */
extern int bcm_bfd_endpoint_destroy_all(
    int unit);

/* Register a callback for handling BFD events */
extern int bcm_bfd_event_register(
    int unit, 
    bcm_bfd_event_types_t event_types, 
    bcm_bfd_event_cb cb, 
    void *user_data);

/* Unregister a callback for handling BFD events */
extern int bcm_bfd_event_unregister(
    int unit, 
    bcm_bfd_event_types_t event_types, 
    bcm_bfd_event_cb cb);

/* 
 * Poll an BFD endpoint object.  Valid only for BFD sessions in Demand
 * Mode and state of bcmBFDStateUp.
 */
extern int bcm_bfd_endpoint_poll(
    int unit, 
    bcm_bfd_endpoint_t endpoint);

/* Set SHA1 authentication entry */
extern int bcm_bfd_auth_sha1_set(
    int unit, 
    int index, 
    bcm_bfd_auth_sha1_t *sha1);

/* Get SHA1 authentication entry */
extern int bcm_bfd_auth_sha1_get(
    int unit, 
    int index, 
    bcm_bfd_auth_sha1_t *sha1);

/* Set Simple Password authentication entry */
extern int bcm_bfd_auth_simple_password_set(
    int unit, 
    int index, 
    bcm_bfd_auth_simple_password_t *sp);

/* Get Simple Password authentication entry */
extern int bcm_bfd_auth_simple_password_get(
    int unit, 
    int index, 
    bcm_bfd_auth_simple_password_t *sp);

/* Reset the bfd discarded statistics in FW. */
extern int bcm_bfd_discard_stat_set(
    int unit, 
    bcm_bfd_discard_stat_t *discarded_info);

/* Get the bfd discarded statistics from FW. */
extern int bcm_bfd_discard_stat_get(
    int unit, 
    bcm_bfd_discard_stat_t *discarded_info);

/* Set ACH Channel Type for MPLS-TP BFD. */
extern int bcm_bfd_ach_channel_set(
    int unit, 
    bcm_bfd_ach_channel_type_t ach_channel_type, 
    uint32 value);

/* Get ACH Channel Type for MPLS-TP BFD. */
extern int bcm_bfd_ach_channel_get(
    int unit, 
    bcm_bfd_ach_channel_type_t ach_channel_type, 
    uint32 *value);

#endif /* defined(INCLUDE_BFD) */

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_BFD_H__ */

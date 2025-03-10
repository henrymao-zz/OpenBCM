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

#include <soc/types.h>
#include <soc/error.h>
#include <soc/portmod/portmod_internal.h>
#include <soc/portmod/portmod.h>
#include <soc/portmod/portmod_dispatch.h>

#ifdef PORTMOD_DIAG

enum_mapping_t portmod_dispatch_type_t_mapping[] = {
#ifdef PORTMOD_PM4X25_SUPPORT
    {"Pm4x25", portmodDispatchTypePm4x25},
#endif /*PORTMOD_PM4X25_SUPPORT  */
#ifdef PORTMOD_PM4X10_SUPPORT
    {"Pm4x10", portmodDispatchTypePm4x10},
#endif /*PORTMOD_PM4X10_SUPPORT  */
#ifdef PORTMOD_PM4X10TD_SUPPORT
    {"Pm4x10td", portmodDispatchTypePm4x10td},
#endif /*PORTMOD_PM4X10TD_SUPPORT  */
#ifdef PORTMOD_PM12X10_SUPPORT
    {"Pm12x10", portmodDispatchTypePm12x10},
#endif /*PORTMOD_PM12X10_SUPPORT  */
#ifdef PORTMOD_PM4x10Q_SUPPORT
    {"Pm4x10Q", portmodDispatchTypePm4x10Q},
#endif /*PORTMOD_PM4x10Q_SUPPORT  */
#ifdef PORTMOD_PM_QTC_SUPPORT
    {"Pm_qtc", portmodDispatchTypePm_qtc},
#endif /*PORTMOD_PM_QTC_SUPPORT  */
#ifdef PORTMOD_PM_OS_ILKN_SUPPORT
    {"PmOsILKN", portmodDispatchTypePmOsILKN},
#endif /*PORTMOD_PM_OS_ILKN_SUPPORT  */
#ifdef PORTMOD_PM_OS_ILKN_50G_SUPPORT
    {"PmOsILKN_50G", portmodDispatchTypePmOsILKN_50G},
#endif /*PORTMOD_PM_OS_ILKN_50G_SUPPORT  */
#ifdef PORTMOD_DNX_FABRIC_SUPPORT
    {"Dnx_fabric", portmodDispatchTypeDnx_fabric},
#endif /*PORTMOD_DNX_FABRIC_SUPPORT  */
#ifdef PORTMOD_DNX_FABRIC_O_NIF_SUPPORT
    {"Dnx_fabric_o_nif", portmodDispatchTypeDnx_fabric_o_nif},
#endif /*PORTMOD_DNX_FABRIC_O_NIF_SUPPORT  */
#ifdef PORTMOD_PM8X50_FABRIC_SUPPORT
    {"Pm8x50_fabric", portmodDispatchTypePm8x50_fabric},
#endif /*PORTMOD_PM8X50_FABRIC_SUPPORT  */
#ifdef PORTMOD_PM8X100_FABRIC_SUPPORT
    {"Pm8x100_fabric", portmodDispatchTypePm8x100_fabric},
#endif /*PORTMOD_PM8X100_FABRIC_SUPPORT  */
#ifdef PORTMOD_PM4X25TD_SUPPORT
    {"Pm4x25td", portmodDispatchTypePm4x25td},
#endif /*PORTMOD_PM4X25TD_SUPPORT  */
#ifdef PORTMOD_PM12X10_XGS_SUPPORT
    {"Pm12x10_xgs", portmodDispatchTypePm12x10_xgs},
#endif /*PORTMOD_PM12X10_XGS_SUPPORT  */
#ifdef PORTMOD_PM4X2P5_SUPPORT
    {"Pm4x2p5", portmodDispatchTypePm4x2p5},
#endif /*PORTMOD_PM4X2P5_SUPPORT  */
#ifdef PORTMOD_CPM4X25_SUPPORT
    {"Cpm4x25", portmodDispatchTypeCpm4x25},
#endif /*PORTMOD_CPM4X25_SUPPORT  */
#ifdef PORTMOD_PM8X50_SUPPORT
    {"Pm8x50", portmodDispatchTypePm8x50},
#endif /*PORTMOD_PM8X50_SUPPORT  */
#ifdef PORTMOD_PM4X10_QTC_SUPPORT
    {"Pm4x10_qtc", portmodDispatchTypePm4x10_qtc},
#endif /*PORTMOD_PM4X10_QTC_SUPPORT  */
#ifdef PORTMOD_PM8X50_FLEXE_GEN2_SUPPORT
    {"Pm8x50_flexe_gen2", portmodDispatchTypePm8x50_flexe_gen2},
#endif /*PORTMOD_PM8X50_FLEXE_GEN2_SUPPORT  */
#ifdef PORTMOD_PM4X25D_SUPPORT
    {"Pm4x25d", portmodDispatchTypePm4x25d},
#endif /*PORTMOD_PM4X25D_SUPPORT  */
#ifdef PORTMOD_PMNULL_SUPPORT
    {"PmNull", portmodDispatchTypePmNull},
#endif /*PORTMOD_PMNULL_SUPPORT  */
    {NULL, 0}
};

enum_mapping_t portmod_loopback_mode_t_mapping[] = {
    {"MacOuter", portmodLoopbackMacOuter},
    {"MacCore", portmodLoopbackMacCore},
    {"MacPCS", portmodLoopbackMacPCS},
    {"MacAsyncFifo", portmodLoopbackMacAsyncFifo},
    {"PhyGloopPCS", portmodLoopbackPhyGloopPCS},
    {"PhyGloopPMD", portmodLoopbackPhyGloopPMD},
    {"PhyRloopPCS", portmodLoopbackPhyRloopPCS},
    {"PhyRloopPMD", portmodLoopbackPhyRloopPMD},
    {"MacRloop", portmodLoopbackMacRloop},
    {NULL, 0}
};

enum_mapping_t portmod_core_port_mode_t_mapping[] = {
    {"Quad", portmodPortModeQuad},
    {"Tri012", portmodPortModeTri012},
    {"Tri023", portmodPortModeTri023},
    {"Dual", portmodPortModeDual},
    {"Single", portmodPortModeSingle},
    {"Single_8", portmodPortModeSingle_8},
    {NULL, 0}
};

enum_mapping_t portmod_port_mode_aux_info_t_mapping[] = {
    {"None", portmodModeInfoNone},
    {"ThreePorts", portmodModeInfoThreePorts},
    {"TwoDualModePorts", portmodModeInfoTwoDualModePorts},
    {NULL, 0}
};

enum_mapping_t portmod_mac_soft_reset_mode_t_mapping[] = {
    {"In_Out", portmodMacSoftResetModeIn_Out},
    {"In", portmodMacSoftResetModeIn},
    {"Out", portmodMacSoftResetModeOut},
    {NULL, 0}
};

enum_mapping_t portmod_prbs_mode_t_mapping[] = {
    {"Phy", portmodPrbsModePhy},
    {"Mac", portmodPrbsModeMac},
    {NULL, 0}
};

enum_mapping_t portmod_ext_to_int_phy_ctrlcode_t_mapping[] = {
    {"Init", portmodExtToInt_CtrlCode_Init},
    {"Reset", portmodExtToInt_CtrlCode_Reset},
    {"Link", portmodExtToInt_CtrlCode_Link},
    {"Enable", portmodExtToInt_CtrlCode_Enable},
    {"Duplex", portmodExtToInt_CtrlCode_Duplex},
    {"Speed", portmodExtToInt_CtrlCode_Speed},
    {"Master", portmodExtToInt_CtrlCode_Master},
    {"AN", portmodExtToInt_CtrlCode_AN},
    {"AdvLocal", portmodExtToInt_CtrlCode_AdvLocal},
    {"AdvRemote", portmodExtToInt_CtrlCode_AdvRemote},
    {"LB", portmodExtToInt_CtrlCode_LB},
    {"Interface", portmodExtToInt_CtrlCode_Interface},
    {"Ability", portmodExtToInt_CtrlCode_Ability},
    {"AbilityAdvert", portmodExtToInt_CtrlCode_AbilityAdvert},
    {"AbilityRemote", portmodExtToInt_CtrlCode_AbilityRemote},
    {"AbilityLocal", portmodExtToInt_CtrlCode_AbilityLocal},
    {"LinkupEvt", portmodExtToInt_CtrlCode_LinkupEvt},
    {"LinkdnEvt", portmodExtToInt_CtrlCode_LinkdnEvt},
    {"MDIX", portmodExtToInt_CtrlCode_MDIX},
    {"MDIXStatus", portmodExtToInt_CtrlCode_MDIXStatus},
    {"MediumConfig", portmodExtToInt_CtrlCode_MediumConfig},
    {"Medium", portmodExtToInt_CtrlCode_Medium},
    {"CableDiag", portmodExtToInt_CtrlCode_CableDiag},
    {"Control", portmodExtToInt_CtrlCode_Control},
    {"Firmware", portmodExtToInt_CtrlCode_Firmware},
    {"TimesyncConfig", portmodExtToInt_CtrlCode_TimesyncConfig},
    {"TimesyncControl", portmodExtToInt_CtrlCode_TimesyncControl},
    {"TimesyncEnhancedCapture", portmodExtToInt_CtrlCode_TimesyncEnhancedCapture},
    {"DiagCtrl", portmodExtToInt_CtrlCode_DiagCtrl},
    {"LaneControl", portmodExtToInt_CtrlCode_LaneControl},
    {"OAMConfig", portmodExtToInt_CtrlCode_OAMConfig},
    {"OAMControl", portmodExtToInt_CtrlCode_OAMControl},
    {"Multi", portmodExtToInt_CtrlCode_Multi},
    {"Probe", portmodExtToInt_CtrlCode_Probe},
    {"PreconditionBeforeProbe", portmodExtToInt_CtrlCode_PreconditionBeforeProbe},
    {"LinkfaultGet", portmodExtToInt_CtrlCode_LinkfaultGet},
    {"SpeedLine", portmodExtToInt_CtrlCode_SpeedLine},
    {NULL, 0}
};

enum_mapping_t portmod_cpm_core_mode_t_mapping[] = {
    {"AllCpri", portmodCpmAllCpri},
    {"AllIEEE", portmodCpmAllIEEE},
    {"AllHIGIG", portmodCpmAllHIGIG},
    {"MixEthCpri", portmodCpmMixEthCpri},
    {NULL, 0}
};

enum_mapping_t portmod_core_port_enet_cpri_type_t_mapping[] = {
    {"EthMode", portmodCpmPrtEthMode},
    {"EthOfMixedMode", portmodCpmPrtEthOfMixedMode},
    {"CpriMode", portmodCpmPrtCpriMode},
    {"CpriOfMixedMode", portmodCpmPrtCpriOfMixedMode},
    {"Rsvd4Mode", portmodCpmPrtRsvd4Mode},
    {"Rsvd4OfMixedMode", portmodCpmPrtRsvd4OfMixedMode},
    {NULL, 0}
};

enum_mapping_t portmod_qtc_mode_t_mapping[] = {
    {"Invalid", portmodQtcModeInvalid},
    {"Ethernet", portmodQtcModeEthernet},
    {"Qsgmii", portmodQtcModeQsgmii},
    {"Usxgmii", portmodQtcModeUsxgmii},
    {NULL, 0}
};

enum_mapping_t portmod_vco_type_t_mapping[] = {
    {"Invalid", portmodVCOInvalid},
    {"20G", portmodVCO20G},
    {"21G", portmodVCO21G},
    {"25G", portmodVCO25G},
    {"26G", portmodVCO26G},
    {"27G", portmodVCO27G},
    {"20P625G", portmodVCO20P625G},
    {"20P937G", portmodVCO20P937G},
    {"22P5G", portmodVCO22P5G},
    {"23G", portmodVCO23G},
    {"25P781G", portmodVCO25P781G},
    {"26P562G", portmodVCO26P562G},
    {"6P25G", portmodVCO6P25G},
    {"6P5625G", portmodVCO6P5625G},
    {"8P125G", portmodVCO8P125G},
    {"9P735G", portmodVCO9P735G},
    {"10G", portmodVCO10G},
    {"10P3125G", portmodVCO10P3125G},
    {"10P9375G", portmodVCO10P9375G},
    {"12P5G", portmodVCO12P5G},
    {"27P343G", portmodVCO27P343G},
    {"28P125G", portmodVCO28P125G},
    {"19P660G", portmodVCO19P660G},
    {"20P275G", portmodVCO20P275G},
    {"24P330G", portmodVCO24P330G},
    {"24P576G", portmodVCO24P576G},
    {"53P125G", portmodVCO53P125G},
    {"26P773G", portmodVCO26P773G},
    {"27P622G", portmodVCO27P622G},
    {"27P739G", portmodVCO27P739G},
    {"27P952G", portmodVCO27P952G},
    {"28P076G", portmodVCO28P076G},
    {"51P5625G", portmodVCO51P5625G},
    {NULL, 0}
};

enum_mapping_t portmod_call_back_action_type_t_mapping[] = {
    {"Pre", portmodCallBackActionTypePre},
    {"During", portmodCallBackActionTypeDuring},
    {"Post", portmodCallBackActionTypePost},
    {"Lock", portmodCallBackActionTypeLock},
    {"Unlock", portmodCallBackActionTypeUnlock},
    {NULL, 0}
};

enum_mapping_t portmod_intr_type_t_mapping[] = {
    {"MibTxMemErr", portmodIntrTypeMibTxMemErr},
    {"MibRxMemErr", portmodIntrTypeMibRxMemErr},
    {"MacTxCdcMemErr", portmodIntrTypeMacTxCdcMemErr},
    {"MacRxCdcMemErr", portmodIntrTypeMacRxCdcMemErr},
    {"MacRxTsCdcMemErr", portmodIntrTypeMacRxTsCdcMemErr},
    {"TscErr", portmodIntrTypeTscErr},
    {"PmdErr", portmodIntrTypePmdErr},
    {"RxFcReqFull", portmodIntrTypeRxFcReqFull},
    {"Core0Intr", portmodIntrTypeCore0Intr},
    {"Core1Intr", portmodIntrTypeCore1Intr},
    {"Core2Intr", portmodIntrTypeCore2Intr},
    {"Core3Intr", portmodIntrTypeCore3Intr},
    {"Tsc0Intr", portmodIntrTypeTsc0Intr},
    {"Tsc1Intr", portmodIntrTypeTsc1Intr},
    {"Tsc2Intr", portmodIntrTypeTsc2Intr},
    {"Linkdown", portmodIntrTypeLinkdown},
    {"MacErr", portmodIntrTypeMacErr},
    {"TxPktUnderflow", portmodIntrTypeTxPktUnderflow},
    {"TxPktOverflow", portmodIntrTypeTxPktOverflow},
    {"TxLlfcMsgOverflow", portmodIntrTypeTxLlfcMsgOverflow},
    {"TxTSFifoOverflow", portmodIntrTypeTxTSFifoOverflow},
    {"RxPktOverflow", portmodIntrTypeRxPktOverflow},
    {"RxMsgOverflow", portmodIntrTypeRxMsgOverflow},
    {"TxCdcSingleBitErr", portmodIntrTypeTxCdcSingleBitErr},
    {"TxCdcDoubleBitErr", portmodIntrTypeTxCdcDoubleBitErr},
    {"RxCdcSingleBitErr", portmodIntrTypeRxCdcSingleBitErr},
    {"RxCdcDoubleBitErr", portmodIntrTypeRxCdcDoubleBitErr},
    {"RxTsMemSingleBitErr", portmodIntrTypeRxTsMemSingleBitErr},
    {"RxTsMemDoubleBitErr", portmodIntrTypeRxTsMemDoubleBitErr},
    {"LocalFaultStatus", portmodIntrTypeLocalFaultStatus},
    {"RemoteFaultStatus", portmodIntrTypeRemoteFaultStatus},
    {"LinkInterruptionStatus", portmodIntrTypeLinkInterruptionStatus},
    {"TsEntryValid", portmodIntrTypeTsEntryValid},
    {"MibMemSingleBitErr", portmodIntrTypeMibMemSingleBitErr},
    {"MibMemDoubleBitErr", portmodIntrTypeMibMemDoubleBitErr},
    {"MibMemMultipleBitErr", portmodIntrTypeMibMemMultipleBitErr},
    {"TscCore0Err", portmodIntrTypeTscCore0Err},
    {"TscCore1Err", portmodIntrTypeTscCore1Err},
    {"FcReqFull", portmodIntrTypeFcReqFull},
    {"Linkup", portmodIntrTypeLinkup},
    {"FdrInterrupt", portmodIntrTypeFdrInterrupt},
    {"TxPfcFifoOverflow", portmodIntrTypeTxPfcFifoOverflow},
    {"RxPfcFifoOverflow", portmodIntrTypeRxPfcFifoOverflow},
    {NULL, 0}
};

enum_mapping_t portmod_stat_val_t_mapping[] = {
    {"IfInOctets", portmodIfInOctets},
    {"IfInUcastPkts", portmodIfInUcastPkts},
    {"IfInNUcastPkts", portmodIfInNUcastPkts},
    {"IfInBroadcastPkts", portmodIfInBroadcastPkts},
    {"IfInMulticastPkts", portmodIfInMulticastPkts},
    {"IfInDiscards", portmodIfInDiscards},
    {"IfInErrors", portmodIfInErrors},
    {"IfOutOctets", portmodIfOutOctets},
    {"IfOutUcastPkts", portmodIfOutUcastPkts},
    {"IfOutNUcastPkts", portmodIfOutNUcastPkts},
    {"IfOutBroadcastPkts", portmodIfOutBroadcastPkts},
    {"IfOutMulticastPkts", portmodIfOutMulticastPkts},
    {"IfOutDiscards", portmodIfOutDiscards},
    {"IfOutErrors", portmodIfOutErrors},
    {"IpInReceives", portmodIpInReceives},
    {"IpInHdrErrors", portmodIpInHdrErrors},
    {"IpForwDatagrams", portmodIpForwDatagrams},
    {"IpInDiscards", portmodIpInDiscards},
    {"Dot1dBasePortMtuExceededDiscards", portmodDot1dBasePortMtuExceededDiscards},
    {"Dot1dTpPortInFrames", portmodDot1dTpPortInFrames},
    {"Dot1dTpPortOutFrames", portmodDot1dTpPortOutFrames},
    {"Dot1dPortInDiscards", portmodDot1dPortInDiscards},
    {"EtherStatsDropEvents", portmodEtherStatsDropEvents},
    {"EtherStatsOctets", portmodEtherStatsOctets},
    {"EtherStatsPkts", portmodEtherStatsPkts},
    {"EtherStatsBroadcastPkts", portmodEtherStatsBroadcastPkts},
    {"EtherStatsMulticastPkts", portmodEtherStatsMulticastPkts},
    {"EtherStatsCRCAlignErrors", portmodEtherStatsCRCAlignErrors},
    {"EtherStatsUndersizePkts", portmodEtherStatsUndersizePkts},
    {"EtherStatsOversizePkts", portmodEtherStatsOversizePkts},
    {"EtherRxOversizePkts", portmodEtherRxOversizePkts},
    {"EtherTxOversizePkts", portmodEtherTxOversizePkts},
    {"EtherStatsFragments", portmodEtherStatsFragments},
    {"EtherStatsJabbers", portmodEtherStatsJabbers},
    {"EtherStatsPkts64Octets", portmodEtherStatsPkts64Octets},
    {"EtherStatsPkts65to127Octets", portmodEtherStatsPkts65to127Octets},
    {"EtherStatsPkts128to255Octets", portmodEtherStatsPkts128to255Octets},
    {"EtherStatsPkts256to511Octets", portmodEtherStatsPkts256to511Octets},
    {"EtherStatsPkts512to1023Octets", portmodEtherStatsPkts512to1023Octets},
    {"EtherStatsPkts1024to1518Octets", portmodEtherStatsPkts1024to1518Octets},
    {"BcmEtherStatsPkts1519to1522Octets", portmodBcmEtherStatsPkts1519to1522Octets},
    {"BcmEtherStatsPkts1522to2047Octets", portmodBcmEtherStatsPkts1522to2047Octets},
    {"BcmEtherStatsPkts2048to4095Octets", portmodBcmEtherStatsPkts2048to4095Octets},
    {"BcmEtherStatsPkts4095to9216Octets", portmodBcmEtherStatsPkts4095to9216Octets},
    {"BcmEtherStatsPkts9217to16383Octets", portmodBcmEtherStatsPkts9217to16383Octets},
    {"BcmReceivedPkts64Octets", portmodBcmReceivedPkts64Octets},
    {"BcmReceivedPkts65to127Octets", portmodBcmReceivedPkts65to127Octets},
    {"BcmReceivedPkts128to255Octets", portmodBcmReceivedPkts128to255Octets},
    {"BcmReceivedPkts256to511Octets", portmodBcmReceivedPkts256to511Octets},
    {"BcmReceivedPkts512to1023Octets", portmodBcmReceivedPkts512to1023Octets},
    {"BcmReceivedPkts1024to1518Octets", portmodBcmReceivedPkts1024to1518Octets},
    {"BcmReceivedPkts1519to2047Octets", portmodBcmReceivedPkts1519to2047Octets},
    {"BcmReceivedPkts2048to4095Octets", portmodBcmReceivedPkts2048to4095Octets},
    {"BcmReceivedPkts4095to9216Octets", portmodBcmReceivedPkts4095to9216Octets},
    {"BcmReceivedPkts9217to16383Octets", portmodBcmReceivedPkts9217to16383Octets},
    {"BcmTransmittedPkts64Octets", portmodBcmTransmittedPkts64Octets},
    {"BcmTransmittedPkts65to127Octets", portmodBcmTransmittedPkts65to127Octets},
    {"BcmTransmittedPkts128to255Octets", portmodBcmTransmittedPkts128to255Octets},
    {"BcmTransmittedPkts256to511Octets", portmodBcmTransmittedPkts256to511Octets},
    {"BcmTransmittedPkts512to1023Octets", portmodBcmTransmittedPkts512to1023Octets},
    {"BcmTransmittedPkts1024to1518Octets", portmodBcmTransmittedPkts1024to1518Octets},
    {"BcmTransmittedPkts1519to2047Octets", portmodBcmTransmittedPkts1519to2047Octets},
    {"BcmTransmittedPkts2048to4095Octets", portmodBcmTransmittedPkts2048to4095Octets},
    {"BcmTransmittedPkts4095to9216Octets", portmodBcmTransmittedPkts4095to9216Octets},
    {"BcmTransmittedPkts9217to16383Octets", portmodBcmTransmittedPkts9217to16383Octets},
    {"EtherStatsTXNoErrors", portmodEtherStatsTXNoErrors},
    {"EtherStatsRXNoErrors", portmodEtherStatsRXNoErrors},
    {"Dot3StatsFCSErrors", portmodDot3StatsFCSErrors},
    {"Dot3StatsInternalMacTransmitErrors", portmodDot3StatsInternalMacTransmitErrors},
    {"Dot3StatsFrameTooLongs", portmodDot3StatsFrameTooLongs},
    {"Dot3StatsSymbolErrors", portmodDot3StatsSymbolErrors},
    {"Dot3ControlInUnknownOpcodes", portmodDot3ControlInUnknownOpcodes},
    {"Dot3InPauseFrames", portmodDot3InPauseFrames},
    {"Dot3OutPauseFrames", portmodDot3OutPauseFrames},
    {"IfHCInOctets", portmodIfHCInOctets},
    {"IfHCInUcastPkts", portmodIfHCInUcastPkts},
    {"IfHCInMulticastPkts", portmodIfHCInMulticastPkts},
    {"IfHCInBroadcastPkts", portmodIfHCInBroadcastPkts},
    {"IfHCOutOctets", portmodIfHCOutOctets},
    {"IfHCOutUcastPkts", portmodIfHCOutUcastPkts},
    {"IfHCOutMulticastPkts", portmodIfHCOutMulticastPkts},
    {"IfHCOutBroadcastPckts", portmodIfHCOutBroadcastPckts},
    {"Ipv6IfStatsInReceives", portmodIpv6IfStatsInReceives},
    {"Ipv6IfStatsInHdrErrors", portmodIpv6IfStatsInHdrErrors},
    {"Ipv6IfStatsInAddrErrors", portmodIpv6IfStatsInAddrErrors},
    {"Ipv6IfStatsInDiscards", portmodIpv6IfStatsInDiscards},
    {"Ipv6IfStatsOutForwDatagrams", portmodIpv6IfStatsOutForwDatagrams},
    {"Ipv6IfStatsOutDiscards", portmodIpv6IfStatsOutDiscards},
    {"Ipv6IfStatsInMcastPkts", portmodIpv6IfStatsInMcastPkts},
    {"Ipv6IfStatsOutMcastPkts", portmodIpv6IfStatsOutMcastPkts},
    {"Ieee8021PfcRequests", portmodIeee8021PfcRequests},
    {"Ieee8021PfcIndications", portmodIeee8021PfcIndications},
    {"BcmIPMCBridgedPckts", portmodBcmIPMCBridgedPckts},
    {"BcmIPMCRoutedPckts", portmodBcmIPMCRoutedPckts},
    {"BcmIPMCInDroppedPckts", portmodBcmIPMCInDroppedPckts},
    {"BcmIPMCOutDroppedPckts", portmodBcmIPMCOutDroppedPckts},
    {"BcmRxVlanTagFrame", portmodBcmRxVlanTagFrame},
    {"BcmRxDoubleVlanTagFrame", portmodBcmRxDoubleVlanTagFrame},
    {"BcmTxVlanTagFrame", portmodBcmTxVlanTagFrame},
    {"BcmTxDoubleVlanTagFrame", portmodBcmTxDoubleVlanTagFrame},
    {"BcmRxPFCControlFrame", portmodBcmRxPFCControlFrame},
    {"BcmTxPFCControlFrame", portmodBcmTxPFCControlFrame},
    {"BcmRxPFCFramePriority0", portmodBcmRxPFCFramePriority0},
    {"BcmRxPFCFramePriority1", portmodBcmRxPFCFramePriority1},
    {"BcmRxPFCFramePriority2", portmodBcmRxPFCFramePriority2},
    {"BcmRxPFCFramePriority3", portmodBcmRxPFCFramePriority3},
    {"BcmRxPFCFramePriority4", portmodBcmRxPFCFramePriority4},
    {"BcmRxPFCFramePriority5", portmodBcmRxPFCFramePriority5},
    {"BcmRxPFCFramePriority6", portmodBcmRxPFCFramePriority6},
    {"BcmRxPFCFramePriority7", portmodBcmRxPFCFramePriority7},
    {"BcmTxPFCFramePriority0", portmodBcmTxPFCFramePriority0},
    {"BcmTxPFCFramePriority1", portmodBcmTxPFCFramePriority1},
    {"BcmTxPFCFramePriority2", portmodBcmTxPFCFramePriority2},
    {"BcmTxPFCFramePriority3", portmodBcmTxPFCFramePriority3},
    {"BcmTxPFCFramePriority4", portmodBcmTxPFCFramePriority4},
    {"BcmTxPFCFramePriority5", portmodBcmTxPFCFramePriority5},
    {"BcmTxPFCFramePriority6", portmodBcmTxPFCFramePriority6},
    {"BcmTxPFCFramePriority7", portmodBcmTxPFCFramePriority7},
    {NULL, 0}
};

enum_mapping_t portmod_preemption_control_t_mapping[] = {
    {"Invalid", portmodPreemptionControlInvalid},
    {"PreemptionSupport", portmodPreemptionControlPreemptionSupport},
    {"EnableTx", portmodPreemptionControlEnableTx},
    {"VerifyEnable", portmodPreemptionControlVerifyEnable},
    {"VerifyTime", portmodPreemptionControlVerifyTime},
    {"VerifyAttempts", portmodPreemptionControlVerifyAttempts},
    {"NonFinalFragSizeRx", portmodPreemptionControlNonFinalFragSizeRx},
    {"FinalFragSizeRx", portmodPreemptionControlFinalFragSizeRx},
    {NULL, 0}
};

enum_mapping_t portmod_preemption_tx_status_t_mapping[] = {
    {"Inactive", portmodPreemptionTxStatusInactive},
    {"Verifying", portmodPreemptionTxStatusVerifying},
    {"Active", portmodPreemptionTxStatusActive},
    {NULL, 0}
};

enum_mapping_t portmod_preemption_verify_status_type_t_mapping[] = {
    {"Status", portmodPreemptionVerifyStatus},
    {"CountStatus", portmodPreemptionVerifyCountStatus},
    {NULL, 0}
};

enum_mapping_t portmod_preemption_verify_status_t_mapping[] = {
    {"Disabled", portmodPreemptionVerifyStatusDisabled},
    {"Initial", portmodPreemptionVerifyStatusInitial},
    {"InProgress", portmodPreemptionVerifyStatusInProgress},
    {"Succeeded", portmodPreemptionVerifyStatusSucceeded},
    {"Failed", portmodPreemptionVerifyStatusFailed},
    {NULL, 0}
};

enum_mapping_t portmod_preemption_force_rx_eop_mode_t_mapping[] = {
    {"SwRxEop", portmodPreemptionForceSwRxEop},
    {"AutoHwEop", portmodPreemptionForceAutoHwEop},
    {NULL, 0}
};

#ifdef CPRIMOD_SUPPORT
enum_mapping_t portmod_cpri_stage_t_mapping[] = {
    {"Rx", portmodCpriStageRx},
    {"Tx", portmodCpriStageTx},
    {NULL, 0}
};

#endif /* CPRIMOD_SUPPORT */
enum_mapping_t portmod_timestamp_mode_t_mapping[] = {
    {"32bit", portmodTimestampMode32bit},
    {"48bit", portmodTimestampMode48bit},
    {NULL, 0}
};

enum_mapping_t portmod_flr_timeout_t_mapping[] = {
    {"Invaild", portmodFlrTimeoutInvaild},
    {"50ms", portmodFlrTimeout50ms},
    {"75ms", portmodFlrTimeout75ms},
    {"100ms", portmodFlrTimeout100ms},
    {"150ms", portmodFlrTimeout150ms},
    {"250ms", portmodFlrTimeout250ms},
    {"500ms", portmodFlrTimeout500ms},
    {NULL, 0}
};

enum_mapping_t portmod_mac_rsv_fields_t_mapping[] = {
    {"WrongSaPkts", portmodMacRsvWrongSaPkts},
    {"StackVlanPkts", portmodMacRsvStackVlanPkts},
    {"UnsupportedPausePfcDaPkts", portmodMacRsvUnsupportedPausePfcDaPkts},
    {"RxCodeErrorPkts", portmodMacRsvRxCodeErrorPkts},
    {"CrcErrorPkts", portmodMacRsvCrcErrorPkts},
    {"LengthCheckFailPkts", portmodMacRsvLengthCheckFailPkts},
    {"TruncatedPkts", portmodMacRsvTruncatedPkts},
    {"GoodPkts", portmodMacRsvGoodPkts},
    {"MulticastPkts", portmodMacRsvMulticastPkts},
    {"BroadcastPkts", portmodMacRsvBroadcastPkts},
    {"PromiscuousPkts", portmodMacRsvPromiscuousPkts},
    {"ControlPkts", portmodMacRsvControlPkts},
    {"PausePkts", portmodMacRsvPausePkts},
    {"BadOpcodePkts", portmodMacRsvBadOpcodePkts},
    {"VlanTaggedPkts", portmodMacRsvVlanTaggedPkts},
    {"UnicastPkts", portmodMacRsvUnicastPkts},
    {"RxFifoFull", portmodMacRsvRxFifoFull},
    {"RuntPkts", portmodMacRsvRuntPkts},
    {"PfcPkts", portmodMacRsvPfcPkts},
    {"SchCrcError", portmodMacRsvSchCrcError},
    {"MacsecPkts", portmodMacRsvMacsecPkts},
    {"DribbleNibbleError", portmodMacRsvDribbleNibbleError},
    {NULL, 0}
};

enum_mapping_t portmod_mac_tx_crc_mode_t_mapping[] = {
    {"Append", portmodMacTxCrcModeAppend},
    {"Keep", portmodMacTxCrcModeKeep},
    {"Replace", portmodMacTxCrcModeReplace},
    {"Auto", portmodMacTxCrcModeAuto},
    {NULL, 0}
};

#endif /*PORTMOD_DIAG*/

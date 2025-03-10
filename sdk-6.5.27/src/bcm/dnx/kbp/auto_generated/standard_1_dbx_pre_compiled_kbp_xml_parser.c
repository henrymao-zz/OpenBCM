/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * This File is Auto-generated - DO NOT TOUCH IT!!!!
 */


#include <shared/utilex/utilex_str.h>
#include <soc/sand/shrextend/shrextend_debug.h>
#include <sal/core/libc.h>
#include <bcm_int/dnx/kbp/auto_generated/standard_1_dbx_pre_compiled_kbp_xml_parser.h>

#define _INTERNAL_AUTO_GENERATED_ARRAYS_MARKER
#define _INTERNAL_AUTO_GENERATED_FILE_SEARCH

/* *INDENT-OFF* */
_INTERNAL_AUTO_GENERATED_ARRAYS_MARKER

const char *jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_0="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!--\n\
    Aligned to Pemla. Arch version: #***\n\
    Auto-Generted - DO NOT EDIT!!!!\n\
-->\n\
\n\
<KbpOpcodesDbCatalogue xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"  xsi:noNamespaceSchemaLocation=\"../../kbp_opcodes_schema.xsd\">\n\
\n\
\n\
<Opcode Name=\"IPV4_MULTICAST_PRIVATE_W_UC_RPF\" OpCode=\"1\" Valid=\"elk.application.ipv4\" ValidForAdapter=\"1\">\n\
    <OneLineDescription>Master Key for MultiCast</OneLineDescription>\n\
    <Description>4 lookups:\n\
                         (1)Forward: (a){VRF,G,S,In_LIF} (b){VRF,G,In_LIF,S}\n\
                         (2)RPF (a){VRF,SIP} (b){SIP}!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <AppDB Name=\"KBP_IPV4_MULTICAST_TCAM_FORWARD\" ResultLocation=\"FWD\" Segments=\"1, 2, 3, 4\"/>\n\
    <AppDB Name=\"KBP_IPV4_UNICAST_PRIVATE_LPM_RPF\" ResultLocation=\"RPF\" Segments=\"1, 3\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"16\" Name=\"ZERO_PADDING\"/>\n\
        <Field Segment=\"1\" BitSize=\"16\" Name=\"VRF\"/>\n\
        <Field Segment=\"2\" BitSize=\"32\" Name=\"IPV4_DIP\"/>\n\
        <Field Segment=\"3\" BitSize=\"32\" Name=\"IPV4_SIP\"/>\n\
        <Field Segment=\"4\" BitSize=\"24\" Name=\"GLOBAL_IN_LIF\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"IPV4___MC_PRIVATE_WO_BF_WO_F2B\"/>\n\
        <Context Name=\"IPV4___MC_PRIVATE_WO_BF_W_F2B\"/>\n\
        <Context Name=\"IPV4___MC_PRIVATE_W_BF_W_F2B\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"IPV4_UNICAST_PRIVATE_W_UC_RPF\" OpCode=\"3\" Valid=\"elk.application.ipv4\" ValidForAdapter=\"1\">\n\
    <OneLineDescription>Master Key for Unicast IPv4</OneLineDescription>\n\
    <Description>4 lookups (1) Private and Public, (2) FWD and RFP, resulting in 2 results: FWD and RPF!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <AppDB Name=\"KBP_IPV4_UNICAST_PRIVATE_LPM_FORWARD\" ResultLocation=\"FWD\" Segments=\"0, 2\"/>\n\
    <AppDB Name=\"KBP_IPV4_UNICAST_PRIVATE_LPM_RPF\" ResultLocation=\"RPF\" Segments=\"0, 1\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"16\" Name=\"VRF\"/>\n\
        <Field Segment=\"1\" BitSize=\"32\" Name=\"IPV4_SIP\"/>\n\
        <Field Segment=\"2\" BitSize=\"32\" Name=\"IPV4_DIP\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"IPV4___PRIVATE_UC\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"IPV6_MULTICAST_PRIVATE_W_UC_RPF\" OpCode=\"2\" Valid=\"elk.application.ipv6\" ValidForAdapter=\"1\">\n\
    <OneLineDescription>Master Key for MultiCast</OneLineDescription>\n\
    <Description>4 lookups:\n\
                         (1)Forward: (a){VRF,G,S,In_LIF} (b){VRF,G,In_LIF,S}\n\
                         (2)RPF (a){VRF,SIP} (b){SIP}!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <AppDB Name=\"KBP_IPV6_MULTICAST_TCAM_FORWARD\" ResultLocation=\"FWD\" Segments=\"1, 5, 2, 3, 6\"/>\n\
    <AppDB Name=\"KBP_IPV6_UNICAST_PRIVATE_LPM_RPF\" ResultLocation=\"RPF\" Segments=\"1, 2\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"8\" Name=\"ZERO_PADDING_4\"/>\n\
        <Field Segment=\"1\" BitSize=\"16\" Name=\"VRF\"/>\n\
        <Field Segment=\"2\" BitSize=\"128\" Name=\"IPV6_SIP\"/>\n\
        <Field Segment=\"3\" BitSize=\"8\" Name=\"GLOBAL_IN_LIF_21_16\"/>\n\
        <Field Segment=\"4\" BitSize=\"16\" Name=\"ZERO_PADDING_3\"/>\n\
        <Field Segment=\"5\" BitSize=";

const char *jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_1="\"128\" Name=\"IPV6_DIP\"/>\n\
        <Field Segment=\"6\" BitSize=\"16\" Name=\"GLOBAL_IN_LIF_15_00\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"IPV6___MC_PRIVATE_WO_BF_WO_F2B\"/>\n\
        <Context Name=\"IPV6___MC_PRIVATE_WO_BF_W_F2B\"/>\n\
        <Context Name=\"IPV6___MC_PRIVATE_W_BF_W_F2B\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"IPV6_UNICAST_PRIVATE_W_UC_RPF\" OpCode=\"4\" Valid=\"elk.application.ipv6\" ValidForAdapter=\"1\">\n\
    <OneLineDescription>Master Key for Unicast IPv6</OneLineDescription>\n\
    <Description>4 lookups (1) Private and Public, (2) FWD and RFP, resulting in 2 results: FWD and RPF!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <AppDB Name=\"KBP_IPV6_UNICAST_PRIVATE_LPM_FORWARD\" ResultLocation=\"FWD\" Segments=\"1, 2\"/>\n\
    <AppDB Name=\"KBP_IPV6_UNICAST_PRIVATE_LPM_RPF\" ResultLocation=\"RPF\" Segments=\"1, 5\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"16\" Name=\"ZERO_PADDING\"/>\n\
        <Field Segment=\"1\" BitSize=\"16\" Name=\"VRF\"/>\n\
        <Field Segment=\"2\" BitSize=\"128\" Name=\"IPV6_DIP\"/>\n\
        <Field Segment=\"3\" BitSize=\"24\" Name=\"GLOBAL_IN_LIF\"/>\n\
        <Field Segment=\"4\" BitSize=\"8\" Name=\"ZERO_PADDING_2\"/>\n\
        <Field Segment=\"5\" BitSize=\"128\" Name=\"IPV6_SIP\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"IPV6___PRIVATE_UC\"/>\n\
        <Context Name=\"IPV6___PRIVATE_UC_BFD\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"NAT_MAPPING\" OpCode=\"7\" Valid=\"elk.application.nat\" ValidForAdapter=\"1\">\n\
    <OneLineDescription>Master Key for NAT mapping</OneLineDescription>\n\
    <Description>!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <AppDB Name=\"KBP_NAT_EXTERNAL_TO_INTERNAL\" ResultLocation=\"FWD\" Segments=\"0, 1, 4, 5\"/>\n\
    <AppDB Name=\"KBP_NAT_INTERNAL_TO_EXTERNAL\" ResultLocation=\"RPF\" Segments=\"0, 1, 2, 3\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"8\" Name=\"IP_PROTOCOL\"/>\n\
        <Field Segment=\"1\" BitSize=\"16\" Name=\"VRF\"/>\n\
        <Field Segment=\"2\" BitSize=\"32\" Name=\"IPV4_SIP\"/>\n\
        <Field Segment=\"3\" BitSize=\"16\" Name=\"L4_SRC_PORT\"/>\n\
        <Field Segment=\"4\" BitSize=\"32\" Name=\"IPV4_DIP\"/>\n\
        <Field Segment=\"5\" BitSize=\"16\" Name=\"L4_DST_PORT\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"IPV4___NAT_DOWNSTREAM\"/>\n\
        <Context Name=\"IPV4___NAT_UPSTREAM\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"NOP\" OpCode=\"16\" Valid=\"0\" ValidForAdapter=\"0\">\n\
    <OneLineDescription>NOP</OneLineDescription>\n\
    <Description>NOP!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <MasterKey/>\n\
    <FwdContexts>\n\
        <Context Name=\"BRIDGE___IPV4MC_SVL\"/>\n\
        <Context Name=\"GENERAL___NOP_CTX\"/>\n\
        <Context Name=\"IPV4___WO_FIB_LOOKUP\"/>\n\
        <Context Name=\"IPV6___WO_FIB_LOOKUP\"/>\n\
        <Context Name=\"MPLS___OAM_ONLY\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"SRV6_ENDPOINT_CLASSIC\" OpCode=\"12\" Valid=\"elk.application.ipv6\" ValidForAdapter=\"1\">\n\
    <OneLineDescription>Master Key for SRv6 Endpoint</OneLineDescription>\n\
    <Description>1 lookups (1) in IPv6!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appe";

const char *jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_2="ar as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <AppDB Name=\"KBP_IPV6_UNICAST_PRIVATE_LPM_FORWARD\" ResultLocation=\"FWD\" Segments=\"1, 2\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"16\" Name=\"ZERO_PADDING\"/>\n\
        <Field Segment=\"1\" BitSize=\"16\" Name=\"VRF\"/>\n\
        <Field Segment=\"2\" BitSize=\"128\" Name=\"IPV6_DIP\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"SRV6___CLASSIC_NOP_CTX\"/>\n\
        <Context Name=\"SRV6___PRIVATE_UC\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"SRV6_ENDPOINT_GSID\" OpCode=\"15\" Valid=\"elk.application.ipv6\" ValidForAdapter=\"1\">\n\
    <OneLineDescription>Master Key for SRv6 Endpoint GSID</OneLineDescription>\n\
    <Description>1 lookups (1) in IPv6!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <AppDB Name=\"KBP_IPV6_UNICAST_PRIVATE_LPM_FORWARD\" ResultLocation=\"FWD\" Segments=\"1, 2\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"16\" Name=\"ZERO_PADDING\"/>\n\
        <Field Segment=\"1\" BitSize=\"16\" Name=\"VRF\"/>\n\
        <Field Segment=\"2\" BitSize=\"128\" Name=\"IPV6_DIP\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"SRV6___GSID_64B_PREFIX_PRIVATE_UC\"/>\n\
        <Context Name=\"SRV6___GSID_NOP_CTX\"/>\n\
        <Context Name=\"SRV6___GSID_PRIVATE_UC\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"SRV6_ENDPOINT_USID\" OpCode=\"13\" Valid=\"elk.application.ipv6\" ValidForAdapter=\"1\">\n\
    <OneLineDescription>Master Key for SRv6 Endpoint uSID</OneLineDescription>\n\
    <Description>1 lookups (1) in IPv6!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <AppDB Name=\"KBP_IPV6_UNICAST_PRIVATE_LPM_FORWARD\" ResultLocation=\"FWD\" Segments=\"1, 2\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"16\" Name=\"ZERO_PADDING\"/>\n\
        <Field Segment=\"1\" BitSize=\"16\" Name=\"VRF\"/>\n\
        <Field Segment=\"2\" BitSize=\"128\" Name=\"IPV6_DIP\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"SRV6___USID_48B_PREFIX_PRIVATE_UC\"/>\n\
        <Context Name=\"SRV6___USID_NOP_CTX\"/>\n\
        <Context Name=\"SRV6___USID_PRIVATE_UC\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"TUNNELED_NAT_MAPPING\" OpCode=\"19\" Valid=\"elk.application.nat\" ValidForAdapter=\"1\">\n\
    <OneLineDescription>Master Key for Tunneled NAT mapping</OneLineDescription>\n\
    <Description>!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <AppDB Name=\"KBP_TUNNELED_NAT\" ResultLocation=\"FWD\" Segments=\"0, 1\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"24\" Name=\"GLOBAL_IN_LIF\"/>\n\
        <Field Segment=\"1\" BitSize=\"16\" Name=\"L4_PORT\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"IPV4___TUNNELED_DST_NAT\"/>\n\
        <Context Name=\"IPV4___TUNNELED_SRC_NAT\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"VIRTUAL_IPV4_PRIVATE_UC\" OpCode=\"8\" Valid=\"elk.application.sllb\" ValidForAdapter=\"1\">\n\
    <OneLineDescription/>\n\
    <Description>1 lookups (1) in KBP_PCC_STATE!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>";

const char *jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_3="\n\
    <AppDB Name=\"KBP_PCC_STATE_TABLE\" ResultLocation=\"FWD\" Segments=\"0, 1\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"16\" Name=\"VIP_ID\"/>\n\
        <Field Segment=\"1\" BitSize=\"32\" Name=\"SIGNATURE\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"SLLB___VIRTUAL_IPV4_ROUTE\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
\n\
<Opcode Name=\"VIRTUAL_IPV6_PRIVATE_UC\" OpCode=\"9\" Valid=\"elk.application.sllb\" ValidForAdapter=\"1\">\n\
    <OneLineDescription>Master Key for PCC_STATE</OneLineDescription>\n\
    <Description>1 lookups (1) in KBP_PCC_STATE!!!!Note!!!!\n\
    this is a not a real AppDB\n\
    this is KBP-Command (Master Key)\n\
    it is appear as AppDB in the device PP for the sake of completeness when transferring information to the SDK\n\
!!!!\n\
</Description>\n\
    <AppDB Name=\"KBP_PCC_STATE_TABLE\" ResultLocation=\"FWD\" Segments=\"0, 1\"/>\n\
    <MasterKey>\n\
        <Field Segment=\"0\" BitSize=\"16\" Name=\"VIP_ID\"/>\n\
        <Field Segment=\"1\" BitSize=\"32\" Name=\"SIGNATURE\"/>\n\
    </MasterKey>\n\
    <FwdContexts>\n\
        <Context Name=\"SLLB___VIRTUAL_IPV6_ROUTE\"/>\n\
    </FwdContexts>\n\
</Opcode>\n\
\n\
</KbpOpcodesDbCatalogue>\n\
";
_INTERNAL_AUTO_GENERATED_ARRAYS_MARKER

shr_error_e
pre_compiled_kbp_standard_1_xml_to_buf(
    char *filePath,
    char **buf,
    long int * size_p)
{
    char *file_buf;
    long int _internal_size_p;
    long int offset;

    SHR_FUNC_INIT_VARS(NO_UNIT);
    
    *size_p = 0;

    _INTERNAL_AUTO_GENERATED_FILE_SEARCH

    if(!sal_strncmp("jericho2_a0/kbp/auto_generated/standard_1/standard_1_kbp_opcodes_definition.xml", filePath, RHFILE_MAX_SIZE))
    {
        _internal_size_p = 0;
        _internal_size_p += sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_0, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE);
        _internal_size_p += sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_1, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE);
        _internal_size_p += sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_2, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE);
        _internal_size_p += sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_3, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE);

        *size_p = _internal_size_p;
        offset = 0;
        file_buf = sal_alloc(*size_p, "buf");

        sal_strncpy(file_buf, jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_0, sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_0, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE));

        offset += sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_0, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE);
        sal_strncpy(file_buf + offset, jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_1, sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_1, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE));

        offset += sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_1, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE);
        sal_strncpy(file_buf + offset, jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_2, sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_2, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE));

        offset += sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_2, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE);
        sal_strncpy(file_buf + offset, jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_3, sal_strnlen(jericho2_a0_kbp_auto_generated_standard_1_standard_1_kbp_opcodes_definition_3, STANDARD_1_KBP_PRE_COMPILED_STRING_MAX_SIZE));


        *buf = file_buf;
        SHR_EXIT();
    }
    _INTERNAL_AUTO_GENERATED_FILE_SEARCH
    
    SHR_SET_CURRENT_ERR(_SHR_E_EXISTS);
    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}


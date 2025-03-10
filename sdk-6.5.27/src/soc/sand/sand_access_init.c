

/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#include <shared/bsl.h>
#define BSL_LOG_MODULE BSL_LS_SOC_INIT
#include <soc/sand/shrextend/shrextend_debug.h>

#include <soc/drv.h>
#ifdef BCM_DNX_SUPPORT
#include <soc/dnx/dnx_data/auto_generated/dnx_data_device.h>
#endif
#ifdef BCM_DNXF_SUPPORT
#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_device.h>
#endif
#ifdef BCM_DPP_SUPPORT
#include <soc/dpp/drv.h>
#endif


#define SAND_SINGLE_BLOCK_CASE(uc_block_name, lc_block_name) \
            case SOC_BLK_##uc_block_name: \
                si->lc_block_name##_block = blk; \
                break;


#define SAND_CORE_BROADCAST_BLOCK_CASE(uc_block_name, lc_block_name) \
            case SOC_BLK_BRDC_##uc_block_name: \
                si->brdc_##lc_block_name##_block = blk; \
                si->broadcast_blocks[blk] = si->lc_block_name##_blocks; \
                si->broadcast_blocks_size[blk] = nof_cores_to_broadcast; \
                break;


#define SAND_MULTI_BLOCK_CASE(uc_block_name, lc_block_name) \
            case SOC_BLK_##uc_block_name: \
                if (blknum >= SOC_MAX_NUM_##uc_block_name##_BLKS) { \
                    SHR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "soc_sand_info_config_blocks: too many " #uc_block_name " blocks %s%s%s\n", EMPTY, EMPTY, EMPTY); \
                } \
                si->lc_block_name##_block[blknum] = blk; \
                si->block_port[blk] = blknum | SOC_REG_ADDR_INSTANCE_MASK; \
                break;


#define SAND_MULTIS_BLOCK_CASE(uc_block_name, lc_block_name) \
            case SOC_BLK_##uc_block_name: \
                if (blknum >= SOC_MAX_NUM_##uc_block_name##_BLKS) { \
                    SHR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "soc_sand_info_config_blocks: too many " #uc_block_name " blocks %s%s%s\n", EMPTY, EMPTY, EMPTY); \
                } \
                si->lc_block_name##_blocks[blknum] = blk; \
                si->block_port[blk] = blknum | SOC_REG_ADDR_INSTANCE_MASK; \
                break;

#define SAND_PTYPE_SET(ptype) \
    si->ptype.min = si->ptype.max = -1; \
    si->ptype.num = 0;


int soc_sand_info_config_blocks(
    int unit,
    uint8 nof_cores_to_broadcast)
{
    soc_info_t  *si;
    soc_invalid_block_instances_t *invalid_instances = SOC_DRIVER(unit)->invalid_block_instances;
    int         blk, blktype, blknum;
    char        instance_string[3];

    SHR_FUNC_INIT_VARS(NO_UNIT);

    si = &SOC_INFO(unit);

    sal_memset(si->has_block, 0, sizeof(soc_block_t) * COUNTOF(si->has_block));
    sal_memset(si->broadcast_blocks, 0, sizeof(si->broadcast_blocks));
    sal_memset(si->broadcast_blocks_size, 0, sizeof(si->broadcast_blocks_size));

    for (blk = 0; blk < SOC_MAX_NUM_BLKS; blk++) {
        si->block_port[blk] = REG_PORT_ANY;
        si->block_valid[blk] = 0;
    }

    SAND_PTYPE_SET(fe)
    SAND_PTYPE_SET(ge)
    SAND_PTYPE_SET(ce)
    SAND_PTYPE_SET(cde)
    SAND_PTYPE_SET(d3c)
    SAND_PTYPE_SET(xe)
    SAND_PTYPE_SET(le)
    SAND_PTYPE_SET(cc)
    SAND_PTYPE_SET(hg)
    SAND_PTYPE_SET(il)
    SAND_PTYPE_SET(fe)
    SAND_PTYPE_SET(qsgmii)
    SAND_PTYPE_SET(cl)
    SAND_PTYPE_SET(clg2)
    SAND_PTYPE_SET(sfi)
    SAND_PTYPE_SET(sci)
    SAND_PTYPE_SET(port)
    SAND_PTYPE_SET(ether)
    SAND_PTYPE_SET(all)
    SAND_PTYPE_SET(pp)
    SAND_PTYPE_SET(flexe_client)
    SAND_PTYPE_SET(flexe_mac)
    SAND_PTYPE_SET(flexe_sar)
    SAND_PTYPE_SET(flexe_phy)
    SAND_PTYPE_SET(otn)

    si->cmic_block = -1;
    si->iproc_block = -1;
    for (blk = 0; blk < SOC_MAX_NUM_OTPC_BLKS; blk++) {
        si->otpc_block[blk] = -1;
    }

    
    for (blk = 0; SOC_BLOCK_INFO(unit, blk).type >= 0; blk++) {
        blktype = SOC_BLOCK_INFO(unit, blk).type;
        switch (blktype)
        {
            case SOC_BLK_CGM:
                if (SOC_IS_DNX(unit)) {
                    si->brdc_cgm_block = SOC_CORE_ALL;
                } else {
                    si->brdc_cgm_block = blk;
                }
                break;
            case SOC_BLK_EGQ:
                si->brdc_egq_block = blk;
                break;
            case SOC_BLK_EPNI:
                if (SOC_IS_DNX(unit)) {
                    si->brdc_epni_block = SOC_CORE_ALL;
                } else {
                    si->brdc_epni_block = blk;
                }
                break;
            case SOC_BLK_IHB:
                si->brdc_ihb_block = blk;
                break;
            case SOC_BLK_IHP:
                si->brdc_ihp_block = blk;
                break;
            case SOC_BLK_IPS:
                if (SOC_IS_DNX(unit)) {
                    si->brdc_ips_block = SOC_CORE_ALL;
                } else {
                    si->brdc_ips_block = blk;
                }
                break;
            case SOC_BLK_IQM:
                if (SOC_IS_DNX(unit)) {
                    si->brdc_iqm_block = SOC_CORE_ALL;
                } else {
                    si->brdc_iqm_block = blk;
                }
                break;
            case SOC_BLK_SCH:
                if (SOC_IS_DNX(unit)) {
                    si->brdc_sch_block = SOC_CORE_ALL;
                } else {
                    si->brdc_sch_block = blk;
                }
                break;
            case SOC_BLK_KAPS_BBS:
                si->brdc_kaps_bbs_block = blk;
                break;
            case SOC_BLK_MRPS:
                si->brdc_mrps_block = SOC_CORE_ALL;
                break;
            case SOC_BLK_FMAC:
                si->brdc_fmac_block[0] = blk;
                break;
            case SOC_BLK_HBC:
                si->brdc_hbc_block[0] = blk;
                break;
            case SOC_BLK_FSRD:
                si->brdc_fsrd_block[0] = blk;
                break;
            case SOC_BLK_BRDC_MTRPS_EM:
                si->brdc_mtrps_em_block = blk;
                break;
        }
    }

    for (blk = 0; SOC_BLOCK_INFO(unit, blk).type >= 0; blk++) {
        blktype = SOC_BLOCK_INFO(unit, blk).type;
        blknum = SOC_BLOCK_INFO(unit, blk).number;
        if (blknum < 0) {
            SHR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "soc_sand_info_config_blocks: illegal block instance number %d %s%s\n", blknum, EMPTY, EMPTY);
        }

        if (blk >= SOC_MAX_NUM_BLKS) {
            SHR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "soc_sand_info_config_blocks: too many blocks for device %s%s%s\n",EMPTY, EMPTY, EMPTY);
        }

        si->has_block[blk] = blktype;
        sal_snprintf(instance_string, sizeof(instance_string), "%d", blknum);

        si->block_valid[blk] = 1;

        switch (blktype)
        {
            SAND_MULTI_BLOCK_CASE(CFC, cfc)
            SAND_MULTIS_BLOCK_CASE(OCB, ocb)
            SAND_MULTIS_BLOCK_CASE(CRPS, crps)
            SAND_MULTIS_BLOCK_CASE(EPRE, epre)
            SAND_MULTIS_BLOCK_CASE(IPPF, ippf)
            SAND_SINGLE_BLOCK_CASE(MDB_ARM, mdb_arm)
            SAND_MULTI_BLOCK_CASE(CDPORT, cdport)
            SAND_MULTI_BLOCK_CASE(CDMAC, cdmac)
            SAND_MULTIS_BLOCK_CASE(FDTL, fdtl)
            SAND_SINGLE_BLOCK_CASE(ECI, eci)
            SAND_MULTIS_BLOCK_CASE(EGQ, egq)
            SAND_SINGLE_BLOCK_CASE(CMIC, cmic)
            SAND_SINGLE_BLOCK_CASE(IPROC, iproc)
            SAND_SINGLE_BLOCK_CASE(NANOSYNC, nanosync)
            SAND_MULTI_BLOCK_CASE(IDI, idi)
            SAND_SINGLE_BLOCK_CASE(FCR, fcr)
            SAND_SINGLE_BLOCK_CASE(FCT, fct)
            SAND_SINGLE_BLOCK_CASE(MMU, mmu)
            SAND_MULTIS_BLOCK_CASE(FDR, fdr)
            SAND_MULTI_BLOCK_CASE(FDA, fda)
            SAND_MULTI_BLOCK_CASE(FDT, fdt)
            SAND_SINGLE_BLOCK_CASE(MESH_TOPOLOGY, mesh_topology)
            SAND_SINGLE_BLOCK_CASE(IDR, idr)
            SAND_MULTIS_BLOCK_CASE(IHB, ihb)
            SAND_MULTIS_BLOCK_CASE(IHP, ihp)
            SAND_MULTIS_BLOCK_CASE(IPS, ips)
            SAND_MULTIS_BLOCK_CASE(IPT, ipt)
            SAND_MULTIS_BLOCK_CASE(IQM, iqm)
            SAND_MULTIS_BLOCK_CASE(IRE, ire)
            SAND_SINGLE_BLOCK_CASE(IRR, irr)
            case SOC_BLK_OTPC:
                si->otpc_block[blknum] = blk;
                break;
            SAND_MULTI_BLOCK_CASE(XLP, xlp)
            SAND_MULTI_BLOCK_CASE(CLP, clp)
            SAND_MULTI_BLOCK_CASE(GPORT, gport)
            SAND_MULTI_BLOCK_CASE(PMQ, pmq)
            SAND_SINGLE_BLOCK_CASE(NBI, nbi)
            SAND_MULTIS_BLOCK_CASE(CGM, cgm)
            SAND_SINGLE_BLOCK_CASE(OAMP, oamp)
            SAND_MULTI_BLOCK_CASE(OLP, olp)
            SAND_MULTIS_BLOCK_CASE(RTP, rtp)
            SAND_MULTIS_BLOCK_CASE(SCH, sch)
            SAND_MULTIS_BLOCK_CASE(EPNI, epni)
            SAND_MULTIS_BLOCK_CASE(MRPS, mrps)
            SAND_MULTI_BLOCK_CASE(FMAC, fmac)
            SAND_MULTI_BLOCK_CASE(FSRD, fsrd)
            SAND_MULTIS_BLOCK_CASE(MTRPS_EM, mtrps_em)
            SAND_MULTIS_BLOCK_CASE(EDB, edb)
            SAND_SINGLE_BLOCK_CASE(ILKN_PMH, ilkn_pmh)
            SAND_SINGLE_BLOCK_CASE(IPST, ipst)
            SAND_MULTI_BLOCK_CASE(ILKN_PML, ilkn_pml)
            SAND_SINGLE_BLOCK_CASE(IQMT, iqmt)
            SAND_MULTIS_BLOCK_CASE(KAPS, kaps)
            SAND_SINGLE_BLOCK_CASE(ILB, ilb)
            SAND_SINGLE_BLOCK_CASE(IEP, iep)
            SAND_SINGLE_BLOCK_CASE(IMP, imp)
            SAND_MULTIS_BLOCK_CASE(SPB, spb)
            SAND_SINGLE_BLOCK_CASE(ITE, ite)
            SAND_MULTIS_BLOCK_CASE(DDP, ddp)
            SAND_SINGLE_BLOCK_CASE(TXQ, txq)
            SAND_MULTI_BLOCK_CASE(TAR, tar)
            SAND_SINGLE_BLOCK_CASE(PTS, pts)
            SAND_MULTIS_BLOCK_CASE(SQM, sqm)
            SAND_MULTIS_BLOCK_CASE(IPSEC_SPU_WRAPPER_TOP, ipsec_spu_wrapper_top)
            SAND_MULTIS_BLOCK_CASE(KAPS_BBS, kaps_bbs)
            SAND_SINGLE_BLOCK_CASE(IPSEC, ipsec)
            SAND_MULTIS_BLOCK_CASE(DQM, dqm)
            SAND_MULTIS_BLOCK_CASE(ECGM, ecgm)
            SAND_SINGLE_BLOCK_CASE(IDB, idb)
            SAND_MULTIS_BLOCK_CASE(PEM, pem)
            SAND_SINGLE_BLOCK_CASE(PPDB_A, ppdb_a)
            SAND_SINGLE_BLOCK_CASE(PPDB_B, ppdb_b)
            SAND_MULTI_BLOCK_CASE(NBIL, nbil)
            SAND_SINGLE_BLOCK_CASE(NBIH, nbih)
            SAND_SINGLE_BLOCK_CASE(DRCA, drca)
            SAND_SINGLE_BLOCK_CASE(DRCB, drcb)
            SAND_SINGLE_BLOCK_CASE(DRCC, drcc)
            SAND_SINGLE_BLOCK_CASE(DRCD, drcd)
            SAND_SINGLE_BLOCK_CASE(DRCE, drce)
            SAND_SINGLE_BLOCK_CASE(DRCF, drcf)
            SAND_SINGLE_BLOCK_CASE(DRCG, drcg)
            SAND_SINGLE_BLOCK_CASE(DRCH, drch)
            SAND_SINGLE_BLOCK_CASE(DRCBROADCAST, drcbroadcast)
            SAND_CORE_BROADCAST_BLOCK_CASE(CGM, cgm)
            SAND_CORE_BROADCAST_BLOCK_CASE(EGQ, egq)
            SAND_CORE_BROADCAST_BLOCK_CASE(EPNI, epni)
            SAND_CORE_BROADCAST_BLOCK_CASE(IHB, ihb)
            SAND_CORE_BROADCAST_BLOCK_CASE(IHP, ihp)
            SAND_CORE_BROADCAST_BLOCK_CASE(IPS, ips)
            SAND_CORE_BROADCAST_BLOCK_CASE(IQM, iqm)
            SAND_CORE_BROADCAST_BLOCK_CASE(SCH, sch)
            case SOC_BLK_BRDC_KAPS_BBS:
                si->brdc_kaps_bbs_block = blk;
                si->broadcast_blocks[blk] = si->kaps_bbs_blocks;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_KAPS_BBS_BLKS;
                break;
            case SOC_BLK_BRDC_MRPS:
                si->brdc_mrps_block = blk;
                si->broadcast_blocks[blk] = si->mrps_blocks;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_MRPS_BLKS;
                break;
            case SOC_BLK_BRDC_FMAC:
                if (blknum >= SOC_MAX_NUM_BRDC_FMAC_BLKS) {
                    SHR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "soc_sand_info_config_blocks: too many BRDC_FMAC blocks %s%s%s\n", EMPTY, EMPTY, EMPTY);
                }
                si->brdc_fmac_block[blknum] = blk;
                si->block_port[blk] = blknum | SOC_REG_ADDR_INSTANCE_MASK;
                si->broadcast_blocks[blk] = si->fmac_block;
                if (SOC_IS_DNX(unit)) {
                    if(SOC_IS_J2C(unit))
                    {
                        si->broadcast_blocks_size[blk] = 12;
                    }
                    else if (SOC_IS_J2P(unit))
                    {
                        si->broadcast_blocks_size[blk] = 48;
                    }
                    else if (SOC_IS_J2X(unit))
                    {
                        si->broadcast_blocks_size[blk] = 16;
                    }
                    else
                    {
                        si->broadcast_blocks_size[blk] = 28;
                    }
                } else {
                    si->broadcast_blocks_size[blk] = SOC_MAX_NUM_FMAC_BLKS;
                }
                break;
            case SOC_BLK_BRDC_HBC:
                if (blknum >= SOC_MAX_NUM_BRDC_HBC_BLKS) {
                    SHR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "soc_sand_info_config_blocks: too many BRDC_HBC blocks %s%s%s\n", EMPTY, EMPTY, EMPTY);
                }
                si->brdc_hbc_block[blknum] = blk;
                si->block_port[blk] = blknum | SOC_REG_ADDR_INSTANCE_MASK;
                si->broadcast_blocks[blk] = si->hbc_block;

                if(SOC_IS_J2C(unit) || SOC_IS_J2X(unit))
                {
                    si->broadcast_blocks_size[blk] = 8;
                }
                else
                {
                    si->broadcast_blocks_size[blk] = SOC_MAX_NUM_HBC_BLKS;
                }
                break;
            case SOC_BLK_BRDC_FSRD:
                if (blknum >= SOC_MAX_NUM_BRDC_FSRD_BLKS) {
                    SHR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "soc_sand_info_config_blocks: too many BRDC_FSRD blocks %s%s%s\n", EMPTY, EMPTY, EMPTY);
                }
                si->brdc_fsrd_block[blknum] = blk;
                si->block_port[blk] = blknum | SOC_REG_ADDR_INSTANCE_MASK;
                si->broadcast_blocks[blk] = si->fsrd_block;
                if (SOC_IS_DNX(unit)) {
                    if(SOC_IS_J2C(unit))
                    {
                        si->broadcast_blocks_size[blk] = 6;
                    }
                    else if (SOC_IS_J2P(unit))
                    {
                        si->broadcast_blocks_size[blk] = 24;
                    }
                    else if (SOC_IS_J2X(unit))
                    {
                        si->broadcast_blocks_size[blk] = 8;
                    }
                    else
                    {
                        si->broadcast_blocks_size[blk] = 14;
                    }
                } else {
                    si->broadcast_blocks_size[blk] = SOC_MAX_NUM_FSRD_BLKS;
                }
                break;
            case SOC_BLK_BRDC_MTRPS_EM:
                si->brdc_mtrps_em_block = blk;
                si->broadcast_blocks[blk] = si->mtrps_em_blocks;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_MTRPS_EM_BLKS;
                break;
            case SOC_BLK_BRDC_IPSEC_SPU_WRAPPER_TOP:
                si->brdc_ipsec_spu_wrapper_top_block = blk;
                si->broadcast_blocks[blk] = si->ipsec_spu_wrapper_top_blocks;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_IPSEC_SPU_WRAPPER_TOP_BLKS;
                break;
            case SOC_BLK_BRDC_DCH:
                si->brdc_dch_block = blk;
                si->broadcast_blocks[blk] = si->dch_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DCH_BLKS;
                break;
            case SOC_BLK_BRDC_CCH:
                si->brdc_cch_block = blk;
                si->broadcast_blocks[blk] = si->cch_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_CCH_BLKS;
                break;
            case SOC_BLK_BRDC_DCML:
                si->brdc_dcml_block = blk;
                si->broadcast_blocks[blk] = si->dcml_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DCML_BLKS;
                break;
            case SOC_BLK_BRDC_LCM:
                si->brdc_lcm_block = blk;
                si->broadcast_blocks[blk] = si->lcm_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_LCM_BLKS;
                break;
            case SOC_BLK_BRDC_CCML:
                si->brdc_ccml_block = blk;
                si->broadcast_blocks[blk] = si->ccml_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_CCML_BLKS;
                break;
            case SOC_BLK_BRDC_DFL:
                si->brdc_dfl_block = blk;
                si->broadcast_blocks[blk] = si->dfl_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DFL_BLKS;
                break;
            case SOC_BLK_BRDC_DFL_FBC:
                si->brdc_dfl_fbc_block = blk;
                si->broadcast_blocks[blk] = si->dfl_fbc_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DFL_FBC_BLKS;
                break;
            case SOC_BLK_BRDC_CCH_VD0:
                si->brdc_cch_vd0_block = blk;
                si->broadcast_blocks[blk] = si->cch_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_CCH_BLKS;
                break;
            case SOC_BLK_BRDC_CCH_VD1:
                si->brdc_cch_vd1_block = blk;
                si->broadcast_blocks[blk] = si->cch_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_CCH_BLKS;
                break;
            case SOC_BLK_BRDC_CCML_VD0:
                si->brdc_ccml_vd0_block = blk;
                si->broadcast_blocks[blk] = si->ccml_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_CCML_BLKS;
                break;
            case SOC_BLK_BRDC_CCML_VD1:
                si->brdc_ccml_vd1_block = blk;
                si->broadcast_blocks[blk] = si->ccml_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_CCML_BLKS;
                break;
            case SOC_BLK_BRDC_DCH_VD0:
                si->brdc_dch_vd0_block = blk;
                si->broadcast_blocks[blk] = si->dch_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DCH_BLKS;
                break;
            case SOC_BLK_BRDC_DCH_VD1:
                si->brdc_dch_vd1_block = blk;
                si->broadcast_blocks[blk] = si->dch_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DCH_BLKS;
                break;
            case SOC_BLK_BRDC_DFL_FBC_VD0:
                si->brdc_dfl_fbc_vd0_block = blk;
                si->broadcast_blocks[blk] = si->dfl_fbc_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DFL_FBC_BLKS;
                break;
            case SOC_BLK_BRDC_DFL_FBC_VD1:
                si->brdc_dfl_fbc_vd1_block = blk;
                si->broadcast_blocks[blk] = si->dfl_fbc_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DFL_FBC_BLKS;
                break;
            case SOC_BLK_BRDC_DFL_VD0:
                si->brdc_dfl_vd0_block = blk;
                si->broadcast_blocks[blk] = si->dfl_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DFL_BLKS;
                break;
            case SOC_BLK_BRDC_DFL_VD1:
                si->brdc_dfl_vd1_block = blk;
                si->broadcast_blocks[blk] = si->dfl_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DFL_BLKS;
                break;
            case SOC_BLK_BRDC_DTL_VD0:
                si->brdc_dtl_vd0_block = blk;
                si->broadcast_blocks[blk] = si->dtl_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DTL_BLKS;
                break;
            case SOC_BLK_BRDC_DTL_VD1:
                si->brdc_dtl_vd1_block = blk;
                si->broadcast_blocks[blk] = si->dtl_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DTL_BLKS;
                break;
            case SOC_BLK_BRDC_DTM_VD0:
                si->brdc_dtm_vd0_block = blk;
                si->broadcast_blocks[blk] = si->dtm_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DTM_BLKS;
                break;
            case SOC_BLK_BRDC_DTM_VD1:
                si->brdc_dtm_vd1_block = blk;
                si->broadcast_blocks[blk] = si->dtm_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DTM_BLKS;
                break;
            case SOC_BLK_BRDC_FSRD_HIGH:
                si->brdc_fsrd_high_block = blk;
                si->broadcast_blocks[blk] = si->fsrd_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_FSRD_BLKS;
                break;
            case SOC_BLK_BRDC_FMAC_HIGH:
                si->brdc_fmac_high_block = blk;
                si->broadcast_blocks[blk] = si->fmac_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_FMAC_BLKS;
                break;
            case SOC_BLK_BRDC_FMAC_HIGH_VD0:
                si->brdc_fmac_high_block_vd0 = blk;
                si->broadcast_blocks[blk] = si->fmac_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_FMAC_BLKS;
                break;
            case SOC_BLK_BRDC_FMAC_HIGH_VD1:
                si->brdc_fmac_high_block_vd1 = blk;
                si->broadcast_blocks[blk] = si->fmac_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_FMAC_BLKS;
                break;
            case SOC_BLK_BRDC_FSRD_LOW:
                si->brdc_fsrd_low_block = blk;
                si->broadcast_blocks[blk] = si->fsrd_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_FSRD_BLKS;
                break;
            case SOC_BLK_BRDC_FMAC_LOW:
                si->brdc_fmac_low_block = blk;
                si->broadcast_blocks[blk] = si->fmac_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_FMAC_BLKS;
                break;
            case SOC_BLK_BRDC_FMAC_LOW_VD0:
                si->brdc_fmac_low_block_vd0 = blk;
                si->broadcast_blocks[blk] = si->fmac_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_FMAC_BLKS;
                break;
            case SOC_BLK_BRDC_FMAC_LOW_VD1:
                si->brdc_fmac_low_block_vd1 = blk;
                si->broadcast_blocks[blk] = si->fmac_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_FMAC_BLKS;
                break;
            case SOC_BLK_BRDC_LCM_VD0:
                si->brdc_lcm_vd0_block = blk;
                si->broadcast_blocks[blk] = si->lcm_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_LCM_BLKS;
                break;
            case SOC_BLK_BRDC_LCM_VD1:
                si->brdc_lcm_vd1_block = blk;
                si->broadcast_blocks[blk] = si->lcm_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_LCM_BLKS;
                break;
            case SOC_BLK_BRDC_QRH_VD0:
                si->brdc_qrh_vd0_block = blk;
                si->broadcast_blocks[blk] = si->qrh_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_QRH_BLKS;
                break;
            case SOC_BLK_BRDC_QRH_VD1:
                si->brdc_qrh_vd1_block = blk;
                si->broadcast_blocks[blk] = si->qrh_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_QRH_BLKS;
                break;
            case SOC_BLK_BRDC_DTL:
                si->brdc_dtl_block = blk;
                si->broadcast_blocks[blk] = si->dtl_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DTL_BLKS;
                break;
            case SOC_BLK_BRDC_DTM:
                si->brdc_dtm_block = blk;
                si->broadcast_blocks[blk] = si->dtm_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_DTM_BLKS;
                break;
            case SOC_BLK_BRDC_RTP:
                si->brdc_rtp_block = blk;
                break;
            case SOC_BLK_BRDC_MCT:
                si->brdc_mct_block = blk;
                break;
            case SOC_BLK_BRDC_QRH:
                si->brdc_qrh_block = blk;
                si->broadcast_blocks[blk] = si->qrh_block;
                si->broadcast_blocks_size[blk] = SOC_MAX_NUM_QRH_BLKS;
                break;
            SAND_SINGLE_BLOCK_CASE(PRM, prm)
            SAND_MULTI_BLOCK_CASE(BLH, blh)
            SAND_SINGLE_BLOCK_CASE(AM_TOP, am_top)
            SAND_MULTI_BLOCK_CASE(MXQ, mxq)
            SAND_SINGLE_BLOCK_CASE(PLL, pll)
            SAND_SINGLE_BLOCK_CASE(NIF, nif)

            
            SAND_MULTI_BLOCK_CASE(CLPORT, clport)

            
            SAND_MULTIS_BLOCK_CASE(DCC, dcc)
            SAND_MULTIS_BLOCK_CASE(DPC, dpc)
            SAND_SINGLE_BLOCK_CASE(FASIC, fasic)
            SAND_SINGLE_BLOCK_CASE(FEU, feu)
            SAND_SINGLE_BLOCK_CASE(FLEXEWP, flexewp)
            SAND_SINGLE_BLOCK_CASE(FPRD, fprd)
            SAND_SINGLE_BLOCK_CASE(FSAR, fsar)
            SAND_SINGLE_BLOCK_CASE(FSCL, fscl)

            
            SAND_MULTIS_BLOCK_CASE(BDM, bdm)
            SAND_MULTI_BLOCK_CASE(CDU, cdu)
            SAND_MULTIS_BLOCK_CASE(CDUM, cdum)
            SAND_MULTI_BLOCK_CASE(DDHA, ddha)
            SAND_MULTI_BLOCK_CASE(DDHB, ddhb)
            SAND_MULTI_BLOCK_CASE(DHC, dhc)
            SAND_MULTI_BLOCK_CASE(DMU, dmu)
            SAND_MULTIS_BLOCK_CASE(EPS, eps)
            SAND_MULTIS_BLOCK_CASE(ERPP, erpp)
            SAND_MULTIS_BLOCK_CASE(ETPPA, etppa)
            SAND_MULTIS_BLOCK_CASE(ETPPB, etppb)
            SAND_MULTIS_BLOCK_CASE(ETPPC, etppc)
            SAND_MULTI_BLOCK_CASE(EVNT, evnt)
            SAND_MULTIS_BLOCK_CASE(FQP, fqp)
            SAND_MULTI_BLOCK_CASE(HBC, hbc)
            SAND_MULTI_BLOCK_CASE(HBM, hbm)
            SAND_MULTI_BLOCK_CASE(HBMC, hbmc)
            SAND_MULTIS_BLOCK_CASE(ILE, ile)
            SAND_SINGLE_BLOCK_CASE(ILKN, ilkn)
            SAND_MULTIS_BLOCK_CASE(CLU, clu)
            SAND_MULTIS_BLOCK_CASE(CLUP, clup)
            SAND_MULTIS_BLOCK_CASE(CDB, cdb)
            SAND_MULTIS_BLOCK_CASE(CDBM, cdbm)
            SAND_MULTIS_BLOCK_CASE(CDPM, cdpm)
            SAND_MULTIS_BLOCK_CASE(OCBM, ocbm)
            SAND_MULTIS_BLOCK_CASE(MSD, msd)
            SAND_MULTIS_BLOCK_CASE(MSS, mss)
            SAND_MULTIS_BLOCK_CASE(MACSEC, macsec)
            SAND_MULTIS_BLOCK_CASE(HRC, hrc)
            SAND_MULTIS_BLOCK_CASE(CLMAC, clmac)
            SAND_MULTIS_BLOCK_CASE(ESB, esb)
            SAND_MULTI_BLOCK_CASE(ILU, ilu)
            SAND_MULTIS_BLOCK_CASE(IPPA, ippa)
            SAND_MULTIS_BLOCK_CASE(IPPB, ippb)
            SAND_MULTIS_BLOCK_CASE(IPPC, ippc)
            SAND_MULTIS_BLOCK_CASE(IPPD, ippd)
            SAND_MULTIS_BLOCK_CASE(IPPE, ippe)
            SAND_MULTIS_BLOCK_CASE(ITPP, itpp)
            SAND_MULTIS_BLOCK_CASE(ITPPD, itppd)
            SAND_MULTI_BLOCK_CASE(MACT, mact)
            SAND_MULTIS_BLOCK_CASE(MCP, mcp)
            SAND_SINGLE_BLOCK_CASE(MDB, mdb)
            SAND_MULTI_BLOCK_CASE(MTM, mtm)
            SAND_MULTIS_BLOCK_CASE(NMG, nmg)
            SAND_MULTIS_BLOCK_CASE(PDM, pdm)
            SAND_MULTIS_BLOCK_CASE(PQP, pqp)
            SAND_MULTIS_BLOCK_CASE(RQP, rqp)
            SAND_MULTIS_BLOCK_CASE(SIF, sif)
            SAND_MULTIS_BLOCK_CASE(TCAM, tcam)
            SAND_MULTIS_BLOCK_CASE(TDU, tdu)
            SAND_MULTIS_BLOCK_CASE(ALIGNER, aligner)
            SAND_MULTIS_BLOCK_CASE(MSU, msu)
            SAND_MULTIS_BLOCK_CASE(PMU, pmu)
            SAND_MULTIS_BLOCK_CASE(NBU, nbu)
            SAND_MULTIS_BLOCK_CASE(DDHX, ddhx)
            SAND_MULTIS_BLOCK_CASE(TCMX, tcmx)
            SAND_MULTIS_BLOCK_CASE(DTQ, dtq)
            SAND_MULTIS_BLOCK_CASE(NBUTX, nbutx)
            SAND_MULTIS_BLOCK_CASE(PBU, pbu)
            SAND_MULTIS_BLOCK_CASE(PHB, phb)
            SAND_MULTIS_BLOCK_CASE(QHC, qhc)
            SAND_MULTIS_BLOCK_CASE(MKX, mkx)
            SAND_SINGLE_BLOCK_CASE(MDBA, mdba)
            SAND_SINGLE_BLOCK_CASE(MDBB, mdbb)
            SAND_SINGLE_BLOCK_CASE(CIG, cig)
            SAND_SINGLE_BLOCK_CASE(PADS, pads)
            SAND_SINGLE_BLOCK_CASE(IPC, ipc)
            SAND_SINGLE_BLOCK_CASE(ARB, arb)
            SAND_SINGLE_BLOCK_CASE(FAWR, fawr)
            SAND_SINGLE_BLOCK_CASE(FAWT, fawt)
            SAND_SINGLE_BLOCK_CASE(FBSW, fbsw)
            SAND_SINGLE_BLOCK_CASE(FDCRL, fdcrl)
            SAND_SINGLE_BLOCK_CASE(FDCRS, fdcrs)
            SAND_SINGLE_BLOCK_CASE(FDMP, fdmp)
            SAND_SINGLE_BLOCK_CASE(FDMXA, fdmxa)
            SAND_SINGLE_BLOCK_CASE(FDMXB, fdmxb)
            SAND_SINGLE_BLOCK_CASE(FDMXC, fdmxc)
            SAND_SINGLE_BLOCK_CASE(FDMXT, fdmxt)
            SAND_SINGLE_BLOCK_CASE(FECRL, fecrl)
            SAND_SINGLE_BLOCK_CASE(FECRS, fecrs)
            SAND_SINGLE_BLOCK_CASE(FFLXO, fflxo)
            SAND_SINGLE_BLOCK_CASE(FFOA, ffoa)
            SAND_SINGLE_BLOCK_CASE(FFOB, ffob)
            SAND_SINGLE_BLOCK_CASE(FGDMP, fgdmp)
            SAND_SINGLE_BLOCK_CASE(FGMAP, fgmap)
            SAND_SINGLE_BLOCK_CASE(FLEXMAC, flexmac)
            SAND_SINGLE_BLOCK_CASE(FLOTN, flotn)
            SAND_SINGLE_BLOCK_CASE(FMACR, fmacr)
            SAND_SINGLE_BLOCK_CASE(FMACT, fmact)
            SAND_SINGLE_BLOCK_CASE(FMAP, fmap)
            SAND_SINGLE_BLOCK_CASE(FMXA, fmxa)
            SAND_SINGLE_BLOCK_CASE(FMXBI, fmxbi)
            SAND_SINGLE_BLOCK_CASE(FMXBJ, fmxbj)
            SAND_SINGLE_BLOCK_CASE(FMXC, fmxc)
            SAND_SINGLE_BLOCK_CASE(FMXT, fmxt)
            SAND_SINGLE_BLOCK_CASE(FOSW, fosw)
            SAND_SINGLE_BLOCK_CASE(FPMR, fpmr)
            SAND_SINGLE_BLOCK_CASE(FPMT, fpmt)
            SAND_SINGLE_BLOCK_CASE(FPTPR, fptpr)
            SAND_SINGLE_BLOCK_CASE(FPTPT, fptpt)
            SAND_SINGLE_BLOCK_CASE(FRWA, frwa)
            SAND_SINGLE_BLOCK_CASE(FRWBC, frwbc)
            SAND_SINGLE_BLOCK_CASE(OFR, ofr)
            SAND_SINGLE_BLOCK_CASE(OFT, oft)
            SAND_SINGLE_BLOCK_CASE(FECPB, fecpb)
            SAND_SINGLE_BLOCK_CASE(FMXBK, fmxbk)
            SAND_SINGLE_BLOCK_CASE(WB, wb)
            SAND_SINGLE_BLOCK_CASE(FICPB, ficpb)
            SAND_SINGLE_BLOCK_CASE(FDMXBJ, fdmxbj)
            SAND_SINGLE_BLOCK_CASE(W40, w40)
            SAND_SINGLE_BLOCK_CASE(FMXAJ, fmxaj)
            SAND_SINGLE_BLOCK_CASE(TSN, tsn)
            SAND_SINGLE_BLOCK_CASE(FMXAI, fmxai)
            SAND_SINGLE_BLOCK_CASE(FDMXBI, fdmxbi)
            SAND_MULTIS_BLOCK_CASE(IPW, ipw)
            SAND_MULTIS_BLOCK_CASE(DC3MAC, dc3mac)
            SAND_MULTIS_BLOCK_CASE(DC3PORT, dc3port)
            SAND_MULTIS_BLOCK_CASE(HBW, hbw)
            SAND_MULTIS_BLOCK_CASE(HPW, hpw)
            SAND_MULTIS_BLOCK_CASE(FDMX, fdmx)
            SAND_MULTIS_BLOCK_CASE(FLFR, flfr)
            SAND_MULTIS_BLOCK_CASE(FLFT, flft)
            SAND_MULTIS_BLOCK_CASE(FMX, fmx)
            SAND_MULTIS_BLOCK_CASE(FOAM, foam)
            SAND_MULTIS_BLOCK_CASE(FODUO, foduo)
            SAND_MULTIS_BLOCK_CASE(FRA, fra)
            SAND_MULTIS_BLOCK_CASE(MDBK, mdbk)
            SAND_SINGLE_BLOCK_CASE(MGU, mgu)
            SAND_MULTIS_BLOCK_CASE(DDHC, ddhc)
            SAND_MULTIS_BLOCK_CASE(DDHAB, ddhab)
            SAND_SINGLE_BLOCK_CASE(MACTMNG, mactmng)
            SAND_SINGLE_BLOCK_CASE(FDTM, fdtm)
            SAND_MULTIS_BLOCK_CASE(EPPS, epps)
            SAND_SINGLE_BLOCK_CASE(CPX, cpx)
            SAND_SINGLE_BLOCK_CASE(SAT, sat)
            SAND_SINGLE_BLOCK_CASE(FDTS, fdts)
            SAND_SINGLE_BLOCK_CASE(SER, ser)
            SAND_SINGLE_BLOCK_CASE(AVS, avs)
            SAND_MULTIS_BLOCK_CASE(MSW, msw)
            SAND_SINGLE_BLOCK_CASE(OCCG, occg)
            SAND_MULTI_BLOCK_CASE(DCH, dch)
            SAND_MULTI_BLOCK_CASE(DCML, dcml)
            SAND_SINGLE_BLOCK_CASE(MCT, mct)
            SAND_SINGLE_BLOCK_CASE(PCU, pcu)
            SAND_MULTI_BLOCK_CASE(QRH, qrh)
            SAND_MULTI_BLOCK_CASE(CCH, cch)
            SAND_MULTI_BLOCK_CASE(LCM, lcm)
            SAND_MULTI_BLOCK_CASE(CCML, ccml)
            SAND_MULTI_BLOCK_CASE(MESH_TOPOLOGY_WRAP, mesh_topology_wrap)
            SAND_MULTI_BLOCK_CASE(DTM, dtm)
            SAND_MULTI_BLOCK_CASE(DTL, dtl)
            SAND_MULTI_BLOCK_CASE(DFL, dfl)
            SAND_MULTI_BLOCK_CASE(DFL_FBC, dfl_fbc)
            SAND_MULTI_BLOCK_CASE(VTMON, vtmon)

            case SOC_BLK_BRDC_CPL:
            case SOC_BLK_BRDC_GPORT:
            case SOC_BLK_BRDC_PMQ:
            case SOC_BLK_BRDC_XPL:
            case SOC_BLK_DEBUG:
                break;

            default:
                LOG_INFO(BSL_LOG_MODULE, (BSL_META_U(unit, "unrecognized block type %d=\"%s\" instance=%d of block %d\n"),
                  blktype, soc_block_name_lookup_ext(blktype, unit), blknum, blk));
                break;
        }


        sal_snprintf(si->block_name[blk], sizeof(si->block_name[blk]),
                     "%s%s", soc_block_name_lookup_ext(blktype, unit), instance_string);
    }
    si->block_num = blk;

    if (invalid_instances) { 
        while (*invalid_instances != (soc_invalid_block_instances_t)(-1)) {
            si->block_valid[*(invalid_instances++)] = 0;
        }
    }

exit:
    SHR_FUNC_EXIT;

}


uint32 soc_sand_is_emulation_system(
    int unit)
{ 
    int rv = SOC_E_NONE;
#ifdef BCM_DNX_SUPPORT
    if(SOC_IS_DNX(unit)){
        rv = dnx_data_device.emulation.emulation_system_get(unit);
    }else
#endif
#ifdef BCM_DNXF_SUPPORT
    if(SOC_IS_DNXF(unit)){
        rv = dnxf_data_device.emulation.emulation_system_get(unit);
    }else
#endif
#ifdef BCM_DPP_SUPPORT
    if(SOC_IS_DPP(unit)){
        rv = SOC_DPP_CONFIG(unit)->emulation_system;
    }else 
#endif
    {
        return 0;
    }

    return rv;
}


void soc_sand_access_conf_get(
    int unit)
{
    int schan_timeout;

    if (SAL_BOOT_QUICKTURN) {
        schan_timeout = SCHAN_TIMEOUT_QT;
    } else if (SAL_BOOT_PLISIM) {
        schan_timeout = SCHAN_TIMEOUT_PLI;
    } else {
        schan_timeout = SCHAN_TIMEOUT;
    }
    SOC_CONTROL(unit)->schanTimeout = soc_property_get(unit, spn_SCHAN_TIMEOUT_USEC, schan_timeout);
    SOC_CONTROL(unit)->schanIntrEnb = soc_property_get(unit, spn_SCHAN_INTR_ENABLE, 0);
    SOC_CONTROL(unit)->miimTimeout =  soc_property_get(unit, spn_MIIM_TIMEOUT_USEC, 2000); 
    SOC_CONTROL(unit)->miimIntrEnb = soc_property_get(unit, spn_MIIM_INTR_ENABLE, 0);
}


/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * The PCID application handler.
 *
 * Requires:
 *     All modules
 *
 * Provides:
 *     User interface, initialization, main()
 *
 */

#include <shared/bsl.h>
#include <shared/bslext.h>

#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <soc/mem.h>
#include <soc/hash.h>
#include <soc/cmext.h>

#include <soc/cmic.h>
#ifdef BCM_CMICM_SUPPORT
#include <soc/cmicm.h>
#endif

#include <soc/drv.h>
#if defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)
#include <soc/dnxc/drv.h>
#endif
#if defined(BCM_PETRA_SUPPORT)
#include <soc/dpp/drv.h>
#endif
#if defined(BCM_DFE_SUPPORT)
#include <soc/dfe/cmn/dfe_drv.h>
#endif
#if defined(BCM_DNX_SUPPORT)
#include <soc/dnx/drv.h>
#endif
#if defined(BCM_DNXF_SUPPORT)
#include <soc/dnxf/cmn/dnxf_drv.h>
#endif
#ifdef BCM_PETRA_SUPPORT
#include <soc/dpp/mbcm.h>
#endif
#ifdef BCM_ACCESS_SUPPORT
#include <soc/access/access.h>
#include <soc/access/auto_generated/common_enum.h>
#include <soc/access/access_regmem_util.h>
#include <soc/access/utils.h>
extern const access_device_versions_t devices[];
#endif
#include <soc/devids.h>
#include <soc/chip.h>
#include <soc/mcm/driver.h>    /* soc_base_driver_table */
#include <soc/debug.h>
#include <sal/appl/io.h>

#include <bde/pli/verinet.h>
#include <bde/pli/plibde.h>

#include <sal/core/boot.h>
#include <sal/appl/config.h>

#include "pcid.h"
#include "mem.h"
#include "cmicsim.h"
#include "dma.h"
#include "pli.h"
#include "socintf.h"
#include "chipsim.h"
#ifdef BCM_CMICX_SUPPORT
#include "cmicx.h"
#endif /* BCM_CMICX_SUPPORT */

#define I2C_ROM_FILE    "soc_i2c.img"

#ifdef BCM_ISM_SUPPORT
extern uint8 ism_init;
#endif

/* used to be static */
pcid_info_t pcid_info;

ibde_t *bde = NULL;

int
bde_create(void)
{
    return plibde_create(&bde);
}

static void
usage(void)
{
#ifdef __STRICT_ANSI__
    fprintf(stderr,
            "Usage: pcid <chip>\n");
#else
    fprintf(stderr,
            "Usage: pcid [-ha] [-p port] [-vPxdilkc] [-G N] [-B N] "
            "[-W 64] [-D N] [-R N] <chip>\n");
    fprintf(stderr,
        "     <chip>     Chip to emulate, e.g. BCM56504_B0\n");
    fprintf(stderr,
        "     -h         Show help\n");
    fprintf(stderr,
        "     -a         List all supported chips \n");
    fprintf(stderr,
        "     -v         Verbose mode\n");
    fprintf(stderr,
        "     -p port    Specify which port to start PCID server on\n");
    fprintf(stderr,
        "     -P         Include PLI register R/W in verbose mode\n");
    fprintf(stderr,
        "     -x         Exit when first client disconnects\n");
    fprintf(stderr,
        "     -d         Run in verinet debug mode\n");
    fprintf(stderr,
        "     -i         Dump code for headless I2C ROM contents into\n");
    fprintf(stderr,
        "                the file %s\n", I2C_ROM_FILE);
    fprintf(stderr,
        "     -l         Loops back packets transmitted out\n");
    fprintf(stderr,
        "     -k         Take packet input using the file method\n");
    fprintf(stderr,
        "     -c         Simulate counter activity (inefficiently!)\n");
    fprintf(stderr,
        "     -G N       Simulate GBP size of N megabytes\n");
    fprintf(stderr,
        "     -B N       Simulate GBP with N banks (2 or 4)\n");
    fprintf(stderr,
            "     -W 64      Simulate GBP width of 64 bits (-G still\n"
        "                specifies size as if it were 128 bits wide)\n");
    fprintf(stderr,
        "     -D N       Override PCI device ID to N; e.g. 0x5616\n");
    fprintf(stderr,
        "     -R N       Override PCI revision ID to N; e.g. 3\n");
    fprintf(stderr,
            "     -C N       Set device config to N; e.g. 1\n");
#endif
    exit(1);
}

static int
pcid_out_hook(bsl_meta_t *meta, const char *format, va_list args)
{
    return vprintf(format, args);
}

static int
pcid_check_hook(bsl_packed_meta_t meta_pack)
{
    int source, severity;

    source = BSL_SOURCE_GET(meta_pack);
    severity = BSL_SEVERITY_GET(meta_pack);

    if (severity <= bslSeverityWarn) {
        return 1;
    }
    if (source == bslSourceShell) {
        return 1;
    }
    if (source == bslSourceCommon) {
        if (severity <= bslSeverityVerbose && pcid_info.opt_verbose) {
            return 1;
        }
    }
    if (source == bslSourceVerinet && pcid_info.opt_debug) {
        if (severity <= bslSeverityInfo) {
            return 1;
        }
        if (severity <= bslSeverityVerbose && pcid_info.opt_verbose) {
            return 1;
        }
    }
    return 0;
}

static void
pcid_info_init(pcid_info_t *pcid_info)
{
    bsl_config_t bsl_config;

    bsl_config_t_init(&bsl_config);
    bsl_config.out_hook = pcid_out_hook;
    bsl_config.check_hook = pcid_check_hook;
    bsl_init(&bsl_config);

    sal_memset(pcid_info, 0, sizeof(pcid_info_t));
    pcid_info->opt_gbp_banks = 2;
    pcid_info->opt_gbp_mb = 32;
    pcid_info->opt_gbp_wid = 128;

    pcid_info->single_mode = 0;

    if ((pcid_info->pkt_mutex = sal_mutex_create("pkt_mutex")) == NULL) {
    printf("sal_mutex_create -pkt_mutex failed\n");
    exit(1);
    }
    soc_cm_init();
}

static void
pcid_clean_regsfile(uint16 pci_dev_id, uint16 pci_rev_id)
{
    soc_reg_t    reg;
    int        disable_ipic;

    disable_ipic = 0;
    switch (pci_dev_id) {
    case 0x5691:    /* 5690 variations */
    case 0x5693:
    case 0x5696:    /* 5695 variations */
    case 0x5698:
    disable_ipic = 1;
    break;
    /* 5665 variations? */
    }

    if (disable_ipic) {
    /*
     * Convert all IPIC registers to _INVALID_REGISTER.
     * soc_internal_write_reg will then complain about them.
     */

    for (reg = 0; reg < NUM_SOC_REG; reg++) {
            if (!SOC_REG_IS_VALID(0, reg)) {
                continue;
            }
        if (SOC_REG_INFO(0, reg).block[0] == SOC_BLK_IPIC) {
        SOC_REG_INFO(0, reg).block[0] = 0;
        SOC_REG_INFO(0, reg).regtype = soc_invalidreg;
        SOC_REG_INFO(0, reg).numels = -1;
        SOC_REG_INFO(0, reg).offset = 0;
        SOC_REG_INFO(0, reg).flags = 0;
        SOC_REG_INFO(0, reg).nFields = 0;
        SOC_REG_INFO(0, reg).fields = NULL;
        SOC_REG_INFO(0, reg).ctr_idx = -1;
        }
    }
    }
}

void
pcid_schan_cb_set(pcid_info_t *pcid_info,  _pcid_schan_f f)
{
    pcid_info->schan_cb = f;
}

void
pcid_reset_cb_set(pcid_info_t *pcid_info,  _pcid_reset_f f)
{
    pcid_info->reset_cb = f;
}


/* main function */
int
main(int argc, char *argv[])
{
    int            i, chip, found;
    char           *s;
#ifndef __STRICT_ANSI__
    extern char    *optarg;
#endif
    struct timeval tmout;
    uint16         pci_dev_id, pci_ven_id;
    uint8          pci_rev_id;
    int            max_command_errors = 100;
    int            command_errors = 0;
    int            len;
    char           *config_file, *config_temp;
    int            chan;
#ifdef BCM_ACCESS_SUPPORT
    access_runtime_info_t **rt_array_pointer = &ACCESS_RUNTIME_INFO(pcid_info.unit);
    access_runtime_info_t *created_runtime_info = NULL;
    const access_device_type_info_t *device_info;
    unsigned current_device;
    int have_new_access = 0;
    int have_only_new_access = 0;
#endif
    pcid_info_init(&pcid_info);

    if ((config_file = getenv("BCM_CONFIG_FILE")) != NULL) {
        len = sal_strlen(config_file);
        if ((config_temp = sal_alloc(len+5, NULL)) != NULL) {
            /* coverity[secure_coding] */
            sal_strcpy(config_temp, config_file);
            /* coverity[secure_coding] */
            sal_strcpy(&config_temp[len], ".tmp");
            sal_config_file_set(config_file, config_temp);
            /* coverity[tainted_data] */
            sal_free(config_temp);
        }
    }

    if (sal_core_init() < 0) {
    printf("sal_core_init failed\n");
    exit(1);
    }

    if (sal_appl_init() < 0) {
    printf("sal_appl_init failed\n");
    exit(1);
    }

    /*
     * Get default port from SOC_TARGET_PORT, if available
     */

    if ((s = getenv("SOC_TARGET_PORT")) != NULL) {
    pcid_info.opt_port = strtol(s, 0, 0);
    }

#ifndef __STRICT_ANSI__
    while ((i = getopt(argc, argv, "havxdilkcG:W:B:Pp:D:R:C:")) >= 0)
        switch (i) {
        case 'h':
            usage();
            break;
        case 'a':
            fprintf(stderr, "List of supported chips:\n");
            for (i = 0; i < SOC_CHIP_TYPES_COUNT; i++) {
                fprintf(stderr, "pcid:  %s\n", soc_chip_type_names[i]);
            }
            exit(1);
            break;
        case 'v':
            pcid_info.opt_verbose = 1;
            break;
        case 'x':
            pcid_info.opt_exit = 1;
            break;
        case 'd':
            pcid_info.opt_debug = 1;
            break;
        case 'i':
            pcid_info.opt_i2crom = 1;
            break;
        case 'l':
            pcid_info.opt_pktloop = 1;
            pcid_info.tx_cb = _pcid_loop_tx_cb;
            break;
        case 'k':
            pcid_info.opt_pktfile = 1;
            break;
        case 'c':
            pcid_info.opt_counter = 1;
            break;
        case 'G':
            pcid_info.opt_gbp_mb = strtol(optarg, 0, 0);
            break;
        case 'B':
            pcid_info.opt_gbp_banks = strtol(optarg, 0, 0);
            break;
        case 'P':
            pcid_info.opt_pli_verbose = 1;
            break;
        case 'p':
            pcid_info.opt_port = strtol(optarg, 0, 0);
            break;
        case 'D':
            pcid_info.opt_override_devid = strtol(optarg, 0, 0);
            break;
        case 'R':
            pcid_info.opt_override_revid = strtol(optarg, 0, 0);
            break;
        case 'W':
            pcid_info.opt_gbp_wid = strtol(optarg, 0, 0);
            break;
        default:
            printf("pcid: unknown option '%c'\n", i);
            usage();
            break;
        }

    /*
     * Check arguments: user must specify a port to bind to.
     */

    if (optind != argc - 1) {
    usage();
    }

    /*
     * Coverity
     *
     * Coverity complains that the variable optind is tainted, since it
     * may take the true path in the above conditional, which means
     * optind != (argc - 1) and thus is unbounded.  Coverity
     * fails to realize that usage() ends with exit(), so no true
     * test of the conditional may proceed with processing.  If the
     * conditional is false, then the variable is bounded and not tainted.
     */
    /* coverity[var_assign_var] : FALSE */
    pcid_info.opt_chip_name = argv[optind];
#else
    if (argc != 2) {
        usage();
    } else {
        pcid_info.opt_chip_name = argv[1];
    }
#endif /*__STRICT_ANSI__*/

    found = 0;
    for (i = 0; i < SOC_CHIP_TYPES_COUNT; i++) {
        if (sal_strcasecmp(pcid_info.opt_chip_name, soc_chip_type_names[i]) == 0) {
            found = 1;
            pcid_info.opt_chip = i;
            break;
        } else
        /* Allow specifying chip by number only, e.g. 5690 or 56504 */
        if (isdigit((unsigned)pcid_info.opt_chip_name[0]) &&
            atoi(pcid_info.opt_chip_name) ==
            atoi(&soc_chip_type_names[i][3])) {
            found = 1;
            pcid_info.opt_chip = i;
            break;
        }
    }
#ifdef BCM_ACCESS_SUPPORT
    /*created_runtime_info = ACCESS_RUNTIME_INFO(pcid_info.unit);*/
    for (current_device = 0; current_device < ACCESS_NOF_DEVICE_TYPES;current_device++)
    {
        /*printf("pcid: unknown option '%s' arg chip name %s \n", devices[current_device].device_name, pcid_info.opt_chip_name);*/
        if (sal_strcasecmp(pcid_info.opt_chip_name, devices[current_device].device_name) == 0) {
            found = 1;
            device_info = devices[current_device].device_versions[0];
            have_new_access = 1;
            break;
        }
    }
    if (have_new_access == 1)
    {
        if (device_info->flags == ACCESS_DEVICE_TYPE_INFO_NO_OLD_ACCESS)
        {
            have_only_new_access = 1;
        }
    }
#endif
    if (!found) {
    fprintf(stderr,
        "pcid: Unrecognized chip type '%s'\n",
        pcid_info.opt_chip_name);
    fprintf(stderr, "pcid: Valid chip types are:\n");
    for (i = 0; i < SOC_CHIP_TYPES_COUNT; i++) {
        fprintf(stderr, "pcid:  %s\n", soc_chip_type_names[i]);
    }
    exit(1);
    }

    /*
     * Set initial contents of PCI configuration space.
     */
#ifdef BCM_ACCESS_SUPPORT
    if (have_only_new_access == 0)
    {
#endif
        chip = soc_chip_type_to_index(pcid_info.opt_chip);
        pci_ven_id = soc_base_driver_table[chip]->pci_vendor;
        pci_dev_id = soc_base_driver_table[chip]->pci_device;
        pci_rev_id = soc_base_driver_table[chip]->pci_revision;
#ifdef BCM_ACCESS_SUPPORT
    } else {
        pci_ven_id = BROADCOM_VENDOR_ID;
        pci_dev_id = device_info->devid;
        pci_rev_id = device_info->default_revision_id;
    }
#endif

    fprintf(stderr,
        "pcid: opt_chip %d, chip %d, pci_ver_id:dev_id:rev_id 0x%4x:0x%4x:0x%2x, chip name:'%s'\n",
        pcid_info.opt_chip, chip, pci_ven_id, pci_dev_id, pci_rev_id, pcid_info.opt_chip_name);


    if (pci_dev_id == 0x0) {
    fprintf(stderr,
        "pcid: Not compiled with support for '%s'\n",
        pcid_info.opt_chip_name);
    exit(1);
    }

    /* From here on, we want the effective ID's */
    if (pcid_info.opt_override_devid) {
        pci_dev_id = pcid_info.opt_override_devid;
    }
    if (pcid_info.opt_override_revid) {
        pci_rev_id = pcid_info.opt_override_revid;
    }

    soc_internal_pcic_init(&pcid_info, pci_dev_id,
                           pci_ven_id, pci_rev_id, 0xcd600000);

    /*
     * Init driver so soc_feature and other functions can be used.
     * Assume that the unit and BDE device are both zero.
     */
    soc_cm_device_create(pci_dev_id, pci_rev_id, NULL, 0);

        SOC_CONTROL(0) = sal_alloc(sizeof (soc_control_t), "soc_control_t");
        memset(SOC_CONTROL(0), 0, sizeof (soc_control_t));
    
        SOC_PERSIST(0) = sal_alloc(sizeof (soc_persist_t), "soc_persist_t");
        memset(SOC_PERSIST(0), 0, sizeof (soc_persist_t));
#ifdef BCM_ACCESS_SUPPORT
    if (have_only_new_access == 0)
    {
#endif
#if defined(BCM_PETRA_SUPPORT)
        if (SOC_CONTROL(0)->chip_driver == NULL && SOC_IS_DPP_TYPE(pci_dev_id)) {
            SOC_CONTROL(0)->chip_driver = soc_dpp_chip_driver_find(pci_dev_id, pci_rev_id);
        }
#endif
#if defined(BCM_DNX_SUPPORT)
        if (SOC_CONTROL(0)->chip_driver == NULL && SOC_IS_DNX_TYPE(pci_dev_id)) {
            soc_dnxc_chip_driver_find(0, pci_dev_id, pci_rev_id, (void *)&(SOC_CONTROL(0)->chip_driver));
        }
#endif
#if defined(BCM_DFE_SUPPORT)
        if (SOC_CONTROL(0)->chip_driver == NULL && SOC_IS_DFE_TYPE(pci_dev_id)) {
            SOC_CONTROL(0)->chip_driver = soc_dfe_chip_driver_find(0, pci_dev_id, pci_rev_id);
        }
#endif
#if defined(BCM_DNXF_SUPPORT)
        if (SOC_CONTROL(0)->chip_driver == NULL && SOC_IS_DNXF_TYPE(pci_dev_id)) {
            soc_dnxc_chip_driver_find(0, pci_dev_id, pci_rev_id, (void *)&(SOC_CONTROL(0)->chip_driver));
        }
#endif
#if  defined(BCM_ESW_SUPPORT)
        if (SOC_CONTROL(0)->chip_driver == NULL) {
            SOC_CONTROL(0)->chip_driver = soc_chip_driver_find(pci_dev_id, pci_rev_id);
        }
#endif
        assert(SOC_CONTROL(0)->chip_driver != NULL);

        PCIC(&pcid_info, 0x14) = SOC_CONTROL(0)->chip_driver->cmicd_base;

        if (soc_base_driver_table[chip]->init) {
        (soc_base_driver_table[chip]->init)();
        }
#ifdef BCM_ACCESS_SUPPORT
    } else {
        if (*rt_array_pointer != NULL) {
            fprintf(stderr, "Error: access already initialized for the device\n\n");
        }
        created_runtime_info = sal_alloc2(sizeof(access_runtime_info_t), SAL_ALLOC_F_ZERO, "access_runtime_info");
        if (created_runtime_info == NULL) {
            fprintf(stderr, "Error: failed to allocate runtime info structure\n");
            exit(1);
        }

        *rt_array_pointer = created_runtime_info;
        created_runtime_info->unit = pcid_info.unit;
        PCIC(&pcid_info, 0x14) = device_info->cmic_axi_offset;
    }
#endif
        /* this sets up the SOC_IS_* macros, amongst other things */
#if defined(BCM_PETRA_SUPPORT)
        if(SOC_IS_DPP_TYPE(pci_dev_id)) {
            soc_dpp_chip_type_set(0, CMDEV(0).dev.info->dev_id);
            if ((i = soc_dpp_defines_init(0)) != SOC_E_NONE) {
                return i;
            }
            mbcm_dpp_init(0);
            soc_dpp_info_config(0);
        } else
#endif
#if defined(BCM_DNX_SUPPORT)
        if(SOC_IS_DNX_TYPE(pci_dev_id)) {
#ifdef BCM_ACCESS_SUPPORT
            if (have_only_new_access == 0)
            {
#endif
                soc_dnxc_chip_type_set(0, CMDEV(0).dev.info->dev_id);
                soc_dnxc_info_config_init(0);
#ifdef BCM_ACCESS_SUPPORT
            }
#endif
        } else
#endif
#if defined(BCM_DFE_SUPPORT)
        if(SOC_IS_DFE_TYPE(pci_dev_id)) {
            soc_dfe_chip_type_set(0, CMDEV(0).dev.info->dev_id);
            soc_dfe_info_config(0, pci_dev_id);
        } else
#endif
#if defined(BCM_DNXF_SUPPORT)
        if(SOC_IS_DNXF_TYPE(pci_dev_id)) {
            soc_dnxc_chip_type_set(0, CMDEV(0).dev.info->dev_id);
            soc_dnxf_info_config(0);
        } else
#endif
        {
#ifdef BCM_XGS_SWITCH_SUPPORT
            soc_info_config(0, SOC_CONTROL(0));
#endif
        }
#ifdef BCM_ACCESS_SUPPORT
    if (have_only_new_access == 0)
    {
#endif
        (void)soc_memstate_alloc(0);
#ifdef BCM_ACCESS_SUPPORT
    }
#endif
    /* set up soc_feature macro */
#ifdef BCM_ACCESS_SUPPORT
    if (have_only_new_access == 0)
    {
#endif
        soc_feature_init(0);
#ifdef BCM_ACCESS_SUPPORT
    }
#endif
    /* Record the SBUS address version, now that features are enabled */
    pcid_info.sbus_addr_version =
        soc_feature(pcid_info.unit, soc_feature_new_sbus_format) ?
        SBUS_ADDR_VERSION_2 : SBUS_ADDR_VERSION_1;


#ifdef BCM_CMICX_SUPPORT
    /* initialize the cmicx sim if we have a cmicx chip */
    if (soc_feature(pcid_info.unit, soc_feature_cmicx)) {
        if (cmicx_init()==FALSE) {
            return 1;
        }
    }
#endif /* BCM_CMICX_SUPPORT */

#ifdef BCM_CMICM_SUPPORT
    pcid_info.cmicm = soc_feature(pcid_info.unit, soc_feature_cmicm) ? CMC0 : -1;
#if defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)
    if (soc_feature(pcid_info.unit, soc_feature_cmicx) &&
      (SOC_IS_DNX(pcid_info.unit) || SOC_IS_DNXF(pcid_info.unit))) {
        /* Use CMICM simulation instead of CMICX simulation */
        pcid_info.cmicm = CMC0;
    }
#endif /* BCM_DNX_SUPPORT || BCM_DNXF_SUPPORT */
#endif

#if defined(BCM_ESW_SUPPORT)
#if (!defined(BCM_PETRA_SUPPORT)) && (!defined(BCM_DFE_SUPPORT))
    /* initialize dcb operations */
    soc_dcb_unit_init(0);
#endif /* (!defined(BCM_PETRA_SUPPORT)) && (!defined(BCM_DFE_SUPPORT)) */
#endif /* defined(BCM_ESW_SUPPORT) */
    /*
     * Initialize memory index_maxes.
     */
#ifdef BCM_ACCESS_SUPPORT
    if (have_only_new_access == 0)
    {
#endif
        for (i = 0; i < NUM_SOC_MEM; i++) {
            if (SOC_MEM_IS_VALID(0, i)) {
                SOP_MEM_STATE_MAX_INDEX_SET(0, i, SOC_MEM_INFO(0, i).index_max);
            }
        }
#ifdef BCM_ACCESS_SUPPORT
    }
#endif
    /*
     * Perform any needed run-time cleanup of regsfile.
     */

    pcid_clean_regsfile(pci_dev_id, pci_rev_id);

    if (pcid_info.opt_port == 0) {
    fprintf(stderr, "pcid: Must specify port number using -p or set\n");
    fprintf(stderr, "      it in SOC_TARGET_PORT environment variable\n");

    exit(1);
    }

    pli_reset_service(&pcid_info);

    pcid_info.sockfd = pcid_setup_socket(pcid_info.opt_port);

    do {
        pcid_info.opt_rpc_error = 0; /* reset the error condition */
        printf("%s: Emulating %s, listening on port %d\n",
               argv[0],
               soc_cm_get_device_name(pci_dev_id, pci_rev_id),
               pcid_info.opt_port);

    pcid_info.newsockfd = pcid_wait_for_cnxn(pcid_info.sockfd);

    if (pcid_info.opt_i2crom) {
        if ((pcid_info.i2crom_fp = fopen(I2C_ROM_FILE, "w")) == 0) {
        perror("unable to open I2C ROM output file");
        }
    }

    printf("%s: Client connected\n", argv[0]);

    /*
     * Queue initial events
     */

    event_init();

    if (pcid_info.opt_pktfile) {
        event_enqueue(&pcid_info, pcid_check_packet_input,
              sal_time_usecs() + PACKET_CHECK_INTERVAL);
    }

    if (pcid_info.opt_counter) {
        event_enqueue(&pcid_info, pcid_counter_activity,
              sal_time_usecs() + COUNTER_ACT_INTERVAL);
    }

#ifdef BCM_ISM_SUPPORT
        ism_init = 0;
#endif


    /*
     * Event/request loop
     */

    for (;;) {
        event_t        *ev;
        int             usec;      /* Signed */
        sal_usecs_t     now;

        now = sal_time_usecs();

        if ((ev = event_peek()) != NULL) {
        usec = SAL_USECS_SUB(ev->abs_time, now);
        } else {
            /* if we have a cmicx chip, we need a different (faster) timeout for the sim */
            if (soc_feature(pcid_info.unit, soc_feature_cmicx)) {
                usec = 10;
            }
            else {
                usec = 100000;
            }
        }

        tmout.tv_sec = 0;
        tmout.tv_usec = (usec > 0 ? usec : 0);

        if ((pcid_process_request(&pcid_info,
                  pcid_info.newsockfd, &tmout) == PR_ERROR) ||
            (pcid_info.opt_rpc_error /* RPC error with client */)) {
                if (++command_errors > max_command_errors) {
                    pcid_info.opt_exit = 1;
                }
            break;
        }


#ifdef BCM_CMICX_SUPPORT
        /* if we have a cmicx chip, update the cmicx sim */
        if (soc_feature(pcid_info.unit, soc_feature_cmicx) &&
            !(SOC_IS_DNX(pcid_info.unit) || SOC_IS_DNXF(pcid_info.unit))) {
            cmicx_update(&pcid_info);
        } else
#endif /* BCM_CMICX_SUPPORT */
        {
            for (chan = 0; chan < N_DMA_CHAN; chan++) {
#ifdef BCM_CMICM_SUPPORT
                if (pcid_info.cmicm >= CMC0) {
                    pcid_dma_cmicm_rx_check(&pcid_info, chan);
                } else
#endif
                {
                    pcid_dma_rx_check(&pcid_info, chan);
                }
            }
        }

        event_process_through(now);
    }

    if (pcid_info.i2crom_fp) {
        /* Write data end marker */
        fputc(0xff, pcid_info.i2crom_fp);
        fputc(0xff, pcid_info.i2crom_fp);
        fputc(0x00, pcid_info.i2crom_fp);
        fclose(pcid_info.i2crom_fp);
    }

        /* Stop DMA on all channels to prevent the PCI polling on old DMA
         * when client connects again.
         */
        pcid_dma_stop_all(&pcid_info);

    pcid_close_cnxn(pcid_info.newsockfd);

    printf("%s: Client disconnected.\n", argv[0]);
    } while (!pcid_info.opt_exit);

    pcid_close_cnxn(pcid_info.sockfd);
    exit(0);
}

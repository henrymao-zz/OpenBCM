#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pty.h>
#include <errno.h>

#ifndef NO_SAL_APPL
#include <sal/appl/sal.h>
#include <sal/appl/config.h>
#include <appl/diag/bslmgmt.h>
#include <appl/diag/opennsa_diag.h>
#endif

#include <bcm/init.h>
#include <bcm/error.h>
#include <soc/cmext.h>
#include <soc/opensoc.h>
#include <sal/core/boot.h>
#include <linux-bde.h>

#ifdef BCM_WARM_BOOT_SUPPORT
#include <bcm/switch.h>
#endif

/*
 * These includes are needed for do_per_switch_setup() part of the demo.
 */
#include <bcm/port.h>
#include <bcm/stg.h>

#if defined(BCM_LTSW_SUPPORT)
#include <appl/diag/sysconf_ltsw.h>
#endif

#include <opennsa/link.h>

//#include <soc/esw/cancun.h>
/*
 * CANCUN file type enumeration
*/
typedef enum {
    CANCUN_SOC_FILE_TYPE_UNKNOWN,
    CANCUN_SOC_FILE_TYPE_CIH,
    CANCUN_SOC_FILE_TYPE_CMH,
    CANCUN_SOC_FILE_TYPE_CCH,
    CANCUN_SOC_FILE_TYPE_CFH,
    CANCUN_SOC_FILE_TYPE_CEH,
    CANCUN_SOC_FILE_TYPE_ISPF,

    /*Note: keep CANCUN_SOC_FILE_TYPE_NUM as the latest element of this enum
     * and update CANCUN_FILE_TYPE_NAMES_INITIALIZER accordingly*/
    CANCUN_SOC_FILE_TYPE_NUM
} soc_cancun_file_type_e;
extern int soc_cancun_generic_load(int unit, uint32 cancun_type);

//linkscan
extern int bcm_linkscan_enable_set(int unit, int us);

#ifdef LINUX_PLI_COMBO_BDE
extern int plibde_create(ibde_t** bde);
#endif

ibde_t *bde;

/*
 * The bus properties are (currently) the only system specific
 * settings required. These must be defined beforehand.
 */

#ifndef SYS_BE_PIO
#error "SYS_BE_PIO must be defined for the target platform"
#endif
#ifndef SYS_BE_PACKET
#error "SYS_BE_PACKET must be defined for the target platform"
#endif
#ifndef SYS_BE_OTHER
#error "SYS_BE_OTHER must be defined for the target platform"
#endif

#if !defined(SYS_BE_PIO) || !defined(SYS_BE_PACKET) || !defined(SYS_BE_OTHER)
#error "platform bus properties not defined."
#endif

/* Function defined in linux-user-bde.c */
extern int
bde_icid_get( int d, uint8 *data, int len );

static soc_chip_info_vectors_t chip_info_vect = {
    bde_icid_get
};

#ifdef INCLUDE_KNET

#include <soc/knet.h>
#include <bcm-knet-kcom.h>
#include <opennsa/knet.h>

/* Function defined in linux-user-bde.c */
extern int
bde_irq_mask_set( int unit, uint32 addr, uint32 mask );
extern int
bde_hw_unit_get( int unit, int inverse );

static soc_knet_vectors_t knet_vect_bcm_knet = {
    {
        bcm_knet_kcom_open,
        bcm_knet_kcom_close,
        bcm_knet_kcom_msg_send,
        bcm_knet_kcom_msg_recv
    },
    bde_irq_mask_set,
    bde_hw_unit_get
};

static void
knet_kcom_config( void )
{
    /* Direct IOCTL by default */
    soc_knet_config( &knet_vect_bcm_knet );
}

#endif /* INCLUDE_KNET */

#ifdef LINUX_PLI_COMBO_BDE
static int sim_path = 0;

int
bcm_sim_path_get(void)
{
    return sim_path;
}

int intr_int_context(void)
{
    extern int pli_intr_int_context() __attribute__((weak));
    extern int linux_intr_int_context() __attribute__((weak));

    if (sim_path) {
        return pli_intr_int_context();
    }
    return linux_intr_int_context();
}
#endif

int
bde_create( void )
{
    linux_bde_bus_t bus;
    bus.be_pio = SYS_BE_PIO;
    bus.be_packet = SYS_BE_PACKET;
    bus.be_other = SYS_BE_OTHER;

#ifdef LINUX_PLI_COMBO_BDE
    if (sim_path) {
        return plibde_create(&bde);
    }
#endif

    return linux_bde_create( &bus, &bde );
}

/* SOC Configuration Manager Device Vectors */

static char *
_sysconf_get_property( const char *property )
{
#ifndef NO_SAL_APPL
    return sal_config_get( property );
#else
    return NULL;
#endif
}

static char *
_config_var_get( soc_cm_dev_t *dev, const char *property )
{
    COMPILER_REFERENCE( dev );

    return _sysconf_get_property( property );
}

static void
_write( soc_cm_dev_t *dev, uint32 addr, uint32 data )
{
    bde->write( dev->dev, addr, data );
}

static uint32
_read( soc_cm_dev_t *dev, uint32 addr )
{
    return bde->read( dev->dev, addr );
}

static void *
_salloc( soc_cm_dev_t *dev, int size, const char *name )
{
    COMPILER_REFERENCE( name );
    return bde->salloc( dev->dev, size, name );
}

static void
_sfree( soc_cm_dev_t *dev, void *ptr )
{
    bde->sfree( dev->dev, ptr );
}

static int
_sflush( soc_cm_dev_t *dev, void *addr, int length )
{
    return( (bde->sflush) ? bde->sflush( dev->dev, addr, length ) : 0 );
}

static int
_sinval( soc_cm_dev_t *dev, void *addr, int length )
{
    return( (bde->sinval) ? bde->sinval( dev->dev, addr, length ) : 0 );
}

static sal_paddr_t
_l2p( soc_cm_dev_t *dev, void *addr )
{
    return( (bde->l2p) ? bde->l2p( dev->dev, addr ) : 0 );
}

static void*
_p2l( soc_cm_dev_t *dev, sal_paddr_t addr )
{
    return( (bde->p2l) ? bde->p2l( dev->dev, addr ) : 0 );
}

static void
_iproc_write( soc_cm_dev_t *dev, uint32 addr, uint32 data )
{
    bde->iproc_write( dev->dev, addr, data );
}

static uint32
_iproc_read( soc_cm_dev_t *dev, uint32 addr )
{
    return( bde->iproc_read( dev->dev, addr ) );
}

static int
_interrupt_connect( soc_cm_dev_t *dev, soc_cm_isr_func_t handler, void *data )
{
    return( bde->interrupt_connect( dev->dev, handler, data ) );
}

static int
_interrupt_disconnect( soc_cm_dev_t *dev )
{
    return( bde->interrupt_disconnect( dev->dev ) );
}

static void
_pci_conf_write( soc_cm_dev_t *dev, uint32 addr, uint32 data )
{
    bde->pci_conf_write( dev->dev, addr, data );
}

static uint32
_pci_conf_read( soc_cm_dev_t *dev, uint32 addr )
{
    return( bde->pci_conf_read( dev->dev, addr) );
}

static int
_spi_read( soc_cm_dev_t *dev, uint32 addr, uint8 *buf, int len )
{
    return( (bde->spi_read) ? bde->spi_read( dev->dev, addr, buf, len ) : -1 );
}

static int
_spi_write( soc_cm_dev_t *dev, uint32 addr, uint8 *buf, int len )
{
    return( (bde->spi_write) ? bde->spi_write(dev->dev, addr, buf, len) : -1 );
}

static int
_i2c_device_read( soc_cm_dev_t *dev, uint32 addr, uint32 *value )
{
    return( (bde->i2c_device_read) ?
             bde->i2c_device_read(dev->dev, addr, value) : -1 );
}

static int
_i2c_device_write( soc_cm_dev_t *dev, uint32 addr, uint32 value )
{
    return( (bde->i2c_device_write) ?
            bde->i2c_device_write( dev->dev, addr, value ) : -1 );
}

/*
 * _setup_bus
 *
 *    Utility routine used by _sysconf_probe
 */

static int
_setup_bus( int unit )
{
    uint16 driverDevID;
    uint16 driverRevID;
    const ibde_dev_t *dev = bde->get_dev( unit );
    char *bus_type;
    uint8 revID = dev->rev;

    soc_cm_get_id_driver( dev->device, revID,
                          &driverDevID, &driverRevID );

    switch( bde->get_dev_type( unit ) & BDE_DEV_BUS_TYPE_MASK )
    {
        case BDE_PCI_DEV_TYPE:
            bus_type = "PCI";
            break;
        case BDE_SPI_DEV_TYPE:
            bus_type = "SPI";
            break;
        case BDE_EB_DEV_TYPE:
            bus_type = "EB";
            break;
        case BDE_ICS_DEV_TYPE:
            bus_type = "ICS";
            break;
        case (BDE_SPI_DEV_TYPE|BDE_EB_DEV_TYPE) :
            bus_type = "SPI/EB";
            break;
        case BDE_ET_DEV_TYPE:
            bus_type = "ETH";
            break;
        case BDE_EMMI_DEV_TYPE:
            bus_type = "EMMI";
            break;
        case BDE_AXI_DEV_TYPE:
            bus_type = "AXI";
            break;
       case BDE_I2C_DEV_TYPE:
            bus_type = "I2C";
            break;
        default:
            printf( "Error : Unknown bus type=0x%x !!\n",
                    bde->get_dev_type( unit ) & BDE_DEV_BUS_TYPE_MASK );
            return -1;
    }

    printf( "BDE unit %d (%s), "
            "Dev 0x%04x, Rev 0x%02x, Chip %s, Driver %s\n",
            unit, bus_type,
            dev->device, revID,
            soc_cm_get_device_name( dev->device, revID ),
            soc_cm_get_device_name( driverDevID, driverRevID ) );

    return 0;
}


/*
 * _sysconf_probe
 *
 * Searches for known devices and creates Configuration Manager instances.
 */

static int _sysconf_probe_done;

static int
_sysconf_probe( void )
{
    int u;
    uint16 devID;
    uint8 revID;

    if( _sysconf_probe_done ){
        printf( "_sysconf_probe: cannot probe more than once\n" );
        return -1;
    }

    /*
     * Initialize system BDE
     */
    if( bde_create() ){
        return -1;
    }

    /* Iterate over device */
    for( u = 0; u < bde->num_devices( BDE_ALL_DEVICES ) &&
                u < SOC_MAX_NUM_SWITCH_DEVICES; u++ ){
        const ibde_dev_t *dev = bde->get_dev( u );
        devID = dev->device;
        revID = dev->rev;

        if ( soc_cm_device_supported( devID, revID ) < 0 ){
            /* Not a switch chip; continue probing other devices */
            printf( "ERROR: device 0x%x revision 0x%x is not supported\n",
                    (unsigned)devID, (unsigned)revID );
            return 0;
        }

        if( _setup_bus( u ) < 0 ){
            /*
             * Error message already printed; continue probing other
             * devices
             */
            return 0;
        }

        /*
         * Create a device handle, but don't initialize yet.  This
         * sneakily relies upon the fact that the cm handle = bde
         * handle.
         */
        (void) soc_cm_device_create( devID, revID, NULL );

        _sysconf_probe_done++;
    }

    return 0;
}

static int
_sysconf_attach( int unit )
{
    int bdx = 0; /* BDE handle */

    /* Ready to install into configuration manager */
    soc_cm_device_vectors_t vectors;

#if defined(BCM_LTSW_SUPPORT)
    if (soc_cm_get_dev_type(unit) & 0x80000000) {
        return sysconf_ltsw_attach(unit);
    }
#endif

    if( soc_cm_dev_num_get( unit, &bdx ) != 0 ){
        printf( "Unable to get BDE handle for unit=%d\n", unit );
        return 0;
    }

    memset( &vectors, 0, sizeof( soc_cm_device_vectors_t ) );

    /* Proceed with BDE device initialization */

    bde->pci_bus_features( bdx, &vectors.big_endian_pio,
                           &vectors.big_endian_packet,
                           &vectors.big_endian_other );
    vectors.config_var_get = _config_var_get;
    vectors.interrupt_connect = _interrupt_connect;
    vectors.interrupt_disconnect= _interrupt_disconnect;
    vectors.base_address = bde->get_dev( bdx )->base_address;
    vectors.read = _read;
    vectors.write = _write;
    vectors.pci_conf_read = _pci_conf_read;
    vectors.pci_conf_write = _pci_conf_write;
    vectors.salloc = _salloc;
    vectors.sfree = _sfree;
    vectors.sinval = _sinval;
    vectors.sflush = _sflush;
    vectors.l2p = _l2p;
    vectors.p2l = _p2l;
    vectors.iproc_read = _iproc_read;
    vectors.iproc_write = _iproc_write;
    vectors.bus_type = bde->get_dev_type( bdx );
    vectors.spi_read = _spi_read;
    vectors.spi_write = _spi_write;
    vectors.i2c_device_read = _i2c_device_read;
    vectors.i2c_device_write = _i2c_device_write;
    if( soc_cm_device_init(unit, &vectors) < 0 ){
        printf( "_sysconf_attach(): CM device init failed for unit=%d\n",
                unit );
        return( -1 );
    }
    return 0;
}


//load port_config.ini and create interfaces
int knet_portconfig_init(int unit)
{
    bcm_knet_netif_t netif;
    bcm_knet_filter_t filter;    
    FILE *fp = NULL;
    char line[256];
    char *token;
    int rv;

    /* open file, allocate buffer and read file into buffer */
    fp = sal_fopen("port_config.ini", "rb");
  
    if (!fp) {
       printf("port_config.ini open failed \n");
       return 0;
    }

    while (fgets(line, sizeof(line), fp)) {
        //printf("%s", line);         //Name
        // skip comments
        if(line[0] == '#') {
            continue;
        }

        bcm_knet_netif_t_init(&netif);
        netif.type = BCM_KNET_NETIF_T_TX_LOCAL_PORT;
        netif.vlan = 0;
        // netif.flags |= BCM_KNET_NETIF_F_ADD_TAG;
        netif.flags |= BCM_KNET_NETIF_F_KEEP_RX_TAG;
        netif.cb_user_data = 0;

        token = strtok(line, " ");
        sal_strncpy(netif.name, token, sizeof(netif.name) - 1);

        token = strtok (NULL, " "); //lanes
        token = strtok (NULL, " "); //alias
        token = strtok (NULL, " "); //index
        netif.port = atoi(token);

        printf("Creating Interface %s index %d\n",netif.name, netif.port);
        if ((rv = bcm_knet_netif_create(unit, &netif)) < 0) {
            printf("Error creating network interface: %d\n",rv );
        }

        //Create filter for KNET interface
        bcm_knet_filter_t_init(&filter);
        filter.type = BCM_KNET_FILTER_T_RX_PKT;
        //filter.flags = BCM_KNET_FILTER_F_STRIP_TAG;
        sal_strncpy(filter.desc, netif.name, sizeof(filter.desc) - 1);
        filter.priority = 100;
        filter.dest_type = BCM_KNET_DEST_T_NETIF;
        filter.dest_id = netif.port;
        filter.dest_proto = 0;

        filter.cb_user_data = 0;

        filter.m_ingport = netif.port;
        filter.match_flags |= BCM_KNET_FILTER_M_INGPORT;

        if ((rv = bcm_knet_filter_create(unit, &filter)) < 0) {
            printf("Error creating packet filter: %d\n", rv);
        }    
    }

    fclose(fp);
    return 0;
}

int switchdev_field_processor_init(int unit)
{
    bcm_error_t rv = BCM_E_NONE;
    bcm_field_group_config_t group_config;
    bcm_field_entry_t eid;
    //bcm_vlan_t vlan = 2, vlan_mask = 0xfff;
    bcm_port_t port = 0; //port_mask = 0xffffffff;
    bcm_mac_t mac_mask = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    //int prio;

    /* Enable IFP for CPU port */
    rv = bcm_port_control_set(unit, port, bcmPortControlFilterIngress, 1);

    /* FP group configuration and creation */
    bcm_field_group_config_t_init(&group_config);

    BCM_FIELD_QSET_INIT(group_config.qset);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyStageIngress);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyInPort);

    group_config.mode = bcmFieldGroupModeAuto;

    rv = bcm_field_group_config_create(unit, &group_config);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_group_config_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* FP entry configuration and creation */

    // EID 1
    rv = bcm_field_entry_create(unit, group_config.group, &eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    
    rv = bcm_field_qualify_DstL3Egress(unit, eid, port);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_DstL3Egress() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionPrioIntNew, 0x7, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* Installing FP entry to FP TCAM */
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    //EID 2
    rv = bcm_field_entry_create(unit, group_config.group, &eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_EtherType(unit, eid, 0x00000800, 0x0000ffff);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_EtherType() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_Ttl(unit, eid, 0x00000000, 0x000000fe);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_Ttl() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_MyStationHit(unit, eid, 0x1, 0x1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_MyStationHit() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionRpDrop, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionUnmodifiedPacketRedirectPort, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionGpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionGpPrioIntNew, 0x7, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionCosQCpuNew, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    //TODO create policer and attach to eid

    //TODO create stats and attach to eid


    /* Installing FP entry to FP TCAM */
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    //EID 3 ARP
    rv = bcm_field_entry_create(unit, group_config.group, &eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_DstMac(unit, eid, mac_mask, mac_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_EtherType() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_qualify_EtherType(unit, eid, 0x00000806, 0x0000ffff);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_EtherType() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_IpType(unit, eid, bcmFieldIpTypeArpRequest);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_IpType() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_InterfaceClassL2(unit, eid, 0x1, 0x1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_MyStationHit() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionYpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionGpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionGpPrioIntNew, 0x7, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionCosQCpuNew, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;

}


int do_per_switch_setup(int unit)
{
    int rv = BCM_E_NONE;


    /* Just an example of things that can be done. */

    /*
     * Set STP state to "forwarding" for all ports that are
     * configured for Ethernet or HiGig encapsulation.
     */
    bcm_port_config_t port_config;
    bcm_port_t port;

    bcm_port_config_get(unit, &port_config);

    BCM_PBMP_ITER(port_config.e, port) {
        BCM_IF_ERROR_RETURN(bcm_port_stp_set(unit, port, BCM_STG_STP_FORWARD));
    }

    BCM_PBMP_ITER(port_config.hg, port) {
        BCM_IF_ERROR_RETURN(bcm_port_stp_set(unit, port, BCM_STG_STP_FORWARD));
    }


    //Enable linkscan
    rv = bcm_linkscan_enable_set(unit, 250000);
    printf( "%s: bcm_inkscan_enable_set( %d ), result=%d\n",
            (rv) ? "FAIL" : "SUCCESS", unit, rv );


    BCM_PBMP_ITER(port_config.port, port) {
        int autoneg, pause_tx, pause_rx;
        BCM_IF_ERROR_RETURN(bcm_linkscan_mode_set(unit, port,
                                                BCM_LINKSCAN_MODE_SW));
        autoneg = TRUE;
        BCM_IF_ERROR_RETURN(bcm_port_autoneg_set(unit, port, autoneg));

        if (BCM_PBMP_MEMBER(port_config.hg, port)) {
            pause_tx = pause_rx = FALSE;
        } else {
            pause_tx = pause_rx = TRUE;
        }
        BCM_IF_ERROR_RETURN(bcm_port_pause_set(unit, port, pause_tx, pause_rx));
        BCM_IF_ERROR_RETURN(bcm_stat_clear(unit, port));
    }

    //Create KNET interfaces
    knet_portconfig_init(unit);

    //Initialize field processor
    //switchdev_field_processor_init(unit);
    return 0;
}

#ifdef BCM_WARM_BOOT_SUPPORT
int scache_read_dummy_f( int unit, uint8 *buf, int offset, int nbytes )
{
    return SOC_E_RESOURCE;
}

int scache_write_dummy_f( int unit, uint8 *buf, int offset, int nbytes )
{
    return SOC_E_RESOURCE;
}
#endif

#ifndef NO_SAL_APPL
#include <sal/appl/pci.h>

uint32 pci_config_getw(pci_dev_t *dev, uint32 addr)
{
#ifdef LINUX_PLI_COMBO_BDE
    extern uint32 pli_pci_config_getw(pci_dev_t *dev, uint32 addr);
    if (sim_path) {
        return pli_pci_config_getw(dev, addr);
    }
#if defined(BCM_LTSW_SUPPORT)
    if (!bde) {
        return 0xffffffff;
    }
#endif
#endif

    /* We only support our own devices */
    if (dev->busNo != 0) {
        return 0xffffffff;
    }

    if (dev->devNo >= bde->num_devices(BDE_SWITCH_DEVICES)) {
        return 0xffffffff;
    }

    return bde->pci_conf_read(dev->devNo, addr);
}
#endif /* NO_SAL_APPL */

/* switchdev netlink thread */
static int switchdev_netlink_thread_priority = 100;
static volatile sal_thread_t switchdev_netlink_thread_id        = SAL_THREAD_ERROR;

extern int switchdev_netlink_main(void);

static void
switchdev_netlink_thread(void *cookie)
{
    COMPILER_REFERENCE(cookie);

    switchdev_netlink_main();

    sal_thread_exit(0);
}

int switchdev_netlink_init(void)
{
    switchdev_netlink_thread_id = sal_thread_create("bcmATP-RX",
                                         SAL_THREAD_STKSZ,
                                         switchdev_netlink_thread_priority,
                                         switchdev_netlink_thread, NULL);
    if (switchdev_netlink_thread_id == SAL_THREAD_ERROR) {
        sal_thread_destroy(switchdev_netlink_thread_id);
        switchdev_netlink_thread_id = SAL_THREAD_ERROR;
        return BCM_E_MEMORY;
    }
    return BCM_E_NONE;
}

extern int switchdev_dstty_init(int ttyfd);


/*
 * Main loop.
 */
#ifdef LIB_SWITCHDEV
int switch_start(void) 

#else
int main( int argc, char *argv[] )
#endif
{
    int i;
    uint32 flags;
    int rv = BCM_E_NONE;
#ifdef LIB_SWITCHDEV
    int ttyfd, appfd;
#endif
#if defined(BCM_LTSW_SUPPORT)
    int cfg_file_idx = 0;
#endif

#ifdef LINUX_PLI_COMBO_BDE
    sim_path = sal_ctoi(getenv("BCM_SIM_PATH"), 0);
#endif

#ifdef LIB_SWITCHDEV

#else
#if defined(BCM_LTSW_SUPPORT)
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-y") == 0) {
            if (++i >= argc) {
                printf("No YAML configuration file specified\n");
                exit(1);
            }
            if (sysconf_ltsw_config_file_set(cfg_file_idx, argv[i]) < 0) {
                printf("Invalid YAML configuration file: %s\n", argv[i]);
                exit(1);
            }
            cfg_file_idx++;
        }
    }
#endif
#endif

    if (sal_core_init() < 0
#ifndef NO_SAL_APPL
        || sal_appl_init() < 0
#endif
        ) {
#ifndef NO_SAL_APPL
        printf( "SAL Initialization failed\r\n" );
#endif
        exit( 1 );
    }

#ifdef LIB_SWITCHDEV

#else
    for( i = 1; i < argc; i++ ){
        if( !strcmp(argv[i], "-r") || !strcmp(argv[i], "--reload") ){
            sal_boot_flags_set( sal_boot_flags_get() | BOOT_F_RELOAD );
#if defined(BCM_LTSW_SUPPORT)
        } else if (!strcmp(argv[i], "-a")) {
            if (++i >= argc) {
                printf("No path specified for storing HA state file.\n");
                exit(1);
            }
            if (sysconf_ltsw_ha_check_set(1, argv[i]) < 0) {
                printf("Can not set SDK HA check status.\n");
                exit(1);
            }
#endif
        }
    }
#endif

#ifdef INCLUDE_KNET
    knet_kcom_config();
#endif
    soc_chip_info_vect_config( &chip_info_vect );

    sal_thread_main_set( sal_thread_self() );

#ifndef NO_SAL_APPL
    bslmgmt_init();
#endif

#if defined(BCM_LTSW_SUPPORT)
    if (sysconf_ltsw_init() < 0) {
        printf("sysconf_init: LTSW initialization failed\n");
        exit(1);
    }
#endif

    soc_cm_init();

    /*
     * At boot time, probe for devices and attach the first one.
     */
    flags = sal_boot_flags_get();

#if defined(BCM_LTSW_SUPPORT)
#ifdef BCM_WARM_BOOT_SUPPORT
    if (flags & BOOT_F_WARM_BOOT) {
        sysconf_ltsw_warmboot_set(1);
    }
#endif
#endif /* BCM_LTSW_SUPPORT */

    if( !(flags & BOOT_F_NO_PROBE) ){
#if defined(BCM_LTSW_SUPPORT)
        if ((sysconf_ltsw_probe()) < 0) {
            printf("Failed to probe LTSW device\n");
        }
#endif /* BCM_LTSW_SUPPORT */
        if( _sysconf_probe() < 0 ){
            printf( "ERROR: PCI SOC device probe failed\n" );
        }

#if defined(BCM_LTSW_SUPPORT)
        if ((sysconf_ltsw_ha_init()) < 0) {
            printf("ERROR: HA initialization failed.\n");
        }
        if ((sysconf_ltsw_config_init()) < 0) {
            printf("ERROR: Config initialization failed.\n");
        }
        if ((sysconf_ltsw_core_start()) < 0) {
            printf("ERROR: ltsw device core start failed\n");
        }
        if ((sysconf_ltsw_keep_netif_set(1)) < 0) {
            printf("ERROR: ltsw keep netif set failed\n");
        }
#endif /* BCM_LTSW_SUPPORT */

        if( !(flags & BOOT_F_NO_ATTACH) ){
            for( i = 0; i < soc_all_ndev; i++ ){
                rv = _sysconf_attach( i );
                printf( "%s: soc_attach( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );

#if defined(BCM_LTSW_SUPPORT)
                if (soc_cm_get_dev_type(i) & 0x80000000) {
#ifndef NO_SAL_APPL
                    diag_rc_set(i, "ltsw.soc");
#endif
#ifdef BCM_WARM_BOOT_SUPPORT
                    if (flags & BOOT_F_WARM_BOOT) {
                        printf("Boot flags: Warm boot\n");
                        SOC_WARM_BOOT_START(i);
                        bcm_warmboot_set(i, 1);
#ifndef NO_SAL_APPL
                        diag_rc_set(i, "reload_ltsw.soc");
#endif
                    } else {
                        printf("Boot flags: Cold boot\n");
                    }
                    if ((sysconf_ltsw_ha_state_comp()) < 0) {
                        printf("ERROR: HA state comparison failed.\n");
                    }
#endif
                    rv = sysconf_ltsw_dev_init(i);
                    printf( "%s: dev_init( %d ), result=%d\n",
                            (rv) ? "FAIL" : "SUCCESS", i, rv );
                    rv = bcm_init(i);
                    printf( "%s: bcm_init( %d ), result=%d\n",
                            (rv) ? "FAIL" : "SUCCESS", i, rv );
#ifdef BCM_WARM_BOOT_SUPPORT
                    if (flags & BOOT_F_WARM_BOOT) {
                        if (!rv) {
                            printf("Warm boot successfully.\n");
                        }
                        sysconf_ltsw_warmboot_set(0);
                        SOC_WARM_BOOT_DONE(i);
                        bcm_warmboot_set(i, 0);
                    }
#endif
                    continue;
                }
#endif /* BCM_LTSW_SUPPORT */
#ifdef BCM_WARM_BOOT_SUPPORT
                SOC_WARM_BOOT_DONE( i );
                rv = soc_stable_set( i, BCM_SWITCH_STABLE_NONE, 0 );
                printf( "%s: soc_stable_set( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );

                rv = soc_stable_size_set( i, 0 );
                printf( "%s: soc_stable_size_set( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );

                rv = soc_switch_stable_register( i,
                                                 scache_read_dummy_f,
                                                 scache_write_dummy_f,
                                                 NULL, NULL );
                printf( "%s: soc_switch_stable_register( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );
#endif
#ifndef BCM_DNX_SUPPORT
                rv = soc_reset_init( i );
                printf( "%s: soc_reset_init( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );

                rv = soc_cancun_generic_load(i, CANCUN_SOC_FILE_TYPE_CMH);
                printf( "%s: soc_cancun_generic_load( %d CMH), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );

                rv = soc_cancun_generic_load(i, CANCUN_SOC_FILE_TYPE_CCH);
                printf( "%s: soc_cancun_generic_load( %d CCH), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );


                rv = soc_cancun_generic_load(i, CANCUN_SOC_FILE_TYPE_CEH);
                printf( "%s: soc_cancun_generic_load( %d CEH), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );


                rv = soc_cancun_generic_load(i, CANCUN_SOC_FILE_TYPE_CIH);
                printf( "%s: soc_cancun_generic_load( %d CIH), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );

#endif /* BCM_DNX_SUPPORT */
                rv = soc_misc_init( i );
                printf( "%s: soc_misc_init( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );
#ifndef BCM_DNX_SUPPORT
                rv = soc_mmu_init( i );
                printf( "%s: soc_mmu_init( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );
#endif /* BCM_DNX_SUPPORT */
                rv = bcm_attach( i, NULL, NULL, i );
                printf( "%s: bcm_attach( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );
#ifdef BCM_DNX_SUPPORT
#ifndef NO_SAL_APPL
                soc_mem_config_set = sal_config_set;
                rv = diag_rc_load(i);
                printf( "%s: diag_rc_load( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );
#endif /* NO_SAL_APPL */
#endif /* BCM_DNX_SUPPORT */
                rv = bcm_init( i );
                printf( "%s: bcm_init( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );

                printf( "Unit=%d completed initialization.\n", i );
#ifndef BCM_DNX_SUPPORT
                rv = do_per_switch_setup( i );
                printf( "%s: do_per_switch_setup( %d ), result=%d\n",
                        (rv) ? "FAIL" : "SUCCESS", i, rv );
#endif /* BCM_DNX_SUPPORT */
                printf( "Unit=%d completed configuration.\n", i );
            }
        } else {
            printf( "Boot flags: Attach NOT performed\n" );
        }
    } else {
        printf( "Boot flags: Probe NOT performed\n" );
    }

    /* Initialize diag shell so we can use it later on. */
    diag_init();
    cmdlist_init();

    /* Initialize netlink to switchdev kernel module */
    switchdev_netlink_init();

#ifdef LIB_SWITCHDEV
    /* Get a pseudo tty */
    if (openpty(&ttyfd, &appfd, NULL, NULL, NULL) < 0) {
        printf("open pty: %s", strerror(errno));
    }
    switchdev_dstty_init(ttyfd);
    printf("switchdev_dstty_init done, redirecting appfd\n");

    /* redirect appfd */
    dup2(appfd, 0);
    dup2(appfd, 1);
    dup2(appfd, 2);    
#endif

    while (1) {
        sh_process(-1, "BCM", TRUE);

#if defined(BCM_LTSW_SUPPORT)
        if (sysconf_ltsw_cleanup() < 0) {
            printf("Failed to do the SDK cleanup.\n");
        }
        if (sysconf_ltsw_ha_deinit() < 0) {
            printf("Failed to do the HA cleanup.\n");
        }
#endif

        break;
    }

    linux_bde_destroy( bde );
    return 0;
}

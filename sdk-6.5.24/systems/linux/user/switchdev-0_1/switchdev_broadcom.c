#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/queue.h>

#include <net/if.h>
#include <arpa/inet.h>

#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <fcntl.h>
#include <linux/netdevice.h>
#include <linux/if_bridge.h>
#include <pthread.h>
#include <pty.h>

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
#include <bcm/l2.h>

#if defined(BCM_LTSW_SUPPORT)
#include <appl/diag/sysconf_ltsw.h>
#endif

#include <opennsa/l2.h>
#include <opennsa/link.h>
#include <opennsa/l3.h>
#include <opennsa/range.h>

#include "switchdev.h"
#include "switchdev_utils.h"

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

bcm_mac_t system_mac;

static int switchdev_fp_add_l3forus_entry(int unit,
                                          bcm_field_group_t group,
                                          bcm_field_entry_t eid,
                                          bcm_policer_t policerId,
                                          int statid) 
{
    bcm_error_t   rv = BCM_E_NONE;
    bcm_pbmp_t    pbm, pbm_mask;     

    rv = bcm_field_entry_create_id(unit, group, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    
    rv = bcm_field_entry_prio_set(unit, eid, 0x4);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_prio_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    //Remove CPU 
    BCM_PBMP_CLEAR(pbm_mask);
    BCM_PBMP_CLEAR(pbm);
    BCM_PBMP_PORT_SET(pbm_mask, 0);
    rv = bcm_field_qualify_InPorts(unit, eid, pbm, pbm_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_InPorts() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_qualify_DstClassL3(unit, eid, 0x1, 0x1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_MyStationHit() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionCosQCpuNew, 0x1, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionPrioIntNew, 0x7, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }    
    
    rv = bcm_field_action_add(unit, eid, bcmFieldActionGpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    
    rv = bcm_field_action_add(unit, eid, bcmFieldActionRpDrop, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* attach policer and stats*/
    rv = bcm_field_entry_policer_attach(unit, eid, 0, policerId);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach policer for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }

    rv = bcm_field_entry_stat_attach(unit, eid, statid);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach stat for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }
    /* install and enable entry*/
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_entry_enable_set(unit, eid, 1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_enable_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    return rv;
}

static int switchdev_fp_add_arp_entry(int unit,
                                          bcm_field_group_t group,
                                          bcm_field_entry_t eid,
                                          bcm_mac_t mac_addr,
                                          bcm_mac_t mac_mask,
                                          bcm_field_IpType_t iptype,
                                          bcm_policer_t policerId,
                                          int statid) 
{
    bcm_error_t   rv = BCM_E_NONE;
    bcm_pbmp_t    pbm, pbm_mask;     

    rv = bcm_field_entry_create_id(unit, group, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_entry_prio_set(unit, eid, 0x4);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_prio_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_DstMac(unit, eid, mac_addr, mac_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_EtherType() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    //Remove CPU 
    BCM_PBMP_CLEAR(pbm_mask);
    BCM_PBMP_CLEAR(pbm);
    BCM_PBMP_PORT_SET(pbm_mask, 0);
    rv = bcm_field_qualify_InPorts(unit, eid, pbm, pbm_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_InPorts() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_qualify_EtherType(unit, eid, 0x00000806, 0x0000ffff);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_EtherType() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_IpType(unit, eid, iptype);
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
    rv = bcm_field_action_add(unit, eid, bcmFieldActionCosQCpuNew, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionPrioIntNew, 0x7, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionGpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionYpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* attach policer and stats*/
    rv = bcm_field_entry_policer_attach(unit, eid, 0, policerId);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach policer for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }

    rv = bcm_field_entry_stat_attach(unit, eid, statid);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach stat for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }
    /* install and enable entry*/
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_entry_enable_set(unit, eid, 1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_enable_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    return rv;
}


static int switchdev_fp_add_icmpv6_entry(int unit,
                                          bcm_field_group_t group,
                                          bcm_field_entry_t eid,
                                          bcm_policer_t policerId,
                                          int statid) 
{
    bcm_error_t         rv = BCM_E_NONE;
    bcm_pbmp_t          pbm, pbm_mask;
    bcm_port_config_t   port_config;
    bcm_range_config_t  range_config;

    rv = bcm_field_entry_create_id(unit, group, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_entry_prio_set(unit, eid, 0x4);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_prio_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    //Remove CPU 
    BCM_PBMP_CLEAR(pbm_mask);
    BCM_PBMP_CLEAR(pbm);
    BCM_PBMP_PORT_SET(pbm_mask, 0);
    rv = bcm_field_qualify_InPorts(unit, eid, pbm, pbm_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_InPorts() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    /* Range Check Configuration and Creation */
    bcm_switch_control_set(unit,bcmSwitchRangeCheckersAPIType, 1);
    /* Setting the Operational mode to PipeGlobal Mode */
    bcm_range_oper_mode_set(unit, bcmRangeOperModeGlobal);

    bcm_port_config_get(unit, &port_config);

    bcm_range_config_t_init(&range_config);
    range_config.rtype = bcmRangeTypeL4SrcPort;
    range_config.rid = 1;
    range_config.min = 0x8500;
    range_config.max = 0x8900;
    range_config.ports = port_config.all;    // bcmRangeOperModeGlobal

    rv = bcm_range_create(unit, BCM_RANGE_CREATE_WITH_ID, &range_config);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_range_create : %s\n", bcm_errmsg(rv));
    }

    rv = bcm_field_qualify_RangeCheck(unit, eid, range_config.rid, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_RangeCheck() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_EtherType(unit, eid, 0x000086dd, 0x0000ffff);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_EtherType() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_IpProtocol(unit, eid, 0x0000003a, 0x000000ff);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_IpProtocol() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_Ttl(unit, eid, 0x000000ff, 0x000000ff);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_Ttl() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_InterfaceClassL2(unit, eid, 0x1, 0x1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_MyStationHit() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionCosQCpuNew, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionPrioIntNew, 0x7, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionGpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionYpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* attach policer and stats*/
    rv = bcm_field_entry_policer_attach(unit, eid, 0, policerId);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach policer for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }

    rv = bcm_field_entry_stat_attach(unit, eid, statid);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach stat for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }
    /* install and enable entry*/
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_entry_enable_set(unit, eid, 1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_enable_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    return rv;
}

static int switchdev_fp_add_lldp_entry(int unit,
                                          bcm_field_group_t group,
                                          bcm_field_entry_t eid,
                                          bcm_mac_t mac_addr,
                                          bcm_mac_t mac_mask,                                          
                                          bcm_policer_t policerId,
                                          int statid) 
{
    bcm_error_t   rv = BCM_E_NONE;
    bcm_pbmp_t    pbm, pbm_mask;     

    rv = bcm_field_entry_create_id(unit, group, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_entry_prio_set(unit, eid, 0x4);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_prio_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_DstMac(unit, eid, mac_addr, mac_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_EtherType() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    //Remove CPU 
    BCM_PBMP_CLEAR(pbm_mask);
    BCM_PBMP_CLEAR(pbm);
    BCM_PBMP_PORT_SET(pbm_mask, 0);
    rv = bcm_field_qualify_InPorts(unit, eid, pbm, pbm_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_InPorts() : %s\n", bcm_errmsg(rv));
        return rv;
    }    


    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionCosQCpuNew, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionPrioIntNew, 0x7, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionGpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionUnmodifiedPacketRedirectPort, 0x8000000, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionRpDrop, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }    
    /* attach policer and stats*/
    rv = bcm_field_entry_policer_attach(unit, eid, 0, policerId);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach policer for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }

    rv = bcm_field_entry_stat_attach(unit, eid, statid);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach stat for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }
    /* install and enable entry*/
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_entry_enable_set(unit, eid, 1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_enable_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    return rv;
}



static int switchdev_fp_add_dhcp_reply_entry(int unit,
                                          bcm_field_group_t group,
                                          bcm_field_entry_t eid,
                                          bcm_mac_t mac_addr,
                                          bcm_mac_t mac_mask,                                          
                                          bcm_policer_t policerId,
                                          int statid) 
{
    bcm_error_t   rv = BCM_E_NONE;
    bcm_pbmp_t    pbm, pbm_mask;     

    rv = bcm_field_entry_create_id(unit, group, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_entry_prio_set(unit, eid, 0x4);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_prio_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_DstMac(unit, eid, mac_addr, mac_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_EtherType() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_qualify_L4DstPort(unit, eid, 0x44, 0xffff);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_L4DstPort() : %s\n", bcm_errmsg(rv));
        return rv;
    }    
    rv = bcm_field_qualify_L4SrcPort(unit, eid, 0x43, 0xffff);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_L4SrcPort() : %s\n", bcm_errmsg(rv));
        return rv;
    }      

    //Remove CPU 
    BCM_PBMP_CLEAR(pbm_mask);
    BCM_PBMP_CLEAR(pbm);
    BCM_PBMP_PORT_SET(pbm_mask, 0);
    rv = bcm_field_qualify_InPorts(unit, eid, pbm, pbm_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_InPorts() : %s\n", bcm_errmsg(rv));
        return rv;
    }    


    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionCosQCpuNew, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionPrioIntNew, 0x7, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionGpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_action_add(unit, eid, bcmFieldActionYpCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* attach policer and stats*/
    rv = bcm_field_entry_policer_attach(unit, eid, 0, policerId);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach policer for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }

    rv = bcm_field_entry_stat_attach(unit, eid, statid);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach stat for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }
    /* install and enable entry*/
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_entry_enable_set(unit, eid, 1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_enable_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    return rv;
}

static int switchdev_fp_init_ingress(int unit)
{
    bcm_error_t              rv = BCM_E_NONE;
    bcm_field_group_config_t group_config;
    bcm_field_entry_t        eid;
    //bcm_vlan_t vlan = 2, vlan_mask = 0xfff;
    bcm_port_t               port = 0; //port_mask = 0xffffffff;
    bcm_mac_t                mac_mask = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    bcm_mac_t                lldp_mac = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x00};
    bcm_mac_t                cdp_mac = {0x01, 0x00, 0x0c, 0xcc, 0xcc, 0xcc};
    bcm_policer_t            policerId;
    bcm_policer_config_t     pol_cfg;    
    bcm_field_stat_t         stat_arr[9];
    int                      stat_arr_sz;     
    int                      statid = -1;
    //int prio;

    /* Enable IFP for CPU port */
    rv = bcm_port_control_set(unit, port, bcmPortControlFilterIngress, 1);

    /* FP group configuration and creation */
    bcm_field_group_config_t_init(&group_config);

    BCM_FIELD_QSET_INIT(group_config.qset);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyDstMac);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyDstIp);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyInPorts);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyRangeCheck);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyL4SrcPort);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyL4DstPort);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyEtherType);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyIpProtocol);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyTtl);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyPacketRes);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyDstClassL3);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyIpInfo);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyIpType);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyStage);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyStageIngress);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyInterfaceClassL2);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyTunnelTerminated);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyL3DestRouteHit);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyDstL3Egress);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyMyStationHit);

    group_config.mode = bcmFieldGroupModeAuto;
    group_config.priority = -3;

    /* Set group gid value and flag bit */
    group_config.flags |= BCM_FIELD_GROUP_CREATE_WITH_ID;
    group_config.group = 1;    

    rv = bcm_field_group_config_create(unit, &group_config);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_group_config_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* FP entry configuration and creation */
    /*************************************************************************************/
    /* Layer3 Forus                                                                      */
    /*************************************************************************************/
    //Create Policer for Layer3 Forus
    bcm_policer_config_t_init(&pol_cfg);

    pol_cfg.ckbits_sec = 6000;
    pol_cfg.ckbits_burst = 0;
    pol_cfg.pkbits_sec = 6000;
    pol_cfg.pkbits_burst = 0;
    pol_cfg.mode = bcmPolicerModeSrTcm;
    pol_cfg.flags |= BCM_POLICER_MODE_PACKETS;
        
    pol_cfg.action_id = 0;
        
    rv = bcm_policer_create(unit, &pol_cfg, &policerId);
    if (rv != BCM_E_NONE) {
            printf("Failed to create policer for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }
        

    //Create Stats for ARP reuest/reply
    stat_arr[0] = bcmFieldStatBytes;
    stat_arr[1] = bcmFieldStatPackets;
    stat_arr[2] = bcmFieldStatGreenBytes;
    stat_arr[3] = bcmFieldStatGreenPackets;
    stat_arr[4] = bcmFieldStatYellowBytes;
    stat_arr[5] = bcmFieldStatYellowPackets;
    stat_arr[6] = bcmFieldStatRedBytes;
    stat_arr[7] = bcmFieldStatRedPackets;
    stat_arr_sz = 8;

    rv = bcm_field_stat_create(unit, group_config.group, stat_arr_sz, stat_arr, &statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create stat for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }

    // EID 0x0a, DstClassL3
    eid = 0x0a;
    rv = switchdev_fp_add_l3forus_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create ARP Request entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }   

    /*************************************************************************************/
    /* ARP                                                                               */
    /*************************************************************************************/
    //Create Policer for ARP request/reply
    bcm_policer_config_t_init(&pol_cfg);

    pol_cfg.ckbits_sec = 600;
    pol_cfg.ckbits_burst = 0;
    pol_cfg.pkbits_sec = 600;
    pol_cfg.pkbits_burst = 0;
    pol_cfg.mode = bcmPolicerModeSrTcm;
    pol_cfg.flags |= BCM_POLICER_MODE_PACKETS;
        
    pol_cfg.action_id = 0;
        
    rv = bcm_policer_create(unit, &pol_cfg, &policerId);
    if (rv != BCM_E_NONE) {
            printf("Failed to create policer for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }
        

    //Create Stats for ARP reuest/reply
    stat_arr[0] = bcmFieldStatBytes;
    stat_arr[1] = bcmFieldStatPackets;
    stat_arr[2] = bcmFieldStatGreenBytes;
    stat_arr[3] = bcmFieldStatGreenPackets;
    stat_arr[4] = bcmFieldStatYellowBytes;
    stat_arr[5] = bcmFieldStatYellowPackets;
    stat_arr[6] = bcmFieldStatRedBytes;
    stat_arr[7] = bcmFieldStatRedPackets;
    stat_arr_sz = 8;

    rv = bcm_field_stat_create(unit, group_config.group, stat_arr_sz, stat_arr, &statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create stat for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }


    // EID 0x10, ARP request
    eid = 0x10;
    rv = switchdev_fp_add_arp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    mac_mask, 
                                    mac_mask, 
                                    bcmFieldIpTypeArpRequest,
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create ARP Request entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }
    // EID 0x11, ARP request forus                               
    eid = 0x11;
    rv = switchdev_fp_add_arp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    system_mac, 
                                    mac_mask, 
                                    bcmFieldIpTypeArpRequest,
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create ARP Request entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }        

    // EID 0x13, ARP reply
    eid = 0x13;
    rv = switchdev_fp_add_arp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    mac_mask, 
                                    mac_mask, 
                                    bcmFieldIpTypeArpReply,
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create ARP Reply entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }
    // EID 0x14, ARP reply
    eid = 0x14;
    rv = switchdev_fp_add_arp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    system_mac, 
                                    mac_mask, 
                                    bcmFieldIpTypeArpReply,
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create ARP Reply entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }
    // EID 0x15, IPV6 ICMP
    eid = 0x15;
    rv = switchdev_fp_add_icmpv6_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create ARP Reply entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }
    /*************************************************************************************/
    /* LLDP                                                                              */
    /*************************************************************************************/ 
   //Create Policer for LLDP request/reply
    bcm_policer_config_t_init(&pol_cfg);

    pol_cfg.ckbits_sec = 100;
    pol_cfg.ckbits_burst = 0;
    pol_cfg.pkbits_sec = 100;
    pol_cfg.pkbits_burst = 0;
    pol_cfg.mode = bcmPolicerModeSrTcm;
    pol_cfg.flags |= BCM_POLICER_MODE_PACKETS;
        
    pol_cfg.action_id = 0;
        
    rv = bcm_policer_create(unit, &pol_cfg, &policerId);
    if (rv != BCM_E_NONE) {
            printf("Failed to create policer for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }
        

    //Create Stats for LLDP reuest/reply
    stat_arr[0] = bcmFieldStatBytes;
    stat_arr[1] = bcmFieldStatPackets;
    stat_arr[2] = bcmFieldStatGreenBytes;
    stat_arr[3] = bcmFieldStatGreenPackets;
    stat_arr[4] = bcmFieldStatYellowBytes;
    stat_arr[5] = bcmFieldStatYellowPackets;
    stat_arr[6] = bcmFieldStatRedBytes;
    stat_arr[7] = bcmFieldStatRedPackets;
    stat_arr_sz = 8;

    rv = bcm_field_stat_create(unit, group_config.group, stat_arr_sz, stat_arr, &statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create stat for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }


    // EID 0x16, LLDP 01:80:c2:00:00:00
    eid = 0x16;
    rv = switchdev_fp_add_lldp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    lldp_mac,
                                    mac_mask, 
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create ARP Request entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }    

    // EID 0x17, LLDP 01:80:c2:00:00:03
    eid = 0x17;
    lldp_mac[5] = 0x03;
    rv = switchdev_fp_add_lldp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    lldp_mac,
                                    mac_mask, 
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create ARP Request entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }    
    
    // EID 0x18, LLDP 01:80:c2:00:00:0e
    eid = 0x18;
    lldp_mac[5] = 0x0e;
    rv = switchdev_fp_add_lldp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    lldp_mac,
                                    mac_mask, 
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create ARP Request entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }    
    // EID 0x19, LLDP 01:00:0c:cc:cc:cc  (CDP)
    eid = 0x19;
    rv = switchdev_fp_add_lldp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    cdp_mac,
                                    mac_mask, 
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create ARP Request entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }    

    /*************************************************************************************/
    /* DHCP                                                                              */
    /*************************************************************************************/ 
   //Create Policer for LLDP request/reply
    bcm_policer_config_t_init(&pol_cfg);

    pol_cfg.ckbits_sec = 600;
    pol_cfg.ckbits_burst = 0;
    pol_cfg.pkbits_sec = 600;
    pol_cfg.pkbits_burst = 0;
    pol_cfg.mode = bcmPolicerModeSrTcm;
    pol_cfg.flags |= BCM_POLICER_MODE_PACKETS;
        
    pol_cfg.action_id = 0;
        
    rv = bcm_policer_create(unit, &pol_cfg, &policerId);
    if (rv != BCM_E_NONE) {
            printf("Failed to create policer for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }
        

    //Create Stats for LLDP reuest/reply
    stat_arr[0] = bcmFieldStatBytes;
    stat_arr[1] = bcmFieldStatPackets;
    stat_arr[2] = bcmFieldStatGreenBytes;
    stat_arr[3] = bcmFieldStatGreenPackets;
    stat_arr[4] = bcmFieldStatYellowBytes;
    stat_arr[5] = bcmFieldStatYellowPackets;
    stat_arr[6] = bcmFieldStatRedBytes;
    stat_arr[7] = bcmFieldStatRedPackets;
    stat_arr_sz = 8;

    rv = bcm_field_stat_create(unit, group_config.group, stat_arr_sz, stat_arr, &statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create stat for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }

    // EID 0x20, DHCP sysmac
    eid = 0x20;
    rv = switchdev_fp_add_dhcp_reply_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    system_mac,
                                    mac_mask, 
                                    policerId,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create DHCP entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }   

    
    return rv;
}


static int switchdev_fp_add_inject_entry(int unit,
                                          bcm_field_group_t group,
                                          bcm_field_entry_t eid,
                                          bcm_mac_t src_mac,
                                          bcm_mac_t mac_mask,                                          
                                          int statid) 
{
    bcm_error_t   rv = BCM_E_NONE;  

    rv = bcm_field_entry_create_id(unit, group, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_entry_prio_set(unit, eid, 0x7fffffff);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_prio_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    //Inport = cpu0 
    rv = bcm_field_qualify_InPort(unit, eid, 0x0, 0xff);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_InPort() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_SrcMac(unit, eid, src_mac, mac_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_SrcMac() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionDoNotLearn, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* attach stats*/
    rv = bcm_field_entry_stat_attach(unit, eid, statid);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach stat for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }
    /* install and enable entry*/
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_entry_enable_set(unit, eid, 1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_enable_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    return rv;
}


static int switchdev_fp_add_inject_lldp_entry(int unit,
                                          bcm_field_group_t group,
                                          bcm_field_entry_t eid,
                                          bcm_mac_t src_mac,
                                          bcm_mac_t mac_mask,                                          
                                          int statid) 
{
    bcm_error_t   rv = BCM_E_NONE;
    bcm_mac_t     lldp_mac = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x00};      
    bcm_mac_t     lldp_mask = {0xff, 0xff, 0xff, 0xff, 0xff, 0xf0};   

    rv = bcm_field_entry_create_id(unit, group, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_entry_prio_set(unit, eid, 0x7ffffffe);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_prio_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_DstMac(unit, eid, lldp_mac, lldp_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_SrcMac() : %s\n", bcm_errmsg(rv));
        return rv;
    }   

    rv = bcm_field_qualify_SrcMac(unit, eid, src_mac, mac_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_SrcMac() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionDoNotLearn, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionDoNotCheckVlan, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* attach stats*/
    rv = bcm_field_entry_stat_attach(unit, eid, statid);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach stat for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }
    /* install and enable entry*/
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_entry_enable_set(unit, eid, 1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_enable_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    return rv;
}


static int switchdev_fp_add_lookup_lldp_entry(int unit,
                                          bcm_field_group_t group,
                                          bcm_field_entry_t eid,                                      
                                          bcm_mac_t lldp_mac,
                                          bcm_mac_t lldp_mask,
                                          int statid) 
{
    bcm_error_t   rv = BCM_E_NONE;

    rv = bcm_field_entry_create_id(unit, group, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_entry_prio_set(unit, eid, 0x7ffffffc);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_prio_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_DstMac(unit, eid, lldp_mac, lldp_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_SrcMac() : %s\n", bcm_errmsg(rv));
        return rv;
    }   

    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionDoNotLearn, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, eid, bcmFieldActionDoNotCheckVlan, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* attach stats*/
    rv = bcm_field_entry_stat_attach(unit, eid, statid);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach stat for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }
    /* install and enable entry*/
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_entry_enable_set(unit, eid, 1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_enable_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    return rv;
}


static int switchdev_fp_add_lookup_sysmac_entry(int unit,
                                          bcm_field_group_t group,
                                          bcm_field_entry_t eid,   
                                          bcm_mac_t src_mac,
                                          bcm_mac_t mac_mask, 
                                          int statid) 
{
    bcm_error_t   rv = BCM_E_NONE;

    rv = bcm_field_entry_create_id(unit, group, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_entry_prio_set(unit, eid, 0x7ffffffd);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_prio_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_SrcMac(unit, eid, src_mac, mac_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_SrcMac() : %s\n", bcm_errmsg(rv));
        return rv;
    }   

    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, eid, bcmFieldActionDoNotLearn, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* attach stats*/
    rv = bcm_field_entry_stat_attach(unit, eid, statid);
    if (rv != BCM_E_NONE) {
        printf("Failed to attach stat for unit: %d, entry %d Error:%s (%d)\r\n",
                unit, eid,  bcm_errmsg (rv), rv);
        return rv;
    }
    /* install and enable entry*/
    rv = bcm_field_entry_install(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    rv = bcm_field_entry_enable_set(unit, eid, 1);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_enable_set() : %s\n", bcm_errmsg(rv));
        return rv;
    }    

    return rv;
}


static int switchdev_fp_init_lookup(int unit)
{
    bcm_error_t              rv = BCM_E_NONE;
    bcm_field_group_config_t group_config;
    bcm_field_entry_t        eid;
    //bcm_vlan_t vlan = 2, vlan_mask = 0xfff;
    bcm_mac_t                mac_mask = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    bcm_mac_t                cdp_mac = {0x01, 0x00, 0x0c, 0xcc, 0xcc, 0xc0};
    bcm_mac_t                lldp_mac = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x00};      
    bcm_mac_t                lldp_mask = {0xff, 0xff, 0xff, 0xff, 0xff, 0xf0};       
    bcm_field_stat_t         stat_arr[9];
    int                      stat_arr_sz;     
    int                      statid = -1;
    //int prio;

    /* FP group configuration and creation */
    bcm_field_group_config_t_init(&group_config);

    BCM_FIELD_QSET_INIT(group_config.qset);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifySrcMac);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyDstMac);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyInPort);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyEtherType);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyStageLookup);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyIpFrag);

    group_config.mode = bcmFieldGroupModeAuto;
    group_config.priority = -0x7FFFFFFF;

    /* Set group gid value and flag bit */
    group_config.flags |= BCM_FIELD_GROUP_CREATE_WITH_ID;
    group_config.group = 2;    

    rv = bcm_field_group_config_create(unit, &group_config);
    if(BCM_FAILURE(rv)) {
        printf("\nFail to create FP group %d : %s\n",group_config.group, bcm_errmsg(rv));
        return rv;
    }

    /* FP entry configuration and creation */
    /*************************************************************************************/
    /* Inject from Host MAC                                                              */
    /*************************************************************************************/
    //Create Stats for inject
    stat_arr[0] = bcmFieldStatPackets;
    stat_arr_sz = 1;

    rv = bcm_field_stat_create(unit, group_config.group, stat_arr_sz, stat_arr, &statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create stat for ARP unit: %d, fp group %d Error:%s (%d)\r\n",
                unit, group_config.group, bcm_errmsg (rv), rv);
            return rv;
    }

    // EID 0x03
    eid = 0x03;
    rv = switchdev_fp_add_inject_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    system_mac,
                                    mac_mask,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create inject entry %d unit: %d, Error:%s (%d)\r\n",
                    eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }   

    /*************************************************************************************/
    /* LLDP                                                                              */
    /*************************************************************************************/ 
    // EID 0x4, LLDP , src MAC = system_mac
    //Create Stats 
    stat_arr[0] = bcmFieldStatPackets;
    stat_arr_sz = 1;

    rv = bcm_field_stat_create(unit, group_config.group, stat_arr_sz, stat_arr, &statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create stat for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }    
    eid = 0x4;
    rv = switchdev_fp_add_inject_lldp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    system_mac,
                                    mac_mask, 
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create LLDP inject entry group %d eid %d unit: %d, Error:%s (%d)\r\n",
                    group_config.group, eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }    

    // EID 0x5, LLDP , src MAC = system_mac
    //Create Stats 
    stat_arr[0] = bcmFieldStatPackets;
    stat_arr_sz = 1;

    rv = bcm_field_stat_create(unit, group_config.group, stat_arr_sz, stat_arr, &statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create stat for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }        
    eid = 0x5;
    rv = switchdev_fp_add_lookup_sysmac_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    system_mac,
                                    mac_mask, 
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create LLDP inject entry group %d eid %d unit: %d, Error:%s (%d)\r\n",
                    group_config.group, eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }    

    // EID 0x6, LLDP lookup
    //Create Stats 
    stat_arr[0] = bcmFieldStatPackets;
    stat_arr_sz = 1;

    rv = bcm_field_stat_create(unit, group_config.group, stat_arr_sz, stat_arr, &statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create stat for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }        
    eid = 0x6;
    rv = switchdev_fp_add_lookup_lldp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    lldp_mac,
                                    lldp_mask,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create LLDP inject entry group %d eid %d unit: %d, Error:%s (%d)\r\n",
                    group_config.group, eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }    

    // EID 0x7, CDP lookup
    //Create Stats 
    stat_arr[0] = bcmFieldStatPackets;
    stat_arr_sz = 1;

    rv = bcm_field_stat_create(unit, group_config.group, stat_arr_sz, stat_arr, &statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create stat for ARP unit: %d, Error:%s (%d)\r\n",
                unit,  bcm_errmsg (rv), rv);
            return rv;
    }        
    eid = 0x7;
    rv = switchdev_fp_add_lookup_lldp_entry(unit, 
                                    group_config.group, 
                                    eid, 
                                    cdp_mac,
                                    lldp_mask,
                                    statid);
    if (rv != BCM_E_NONE) {
            printf("Failed to create LLDP inject entry group %d eid %d unit: %d, Error:%s (%d)\r\n",
                    group_config.group, eid, unit,  bcm_errmsg (rv), rv);
            return rv;
    }    

    return rv;
}

int switchdev_field_processor_init(int unit)
{
    bcm_error_t              rv = BCM_E_NONE;

    rv = switchdev_fp_init_ingress(unit);
    if (rv != BCM_E_NONE) {
        printf("Failed to ingress Stage FP unit: %d, Error:%s (%d)\r\n",
               unit,  bcm_errmsg (rv), rv);
        return rv;
    }    

    rv = switchdev_fp_init_lookup(unit);
    if (rv != BCM_E_NONE) {
        printf("Failed to Lookup Stage FP unit: %d, Error:%s (%d)\r\n",
               unit,  bcm_errmsg (rv), rv);
        return rv;
    }        
    return rv;
}


int do_per_switch_setup(int unit)
{
    int rv = BCM_E_NONE;

    //Enable linkscan
    rv = bcm_linkscan_enable_set(unit, 250000);
    printf( "%s: bcm_inkscan_enable_set( %d ), result=%d\n",
            (rv) ? "FAIL" : "SUCCESS", unit, rv );

    /* setup cpu port*/
    bcm_port_control_set(unit, 0, bcmPortControlL2Learn, BCM_PORT_LEARN_FWD);
    bcm_port_control_set(unit, 0, bcmPortControlL2Move, BCM_PORT_LEARN_FWD);
    bcm_port_control_set(unit, 0, bcmPortControlIP4, TRUE);
    bcm_port_control_set(unit, 0, bcmPortControlForwardStaticL2MovePkt, TRUE);

    bcm_switch_control_set(unit, bcmSwitchL3EgressMode, 1);
    bcm_switch_control_set(unit, bcmSwitchL3IngressMode, 1);
    bcm_switch_control_set(unit, bcmSwitchIpmcSameVlanL3Route, 1);
    bcm_switch_control_set(unit, bcmSwitchL3IngressInterfaceMapSet, 1);
    bcm_switch_control_set(unit, bcmSwitchL2DstHitEnable, 0);

    //Initialize field processor
    switchdev_field_processor_init(unit);
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

/* broadcom switch main thread */
static int switchdev_broadcom_thread_priority = 100;
static volatile sal_thread_t switchdev_broadcom_thread_id        = SAL_THREAD_ERROR;

static void
switchdev_broadcom_thread(void *cookie)
{
    COMPILER_REFERENCE(cookie);

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
    sal_thread_exit(0);
}

static int switchdev_broadcom_init(void)
{
    switchdev_broadcom_thread_id = sal_thread_create("Main",
                                         SAL_THREAD_STKSZ,
                                         switchdev_broadcom_thread_priority,
                                         switchdev_broadcom_thread, NULL);
    if (switchdev_broadcom_thread_id == SAL_THREAD_ERROR) {
        sal_thread_destroy(switchdev_broadcom_thread_id);
        switchdev_broadcom_thread_id = SAL_THREAD_ERROR;
        return BCM_E_MEMORY;
    }
    sal_thread_main_set(switchdev_broadcom_thread_id);
    return BCM_E_NONE;
}


int SwitchdevCreateSwitch(int unit, uint8_t sysmac[6])
{
    //create a switch object, and do init
    int i;
    uint32 flags;
    int rv = BCM_E_NONE;
#if defined(BCM_LTSW_SUPPORT)
    int cfg_file_idx = 0;
#endif

    memcpy(system_mac, sysmac, 6);

    sal_config_file_set("/etc/bcm/config.bcm", "/etc/bcm/config.tmp");

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

#if 0
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

    knet_kcom_config();

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

    //create thread for bcmshell processing
    switchdev_broadcom_init();

    return 0;
}



static int switchdev_l3_port_init(IfParam *param, int *l3_intf_id)
{
    bcm_l2_station_t         l2_station;
    int                      station_id;
    bcm_if_t                 ingress_if_egr;
    bcm_l3_ingress_t         l3_ingress;
    bcm_l3_intf_t            l3_intf;
    bcm_error_t              rv       = BCM_E_NONE;        
    bcm_mac_t                mac_mask = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    /* L2 station */
    bcm_l2_station_t_init(&l2_station);
    memcpy(l2_station.dst_mac, param->Mac, 6);
    memcpy(l2_station.dst_mac_mask, mac_mask, 6);
    l2_station.flags        = BCM_L2_STATION_IPV4 | BCM_L2_STATION_IPV6 | BCM_L2_STATION_ARP_RARP | BCM_L2_STATION_MPLS; 
    l2_station.vlan         = param->VlanId;
    l2_station.vlan_mask    = 0xfff;
    l2_station.src_port     = param->HalPort;
    l2_station.src_port_mask = 0x00ff;

    rv = bcm_l2_station_add(param->Unit, &station_id, &l2_station);
	if (BCM_E_NONE != rv) {
			printf("bcm_l2_station_add failed %s\n", bcm_errmsg(rv));
			return rv;
	}
    /* L3 Interface */
    bcm_l3_intf_t_init(&l3_intf);
    memcpy(l3_intf.l3a_mac_addr, param->Mac,6);
    l3_intf.l3a_vid = param->VlanId;
    l3_intf.l3a_vrf = 0;
    //l3_intf.l3a_flags |= BCM_L3_ADD_TO_ARL;
    rv = bcm_l3_intf_create(param->Unit, &l3_intf);
    if (BCM_FAILURE(rv)) {
       printf("Perf: Create L3 intf failed: %s\n", bcm_errmsg(rv));
       return rv;
    }
    
    /*
     * Use the same ID to allocate the ingress interface (L3_IIF)
     * (This is really not needed for L3MPLS init, since we only need
     *  to use EGR_L3_INTF to create the tunnel)
     */
    ingress_if_egr = l3_intf.l3a_intf_id;

    bcm_l3_ingress_t_init(&l3_ingress);
    l3_ingress.flags = BCM_L3_INGRESS_REPLACE;
    l3_ingress.vrf  = 0;
    l3_ingress.ipmc_intf_id  = ingress_if_egr;
    rv = bcm_l3_ingress_create(param->Unit, &l3_ingress, &ingress_if_egr);
    if (BCM_FAILURE(rv)) {
       printf("Perf: Create L3 ingress intf failed: %s\n", bcm_errmsg(rv));
       return rv;
    }

    /* set port.l3_iif to ingress_if_egr */
    rv = bcm_port_control_set(param->Unit, param->HalPort, bcmPortControlL3Ingress, ingress_if_egr);
    if (BCM_FAILURE(rv)) {
       printf("l3_port_init bcmPortControlL3Ingress port %d if_egr %d failed: %s\n", 
               param->HalPort, ingress_if_egr, bcm_errmsg(rv));
       return rv;
    }

    *l3_intf_id = l3_intf.l3a_intf_id;

    return rv;
}


int SwitchdevCreateVlan(int unit, int vid, int ifclass, bool blockbroadcast)
{
    int                      rc   = 0;
    bcm_vlan_control_vlan_t  vlan_control;
    bcm_port_config_t        port_config;
    bcm_vlan_block_t         vlan_block;

    rc = bcm_vlan_create(unit,vid);

    if(rc) {
        if (rc != BCM_E_EXISTS) {
            printf("SwitchdevCreateVlan failed to create vlan %d rc %d\n",vid, rc);
        } else {
            return 0;
        }
        return rc;
    }
    
    //Set if_class if not 0(default)
    if (ifclass) {
        bcm_vlan_control_vlan_get(unit, vid, &vlan_control);
        vlan_control.if_class = ifclass;
        bcm_vlan_control_vlan_set(unit, vid, vlan_control);
    }

    //set vlan block
    if (blockbroadcast) {
        bcm_port_config_get(unit, &port_config); 

        bcm_vlan_block_t_init(&vlan_block);
        vlan_block.unknown_multicast = port_config.all; 
        vlan_block.unknown_unicast   = port_config.all; 
        vlan_block.broadcast         = port_config.all;    
        bcm_vlan_block_set(unit, vid, &vlan_block);
    }

    return rc;
}

static int swtichdevUpdateIntfPhysical(IfParam *param)
{
    int    rc;

    rc = bcm_port_enable_set(param->Unit, param->HalPort, param->AdminState);
    if (BCM_FAILURE(rc)) {
        printf("bcm_port_enable_set failed port %d: %s\n",param->HalPort, bcm_edrrmsg(rc));
        return rc;
    }

    return rc;
}

static int SwitchdevCreateIntfPhysical(IfParam *param)
{
    int                  rc        = 0;
    bcm_knet_netif_t     netif;
    bcm_knet_filter_t    filter;  
    bcm_pbmp_t           pbmp;


    if (!param) {
        return -1;
    }

    if (param->HalL3Intf > 0) {
        //interface already exist, invoke update
        return swtichdevUpdateIntfPhysical(param);
    }

    //create bcm_knet
    bcm_knet_netif_t_init(&netif);
    netif.type = BCM_KNET_NETIF_T_TX_LOCAL_PORT;
    netif.vlan = 0;
    netif.port = param->HalPort;
    // netif.flags |= BCM_KNET_NETIF_F_ADD_TAG;
    netif.flags |= BCM_KNET_NETIF_F_KEEP_RX_TAG;
    memcpy(netif.mac_addr, param->Mac, sizeof(bcm_mac_t));
    netif.cb_user_data = 0;

    sal_strncpy(netif.name, param->IfName, sizeof(netif.name) - 1);
    netif.name[sizeof(netif.name) - 1] = '\0';

    if ((rc = bcm_knet_netif_create(param->Unit, &netif)) < 0) {
        printf("Error creating network interface:%s port %d rc %d\n",netif.name, netif.port, rc );
    } else {
        printf("Creating Interface %s port %d\n",netif.name, netif.port);
	}

    //get and save ifindex
    param->IfIndex = if_nametoindex(param->IfName);
    //printf("async_obj_intf_create_physical ifindex %d ifname %s\n", param->IfIndex, param->IfName);

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

    if ((rc = bcm_knet_filter_create(param->Unit, &filter)) < 0) {
        printf("Error creating packet filter: %d\n", rc);
    }   

    //spanning tree
    bcm_port_stp_set(param->Unit, param->HalPort, BCM_STG_STP_FORWARD);

    //linkscan mode
    bcm_linkscan_mode_set(param->Unit, param->HalPort, BCM_LINKSCAN_MODE_SW);

    //autoneg
    bcm_port_autoneg_set(param->Unit, param->HalPort, param->AutoNeg);

    bcm_port_pause_set(param->Unit, param->HalPort, param->PauseTx, param->PauseRx);

    bcm_stat_clear(param->Unit, param->HalPort);

    //l3 mode, create l3 intf (default is l3 mode)
    //initilize l3 intf in hardware
    if (param->IsRoutedPort) {
        //disable ARL for routed ports
        bcm_port_control_set(param->Unit, param->HalPort, bcmPortControlL2Learn, BCM_PORT_LEARN_FWD);
        bcm_port_control_set(param->Unit, param->HalPort, bcmPortControlL2Move, BCM_PORT_LEARN_FWD);

        switchdev_l3_port_init(param, &param->HalL3Intf);

        //Put port into VLAN 4095 -untagged (routed port)
        BCM_PBMP_PORT_SET(pbmp, param->HalPort);
        bcm_vlan_port_add(param->Unit, param->VlanId, pbmp, pbmp);

        bcm_port_untagged_vlan_set(param->Unit, param->HalPort, param->VlanId);
    }

    //printf("local if ifindex %d %s port %d l3_intf %d \n", 
    //       local_if->ifindex, local_if->name, local_if->hw_port, local_if->l3_intf);

    return rc;
}


static int swtichdevUpdateIntfVlan(IfParam *param)
{
    // TODO
    return 0;
}

static int SwitchdevCreateIntfVlan(IfParam *param)
{
    int                  rc        = 0;
    bcm_l2_station_t         l2_station;
    int                      station_id;
    bcm_l3_intf_t            l3_intf;
    bcm_mac_t                mac_mask = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    if (!param) {
        return -1;
    }

    printf("SwitchdevCreateIntfVlan %s\n", param->IfName);

    if (param->HalL3Intf > 0) {
        //interface already exist, invoke update
        return swtichdevUpdateIntfVlan(param);
    }

    //create l2 station for the interface
    bcm_l2_station_t_init(&l2_station);
    memcpy(l2_station.dst_mac, param->Mac, 6);
    memcpy(l2_station.dst_mac_mask, mac_mask, 6);
    l2_station.flags        = BCM_L2_STATION_IPV4 | BCM_L2_STATION_IPV6 | BCM_L2_STATION_ARP_RARP | BCM_L2_STATION_MPLS; 
    l2_station.vlan         = 0;
    l2_station.vlan_mask    = 0;
    l2_station.src_port     = 0;
    l2_station.src_port_mask = 0;

    rc = bcm_l2_station_add(param->Unit, &station_id, &l2_station);
	if (BCM_E_NONE != rc) {
			printf("SwitchdevCreateIntfVlan bcm_l2_station_add failed %s\n", bcm_errmsg(rc));
			return rc;
	}

    /* L3 Interface */
    bcm_l3_intf_t_init(&l3_intf);
    memcpy(l3_intf.l3a_mac_addr, param->Mac,6);
    l3_intf.l3a_vid = param->VlanId;
    l3_intf.l3a_vrf = 0;
    //l3_intf.l3a_flags |= BCM_L3_ADD_TO_ARL;
    rc = bcm_l3_intf_create(param->Unit, &l3_intf);
    if (BCM_FAILURE(rc)) {
       printf("SwitchdevCreateIntfVlan: Create L3 intf failed: %s\n", bcm_errmsg(rc));
       return rc;
    }

    param->HalL3Intf = l3_intf.l3a_intf_id;

    //printf("local if ifindex %d %s port %d l3_intf %d \n", 
    //       local_if->ifindex, local_if->name, local_if->hw_port, local_if->l3_intf);

    return rc;
}


int SwitchdevCreateIntf(IfParam *param)
{
    switch(param->IfType) {
        case INTF_TYPE_PHYSICAL:
            return SwitchdevCreateIntfPhysical(param);

        case INTF_TYPE_VLAN:
            return SwitchdevCreateIntfVlan(param);
    }
    return 0;
}



int SwitchdevCreateNeigh(NeighParam *param)
{
    bcm_l3_egress_t    egress_object;
    int                rc        = 0;
    int                object_id = -1;

    //printf("async_obj_neigh_create_cb %p enter\n", obj);

    if (!param) {
        return -1;
    }

    bcm_l3_egress_t_init(&egress_object);

    egress_object.module = 0;
    egress_object.port   = param->HalPort;        
    egress_object.intf   = param->HalL3Intf;
    egress_object.vlan   = param->VlanId;

    memcpy(egress_object.mac_addr, param->Mac, 6);

    // create l3 egress
    rc = bcm_l3_egress_create(param->Unit, 0, &egress_object, &object_id);    
    if (rc) {
        printf("SwitchdevCreateNeigh l3_egress create failed %d\n", rc);
    } 
    param->HalObjectId = object_id;

    return rc;
}

int SwitchdevDeleteNeigh(NeighParam *param)
{
    int                rc        = 0;

    //printf("async_obj_neigh_create_cb %p enter\n", obj);

    if (!param) {
        return -1;
    }

    rc = bcm_l3_egress_destroy(param->Unit, param->HalObjectId);
    if (BCM_FAILURE(rc)) {
        printf("async_obj_neigh_delete_cb l3_egress delete failed %d\n", rc);
    } 

    return rc;
}



static void ipv6_create_mask(uint8 *ip6_mask, uint32 prefix_length) {
    int i;

    for (i=15; i>=0; i--) {
        if (i < prefix_length/8) {
            ip6_mask[i] = 0xFF;
        } else if (i == prefix_length/8) {
            ip6_mask[i] = 0xFF - ((1 << (8 -(prefix_length % 8))) - 1);
        } else {
            ip6_mask[i] = 0X00;
        }
    }
}

static int switchdevCreateFIBSimple(FIBParam *param)
{
    bcm_l3_route_t     route_info;
    int                rc    = 0;

    if (!param) {
        return -1;
    }

    bcm_l3_route_t_init(&route_info);

    if (param->Dest.family == AF_INET) {
        route_info.l3a_subnet  = ntohl(param->Dest.ip[0]);
        if (param->PrefixLen == 0) {
            route_info.l3a_ip_mask = 0;
        } else {
            route_info.l3a_ip_mask = (0xFFFFFFFF << (32 - param->PrefixLen)) & 0xFFFFFFFF;
        }
        //printf("async_obj_fib_create_cb l3a_subnet %x l3a_ip_mask %x\n", route_info.l3a_subnet, route_info.l3a_ip_mask);
    } else {
        route_info.l3a_flags = BCM_L3_IP6;
        memcpy(route_info.l3a_ip6_net, param->Dest.ip, 16);
        ipv6_create_mask(route_info.l3a_ip6_mask, param->PrefixLen);
    } 
    route_info.l3a_intf = param->HalL3Neigh[0];
    rc = bcm_l3_route_add(param->Unit, &route_info);
    if (BCM_FAILURE(rc)) {
        printf("switchdevCreateFIBSimple l3 route create failed: %s\n", bcm_errmsg(rc));
    }

    return rc;
}


static int switchdevCreateFIBEcmp(FIBParam *param)
{
    bcm_l3_route_t        route_info;
    bcm_l3_egress_ecmp_t  ecmp_info;
    int                   rc    = 0;

    if (!param) {
        return -1;
    }

    bcm_l3_egress_ecmp_t_init(&ecmp_info);
    //ecmp_info.dynamic_mode=0;
    //ecmp_info.max_paths = 16;
    printf("switchdevCreateFIBEcmp num %d\n", param->NumPath);
    //rc = bcm_l3_egress_multipath_create(0, 0, num_ecmp, ecmp_egr, &ecmp_group_id);
    rc = bcm_l3_egress_ecmp_create(param->Unit, &ecmp_info, param->NumPath, param->HalL3Neigh);
    if (BCM_FAILURE(rc)) {
        printf("Error executing bcm_l3_egress_ecmp_create(): %s.\n", bcm_errmsg(rc));
        return rc;
    }

    param->HalEcmpGroupId = ecmp_info.ecmp_intf;

    bcm_l3_route_t_init(&route_info);

    if (param->Dest.family == AF_INET) {
        route_info.l3a_subnet  = ntohl(param->Dest.ip[0]);
        if (param->PrefixLen == 0) {
            route_info.l3a_ip_mask = 0;
        } else {
            route_info.l3a_ip_mask = (0xFFFFFFFF << (32 - param->PrefixLen)) & 0xFFFFFFFF;
        }
        //printf("async_obj_fib_create_cb l3a_subnet %x l3a_ip_mask %x\n", route_info.l3a_subnet, route_info.l3a_ip_mask);
    } else {
        route_info.l3a_flags = BCM_L3_IP6;
        memcpy(route_info.l3a_ip6_net, param->Dest.ip, 16);
        ipv6_create_mask(route_info.l3a_ip6_mask, param->PrefixLen);
    } 
    route_info.l3a_flags |= BCM_L3_MULTIPATH;

    route_info.l3a_intf = param->HalEcmpGroupId;
    rc = bcm_l3_route_add(param->Unit, &route_info);
    if (BCM_FAILURE(rc)) {
        printf("switchdevCreateFIBEcmp l3 route create failed: %s\n", bcm_errmsg(rc));
    }

    return rc;
}

int SwitchdevCreateFIB(FIBParam *param)
{
    int    rc = 0;

    if (!param) {
        return -1;
    }

    if (!param->IsECMP) {
        // none ecmp route
        rc = switchdevCreateFIBSimple(param);
    } else {
        // handle ecmp route
        rc = switchdevCreateFIBEcmp(param);
    }

    return rc;
}

int SwitchdevDeleteFIB(FIBParam *param)
{
    bcm_l3_route_t   route_info;
    int              rc = 0;

    if (!param) {
        return -1;
    }
    
    if (param->Dest.family == AF_INET) {
        route_info.l3a_subnet  = ntohl(param->Dest.ip[0]);
        if (param->PrefixLen == 0) {
            route_info.l3a_ip_mask = 0;
        } else {
            route_info.l3a_ip_mask = (0xFFFFFFFF << (32 - param->PrefixLen)) & 0xFFFFFFFF;
        }
        //printf("async_obj_fib_create_cb l3a_subnet %x l3a_ip_mask %x\n", route_info.l3a_subnet, route_info.l3a_ip_mask);
    } else {
        route_info.l3a_flags = BCM_L3_IP6;
        memcpy(route_info.l3a_ip6_net, param->Dest.ip, 16);
        ipv6_create_mask(route_info.l3a_ip6_mask, param->PrefixLen);
    } 
 
    rc = bcm_l3_route_delete(param->Unit, &route_info);

    if (BCM_FAILURE(rc)) {
        printf("SwitchdevDeleteFIB l3_route delete failed %d\n", rc);
    } 
    return rc;
}


int SwitchdevCreateL3Host(L3HostParam *param)
{
    bcm_l3_host_t       host_info;
    int                 rc;

    if (!param) {
        return -1;
    }

    bcm_l3_host_t_init(&host_info);
    host_info.l3a_lookup_class = param->LookupClass;
    host_info.l3a_intf = param->HalL3Neigh; 

    if (param->Host.family == AF_INET) {
        host_info.l3a_ip_addr = ntohl(param->Host.ip[0]); 
    } else {
        host_info.l3a_flags =  BCM_L3_IP6;
        memcpy(host_info.l3a_ip6_addr, param->Host.ip, 16);
    }

    printf("SwitchdevCreateL3Host %s\n", ipaddr2str(&param->Host));

    rc = bcm_l3_host_add(param->Unit, &host_info);

    if(rc) {
        if (rc == BCM_E_EXISTS) {
            return 0;
        }
        printf("SwitchdevCreateL3Host bcm_l3_host_add %s failed, rc = %d\n",ipaddr2str(&param->Host), rc);
    }
    return rc;
}


int SwitchdevDeleteL3Host(L3HostParam *param)
{
    bcm_l3_host_t       host_info;
    int                 rc;

    if (!param) {
        return -1;
    }    

    bcm_l3_host_t_init(&host_info);
    host_info.l3a_lookup_class = param->LookupClass;
    host_info.l3a_intf = param->HalL3Neigh; 

    if (param->Host.family == AF_INET) {
        host_info.l3a_ip_addr = ntohl(param->Host.ip[0]); 
    } else {
        host_info.l3a_flags =  BCM_L3_IP6;
        memcpy(host_info.l3a_ip6_addr, param->Host.ip, 16);
    }

    printf("SwitchdevDeleteL3Host %s\n", ipaddr2str(&param->Host));

    rc = bcm_l3_host_delete(param->Unit, &host_info);

    if(rc) {
       printf("SwitchdevDeleteL3Host bcm_l3_host_delete failed, rc = %d\n", rc);
    }
    return rc;
}


#ifndef SWITCHDEV_BROADCOM_H
#define SWITCHDEV_BROADCOM_H


int SwitchdevCreateSwitch(int unit, uint8_t sysmac[6]);
int SwitchdevCreateVlan(int unit, int vid, int ifclass, bool blockbroadcast);

enum port_type_e {
    INTF_TYPE_VLAN,
    INTF_TYPE_PHYSICAL,
};

typedef struct IfParam_s {
    int     Unit;
    char   *IfName; 
    int     IfType;  
    uint8_t Mac[6];
    bool    AdminState;              // true - UP

    bool    IsRoutedPort;            // routed port vs switchport
    int     HalPort;                 // hardware port id
    int     VlanId;                  // should always be 4095 for routed port
    int     HalL3Intf;               // return value
    int     IfIndex;                 // return value, linux ifindex

    bool    AutoNeg;
    bool    PauseTx;
    bool    PauseRx;   
}IfParam;

int SwitchdevCreateIntf(IfParam *param);

enum neigh_type_e {
     NEIGH_DYNAMIC,
     NEIGH_FORUS,
};

typedef struct ip_address_s {
    uint32_t family;      //AF_INET4 AF_INET6
    uint32_t ip[4];
}ip_address_t;

typedef struct NeighParam_s {
    int                NeighType;
    ip_address_t       Nh;
    uint8_t            Mac[6];
    int                IfIndex;               //linux ifindex
    char              *IfName;                //linux ifname
    int                HalPort;               // asic port
    int                HalL3Intf;
    int                VlanId;
    int                HalObjectId;           // return value
}NeighParam;

int SwitchdevCreateNeigh(NeighParam *param);

#endif

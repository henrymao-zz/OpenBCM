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
#endif

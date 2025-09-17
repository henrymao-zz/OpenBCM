#ifndef SWITCHDEV_BROADCOM_H
#define SWITCHDEV_BROADCOM_H


int SwitchdevCreateSwitch(int unit, uint8_t sysmac[6]);
int SwitchdevCreateVlan(int unit, int vid, int ifclass, bool blockbroadcast);

#endif

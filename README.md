# How to Run OpenBCM on Dell N3248TE-ON

```
sudo apt install -y libnsl-dev  
export KERNDIR=/usr/src/linux-headers-6.8.0-1000-sonic
cd sdk-6.5.24
make -C systems/linux/user/x86-smp_generic_64-2_6/
make -j4 -C systems/linux/user/x86-smp_generic_64-2_6/        

tar -zcvf openbcm.tar.gz build/linux/user/x86-smp_generic_64-2_6/ rc/cmicfw/*.bin rc/n3248te/*
```

start bcm.user on switch
```
$./bcm.user
BCM.0>
BCM.0>config add parity_enable=0
BCM.0>init soc
BCM.0>m0 load 0 0x0 linkscan_led_fw.bin
BCM.0>m0 load 0 0x3800 custom_led.bin

BCM.0>cancun load cch
BCM.0>cancun load ceh
BCM.0>cancun load cmh
BCM.0>cancun load cih
BCM.0>init misc

BCM.0>init mmu

BCM.0>init bcm

BCM.0>linkscan 250000
BCM.0>port ge linkscan=on autoneg=on speed=1000 fullduplex=true txpause=true rxpause=true
BCM.0>stg stp 1 all forward
```

Port shall be up by now:

```
BCM.0> portstat
                 ena/        speed/ link auto    STP                  lrn  inter   max   cut   loop        
           port  link  Lns   duplex scan neg?   state   pause  discrd ops   face frame  thru?  back   encap
       ge0(  1)  up     1    1G  FD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
       ge1(  2)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
       ge2(  3)  up     1    1G  FD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
       ge3(  4)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
       ge4(  5)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
       ge5(  6)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
       ge6(  7)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
       ge7(  8)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
       ge8(  9)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
       ge9( 10)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge10( 11)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge11( 12)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge12( 13)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge13( 14)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge14( 15)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge15( 16)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge16( 17)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge17( 18)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge18( 19)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge19( 20)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge20( 21)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge21( 22)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge22( 23)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge23( 24)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge24( 25)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge25( 26)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge26( 27)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge27( 28)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge28( 29)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge29( 30)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge30( 31)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge31( 32)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge32( 33)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge33( 34)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge34( 35)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge35( 36)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge36( 37)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge37( 38)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge38( 39)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge39( 40)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge40( 41)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge41( 42)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge42( 43)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge43( 44)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge44( 45)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge45( 46)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge46( 47)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
      ge47( 48)  down   1    1G  HD   SW  Yes  Forward  TX RX   None   FA  SGMII 12284                IEEE
       xe0( 49)  down   1   10G  FD None  No   Forward  TX RX   None   FA    XFI 12284                IEEE
       xe1( 50)  down   1   10G  FD None  No   Forward  TX RX   None   FA    XFI 12284                IEEE
       xe2( 51)  down   1   10G  FD None  No   Forward  TX RX   None   FA    XFI 12284                IEEE
       xe3( 52)  down   1   10G  FD None  No   Forward  TX RX   None   FA    XFI 12284                IEEE
       ce0( 53)  down   4  100G  FD None  No   Forward  TX RX   None   FA  CAUI4 12284                IEEE
       ce1( 57)  down   4  100G  FD None  No   Forward  TX RX   None   FA  CAUI4 12284                IEEE
BCM.0> 
```

# OpenBCM Broadcom Core Switch Software Development Kit (SDK)

Overview
========

OpenBCM Broadcom Switch Software Development Kit contains the source code for Broadcom network switch APIs 
and drivers for programming Broadcom network switch silicon based platforms.

Legal
=====

The SDK APIs, drivers and samples are covered by the following license see Legal/LICENSE file.
OpenBCM uses a few open source components, see Legal/EXTLICENSE file for license terms.
The source code in the gpl-module and dcb-gpl-modules directories are covered by GPLv2 license.

Supported devices
=================
This release has support for XGS switch devices such as Trident (TD2, TD3, TD4), Tomahawk (TH, TH2, TH3)
and DNX devices such as Ramon, Qumran (Q2A, Q2U) and Jericho (JR2, J2C).

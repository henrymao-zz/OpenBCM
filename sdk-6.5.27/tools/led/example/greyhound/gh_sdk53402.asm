;
; $Id: gh_sdk53402.asm,v 1.0 Broadcom SDK $
;
; This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
; 
; Copyright 2007-2022 Broadcom Inc. All rights reserved.
;
;
; This is the default program for Greyhound SKUs:
;       BCM534x2
;
; To start it, use the following commands from BCM:
;
;       led load gh_sdk53402.hex
;       led auto on
;       led start
;
; Assume 1 LED per port for Link. And 2 bits stream per LED.
;       Link-Down = Off (b'00)
;       Link-Up = On (b'01)
;
; Totally 8 ports/LEDs will be outputed.
;
; Link up/down info cannot be derived from LINKEN or LINKUP, as the LED
; processor does not always have access to link status.  This program
; assumes link status is kept current in bit 0 of RAM byte (0xA0 + portnum).
; Generally, a program running on the main CPU must update these
; locations on link change; see linkscan callback in
; $SDK/src/appl/diag/ledproc.c.
;

;
; Constants
;
NUM_PORTS   equ 8
MIN_PORT_0 equ 22
MAX_PORT_0 equ 29

;
; LED process
;
start:
    ld  a, MIN_PORT_0

iter_sec0:
    cmp a, MAX_PORT_0+1
    jnc  end

    cmp a, MIN_PORT_0
    jz  iter_sec0_init
    jc  iter_sec0_init
    jmp iter_sec0_start
iter_sec0_init:
    ld  a, MIN_PORT_0
    ld  b, MAX_PORT_0
    ld  (SEC_MAX), b
iter_sec0_start:
    jmp iter_common

iter_common:
    port    a
    ld  (PORT_NUM), a

    call    get_link

    ld  a, (PORT_NUM)
    inc a
    ld b, (SEC_MAX)
    inc b
    cmp a, b
    jz iter_sec0
    jmp iter_common

end:
	send    2*NUM_PORTS

;
; get_link
;
;  This routine finds the link status LED for a port.
;  Link info is in bit 0 of the byte read from PORTDATA[port]
;  Inputs: (PORT_NUM)
;  Outputs: Carry flag set if link is up, clear if link is down.
;  Destroys: a, b
get_link:
    ld  b, PORTDATA
    add b, (PORT_NUM)
    ld  a, (b)
    tst a, 0

    jc led_green
    jmp led_black

;
; led_green
;
;  Outputs: Bits to the LED stream indicating ON
;
led_green:
    push 0
    pack
    push 1
    pack
    ret

;
; led_black
;
;  Outputs: Bits to the LED stream indicating OFF
;
led_black:
    push 0
    pack
    push 0
    pack
    ret

; Variables (SDK software initializes LED memory from 0xA0-0xff to 0)
PORTDATA    equ 0xA0
PORT_NUM    equ 0xE0
SEC_MAX equ 0xE1

; Symbolic names for the bits of the port status fields
RX      equ 0x0 ; received packet
TX      equ 0x1 ; transmitted packet
COLL    equ 0x2 ; collision indicator
SPEED_C equ 0x3 ; 100 Mbps
SPEED_M equ 0x4 ; 1000 Mbps
DUPLEX  equ 0x5 ; half/full duplex
FLOW    equ 0x6 ; flow control capable
LINKUP  equ 0x7 ; link down/up status
LINKEN  equ 0x8 ; link disabled/enabled status
ZERO    equ 0xE ; always 0
ONE     equ 0xF ; always 1

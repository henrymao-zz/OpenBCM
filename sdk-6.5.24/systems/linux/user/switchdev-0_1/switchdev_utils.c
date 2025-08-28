#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "switchdev_utils.h"

static __thread char ipaddr_buf[IPADDR_STR_LEN];

char *format_ipaddr(ip_address_t *ipaddr)
{
    uint8_t *data = ipaddr->ip;

    if(ipaddr->protocol == AF_INET) {
        sprintf(ipaddr_buf, "%d.%d.%d.%d",
            (ipaddr->ip[0] >> 24) & 0xff, (ipaddr->ip[0] >> 16) & 0xff,
            (ipaddr->ip[0] >> 8) & 0xff, ipaddr->ip[0] & 0xff);
    } else {
        sprintf(ipaddr_buf, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
            (((uint16)data[0] << 8) | data[1]),
            (((uint16)data[2] << 8) | data[3]),
            (((uint16)data[4] << 8) | data[5]),
            (((uint16)data[6] << 8) | data[7]),
            (((uint16)data[8] << 8) | data[9]),
            (((uint16)data[10] << 8) | data[11]),
            (((uint16)data[12] << 8) | data[13]),
            (((uint16)data[14] << 8) | data[15]));
    }
    return ipaddr_buf;
}


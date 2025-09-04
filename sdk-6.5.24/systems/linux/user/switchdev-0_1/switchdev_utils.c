#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "switchdev_utils.h"

#define IPADDR_STR_LEN 64
static __thread char ipaddr_buf[IPADDR_STR_LEN];

char *ipaddr2str(ip_address_t *ipaddr)
{
    uint8_t *data = (uint8_t *)ipaddr->ip;
    uint32_t ipv4 = ntohl(ipaddr->ip[0]);

    if(ipaddr->protocol == AF_INET) {
        sprintf(ipaddr_buf, "%d.%d.%d.%d",
            (ipv4 >> 24) & 0xff, (ipv4 >> 16) & 0xff,
            (ipv4 >> 8) & 0xff, ipv4 & 0xff);
    } else {
        sprintf(ipaddr_buf, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
            (((uint16_t)data[0] << 8) | data[1]),
            (((uint16_t)data[2] << 8) | data[3]),
            (((uint16_t)data[4] << 8) | data[5]),
            (((uint16_t)data[6] << 8) | data[7]),
            (((uint16_t)data[8] << 8) | data[9]),
            (((uint16_t)data[10] << 8) | data[11]),
            (((uint16_t)data[12] << 8) | data[13]),
            (((uint16_t)data[14] << 8) | data[15]));
    }
    return ipaddr_buf;
}

#define MACADDR_STR_LEN 64
static __thread char macaddr_buf[MACADDR_STR_LEN];

char *macaddr2str(uint8_t *mac_addr)
{
    sprintf(macaddr_buf, "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[5], mac_addr[4],mac_addr[3], mac_addr[2],mac_addr[1],mac_addr[0]);   

    return macaddr_buf;
}

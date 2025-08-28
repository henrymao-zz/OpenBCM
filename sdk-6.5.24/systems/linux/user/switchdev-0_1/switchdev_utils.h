#ifndef SWITCHDEV_UTILS_H
#define SWITCHDEV_UTILS_H

// common data structure 
typedef struct ip_address_s {
    uint32_t protocol;      //AF_INET4 AF_INET6
    uint32_t ip[4];
}ip_address_t;


char *ipaddr2str(ip_address_t *ipaddr);

#endif

#ifndef GET_SYSINFO_H
#define GET_SYSINFO_H

#include <sys/sysinfo.h>
#include <stdio.h>
#include <string.h>

int get_cpu_usage();
int get_memory_usage();
int get_temperature();
void get_network_traffic(const char *interface, unsigned long *rx_bytes, unsigned long *tx_bytes);
char *get_lan_ip();

#endif /* GET_SYSINFO_H */

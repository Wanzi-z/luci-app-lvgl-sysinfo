#ifndef GET_CONFIG_H
#define GET_CONFIG_H

#define CONFIG_FILE "/etc/config/qmodem"

#include <stdio.h>
#include <string.h>

int get_at_port_number(char *at_port_number, size_t size);
const char *get_display_mode();

#endif /* GET_CONFIG_H */

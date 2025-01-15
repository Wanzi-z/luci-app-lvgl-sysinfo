#ifndef GET_MODEM_INFO_H
#define GET_MODEM_INFO_H

#include <stdio.h>
#include <unistd.h>
#include "get_config.h"
#include <stdlib.h>

#define AT_COMMAND "AT+CSQ"

#define RSSI_MIN 0
#define RSSI_MAX 31
#define DBM_MIN -113
#define DBM_MAX -51

#define MIN_RSRP -140
#define MAX_RSRP -44

typedef struct
{
    int rsrp;
    int rsrq;
    int sinr;
} ModemInfo;

int get_rssi_from_modem(const char *port_number);
int get_rsrp_from_modem(const char *port_number);
int get_modem_info(ModemInfo *info);

#endif /* GET_MODEM_INFO_H */

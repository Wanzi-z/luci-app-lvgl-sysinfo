#ifndef UPDATE_CB_H
#define UPDATE_CB_H

#include "../lvgl/lvgl.h"
#include "../ui/top_bar.h"
#include "../ui/bottom_bar.h"
#include "../ui/mid_content.h"
#include "get_sysinfo.h"
#include "tools.h"
#include <time.h>
#include <stdio.h>
#include "get_modem_info.h"

#define RSSI_MIN 0
#define RSSI_MAX 31
#define DBM_MIN -113
#define DBM_MAX -51

#define MIN_RSRP -140
#define MAX_RSRP -44

void update_ip();
void update_network_traffic_cb(lv_timer_t *timer);

void update_gauges_cb(lv_timer_t *timer);

void update_time_cb(lv_timer_t *timer);

// void update_rssi_gauge_cb(lv_timer_t *timer);

#endif /* UPDATE_CB_H */

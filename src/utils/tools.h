#ifndef TOOLS_H
#define TOOLS_H

#include "../lvgl/lvgl.h"
#include <string.h>
#include <stdio.h>

void format_traffic(unsigned long bytes, char *output, size_t size);

lv_color_t get_rsrp_color(int rsrq);
lv_color_t get_rsrq_color(int rsrp);
lv_color_t get_sinr_color(int sinr);

int get_rsrp_percentage(int rsrp);
int get_rsrq_percentage(int rsrq);
int get_sinr_percentage(int sinr);

#endif /* TOOLS_H */
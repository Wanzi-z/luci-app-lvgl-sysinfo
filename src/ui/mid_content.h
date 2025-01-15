#ifndef MID_CONTENT_H
#define MID_CONTENT_H
#include "../lvgl/lvgl.h"

typedef struct
{
    lv_obj_t *arc;
    lv_obj_t *value_label;
} gauge_t;

extern gauge_t rsrp_gauge;
extern gauge_t rsrq_gauge;
extern gauge_t sinrb_gauge;

extern gauge_t cpu_gauge;
extern gauge_t mem_gauge;
extern gauge_t temp_gauge;

void create_center_widgets(lv_obj_t *parent);
void create_modem_center_widgets(lv_obj_t *parent);

#endif /* MID_CONTENT_H */
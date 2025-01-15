#ifndef BOTTOM_BAR_H
#define BOTTOM_BAR_H

#include "../lvgl/lvgl.h"

extern lv_obj_t *time_label, *upload_label, *download_label;

void create_bottom_bar(lv_obj_t *parent);

#endif /* BOTTOM_BAR_H */
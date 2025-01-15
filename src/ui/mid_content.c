#include "mid_content.h"

gauge_t rsrp_gauge, rsrq_gauge, sinrb_gauge, mem_gauge, temp_gauge, cpu_gauge;

void create_gauge(lv_obj_t *parent, const char *name, gauge_t *gauge, lv_color_t arc_color, lv_align_t align, int x_ofs, int y_ofs)
{

    lv_obj_t *container = lv_obj_create(parent);
    lv_obj_set_size(container, 65, 65);
    lv_obj_set_style_radius(container, 10, 0);
    lv_obj_set_style_bg_color(container, lv_color_hex(0x333333), 0);
    lv_obj_set_style_border_width(container, 1, 0);
    lv_obj_set_style_border_color(container, arc_color, 0);
    lv_obj_align(container, align, x_ofs, y_ofs);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *arc = lv_arc_create(container);
    lv_obj_set_size(arc, 55, 55);
    lv_arc_set_range(arc, 0, 100);
    lv_obj_set_style_arc_width(arc, 2, LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc, 2, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc, arc_color, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc, lv_color_hex(0xeeeeee), 0);
    lv_obj_center(arc);

    lv_obj_t *value_label = lv_label_create(container);
    lv_label_set_text(value_label, "0");
    lv_obj_set_style_text_color(value_label, arc_color, 0);
    lv_obj_set_style_text_font(value_label, &lv_font_montserrat_12, 0);
    lv_obj_align(value_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *name_label = lv_label_create(container);
    lv_label_set_text(name_label, name);
    lv_obj_set_style_text_color(name_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(name_label, &lv_font_montserrat_10, 0);
    lv_obj_align(name_label, LV_ALIGN_BOTTOM_MID, 0, 13);

    gauge->arc = arc;
    gauge->value_label = value_label;
}

void create_center_widgets(lv_obj_t *parent)
{

    create_gauge(parent, "CPU", &cpu_gauge, lv_color_hex(0x6FCF97), LV_ALIGN_LEFT_MID, 10, 2);

    create_gauge(parent, "Mem", &mem_gauge, lv_color_hex(0x56CCF2), LV_ALIGN_CENTER, 0, 2);

    create_gauge(parent, "Temp", &temp_gauge, lv_color_hex(0xEB5757), LV_ALIGN_RIGHT_MID, -10, 2);
}

void create_rssi_gauge(lv_obj_t *parent, const char *name, gauge_t *gauge, lv_align_t align, int x_ofs, int y_ofs)
{

    lv_obj_t *container = lv_obj_create(parent);
    lv_obj_set_size(container, 65, 65);
    lv_obj_set_style_radius(container, 10, 0);
    lv_obj_set_style_bg_color(container, lv_color_hex(0x333333), 0);
    lv_obj_set_style_border_width(container, 1, 0);
    lv_obj_set_style_border_color(container, lv_color_hex(0x555555), 0);
    lv_obj_align(container, align, x_ofs, y_ofs);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *arc = lv_arc_create(container);
    lv_obj_set_size(arc, 55, 55);
    lv_arc_set_range(arc, 0, 100);
    lv_obj_set_style_arc_width(arc, 2, LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc, 2, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc, lv_color_hex(0xeeeeee), 0);
    lv_obj_center(arc);

    lv_obj_t *value_label = lv_label_create(container);
    lv_label_set_text(value_label, "0");
    lv_obj_set_style_text_color(value_label, lv_color_hex(0x6FCF97), 0);
    lv_obj_set_style_text_font(value_label, &lv_font_montserrat_12, 0);
    lv_obj_align(value_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *name_label = lv_label_create(container);
    lv_label_set_text(name_label, name);
    lv_obj_set_style_text_color(name_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(name_label, &lv_font_montserrat_10, 0);
    lv_obj_align(name_label, LV_ALIGN_BOTTOM_MID, 0, 13);

    gauge->arc = arc;
    gauge->value_label = value_label;
}

void create_modem_center_widgets(lv_obj_t *parent)
{

    create_rssi_gauge(parent, "RSRP", &rsrp_gauge, LV_ALIGN_LEFT_MID, 10, 2);

    create_rssi_gauge(parent, "RSRQ", &rsrq_gauge, LV_ALIGN_CENTER, 0, 2);

    create_rssi_gauge(parent, "SINR", &sinrb_gauge, LV_ALIGN_RIGHT_MID, -10, 2);
}
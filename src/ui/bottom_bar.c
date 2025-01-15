#include "bottom_bar.h"

lv_obj_t *time_label, *upload_label, *download_label;

void create_bottom_bar(lv_obj_t *parent)
{

    lv_obj_t *time_container = lv_obj_create(parent);
    lv_obj_set_size(time_container, 50, 25);
    lv_obj_set_style_bg_color(time_container, lv_color_hex(0x3B4048), 0);
    lv_obj_set_style_border_width(time_container, 1, 0);
    lv_obj_set_style_border_color(time_container, lv_color_hex(0x555555), 0);
    lv_obj_align(time_container, LV_ALIGN_BOTTOM_LEFT, 10, -3);
    lv_obj_clear_flag(time_container, LV_OBJ_FLAG_SCROLLABLE);

    time_label = lv_label_create(time_container);
    lv_label_set_text(time_label, "12:30:50");
    lv_obj_set_style_text_color(time_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(time_label, &lv_font_montserrat_10, 0);
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *speed_container = lv_obj_create(parent);
    lv_obj_set_size(speed_container, 160, 25);
    lv_obj_set_style_bg_color(speed_container, lv_color_hex(0x333333), 0);
    lv_obj_set_style_border_width(speed_container, 1, 0);
    lv_obj_set_style_border_color(speed_container, lv_color_hex(0x555555), 0);
    lv_obj_align(speed_container, LV_ALIGN_BOTTOM_RIGHT, -10, -3);

    upload_label = lv_label_create(speed_container);
    lv_label_set_text(upload_label, "UP: 0 B/s");
    lv_obj_set_style_text_color(upload_label, lv_color_hex(0xF2994A), 0);
    lv_obj_set_style_text_font(upload_label, &lv_font_montserrat_12, 0);
    lv_obj_align(upload_label, LV_ALIGN_LEFT_MID, -10, 0);

    download_label = lv_label_create(speed_container);
    lv_label_set_text(download_label, "Down: 0 B/s");
    lv_obj_set_style_text_color(download_label, lv_color_hex(0x2F80ED), 0);
    lv_obj_set_style_text_font(download_label, &lv_font_montserrat_12, 0);
    lv_obj_align(download_label, LV_ALIGN_RIGHT_MID, 10, 0);

    lv_obj_clear_flag(speed_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(speed_container, LV_SCROLLBAR_MODE_OFF);
}
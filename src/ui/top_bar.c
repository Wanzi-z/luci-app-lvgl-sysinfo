#include "top_bar.h"

lv_obj_t *ip_label;

void create_top_bar(lv_obj_t *parent)
{

    lv_obj_t *logo_container = lv_obj_create(parent);
    lv_obj_set_size(logo_container, 45, 30);
    lv_obj_align(logo_container, LV_ALIGN_TOP_LEFT, 10, 2);
    lv_obj_set_style_bg_color(logo_container, lv_color_hex(0x93b5cf), 0);

    lv_obj_set_style_border_width(logo_container, 1, 0);
    lv_obj_set_style_border_color(logo_container, lv_color_hex(0x555555), 0);
    lv_obj_clear_flag(logo_container, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *logo = lv_label_create(logo_container);
    lv_label_set_text(logo, "H29K");
    lv_obj_set_style_text_color(logo, lv_color_hex(0x6A577F), 0);
    lv_obj_set_style_text_font(logo, &lv_font_montserrat_12, 0);
    lv_obj_align(logo, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *ip_container = lv_obj_create(parent);
    lv_obj_set_size(ip_container, 165, 30);
    lv_obj_align(ip_container, LV_ALIGN_TOP_RIGHT, -10, 2);
    lv_obj_set_style_bg_color(ip_container, lv_color_hex(0x1ba784), 0);
    lv_obj_set_style_border_width(ip_container, 1, 0);
    lv_obj_set_style_border_color(ip_container, lv_color_hex(0x555555), 0);

    lv_obj_clear_flag(ip_container, LV_OBJ_FLAG_SCROLLABLE);

    ip_label = lv_label_create(ip_container);
    lv_label_set_text(ip_label, "IP: Fetching...");
    lv_obj_set_style_text_color(ip_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(ip_label, &lv_font_montserrat_12, 0);
    lv_obj_align(ip_label, LV_ALIGN_CENTER, 0, 0);
}
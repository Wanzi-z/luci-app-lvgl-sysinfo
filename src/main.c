#include "main.h"

void hal_init(int32_t w, int32_t h)
{
    lv_display_t *disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");

    lv_obj_t *screen = lv_scr_act();

    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);

    create_top_bar(screen);

    const char *ui_mode = get_display_mode();
    if (strcmp(ui_mode, "modem") == 0)
    {
        printf("UI Mode: Modem\n");
        create_modem_center_widgets(screen);
    }
    else if (strcmp(ui_mode, "system") == 0)
    {
        printf("UI Mode: System\n");
        create_center_widgets(screen);
    }
    else
    {
        printf("Unknown UI Mode: %s. Defaulting to System Mode.\n", ui_mode);

        create_center_widgets(screen);
    }

    create_bottom_bar(screen);

    update_ip();
    lv_timer_create(update_time_cb, 1000, NULL);

    lv_timer_create(update_gauges_cb, 1000, NULL);

    lv_timer_create(update_network_traffic_cb, 1000, NULL);
}

int main(int argc, char **argv)
{
    lv_init();

    hal_init(240, 135);

    while (1)
    {
        lv_timer_handler();
        usleep(5 * 1000);
    }

    return 0;
}
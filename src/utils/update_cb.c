#include "update_cb.h"

void update_ip()
{
    char *ip = get_lan_ip();
    lv_label_set_text_fmt(ip_label, "IP: %s", ip);
}

void update_network_traffic_cb(lv_timer_t *timer)
{
    static unsigned long prev_rx = 0, prev_tx = 0;
    static struct timespec prev_time = {0, 0};

    unsigned long curr_rx = 0, curr_tx = 0;
    struct timespec curr_time = {0, 0};

    get_network_traffic("br-lan", &curr_rx, &curr_tx);

    clock_gettime(CLOCK_MONOTONIC, &curr_time);

    double time_diff = (curr_time.tv_sec - prev_time.tv_sec) +
                       (curr_time.tv_nsec - prev_time.tv_nsec) / 1e9;

    if (time_diff > 0 && prev_rx > 0 && prev_tx > 0)
    {
        unsigned long rx_diff = curr_rx - prev_rx;
        unsigned long tx_diff = curr_tx - prev_tx;

        unsigned long rx_rate = rx_diff / time_diff;
        unsigned long tx_rate = tx_diff / time_diff;

        char upload_text[32];
        char download_text[32];
        format_traffic(tx_rate, upload_text, sizeof(upload_text));
        format_traffic(rx_rate, download_text, sizeof(download_text));

        lv_label_set_text(upload_label, upload_text);
        lv_label_set_text(download_label, download_text);
    }

    prev_rx = curr_rx;
    prev_tx = curr_tx;
    prev_time = curr_time;
}

void update_time_cb(lv_timer_t *timer)
{
    time_t now = time(NULL);
    struct tm *time_info = localtime(&now);

    char time_str[16];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", time_info);
    lv_label_set_text(time_label, time_str);
}

void update_modem_gauges()
{

    ModemInfo modem_info;
    if (get_modem_info(&modem_info) != 0)
    {
        fprintf(stderr, "Failed to get modem information\n");
        return;
    }

    printf("Modem Info - RSRP: %d, RSRQ: %d, SINR: %d\n", modem_info.rsrp, modem_info.rsrq, modem_info.sinr);

    printf("Updating RSRP Gauge...\n");
    if (rsrp_gauge.arc && rsrp_gauge.value_label)
    {
        int rsrp_percentage = get_rsrp_percentage(modem_info.rsrp);
        printf("RSRP Percentage: %d\n", rsrp_percentage);
        lv_arc_set_value(rsrp_gauge.arc, rsrp_percentage);
        lv_label_set_text_fmt(rsrp_gauge.value_label, "%d", rsrp_percentage);
        lv_color_t rsrp_color = get_rsrp_color(modem_info.rsrp);
        lv_obj_set_style_arc_color(rsrp_gauge.arc, rsrp_color, LV_PART_INDICATOR);
        lv_obj_set_style_text_color(rsrp_gauge.value_label, rsrp_color, 0);
    }
    else
    {
        fprintf(stderr, "rsrp_gauge.arc or rsrp_gauge.value_label is NULL\n");
    }

    printf("Updating RSRQ Gauge...\n");
    if (rsrq_gauge.arc && rsrq_gauge.value_label)
    {
        int rsrq_percentage = get_rsrq_percentage(modem_info.rsrq);
        printf("RSRQ Percentage: %d\n", rsrq_percentage);
        lv_arc_set_value(rsrq_gauge.arc, rsrq_percentage);
        lv_label_set_text_fmt(rsrq_gauge.value_label, "%d", rsrq_percentage);
        lv_color_t rsrq_color = get_rsrq_color(modem_info.rsrq);
        lv_obj_set_style_arc_color(rsrq_gauge.arc, rsrq_color, LV_PART_INDICATOR);
        lv_obj_set_style_text_color(rsrq_gauge.value_label, rsrq_color, 0);
    }
    else
    {
        fprintf(stderr, "rsrq_gauge.arc or rsrq_gauge.value_label is NULL\n");
    }

    printf("Updating SINR Gauge...\n");
    if (sinrb_gauge.arc && sinrb_gauge.value_label)
    {
        int sinr_percentage = get_sinr_percentage(modem_info.sinr);
        printf("SINR Percentage: %d\n", sinr_percentage);
        lv_arc_set_value(sinrb_gauge.arc, sinr_percentage);
        lv_label_set_text_fmt(sinrb_gauge.value_label, "%d", sinr_percentage);
        lv_color_t sinr_color = get_sinr_color(modem_info.sinr);
        lv_obj_set_style_arc_color(sinrb_gauge.arc, sinr_color, LV_PART_INDICATOR);
        lv_obj_set_style_text_color(sinrb_gauge.value_label, sinr_color, 0);
    }
    else
    {
        fprintf(stderr, "sinr_gauge.arc or sinr_gauge.value_label is NULL\n");
    }
}

void update_system_gauges()
{

    int cpu_usage = get_cpu_usage();
    int mem_usage = get_memory_usage();
    int temperature = get_temperature();

    lv_arc_set_value(cpu_gauge.arc, cpu_usage);
    lv_label_set_text_fmt(cpu_gauge.value_label, "%d", cpu_usage);

    lv_arc_set_value(mem_gauge.arc, mem_usage);
    lv_label_set_text_fmt(mem_gauge.value_label, "%d", mem_usage);

    lv_arc_set_value(temp_gauge.arc, temperature);
    lv_label_set_text_fmt(temp_gauge.value_label, "%d", temperature);
}

/**
 * 更新仪表盘回调函数
 */
void update_gauges_cb(lv_timer_t *timer)
{
    const char *ui_mode = get_display_mode();
    if (ui_mode == NULL || strlen(ui_mode) == 0)
    {
        ui_mode = "system";
    }
    printf("UI Mode: %s\n", ui_mode);

    if (strcmp(ui_mode, "modem") == 0)
    {
        printf("Updating Modem Gauges...\n");
        update_modem_gauges();
    }
    else if (strcmp(ui_mode, "system") == 0)
    {
        printf("Updating System Gauges...\n");
        update_system_gauges();
    }
    else
    {
        printf("Unknown UI Mode: %s. Defaulting to System Gauges...\n", ui_mode);
        update_system_gauges();
    }
}
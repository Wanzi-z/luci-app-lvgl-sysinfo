#include "tools.h"

lv_color_t get_rsrp_color(int rsrp)
{
    if (rsrp >= -80)
    {
        return lv_palette_main(LV_PALETTE_GREEN);
    }
    else if (rsrp >= -100)
    {
        return lv_palette_main(LV_PALETTE_YELLOW);
    }
    else if (rsrp >= -120)
    {
        return lv_palette_main(LV_PALETTE_ORANGE);
    }
    else
    {
        return lv_palette_main(LV_PALETTE_RED);
    }
}

lv_color_t get_rsrq_color(int rsrq)
{
    if (rsrq >= -10)
    {
        return lv_palette_main(LV_PALETTE_GREEN);
    }
    else if (rsrq >= -15)
    {
        return lv_palette_main(LV_PALETTE_YELLOW);
    }
    else if (rsrq >= -20)
    {
        return lv_palette_main(LV_PALETTE_ORANGE);
    }
    else
    {
        return lv_palette_main(LV_PALETTE_RED);
    }
}

lv_color_t get_sinr_color(int sinr)
{
    if (sinr >= 20)
    {
        return lv_palette_main(LV_PALETTE_GREEN);
    }
    else if (sinr >= 10)
    {
        return lv_palette_main(LV_PALETTE_YELLOW);
    }
    else if (sinr >= 0)
    {
        return lv_palette_main(LV_PALETTE_ORANGE);
    }
    else
    {
        return lv_palette_main(LV_PALETTE_RED);
    }
}

int get_rsrp_percentage(int rsrp)
{
    int min_rsrp = -140;
    int max_rsrp = -44;
    if (rsrp < min_rsrp)
        rsrp = min_rsrp;
    if (rsrp > max_rsrp)
        rsrp = max_rsrp;
    return (rsrp - min_rsrp) * 100 / (max_rsrp - min_rsrp);
}

int get_rsrq_percentage(int rsrq)
{
    int min_rsrq = -20;
    int max_rsrq = -3;
    if (rsrq < min_rsrq)
        rsrq = min_rsrq;
    if (rsrq > max_rsrq)
        rsrq = max_rsrq;
    return (rsrq - min_rsrq) * 100 / (max_rsrq - min_rsrq);
}

int get_sinr_percentage(int sinr)
{
    int min_sinr = 0;
    int max_sinr = 30;
    if (sinr < min_sinr)
        sinr = min_sinr;
    if (sinr > max_sinr)
        sinr = max_sinr;
    return (sinr - min_sinr) * 100 / (max_sinr - min_sinr);
}

void format_traffic(unsigned long bytes, char *output, size_t size)
{
    if (bytes >= 1024 * 1024 * 1024)
    {
        snprintf(output, size, "%.2f GB/s", bytes / (1024.0 * 1024.0 * 1024.0));
    }
    else if (bytes >= 1024 * 1024)
    {
        snprintf(output, size, "%.2f MB/s", bytes / (1024.0 * 1024.0));
    }
    else if (bytes >= 1024)
    {
        snprintf(output, size, "%.2f KB/s", bytes / 1024.0);
    }
    else
    {
        snprintf(output, size, "%lu B/s", bytes);
    }
}
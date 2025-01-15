#include "get_sysinfo.h"

int get_cpu_usage()
{
    static long prev_idle = 0, prev_total = 0;
    long idle, total, diff_idle, diff_total;
    double usage;
    FILE *file = fopen("/proc/stat", "r");
    if (!file)
        return 0;

    char buffer[128];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    long user, nice, system, idle_time, iowait, irq, softirq;
    sscanf(buffer, "cpu %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle_time, &iowait, &irq, &softirq);

    idle = idle_time + iowait;
    total = user + nice + system + idle_time + iowait + irq + softirq;

    diff_idle = idle - prev_idle;
    diff_total = total - prev_total;
    prev_idle = idle;
    prev_total = total;

    usage = (double)(diff_total - diff_idle) / diff_total * 100.0;
    return (int)usage;
}

int get_memory_usage()
{
    struct sysinfo info;
    if (sysinfo(&info) == -1)
        return 0;

    long total = info.totalram / 1024;
    long free = info.freeram / 1024;
    return (int)((total - free) * 100 / total);
}

int get_temperature()
{
    FILE *file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (!file)
        return 0;

    int temp;
    fscanf(file, "%d", &temp);
    fclose(file);

    return temp / 1000;
}

void get_network_traffic(const char *interface, unsigned long *rx_bytes, unsigned long *tx_bytes)
{
    char path[128];
    FILE *file;

    snprintf(path, sizeof(path), "/sys/class/net/%s/statistics/rx_bytes", interface);
    file = fopen(path, "r");
    if (file)
    {
        fscanf(file, "%lu", rx_bytes);
        fclose(file);
    }
    else
    {
        *rx_bytes = 0;
    }

    snprintf(path, sizeof(path), "/sys/class/net/%s/statistics/tx_bytes", interface);
    file = fopen(path, "r");
    if (file)
    {
        fscanf(file, "%lu", tx_bytes);
        fclose(file);
    }
    else
    {
        *tx_bytes = 0;
    }
}

char *get_lan_ip()
{
    static char ip[16] = "0.0.0.0";
    FILE *fp = popen("ubus call network.interface.lan status | jsonfilter -e '@[\"ipv4-address\"][0].address'", "r");
    if (fp == NULL)
    {
        perror("Failed to run command");
        return ip;
    }

    if (fgets(ip, sizeof(ip), fp) != NULL)
    {

        char *newline = strchr(ip, '\n');
        if (newline)
            *newline = '\0';
    }
    else
    {
        strcpy(ip, "0.0.0.0");
    }

    pclose(fp);
    return ip;
}
#include "get_config.h"

int get_at_port_number(char *at_port_number, size_t size)
{
    FILE *file = fopen(CONFIG_FILE, "r");
    if (!file)
    {
        perror("Failed to open configuration file");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "option at_port"))
        {
            char *start = strstr(line, "ttyUSB");
            if (start)
            {
                snprintf(at_port_number, size, "%s", start + 6);
                char *newline = strchr(at_port_number, '\'');
                if (newline)
                    *newline = '\0';
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    fprintf(stderr, "Failed to find 'option at_port' in configuration file\n");
    return -1;
}

const char *get_display_mode()
{
    static char mode[16] = "system";
    FILE *file = fopen("/etc/config/lvgl-sysinfo", "r");
    if (!file)
    {
        perror("Failed to open /etc/config/lvgl-sysinfo");
        return mode;
    }

    char line[128];
    while (fgets(line, sizeof(line), file))
    {

        if (strstr(line, "option display_mode"))
        {

            char *start = strchr(line, '\'');
            if (start)
            {
                start++;
                char *end = strchr(start, '\'');
                if (end && (end - start) < sizeof(mode))
                {
                    strncpy(mode, start, end - start);
                    mode[end - start] = '\0';
                }
            }
        }
    }
    fclose(file);
    return mode;
}
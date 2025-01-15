#include "get_modem_info.h"

int get_rssi_from_modem(const char *port_number)
{
    char command[128];
    snprintf(command, sizeof(command), "sendat %s \"%s\"", port_number, AT_COMMAND);

    fprintf(stderr, "Executing command: %s\n", command);

    FILE *pipe = popen(command, "r");
    if (!pipe)
    {
        perror("Failed to execute sendat command");
        return -1;
    }

    char response[128];
    int rssi = -1;
    while (fgets(response, sizeof(response), pipe))
    {
        fprintf(stderr, "AT Command Response: %s", response);

        if (strstr(response, "+CSQ:"))
        {
            char *start = strchr(response, ':');
            if (start)
            {
                if (sscanf(start + 1, "%d", &rssi) == 1)
                {
                    break;
                }
            }
        }
    }

    pclose(pipe);

    if (rssi == -1)
    {
        fprintf(stderr, "Failed to parse RSSI value from AT command response\n");
    }
    return rssi;
}

/**
 * 获取 Modem 信息（RSRP、RSRQ、SINR）
 * @param port_number AT指令端口号，例如 "3"
 * @param info 存储解析后的 Modem 信息
 * @return 0 表示成功，-1 表示失败
 */
int get_modem_info(ModemInfo *info)
{
    char at_port_number[8];
    if (get_at_port_number(at_port_number, sizeof(at_port_number)) != 0)
    {
        fprintf(stderr, "Failed to get AT port number\n");
        return -1;
    }
    char command[128];
    snprintf(command, sizeof(command), "sendat %s \"AT+QENG=\\\"servingcell\\\"\"", at_port_number);

    FILE *pipe = popen(command, "r");
    if (!pipe)
    {
        perror("Failed to execute sendat command");
        return -1;
    }

    char response[256];
    memset(info, -1, sizeof(ModemInfo));

    while (fgets(response, sizeof(response), pipe))
    {

        if (strstr(response, "+QENG:"))
        {

            char *start = strstr(response, "+QENG:");
            if (start)
            {
                char *fields[20];
                int field_count = 0;

                char *token = strtok(start, ",");
                while (token && field_count < 20)
                {
                    fields[field_count++] = token;
                    token = strtok(NULL, ",");
                }

                if (field_count >= 16)
                {
                    info->rsrp = atoi(fields[12]);
                    info->rsrq = atoi(fields[13]);
                    info->sinr = atoi(fields[14]);

                    break;
                }
                else
                {
                    fprintf(stderr, "Unexpected number of fields: %d\n", field_count);
                }
            }
        }
    }

    pclose(pipe);

    if (info->rsrp == -1 || info->rsrq == -1 || info->sinr == -1)
    {
        fprintf(stderr, "Failed to parse Modem info\n");
        return -1;
    }

    return 0;
}
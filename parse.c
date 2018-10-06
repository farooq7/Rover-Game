#include "parse.h"
#include "common.h"
#include <stdlib.h>

void parse(char* json_string, struct PARSE_DATA* data)
{
    printf("Starting parse.\n");

    jsmn_parser jparse;
    jsmntok_t t[128];
    jsmn_init(&jparse);

    int r = jsmn_parse(&jparse, json_string, strlen(json_string), t, 20);
    int i;
    for (i = 1; i < r; i += 2)
    {
        char key[255], value[255];

        sprintf(key, "%.*s", t[i].end - t[i].start,
                json_string + t[i].start);
        sprintf(value, "%.*s", t[i+1].end - t[i+1].start,
                json_string + t[i+1].start);

        if (!strncmp(key, "cmd", 255))
        {
            strcpy(data->cmd, value);
        }
        else if (!strncmp(key, "seq", 255))
        {
            data->seq = atoi(value);
        }
        else if (!strncmp(key, "motor_left", 255))
        {
            data->motor_left = atoi(value);
        }
        else if (!strncmp(key, "motor_right", 255))
        {
            data->motor_right = atoi(value);
        }
    }
}

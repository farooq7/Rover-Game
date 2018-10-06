#ifndef _PARSE_H
#define _PARSE_H

#include <stdio.h>
#include <string.h>

#include "jsmn.h"

struct PARSE_DATA {
   char cmd[255];
   unsigned int seq;
   int motor_right;
   int motor_left;
};

void parse(char* json_string, struct PARSE_DATA* data);

#endif

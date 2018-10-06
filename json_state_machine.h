#ifndef _JSON_STATE_MACHINE_H
#define _JSON_STATE_MACHINE_H

#include "common.h"

typedef enum {
	before_open_curly = 0,
	close_curly = 1,
	backwards = 2,
	done = 3
} JSON_STATE;

void read_JSON_request(JSON_STATE * curr_state_json, char JSONmessage[255], char JSON_byte, int * curr_JSONchar);

#endif
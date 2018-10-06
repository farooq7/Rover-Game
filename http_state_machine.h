#ifndef _HTTP_STATE_MACHINE_H
#define _HTTP_STATE_MACHINE_H

#include "common.h"
/*
This state machine checks the validity of the HTTP request and passes all of the internal chars to the
JSON-parsing state machine.
*/

typedef enum {
	open0 = 0,
	open1 = 1,
	open2 = 2,
	open3 = 3,
	open4 = 4,
	open5 = 5,
	JSON_read = 6,
	close1 = 7,
	close2 = 8,
	close3 = 9,
	close4 = 10,
	close5 = 11
} HTTP_STATE;

int charCount = 0;

void parseHTTP(HTTP_STATE *curr_state, char message[255], char HTTP_byte, bool *flag);

#endif

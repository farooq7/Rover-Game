#ifndef _DEBUG_H
#define _DEBUG_H

#include "common.h"

// task constants
#define TASK_ENTER 1
#define TASK_BEFORE_WHILE 2
#define TASK_BEFORE_RECIEVE 3
#define TASK_AFTER_RECIEVE 4

// ISR constants
#define ISR_ENTER 5
#define ISR_EXIT 6
#define ISR_BEFORE_SEND 7
#define ISR_AFTER_SEND 8

// error constant
#define ERROR 63

void dbgOutputVal(unsigned int outVal);
void dbgUARTVal(unsigned char outVal);
void dbgOutputEvent(unsigned int outVal);
void dbgFail();
void dbgPulse();
void dbgInitialize();

#endif
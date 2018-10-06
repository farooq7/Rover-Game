#ifndef _COMMON_H    /* Guard against multiple inclusion */
#define _COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "system_config.h"
#include "system_definitions.h"
#include "http_state_machine.h"
#include "json_state_machine.h"
#include "motor_control.h"
#include "jsmn.h"
#include "debug.h"
#include "MotorThread.h"
#include "RXThread.h"
#include "TXThread.h"
#include "parse.h"

#define MAX_MESSAGE_SIZE    8    // Total size of bytes for contents
#define MAX_BUFFER_SIZE     255  // Number of bytes allowed to be held from the buffer
#define MAX_TOTAL_SIZE      10  // Total size of content and delimiters and extraneous data

//Commands
#define MOTOR_CONTROL 0x01
#define MOTOR_CALIBRATE 0x02

typedef struct {
    unsigned int sequenceNumber;
    //char command[1024];
    int command;
    signed int motorLeft;
    signed int motorRight;
} MOTOR_MESSAGE;

typedef struct 
{
    unsigned int rgbC;
    unsigned int rgbR;
    unsigned int rgbG;
    unsigned int rgbB;
    
    unsigned int rgbC1;
    unsigned int rgbR1;
    unsigned int rgbG1;
    unsigned int rgbB1;
} RGB_MESSAGE;

void initializeBuffer();

BaseType_t sendToTXBuffer(char msg);
BaseType_t sendToTXBufferFromISR(char msg);

BaseType_t sendToTXQueue(RGB_MESSAGE msg);
BaseType_t sendToTXQueueFromISR(RGB_MESSAGE msg);

BaseType_t sendToRXQueue(char msg);
BaseType_t sendToRXQueueFromISR(char msg);

BaseType_t sendToMotorQueue(MOTOR_MESSAGE msg);
BaseType_t sendToMotorQueueFromISR(MOTOR_MESSAGE msg);

unsigned int ISR_count = 0;
RGB_MESSAGE RGB_struct;
MOTOR_MESSAGE m_message;

#endif
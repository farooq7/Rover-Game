#include "rxthread.h"
#include "parse.h"

RXTHREAD_DATA rxData;

BaseType_t sendToRXQueue(char msg)
{
    xQueueSend(rxData.rxQueue, &msg, portMAX_DELAY);
}

BaseType_t sendToRXQueueFromISR(char msg)
{
    xQueueSendFromISR(rxData.rxQueue, &msg, 0);
}

void RXTHREAD_Initialize ( void )
{
    rxData.rxQueue = xQueueCreate(MAX_BUFFER_SIZE, 8);
    first_run = true;
}

void RXTHREAD_Tasks ( void )
{
    HTTP_STATE mystate;
    char queue_current_char;
    char HTTP_output[255];
    char HTTP_shifted[255];
    bool isParsed;
    
    MOTOR_MESSAGE MM;
    
    if(first_run == true)
    {
        mystate = open0;
        isParsed = false;
        first_run = false;
    }
   
    xQueueReceive(rxData.rxQueue, &queue_current_char, portMAX_DELAY);
    
    parseHTTP(&mystate, HTTP_output, queue_current_char, &isParsed);
    
    if(isParsed == true)
    {
        //get rid of first 4 empty bytes
        int i;
        for(i = 0; i < 250; i++)
        {
            HTTP_shifted[i] = HTTP_output[i+4];
        }
        
        //null-fill everything after the curly brace
        bool curly = false;
        for(i = 254; i > 60; i--)
        {
            if(curly == false)
            {
                if(HTTP_output[i] != '}')
                {
                    HTTP_output[i] = '\0';
                }
                else
                {
                    curly = true;
                }
            }
        }        
        
        MOTOR_MESSAGE MM;
        
        struct PARSE_DATA motorData;
        parse(HTTP_shifted, &motorData);
      
        MM.sequenceNumber = motorData.seq;
        
        if(!strncmp(motorData.cmd, "motor_control", 255))
        {
            MM.command = MOTOR_CONTROL;
        }
        else if(!strncmp(motorData.cmd, "motor_calibrate", 255))
        {
            MM.command = MOTOR_CALIBRATE;
        }
        
        MM.motorLeft = motorData.motor_left;
        MM.motorRight = motorData.motor_right;
        
        sendToMotorQueue(MM);
    }
}
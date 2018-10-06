#ifndef _TXTHREAD_H
#define _TXTHREAD_H

#include "common.h"
#include "driver/i2c/drv_i2c.h"

typedef struct
{
    QueueHandle_t           txQueue;
    DRV_HANDLE              handleI2C0;
    DRV_I2C_BUFFER_HANDLE   I2CBufferHandle;
    DRV_I2C_BUFFER_EVENT    I2CBufferEvent;
} TXTHREAD_DATA;

TXTHREAD_DATA txData;

void constructHTTP(char* request, char* json_message);
void sendRequest(char* http_request);

void TXTHREAD_Initialize ( void );
void TXTHREAD_Tasks( void );

#endif /* _TXTHREAD_H */
#ifndef _RXTHREAD_H
#define _RXTHREAD_H

#include "common.h"

typedef struct
{
    QueueHandle_t rxQueue;
} RXTHREAD_DATA;

void RXTHREAD_Initialize ( void );

void RXTHREAD_Tasks( void );

bool first_run;

#endif /* _RXTHREAD_H */
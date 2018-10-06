#ifndef _MOTORTHREAD_H
#define _MOTORTHREAD_H

#include "common.h"

typedef struct
{
   QueueHandle_t motorQueue;
} MOTORTHREAD_DATA;

//variables
uint16_t encoder1 = 0;  //left encoder counter
uint16_t encoder2 = 0;  //right encoder counter

//counts number of times 125ms timer has rolled over
//used to calibrate motor
unsigned int timer_counter = 0;

//holds encoder values at each of the below motor speeds
//1000, 1025, 1050, 1075, 1100, 1125, 1150, 1175, 1200, 1225, 1250, 1275, 
//1300, 1325, 1350, 1375, 1400, 1425, 1450, 1475, 1500, 1525, 1550, 1575, 1600
char motor1_forward_speeds[25];
char motor1_reverse_speeds[25];
char motor2_forward_speeds[25];
char motor2_reverse_speeds[25];

//array of all used pwm values
char pwm_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

//encoder minimum/maximum values
uint16_t encoder1_maximum;
uint16_t encoder2_maximum;
uint16_t encoder1_minimum;
uint16_t encoder2_minimum;

MOTORTHREAD_DATA motorData;

bool is_calibrating;    //=true in calibration mode, false when not in calibration mode

void MOTORTHREAD_Initialize ( void );

void MOTORTHREAD_Tasks( void );

void motorInitialize();

void calibrate_motors( void );

void find_minmax( void );


#endif /* _MOTORTHREAD_H */
#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H

#include <stdint.h>
#include "motorthread.h"
#include "peripheral/oc/plib_oc.h"

//set motor1 (left) direction and speed
void set_motor1(char direction, unsigned int speed);

//set motor2 (right) direction and speed)
void set_motor2(char direction, unsigned int speed);

//get motor speed
unsigned int get_motor_speed(unsigned int motor);

//get motor direction
char get_motor_direction(unsigned int motor);

void control_motors(signed int motorLeft, signed int motorRight);

unsigned int motor1_spd;
unsigned int motor2_spd;
char motor1_dir;
char motor2_dir;

#endif
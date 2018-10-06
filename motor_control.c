#include "motor_control.h"

void set_motor1(char direction, unsigned int speed)
{
    //set direction
    if(direction == 'F')
    {
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, 14);      //forward
        motor1_dir = 'F';
    }
    else if(direction == 'B')
    {
        PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, 14);    //reverse
        motor1_dir = 'B';
    }
    else
    {
        //direction error statement
    }
    
    //set speed (PWM)
    if(speed <= 1600 && speed >= 0)
    {
        DRV_OC0_PulseWidthSet(speed);
        motor1_spd = speed;
    }
    else
    {
        //speed error statement
    }
}

void set_motor2(char direction, unsigned int speed)
{
    //set direction
    if(direction == 'F')
    {
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, 1);      //forward
        motor2_dir = 'F';
    }
    else if(direction == 'B')
    {
        PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, 1);    //reverse
        motor2_dir = 'B';
    }
    else
    {
        //direction error statement
    }
    
    //set speed (PWM)
    if(speed <= 1600 && speed >= 0)
    {
        DRV_OC1_PulseWidthSet(speed);
        motor2_spd = speed;
    }
    else
    {
        //speed error statement
    }
}

unsigned int get_motor_speed(unsigned int motor)
{
    if(motor == 1)
    {
        return motor1_spd;
    }
    else if(motor == 2)
    {
        return motor2_spd;
    }
    //error statement
    return 0;
}

char get_motor_direction(unsigned int motor)
{
    if(motor == 1)
    {
        return motor1_dir;
    }
    else if(motor == 2)
    {
        return motor2_dir;
    }
    //error statement
    return '0';
}

void control_motors(signed int motorLeft, signed int motorRight)
{
    //decode motorLeft/motor1 speed/directions
    if(motorLeft == 10)
    {
        set_motor1('F', 1600);
    }
    else if(motorLeft == 9)
    {
        set_motor1('F', 1560);
    }
    else if(motorLeft == 8)
    {
        set_motor1('F', 1520);
    }
    else if(motorLeft == 7)
    {
        set_motor1('F', 1480);
    }
    else if(motorLeft == 6)
    {
        set_motor1('F', 1440);
    }
    else if(motorLeft == 5)
    {
        set_motor1('F', 1400);
    }
    else if(motorLeft == 4)
    {
        set_motor1('F', 1360);
    }
    else if(motorLeft == 3)
    {
        set_motor1('F', 1320);
    }
    else if(motorLeft == 2)
    {
        set_motor1('F', 1280);
    }
    else if(motorLeft == 1)
    {
        set_motor1('F', 1240);
    }
    else if(motorLeft == -10)
    {
        set_motor1('B', 1600);
    }
    else if(motorLeft == -9)
    {
        set_motor1('B', 1560);
    }
    else if(motorLeft == -8)
    {
        set_motor1('B', 1520);
    }
    else if(motorLeft == -7)
    {
        set_motor1('B', 1480);
    }
    else if(motorLeft == -6)
    {
        set_motor1('B', 1440);
    }
    else if(motorLeft == -5)
    {
        set_motor1('B', 1400);
    }
    else if(motorLeft == -4)
    {
        set_motor1('B', 1360);
    }
    else if(motorLeft == -3)
    {
        set_motor1('B', 1320);
    }
    else if(motorLeft == -2)
    {
        set_motor1('B', 1280);
    }
    else if(motorLeft == -1)
    {
        set_motor1('B', 1240);
    }
    else
    {
        set_motor1('F', 0);
    }
    
    //decode motorRight/motor2 speed/directions
    if(motorRight == 10)
    {
        set_motor2('F', 1600);
    }
    else if(motorRight == 9)
    {
        set_motor2('F', 1570);
    }
    else if(motorRight == 8)
    {
        set_motor2('F', 1540);
    }
    else if(motorRight == 7)
    {
        set_motor2('F', 1510);
    }
    else if(motorRight == 6)
    {
        set_motor2('F', 1480);
    }
    else if(motorRight == 5)
    {
        set_motor2('F', 1450);
    }
    else if(motorRight == 4)
    {
        set_motor2('F', 1420);
    }
    else if(motorRight == 3)
    {
        set_motor2('F', 1390);
    }
    else if(motorRight == 2)
    {
        set_motor2('F', 1360);
    }
    else if(motorRight == 1)
    {
        set_motor2('F', 1330);
    }
    else if(motorRight == -10)
    {
        set_motor2('B', 1600);
    }
    else if(motorRight == -9)
    {
        set_motor2('B', 1570);
    }
    else if(motorRight == -8)
    {
        set_motor2('B', 1540);
    }
    else if(motorRight == -7)
    {
        set_motor2('B', 1510);
    }
    else if(motorRight == -6)
    {
        set_motor2('B', 1480);
    }
    else if(motorRight == -5)
    {
        set_motor2('B', 1450);
    }
    else if(motorRight == -4)
    {
        set_motor2('B', 1420);
    }
    else if(motorRight == -3)
    {
        set_motor2('B', 1390);
    }
    else if(motorRight == -2)
    {
        set_motor2('B', 1360);
    }
    else if(motorRight == -1)
    {
        set_motor2('B', 1330);
    }
    else
    {
        set_motor2('F', 0);
    }
}
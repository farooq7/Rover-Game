#include "motorthread.h"

BaseType_t sendToMotorQueue(MOTOR_MESSAGE msg)
{
    xQueueSend(motorData.motorQueue, &msg, portMAX_DELAY);
}

BaseType_t sendToMotorQueueFromISR(MOTOR_MESSAGE msg)
{
    xQueueSendFromISR(motorData.motorQueue, &msg, 0);
}

void motorInitialize()
{
    //TO SETUP MOTORS:
    //connect ChipKit Pin 2 to ChipKit Pin 23   --  encoder1 setup
    //connect ChipKit Pin 7 to ChipKit Pin 11   --  encoder2 setup
    
    TRISCCLR = 1 << 14;
    TRISGCLR = 1 << 1;
    TRISDCLR = 1;
    TRISDCLR = 1 << 1;
    
    //B1 and B2 input signals from motor shield board
    TRISCSET = 1 << 4;  //motor 1 (left) encoder signal - T4CK = RC3
    TRISCSET = 1 << 3;  //motor 2 (right) encoder signal - T5CK = RC4
    
    //led5 setup
    TRISCCLR = 1 << 1;
    
    //debug outputs
    TRISECLR = 0b11111111;
    
    //start timers and comparators
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    DRV_TMR2_Start();
    DRV_TMR3_Start();
    
    DRV_OC0_Start();
    DRV_OC1_Start();
    
    //start motor as stopped
    set_motor1('F', 0);     //min 1000, max 1600
    set_motor2('F', 0);     //min 1000, max 1600
    
    //initialize is_calibrating as false
    is_calibrating = false;
}

void MOTORTHREAD_Initialize ( void )
{
    motorData.motorQueue = xQueueCreate(16, sizeof(MOTOR_MESSAGE));
    motorInitialize();
}

void MOTORTHREAD_Tasks ( void )
{
    dbgOutputEvent(is_calibrating);
    
    if(!is_calibrating)
    {
        xQueueReceive(motorData.motorQueue, &m_message, portMAX_DELAY);
        
        //dbgOutputEvent(m_message.command);
        
        if(m_message.command == MOTOR_CALIBRATE)
        {
            timer_counter = 0;
            calibrate_motors();
            find_minmax();
        }
        else if(m_message.command == MOTOR_CONTROL)
        {
            //read in motor1 and motor2 values and use them for control
            control_motors(m_message.motorLeft, m_message.motorRight);
        }
    }
    else
    {
        //DO NOTHNG BC CALIBRATING
        MOTOR_MESSAGE ignored;
        xQueueReceive(motorData.motorQueue, &ignored, portMAX_DELAY);
        
        calibrate_motors();
        find_minmax();
    }
}

void calibrate_motors( void )
{
    //cycle through all motor speeds, forwards & backwards, and store those values
    
    //FORWARD SPEEDS:
    
    is_calibrating = true;
    
    //1000
    if(timer_counter == 10)
    {
        set_motor1('F', 1000);     //min 800, max 1600
        set_motor2('F', 1000);
    }
    else if(timer_counter == 15)
    {
        motor1_forward_speeds[0] = encoder1;
        motor2_forward_speeds[0] = encoder2;
    }
    
    //1025
    else if(timer_counter == 20)
    {
        set_motor1('F', 1025);     //min 800, max 1600
        set_motor2('F', 1025);
    }
    else if(timer_counter == 25)
    {
        motor1_forward_speeds[1] = encoder1;
        motor2_forward_speeds[1] = encoder2;
    }
    
    //1050
    else if(timer_counter == 30)
    {
        set_motor1('F', 1050);     //min 800, max 1600
        set_motor2('F', 1050);
    }
    else if(timer_counter == 35)
    {
        motor1_forward_speeds[2] = encoder1;
        motor2_forward_speeds[2] = encoder2;
    }
    
    //1075
    else if(timer_counter == 40)
    {
        set_motor1('F', 1075);     //min 800, max 1600
        set_motor2('F', 1075);
    }
    else if(timer_counter == 45)
    {
        motor1_forward_speeds[3] = encoder1;
        motor2_forward_speeds[3] = encoder2;
    }
    
    //1100
    else if(timer_counter == 50)
    {
        set_motor1('F', 1100);     //min 800, max 1600
        set_motor2('F', 1100);
    }
    else if(timer_counter == 55)
    {
        motor1_forward_speeds[4] = encoder1;
        motor2_forward_speeds[4] = encoder2;
    }
    
    //1125
    else if(timer_counter == 60)
    {
        set_motor1('F', 1125);     //min 800, max 1600
        set_motor2('F', 1125);
    }
    else if(timer_counter == 65)
    {
        motor1_forward_speeds[5] = encoder1;
        motor2_forward_speeds[5] = encoder2;
    }
    
    //1150
    else if(timer_counter == 70)
    {
        set_motor1('F', 1150);     //min 800, max 1600
        set_motor2('F', 1150);
    }
    else if(timer_counter == 75)
    {
        motor1_forward_speeds[6] = encoder1;
        motor2_forward_speeds[6] = encoder2;
    }
    
    //1175
    else if(timer_counter == 80)
    {
        set_motor1('F', 1175);     //min 800, max 1600
        set_motor2('F', 1175);
    }
    else if(timer_counter == 85)
    {
        motor1_forward_speeds[7] = encoder1;
        motor2_forward_speeds[7] = encoder2;
    }
    
    //1200
    else if(timer_counter == 90)
    {
        set_motor1('F', 1200);     //min 800, max 1600
        set_motor2('F', 1200);
    }
    else if(timer_counter == 95)
    {
        motor1_forward_speeds[8] = encoder1;
        motor2_forward_speeds[8] = encoder2;
    }
    
    //1225
    else if(timer_counter == 100)
    {
        set_motor1('F', 1225);     //min 800, max 1600
        set_motor2('F', 1225);
    }
    else if(timer_counter == 105)
    {
        motor1_forward_speeds[9] = encoder1;
        motor2_forward_speeds[9] = encoder2;
    }
    
    //1250
    else if(timer_counter == 110)
    {
        set_motor1('F', 1250);     //min 800, max 1600
        set_motor2('F', 1250);
    }
    else if(timer_counter == 115)
    {
        motor1_forward_speeds[10] = encoder1;
        motor2_forward_speeds[10] = encoder2;
    }
    
    //1275
    else if(timer_counter == 120)
    {
        set_motor1('F', 1275);     //min 800, max 1600
        set_motor2('F', 1275);
    }
    else if(timer_counter == 125)
    {
        motor1_forward_speeds[11] = encoder1;
        motor2_forward_speeds[11] = encoder2;
    }
    
    //1300
    else if(timer_counter == 130)
    {
        set_motor1('F', 1300);     //min 800, max 1600
        set_motor2('F', 1300);
    }
    else if(timer_counter == 135)
    {
        motor1_forward_speeds[12] = encoder1;
        motor2_forward_speeds[12] = encoder2;
    }
    
    //1325
    else if(timer_counter == 140)
    {
        set_motor1('F', 1325);     //min 800, max 1600
        set_motor2('F', 1325);
    }
    else if(timer_counter == 145)
    {
        motor1_forward_speeds[13] = encoder1;
        motor2_forward_speeds[13] = encoder2;
    }
    
    //1350
    else if(timer_counter == 150)
    {
        set_motor1('F', 1350);     //min 800, max 1600
        set_motor2('F', 1350);
    }
    else if(timer_counter == 155)
    {
        motor1_forward_speeds[14] = encoder1;
        motor2_forward_speeds[14] = encoder2;
    }
    
    //1375
    else if(timer_counter == 160)
    {
        set_motor1('F', 1375);     //min 800, max 1600
        set_motor2('F', 1375);
    }
    else if(timer_counter == 165)
    {
        motor1_forward_speeds[15] = encoder1;
        motor2_forward_speeds[15] = encoder2;
    }
    
    //1400
    else if(timer_counter == 170)
    {
        set_motor1('F', 1400);     //min 800, max 1600
        set_motor2('F', 1400);
    }
    else if(timer_counter == 175)
    {
        motor1_forward_speeds[16] = encoder1;
        motor2_forward_speeds[16] = encoder2;
    }
    
    //1425
    else if(timer_counter == 180)
    {
        set_motor1('F', 1425);     //min 800, max 1600
        set_motor2('F', 1425);
    }
    else if(timer_counter == 185)
    {
        motor1_forward_speeds[17] = encoder1;
        motor2_forward_speeds[17] = encoder2;
    }
    
    //1450
    else if(timer_counter == 190)
    {
        set_motor1('F', 1450);     //min 800, max 1600
        set_motor2('F', 1450);
    }
    else if(timer_counter == 195)
    {
        motor1_forward_speeds[18] = encoder1;
        motor2_forward_speeds[18] = encoder2;
    }
    
    //1475
    else if(timer_counter == 200)
    {
        set_motor1('F', 1475);     //min 800, max 1600
        set_motor2('F', 1475);
    }
    else if(timer_counter == 205)
    {
        motor1_forward_speeds[19] = encoder1;
        motor2_forward_speeds[19] = encoder2;
    }
    
    //1500
    else if(timer_counter == 210)
    {
        set_motor1('F', 1500);     //min 800, max 1600
        set_motor2('F', 1500);
    }
    else if(timer_counter == 215)
    {
        motor1_forward_speeds[20] = encoder1;
        motor2_forward_speeds[20] = encoder2;
    }
    
    //1525
    else if(timer_counter == 220)
    {
        set_motor1('F', 1525);     //min 800, max 1600
        set_motor2('F', 1525);
    }
    else if(timer_counter == 225)
    {
        motor1_forward_speeds[21] = encoder1;
        motor2_forward_speeds[21] = encoder2;
    }
    
    //1550
    else if(timer_counter == 230)
    {
        set_motor1('F', 1550);     //min 800, max 1600
        set_motor2('F', 1550);
    }
    else if(timer_counter == 235)
    {
        motor1_forward_speeds[22] = encoder1;
        motor2_forward_speeds[22] = encoder2;
    }
    
    //1575
    else if(timer_counter == 240)
    {
        set_motor1('F', 1575);     //min 800, max 1600
        set_motor2('F', 1575);
    }
    else if(timer_counter == 245)
    {
        motor1_forward_speeds[23] = encoder1;
        motor2_forward_speeds[23] = encoder2;
    }
    
    //1600
    else if(timer_counter == 250)
    {
        set_motor1('F', 1600);     //min 800, max 1600
        set_motor2('F', 1600);
    }
    else if(timer_counter == 255)
    {
        motor1_forward_speeds[24] = encoder1;
        motor2_forward_speeds[24] = encoder2;
    }
    
    //REVERSE SPEEDS:
    
    //1000
    if(timer_counter == 260)
    {
        set_motor1('B', 1000);     //min 800, max 1600
        set_motor2('B', 1000);
    }
    else if(timer_counter == 265)
    {
        motor1_reverse_speeds[0] = encoder1;
        motor2_reverse_speeds[0] = encoder2;
    }
    
    //1025
    else if(timer_counter == 270)
    {
        set_motor1('B', 1025);     //min 800, max 1600
        set_motor2('B', 1025);
    }
    else if(timer_counter == 275)
    {
        motor1_reverse_speeds[1] = encoder1;
        motor2_reverse_speeds[1] = encoder2;
    }
    
    //1050
    else if(timer_counter == 280)
    {
        set_motor1('B', 1050);     //min 800, max 1600
        set_motor2('B', 1050);
    }
    else if(timer_counter == 285)
    {
        motor1_reverse_speeds[2] = encoder1;
        motor2_reverse_speeds[2] = encoder2;
    }
    
    //1075
    else if(timer_counter == 290)
    {
        set_motor1('B', 1075);     //min 800, max 1600
        set_motor2('B', 1075);
    }
    else if(timer_counter == 295)
    {
        motor1_reverse_speeds[3] = encoder1;
        motor2_reverse_speeds[3] = encoder2;
    }
    
    //1100
    else if(timer_counter == 300)
    {
        set_motor1('B', 1100);     //min 800, max 1600
        set_motor2('B', 1100);
    }
    else if(timer_counter == 305)
    {
        motor1_reverse_speeds[4] = encoder1;
        motor2_reverse_speeds[4] = encoder2;
    }
    
    //1125
    else if(timer_counter == 310)
    {
        set_motor1('B', 1125);     //min 800, max 1600
        set_motor2('B', 1125);
    }
    else if(timer_counter == 315)
    {
        motor1_reverse_speeds[5] = encoder1;
        motor2_reverse_speeds[5] = encoder2;
    }
    
    //1150
    else if(timer_counter == 320)
    {
        set_motor1('B', 1150);     //min 800, max 1600
        set_motor2('B', 1150);
    }
    else if(timer_counter == 325)
    {
        motor1_reverse_speeds[6] = encoder1;
        motor2_reverse_speeds[6] = encoder2;
    }
    
    //1175
    else if(timer_counter == 330)
    {
        set_motor1('B', 1175);     //min 800, max 1600
        set_motor2('B', 1175);
    }
    else if(timer_counter == 335)
    {
        motor1_reverse_speeds[7] = encoder1;
        motor2_reverse_speeds[7] = encoder2;
    }
    
    //1200
    else if(timer_counter == 340)
    {
        set_motor1('B', 1200);     //min 800, max 1600
        set_motor2('B', 1200);
    }
    else if(timer_counter == 345)
    {
        motor1_reverse_speeds[8] = encoder1;
        motor2_reverse_speeds[8] = encoder2;
    }
    
    //1225
    else if(timer_counter == 350)
    {
        set_motor1('B', 1225);     //min 800, max 1600
        set_motor2('B', 1225);
    }
    else if(timer_counter == 355)
    {
        motor1_reverse_speeds[9] = encoder1;
        motor2_reverse_speeds[9] = encoder2;
    }
    
    //1250
    else if(timer_counter == 360)
    {
        set_motor1('B', 1250);     //min 800, max 1600
        set_motor2('B', 1250);
    }
    else if(timer_counter == 365)
    {
        motor1_reverse_speeds[10] = encoder1;
        motor2_reverse_speeds[10] = encoder2;
    }
    
    //1275
    else if(timer_counter == 370)
    {
        set_motor1('B', 1275);     //min 800, max 1600
        set_motor2('B', 1275);
    }
    else if(timer_counter == 375)
    {
        motor1_reverse_speeds[11] = encoder1;
        motor2_reverse_speeds[11] = encoder2;
    }
    
    //1300
    else if(timer_counter == 380)
    {
        set_motor1('B', 1300);     //min 800, max 1600
        set_motor2('B', 1300);
    }
    else if(timer_counter == 385)
    {
        motor1_reverse_speeds[12] = encoder1;
        motor2_reverse_speeds[12] = encoder2;
    }
    
    //1325
    else if(timer_counter == 390)
    {
        set_motor1('B', 1325);     //min 800, max 1600
        set_motor2('B', 1325);
    }
    else if(timer_counter == 395)
    {
        motor1_reverse_speeds[13] = encoder1;
        motor2_reverse_speeds[13] = encoder2;
    }
    
    //1350
    else if(timer_counter == 400)
    {
        set_motor1('B', 1350);     //min 800, max 1600
        set_motor2('B', 1350);
    }
    else if(timer_counter == 405)
    {
        motor1_reverse_speeds[14] = encoder1;
        motor2_reverse_speeds[14] = encoder2;
    }
    
    //1375
    else if(timer_counter == 410)
    {
        set_motor1('B', 1375);     //min 800, max 1600
        set_motor2('B', 1375);
    }
    else if(timer_counter == 415)
    {
        motor1_reverse_speeds[15] = encoder1;
        motor2_reverse_speeds[15] = encoder2;
    }
    
    //1400
    else if(timer_counter == 420)
    {
        set_motor1('B', 1400);     //min 800, max 1600
        set_motor2('B', 1400);
    }
    else if(timer_counter == 425)
    {
        motor1_reverse_speeds[16] = encoder1;
        motor2_reverse_speeds[16] = encoder2;
    }
    
    //1425
    else if(timer_counter == 430)
    {
        set_motor1('B', 1425);     //min 800, max 1600
        set_motor2('B', 1425);
    }
    else if(timer_counter == 435)
    {
        motor1_reverse_speeds[17] = encoder1;
        motor2_reverse_speeds[17] = encoder2;
    }
    
    //1450
    else if(timer_counter == 440)
    {
        set_motor1('B', 1450);     //min 800, max 1600
        set_motor2('B', 1450);
    }
    else if(timer_counter == 445)
    {
        motor1_reverse_speeds[18] = encoder1;
        motor2_reverse_speeds[18] = encoder2;
    }
    
    //1475
    else if(timer_counter == 450)
    {
        set_motor1('B', 1475);     //min 800, max 1600
        set_motor2('B', 1475);
    }
    else if(timer_counter == 455)
    {
        motor1_reverse_speeds[19] = encoder1;
        motor2_reverse_speeds[19] = encoder2;
    }
    
    //1500
    else if(timer_counter == 460)
    {
        set_motor1('B', 1500);     //min 800, max 1600
        set_motor2('B', 1500);
    }
    else if(timer_counter == 465)
    {
        motor1_reverse_speeds[20] = encoder1;
        motor2_reverse_speeds[20] = encoder2;
    }
    
    //1525
    else if(timer_counter == 470)
    {
        set_motor1('B', 1525);     //min 800, max 1600
        set_motor2('B', 1525);
    }
    else if(timer_counter == 475)
    {
        motor1_reverse_speeds[21] = encoder1;
        motor2_reverse_speeds[21] = encoder2;
    }
    
    //1550
    else if(timer_counter == 480)
    {
        set_motor1('B', 1550);     //min 800, max 1600
        set_motor2('B', 1550);
    }
    else if(timer_counter == 485)
    {
        motor1_reverse_speeds[22] = encoder1;
        motor2_reverse_speeds[22] = encoder2;
    }
    
    //1575
    else if(timer_counter == 490)
    {
        set_motor1('B', 1575);     //min 800, max 1600
        set_motor2('B', 1575);
    }
    else if(timer_counter == 495)
    {
        motor1_reverse_speeds[23] = encoder1;
        motor2_reverse_speeds[23] = encoder2;
    }
    
    //1600
    else if(timer_counter == 500)
    {
        set_motor1('B', 1600);     //min 800, max 1600
        set_motor2('B', 1600);
    }
    else if(timer_counter == 505)
    {
        motor1_reverse_speeds[24] = encoder1;
        motor2_reverse_speeds[24] = encoder2;
    }
    
    //stop motors
    else if(timer_counter >= 510)
    {
        set_motor1('F', 0);     
        set_motor2('F', 0);
        is_calibrating = false;
    }
}

//calculate encoder minimums/maximums
void find_minmax( void )
{
    unsigned int i;
    for(i = 0; i < 24; i++)
    {
        if(motor1_forward_speeds[i] > encoder1_maximum)
        {
            encoder1_maximum = pwm_values[i];
        }
        
        if(motor2_forward_speeds[i] > encoder2_maximum)
        {
            encoder2_maximum = pwm_values[i];
        }
        
        if(motor1_forward_speeds[i] == 33 || motor1_forward_speeds[i] == 34)
        {
            encoder1_minimum = pwm_values[i];
        }
        
        if(motor2_forward_speeds[i] == 33 || motor2_forward_speeds[i] == 34)
        {
            encoder2_minimum = pwm_values[i];
        }
    }
}

#include "rgb_sensor.h"
#include "TXThread.h"
#include <math.h>

void DRV_TCS_Init()
{
    bool appInitialized = true;
            
    if (txData.handleI2C0 == DRV_HANDLE_INVALID)
    {
        txData.handleI2C0 = DRV_I2C_Open(TXTHREAD_DRV_I2C_INDEX, DRV_IO_INTENT_READWRITE);
        appInitialized &= ( DRV_HANDLE_INVALID != txData.handleI2C0 );
    }
    
    if ((BufferHandle == NULL) || (DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_COMPLETE) || (DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_ERROR))
    {
        unsigned char message[2];
        message[0] = (TCS_COMMAND_SELECT_MASK | TCS_ENABLE_REGISTER);
        message[1] = (TCS_COMMAND_AUTO_INCREMENT);
        BufferHandle = DRV_I2C_Transmit(txData.handleI2C0, TCS_I2C_ADDRESS << 1, message, 2, NULL);
    }
    
    while(1)
    {
        if ((DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_COMPLETE) || (DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_ERROR))
        {
            unsigned char send_buffer[2];
            send_buffer[0] = (TCS_ENABLE_REGISTER & TCS_REGISTER_ADDRESS_MASK) | (TCS_COMMAND_SELECT_MASK);
            send_buffer[1] = (TCS_ENABLE_PON_MASK | TCS_ENABLE_AEN_MASK);
            BufferHandle = DRV_I2C_Transmit(txData.handleI2C0, TCS_I2C_ADDRESS << 1, send_buffer, 2, NULL);
            break;
        }
    }
    
    while(1)
    {
        if ((DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_COMPLETE) || (DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_ERROR))
        {         
            unsigned char send_buffer1[2];
            send_buffer1[0] = (TCS_RGBC_TIMING_REGISTER & TCS_REGISTER_ADDRESS_MASK) | (TCS_COMMAND_SELECT_MASK);
            send_buffer1[1] = 0x00;
            BufferHandle = DRV_I2C_Transmit(txData.handleI2C0, TCS_I2C_ADDRESS << 1, send_buffer1, 2, NULL);
            break;
        }
    }
    
    while(1)
    {
        if ((DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_COMPLETE) || (DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_ERROR))
        {         
            unsigned char send_buffer2[2];
            send_buffer2[0] = (TCS_CONTROL_REGISTER & TCS_REGISTER_ADDRESS_MASK) | (TCS_COMMAND_SELECT_MASK);
            send_buffer2[1] = (TCS_AGAIN_4X & TCS_CONTROL_AGAIN_MASK);
            BufferHandle = DRV_I2C_Transmit(txData.handleI2C0, TCS_I2C_ADDRESS << 1, send_buffer2, 2, NULL);
            break;
        }
    }
}

RGB_MESSAGE DRV_TCS_GetData()
{
    RGB_MESSAGE rgbmsg;
    while(1)
    {
        if ((BufferHandle == NULL) || (DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_COMPLETE) || (DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_ERROR))
        {
            unsigned char address = TCS_RGBC_CLEAR_LOW_REGISTER;
            address &= TCS_REGISTER_ADDRESS_MASK;
            address |= (TCS_COMMAND_SELECT_MASK);
            BufferHandle = DRV_I2C_TransmitThenReceive (txData.handleI2C0, TCS_I2C_ADDRESS << 1, &address, 1, ColorData, 8, NULL);
            break;
        }
    }
       
    while(1)
    {
        if ((BufferHandle == NULL) || (DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_COMPLETE) || (DRV_I2C_TransferStatusGet(txData.handleI2C0, BufferHandle) == DRV_I2C_BUFFER_EVENT_ERROR))
        {
            unsigned int c, r, g ,b;
               
            c = ColorData[0] | (ColorData[1] << 8);
            r = ColorData[2] | (ColorData[3] << 8);
            g = ColorData[4] | (ColorData[5] << 8);
            b = ColorData[6] | (ColorData[7] << 8);
            
            uint32_t sum = c;
            static float r1, g1, b1;
            r1 = r; r1 /= sum;
            g1 = g; g1 /= sum;
            b1 = b; b1 /= sum;
            r1 *= 255; g1 *= 255; b1 *= 255;
            
            rgbmsg.rgbC = c;
            rgbmsg.rgbR = r1;
            rgbmsg.rgbG = g1;
            rgbmsg.rgbB = b1;
            
            rgbmsg.rgbC1 = c;
            rgbmsg.rgbR1 = r;
            rgbmsg.rgbG1 = g;
            rgbmsg.rgbB1 = b;
            
            return rgbmsg;
            break;
        }
    }
}

void callbackSensorTimer(TimerHandle_t timer)
{
    RGB_MESSAGE msg = DRV_TCS_GetData();
    sendToTXQueueFromISR(msg);
    
    timer_counter++;
    
    //get encoder values
    encoder1 = DRV_TMR2_CounterValueGet();
    encoder2 = DRV_TMR3_CounterValueGet();
    
    //write encoder2 values
    if(timer_counter < 520)
    {
        //PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, encoder2);
    }
    
    //write out encoder2 maximum value
    else if(timer_counter % 2 == 1)
    {
        //encoder2_minimum = PWM value on range 0-24
        //real PWM value (max of 1600) = (encoder2_minimum*25)+1000
        //PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, encoder2_minimum);
    }
    
    //write out encoder2 minimum value
    else
    {
        //encoder2_maximum = PWM value on range 0-24
        //real PWM value (max of 1600) = (encoder2_maximum*25)+1000
        //PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, encoder2_maximum);
    }

    //clear encoder timers
    DRV_TMR2_CounterValueSet(0);
    DRV_TMR3_CounterValueSet(0); 
    
    dbgPulse();
}

void initializeSensorTimer()
{
    TimerHandle_t irTimer;
    
    irTimer = xTimerCreate
                 ( "irTimerString",
                   (200 / portTICK_PERIOD_MS),
                   pdTRUE,
                   (void *) 2,
                   callbackSensorTimer);
    
    xTimerStart(irTimer,0);
}
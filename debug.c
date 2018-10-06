#include "debug.h"

// local variables
bool dbgLD5;

void dbgOutputVal(unsigned int outVal)
{
    if (outVal > 127)
    {
        return;
    }
    //LATB = outVal << 8;
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_B, (outVal << 8));
}

void dbgOutputEvent(unsigned int outVal)
{
    if (outVal > 127)
    {
        return;
    }
//    else if(outVal == ERROR)
//    {
//        dbgFail();
//    }
    else
    {
        //LATE = outVal & 0x00FF;
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, outVal);
    }
}

void dbgFail()
{
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, ERROR);    //output ERROR value over GPIO event pins
    
    LATASET = 1 << 3;           //turn on LED4
    
    vTaskSuspendAll();          //stop all apps
    
    SYS_INT_Disable();          //turn off global interrupts
    
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, ERROR);    //output ERROR value over GPIO event pins
    while(1){}
}

void dbgPulse()
{
    LATCINV = 1 << 1;
}

void dbgInitialize()
{
    // LD5 (pulse)
    TRISCCLR = 1 << 1;
    LATCSET = 1 << 1;
    dbgLD5 = true;

    // LD4 (fail))
    TRISACLR = 1 << 3;
    LATACLR = 1 << 3;

    // output event
    TRISBCLR = 0xFF00;

    // output value
    TRISECLR = 0x00FF;
}
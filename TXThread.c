#include "txthread.h"
#include <string.h>
#include <math.h>

BaseType_t sendToTXQueue(RGB_MESSAGE msg)
{
    xQueueSend(txData.txQueue, &msg, portMAX_DELAY);
}

BaseType_t sendToTXQueueFromISR(RGB_MESSAGE msg)
{
    xQueueSendFromISR(txData.txQueue, &msg, 0);
}
uint16_t defColors[6][3] = {
  {177, 50, 46},
  {39, 134, 68},
  {27, 91, 128},
  {179, 166, 63},
  {65, 101, 79},
  {185, 255, 255}
};

void constructHTTP(char* request, char* json_message)
{
    int content_length = 0;
    char c = json_message[0];
    while (c != '\0')
    {
        content_length++;
        c = json_message[content_length];
    }
    sprintf(request, "\
POST /api/rover HTTP/1.0\r\n\
Connection: keep-alive\r\n\
Content-Type: application/json\r\n\
Content-Length: %d\r\n\r\n%s\r\n",
            content_length, json_message);
}

void constructJSON(char* json_message, RGB_MESSAGE data, int seq)
{   
    unsigned int c, r, g ,b, c1, r1, g1, b1;
    int index = -1;
    int dist = 10000;
    int aux, j;
    
    c = data.rgbC;
    r = data.rgbR;
    g = data.rgbG;
    b = data.rgbB;
    c1 = data.rgbC1;
    r1 = data.rgbR1;
    g1 = data.rgbG1;
    b1 = data.rgbB1;
   
    for (j = 0 ; j < 6 ; j++) 
    {
        aux = sqrt( ((r - defColors[j][0])*(r - defColors[j][0])) + ((g - defColors[j][1])*(g - defColors[j][1])) + ((b - defColors[j][2])*(b - defColors[j][2]) ));
    
        if (aux < dist) 
        {
          dist = aux;
          index = j;
        }
    }
    
    /*if(index == 0)      //red
    {
        sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"red\"}",
                seq, r, g, b);
    }
    else if(index == 1) //green
    {
        sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"green\"}",
                seq, r, g, b);
    }
    else if(index == 2) //blue
    {
        sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"blue\"}",
                seq, r, g, b);
    }
    else if(index == 3) //yellow
    {
        sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"yellow\"}",
                seq, r, g, b);
    }
    else if(index == 4) //black
    {
        sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"black\"}",
                seq, r, g, b);
    }
    else if(index == 5) //white/undefined
    {
        sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"white\"}",
                seq, r, g, b);
    }*/
    
     if((r >= 162 && r <= 192) && (g >= 35 && g <= 65) && (b >= 31 && b <= 61))
    {
       sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"red\"}",
                seq, r, g, b);
    }
    else if((r >= 24 && r <= 54) && (g >= 119 && g <= 149) && (b >= 53 && b <= 83))
    {
       sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"green\"}",
                seq, r, g, b);
    }
    else if((r >= 12 && r <= 42) && (g >= 76 && g <= 106) && (b >= 113 && b <= 143))
    {
       sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"blue\"}",
                seq, r, g, b);
    }
    else if((r >= 164 && r <= 210) && (g >= 151 && g <= 200) && (b >= 48 && b <= 78))
    {
       sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"yellow\"}",
                seq, r, g, b);
    }
    else if((r >= 42 && r <= 80) && (g >= 76 && g <= 126) && (b >= 60 && b <= 110))
    {
         sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"black\"}",
                seq, r, g, b);
    }
    else if((r >= 160) && (g >= 200) && (b >= 200))
    {
       sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"white\"}",
                seq, r, g, b);
    }
    else
    {
       sprintf(json_message, "{\"seq\": %d, \"data\": \"RGB\", \"rgb_r\": %d, \"rgb_g\": %d, \"rgb_b\": %d, \"color\": \"undefined\"}",
                seq, r, g, b);
    }
}

void sendRequest(char* http_request)
{
    int i = 0;
    char c = http_request[0];
    while (c != '\0')
    {
        sendToTXBuffer(c);
        i++;
        c = http_request[i];
    }
    sendToTXBuffer('\n'); // finish request with blank line
}

void TXTHREAD_Initialize ( void )
{
    txData.handleI2C0 = DRV_HANDLE_INVALID;
    txData.txQueue = xQueueCreate(16, sizeof(RGB_MESSAGE));
}

void TXTHREAD_Tasks ( void )
{
    DRV_TCS_Init();
    initializeSensorTimer();
    
    RGB_MESSAGE data;
    int seq = 0;
    
    while(1)
    {
        while(!xQueueReceive(txData.txQueue, &data, portMAX_DELAY));
        char json_message[255];
        constructJSON(json_message, data, seq);
        char http_request[255];
        constructHTTP(http_request, json_message);
        sendRequest(http_request);
        seq++;
    }
}
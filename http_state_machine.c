#include "http_state_machine.h"

void parseHTTP(HTTP_STATE *curr_state, char message[255], char HTTP_byte, bool *parse)
{
    switch (*curr_state)
	{
	case open0:
		if (HTTP_byte == '{')
		{
            message[charCount] = HTTP_byte;
            charCount++;
            *parse = false;
            *curr_state = JSON_read;
		}
		else
		{
			*curr_state = open0;
			charCount = 4;
		}
        
		break;
        
    case JSON_read:
        if (HTTP_byte == '}')
		{
            *curr_state = close1;
			message[charCount] = HTTP_byte;
			charCount++;
		}
		else
		{
            message[charCount] = HTTP_byte;
            charCount++;
		}
        
		break;

	case close1:
		*parse = true;
        message[charCount] = '\0';
        charCount = 4;
        *curr_state = open0;
		break;

    default:
		//error statement here?
		break;
    }
}

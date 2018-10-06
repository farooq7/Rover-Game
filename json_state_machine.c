#include "json_state_machine.h"

void read_JSON_request(JSON_STATE * curr_state_json, char JSONmessage[255], char JSON_byte, int * curr_JSONchar)
{
	switch (*curr_state_json)
	{
	case before_open_curly:
		if (JSON_byte != '{')
		{
			*curr_state_json = before_open_curly;
			*curr_JSONchar = 0;
		}
		else
		{
			JSONmessage[*curr_JSONchar] = JSON_byte;
			(*curr_JSONchar)++;
			*curr_state_json = close_curly;
		}
		break;

	case close_curly:
		if (JSON_byte != '\0')
		{
			*curr_state_json = close_curly;
			JSONmessage[*curr_JSONchar] = JSON_byte;
			(*curr_JSONchar)++;
		}
		else
		{
			//JSONmessage[*curr_JSONchar] = '\0';
			//(*curr_JSONchar)--;
			*curr_state_json = backwards;
		}
		break;

	case backwards:
		if (JSONmessage[*curr_JSONchar] != '}')
		{
			JSONmessage[*curr_JSONchar] = '\0';
			(*curr_JSONchar)--;
			*curr_state_json = backwards;
		}
		else if(JSONmessage[*curr_JSONchar] == '}')
		{
			JSONmessage[*curr_JSONchar] = '}';
			*curr_state_json = done;
		}
		break;
	case done:
		break;

	default:
		break;
	}
}

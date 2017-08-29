
#include "InputGetter.h"




INPUT_RECORD* eventBuffer;
DWORD numEventsRead;

vec2 mouse{ 0, 0 };
bool lclick = false;
bool rclick = false;
bool shouldExit = false;



//I did not write this function
DWORD getInput(INPUT_RECORD **evB)
{
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;

	GetNumberOfConsoleInputEvents(hstdin, &numEvents);

	if (numEvents)
	{
		*evB = (INPUT_RECORD*)malloc(sizeof(INPUT_RECORD) * numEvents);
		//ORIGINAL CODE
		//*eventBuffer = malloc(sizeof(INPUT_RECORD) * numEvents);

		ReadConsoleInput(hstdin, *evB, numEvents, &numEventsRead);
	}

	return numEventsRead;
}

void checkInput()
{
	numEventsRead = getInput(&eventBuffer);

	if (numEventsRead)
	{
		for (int i = 0; i < numEventsRead; ++i)
		{
			switch (eventBuffer[i].EventType)
			{
			case KEY_EVENT:
				if (eventBuffer[i].Event.KeyEvent.bKeyDown)
				{
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
					{
					case VK_ESCAPE:
						shouldExit = true;
					}
				}
				break;
			case MOUSE_EVENT:
				if (eventBuffer[i].Event.MouseEvent.dwButtonState == 0x0001)
				{
					lclick = true;
				}
				if (eventBuffer[i].Event.MouseEvent.dwButtonState == 0x0002)
				{
					rclick = true;
				}
				if (eventBuffer[i].Event.MouseEvent.dwEventFlags == 0x0001)
				{
					mouse.x = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					mouse.y = WIN_HEIGHT - 1 - eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;

				}
				else if (eventBuffer[i].Event.MouseEvent.dwEventFlags == 0x0000)
				{

				}
				break;
			}
		}
	}
}

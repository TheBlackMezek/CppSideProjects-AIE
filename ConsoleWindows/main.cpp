

//#include <windows.h>
#include <iostream>
#include <time.h>

#include "WindowSetup.h"
#include "Screen.h"
#include "ScreenElement.h"
#include "TextButton.h"



struct vec2
{
	int x;
	int y;
};





DWORD getInput(INPUT_RECORD **eventBuffer);
//Returns the distance between two points
float dist(int x1, int y1, int x2, int y2);

void renderWindow();


// ---------- FANCY CONSOLE STUFF ---------- //
vec2 lastpos{ 0, 0 };

INPUT_RECORD* eventBuffer;
DWORD numEventsRead;
// ----------------------------------------- //



vec2 mouse{ 0, 0 };
bool left = false;
bool right = false;
bool up = false;
bool down = false;
bool lclick = false;
bool rclick = false;

Screen test;
TextButton testButton;









int main()
{
	srand(time(NULL));


	//// ---------- WINDOW SETUP ---------- //

	WindowSetup();


	test = Screen();
	test.setSize(WIN_WIDTH, WIN_HEIGHT);
	test.makeImage(); //Unnecessary, but here unless you forget to do it later
	// -------------------------------- //

	
	ElementData testButElmDat = ScreenElement::makeElementData(10, 10, 6, 3, 0x000F);
	ButtonData testButDat = TextButton::makeButtonData("Test", NULL);
	TextButton::makeImage(&testButElmDat, &testButDat);

	Component cp = { true };

	ElementData button2 =  ScreenElement::makeElementData(20, 20, 10, 4, 0x000A);
	ButtonData buttondat2 = TextButton::makeButtonData("Test2", NULL);
	TextButton::makeImage(&button2, &buttondat2);


	//test.addElement(testButton);
	int butIdx = test.addElement(testButElmDat);
	test.addButton(butIdx, testButDat);

	butIdx = test.addElement(button2);
	test.addButton(butIdx, buttondat2);

	test.makeImage();






	while (true)
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
							return 0;
						case 0x57: //W
							up = true;
							break;
						case 0x41: //A
							left = true;
							break;
						case 0x53: //S
							down = true;
							break;
						case 0x44: //D
							right = true;
							break;
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

		test.update(mouse.x, WIN_HEIGHT - mouse.y);

		renderWindow();
	}



	std::cin.get();

	return 0;
}



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

float dist(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(((float)x2 - (float)x1), 2) + pow(((float)y2 - (float)y1), 2));
}





void renderWindow()
{

	//Renders from top-left to bottom-right
	//The y loop increments backwards here so tiles can be set intuitively elsewhere
	std::vector<CharData> image = test.getImage();
	int bufferCoord = 0;
	for (int y = WIN_HEIGHT - 1; y >= 0; --y)
	{
		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			char chr = 0;
			int frontColor = 0;
			int backColor = 0;
			int color = 0;

			
			/*if (mouse.x == x && mouse.y == y)
			{
				backColor = 0x00F0;
			}

			frontColor = 0x000F;*/
			chr = image[bufferCoord].chr;
			color = image[bufferCoord].color;

			

			consoleBuffer[bufferCoord].Char.AsciiChar = chr;
			consoleBuffer[bufferCoord].Attributes = color;
			++bufferCoord;
		}
	}



	

	WriteConsoleOutputA(hstdout, consoleBuffer, charBufferSize, charPosition, &consoleWriteArea);
}


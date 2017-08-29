

//#include <windows.h> //This is in WindowSetup.h
#include <iostream>
#include <time.h>

//#include "WindowSetup.h" //This is in InputGetter.h
#include "InputGetter.h"
#include "Screen.h"
#include "DataMaker.h"
#include "ImageMaker.h"









//Returns the distance between two points
float dist(int x1, int y1, int x2, int y2);

void renderWindow();




Screen test;









int main()
{
	srand(time(NULL));


	//// ---------- WINDOW SETUP ---------- //
	WindowSetup();

	test = Screen();
	test.setSize(WIN_WIDTH, WIN_HEIGHT);
	test.makeImage(); //Unnecessary, but here unless you forget to do it later
	// -------------------------------- //

	
	ElementData testButElmDat = makeElementData(10, 10, 6, 3, 0x000F);
	ButtonData testButDat = makeButtonData(false, "Test", NULL);
	//TextButton::makeImage(&testButElmDat, &testButDat);
	makeButtonImage(&testButElmDat, &testButDat);

	ElementData button2 =  makeElementData(20, 20, 10, 4, 0x000A);
	ButtonData buttondat2 = makeButtonData(true, "Test2", NULL);
	makeButtonImage(&button2, &buttondat2);
	//TextButton::makeImage(&button2, &buttondat2);


	//test.addElement(testButton);
	int butIdx = test.addElement(testButElmDat);
	test.addButton(butIdx, testButDat);

	butIdx = test.addElement(button2);
	test.addButton(butIdx, buttondat2);

	test.makeImage();






	while (!shouldExit)
	{
		checkInput();

		test.update(mouse.x, WIN_HEIGHT - mouse.y);

		renderWindow();
	}




	return 0;
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


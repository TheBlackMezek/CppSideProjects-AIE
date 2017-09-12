

#include <iostream>
//#include <Windows.h>

//#include "structs.h"
#include "WindowSetup.h"
#include "InputGetter.h"
#include "ImageMaker.h"
#include "DataMaker.h"
#include "GameScreens.h"
#include "Player.h"
#include "GameScreen.h"
//#include "Screen.h"


//Gets word i from the string, words being separated by spaces
std::string getWord(std::string s, int i);

void renderWindow();




//------ PLAYER DATA ------//
//const int baySize = 10;
//int itemsInBay = 0;
//cargo bay[baySize];
//float maxFuel = 100.0f;
//float fuel = maxFuel;
//int loc = 2;
//int money = 200;
//std::string shipName = "";
//-------------------------//









int main()
{


	//This puts all the data in gal[]
	//This needs to come before initScreens()
	//initGalaxy();
	Player();

	


	printf("Welcome to Space Trader!\n");
	printf("Enter the name of your ship:\n");
	//std::getline(std::cin, shipName);
	//brk();
	//printf("Welcome aboard the %s captain!\n", shipName.c_str());
	//printHelp();

	WindowSetup("Shooting Game");


	initScreens();



	switchScreenToGame();


	while (!shouldExit)
	{
		checkInput();

		gameScreen.update(mouse.x, WIN_HEIGHT - mouse.y);



		renderWindow();


		Sleep(100);
	}

	delete screen;

	return 0;
}








std::string getWord(std::string s, int i)
{
	int lastPos = -1;
	int pos = 0;

	do
	{
		if (lastPos == -1)
		{
			pos = s.find(' ');
		}
		else
		{
			pos = s.find(' ', lastPos + 1);
		}

		if (pos == std::string::npos)
		{
			return s.substr(lastPos + 1, pos);
		}
		else if (i == 0)
		{
			return s.substr(lastPos + 1, pos - lastPos - 1);
		}
		--i;
		lastPos = pos;

	} while (i >= 0);
}



void renderWindow()
{

	//Renders from top-left to bottom-right
	//The y loop increments backwards here so tiles can be set intuitively elsewhere
	std::vector<CharData> image = screen->getImage();
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

#include <iostream>
#include <time.h>
#include <windows.h>

/*
CONTINENTAL TERRAIN
Map made of squares, rendered as text
Terrain attributes: elevation, water, temperature, rainfall, render color & text
Render each step of terrain gen separately to display the process

Try out storing terrain in flat array
Make array size adjustable to accomodate new terrain attributes later on
Need to store map width and height and number of attribs per tile
*/

//Color codes: 1 dark blue, 2 green, 3 turquoise, 4 red, 5 pink-violet, 6 yellow, 7 white, 8 white, 9 bright blue
//Colors by rainbow: 5 pink-violet, 1 dark blue, 9 light blue, 3 torquoise, 2 green, 6 yellow, 4 red

//Text color code copied from:
//http://www.cplusplus.com/forum/beginner/5830/




HANDLE hstdin;
HANDLE hstdout;




int main()
{
	srand(time(nullptr));
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//Elevation, waterdrops
	const int attribs = 2;
	const int width = 20;
	const int height = 20;

	int terrain[attribs * width * height];

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			//terrain[y * width + x * attribs] = rand() % 7 + 1;
			terrain[y * width * attribs + x * attribs] = 9;
			terrain[y * width + x];
		}
	}


	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	std::cout << std::endl;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			switch (terrain[y * width + x * attribs])
			{
			case 1:
				SetConsoleTextAttribute(hstdout, 5);
				break;
			case 2:
				SetConsoleTextAttribute(hstdout, 1);
				break;
			case 3:
				SetConsoleTextAttribute(hstdout, 9);
				break;
			case 4:
				SetConsoleTextAttribute(hstdout, 3);
				break;
			case 5:
				SetConsoleTextAttribute(hstdout, 2);
				break;
			case 6:
				SetConsoleTextAttribute(hstdout, 6);
				break;
			case 7:
				SetConsoleTextAttribute(hstdout, 4);
				break;
			}
			std::cout << terrain[y * width + x];
		}
		std::cout << std::endl;
	}

	// Return to original state
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);

	std::cin.get();


	FlushConsoleInputBuffer(hstdin);

	return 0;
}

#include <windows.h>
#include <iostream>
#include <time.h>

#include "Vecs.h"
#include "Perlin.h"
#include "TerrainGenerator.h"




DWORD getInput(INPUT_RECORD **eventBuffer);
//Returns the distance between two points
float dist(int x1, int y1, int x2, int y2);

void simulate();
void renderWindow();
void genTerrain();
void copyTileToNew();
void copyNewToTile();

// ---------- FANCY CONSOLE STUFF ---------- //
vec2 lastpos{ 0, 0 };

const int WIN_WIDTH = 100;
const int WIN_HEIGHT = 50;
const int MAP_HEIGHT = WIN_HEIGHT - 1;

//Each CHAR_INFO contains data for a single character: its ASCII char and color
CHAR_INFO consoleBuffer[WIN_WIDTH * WIN_HEIGHT];
COORD charBufferSize = { WIN_WIDTH, WIN_HEIGHT };
COORD charPosition = { 0, 0 };
SMALL_RECT consoleWriteArea{ 0, 0, WIN_WIDTH - 1, WIN_HEIGHT - 1 };

HANDLE hstdin;
HANDLE hstdout;

INPUT_RECORD* eventBuffer;
DWORD numEventsRead;
// ----------------------------------------- //

//Framerate is 1000/framepause
int framepause = 10;

int lastFrame = GetTickCount();

int tiles[WIN_WIDTH * WIN_HEIGHT];
int tilesNew[WIN_WIDTH * WIN_HEIGHT];
std::string winmsg;

vec2 mouse{ 0, 0 };
bool left = false;
bool right = false;
bool up = false;
bool down = false;
bool lclick = false;
bool rclick = false;



//Fancy console stuff learned/copied from:
//http://cecilsunkure.blogspot.com/2011/11/windows-console-game-setting-up-window.html




int main()
{
	srand(time(NULL));


	//Window size coordinates, must start at 0
	SMALL_RECT winSize = { 0, 0, WIN_WIDTH - 1, WIN_HEIGHT - 1 };

	//COORD struct for specifying screen buffer simensions
	COORD bufferSize = { WIN_WIDTH, WIN_HEIGHT };

	//Get window handles
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTitle("Mouse Painter");

	//Set screen buffer size
	SetConsoleScreenBufferSize(hstdout, bufferSize);

	//Set window size
	SetConsoleWindowInfo(hstdout, TRUE, &winSize);



	genTerrain();


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

		

		simulate();

		renderWindow();

		Sleep(framepause);
	}




	return 0;
}


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



void simulate()
{
	int deltaT = GetTickCount() - lastFrame;
	lastFrame = GetTickCount();

	if ((lclick || rclick) && tiles[mouse.x + mouse.y * WIN_WIDTH] != 2)
	{
		if (lclick)
		{
			tiles[mouse.x + mouse.y * WIN_WIDTH] = 0;
		}
		if (rclick)
		{
			tiles[mouse.x + mouse.y * WIN_WIDTH] = 1;
		}
	}

	
	

	up = down = right = left = rclick = lclick = false;


	copyTileToNew();

	//Block simulation
	//for (int y = 0; y < MAP_HEIGHT; ++y)
	//{
	//	for (int x = 0; x < WIN_WIDTH; ++x)
	//	{
	//		//Water flow
	//		if (tiles[x + y * WIN_WIDTH] == 3)
	//		{
	//			int leftRight = rand() % 2;
	//			if (leftRight == 0) { leftRight = -1; }

	//			if (!tilesNew[x + (y - 1) * WIN_WIDTH])
	//			{
	//				tilesNew[x + y * WIN_WIDTH] = 0;
	//				tilesNew[x + (y - 1) * WIN_WIDTH] = 3;
	//			}
	//			else if ((x + leftRight >= 0 && x + leftRight < WIN_WIDTH)
	//				&& !tilesNew[x + leftRight + (y - 1) * WIN_WIDTH])
	//			{
	//				tilesNew[x + y * WIN_WIDTH] = 0;
	//				tilesNew[x + leftRight + (y - 1) * WIN_WIDTH] = 3;
	//			}
	//			else if ((x - leftRight >= 0 && x - leftRight < WIN_WIDTH)
	//				&& !tilesNew[x - leftRight + (y - 1) * WIN_WIDTH])
	//			{
	//				tilesNew[x + y * WIN_WIDTH] = 0;
	//				tilesNew[x - leftRight + (y - 1) * WIN_WIDTH] = 3;
	//			}
	//			else if ((x + leftRight >= 0 && x + leftRight < WIN_WIDTH)
	//				&& !tilesNew[x + leftRight + y * WIN_WIDTH])
	//			{
	//				tilesNew[x + y * WIN_WIDTH] = 0;
	//				tilesNew[x + leftRight + y * WIN_WIDTH] = 3;
	//			}
	//			else if ((x - leftRight >= 0 && x - leftRight < WIN_WIDTH)
	//				&& !tilesNew[x - leftRight + y * WIN_WIDTH])
	//			{
	//				tilesNew[x + y * WIN_WIDTH] = 0;
	//				tilesNew[x - leftRight + y * WIN_WIDTH] = 3;
	//			}
	//		}
	//	}

	//}

	copyNewToTile();
}

void renderWindow()
{

	//Renders from top-left to bottom-right
	//The y loop increments backwards here so tiles can be set intuitively elsewhere
	int bufferCoord = 0;
	for (int y = WIN_HEIGHT - 1; y >= 0; --y)
		//for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			char chr = 0;
			int frontColor = 0;
			int backColor = 0;

			
			if (mouse.x == x && mouse.y == y)
			{
				backColor = 0x00F0;
			}

			

			switch (tiles[x + y * WIN_WIDTH])
			{
			case 0:
				//Water
				frontColor = 0x0003;
				//chr = (chr == 0) ? 0xB2 : chr;
				chr = '0';
				break;
			case 1:
				//Plains
				frontColor = 0x0006;
				//chr = (chr == 0) ? 0xB2 : chr;
				chr = '1';
				break;
			case 2:
				//Forest
				//backColor = 0x0060;
				frontColor = 0x000A;
				//chr = (chr == 0) ? 'T' : chr;
				chr = '2';
				break;
			case 3:
				//Mountains
				frontColor = 0x0007;
				//chr = (chr == 0) ? '^' : chr;
				chr = '3';
				break;
			default:
				//E is for Error 'E'
				chr = (chr == 0) ? 'E' : chr;
				break;
			}

			/*consoleBuffer[x + WIN_WIDTH * y].Char.AsciiChar = chr;
			consoleBuffer[x + WIN_WIDTH * y].Attributes = frontColor + backColor;*/
			consoleBuffer[bufferCoord].Char.AsciiChar = chr;
			consoleBuffer[bufferCoord].Attributes = frontColor + backColor;
			++bufferCoord;
		}
	}

	////If the msg is longer, it might create a new line, which would hide some of the world render.
	//winmsg.resize(WIN_WIDTH, ' ');
	////std::cout << msg.c_str();

	//for (int y = MAP_HEIGHT; y < WIN_HEIGHT - 1; ++y)
	//{
	//	for (int x = 0; x < WIN_WIDTH; ++x)
	//	{
	//		consoleBuffer[x + WIN_WIDTH * y].Char.AsciiChar = winmsg.at(x);
	//		consoleBuffer[x + WIN_WIDTH * y].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN |
	//			FOREGROUND_RED | FOREGROUND_INTENSITY;
	//	}
	//}


	

	WriteConsoleOutputA(hstdout, consoleBuffer, charBufferSize, charPosition, &consoleWriteArea);
}

void genTerrain()
{

	//Generate base terrain
	/*
	//Height limit MAP_HEIGHT - 2. 1 for bedrock, 1 for open space on top.
	int height = rand() % (MAP_HEIGHT - 2) + 1;

	for (int x = 0; x < WIN_WIDTH; ++x)
	{

		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			if (y == 0)
			{
				tiles[x + y * WIN_WIDTH] = 2;
			}
			else if (y <= height)
			{
				tiles[x + y * WIN_WIDTH] = 1;
			}
			else
			{
				tiles[x + y * WIN_WIDTH] = 0;
			}
		}

		if (height < MAP_HEIGHT - 2)
		{
			height += rand() % 3 - 1; // collatz series (sort-of not really)
		}
		else
		{
			height -= rand() % 2;
		}

	}



	//Clean little bumps and divets in terrain
	int right = 1;
	for (int x = 0; x < WIN_WIDTH; ++x)
	{
		if (x == WIN_WIDTH - 1)
		{
			right = 0;
		}
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			bool res = true;

			if (y < MAP_HEIGHT)    res = res && !tiles[x + (y + 1) * WIN_WIDTH];
			if (x < WIN_WIDTH - 1) res = res && !tiles[x + 1 + y * WIN_WIDTH];
			if (x != 0)		       res = res && !tiles[x - 1 + y * WIN_WIDTH];

			// non-branching single statement solution
			res = ((y < MAP_HEIGHT) && !tiles[x + (y + 1) * WIN_WIDTH]) &&
				((x == WIN_WIDTH - 1) || !tiles[x + 1 + y * WIN_WIDTH]) &&
				((x == 0) || !tiles[x - 1 + y * WIN_WIDTH]);

			// in C++, non-zero values are true.
			if (res) tiles[x + y * WIN_WIDTH] = 0;


			res = ((y > 0) && tiles[x + (y - 1) * WIN_WIDTH]) &&
				((x == WIN_WIDTH - 1) || tiles[x + 1 + y * WIN_WIDTH]) &&
				((x == 0) || tiles[x - 1 + y * WIN_WIDTH]);

			if (res) tiles[x + y * WIN_WIDTH] = 1;
		}

	}
	*/

	//float grid[WIN_WIDTH * WIN_HEIGHT];
	//Perlin::makeGrid(grid, WIN_WIDTH, WIN_HEIGHT, 1, 10, 5);
	TerrainGenerator::genBiomes(tiles, WIN_WIDTH, WIN_HEIGHT, 2);

	/*for (int x = 0; x < WIN_WIDTH; ++x)
	{
		for (int y = 0; y < WIN_HEIGHT; ++y)
		{
			if (grid[x + y * WIN_WIDTH] > 2)
			{
				tiles[x + y * WIN_WIDTH] = 2;
			}
			else
			{
				tiles[x + y * WIN_WIDTH] = 0;
			}
		}
	}*/
}

void copyNewToTile()
{
	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			tiles[x + y * WIN_WIDTH] = tilesNew[x + y * WIN_WIDTH];
		}
	}
}

void copyTileToNew()
{
	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			tilesNew[x + y * WIN_WIDTH] = tiles[x + y * WIN_WIDTH];
		}
	}
}

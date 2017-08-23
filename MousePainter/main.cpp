

#include <windows.h>
#include <iostream>
#include <time.h>



struct vec2
{
	int x;
	int y;
};





DWORD getInput(INPUT_RECORD **eventBuffer);
//Returns the distance between two points
float dist(int x1, int y1, int x2, int y2);

void simulate();
void renderWindow();
void genTerrain();


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

int tiles[WIN_WIDTH * MAP_HEIGHT];
std::string winmsg;

vec2 player{ 50, 48 };
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
							//++player.y;
							up = true;
							break;
						case 0x41: //A
							//--player.x;
							left = true;
							break;
						case 0x53: //S
							//--player.y;
							down = true;
							break;
						case 0x44: //D
							//++player.x;
							right = true;
							break;
						}
					}
					break;
				case MOUSE_EVENT:
					//int offsetx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					//int offsety = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					/*consoleBuffer[lastpos.x + lastpos.y * WIN_WIDTH].Char.AsciiChar = ' ';
					consoleBuffer[lastpos.x + lastpos.y * WIN_WIDTH].Attributes = 0x0000;
					consoleBuffer[offsetx + offsety * WIN_WIDTH].Char.AsciiChar = 0xB2;
					consoleBuffer[offsetx + offsety * WIN_WIDTH].Attributes = 0x00FF;*/
					//lastpos = { offsetx, offsety };
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
						mouse.y = MAP_HEIGHT - 1 - eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
						
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags == 0x0000)
					{
						
					}
					break;
				}
			}
			//WriteConsoleOutputA(hstdout, consoleBuffer, charBufferSize, charPosition, &consoleWriteArea);
		}

		simulate();

		renderWindow();

		Sleep(framepause);
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



void simulate()
{
	if ((lclick || rclick) && (player.x != mouse.x || player.y != mouse.y))
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

	if (!tiles[player.x + (player.y - 1) * WIN_WIDTH])
	{
		--player.y;
	}

	if (right && player.y < WIN_WIDTH - 1)
	{
		//Check for straight right movement
		if (!tiles[player.x + 1 + player.y * WIN_WIDTH])
		{
			++player.x;
		}
		//Check for up-right movement
		else if (player.y < MAP_HEIGHT - 1
			&&	tiles[player.x + 1 + player.y * WIN_WIDTH]
			&& !tiles[player.x + 1 + (player.y + 1) * WIN_WIDTH])
		{
			++player.x;
			++player.y;
		}
		//Check for down-right movement
		else if (player.y > 1
			 &&  tiles[player.x + 1 + (player.y - 2) * WIN_WIDTH]
			 && !tiles[player.x + 1 + (player.y - 1) * WIN_WIDTH])
		{
			++player.x;
			--player.y;
		}
	}

	if (left && player.y > 0)
	{
		//Check for straight right movement
		if (!tiles[player.x - 1 + player.y * WIN_WIDTH])
		{
			--player.x;
		}
		//Check for up-right movement
		else if (player.y < MAP_HEIGHT - 1
			&&  tiles[player.x - 1 + player.y * WIN_WIDTH]
			&& !tiles[player.x - 1 + (player.y + 1) * WIN_WIDTH])
		{
			--player.x;
			++player.y;
		}
		//Check for down-right movement
		else if (player.y > 1
			&&  tiles[player.x - 1 + (player.y - 2) * WIN_WIDTH]
			&& !tiles[player.x - 1 + (player.y - 1) * WIN_WIDTH])
		{
			--player.x;
			--player.y;
		}
	}

	up = down = right = left = rclick = lclick = false;
}

void renderWindow()
{
	
	//Renders from top-left to bottom-right
	//The y loop increments backwards here so blocks can be set intuitively elsewhere
	int bufferCoord = 0;
	for (int y = MAP_HEIGHT - 1; y >= 0; --y)
		//for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			char chr = 0;
			int frontColor = 0;
			int backColor = 0;

			if (player.x == x && player.y == y)
			{
				chr = '@';
				frontColor = 0x000F;
			}
			if (mouse.x == x && mouse.y == y)
			{
				backColor = 0x00F0;
			}

			switch (tiles[x + y * WIN_WIDTH])
			{
			case 0:
				//Empty space ' '
				chr = (chr == 0) ? 0x00 : chr;
				break;
			case 1:
				//Normal block 'X'
				//backColor = 0x0020;
				frontColor = 0x0006;
				chr = (chr == 0) ? 'X' : chr;
				//chr = 'X';
				break;
			case 2:
				//Bedrock, holding up the world 'W'
				backColor = 0x0060;
				frontColor = 0x0006;
				chr = (chr == 0) ? 0x57 : chr;
				break;
			case 3:
				//Water '-'
				frontColor = 0x0003;
				//chr = (chr == 0) ? 0xC4 : chr;
				chr = (chr == 0) ? 176 : chr;
				break;
			default:
				//E is for Error 'E'
				std::cout << "E";
				break;
			}

			/*consoleBuffer[x + WIN_WIDTH * y].Char.AsciiChar = chr;
			consoleBuffer[x + WIN_WIDTH * y].Attributes = frontColor + backColor;*/
			consoleBuffer[bufferCoord].Char.AsciiChar = chr;
			consoleBuffer[bufferCoord].Attributes = frontColor + backColor;
			++bufferCoord;
		}
	}

	//If the msg is longer, it might create a new line, which would hide some of the world render.
	winmsg.resize(WIN_WIDTH, ' ');
	//std::cout << msg.c_str();

	for (int y = MAP_HEIGHT; y < WIN_HEIGHT - 1; ++y)
	{
		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			consoleBuffer[x + WIN_WIDTH * y].Char.AsciiChar = winmsg.at(x);
			consoleBuffer[x + WIN_WIDTH * y].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN |
				FOREGROUND_RED | FOREGROUND_INTENSITY;
		}
	}

	WriteConsoleOutputA(hstdout, consoleBuffer, charBufferSize, charPosition, &consoleWriteArea);
}

void genTerrain()
{

	//Generate base terrain

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

			if (y < MAP_HEIGHT)    res = res && !tiles[x + (y+1) * WIN_WIDTH];
			if (x < WIN_WIDTH - 1) res = res && !tiles[x + 1 + y * WIN_WIDTH];
			if (x != 0)		       res = res && !tiles[x - 1 + y * WIN_WIDTH];

			// non-branching single statement solution
			res = ((y < MAP_HEIGHT) && !tiles[x + (y+1) * WIN_WIDTH]) &&
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
}

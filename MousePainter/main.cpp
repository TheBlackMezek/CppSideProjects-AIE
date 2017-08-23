

#include <windows.h>
#include <iostream>
#include <time.h>



struct vec2
{
	int x;
	int y;
};



DWORD getInput(INPUT_RECORD **eventBuffer);

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

int tiles[WIN_WIDTH * MAP_HEIGHT];
std::string winmsg;






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


	//for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; ++i)
	//{
	//	//consoleBuffer[i].Char.AsciiChar = 0xB2; //That solid-grate char
	//	/*consoleBuffer[i].Char.AsciiChar = 't';
	//	consoleBuffer[i].Attributes = 0x00FF;*/
	//	consoleBuffer[i].Char.AsciiChar = ' ';
	//	consoleBuffer[i].Attributes = 0x0000; 
	//}




	//WriteConsoleOutputA(hstdout, consoleBuffer, charBufferSize, charPosition, &consoleWriteArea);

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
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
					{
					case VK_ESCAPE:
						return 0;
					}
				case MOUSE_EVENT:
					int offsetx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					int offsety = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					/*consoleBuffer[lastpos.x + lastpos.y * WIN_WIDTH].Char.AsciiChar = ' ';
					consoleBuffer[lastpos.x + lastpos.y * WIN_WIDTH].Attributes = 0x0000;
					consoleBuffer[offsetx + offsety * WIN_WIDTH].Char.AsciiChar = 0xB2;
					consoleBuffer[offsetx + offsety * WIN_WIDTH].Attributes = 0x00FF;*/
					lastpos = { offsetx, offsety };
				}
			}
			//WriteConsoleOutputA(hstdout, consoleBuffer, charBufferSize, charPosition, &consoleWriteArea);
		}

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


#include <iostream>
#include <time.h>
#include <windows.h>
#include <string>



//Is passing arrays bad?
void renderWindow(int** blocks, std::string msg);
//I read that this will return a pointer to a 2D array
int** genBlockArray();
int** genBlockNewArray();
int** genTerrain(int** blocks);
//a2 = a1
void copyBlockArray(int** a1, int** a2);
void simulate();
void game();


const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 23;

bool endGame = false;
//When simulating, blocks is copied to blocksNew
//blocks is used to determine what needs to be simulated
//blocksNew is used for collisions, etc.
int** blocks;
int** blocksNew;
std::string winmsg = "";

HANDLE hstdin;
HANDLE hstdout;



//Default console size at home is 80x24 characters. Check at AIE.

//Text color code copied from:
//http://www.cplusplus.com/forum/beginner/5830/


int main()
{

	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);



	srand(time(nullptr));


	blocks = genTerrain(genBlockArray());
	blocksNew = genBlockNewArray();
	copyBlockArray(blocks, blocksNew);

	//renderWindow(blocks, "Test message. This has to be very long so that I can test the string resize function. I don't have a clue how many characters I've written in it so far.");

	game();

	for (int w = 0; w < MAP_WIDTH; ++w)
	{
		delete[] blocks[w];
	}
	delete[] blocks;

	for (int w = 0; w < MAP_WIDTH; ++w)
	{
		delete[] blocksNew[w];
	}
	delete[] blocksNew;




	FlushConsoleInputBuffer(hstdin);



	//system("pause");

	return 0;
}

//The game loop
void game()
{
	std::string input;

	renderWindow(blocks, winmsg);

	while (!endGame)
	{
		winmsg = "";

		std::getline(std::cin, input);
		system("cls");

		if (input == "exit")
		{
			endGame = true;
		}
		else if (input == "regen")
		{
			genTerrain(blocks);
			winmsg = "Terrain regenerated";
		}
		else if (input.substr(0, 4) == "seed")
		{
			if (input.substr(5, input.npos) == "time")
			{
				srand(time(NULL));
			}
			else
			{
				srand(std::stoi(input.substr(5, input.npos)));
			}
			winmsg = "Seed set to " + input.substr(5, input.npos);
		}
		else if (input == "rain")
		{
			for (int x = 0; x < MAP_WIDTH; ++x)
			{
				blocks[x][MAP_HEIGHT - 1] = 3;
			}
			winmsg = "Rain added";
		}
		else if (input.substr(0, 3) == "sim")
		{
			if (input.size() != 3)
			{
				int runs = std::stoi(input.substr(4, input.npos));
				for (int i = 0; i < runs - 1; ++i)
				{
					simulate();
					renderWindow(blocks, winmsg);
					Sleep(250);
				}
			}
			simulate();
		}

		renderWindow(blocks, winmsg);
	}
}



void simulate()
{
	copyBlockArray(blocks, blocksNew);

	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		int leftRight = rand() % 2;
		if (leftRight == 0) { leftRight = -1; }
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			//Water flow
			if (blocks[x][y] == 3)
			{
				
				if (!blocksNew[x][y - 1])
				{
					blocksNew[x][y] = 0;
					blocksNew[x][y - 1] = 3;
				}
				else if ((x + leftRight >= 0 && x + leftRight < MAP_WIDTH)
					&& !blocksNew[x + leftRight][y - 1])
				{
					blocksNew[x][y] = 0;
					blocksNew[x + leftRight][y - 1] = 3;
				}
				else if ((x - leftRight >= 0 && x - leftRight < MAP_WIDTH)
					&& !blocksNew[x - leftRight][y - 1])
				{
					blocksNew[x][y] = 0;
					blocksNew[x - leftRight][y - 1] = 3;
				}
				else if ((x + leftRight >= 0 && x + leftRight < MAP_WIDTH)
					&& !blocksNew[x + leftRight][y])
				{
					blocksNew[x][y] = 0;
					blocksNew[x + leftRight][y] = 3;
				}
				else if ((x - leftRight >= 0 && x - leftRight < MAP_WIDTH)
					&& !blocksNew[x - leftRight][y])
				{
					blocksNew[x][y] = 0;
					blocksNew[x - leftRight][y] = 3;
				}
			}
		}

	}

	copyBlockArray(blocksNew, blocks);
}

void renderWindow(int** blocks, std::string msg)
{
	//Makeshift "clear window"
	//std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	//Renders from top-left to bottom-right
	//The y loop increments backwards here so blocks can be set intuitively elsewhere
	for (int y = 22; y >= 0; --y)
	{
		for (int x = 0; x < 80; ++x)
		{
			switch (blocks[x][y])
			{
			case 0:
				//Empty space
				std::cout << " ";
				break;
			case 1:
				//Normal block
				SetConsoleTextAttribute(hstdout, 0x06);
				std::cout << "X";
				break;
			case 2:
				//Bedrock, holding up the world
				SetConsoleTextAttribute(hstdout, 0x66);
				std::cout << "W";
				break;
			case 3:
				//Water
				SetConsoleTextAttribute(hstdout, 0x03);
				std::cout << "-";
				break;
			default:
				//E is for Error
				std::cout << "E";
				break;
			}
		}
	}

	// Return to original state
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);

	//If the msg is longer, it might create a new line, which would hide some of the world render.
	msg.resize(80, ' ');
	std::cout << msg.c_str();
}

int** genBlockArray()
{
	//Create array

	//REMEMBER TO DELETE THIS ARRAY WHEN DONE WITH IT
	int** blocks = 0;
	blocks = new int*[MAP_WIDTH];

	for (int w = 0; w < MAP_WIDTH; ++w)
	{
		blocks[w] = new int[MAP_HEIGHT];

		for (int h = 0; h < MAP_HEIGHT; ++h)
		{
			blocks[w][h] = 0;
		}
	}

	return blocks;
}

int** genBlockNewArray()
{
	//Create array

	//REMEMBER TO DELETE THIS ARRAY WHEN DONE WITH IT
	int** blocksNew = 0;
	blocksNew = new int*[MAP_WIDTH];

	for (int w = 0; w < MAP_WIDTH; ++w)
	{
		blocksNew[w] = new int[MAP_HEIGHT];

		for (int h = 0; h < MAP_HEIGHT; ++h)
		{
			blocksNew[w][h] = 0;
		}
	}

	return blocksNew;
}

int** genTerrain(int** blocks)
{

	//Generate base terrain

	//Height limit 21 of 23. 1 for bedrock (later), 1 for open space on top.
	int height = rand() % 21 + 1;

	for (int x = 0; x < MAP_WIDTH; ++x)
	{

		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			if (y == 0)
			{
				blocks[x][y] = 2;
			}
			else if (y <= height)
			{
				blocks[x][y] = 1;
			}
			else
			{
				blocks[x][y] = 0;
			}
		}

		if (height < 21)
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
	for (int x = 0; x < MAP_WIDTH; ++x)
	{
		if (x == MAP_WIDTH -1)
		{
			right = 0;
		}
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			bool res = true;

			if(y < MAP_HEIGHT)  res = res && !blocks[x][y + 1];
			if(x < MAP_WIDTH-1) res = res && !blocks[x + 1][y];
			if(x != 0)		    res = res && !blocks[x - 1][y];

			// non-branching single statement solution
			res = ((y < MAP_HEIGHT)     && !blocks[x][y + 1]) &&
				  ((x == MAP_WIDTH - 1) || !blocks[x + 1][y]) &&
				  ((x == 0)             || !blocks[x - 1][y]);
			 
			// in C++, non-zero values are true.
			if (res) blocks[x][y] = 0;

			
			res = ((y > 0)				&& blocks[x][y - 1]) &&
				  ((x == MAP_WIDTH - 1) || blocks[x + 1][y]) &&
				  ((x == 0)				|| blocks[x - 1][y]);

			if (res) blocks[x][y] = 1;
			/*
			if ((blocks[x][y] != 0 
				&& (y == MAP_HEIGHT-1 || blocks[x][y + 1] == 0))
				&& 
					((x == 0 && blocks[x+right][y] == 0)
					|| (x == MAP_WIDTH-1 && blocks[x-1][y] == 0)
					|| (blocks[x + 1][y] == 0 && blocks[x - 1][y] == 0))
				)
			{
				blocks[x][y] = 0;
			}*/
		}

	}
	


	return blocks;
}

void copyBlockArray(int** a1, int** a2)
{
	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			a2[x][y] = a1[x][y];
		}
	}
}

// short-circuiting 

//	A && B : if A is false, then there is no need to bother evaluating B
//  A || B : if A is true, then there is no need to bother evaluating B

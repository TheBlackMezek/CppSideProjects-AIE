
#include <iostream>
#include <time.h>
#include <windows.h>
#include <string>

#include "PlantStruct.h"




const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 23;

void game();
void simulate();
//Is passing arrays bad?
void renderWindow(int** blocks, std::string msg);
//I read that this will return a pointer to a 2D array
int** genBlockArray();
int** genBlockNewArray();
void genPlantArray();
int** genTerrain(int** blocks);
//a2 = a1
void copyBlockArray(int** a1, int** a2);
void killPlants();
void rain();


bool endGame = false;
std::string winmsg = "";
//When simulating, blocks is copied to blocksNew
//blocks is used to determine what needs to be simulated
//blocksNew is used for collisions, etc.
int** blocks;
int** blocksNew;
Plant** plants;
Plant plantTypes[]
{
	{ 0, 0, 0, 0, 0, 0}, //No plant
	{ 1, '%', 6, 6, 10, 10 }, //Simple spreader
	{ 2, '|', 10, 10, 8, 8 } //Reed
};

int sleepTime = 250;
int rainInterval = -1;
int rainTimer = 0;

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

	genPlantArray();

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

	for (int w = 0; w < MAP_WIDTH; ++w)
	{
		delete[] plants[w];
	}
	delete[] plants;




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
			killPlants();
			winmsg = "Terrain regenerated";
		}
		else if (input.substr(0, 5) == "seed ")
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
		else if (input.substr(0, 4) == "rain")
		{
			if (input.size() == 4)
			{
				rain();
				winmsg = "Rain added";
			}
			else
			{
				rainInterval = std::stoi(input.substr(5, input.npos));
				rainTimer = 0;
				winmsg = "Rain interval set to " + std::to_string(rainInterval);
			}
		}
		else if (input.substr(0, 4) == "sim ")
		{
			if (input.size() != 3)
			{
				int runs = std::stoi(input.substr(4, input.npos));
				for (int i = 0; i < runs - 1; ++i)
				{
					simulate();
					renderWindow(blocks, winmsg);
					Sleep(sleepTime);
				}
			}
			simulate();
		}
		else if (input.substr(0, 5) == "life ")
		{
			int type = stoi(input.substr(5, input.npos));
			for (int y = 0; y < MAP_HEIGHT; ++y)
			{
				for (int x = 0; x < MAP_WIDTH; ++x)
				{
					if (type == 1 || type == 2) {
						if (!blocks[x][y] && blocks[x][y - 1] == 1
							&& rand() % 10 == 0
							&& plants[x][y].type == 0)
						{
							plants[x][y] = plantTypes[type];
						}
					}
				}
			}
		}
		else if (input == "kill")
		{
			killPlants();
		}
		else if (input == "dry")
		{
			for (int y = 0; y < MAP_HEIGHT; ++y)
			{
				for (int x = 0; x < MAP_WIDTH; ++x)
				{
					if (blocks[x][y] == 3)
					{
						blocks[x][y] = 0;
					}
				}
			}
		}
		else if (input.substr(0, 7) == "simwait")
		{
			sleepTime = stoi(input.substr(8, input.npos));
			winmsg = "Sim wait time set to " + std::to_string(sleepTime) + " milliseconds";
		}

		renderWindow(blocks, winmsg);
	}
}



void simulate()
{
	copyBlockArray(blocks, blocksNew);

	//Block simulation
	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			//Water flow
			if (blocks[x][y] == 3)
			{
				int leftRight = rand() % 2;
				if (leftRight == 0) { leftRight = -1; }
				
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

	//Rainfall
	if (rainInterval >= 0)
	{
		if (rainTimer == 0)
		{
			winmsg = "Raining";
			rainTimer = rainInterval;
			rain();
		}
		else
		{
			--rainTimer;
		}
	}

	//Plant simulation
	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < MAP_WIDTH; ++x)
		{

			//Basic spreader
			if (plants[x][y].type == 1)
			{
				//Heal if full on food
				if (plants[x][y].food == plants[x][y].maxFood &&
					plants[x][y].health < plants[x][y].maxHealth)
				{
					++plants[x][y].health;
				}

				//Seed if full enough and healthy
				if (plants[x][y].food   >  plants[x][y].maxFood / 2
				 && plants[x][y].health == plants[x][y].maxHealth)
				{
					bool seeded = false;
					for (int xx = x - 2; xx <= x + 2; ++xx)
					{
						if (xx >= 0 && xx < MAP_WIDTH)
						{
							for (int yy = y - 2; yy <= y + 2; ++yy)
							{
								if (yy > 0 && yy < MAP_HEIGHT
									&& plants[xx][yy].type == 0
									&& !blocks[xx][yy] && blocks[xx][yy-1] == 1)
								{
									seeded = true;
									plants[xx][yy] = plantTypes[1];
									plants[xx][yy].food = plants[x][y].food / 2;
									plants[x][y].food /= 2;
									break;
								}
							}
						}
						if (seeded) { break; }
					}
				}

				//Use up food
				--plants[x][y].food;
				//No negative food
				if (plants[x][y].food < 0)
				{
					plants[x][y].food = 0;
				}

				//Water-in-tile logic
				if (blocks[x][y] == 3)
				{
					//Consume water if hungry
					if (plants[x][y].food < plants[x][y].maxFood - 1)
					{
						blocks[x][y] = 0;
						plants[x][y].food += 5;
					}
					//If not hungry and submerged, drown
					else if(y != MAP_HEIGHT-1 && blocks[x][y+1] == 3)
					{
						plants[x][y].health -= 2;
					}

					//No food overflow
					if (plants[x][y].food > plants[x][y].maxFood)
					{
						plants[x][y].food = plants[x][y].maxFood;
					}
				}

				//Starvation
				if (plants[x][y].food < 1)
				{
					plants[x][y].health -= 2;
				}

				//Death
				if (plants[x][y].health < 1)
				{
					plants[x][y] = plantTypes[0];
				}
			}


		}
	}
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
			char chr = plants[x][y].chr;
			int frontColor = 0;
			int backColor = 0;
			if (chr != 0)
			{
				frontColor = 0x02;
			}

			switch (blocks[x][y])
			{
			case 0:
				//Empty space
				chr = (chr == 0) ? ' ' : chr;
				break;
			case 1:
				//Normal block
				frontColor = 0x06;
				chr = (chr == 0) ? 'X' : chr;
				break;
			case 2:
				//Bedrock, holding up the world
				//SetConsoleTextAttribute(hstdout, 0x66);
				//std::cout << "W";
				backColor = 0x60;
				frontColor = 0x06;
				chr = (chr == 0) ? 'W' : chr;
				break;
			case 3:
				//Water
				frontColor = 0x03;
				chr = (chr == 0) ? '-' : chr;
				break;
			default:
				//E is for Error
				std::cout << "E";
				break;
			}

			SetConsoleTextAttribute(hstdout, frontColor + backColor);
			std::cout << chr;
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

void genPlantArray()
{
	//Create array

	//REMEMBER TO DELETE THIS ARRAY WHEN DONE WITH IT
	Plant** ar = 0;
	ar = new Plant*[MAP_WIDTH];

	for (int w = 0; w < MAP_WIDTH; ++w)
	{
		ar[w] = new Plant[MAP_HEIGHT];

		for (int h = 0; h < MAP_HEIGHT; ++h)
		{
			ar[w][h] = { 0, 0, 0, 0, 0, 0 };
		}
	}

	plants = ar;
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

void killPlants()
{
	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			plants[x][y] = plantTypes[0];
		}
	}
}

void rain()
{
	for (int x = 0; x < MAP_WIDTH; ++x)
	{
		if (blocks[x][MAP_HEIGHT - 1] == 0)
		{
			blocks[x][MAP_HEIGHT - 1] = 3;
		}
	}
}

// short-circuiting 

//	A && B : if A is false, then there is no need to bother evaluating B
//  A || B : if A is true, then there is no need to bother evaluating B


//IDEAS FOR LIFE FORMS
//
//Blocktype life: just a block type with special rules
//No additional data possible
//
//Superblock life: exists in a block array of one type of struct/class
//Data storage ability has same limit for all life forms
//No overlapping possible, but very easy to find what you want
//
//Entity life: exists in a 1d array of one type of struct/class
//Data storage ability has same limit for all life forms
//Overlapping possible, but must loop through whole list to find one organism
//
//
//SUPERBLOCK IDEAS
//
//Simple spreader: replicates on nearby terrain
//
//Reed: replicates upward and shares food
//
//Kelp: like reed but underwater
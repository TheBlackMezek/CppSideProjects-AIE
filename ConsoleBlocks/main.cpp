
#include <iostream>
#include <time.h>



//Is passing arrays bad?
void renderWindow(int** blocks, std::string msg);
//I read that this will return a pointer to a 2D array
int** genTerrain();


const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 23;



//Default console size at home is 80x24 characters. Check at AIE.

int main()
{
	std::cout << "Hello world!" << std::endl;

	srand(time(nullptr));


	int** blockTest = genTerrain();

	renderWindow(blockTest, "Test message. This has to be very long so that I can test the string resize function. I don't have a clue how many characters I've written in it so far.");

	for (int w = 0; w < MAP_WIDTH; ++w)
	{
		delete[] blockTest[w];
	}
	delete[] blockTest;


	system("pause");

	return 0;
}


void renderWindow(int** blocks, std::string msg)
{
	//Makeshift "clear window"
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

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
				std::cout << "X";
				break;
			case 2:
				//Bedrock, holding up the world
				std::cout << "W";
				break;
			default:
				//E is for Error
				std::cout << "E";
				break;
			}
		}
	}

	//If the msg is longer, it might create a new line, which would hide some of the world render.
	msg.resize(80, ' ');
	std::cout << msg.c_str();
}

int** genTerrain()
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



	//Clean little bumps on terrain
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
			res = ((y < MAP_HEIGHT)    && !blocks[x][y + 1]) &&
				  ((x < MAP_WIDTH - 1) && !blocks[x + 1][y]) &&
				  ((x != 0)            && !blocks[x - 1][y]);
			 
			// in C++, non-zero values are true.
			if (res) blocks[x][y] = 0;
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

// short-circuiting 

//	A && B : if A is false, then there is no need to bother evaluating B
//  A || B : if A is true, then there is no need to bother evaluating B

#include "TerrainGenerator.h"


#include <vector>

#include "Perlin.h"


TerrainGenerator::TerrainGenerator()
{
}


TerrainGenerator::~TerrainGenerator()
{
}


void TerrainGenerator::genBiomes(int grid[], int sizex, int sizey, int seed)
{
	std::vector<float> perlin(sizex * sizey);
	Perlin::makeGrid(&perlin, sizex, sizey, seed, 10, 1);

	//0 is water, 1 is plains, 2 is forest, 3 is mountain

	for (int y = 0; y < sizey; ++y)
	{
		for (int x = 0; x < sizex; ++x)
		{
			if (perlin[x + y * sizex] <= 1)
			{
				grid[x + y * sizex] = 0;
			}
			else if (perlin[x + y * sizex] <= 5)
			{
				grid[x + y * sizex] = 1;
			}
			else if (perlin[x + y * sizex] <= 9)
			{
				grid[x + y * sizex] = 2;
			}
			else //if (perlin[x + y * sizex] <= 4)
			{
				grid[x + y * sizex] = 3;
			}
		}
	}
}
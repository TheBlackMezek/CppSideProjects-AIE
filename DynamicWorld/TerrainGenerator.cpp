#include "TerrainGenerator.h"


#include <vector>

#include "Perlin.h"


TerrainGenerator::TerrainGenerator()
{
}


TerrainGenerator::~TerrainGenerator()
{
}


void TerrainGenerator::genBiomes(Tile grid[], int sizex, int sizey, int seed)
{
	std::vector<float> perlin(sizex * sizey);
	Perlin::makeGridOctaves(&perlin, sizex, sizey, seed, 25, 150, 4, 0.5f, 0.5f);

	//0 is water, 1 is plains, 2 is forest, 3 is mountain

	for (int y = 0; y < sizey; ++y)
	{
		for (int x = 0; x < sizex; ++x)
		{
			if (perlin[x + y * sizex] <= 0)
			{
				grid[x + y * sizex].type = 0;
				grid[x + y * sizex].foodMax = 10;
				grid[x + y * sizex].food = grid[x + y * sizex].foodMax;
				grid[x + y * sizex].foodInc = 1;
			}
			else if (perlin[x + y * sizex] <= 40)
			{
				grid[x + y * sizex].type = 1;
				grid[x + y * sizex].foodMax = 5;
				grid[x + y * sizex].food = grid[x + y * sizex].foodMax;
				grid[x + y * sizex].foodInc = 0.2f;
			}
			else if (perlin[x + y * sizex] <= 80)
			{
				grid[x + y * sizex].type = 2;
				grid[x + y * sizex].foodMax = 8;
				grid[x + y * sizex].food = grid[x + y * sizex].foodMax;
				grid[x + y * sizex].foodInc = 0.5f;
			}
			else //if (perlin[x + y * sizex] <= 4)
			{
				grid[x + y * sizex].type = 3;
				grid[x + y * sizex].foodMax = 1;
				grid[x + y * sizex].food = grid[x + y * sizex].foodMax;
				grid[x + y * sizex].foodInc = 0.1f;
			}
		}
	}
}
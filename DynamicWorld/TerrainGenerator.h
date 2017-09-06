#pragma once

#ifndef _TERRAINGENERATOR_H_
#define _TERRAINGENERATOR_H_

#include "MapTile.h"

class TerrainGenerator
{
public:
	TerrainGenerator();
	~TerrainGenerator();

	static void genBiomes(Tile grid[], int sizex, int sizey, int seed);
};


#endif
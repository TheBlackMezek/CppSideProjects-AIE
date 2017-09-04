#pragma once

#ifndef _TERRAINGENERATOR_H_
#define _TERRAINGENERATOR_H_



class TerrainGenerator
{
public:
	TerrainGenerator();
	~TerrainGenerator();

	static void genBiomes(int grid[], int sizex, int sizey, int seed);
};


#endif
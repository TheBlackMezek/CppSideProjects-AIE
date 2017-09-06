#pragma once


#include "MapTile.h"


class Tribe
{
public:
	Tribe();
	~Tribe();

	int x;
	int y;

	int pop;
	float food;
	float foodMax;

	void sim(Tile map[], int sizex, int sizey);
};


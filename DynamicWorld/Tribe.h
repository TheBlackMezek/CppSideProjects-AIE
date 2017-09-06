#pragma once


#include "MapTile.h"
#include "NeuralNet.h"


class Tribe
{
public:
	Tribe();
	~Tribe();

	int x;
	int y;

	int color;

	int pop;
	float food;
	float foodMax;

	NeuralNet brain;

	void sim(Tile map[], int sizex, int sizey);
};


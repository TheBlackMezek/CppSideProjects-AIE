#include "Tribe.h"


#include <random>


Tribe::Tribe()
{
}


Tribe::~Tribe()
{
}


void Tribe::sim(int map[], int sizex, int sizey)
{
	int prevx = x;
	int prevy = y;

	x += rand() % 3 - 1;
	y += rand() % 3 - 1;

	if (map[x + y * sizex] == 0)
	{
		x = prevx;
		y = prevy;
	}

	if (x >= sizex)
	{
		x = sizex - 1;
	}
	else if (x < 0)
	{
		x = 0;
	}

	if (y >= sizey)
	{
		y = sizey - 1;
	}
	else if (y < 0)
	{
		y = 0;
	}
}
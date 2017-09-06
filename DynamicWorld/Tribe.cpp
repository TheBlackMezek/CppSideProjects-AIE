#include "Tribe.h"


#include <random>


Tribe::Tribe()
{
	pop = 5;
	food = 0;
	foodMax = pop * 2;
}


Tribe::~Tribe()
{
}


void Tribe::sim(Tile map[], int sizex, int sizey)
{
	//Movement
	int prevx = x;
	int prevy = y;

	x += rand() % 3 - 1;
	y += rand() % 3 - 1;

	if (map[x + y * sizex].type == 0)
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


	//Food
	for (int xx = x - 1; xx <= x + 1; ++xx)
	{
		if (xx >= 0 && xx < sizex)
		{
			for (int yy = y - 1; yy <= y + 1; ++yy)
			{
				if (yy >= 0 && yy < sizey)
				{
					float prevFood = food;
					food += map[xx + yy * sizex].food;
					if (food > foodMax)
					{
						food = foodMax;
					}
					map[xx + yy * sizex].food -= food - prevFood;
				}
			}
		}
	}
	

	food -= pop;
	//Starvation
	if (food < 0)
	{
		pop += (int)food;
		foodMax = pop * 2;
		food = 0;
	}
	else if (food >= 1)
	{
		++pop;
		foodMax = pop * 2;
	}
}
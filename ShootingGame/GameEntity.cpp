#include "GameEntity.h"



GameEntity::GameEntity(char ic, int xx, int yy, Player* p, std::vector<bool>* m, int mx, int my)
{
	icon = ic;
	x = xx;
	y = xx;
	player = p;
	mapsizex = mx;
	mapsizey = my;
	physmap = m;
}


GameEntity::~GameEntity()
{
}


void GameEntity::update()
{
	//stay, up, down, right, left
	int dir = rand() % 5;

	if (dir == 1 && y < mapsizey - 1 && physmap->at(x + (y + 1) * mapsizex) == false)
	{
		++y;
	}
	else if (dir == 2 && y > 0 && physmap->at(x + (y - 1) * mapsizex) == false)
	{
		--y;
	}
	else if (dir == 3 && x < mapsizex - 1 && physmap->at(x + 1 + y * mapsizex) == false)
	{
		++x;
	}
	else if (dir == 4 && x > 0 && physmap->at(x - 1 + y * mapsizex) == false)
	{
		--x;
	}
}

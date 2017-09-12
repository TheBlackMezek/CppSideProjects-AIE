#include "GameEntity.h"



GameEntity::GameEntity(char ic, int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my)
{
	alive = true;

	icon = ic;
	visible = true;
	x = xx;
	y = yy;
	//vel = Vec2(0, 0);
	vel = Vec2(p->x - x, p->y - y);
	vel.unit();
	player = p;
	entities = e;
	mapsizex = mx;
	mapsizey = my;
	physmap = m;
}

GameEntity::GameEntity()
{
	vel = Vec2(0, 0);
}


GameEntity::~GameEntity()
{
}


void GameEntity::update()
{
	//stay, up, down, right, left
	/*int dir = rand() % 5;
	
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
	}*/
	vel.x = player->x - x;
	vel.y = player->y - y;
	vel.unit();

	vel.x /= 10;
	vel.y /= 10;

	x += vel.x;
	y += vel.y;

	if (physmap->at((int)x + (int)y * mapsizex) == true)
	{
		x -= vel.x;
		y -= vel.y;
	}

	if (x < 0)
	{
		x = 0;
	}
	if (x > mapsizex - 1)
	{
		x = mapsizex - 1;
	}
	if (y < 0)
	{
		y = 0;
	}
	if (y > mapsizey - 1)
	{
		y = mapsizey - 1;
	}

	
}

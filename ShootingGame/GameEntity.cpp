#include "GameEntity.h"



GameEntity::GameEntity(char ic, int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my)
{
	alive = true;

	icon = ic;
	visible = true;
	x = xx;
	y = yy;
	vel = Vec2(0, 0);
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
	
}

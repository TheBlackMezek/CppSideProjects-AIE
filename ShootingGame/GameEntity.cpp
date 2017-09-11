#include "GameEntity.h"



GameEntity::GameEntity(char ic, int xx, int yy, Player* p, std::vector<bool>* m)
{
	icon = ic;
	x = xx;
	y = xx;
	player = p;
	physmap = m;
}


GameEntity::~GameEntity()
{
}


#include "Entity.h"



int Entity::getPosx()
{
	return posx;
}
int Entity::getPosy()
{
	return posy;
}
int Entity::getHealth()
{
	return health;
}

void Entity::setPosx(int x)
{
	posx = x;
}
void Entity::setPosy(int y)
{
	posy = y;
}
void Entity::setHealth(int h)
{
	health = h;
}
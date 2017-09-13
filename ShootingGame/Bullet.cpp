#include "Bullet.h"



Bullet::Bullet(int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my)
	: GameEntity('*', xx, yy, p, m, e, mx, my)
{
	
}


Bullet::~Bullet()
{
}


void Bullet::update()
{
	x += vel.x;
	y += vel.y;

	if (x < 0 || x > mapsizex - 1 || y < 0 || y > mapsizey - 1)
	{
		alive = false;
	}
	else if (physmap->at((int)x + (int)y * mapsizex) == true)
	{
		alive = false;
	}
	else
	{
		for (int i = 0; i < entities->size(); ++i)
		{
			if (entities->at(i)->icon == '&' && (int)entities->at(i)->x == (int)x && (int)entities->at(i)->y == (int)y)
			{
				entities->at(i)->alive = false;
				alive = false;
				break;
			}
		}
	}
}
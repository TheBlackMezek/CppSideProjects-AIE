#include "Enemy.h"

#include "InputGetter.h"


Enemy::Enemy(int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my)
	: GameEntity('&', xx, yy, p, m, e, mx, my)
{
	vel = Vec2(p->x - x, p->y - y);
	vel.unit();
}


Enemy::~Enemy()
{
}


void Enemy::update()
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

	vel.x /= 10 * 2;
	vel.y /= 10 * 2;

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

	if (((int)x == player->x && (int)y == player->y) || vel.dist(x, y, player->x, player->y) < 1)
	{
		shouldExit = true;
	}


}

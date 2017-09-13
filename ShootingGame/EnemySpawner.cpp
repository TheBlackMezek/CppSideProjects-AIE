#include "EnemySpawner.h"

#include "Enemy.h"


EnemySpawner::EnemySpawner(char ic, int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my)
	: GameEntity(ic, xx, yy, p, m, e, mx, my)
{
	vel.x = 0;
	vel.y = 300 * 2;

	visible = false;
}

EnemySpawner::~EnemySpawner()
{
}




void EnemySpawner::update()
{
	++vel.x;

	if (vel.x == vel.y)
	{
		vel.x = 0;

		Enemy* e = new Enemy('&', x, y, player, physmap, entities, mapsizex, mapsizey);

		entities->push_back(e);
	}
}

#include "EnemySpawner.h"

#include "Enemy.h"


EnemySpawner::EnemySpawner(int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my)
	: GameEntity('^', xx, yy, p, m, e, mx, my)
{
	vel.x = 0;
	vel.y = 30 * 2;

	//visible = false;
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

		if (vel.y > 100)
		{
			vel.y -= 10;
		}

		Enemy* e = new Enemy(x, y, player, physmap, entities, mapsizex, mapsizey);

		entities->push_back(e);
	}
}

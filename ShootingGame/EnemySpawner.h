#pragma once
#include "GameEntity.h"



#ifndef _ENEMYSPAWNER_H_
#define _ENEMYSPAWNER_H_




class EnemySpawner :
	public GameEntity
{
public:
	EnemySpawner(int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my);
	~EnemySpawner();

	void update();
};

#endif
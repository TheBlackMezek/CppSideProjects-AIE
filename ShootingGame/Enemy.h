#pragma once
#include "GameEntity.h"



#ifndef _ENEMY_H_
#define _ENEMY_H_




class Enemy :
	public GameEntity
{
public:
	Enemy(char ic, int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my);
	~Enemy();

	void update();
};

#endif
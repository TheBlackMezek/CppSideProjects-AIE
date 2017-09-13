#pragma once
#include "GameEntity.h"



#ifndef _BULLET_H_
#define _BULLET_H_




class Bullet :
	public GameEntity
{
public:
	Bullet(int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my);
	~Bullet();

	void update();
};

#endif
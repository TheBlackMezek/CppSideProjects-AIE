#pragma once
#include "GameEntity.h"


#ifndef _LIGHTSPOT_H_
#define _LIGHTSPOT_H_



class LightSpot :
	public GameEntity
{
public:
	LightSpot(int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my);
	~LightSpot();

	void update();
};

#endif
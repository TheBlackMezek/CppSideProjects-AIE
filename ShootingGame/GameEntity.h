#pragma once


#ifndef _GAMEENTITY_H_
#define _GAMEENTITY_H_


#include <vector>
#include "Player.h"


class GameEntity
{
public:
	char icon;
	int x;
	int y;
	Player* player;
	int mapsizex;
	int mapsizey;
	std::vector<bool>* physmap;

	GameEntity(char ic, int xx, int yy, Player* p, std::vector<bool>* m, int mx, int my);
	~GameEntity();

	void update();
};

#endif
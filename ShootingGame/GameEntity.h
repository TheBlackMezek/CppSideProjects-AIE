#pragma once


#ifndef _GAMEENTITY_H_
#define _GAMEENTITY_H_


#include <vector>
#include "Player.h"
#include "Vec2.h"


class GameEntity
{
public:
	bool alive;

	char icon;
	bool visible;
	float x;
	float y;
	Vec2 vel;
	Player* player;
	std::vector<bool>* physmap;
	std::vector<GameEntity*>* entities;
	int mapsizex;
	int mapsizey;

	GameEntity();
	GameEntity(char ic, int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my);
	~GameEntity();

	virtual void update();
};

#endif
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_



class Player
{
public:
	Player();
	~Player();

	int x;
	int y;

	int gunCoolDown;
	int gunHeat;

	int walkCoolDown;
	int walkHeat;


	void update();
};

#endif
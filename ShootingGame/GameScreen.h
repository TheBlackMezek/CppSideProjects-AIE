#pragma once
#include "Screen.h"

#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_

#include "Player.h"


class GameScreen :
	public Screen
{
public:
	GameScreen();
	~GameScreen();

	void update(int mouseX, int mouseY);
	void makeImage();
private:
	Player player;
};


#endif
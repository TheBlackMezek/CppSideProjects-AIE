#pragma once
#include "Screen.h"

#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_

#include <vector>

#include "Player.h"


class GameScreen :
	public Screen
{
public:
	GameScreen();
	GameScreen(int winx, int winy, int mapx, int mapy);
	~GameScreen();

	void update(int mouseX, int mouseY);
	void makeImage();
	void loadMap(char name[]);
private:
	Player player;
	int mapSizeX;
	int mapSizeY;

	std::vector<char> charMap;
	std::vector<int> colorMap;
	std::vector<int> lightMap;
	std::vector<bool> physMap;
	int charColors[256];
};


#endif
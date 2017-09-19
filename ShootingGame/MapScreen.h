#pragma once
#include "Screen.h"
class MapScreen :
	public Screen
{
public:
	MapScreen(int winx, int winy);
	~MapScreen();

	static void loadMap(ElementData* e);
};


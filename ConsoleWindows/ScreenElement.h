#pragma once


#ifndef _SCREENELEMENT_H_
#define _SCREENELEMENT_H_


#include <string>
#include <vector>

#include "ElementStructs.h"







class ScreenElement
{
protected:
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	int textColor;
	//std::vector<CharData> image;
public:
	void makeImage();
	std::vector<CharData> getImage();

	void setPos(int x, int y);
	void setSize(int x, int y);

	int getPosX();
	int getPosY();
	int getSizeX();
	int getSizeY();

	ElementData static makeElementData(int px, int py, int sx, int sy, int color);
};


#endif
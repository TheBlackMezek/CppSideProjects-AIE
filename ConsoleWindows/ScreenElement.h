#pragma once


#ifndef _SCREENELEMENT_H_
#define _SCREENELEMENT_H_


#include <string>
#include <vector>



struct CharData
{
	char chr;
	int color;
};

struct ElementData
{
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	int textColor;
	std::vector<CharData> image;
};

struct Element
{
	bool exists     = false;
	int elementData = -1;
	int buttonData  = -1;
};



class ScreenElement
{
protected:
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	int textColor;
	std::vector<CharData> image;
public:
	void makeImage();
	std::vector<CharData> getImage();

	void setPos(int x, int y);
	void setSize(int x, int y);

	int getPosX();
	int getPosY();
	int getSizeX();
	int getSizeY();
};


#endif
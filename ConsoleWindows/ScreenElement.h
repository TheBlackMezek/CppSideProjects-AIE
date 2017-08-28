#pragma once


#ifndef _SCREENELEMENT_H_
#define _SCREENELEMENT_H_


#include <string>



class ScreenElement
{
protected:
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	std::string image;
public:
	void makeImage();
	std::string getImage();

	void setPos(int x, int y);
	void setSize(int x, int y);

	int getPosX();
	int getPosY();
	int getSizeX();
	int getSizeY();
};


#endif
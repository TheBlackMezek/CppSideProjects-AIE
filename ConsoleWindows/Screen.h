#pragma once


#ifndef _SCREEN_H_
#define _SCREEN_H_


//I wish I didn't have to include in a header
#include <vector>
#include <string>
#include "ScreenElement.h"



class Screen
{
private:
	int sizeX;
	int sizeY;
	std::string image;
	std::vector<ScreenElement> elements;
public:
	void update(int mouseX, int mouseY);
	void makeImage();
	void click();

	void addElement(ScreenElement e);
	void setSize(int x, int y);

	int getSizeX();
	int getSizeY();
	std::string getImage();
};


#endif
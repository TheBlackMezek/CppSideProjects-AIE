#pragma once


#ifndef _TEXTBUTTON_H_
#define _TEXTBUTTON_H_


#include <string>



class TextButton
{
private:
	bool mouseOver;
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	std::string text;
	std::string image;
	void(*callback)();
public:
	void update(int mouseX, int mouseY);
	void makeImage();
	void click();
	std::string getImage();

	void setPos(int x, int y);
	void setSize(int x, int y);
	void setText(std::string t);
	void setCallback(void(*f)());

	bool isMouseOver();
	int getPosX();
	int getPosY();
	int getSizeX();
	int getSizeY();
};


#endif
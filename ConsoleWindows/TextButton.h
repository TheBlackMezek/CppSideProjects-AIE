#pragma once


#ifndef _TEXTBUTTON_H_
#define _TEXTBUTTON_H_


//I wish I didn't have to include in a header
#include <string>
#include "ScreenElement.h"


struct ButtonData
{
	bool mouseOver;
	std::string text;
	void(*callback)();
};


class TextButton : public ScreenElement
{
private:
	bool mouseOver;
	std::string text;
	void(*callback)();
public:
	void update(int mouseX, int mouseY);
	void makeImage();
	void click();

	void setText(std::string t);
	void setCallback(void(*f)());

	bool isMouseOver();
};


#endif
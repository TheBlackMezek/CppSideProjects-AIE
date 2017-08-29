#pragma once



#include <vector>






struct CharData
{
	char chr;
	int color;
};




struct Component
{
	bool exists;
};

struct Element : Component
{
	int elementData = -1;
	int buttonData = -1;
};

struct ElementData : Component
{
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	int textColor;
	std::vector<CharData> image;
};

struct ButtonData : Component
{
	bool bordered;
	bool mouseOver;
	std::string text;
	void(*callback)();
};
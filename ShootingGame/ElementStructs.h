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
	int varText = -1;
};

struct ElementData : Component
{
	bool bordered;
	bool visible;
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	int textColor;
	std::vector<CharData> image;
	void(*imgRenderer)(ElementData* e);
	std::string data;
};

struct ButtonData : Component
{
	bool bordered;
	bool mouseOver;
	int onColor;
	int offColor;
	std::string text;
	void(*callback)();
	void(*dataCallback)(ElementData* b);
};

//Variable Text, text that uses variables for some of its content
struct VarText : Component
{
	std::string text;
	int type; //0 is int, 1 is float, 2 is string
	void* var;
};
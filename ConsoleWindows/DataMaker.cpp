
#include "DataMaker.h"





ElementData makeElementData(int px, int py, int sx, int sy, int color)
{
	ElementData ret;
	ret.exists = true;
	ret.posX = px;
	ret.posY = py;
	ret.sizeX = sx;
	ret.sizeY = sy;
	ret.textColor = color;
	return ret;
}

ButtonData makeButtonData(bool bordered, std::string text, void(*c)())
{
	ButtonData ret;
	ret.bordered = bordered;
	ret.exists = true;
	ret.mouseOver = false;
	ret.text = text;
	ret.callback = c;
	return ret;
}
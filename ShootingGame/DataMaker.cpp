
#include "DataMaker.h"





ElementData makeElementData(int px, int py, int sx, int sy, int color)
{
	ElementData ret;
	ret.bordered = false;
	ret.visible = true;
	ret.exists = true;
	ret.posX = px;
	ret.posY = py;
	ret.sizeX = sx;
	ret.sizeY = sy;
	ret.textColor = color;
	ret.imgRenderer = NULL;
	ret.data = "";
	return ret;
}

ButtonData makeButtonData(bool bordered, int offColor, int onColor, std::string text, void(*c)())
{
	ButtonData ret;
	ret.bordered = bordered;
	ret.exists = true;
	ret.mouseOver = false;
	ret.offColor = offColor;
	ret.onColor = onColor;
	ret.text = text;
	ret.callback = c;
	ret.dataCallback = NULL;
	return ret;
}

VarText makeVarText(std::string text, int type, void* v)
{
	VarText ret;
	ret.exists = true;
	ret.text = text;
	ret.type = type;
	ret.var = v;
	return ret;
}
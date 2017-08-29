
#include "ScreenElement.h"






std::vector<CharData> ScreenElement::getImage()
{
	//return image;
	return std::vector<CharData>();
}

void ScreenElement::makeImage()
{
	std::vector<CharData> image = std::vector<CharData>();
	image.resize(sizeX * sizeY);
	//TEMPORARY, should be in constructor
	textColor = 0x000F;
	char ap = ' ';

	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			image[x + y * sizeX].chr = '#';
			image[x + y * sizeX].color = textColor;
		}
	}
}

void ScreenElement::setPos(int x, int y)
{
	posX = x;
	posY = y;
}

void ScreenElement::setSize(int x, int y)
{
	sizeX = x;
	sizeY = y;
}




int ScreenElement::getPosX()
{
	return posX;
}

int ScreenElement::getPosY()
{
	return posY;
}

int ScreenElement::getSizeX()
{
	return sizeX;
}

int ScreenElement::getSizeY()
{
	return sizeY;
}



ElementData ScreenElement::makeElementData(int px, int py, int sx, int sy, int color)
{
	ElementData ret;
	ret.exists = true;
	ret.posX = px;
	ret.posY = py;
	ret.sizeX = sx;
	ret.sizeY = sy;
	return ret;
}
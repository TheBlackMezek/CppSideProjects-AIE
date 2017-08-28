
#include "ScreenElement.h"






std::string ScreenElement::getImage()
{
	return image;
}

void ScreenElement::makeImage()
{
	image = "";
	char ap = ' ';

	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			image += "#";
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
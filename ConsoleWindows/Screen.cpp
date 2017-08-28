
#include "Screen.h"







void Screen::update(int mouseX, int mouseY)
{
	for (int i = 0; i < elements.size(); ++i)
	{
		
	}
}

void Screen::makeImage()
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

void Screen::click()
{
	
}





void Screen::addElement(ScreenElement e)
{
	elements.push_back(e);
}

void Screen::setSize(int x, int y)
{
	sizeX = x;
	sizeY = y;
}





int Screen::getSizeX()
{
	return sizeX;
}

int Screen::getSizeY()
{
	return sizeY;
}

std::string Screen::getImage()
{
	return image;
}
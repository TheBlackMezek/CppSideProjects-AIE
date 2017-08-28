
#include "Screen.h"







void Screen::update(int mouseX, int mouseY)
{
	for (int i = 0; i < elements.size(); ++i)
	{
		
	}
}

void Screen::makeImage()
{
	image = std::vector<CharData>();
	image.resize(sizeX * sizeY);
	char ap = ' ';

	//Make an empty image first, of the correct size
	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			image[x + y * sizeX].chr = ' ';
			image[x + y * sizeX].color = 0x000F;
		}
	}

	//Add images from elements
	for (int i = 0; i < elements.size(); ++i)
	{
		std::vector<CharData> eimg = elements[i].getImage();
		for (int y = elements[i].getPosY(); y < elements[i].getPosY() + elements[i].getSizeY(); ++y)
		{
			for (int x = elements[i].getPosX(); x < elements[i].getPosX() + elements[i].getSizeX(); ++x)
			{
				if (x < sizeX && y < sizeY)
				{
					int imgPos = x - elements[i].getPosX() + (y - elements[i].getPosY()) * elements[i].getSizeX();
					image[x + y * sizeX].chr = elements[i].getImage().at(imgPos).chr;
					image[x + y * sizeX].color = elements[i].getImage().at(imgPos).color;

					/*image.replace(x + y * sizeX, 1, 
						eimg.substr( x - elements[i].getPosX() + (y - elements[i].getPosY()) * elements[i].getSizeX(), 1 ) );*/
				}
			}
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

std::vector<CharData> Screen::getImage()
{
	return image;
}
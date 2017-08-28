
#include "Screen.h"







Screen::Screen()
{
	maxElms = 100;
}


void Screen::update(int mouseX, int mouseY)
{
	for (int i = 0; i < maxElms; ++i)
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
	for (int i = 0; i < maxElms; ++i)
	{
		//std::vector<CharData> eimg = elements[i].getImage();
		std::vector<CharData> eimg = elmDat[elements[i].elementData].image;
		for (int y = elmDat[elements[i].elementData].posY; y < elmDat[elements[i].elementData].posY + elmDat[elements[i].elementData].sizeY; ++y)
		{
			for (int x = elmDat[elements[i].elementData].posX; x < elmDat[elements[i].elementData].posX + elmDat[elements[i].elementData].sizeX; ++x)
			{
				if (x < sizeX && y < sizeY)
				{
					int imgPos = x - elmDat[elements[i].elementData].posX + (y - elmDat[elements[i].elementData].posY) * elmDat[elements[i].elementData].sizeX;
					image[x + y * sizeX].chr = elmDat[elements[i].elementData].image.at(imgPos).chr;
					image[x + y * sizeX].color = elmDat[elements[i].elementData].image.at(imgPos).color;

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





int Screen::addElement(ElementData ed)
{
	//elements.push_back(e);
	Element e;
	int open = getOpenIndex(elmDat);
	elmDat[open] = ed;
	e.elementData = open;

	open = getOpenIndex(elements);
	elements[open] = e;

	return open;
}

int Screen::addButton(int elm, ButtonData b)
{
	int open = getOpenIndex(butDat);
	butDat[open] = b;

	elements[elm].buttonData = open;

	return open;
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



int Screen::getOpenIndex(Component *c)
{
	int i = 0;
	for (; c[i].exists; ++i) {}
	c[i].exists = true;
	return i;
}
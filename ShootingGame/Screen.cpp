
#include "Screen.h"


#include "ImageMaker.h"
#include "InputGetter.h"




Screen::Screen()
{
	maxElms = 100;
	for (int i = 0; i < maxElms; ++i)
	{
		elements[i].exists = false;
	}
	for (int i = 0; i < maxElms; ++i)
	{
		elmDat[i].exists = false;
	}
	for (int i = 0; i < maxElms; ++i)
	{
		butDat[i].exists = false;
	}
	for (int i = 0; i < maxElms; ++i)
	{
		varTxt[i].exists = false;
	}
}




void Screen::update(int mouseX, int mouseY)
{
	for (int i = 0; i < maxElms; ++i)
	{
		if (elements[i].exists && elements[i].buttonData >= 0)
		{
			if (mouseX >= elmDat[elements[i].elementData].posX &&
				mouseX <= elmDat[elements[i].elementData].posX + elmDat[elements[i].elementData].sizeX - 1 &&
				mouseY >  elmDat[elements[i].elementData].posY &&
				mouseY <= elmDat[elements[i].elementData].posY + elmDat[elements[i].elementData].sizeY)
			{
				butDat[elements[i].buttonData].mouseOver = true;
				if (lclick)
				{
					if (butDat[elements[i].buttonData].callback)
					{
						butDat[elements[i].buttonData].callback();
					}
					if (butDat[elements[i].buttonData].dataCallback)
					{
						butDat[elements[i].buttonData].dataCallback(&elmDat[elements[i].elementData]);
					}
					//lclick = false;
				}
			}
			else
			{
				butDat[elements[i].buttonData].mouseOver = false;
			}
			makeButtonImage(&elmDat[elements[i].elementData], &butDat[elements[i].buttonData]);
		}
	}

	//if (lclick) { lclick = false; }

	makeImage();
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
		if (elements[i].exists && elmDat[elements[i].elementData].visible)
		{
			if (elmDat[elements[i].elementData].imgRenderer != NULL)
			{
				elmDat[elements[i].elementData].imgRenderer(&elmDat[elements[i].elementData]);
			}
			else if (elements[i].varText != -1)
			{
				makeTextImageWithVars(elmDat[elements[i].elementData].bordered,
					varTxt[elements[i].varText].text,
					varTxt[elements[i].varText].text.size(),
					&elmDat[elements[i].elementData],
					&varTxt[elements[i].varText]);
			}

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
					}
				}
			}
		}
	}
}

void Screen::click()
{
	for (int i = 0; i < maxElms; ++i)
	{
		if (butDat[i].mouseOver)
		{
			if (butDat[i].callback != NULL)
			{
				butDat[i].callback();
			}
			if (butDat[i].dataCallback != NULL)
			{
				butDat[i].dataCallback(&elmDat[i]);
			}
		}
	}
}





int Screen::addElement(ElementData ed)
{
	Element e;
	e.exists = true;
	e.buttonData = -1;
	e.varText = -1;
	int open = getOpenIndex(elmDat);
	elmDat[open] = ed;
	e.elementData = open;

	if (ed.imgRenderer != NULL)
	{
		ed.imgRenderer(&ed);
	}

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

int Screen::addVarText(int elm, VarText t)
{
	int open = getOpenIndex(varTxt);
	varTxt[open] = t;

	elements[elm].varText = open;

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



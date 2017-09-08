#include "GameScreen.h"


#include "InputGetter.h"
#include "Player.h"
#include "ImageMaker.h"


GameScreen::GameScreen()
{
	player = Player();
}


GameScreen::~GameScreen()
{
}


void GameScreen::update(int mouseX, int mouseY)
{
	Screen::update(mouseX, mouseY);

	if (UP)
	{
		++player.y;
	}
	if (DOWN)
	{
		--player.y;
	}
	if (RIGHT)
	{
		++player.x;
	}
	if (LEFT)
	{
		--player.x;
	}

	makeImage();
}


void GameScreen::makeImage()
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

	image[player.x + (sizeY - 1 - player.y) * sizeX].chr = '@';
	image[player.x + (sizeY - 1 - player.y) * sizeX].color = 0x000F;
}


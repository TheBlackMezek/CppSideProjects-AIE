#include "GameScreen.h"


#include "InputGetter.h"
#include "Player.h"
#include "ImageMaker.h"


GameScreen::GameScreen()
{
	for (int i = 0; i < 256; ++i)
	{
		charColors[i] = 0x000F;
	}
	player = Player();
}

GameScreen::GameScreen(int winx, int winy, int mapx, int mapy)
{
	sizeX = winx;
	sizeY = winy;
	mapSizeX = mapx;
	mapSizeY = mapy;

	for (int i = 0; i < 256; ++i)
	{
		charColors[i] = rand() % 16;
	}
	player = Player();
	
	charColors['.'] = 0x000A;

	charMap = std::vector<char>(mapx * mapy);
	for (int i = 0; i < mapx * mapy; ++i)
	{
		charMap[i] = rand() % 256;
	}
	colorMap = std::vector<int>(mapx * mapy);
	for (int i = 0; i < mapx * mapy; ++i)
	{
		colorMap[i] = 0;
	}
	lightMap = std::vector<int>(mapx * mapy);
	for (int i = 0; i < mapx * mapy; ++i)
	{
		lightMap[i] = 1;
	}
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

	for (int y = 0; y < mapSizeY; ++y)
	{
		for (int x = 0; x < mapSizeX; ++x)
		{
			if (lightMap[x + y * mapSizeX] > 0)
			{
				colorMap[x + y * mapSizeX] = charColors[charMap[x + y * mapSizeX]];
			}
			else
			{
				colorMap[x + y * mapSizeX] = 0x0000;
			}
		}
	}

	//Make an empty image first, of the correct size
	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			//image[x + y * sizeX].chr = ' ';
			//image[x + y * sizeX].color = 0x000F;
			if (x == sizeX / 2 && y == sizeY / 2)
			{
				image[x + y * sizeX].chr = '@';
				image[x + y * sizeX].color = 0x000F;
			}
			else if (x - sizeX / 2 + player.x >= 0 && x - sizeX / 2 + player.x < mapSizeX &&
				     y - sizeY / 2 - player.y >= 0 && y - sizeY / 2 - player.y < mapSizeY)
			{
				image[x + y * sizeX].chr =   charMap [(x - sizeX / 2 + player.x) + (y - sizeY / 2 - player.y) * mapSizeX];
				image[x + y * sizeX].color = colorMap[(x - sizeX / 2 + player.x) + (y - sizeY / 2 - player.y) * mapSizeX];
			}
			else
			{
				image[x + y * sizeX].chr = ' ';
				image[x + y * sizeX].color = 0x000F;
			}
		}
	}

	//Add images from elements
	/*for (int i = 0; i < maxElms; ++i)
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
	}*/

	//image[player.x + (sizeY - 1 - player.y) * sizeX].chr = '@';
	//image[player.x + (sizeY - 1 - player.y) * sizeX].color = 0x000F;
}


#include "GameScreen.h"

#include <fstream>
#include <string>

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
		charColors[i] = 0x000F;
	}
	for (int i = 0; i < 256; ++i)
	{
		charPhys[i] = false;
	}
	for (int i = 0; i < 256; ++i)
	{
		charLights[i] = 0;
	}

	player = Player();
	
	charColors['.'] = 0x000A;
	charColors['W'] = 0x0088;
	charPhys['W'] = true;


	entities = std::vector<GameEntity*>();


	charMap = std::vector<char>(mapx * mapy);
	for (int i = 0; i < mapx * mapy; ++i)
	{
		charMap[i] = '.';
	}
	colorMap = std::vector<int>(mapx * mapy);
	for (int i = 0; i < mapx * mapy; ++i)
	{
		colorMap[i] = 0;
	}
	lightMap = std::vector<int>(mapx * mapy);
	for (int i = 0; i < mapx * mapy; ++i)
	{
		lightMap[i] = 0;
	}
	physMap = std::vector<bool>(mapx * mapy);
	for (int i = 0; i < mapx * mapy; ++i)
	{
		physMap[i] = false;
	}
	
	

	loadMap("map.txt");
	player = player;
}


GameScreen::~GameScreen()
{
	for (int i = 0; i < entities.size(); ++i)
	{
		delete entities[i];
	}
}


void GameScreen::update(int mouseX, int mouseY)
{
	//Screen::update(mouseX, mouseY);

	if (UP && player.y + 1 < mapSizeY && physMap[player.x + (player.y + 1) * mapSizeX] == false)
	{
		++player.y;
	}
	if (DOWN && player.y - 1 >= 0 && physMap[player.x + (player.y - 1) * mapSizeX] == false)
	{
		--player.y;
	}
	if (RIGHT && player.x + 1 < mapSizeX && physMap[player.x + 1 + player.y * mapSizeX] == false)
	{
		++player.x;
	}
	if (LEFT && player.x - 1 >= 0 && physMap[player.x - 1 + player.y * mapSizeX] == false)
	{
		--player.x;
	}

	for (int i = 0; i < entities.size(); ++i)
	{
		entities[i]->update();
	}

	makeImage();
}


void GameScreen::makeImage()
{
	image = std::vector<CharData>();
	image.resize(sizeX * sizeY);
	char ap = ' ';

	makeLight();

	//Make an empty image first, of the correct size
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
				     y - sizeY / 2 + player.y >= 0 && y - sizeY / 2 + player.y < mapSizeY)
			{
				image[x + (sizeY - 1 - y) * sizeX].chr =   charMap [(x - sizeX / 2 + player.x) + (y - sizeY / 2 + player.y) * mapSizeX];
				image[x + (sizeY - 1 - y) * sizeX].color = colorMap[(x - sizeX / 2 + player.x) + (y - sizeY / 2 + player.y) * mapSizeX];
			}
			else
			{
				image[x + (sizeY - 1 - y) * sizeX].chr = ' ';
				image[x + (sizeY - 1 - y) * sizeX].color = 0x000F;
			}
		}
	}

	for (int i = 0; i < entities.size(); ++i)
	{
		image[(entities[i]->x + sizeX / 2 - player.x) + (sizeY - 1 - (entities[i]->y + sizeY / 2 - player.y)) * sizeX].chr = entities[i]->icon;
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


void GameScreen::loadMap(char name[])
{
	std::fstream file;
	file.open(name);

	std::string line;
	//Get color, physics and light data
	std::getline(file, line);
	for (int i = 0; i < line.size(); i += 5)
	{
		charColors[line[i]] = std::stoi(line.substr(i + 2, 2), nullptr, 16);
	}
	std::getline(file, line);
	for (int i = 0; i < line.size(); i += 4)
	{
		charPhys[line[i]] = std::stoi(line.substr(i + 2, 1));
	}
	std::getline(file, line);
	for (int i = 0; i < line.size(); i += 0)
	{
		int numEnd = line.find(' ', i+2);
		charLights[line[i]] = std::stoi(line.substr(i + 2, line.size() - numEnd - 1));
		i += numEnd - i + 1;
		if (numEnd == line.npos)
		{
			break;
		}
	}

	//Build map
	std::string text;
	int lineCount = 0;
	while (std::getline(file, line))
	{
		if (line.at(line.size() - 1) == '\n')
		{
			line.erase(line.end());
		}
		text.append(line);
		++lineCount;
	}

	mapSizeX = line.size();
	mapSizeY = lineCount;

	charMap.clear();
	charMap.resize(mapSizeX * mapSizeY);
	physMap.clear();
	physMap.resize(mapSizeX * mapSizeY);
	for (int i = 0; i < mapSizeX * mapSizeY; ++i)
	{
		physMap[i] = false;
	}
	lightMap.clear();
	lightMap.resize(mapSizeX * mapSizeY);
	colorMap.clear();
	colorMap.resize(mapSizeX * mapSizeY);

	for (int y = 0; y < mapSizeY; ++y)
	{
		for (int x = 0; x < mapSizeX; ++x)
		{
			if (text[x + y * mapSizeX] == '@')
			{
				charMap[x + (mapSizeY - 1 - y) * mapSizeX] = '.';
				player.x = x;
				player.y = (mapSizeY - 1 - y);
			}
			else if (text[x + y * mapSizeX] == '&')
			{

				charMap[x + (mapSizeY - 1 - y) * mapSizeX] = '.';
				GameEntity* terry = new GameEntity('&', x, y, &player, &physMap, mapSizeX, mapSizeY);
				
				entities.push_back(terry);
			}
			else
			{
				charMap[x + (mapSizeY - 1 - y) * mapSizeX] = text[x + y * mapSizeX];
				if (charPhys[text[x + y * mapSizeX]])
				{
					physMap[x + (mapSizeY - 1 - y) * mapSizeX] = true;
				}
			}
		}
	}

	file.close();
}


void GameScreen::makeLight()
{
	for (int y = 0; y < mapSizeY; ++y)
	{
		for (int x = 0; x < mapSizeX; ++x)
		{
			lightMap[x + y * mapSizeX] = 0;
		}
	}

	for (int y = 0; y < mapSizeY; ++y)
	{
		for (int x = 0; x < mapSizeX; ++x)
		{

			if (charLights[charMap[x + y * mapSizeX]] > 0)
			{
				int ls = charLights[charMap[x + y * mapSizeX]];
				for (int yy = y - ls; yy <= y + ls; ++yy)
				{
					for (int xx = x - ls; xx <= x + ls; ++xx)
					{
						if (xx >= 0 && xx < mapSizeX && yy >= 0 && yy < mapSizeY)
						{
							lightMap[xx + yy * mapSizeX] = 1;
						}
					}
				}
			}

		}
	}
}

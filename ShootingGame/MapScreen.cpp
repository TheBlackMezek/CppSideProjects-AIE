#include "MapScreen.h"


#include <fstream>

#include "DataMaker.h"
#include "ImageMaker.h"
#include "GameScreens.h"


MapScreen::MapScreen(int winx, int winy)
{
	sizeX = winx;
	sizeY = winy;



	ElementData elmdat;
	VarText var;
	int idx;
	ButtonData butDat;


	int map = 1;
	int mapX = 5;
	int mapY = 3;
	std::string mname = "map.txt";
	std::string butText = "map";
	while (std::ifstream(mname.insert(3, std::to_string(map))) && map <= 90)
	{
		std::ifstream file;
		file.open(mname);
		std::getline(file, butText);
		butText = butText.substr(butText.find(' ') + 1, butText.npos);


		elmdat = makeElementData(mapX, mapY, butText.size() + 2, 3, 0x000F);
		elmdat.data = mname;
		butDat = makeButtonData(true, 0x000A, 0x000C, butText, NULL);
		butDat.dataCallback = &loadMap;
		makeButtonImage(&elmdat, &butDat);
		idx = addElement(elmdat);
		addButton(idx, butDat);

		++map;
		mapY += 5;

		if (map == 10)
		{
			mapX = 50;
			mapY = 3;
		}

		mname.erase(3, 1);

	}


}


MapScreen::~MapScreen()
{
}


void MapScreen::loadMap(ElementData* e)
{
	gameScreen->loadMap(e->data.c_str());
	switchScreenToGame();
}



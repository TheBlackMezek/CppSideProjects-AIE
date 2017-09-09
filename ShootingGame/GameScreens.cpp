
#include "GameScreens.h"

#include <string>

#include "WindowSetup.h"
#include "DataMaker.h"
#include "ImageMaker.h"
#include "InputGetter.h"


GameScreen* screen;
GameScreen gameScreen;



void initScreens()
{
	initGameScreen();
}



void initGameScreen()
{
	gameScreen = GameScreen(WIN_WIDTH, WIN_HEIGHT, 200, 200);
	//gameScreen.setSize(WIN_WIDTH, WIN_HEIGHT);

	std::string termStr = "TERMINOLOGY:\n\n"
		"object - Anything in space, be it planet, moon, star, or ship.\n"
		"satellite - Anything in orbit of something else.\n"
		"    Moons are satellites of planets.\n"
		"\n"
		"synthlife - Artificial plants and animals.\n"
		"    Some are for pleasure, but most are for utility.\n"
		"    Most cannot reproduce and must be manufactured.\n";
	ElementData elmdat = makeElementData(10, 10, WIN_WIDTH - 20, 10, 0x000F);
	makeTextImageMultiLine(false, termStr.c_str(), termStr.size(), &elmdat);
	gameScreen.addElement(elmdat);
	


	//Screen buttons
	elmdat = makeElementData(1, 1, 6, 3, 0x000F);
	ButtonData butDat = makeButtonData(true, 0x000B, 0x0009, "Game", &switchScreenToGame);
	makeButtonImage(&elmdat, &butDat);
	int idx = gameScreen.addElement(elmdat);
	gameScreen.addButton(idx, butDat);


	gameScreen.makeImage();
}




void switchScreenToGame()
{
	screen = &gameScreen;
}





#include "ScoreScreen.h"

#include <fstream>
#include <list>

#include "DataMaker.h"
#include "ImageMaker.h"
#include "GameScreens.h"



ScoreScreen::ScoreScreen(int winx, int winy)
{
	sizeX = winx;
	sizeY = winy;

	std::fstream file;
	file.open("HighScores.txt");

	ElementData elmdat;
	VarText var;
	int idx;

	std::string termStr = "High Scores for ";
	elmdat = makeElementData(2, 2, 70, 3, 0x000F);
	var = makeVarText("High Scores for %s", 2, &gameScreen->mapName);
	makeTextImageWithVars(true, "%s", 2, &elmdat, &var);
	idx = addElement(elmdat);
	addVarText(idx, var);


	std::string line;
	std::list<int> highScores;

	while (std::getline(file, line))
	{
		if (line.substr(line.find(' ') + 1, line.npos) == gameScreen->mapName)
		{
			int thisScore = std::stoi(line.substr(0, line.find(' ')));

			std::list<int>::iterator it;
			for (it = highScores.begin(); it != highScores.end(); ++it)
			{
				if (thisScore >= *it)
				{
					highScores.insert(it, thisScore);
					break;
				}
			}
			if (highScores.empty())
			{
				highScores.push_back(thisScore);
			}
		}
	}


	int scorey = 10;
	int maxScores = 8;
	int scoreCount = 0;

	std::list<int>::iterator it;
	for (it = highScores.begin(); it != highScores.end() && scoreCount < maxScores; ++it)
	{
		elmdat = makeElementData(sizeX / 2 - 6, scorey, 12, 3, 0x000F);
		makeTextImage(true, std::to_string(*it).c_str(),
			std::to_string(*it).size(), &elmdat);
		addElement(elmdat);

		scorey += 4;

		++scoreCount;
	}
	

	elmdat = makeElementData(sizeX - 13, 1, 11, 3, 0x000F);
	ButtonData butDat = makeButtonData(true, 0x000A, 0x000C, "Try Again", &switchScreenToGame);
	makeButtonImage(&elmdat, &butDat);
	idx = addElement(elmdat);
	addButton(idx, butDat);
}


ScoreScreen::~ScoreScreen()
{
}

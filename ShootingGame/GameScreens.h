#pragma once

#include "Screen.h"

#include "GameScreen.h"
#include "ScoreScreen.h"
#include "MapScreen.h"


extern Screen* screen;
extern GameScreen* gameScreen;
extern ScoreScreen* scoreScreen;
extern MapScreen* mapScreen;

//#define gameScreen (*screen)

void initScreens();

void cleanupScreens();

void initGameScreen();


void switchScreenToGame();

void switchScreenToMap();






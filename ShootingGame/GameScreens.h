#pragma once

#include "Screen.h"

#include "GameScreen.h"
#include "ScoreScreen.h"


extern Screen* screen;
extern GameScreen* gameScreen;
extern ScoreScreen* scoreScreen;

//#define gameScreen (*screen)

void initScreens();

void cleanupScreens();

void initGameScreen();


void switchScreenToGame();






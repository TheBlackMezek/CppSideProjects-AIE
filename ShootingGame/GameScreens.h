#pragma once

#include "Screen.h"

#include "GameScreen.h"


extern GameScreen* screen;
//extern GameScreen gameScreen;

#define gameScreen (*screen)

void initScreens();

void initGameScreen();


void switchScreenToGame();






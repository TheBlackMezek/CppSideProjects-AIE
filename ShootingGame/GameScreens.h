#pragma once

#include "Screen.h"



extern Screen* screen;
extern Screen gameScreen;

void initScreens();

void initGameScreen();


void switchScreenToGame();




void makeCurrentOrbitImg(ElementData* e);
void makeCargoImg(ElementData* e);
void makeShipScreenImg(ElementData* e);
void makeShopNameImg(ElementData* e);
void makeShopItemImg(ElementData* e);
void makeFuelCostImg(ElementData* e);
void makeRetirementImg(ElementData* e);
void makeRetireCostImg(ElementData* e);
void makeEndImg(ElementData* e);

void buyGoods(ElementData* e);
void sellGoods(ElementData* e);
void goToObj(ElementData* e);
void clickRetire();

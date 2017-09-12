#pragma once


#include "WindowSetup.h"
#include "Vec2.h"



//struct vec2
//{
//	int x;
//	int y;
//};



extern INPUT_RECORD* eventBuffer;
extern DWORD numEventsRead;

extern Vec2 mouse;
extern bool lclick;
extern bool ldown;
extern bool lclickswitch;
extern bool rclick;
extern bool rdown;
extern bool rclickswitch;
extern bool shouldExit;


extern bool UP;
extern bool DOWN;
extern bool LEFT;
extern bool RIGHT;


DWORD getInput(INPUT_RECORD **evB);

void checkInput();


#pragma once


#include <windows.h>


const int WIN_WIDTH = 100;
const int WIN_HEIGHT = 50;

//Each CHAR_INFO contains data for a single character: its ASCII char and color
//CHAR_INFO consoleBuffer[WIN_WIDTH * WIN_HEIGHT];
extern CHAR_INFO consoleBuffer[];
extern COORD charBufferSize;
extern COORD charPosition;
extern SMALL_RECT consoleWriteArea;

extern HANDLE hstdin;
extern HANDLE hstdout;


void WindowSetup();


//Fancy console stuff learned/copied from:
//http://cecilsunkure.blogspot.com/2011/11/windows-console-game-setting-up-window.html
#pragma once


#include <windows.h>


const int WIN_WIDTH = 101;
const int WIN_HEIGHT = 51;

//Each CHAR_INFO contains data for a single character: its ASCII char and color
extern CHAR_INFO consoleBuffer[];
extern COORD charBufferSize;
extern COORD charPosition;
extern SMALL_RECT consoleWriteArea;

extern CONSOLE_CURSOR_INFO cursorInfo;

extern HANDLE hstdin;
extern HANDLE hstdout;


void WindowSetup(char title[]);


//Fancy console stuff learned/copied from:
//http://cecilsunkure.blogspot.com/2011/11/windows-console-game-setting-up-window.html

//Cursor disabling code copied from:
//https://stackoverflow.com/questions/18028808/blinking-underscore-with-console
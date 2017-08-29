#pragma once


#include "ElementStructs.h"


ElementData makeElementData(int px, int py, int sx, int sy, int color);

ButtonData makeButtonData(bool bordered, std::string text, void(*c)());
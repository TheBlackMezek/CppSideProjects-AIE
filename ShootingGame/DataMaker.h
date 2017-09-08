#pragma once


#include "ElementStructs.h"


ElementData makeElementData(int px, int py, int sx, int sy, int color);

ButtonData makeButtonData(bool bordered, int offColor, int onColor, std::string text, void(*c)());

VarText makeVarText(std::string text, int type, void* v);

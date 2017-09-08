#pragma once


#include "ElementStructs.h"


void makeEmptyImage(ElementData *e);

void makeTextImage(bool bordered, const char text[], int textSize, ElementData *e);

void makeTextImageMultiLine(bool bordered, const char text[], int textSize, ElementData *e);

void makeTextImageWithVars(bool bordered, std::string text, int textSize, ElementData *e, VarText* v);

void makeButtonImage(ElementData *e, ButtonData* b);
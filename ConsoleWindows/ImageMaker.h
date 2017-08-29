#pragma once


#include "ElementStructs.h"


void makeEmptyImage(ElementData *e);

void makeTextImage(bool bordered, const char text[], int textSize, ElementData *e);

void makeButtonImage(ElementData *e, ButtonData* b);
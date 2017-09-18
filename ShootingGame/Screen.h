#pragma once


#ifndef _SCREEN_H_
#define _SCREEN_H_


//I wish I didn't have to include in a header
#include <vector>
#include <string>
#include "ElementStructs.h"


class Screen
{
protected:
	int sizeX;
	int sizeY;
	std::vector<CharData> image;

	template<typename T>
	int getOpenIndex(const T data[])
	{
		int i = 0;
		for (; data[i].exists; ++i);
		return i;
	}

public:
	Screen();
	// ---------- AGGREGATION TEST ---------- //
	int maxElms; //This needs to be made static, constant
	Element     elements[100];
	ElementData elmDat[100];
	ButtonData  butDat[100];
	VarText     varTxt[100];
	// -------------------------------------- //

	virtual void update(int mouseX, int mouseY);
	void makeImage();
	void click();

	int addElement(ElementData ed);
	int addButton(int elm, ButtonData b);
	int addVarText(int elm, VarText t);
	void setSize(int x, int y);

	int getSizeX();
	int getSizeY();
	std::vector<CharData> getImage();
};


#endif
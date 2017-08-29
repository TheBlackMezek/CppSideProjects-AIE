#pragma once


#ifndef _SCREEN_H_
#define _SCREEN_H_


//I wish I didn't have to include in a header
#include <vector>
#include <string>
#include "ElementStructs.h"


class Screen
{
private:
	int sizeX;
	int sizeY;
	//std::string image;
	std::vector<CharData> image;
	//std::vector<ScreenElement> elements;
	// ---------- AGGREGATION TEST ---------- //
	int maxElms; //This needs to be made static, constant
	Element     elements[100];
	ElementData elmDat[100];
	ButtonData  butDat[100];
	// -------------------------------------- //
	/*int getOpenIndex(Component c[]);
	int getOpenIndex(Element c[]);
	int getOpenIndex(ElementData c[]);
	int getOpenIndex(ButtonData c[]);

	int getOpenIndex(Component *data, int stride);*/

	template<typename T>
	int getOpenIndex(const T data[])
	{
		//return getOpenIndex(data, sizeof(T));
		int i = 0;
		for (; data[i].exists; ++i);
		return i;
	}

public:
	Screen();

	void update(int mouseX, int mouseY);
	void makeImage();
	void click();

	int addElement(ElementData ed);
	int addButton(int elm, ButtonData b);
	void setSize(int x, int y);

	int getSizeX();
	int getSizeY();
	std::vector<CharData> getImage();
};


#endif
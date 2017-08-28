
#include "TextButton.h"


void TextButton::update(int mouseX, int mouseY)
{
	if (mouseX >= posX &&
		mouseX <= posX + sizeX - 1 &&
		mouseY >= posY &&
		mouseY <= posY + sizeY - 1)
	{
		mouseOver = true;
	}
	else
	{
		mouseOver = false;
	}
}

void TextButton::makeImage()
{
	image = "";
	char ap = ' ';

	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			//Corners
			//Bottom left
			if (x == 0 && y == 0)
			{
				image += char(0xC9);
			}
			//Top left
			else if (x == 0 && y == sizeY - 1)
			{
				image += char(0xC8);
			}
			//Bottom right
			else if (x == sizeX - 1 && y == 0)
			{
				image += char(0xBB);
			}
			//Top right
			else if (x == sizeX - 1 && y == sizeY - 1)
			{
				image += char(0xBC);
			}

			//Sides
			//Bottom and Top sides
			else if (y == 0 || y == sizeY - 1)
			{
				image += char(0xCD);
			}
			//Left and Right sides
			else if (x == 0 || x == sizeX - 1)
			{
				image += char(0xBA);
				//image += " ";
			}

			//Text
			else if (y == (sizeY - 1) / 2 && x <= text.size())
			{
				image += text.at(x - 1);
			}

			//Empty space
			else
			{
				image += " ";
			}
		}
	}
}

void TextButton::click()
{
	if (mouseOver)
	{
		callback();
	}
}

void TextButton::setText(std::string t)
{
	text = t;
}

void TextButton::setCallback(void(*f)())
{
	callback = f;
}



bool TextButton::isMouseOver()
{
	return mouseOver;
}
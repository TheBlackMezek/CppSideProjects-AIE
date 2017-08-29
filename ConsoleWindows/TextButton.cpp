
#include "TextButton.h"


void TextButton::update(int mouseX, int mouseY)
{
	if (mouseX >= posX &&
		mouseX <= posX + sizeX - 1 &&
		mouseY >= posY &&
		mouseY <= posY + sizeY - 1)
	{
		mouseOver = true;
		textColor = 0x0006;
	}
	else
	{
		mouseOver = false;
		textColor = 0x000F;
	}
	//makeImage();
}

void TextButton::makeImage(ElementData* e, ButtonData* b)
{
	e->image = std::vector<CharData>();
	e->image.resize(e->sizeX * e->sizeY);
	char ap = ' ';
	//TEMPORARY
	if (b->mouseOver)
	{
		e->textColor = 0x000B;
		//e->textColor = rand() % 100;
	}
	else
	{
		e->textColor = 0x000F;
	}
	

	for (int y = 0; y < e->sizeY; ++y)
	{
		for (int x = 0; x < e->sizeX; ++x)
		{
			//Corners
			//Bottom left
			if (x == 0 && y == 0)
			{
				e->image[x + y * e->sizeX].chr = char(0xC9);
			}
			//Top left
			else if (x == 0 && y == e->sizeY - 1)
			{
				e->image[x + y * e->sizeX].chr = char(0xC8);
			}
			//Bottom right
			else if (x == e->sizeX - 1 && y == 0)
			{
				e->image[x + y * e->sizeX].chr = char(0xBB);
			}
			//Top right
			else if (x == e->sizeX - 1 && y == e->sizeY - 1)
			{
				e->image[x + y * e->sizeX].chr = char(0xBC);
			}

			//Sides
			//Bottom and Top sides
			else if (y == 0 || y == e->sizeY - 1)
			{
				e->image[x + y * e->sizeX].chr = char(0xCD);
			}
			//Left and Right sides
			else if (x == 0 || x == e->sizeX - 1)
			{
				e->image[x + y * e->sizeX].chr = char(0xBA);
			}

			//Text
			else if (y == (e->sizeY - 1) / 2 && x <= b->text.size())
			{
				e->image[x + y * e->sizeX].chr = b->text.at(x - 1);
			}

			//Empty space
			else
			{
				e->image[x + y * e->sizeX].chr = ' ';
			}

			e->image[x + y * e->sizeX].color = e->textColor;
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



ButtonData TextButton::makeButtonData(std::string text, void(*c)())
{
	ButtonData ret;
	ret.exists = true;
	ret.mouseOver = false;
	ret.text = text;
	ret.callback = c;
	return ret;
}
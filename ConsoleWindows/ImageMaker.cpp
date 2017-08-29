
#include "ImageMaker.h"

#include <vector>




void makeEmptyImage(ElementData *e)
{
	std::vector<CharData> image = std::vector<CharData>();
	image.resize(e->sizeX * e->sizeY);
	char ap = ' ';

	for (int y = 0; y < e->sizeY; ++y)
	{
		for (int x = 0; x < e->sizeX; ++x)
		{
			image[x + y * e->sizeX].chr = ' ';
			image[x + y * e->sizeX].color = e->textColor;
		}
	}
}

void makeTextImage(bool bordered, const char text[], int textSize, ElementData *e)
{
	e->image = std::vector<CharData>();
	e->image.resize(e->sizeX * e->sizeY);
	char ap = ' ';


	for (int y = 0; y < e->sizeY; ++y)
	{
		for (int x = 0; x < e->sizeX; ++x)
		{
			if (bordered)
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
				else if (y == (e->sizeY - 1) / 2 && x <= textSize)
				{
					e->image[x + y * e->sizeX].chr = text[x - 1];
				}

				//Empty space
				else
				{
					e->image[x + y * e->sizeX].chr = ' ';
				}
			}
			else
			{
				//Text
				if (y == (e->sizeY - 1) / 2 && x <= textSize)
				{
					e->image[x + y * e->sizeX].chr = text[x - 1];
				}

				//Empty space
				else
				{
					e->image[x + y * e->sizeX].chr = ' ';
				}
			}

			e->image[x + y * e->sizeX].color = e->textColor;
		}
	}
}

void makeButtonImage(ElementData *e, ButtonData* b)
{
	if (b->mouseOver)
	{
		e->textColor = 0x000B;
	}
	else
	{
		e->textColor = 0x000F;
	}
	makeTextImage(b->bordered, b->text.c_str(), b->text.size(), e);
}
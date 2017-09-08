
#include "ImageMaker.h"

#include <vector>
#include <string>




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

void makeTextImageMultiLine(bool bordered, const char text[], int textSize, ElementData *e)
{
	


	e->image = std::vector<CharData>();
	e->image.resize(e->sizeX * e->sizeY);
	char ap = ' ';
	int chridx = 0;
	int chrLine = 0;


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
				else if (chridx < textSize && y - 1 == chrLine
					&& y > 0 && y < e->sizeY - 1)
				{
					e->image[x + y * e->sizeX].chr = text[chridx];
					++chridx;
					while (chridx < textSize && text[chridx] == '\n')
					{
						++chrLine;
						++chridx;
					}
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
				if (chridx < textSize && y == chrLine)
				{
					e->image[x + y * e->sizeX].chr = text[chridx];
					++chridx;
					while (chridx < textSize && text[chridx] == '\n')
					{
						++chrLine;
						++chridx;
					}
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

void makeTextImageWithVars(bool bordered, std::string text, int textSize, ElementData *e, VarText* v)
{
	if (v->type == 0)
	{
		text = text.replace(text.find("%i"), 2, std::to_string(*(int*)v->var));
	}
	else if (v->type == 1)
	{
		text = text.replace(text.find("%f"), 2, std::to_string(*(float*)v->var));
	}
	else if (v->type == 2)
	{
		text = text.replace(text.find("%s"), 2, *(std::string*)v->var);
	}

	textSize = text.size();


	e->image = std::vector<CharData>();
	e->image.resize(e->sizeX * e->sizeY);
	char ap = ' ';
	int chridx = 0;
	int chrLine = 0;


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
				else if (chridx < textSize && y - 1 == chrLine
					&& y > 0 && y < e->sizeY - 1)
				{
					e->image[x + y * e->sizeX].chr = text[chridx];
					++chridx;
					while (chridx < textSize && text[chridx] == '\n')
					{
						++chrLine;
						++chridx;
					}
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
				if (chridx < textSize && y == chrLine)
				{
					e->image[x + y * e->sizeX].chr = text[chridx];
					++chridx;
					while (chridx < textSize && text[chridx] == '\n')
					{
						++chrLine;
						++chridx;
					}
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
		e->textColor = b->onColor;
	}
	else
	{
		e->textColor = b->offColor;
	}
	makeTextImage(b->bordered, b->text.c_str(), b->text.size(), e);
}
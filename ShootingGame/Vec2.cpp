#include "Vec2.h"


#include <math.h>


Vec2::Vec2()
{
}


Vec2::Vec2(int xx, int yy)
{
	x = xx;
	y = yy;
}


Vec2::~Vec2()
{
}




float Vec2::mag()
{
	/*if (x == 0 && y == 0)
	{
		return 0;
	}
	else
	{*/
		return sqrt(x * x + y * y);
	//}
}

void Vec2::unit()
{
	float m = mag();

	if (m == 0)
	{
		x = 0;
		y = 0;
	}
	else
	{
		x /= m;
		y /= m;
	}
}

float Vec2::dist(Vec2 v)
{
	return sqrt(pow(x - v.x, 2) + pow(y - v.y, 2));
}

float Vec2::dist(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

float Vec2::dist(float x2, float y2)
{
	return sqrt(pow(x - x2, 2) + pow(y - y2, 2));
}

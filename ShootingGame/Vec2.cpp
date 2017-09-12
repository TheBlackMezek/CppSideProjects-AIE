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
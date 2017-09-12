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
	return sqrt(x * x + y * y);
}

void Vec2::unit()
{
	float m = mag();

	x /= m;
	y /= m;
}
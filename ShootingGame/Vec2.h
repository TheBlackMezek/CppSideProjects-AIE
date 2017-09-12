#pragma once



#ifndef _VEC2_H_
#define _VEC2_H_






class Vec2
{
public:
	Vec2();
	Vec2(int xx, int yy);
	~Vec2();

	float x;
	float y;

	float mag();
	void unit();
};

#endif
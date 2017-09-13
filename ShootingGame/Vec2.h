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
	float dist(Vec2 v);
	float dist(float x1, float y1, float x2, float y2);
	float dist(float x2, float y2);
};

#endif
#pragma once


#ifndef _PERLIN_H_
#define _PERLIN_H_


#include <vector>
#include "Vecs.h"


class Perlin
{
public:
	Perlin();
	~Perlin();
	
	static void makeGrid(float grid[], int sizex, int sizey, int seed, int scale, int heightscale);
	static void makeGrid(std::vector<float>* grid, int sizex, int sizey, int seed, int scale, int heightscale);
	static float dot(vec2 v1, vec2 v2);
	static float lerp(vec2f v1, vec2f v2, float midx);
};

#endif
#pragma once


#ifndef _PERLIN_H_
#define _PERLIN_H_


class Perlin
{
public:
	Perlin();
	~Perlin();
	
	static void makeGrid(float grid[], const int sizex, const int sizey, const int seed, const int scale);
};

#endif
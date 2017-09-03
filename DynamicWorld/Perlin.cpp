#include "Perlin.h"


#include <iostream> //Only here for rand

#include "Vecs.h"




Perlin::Perlin()
{
}


Perlin::~Perlin()
{
}

void Perlin::makeGrid(float grid[], const int sizex, const int sizey, const int seed, const int scale)
{
	srand(seed);

	//Gradient vectors
	vec2 grads[sizex];
}
#include "Perlin.h"


#include <iostream> //Only here for rand
#include <vector>

#include "Vecs.h"




Perlin::Perlin()
{
}


Perlin::~Perlin()
{
}

void Perlin::makeGrid(float grid[], int sizex, int sizey, int seed, int scale, int heightscale)
{
	srand(seed);

	//Gradient vectors
	//vec2 grads[sizex]; //I would really rather use this than a vector
	int gradsizex = sizex / scale + 1; //21
	std::vector<vec2> grads(gradsizex * (sizey / scale + 1));
	for (int i = 0; i < grads.size(); ++i)
	{
		grads[i] = {rand() % (heightscale * 2) - heightscale, rand() % (heightscale * 2) - heightscale };
	}

	std::vector<vec2> dist(4);
	for (int y = 0; y < sizey; ++y)
	{
		if (y >= 44) {
			dist.size();
		}
		for (int x = 0; x < sizex; ++x)
		{
			//Make distance vectors: 0,0  1,0  0,1  1,1
			if (y >= 44 && x > 98) {
				int werlkw = 0;
			}
			dist[0] = { (x / scale) * scale - x,			(y / scale) * scale - y };
			if (y >= 44 && x > 98) {
				dist.size();
			}
			dist[1] = { (x / scale) * scale + scale - x,	(y / scale) * scale - y };
			if (y >= 44 && x > 98) {
				dist.size();
			}
			dist[2] = { (x / scale) * scale - x,			(y / scale) * scale + scale - y };
			if (y >= 44 && x > 98) {
				dist.size();
			}
			dist[3] = { (x / scale) * scale + scale - x,	(y / scale) * scale + scale - y };

			//Get dot products
			if (y >= 44 && x > 98) {
				dist.size();
			}
			float dot00 = dot(dist[0], grads[x / scale + (y / scale) * gradsizex]);
			if (y >= 44 && x > 98) {
				dist.size();
			}
			float dot10 = dot(dist[1], grads[x / scale + 1 + (y / scale) * gradsizex]);
			if (y >= 44 && x > 98) {
				dist.size();
			}
			float dot01 = dot(dist[2], grads[x / scale + (y / scale + 1) * gradsizex]);
			if (y >= 44 && x > 98) {
				dist.size();
			}
			float dot11 = dot(dist[3], grads[x / scale + 1 + (y / scale + 1) * gradsizex]); //46 at y=1 x=99
			if (y >= 44 && x > 98) {
				dist.size();
			}

			//Interpolate
			if (y >= 44 && x > 98) {
				dist.size();
			}
			float lerpy0 = lerp( { (float)((x / scale) * scale) , dot00 }, { (float)((x / scale) * scale + scale) , dot10 }, x);
			if (y >= 44 && x > 98) {
				dist.size();
			}
			float lerpy1 = lerp( { (float)((x / scale) * scale) , dot01 }, { (float)((x / scale) * scale + scale) , dot11 }, x);
			if (y >= 44 && x > 98) {
				dist.size();
			}
			grid[x + y * sizex] = lerp(	{ (float)((y / scale) * scale) , dot01 }, { (float)((y / scale) * scale + scale) , dot11 }, y);
			if (y >= 44 && x > 98) {
				dist.size();
			}
		}
	}
}

float Perlin::dot(vec2 v1, vec2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Perlin::lerp(vec2f v1, vec2f v2, float midx)
{
	return ( (midx - v1.x) * (v2.y - v1.y) ) / (v2.x - v1.x) + v1.y;
}
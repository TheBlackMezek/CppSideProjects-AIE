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

	float gradsizex = (float)sizex / (float)scale + 2.5f;
	std::vector<vec2> grads(ceil( gradsizex * (((float)sizey / (float)scale) + 2.5f) ));
	int gradSizeTotal = grads.size();

	for (int i = 0; i < grads.size(); ++i)
	{
		grads[i] = {rand() % (heightscale * 2) - heightscale, rand() % (heightscale * 2) - heightscale };
	}

	std::vector<vec2> dist(4);
	for (int y = 0; y < sizey; ++y)
	{
		for (int x = 0; x < sizex; ++x)
		{
			//Make distance vectors: 0,0  1,0  0,1  1,1
			dist[0] = { (x / scale) * scale - x,			(y / scale) * scale - y };
			dist[1] = { (x / scale) * scale + scale - x,	(y / scale) * scale - y };
			dist[2] = { (x / scale) * scale - x,			(y / scale) * scale + scale - y };
			dist[3] = { (x / scale) * scale + scale - x,	(y / scale) * scale + scale - y };

			//Get dot products
			float dot00 = dot(dist[0], grads[x / scale + (y / scale) * gradsizex]);
			float dot10 = dot(dist[1], grads[x / scale + 1 + (y / scale) * gradsizex]);
			float dot01 = dot(dist[2], grads[x / scale + (y / scale + 1) * gradsizex]);
			float dot11 = dot(dist[3], grads[x / scale + 1 + (y / scale + 1) * gradsizex]);

			//Interpolate
			float lerpy0 = lerp( { (float)((x / scale) * scale) , dot00 }, { (float)((x / scale) * scale + scale) , dot10 }, x);
			float lerpy1 = lerp( { (float)((x / scale) * scale) , dot01 }, { (float)((x / scale) * scale + scale) , dot11 }, x);
			grid[x + y * sizex] = lerp(	{ (float)((y / scale) * scale) , lerpy0 }, { (float)((y / scale) * scale + scale) , lerpy1 }, y);

		}
	}
}

void Perlin::makeGrid(std::vector<float>* grid, int sizex, int sizey, int seed, int scale, int heightscale)
{
	srand(seed);

	grid->clear();

	//Gradient vectors
	//vec2 grads[sizex]; //I would really rather use this than a vector

	float gradsizex = (float)sizex / (float)scale + 2.5f;
	std::vector<vec2> grads(ceil(gradsizex * (((float)sizey / (float)scale) + 2.5f)));
	int gradSizeTotal = grads.size();

	for (int i = 0; i < grads.size(); ++i)
	{
		grads[i] = { rand() % (heightscale * 2) - heightscale, rand() % (heightscale * 2) - heightscale };
	}

	std::vector<vec2f> dist(4);
	for (int y = 0; y < sizey; ++y)
	{
		for (int x = 0; x < sizex; ++x)
		{
			//Make distance vectors: 0,0  1,0  0,1  1,1
			/*dist[0] = { (x / scale) * scale - x,			(y / scale) * scale - y };
			dist[1] = { (x / scale) * scale + scale - x,	(y / scale) * scale - y };
			dist[2] = { (x / scale) * scale - x,			(y / scale) * scale + scale - y };
			dist[3] = { (x / scale) * scale + scale - x,	(y / scale) * scale + scale - y };*/
			dist[0] = { (x / scale) - ((float)x / (float)scale), (y / scale) - ((float)y / (float)scale) };
			dist[1] = { (x / scale) + 1 - ((float)x / (float)scale), (y / scale) - ((float)y / (float)scale) };
			dist[2] = { (x / scale) - ((float)x / (float)scale), (y / scale) + 1 - ((float)y / (float)scale) };
			dist[3] = { (x / scale) + 1 - ((float)x / (float)scale), (y / scale) + 1 - ((float)y / (float)scale) };

			//Get dot products
			float dot00 = dot(dist[0], grads[x / scale + (y / scale) * gradsizex]);
			float dot10 = dot(dist[1], grads[x / scale + 1 + (y / scale) * gradsizex]);
			float dot01 = dot(dist[2], grads[x / scale + (y / scale + 1) * gradsizex]);
			float dot11 = dot(dist[3], grads[x / scale + 1 + (y / scale + 1) * gradsizex]);

			//Interpolate
			float lerpy0 = lerp({ (float)((x / scale) * scale) , dot00 }, { (float)((x / scale) * scale + scale) , dot10 }, x);
			float lerpy1 = lerp({ (float)((x / scale) * scale) , dot01 }, { (float)((x / scale) * scale + scale) , dot11 }, x);
			grid->push_back(lerp({ (float)((y / scale) * scale) , lerpy0 }, { (float)((y / scale) * scale + scale) , lerpy1 }, y));
		}
	}
}

void Perlin::makeGridOctaves(std::vector<float>* grid, int sizex, int sizey, int seed, int scale, int heightscale, int octaves, float lacunarity, float persistence)
{
	srand(seed);

	makeGrid(grid, sizex, sizey, rand(), scale, heightscale);

	std::vector<float> octave(sizex * sizey);
	float scaleMult = 1 * lacunarity;
	float heightMult = 1 * persistence;
	for (int i = 1; i < octaves; ++i)
	{
		makeGrid(&octave, sizex, sizey, rand(), scale * scaleMult, heightscale * heightMult);

		for (int y = 0; y < sizey; ++y)
		{
			for (int x = 0; x < sizex; ++x)
			{
				(*grid)[x + y * sizex] = (*grid)[x + y * sizex] + octave[x + y * sizex];
			}
		}

		scaleMult *= lacunarity;
		heightMult *= persistence;
	}
	
}

float Perlin::dot(vec2 v1, vec2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Perlin::dot(vec2f v1, vec2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Perlin::lerp(vec2f v1, vec2f v2, float midx)
{
	return ( (midx - v1.x) * (v2.y - v1.y) ) / (v2.x - v1.x) + v1.y;
}
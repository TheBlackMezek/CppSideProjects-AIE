#include "Tribe.h"


#include <random>
#include <vector>


Tribe::Tribe()
{
	pop = 5;
	food = 0;
	foodMax = pop * 2;

	brain = NeuralNet();

	//Current inputs: posx, posy, food, pop, tiletype
	NeuronLayer input = NeuronLayer();
	for (int i = 0; i < 5; ++i)
	{
		Neuron n = Neuron();
		n.randWeights(5);
		input.neurons.push_back(n);
	}
	brain.layers.push_back(input);

	NeuronLayer mid = NeuronLayer();
	for (int i = 0; i < 5; ++i)
	{
		Neuron n = Neuron();
		n.randWeights(5);
		mid.neurons.push_back(n);
	}
	brain.layers.push_back(mid);

	NeuronLayer out = NeuronLayer();
	for (int i = 0; i < 5; ++i)
	{
		Neuron n = Neuron();
		n.randWeights(5);
		out.neurons.push_back(n);
	}
	brain.layers.push_back(out);
}


Tribe::~Tribe()
{
}


void Tribe::sim(Tile map[], int sizex, int sizey)
{
	//Movement
	int prevx = x;
	int prevy = y;

	std::vector<float> thot = brain.think(std::vector<float>{(float)x, (float)y, food, (float)pop,
		(float)map[x + y * sizex].type});

	//x += rand() % 3 - 1;
	//y += rand() % 3 - 1;
	if (thot[0] > 0)
	{
		++x;
	}
	else if (thot[0] < 0)
	{
		--x;
	}

	if (thot[1] > 0)
	{
		++y;
	}
	else if (thot[1] < 0)
	{
		--y;
	}




	if (x >= sizex)
	{
		x = sizex - 1;
	}
	else if (x < 0)
	{
		x = 0;
	}

	if (y >= sizey)
	{
		y = sizey - 1;
	}
	else if (y < 0)
	{
		y = 0;
	}

	if (map[x + y * sizex].type == 0)
	{
		x = prevx;
		y = prevy;
	}


	//Food
	for (int xx = x - 1; xx <= x + 1; ++xx)
	{
		if (xx >= 0 && xx < sizex)
		{
			for (int yy = y - 1; yy <= y + 1; ++yy)
			{
				if (yy >= 0 && yy < sizey)
				{
					float prevFood = food;
					food += map[xx + yy * sizex].food;
					if (food > foodMax)
					{
						food = foodMax;
					}
					map[xx + yy * sizex].food -= food - prevFood;
				}
			}
		}
	}
	

	food -= pop;
	//Starvation
	if (food < 0)
	{
		pop += (int)food;
		foodMax = pop * 2;
		food = 0;
	}
	else if (food >= 1)
	{
		++pop;
		foodMax = pop * 2;
	}
}
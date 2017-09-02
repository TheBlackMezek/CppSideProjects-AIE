#pragma once


#include <vector>


//Code somewhat copied from http://natureofcode.com/book/chapter-10-neural-networks/


class Neuron
{
public:
	std::vector<float> weights;

	void randWeights(int s);
	float activate(std::vector<float> inputs);
};


class NeuronLayer
{
public:
	std::vector<Neuron> neurons;
	
	std::vector<float> think(std::vector<float> inputs);
};


class NeuralNet
{
public:
	std::vector<NeuronLayer> layers;

	std::vector<float> think(std::vector<float> inputs);
};
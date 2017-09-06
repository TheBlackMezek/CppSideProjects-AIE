#pragma once


#ifndef _NEURALNET_H_
#define _NEURALNET_H_



#include <vector>


//Code somewhat copied from http://natureofcode.com/book/chapter-10-neural-networks/


class Neuron
{
public:
	std::vector<float> weights;

	void randWeights(int links);
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


class NetTrainer
{
public:
	float prevDist;
	float c; //Training constant
	NeuralNet* net;

	void train(float dist);
};


#endif
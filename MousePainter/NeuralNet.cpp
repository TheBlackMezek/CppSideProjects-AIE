
#include "NeuralNet.h"





void Neuron::randWeights(int s)
{
	weights.clear();
	for (int i = 0; i < s; ++i)
	{
		weights.push_back((rand() % 200 - 100) / 100.0f);
	}
}

float Neuron::activate(std::vector<float> inputs)
{
	float sum = 0;
	for (int i = 0; i < inputs.size(); ++i)
	{
		sum += inputs[i] * weights[i];
	}
	if (sum > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}


std::vector<float> NeuronLayer::think(std::vector<float> inputs)
{
	std::vector<float> ret = std::vector<float>(neurons.size());

	int s = neurons.size();
	for (int i = 0; i < neurons.size(); ++i)
	{
		ret[i] = neurons[i].activate(inputs);
	}

	return ret;
}

std::vector<float> NeuralNet::think(std::vector<float> inputs)
{
	//std::vector<float> ret = std::vector<float>(layers.back().neurons.size());
	std::vector<float> ret = layers[0].think(inputs);

	if (layers.size() > 1)
	{
		for (int i = 1; i < layers.size(); ++i)
		{
			ret = layers[i].think(ret);
		}
	}

	return ret;
}
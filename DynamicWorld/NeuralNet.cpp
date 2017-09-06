
#include "NeuralNet.h"





void Neuron::randWeights(int links)
{
	weights.clear();
	for (int i = 0; i < links; ++i)
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


void NetTrainer::train(float dist)
{
	if (dist >= prevDist)
	{
		for (int i = 0; i < net->layers.size(); ++i)
		{
			for (int q = 0; q < net->layers[i].neurons.size(); ++q)
			{
				for (int n = 0; n < net->layers[i].neurons[q].weights.size(); ++n)
				{
					net->layers[i].neurons[q].weights[n] += (rand() % 3 - 1) * dist * c;
					if (net->layers[i].neurons[q].weights[n] > 1)
					{
						net->layers[i].neurons[q].weights[n] = 1;
					}
					else if (net->layers[i].neurons[q].weights[n] < -1)
					{
						net->layers[i].neurons[q].weights[n] = -1;
					}
				}
			}
		}
	}
}
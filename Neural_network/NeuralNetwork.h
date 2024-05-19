#ifndef _NEURAL_NETWORK_H_
#define _NEURAL_NETWORK_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include "Matrix.h"
#include "Layer.h"
#include "utils.h"

class NeuralNetwork
{
public:
	// Constructor to create layers with zeroes and weights with random values
	NeuralNetwork(std::vector<int> _topology);
	void feedForward();
	void backpropagation();
	// Setter
	void setCurrentInput(std::vector<double> input);
	void setCurrentTarget(std::vector<double> target);
	void setErrors();
	// Print Layers and weights
	void printToConsole(bool showWeights);
	void printOutputToConsole();

	// Getter
	Matrix* getNeuronsFromLayer(int index) { return this->layers.at(index)->matrixifyVals(); };
	Matrix* getActivatedNeuronsFromLayer(int index) { return this->layers.at(index)->matrixifyActivatedVals(); };
	Matrix* getDerivedNeuronsFromLayer(int index) { return this->layers.at(index)->matrixifyDerivedVals(); };
	Matrix* getWeight(int index) { return this->weights.at(index); };
	double getTotalError() { return this->error; };
	std::vector<double> getErorrs() { return this->errors; };

private:
	int						topologySize; // Number of layers
	std::vector<int>		topology; // Amount of neurons in each layer
	std::vector<Layer*>		layers; // Layers with neurons
	std::vector<Matrix*>	weights; // Weights
	std::vector<Matrix*>	gradients; // Gradients
	std::vector<double>		input; // Input layer
	std::vector<double>		target; // Expected output
	double					error; // Sum of errors in vector errors
	std::vector<double>		errors; // Set of errors for each neuron in output
	std::vector<double>		historicalErrors;
};

#endif
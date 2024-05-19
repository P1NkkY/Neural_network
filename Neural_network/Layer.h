#ifndef _LAYER_H_
#define _LAYER_H_

#include <iostream>
#include <vector>
#include "Neuron.h"
#include "Matrix.h"

class Layer
{
public:
	// Constructor with zero values
	Layer(int _size);
	// Setter
	void setVal(int idx, double val);
	void setNeurons(std::vector<Neuron*> neurons) { this->neurons = neurons; };
	// Getter
	std::vector<Neuron*> getNeurons() { return this->neurons; };
	// Vector to matrix
	Matrix* matrixifyVals();
	Matrix* matrixifyActivatedVals();
	Matrix* matrixifyDerivedVals();
	// Print layer
	void printLayer();

private:
	int size; // Length of the layer
	std::vector<Neuron*> neurons; // Layer of neurons
};

#endif

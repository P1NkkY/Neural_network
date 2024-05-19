#include "Layer.h"

Layer::Layer(int _size) : size(_size)
{
	for (int iter = 0; iter < size; iter++) {
		Neuron* n = new Neuron(0.0);
		this->neurons.push_back(n);
	}
}

void Layer::setVal(int idx, double val)
{
	this->neurons.at(idx)->setVal(val);
}

Matrix* Layer::matrixifyVals()
{
	Matrix* m = new Matrix(1, this->neurons.size(), false);
	for (int iter = 0; iter < neurons.size(); iter++) {
		m->setVal(0, iter, this->neurons.at(iter)->getVal());
	}

	return m;
}

Matrix* Layer::matrixifyActivatedVals()
{
	Matrix* m = new Matrix(1, this->neurons.size(), false);
	for (int iter = 0; iter < neurons.size(); iter++) {
		m->setVal(0, iter, this->neurons.at(iter)->getActivatedVal());
	}

	return m;
}

Matrix* Layer::matrixifyDerivedVals()
{
	Matrix* m = new Matrix(1, this->neurons.size(), false);
	for (int iter = 0; iter < neurons.size(); iter++) {
		m->setVal(0, iter, this->neurons.at(iter)->getDerivedVal());
	}

	return m;
}

void Layer::printLayer()
{
	for (int iter = 0; iter < size; iter++) {
		std::cout << neurons.at(iter)->getVal() << std::endl;
	}
}
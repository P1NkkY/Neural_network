#include "Neuron.h"

Neuron::Neuron(double val)
{
	this->val = val;
	activate();
	derive();
}

void Neuron::activate()
{
	this->activatedVal = this->val / (1.0 + std::abs(this->val));
}

void Neuron::derive()
{
	this->derivedVal = this->activatedVal * (1.0 - this->activatedVal);
}

void Neuron::setVal(double val)
{
	this->val = val;
	activate();
	derive();
}

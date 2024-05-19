#ifndef _NEURON_H_
#define _NEURON_H_

#include <iostream>

class Neuron
{
public:
	// Constructor
	Neuron(double val);
	// Sigmoid function
	void activate();
	// Derivative for Sigmoid function
	void derive(); 
	// Setter
	void setVal(double val);
	// Getter
	double getVal() const { return this->val; };
	double getActivatedVal() const { return this->activatedVal; };
	double getDerivedVal() const { return this->derivedVal; };

private:
	double val; // value of the Neuron
	double activatedVal; // activated value of the Neuron
	double derivedVal; // derivative of the activated value
};


#endif // !NEURON_H_



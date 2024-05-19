#include <iostream>
#include "NeuralNetwork.h"

int main()
{
	std::vector<double> input = { 1, 0, 1 };

	NeuralNetwork* network = new NeuralNetwork({ 3, 10, 3 });
	network->setCurrentInput(input);
	network->setCurrentTarget(input);
	
	// training process
	for (int iter = 0; iter < 1000; iter++) {
		network->feedForward();
		network->setErrors();
		// network->printToConsole(true);
		//std::cout << std::endl;
		std::cout << "ERROR: " << network->getTotalError() << std::endl;
		network->backpropagation();
	}
	network->printOutputToConsole();

	//Matrix* m = new Matrix(3, 4, true);
	//m->printMatrix();
	//std::cout << "------" << std::endl;
	//Matrix* mT = m->transpose();
	//mT->printMatrix();
	// Layer* l = new Layer(5);
	// l->printNeurons();
	// Neuron* n = new Neuron(1.5);
	// std::cout << n->getVal() << " " << n->getActivatedVal() << "  " << n->getDerivedVal() << std::endl;

	return 1;
}
#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(std::vector<int> _topology) : topology(_topology), topologySize(_topology.size())
{
	// Create layers
	for (int iter = 0; iter < topologySize; iter++) {
		Layer* l = new Layer(topology[iter]);
		this->layers.push_back(l);
	}
	// Create weights
	for (int iter = 0; iter < topologySize - 1; iter++) {
		Matrix* m = new Matrix(topology[iter], topology[iter + 1], true);
		this->weights.push_back(m);
	}
}

void NeuralNetwork::feedForward()
{
	for (int layer = 0; layer < this->layers.size() - 1; layer++) {
		Matrix* a = this->getNeuronsFromLayer(layer);
		if (layer != 0) {
			a = this->getActivatedNeuronsFromLayer(layer);
		}

		Matrix* b = this->getWeight(layer);
		Matrix* c = (new utils::MultiplyMatrix(a, b))->execute();

		for (int c_index = 0; c_index < c->getNumCols(); c_index++) {
			this->layers.at(layer + 1)->setVal(c_index, c->getVal(0, c_index));
		}
	}
}

void NeuralNetwork::backpropagation()
{
	std::vector<Matrix*> newWeights;
	Matrix* gradient;

	// output to hidden layers
	int outputLayerIndex = this->layers.size() - 1;
	Matrix* derivedValuesYtoZ = this->layers.at(outputLayerIndex)->matrixifyDerivedVals();
	Matrix* gradientsYtoZ = new Matrix(1, this->layers.at(outputLayerIndex)->getNeurons().size(), false);
	for (int iter = 0; iter < this->errors.size(); iter++) {
		double d = derivedValuesYtoZ->getVal(0, iter);
		double er = this->errors.at(iter);
		double gr = d * er;
		gradientsYtoZ->setVal(0, iter, gr);
	}
	// Calculate delta for hidden layers
	int lastHiddenLayerIndex = outputLayerIndex - 1;
	Layer* lastHiddenLayer = this->layers.at(lastHiddenLayerIndex);
	Matrix* weightsOutputToHidden = this->weights.at(lastHiddenLayerIndex);
	Matrix* deltaOtputToHidden = (new utils::MultiplyMatrix(gradientsYtoZ->transpose(), lastHiddenLayer->matrixifyActivatedVals()))->execute()->transpose();
	
	Matrix* newWeightsOutputToHidden = new Matrix(deltaOtputToHidden->getNumRows(), deltaOtputToHidden->getNumCols(), false);
	
	for (int iter = 0; iter < deltaOtputToHidden->getNumRows(); iter++) {
		for (int jter = 0; jter < deltaOtputToHidden->getNumCols(); jter++) {
			double originalWeight = weightsOutputToHidden->getVal(iter, jter);
			double deltaWeight = deltaOtputToHidden->getVal(iter, jter);
			newWeightsOutputToHidden->setVal(iter, jter, originalWeight - deltaWeight);
		}
	}

	newWeights.push_back(newWeightsOutputToHidden);
	gradient = new Matrix(gradientsYtoZ->getNumRows(), gradientsYtoZ->getNumCols(), false);
	for (int iter = 0; iter < gradient->getNumRows(); iter++) {
		for (int jter = 0; jter < gradient->getNumCols(); jter++) {
			gradient->setVal(iter, jter, gradientsYtoZ->getVal(iter, jter));
		}
	}

	for (int layer = outputLayerIndex - 1; layer > 0; layer--) {
		Layer* l = this->layers.at(layer);
		Matrix* activatedHidden = l->matrixifyActivatedVals();
		Matrix* derivedHidden = l->matrixifyDerivedVals();
		Matrix* derivedGradients = new Matrix(1, l->getNeurons().size(), false);

		Matrix* weightMatrix = this->weights.at(layer);
		Matrix* originalWeight = this->weights.at(layer - 1);
		for (int r = 0; r < weightMatrix->getNumRows(); r++) {
			double sum = 0;
			for (int c = 0; c < weightMatrix->getNumCols(); c++) {
				double p = gradient->getVal(0, c)* weightMatrix->getVal(r, c);
				sum += p;
			}
			double g = sum * activatedHidden->getVal(0, r);
			derivedGradients->setVal(0, r, g);
		}

		Matrix* leftNeurons = (layer - 1) == 0 ? this->layers.at(0)->matrixifyActivatedVals() : this->layers.at(layer - 1)->matrixifyActivatedVals();

		Matrix* deltaWeights = (new utils::MultiplyMatrix(derivedGradients->transpose(), leftNeurons))->execute()->transpose();

		Matrix* newWeightsHidden = new Matrix(deltaWeights->getNumRows(), deltaWeights->getNumCols(), false);
		for (int iter = 0; iter < newWeightsHidden->getNumRows(); iter++) {
			for (int jter = 0; jter < newWeightsHidden->getNumCols(); jter++) {
				double w = originalWeight->getVal(iter, jter);
				double d = deltaWeights->getVal(iter, jter);
				double n = w - d;
				newWeightsHidden->setVal(iter, jter, n);
			}
		}
		newWeights.push_back(newWeightsHidden);

		gradient = new Matrix(derivedGradients->getNumRows(), derivedGradients->getNumCols(), false);
		for (int iter = 0; iter < derivedGradients->getNumRows(); iter++) {
			for (int jter = 0; jter < derivedGradients->getNumCols(); jter++) {
				gradient->setVal(iter, jter, derivedGradients->getVal(iter, jter));
			}
		}
	}
	
	std::reverse(newWeights.begin(), newWeights.end());
	this->weights = newWeights;
}

void NeuralNetwork::setCurrentInput(std::vector<double> input)
{
	this->input = input;
	for (int iter = 0; iter < input.size(); iter++) {
		this->layers[0]->setVal(iter, input[iter]);
	}
}

void NeuralNetwork::setCurrentTarget(std::vector<double> target)
{
	this->target = target; 
	errors.resize(target.size());
}

void NeuralNetwork::setErrors()
{
	if (this->target.size() == 0) {
		std::cerr << "No target for this neural network" << std::endl;
		assert(false);
	}
	if (this->target.size() != this->layers.at(this->layers.size() - 1)->getNeurons().size()) {
		std::cerr << "Target size is not the same as output layer size" << std::endl;
		assert(false);
	}

	this->error = 0.0;
	int outputLayerSize = this->layers.size() - 1;
	std::vector<Neuron*> outputNeurons = this->layers.at(outputLayerSize)->getNeurons();
	for (int iter = 0; iter < outputNeurons.size(); iter++) {
		double tempErr = (outputNeurons.at(iter)->getActivatedVal() - this->target.at(iter));
		this->errors.at(iter) = tempErr;
		// this->error += tempErr;
		this->error += std::pow(tempErr, 2); // quadratic cost function
	}
	this->error = 0.5 * this->error;  // quadratic cost function

	this->historicalErrors.push_back(this->error);
}

void NeuralNetwork::printToConsole(bool showWeights)
{
	for (int layer = 0; layer < this->layers.size(); layer++) {
		std::cout << "LAYER: " << layer << std::endl;
		if (layer == 0) {
			Matrix* m = this->layers[layer]->matrixifyVals();
			m->printMatrix();
		}
		else {
			Matrix* m = this->layers[layer]->matrixifyActivatedVals();
			m->printMatrix();
		}
	}

	if (!showWeights)
		return;

	std::cout << std::endl;
	for (int layer = 0; layer < this->weights.size(); layer++) {
		std::cout << "WEIGHT: " << layer << std::endl;
		for (int iter = 0; iter < this->weights.at(layer)->getNumRows(); iter++) {
			for (int jter = 0; jter < this->weights.at(layer)->getNumCols(); jter++) {
				std::cout << this->weights.at(layer)->getVal(iter, jter) << " ";
			}
			std::cout << std::endl;
		}
	}
}

void NeuralNetwork::printOutputToConsole()
{
	Matrix* outputValues = this->layers.at(this->layers.size() - 1)->matrixifyActivatedVals();
	for (int iter = 0; iter < outputValues->getNumCols(); iter++) {
		std::cout << outputValues->getVal(0, iter) << " ";
	}
	std::cout << std::endl;
}

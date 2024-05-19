#include "Matrix.h"

Matrix::Matrix(int _numRows, int _numCols, bool isRandom) : 
	numRows(_numRows), numCols(_numCols)
{
	for (int iter = 0; iter < numRows; iter++) {
		std::vector<double> colValues;
		for (int jter = 0; jter < numCols; jter++) {
			double r = 0.0;
			if (isRandom) {
				r = this->generateRandomVal();
			}
			colValues.push_back(r);
		}
		matrix.push_back(colValues);
	}
}

double Matrix::generateRandomVal()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	return dis(gen);
}

Matrix* Matrix::transpose()
{
	Matrix* mT = new Matrix(numCols, numRows, false);
	for (int iter = 0; iter < numRows; iter++) {
		for (int jter = 0; jter < numCols; jter++) {
			mT->setVal(jter, iter, this->getVal(iter, jter));
		}
	}

	return mT;
}

void Matrix::printMatrix()
{
	for (int iter = 0; iter < numRows; iter++) {
		for (int jter = 0; jter < numCols; jter++) {
			std::cout << matrix.at(iter).at(jter) << " ";
		}
		std::cout << std::endl;
	}
}
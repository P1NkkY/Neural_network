#include "utils.h"

utils::MultiplyMatrix::MultiplyMatrix(Matrix* _a, Matrix* _b) : a(_a), b(_b)
{
	if (a->getNumCols() != b->getNumRows()) {
		std::cerr << "a_rows: " << a->getNumRows() << " != b_cols: " << b->getNumCols() << std::endl;
		assert(false);
	}
	this->res = new Matrix(a->getNumRows(), b->getNumCols(), false);
}

Matrix* utils::MultiplyMatrix::execute()
{
	for (int iter = 0; iter < a->getNumRows(); iter++) {
		for (int jter = 0; jter < b->getNumCols(); jter++) {
			for (int kter = 0; kter < b->getNumRows(); kter++) {
				double p = this->a->getVal(iter, kter) * this->b->getVal(kter, jter);
				double newVal = this->res->getVal(iter, jter) + p;
				this->res->setVal(iter, jter, newVal);
			}
		}
	}

	return this->res;
}

utils::MatrixToVector::MatrixToVector(Matrix* a)
{
	this->a = a;
}

std::vector<double> utils::MatrixToVector::execute()
{
	std::vector<double> result;
	
	for (int iter = 0; iter < a->getNumRows(); iter++) {
		for (int jter = 0; jter < a->getNumCols(); jter++) {
			result.push_back(a->getVal(iter, jter));
		}
	}

	return result;
}

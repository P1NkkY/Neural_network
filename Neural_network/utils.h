#ifndef _MULTIPLY_MATRIX_H_
#define _MULTIPLY_MATRIX_H_

#include <iostream>
#include <vector>
#include <assert.h>
#include "Matrix.h"

namespace utils
{
	class MultiplyMatrix
	{
	public:
		MultiplyMatrix(Matrix* _a, Matrix* _b);
		Matrix* execute();

	private:
		Matrix* a;
		Matrix* b;
		Matrix* res;
	};

	class MatrixToVector
	{
	public:
		MatrixToVector(Matrix* a);

		std::vector<double> execute();
	private:
		Matrix* a;
	};
}

#endif
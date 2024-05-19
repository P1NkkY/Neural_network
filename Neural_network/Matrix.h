#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <vector>
#include <random>

class Matrix
{
public:
	// Contructor to create matrix with values from 0 to 1
	Matrix(int _numRows, int _numCols, bool isRandom);
	// Generate random value from 0 to 1
	double generateRandomVal();
	// Setter
	void setVal(int idxRow, int idxCol, double val) { this->matrix.at(idxRow).at(idxCol) = val; };
	// Getter
	double getVal(int idxRow, int idxCol) { return this->matrix.at(idxRow).at(idxCol); };
	int getNumRows() const { return this->numRows; };
	int getNumCols() const { return this->numCols; };
	// Transpose the matrix
	Matrix* transpose();
	// Prints the matrix
	void printMatrix();

private:
	int numRows; // number of rows
	int numCols; // number of columns
	std::vector<std::vector<double>> matrix; // current matrix
};

#endif
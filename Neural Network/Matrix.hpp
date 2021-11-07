#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <vector>
#include <random>
using namespace std;

class Matrix
{
public:
	// Constructor
	Matrix(int numRows, int numCols, bool isRandom);

	Matrix* transpose();

	double generateRandomNumber();

	void printToConsole();

	// Setters
	void setValue(int row, int col, double val) { this->values.at(row).at(col) = val; };

	// Getters
	double getValue(int row, int col) { return this->values.at(row).at(col); };
	int getNumRows() { return this->numRows; };
	int getNumCols() { return this->numCols; };

private:
	int numRows;
	int numCols;
	vector<vector<double>> values;
};

#endif
#include "Matrix.hpp"

Matrix::Matrix(int numRows, int numCols, bool isRandom)
{
	this->numRows = numRows;
	this->numCols = numCols;

	for (int i = 0; i < numRows; i++)
	{
		vector<double> colValues;

		for (int j = 0; j < numCols; j++)
		{
			double r = 0.00;
			if (isRandom)
			{
				r = this->generateRandomNumber();
			}

			colValues.push_back(r);
		}

		this->values.push_back(colValues);
	}
}

Matrix* Matrix::transpose()
{
	Matrix* m = new Matrix(this->numCols, this->numRows, false);
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			m->setValue(j, i, this->getValue(i, j));
		}
	}
	return m;
}

double Matrix::generateRandomNumber()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);

	return dis(gen);
}

void Matrix::printToConsole()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			cout << this->values.at(i).at(j) << "\t\t";
		}
		cout << endl;
	}
}

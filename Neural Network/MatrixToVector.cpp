#include "MatrixToVector.hpp"

utils::MatrixToVector::MatrixToVector(Matrix* a)
{
	this->a = a;
}

vector<double> utils::MatrixToVector::execute()
{
	vector<double> result;

	for (int row = 0; row < a->getNumRows(); row++)
	{
		for (int col = 0; col < a->getNumCols(); col++)
		{
			result.push_back(a->getValue(row, col));
		}
	}
	return result;
}

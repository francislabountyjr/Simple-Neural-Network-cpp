#include "MultiplyMatrix.hpp"

utils::MultiplyMatrix::MultiplyMatrix(Matrix* a, Matrix* b)
{
	this->a = a;
	this->b = b;

	if (a->getNumCols() != b->getNumRows())
	{
		cerr << "A_rows: " << a->getNumRows() << " != B_cols: " << b->getNumCols() << endl;
		cerr << "A_cols: " << a->getNumCols() << " != B_rows: " << b->getNumRows() << endl;
		assert(false);
	}

	this->c = new Matrix(a->getNumRows(), b->getNumCols(), false);
}

Matrix* utils::MultiplyMatrix::execute()
{
	for (int i = 0; i < a->getNumRows(); i++)
	{
		for (int j = 0; j < b->getNumCols(); j++)
		{
			for (int k = 0; k < b->getNumRows(); k++)
			{
				double p = this->a->getValue(i, k) * this->b->getValue(k, j);
				double newVal = this->c->getValue(i, j) + p;
				this->c->setValue(i, j, newVal);
			}
		}
	}
	return this->c;
}

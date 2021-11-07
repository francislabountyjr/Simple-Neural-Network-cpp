#ifndef _MATRIX_TO_VECTOR_HPP_
#define _MATRIX_TO_VECTOR_HPP_

#include <iostream>
#include <vector>
#include <assert.h>
#include "Matrix.hpp"
using namespace std;

namespace utils
{
	class MatrixToVector
	{
	public:
		// Constructor
		MatrixToVector(Matrix* a);

		vector<double> execute();
	private:
		Matrix* a;
	};
}

#endif
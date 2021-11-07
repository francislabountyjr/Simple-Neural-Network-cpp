#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <iostream>
#include <vector>
#include "Neuron.hpp"
#include "Matrix.hpp"
using namespace std;

class Layer
{
public:
	// Constructor
	Layer(int size);

	Matrix* matrixifyVals();
	Matrix* matrixifyActivatedVals();
	Matrix* matrixifyDerivedVals();

	// Getter
	vector<Neuron*> getNeurons() { return this->neurons; };

	// Setter
	void setNeuron(int i, double v);

private:
	int size;
	vector<Neuron*> neurons;
};

#endif
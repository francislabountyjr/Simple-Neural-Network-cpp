#include "Layer.hpp"

Layer::Layer(int size)
{
	this->size = size;
	for (int i = 0; i < size; i++)
	{
		Neuron* n = new Neuron(0.00);
		this->neurons.push_back(n);
	}
}

Matrix* Layer::matrixifyVals()
{
	Matrix* m = new Matrix(1, this->neurons.size(), false);
	for (int i = 0; i < this->neurons.size(); i++)
	{
		m->setValue(0, i, this->neurons.at(i)->getVal());
	}
	return m;
}

Matrix* Layer::matrixifyActivatedVals()
{
	Matrix* m = new Matrix(1, this->neurons.size(), false);
	for (int i = 0; i < this->neurons.size(); i++)
	{
		m->setValue(0, i, this->neurons.at(i)->getActivationVal());
	}
	return m;
}

Matrix* Layer::matrixifyDerivedVals()
{
	Matrix* m = new Matrix(1, this->neurons.size(), false);
	for (int i = 0; i < this->neurons.size(); i++)
	{
		m->setValue(0, i, this->neurons.at(i)->getDerivedVal());
	}
	return m;
}

void Layer::setNeuron(int i, double v)
{
	this->neurons.at(i)->setVal(v);
}

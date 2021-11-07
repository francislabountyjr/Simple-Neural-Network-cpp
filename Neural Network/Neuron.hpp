#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include <iostream>
#include <math.h>
using namespace std;

class Neuron
{
public:
	// Constructor
	Neuron(double val);

	// Fast Sigmoid Function
	// f(x) = x / (1 + |x|)
	void activate();

	// Derivative of Fast Sigmoid Function
	// f'(x) = f(x) * (1 - f(x))
	void derive();

	// Getters
	double getVal() { return this->val; };
	double getActivationVal() { return this->activatedVal; };
	double getDerivedVal() { return this->derivedVal; };

	// Setters
	void setVal(double val);

private:
	double val;
	double activatedVal;
	double derivedVal;
};

#endif
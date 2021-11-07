#include <iostream>
#include <math.h>
#include <algorithm>
#include "Neuron.hpp"
#include "Matrix.hpp"
#include "NeuralNetwork.hpp"
#include "MultiplyMatrix.hpp"
using namespace std;

int main()
{
	vector<int> topology = { 3, 20, 3 };
	vector<double> input = { 0.5, 0.2, 0.3 };
	vector<double> target = input;
	for (double& val : target)
	{
		val = (val * val) + .8 * val;
	}
	int epochs = 100;
	int numReports = 2;

	NeuralNetwork* nn = new NeuralNetwork(topology);
	nn->setCurrentInput(input);
	nn->setCurrentTarget(target);
	nn->printToConsole();

	// training process
	for (int i = 1; i <= epochs; i++)
	{
		nn->feedForward();
		nn->backPropagation();
		if ((i) % (epochs/numReports) == 0)
		{
			cout << "Epoch: " << (i) << endl;
			cout << "Total Error: " << nn->getTotalError() << endl;
			cout << "-------------------------" << endl;
			cout << "OUTPUT: ";
			nn->printOutputToConsole();

			cout << "TARGET: ";
			nn->printTargetToConsole();
			cout << "-------------------------" << endl;
			cout << endl;
		}
	}

	nn->printHistoricalErrors();

	return 0;
}
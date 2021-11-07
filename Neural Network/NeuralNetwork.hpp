#ifndef _NEURAL_NETWORK_HPP_
#define _NEURAL_NETWORK_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include "Matrix.hpp"
#include "Layer.hpp"
#include "MultiplyMatrix.hpp"
using namespace std;

class NeuralNetwork
{
public:
	// Constructor
	NeuralNetwork(vector<int> topology);
	
	void setCurrentInput(vector<double> input);

	void setCurrentTarget(vector<double> target);

	void feedForward();

	void backPropagation();

	void setErrors();

	void printToConsole();
	void printInputToConsole();
	void printOutputToConsole();
	void printTargetToConsole();
	void printHistoricalErrors();

	// Getters
	Matrix* getNeuronMatrix(int index) { return this->layers.at(index)->matrixifyVals(); };
	Matrix* getActivatedNeuronMatrix(int index) { return this->layers.at(index)->matrixifyActivatedVals(); };
	Matrix* getDerivedNeuronMatrix(int index) { return this->layers.at(index)->matrixifyDerivedVals(); };
	Matrix* getWeightMatrix(int index) { return this->weightMatrices.at(index); };

	double getTotalError() { return this->error; };
	vector<double> getErrors() { return this->errors; };

	// Setters
	void setNeuronValue(int indexLayer, int indexNeuron, double val) { this->layers.at(indexLayer)->setNeuron(indexNeuron, val); };

private:
	vector<int> topology;
	int topologySize;
	vector<Layer*> layers;
	vector<Matrix*> weightMatrices;
	vector<Matrix*> gradientMatrices;
	vector<double> input;
	vector<double> target;
	double error;
	vector<double> errors;
	vector<double> historicalErrors;
};
#endif
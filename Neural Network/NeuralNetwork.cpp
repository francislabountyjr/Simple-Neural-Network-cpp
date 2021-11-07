#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(vector<int> topology)
{
	this->topology = topology;
	this->topologySize = topology.size();
	for (int i = 0; i < topologySize; i++)
	{
		Layer* l = new Layer(topology.at(i));
		this->layers.push_back(l);
	}

	for (int i = 0; i < topologySize - 1; i++)
	{
		Matrix* m = new Matrix(topology.at(i), topology.at(i + 1), true);
		this->weightMatrices.push_back(m);
	}

	for (int i = 0; i < topology.at(topologySize - 1); i++)
	{
		errors.push_back(0.00);
	}
}

void NeuralNetwork::setCurrentInput(vector<double> input)
{
	this->input = input;

	for (int i = 0; i < input.size(); i++)
	{
		this->layers.at(0)->setNeuron(i, input.at(i));
	}
}

void NeuralNetwork::setCurrentTarget(vector<double> target)
{
	this->target = target;

	for (int i = 0; i < target.size(); i++)
	{
		this->layers.at(0)->setNeuron(i, target.at(i));
	}
}

void NeuralNetwork::feedForward()
{
	for (int i = 0; i < (this->layers.size() - 1); i++)
	{
		Matrix* a = this->getNeuronMatrix(i);

		if (i != 0)
		{
			a = this->getActivatedNeuronMatrix(i);
		}

		Matrix* b = this->getWeightMatrix(i);
		Matrix* c = (new utils::MultiplyMatrix(a, b))->execute();

		for (int c_index = 0; c_index < c->getNumCols(); c_index++)
		{
			this->setNeuronValue(i + 1, c_index, c->getValue(0, c_index));
		}
	}
}

void NeuralNetwork::backPropagation()
{
	this->setErrors();
	vector<Matrix*> newWeights;
	Matrix* gradient;

	// output layer to hidden layer
	int outputLayerIndex = this->layers.size() - 1;
	Matrix* derivedValuesYToZ = this->layers.at(outputLayerIndex)->matrixifyDerivedVals();
	Matrix* gradientsYToZ = new Matrix(1, this->layers.at(outputLayerIndex)->getNeurons().size(), false);
	for (int i = 0; i < this->errors.size(); i++)
	{
		double d = derivedValuesYToZ->getValue(0, i);
		double e = this->errors.at(i);
		double g = d * e;
		gradientsYToZ->setValue(0, i, g);
	}

	int lastHiddenLayerIndex = outputLayerIndex - 1;
	Layer* lastHiddenLayer = this->layers.at(lastHiddenLayerIndex);
	Matrix* weightsOutputToHidden = this->weightMatrices.at(outputLayerIndex - 1);
	Matrix* deltaOutputToHidden = (new utils::MultiplyMatrix(gradientsYToZ->transpose(), lastHiddenLayer->matrixifyActivatedVals()))->execute()->transpose();
	Matrix* newWeightsOutputToHidden = new Matrix(deltaOutputToHidden->getNumRows(), deltaOutputToHidden->getNumCols(), false);

	for (int row = 0; row < deltaOutputToHidden->getNumRows(); row++)
	{
		for (int col = 0; col < deltaOutputToHidden->getNumCols(); col++)
		{
			double originalWeight = weightsOutputToHidden->getValue(row, col);
			double deltaWeight = deltaOutputToHidden->getValue(row, col);
			newWeightsOutputToHidden->setValue(row, col, originalWeight - deltaWeight);
		}
	}

	newWeights.push_back(newWeightsOutputToHidden);

	gradient = new Matrix(gradientsYToZ->getNumRows(), gradientsYToZ->getNumCols(), false);
	for (int row = 0; row < gradientsYToZ->getNumRows(); row++)
	{
		for (int col = 0; col < gradientsYToZ->getNumCols(); col++)
		{
			gradient->setValue(row, col, gradientsYToZ->getValue(row, col));
		}
	}


	// Moving from last hidden layer to input layer
	for (int i = outputLayerIndex - 1; i > 0; i--)
	{
		Layer* l = this->layers.at(i);
		Matrix* derivedHidden = l->matrixifyDerivedVals();
		Matrix* activatedHidden = l->matrixifyActivatedVals();
		Matrix* derivedGradients = new Matrix(1, l->getNeurons().size(), false);
		Matrix* weightMatrix = this->weightMatrices.at(i);
		Matrix* originalWeightMatrix = this->weightMatrices.at(i - 1);
		
		for (int row = 0; row < weightMatrix->getNumRows(); row++)
		{
			double sum = 0.0;
			for (int col = 0; col < weightMatrix->getNumCols(); col++)
			{
				double p = gradient->getValue(0, col) * weightMatrix->getValue(row, col);
				sum += p;
			}
			//double g = sum * activatedHidden->getValue(0, row);
			double g = sum * derivedHidden->getValue(0, row);
			derivedGradients->setValue(0, row, g);
		}

		Matrix* leftNeurons = (i - 1) == 0 ? this->layers.at(0)->matrixifyVals() : this->layers.at(i - 1)->matrixifyActivatedVals();
		Matrix* deltaWeights = (new utils::MultiplyMatrix(derivedGradients->transpose(), leftNeurons))->execute()->transpose();
		Matrix* newWeightsHidden = new Matrix(deltaWeights->getNumRows(), deltaWeights->getNumCols(), false);

		for (int row = 0; row < newWeightsHidden->getNumRows(); row++)
		{
			for (int col = 0; col < newWeightsHidden->getNumCols(); col++)
			{
				double w = originalWeightMatrix->getValue(row, col);
				double d = deltaWeights->getValue(row, col);
				double n = w - d;
				newWeightsHidden->setValue(row, col, n);
			}
		}

		gradient = new Matrix(derivedGradients->getNumRows(), derivedGradients->getNumCols(), false);
		for (int row = 0; row < derivedGradients->getNumRows(); row++)
		{
			for (int col = 0; col < derivedGradients->getNumCols(); col++)
			{
				gradient->setValue(row, col, derivedGradients->getValue(row, col));
			}
		}

		newWeights.push_back(newWeightsHidden);

		reverse(newWeights.begin(), newWeights.end());
		this->weightMatrices = newWeights;
	}
}

void NeuralNetwork::setErrors()
{
	if (this->target.size() == 0)
	{
		cerr << "No target for this neural network" << endl;
		assert(false);
	}

	if (this->target.size() != this->layers.at(this->layers.size() - 1)->getNeurons().size())
	{
		cerr << "Target size is not the same as the output layer size: " << this->layers.at(this->layers.size() - 1)->getNeurons().size() << endl;
		assert(false);
	}

	this->error = 0.00;
	int outputLayerIndex = this->layers.size() - 1;
	vector<Neuron*> outputNeurons = this->layers.at(outputLayerIndex)->getNeurons();
	for (int i = 0; i < target.size(); i++)
	{
		// Cost Function
		double tempErr = outputNeurons.at(i)->getActivationVal() - target.at(i);
		errors.at(i) = tempErr;
		this->error += pow(tempErr, 2);
	}

	this->error = 0.5 * this->error;

	historicalErrors.push_back(this->error);
}

void NeuralNetwork::printToConsole()
{
	for (int i = 0; i < this->layers.size(); i++)
	{
		cout << "LAYER: " << i << endl;
		if (i == 0)
		{
			Matrix* m = this->layers.at(i)->matrixifyVals();
			m->printToConsole();
		}
		else
		{
			Matrix* m = this->layers.at(i)->matrixifyActivatedVals();
			m->printToConsole();
		}
		cout << "---------------------" << endl;
		if (i != this->layers.size() - 1)
		{
			cout << "Weight Matrix: " << i << endl;
			this->getWeightMatrix(i)->printToConsole();
		}
		cout << "---------------------" << endl;
	}
}

void NeuralNetwork::printInputToConsole()
{
	for (int i = 0; i < this->input.size(); i++)
	{
		cout << this->input.at(i) << "\t";
	}
	cout << endl;
}

void NeuralNetwork::printOutputToConsole()
{
	int indexOfOutputLayer = this->layers.size() - 1;
	Matrix* outputValues = this->layers.at(indexOfOutputLayer)->matrixifyActivatedVals();
	for (int col = 0; col < outputValues->getNumCols(); col++)
	{
		cout << outputValues->getValue(0, col) << "\t";
	}
	cout << endl;
}

void NeuralNetwork::printTargetToConsole()
{
	for (int i = 0; i < this->target.size(); i++)
	{
		cout << this->target.at(i) << "\t";
	}
	cout << endl;
}

void NeuralNetwork::printHistoricalErrors()
{
	for (int i = 0; i < this->historicalErrors.size(); i++)
	{
		cout << this->historicalErrors.at(i);
		if (i != this->historicalErrors.size() - 1)
		{
			cout << ",";
		}
	}
	cout << endl;
}

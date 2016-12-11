//
// Created by myychal on 2016-11-06.
//

#ifndef NEURALNETGA_NET_H
#define NEURALNETGA_NET_H
#include <iostream>
#include <vector>
#include <exception>
#include "Neuron.h"
#include "../Dataset.h"
#include "../Exceptions/DifferentSizesOfVectors.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

class NeuralNet {
private:
	vector<vector<double>> Connections;
	vector<vector<Neuron>> Layers;
	vector<int> Topology;
	double LearningRate;
	double DropoutProbability;
	bool DropoutMethod;
public:
	NeuralNet(vector<int> Topology, double learning_rate, bool dropout_method, double dropout_probability);

	NeuralNet(vector<int> Topology, double learning_rate, bool dropout_method);

	vector<vector<double>> &getConnections();

	void setConnections(const vector<vector<double>> &Connections);

	vector<vector<Neuron>> &getLayers();

	void setLayers(const vector<vector<Neuron>> &Layers);

	void CreateLayers();

	void CreateConnections();

	virtual ~NeuralNet();

	void ProcessDataForward();

	void ChangeOutputsInInputLayer(vector<double> new_outputs);

	void SetOutputOfBiasNeuron(double);

	void BackPropagationForLastLayer(vector<double> desired_outputs);

	void BackPropagationForHiddenLayers();

	void UpdateWeights();

	void ResetInputs();

	void ResetPropagatedError();

//    void
//    Fit(vector<vector<double>> data_to_fit, vector<vector<double>> desired_outputs, double accuracy);

	double CalculateSquaredError(vector<double> desired_outputs);

	vector<double> Predict(vector<double> data_to_predict, bool echo);

	void PartialFit(vector<vector<double>> data_to_fit, vector<vector<double>> desired_outputs,
	                double accuracy);

	void PartialFit(Dataset<double,double> dataset, double accuracy);

	void Dropout(int layer_to_dropout);

	bool ToDropOrNotToDrop();

	void SaveErrorsToFile(const char *path, vector<double> errors);

	double CheckAccuracy(Dataset<double, double> &testSet);
};


#endif //NEURALNETGA_NET_H
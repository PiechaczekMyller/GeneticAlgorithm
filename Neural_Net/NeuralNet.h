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
#include <fstream>
#include <cmath>
using namespace std;

class NeuralNet {
private:
	vector<vector<double>> Connections;
	vector<vector<Neuron>> Layers;
	vector<int> Topology;
	double LearningRate;
    double Accuracy;
    double Tolerance;
	double DropoutProbability;
	bool DropoutMethod;
	vector<int> LayersToDropout;
public:
	NeuralNet(vector<int> Topology, double learning_rate, double Accuracy, double Tolerance, bool dropout_method, double dropout_probability, vector<int> LayersToDropout);

	NeuralNet(vector<int> Topology, double learning_rate, double Accuracy, double Tolerance, bool dropout_method);

	vector<vector<double>> &getConnections();

	void setConnections(const vector<vector<double>> &Connections);

	vector<vector<Neuron>> &getLayers();

	void setLayers(const vector<vector<Neuron>> &Layers);

	void CreateConnections();

    void CreateLayers();

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
		                bool echo);

	void PartialFit(Dataset<double,double> dataset, bool echo);

	void Dropout(int layer_to_dropout);


	double CheckAccuracy(const Dataset<double, double> &testSet);

    double CheckAccuracy(vector<vector<double>> features, vector<vector<double>> labels);
};


#endif //NEURALNETGA_NET_H
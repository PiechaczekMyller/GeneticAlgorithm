#include <iostream>
#include "NeuralNet.h"
#include "Dataset.h"
#include "LoadingDatasetFunctions.h"
#include "GeneticAlgorithm.h"
const int BIAS_NEURON = 1;
using namespace std;
int main() {
    vector<int> Topology;
    Topology.push_back(256);
    Topology.push_back(50 + BIAS_NEURON);
    Topology.push_back(30 + BIAS_NEURON);
    Topology.push_back(2);
    NeuralNet myNet(Topology);
	char path[] = "/Users/apple/ClionProjects/GeneticAlgorithm/Datasets/ecu_1_100_dtf3_train.dat";
	Dataset<double,bool> dataset=LoadingDatasetFromFile(path);
	GeneticAlgorithm<double,bool> geneticAlgorithm(dataset);
	geneticAlgorithm.run();

    return 0;
}
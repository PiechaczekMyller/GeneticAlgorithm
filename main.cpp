#include <iostream>
<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "NeuralNet.h"
#include "Dataset.h"
#include "LoadingDatasetFunctions.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "GeneticAlgorithm/Gene.h"
const int BIAS_NEURON = 1;
=======
#include "Neural_Net/NeuralNet.h"
#include "Dataset.h"
#include "LoadingDatasetFunctions.h"
>>>>>>> 9e0ebad187e91eec5a998b338312a88ca15a8cd9
using namespace std;
int main() {
	srand(time(0));
    vector<int> Topology;
    Topology.push_back(7);
    Topology.push_back(5);
    Topology.push_back(3);
    Topology.push_back(2);

    NeuralNet myNet(Topology);
	char path[] = "/Users/apple/ClionProjects/GeneticAlgorithm/Datasets/ecu_1_100_dtf3_train.dat";
	Dataset<double,bool> dataset=LoadingDatasetFromFile(path);
	GeneticAlgorithm<double,bool> geneticAlgorithm(dataset);
	geneticAlgorithm.sizeOfPopulation=1;
	geneticAlgorithm.sizeOfIndyvidual =200;
	geneticAlgorithm.run();

    vector<double> Data;
    Data.push_back(0.1);
    Data.push_back(0.9);
    Data.push_back(0.5);
    Data.push_back(0.2);
    Data.push_back(0.6);
    Data.push_back(0.4);
    Data.push_back(0.3);
    NeuralNet Net(Topology);
    Net.ChangeOutputsInInputLayer(Data);
    Net.SetOutputOfBiasNeuron(1);
    Net.ProcessDataForward();
//	char path[] = "/Users/apple/ClionProjects/GeneticAlgorithm/Datasets/ecu_1_100_dtf3_train.dat";
//	Dataset<double,bool> dataset=LoadingDatasetFromFile(path);

    return 0;
}
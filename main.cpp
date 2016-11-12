#include <iostream>
#include "Neural_Net/NeuralNet.h"
#include "Dataset.h"
#include "LoadingDatasetFunctions.h"
using namespace std;
int main() {
    vector<int> Topology;
    Topology.push_back(7);
    Topology.push_back(5);
    Topology.push_back(3);
    Topology.push_back(2);
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
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Neural_Net/NeuralNet.h"
#include "Dataset.h"
#include "LoadingDatasetFunctions.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "GeneticAlgorithm/Gene.h"
const int BIAS_NEURON = 1;

using namespace std;
int main() {
	srand(time(0));
    vector<int> Topology;
    Topology.push_back(26);
    Topology.push_back(50);
    Topology.push_back(1);

	NeuralNet myNet(Topology,0.9,false);
	vector<vector<double>> labels;
	vector<vector<double>> features;
	LoadDataset("/Users/apple/ClionProjects/GeneticAlgorithm/Datasets/dataset.txt",features,labels,26,1);
	Dataset<double,double> trainingSet(features, labels);
	labels.clear();
	features.clear();
	LoadDataset("/Users/apple/ClionProjects/GeneticAlgorithm/Datasets/testSet.txt",features,labels,26,1);
	Dataset<double,double> testSet(features, labels);
	myNet.PartialFit(trainingSet, 0.02);
	cout << myNet.CheckAccuracy(trainingSet);

//	GeneticAlgorithm<double,double> geneticAlgorithm(trainingSet);
//	geneticAlgorithm.sizeOfPopulation=2;
//	geneticAlgorithm.sizeOfIndyvidual =100;
//	geneticAlgorithm.run();
//	cout << "elo";
	return 0;
}

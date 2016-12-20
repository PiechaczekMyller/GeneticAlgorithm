#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Neural_Net/NeuralNet.h"
#include "Dataset.h"
#include "LoadingDatasetFunctions.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"

const int BIAS_NEURON = 1;

using namespace std;
int main() {
	srand(time(0));

	vector<vector<double>> labels;
	vector<vector<double>> features;
	LoadDataset("/Users/apple/ClionProjects/GeneticAlgorithm/Datasets/dataset.txt",features,labels,26,1);
	Dataset<double,double> trainingSet(features, labels);
	vector<vector<double>> testLabels;
	vector<vector<double>> testFeatures;
	LoadDataset("/Users/apple/ClionProjects/GeneticAlgorithm/Datasets/testSet.txt",testFeatures,testLabels,26,1);
	Dataset<double,double> testSet(features, labels);
	GeneticAlgorithm geneticAlgorithm(trainingSet,testSet);
	geneticAlgorithm.run();

	return 0;
}

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

	Dataset<double,double> wholeSet;
	wholeSet = LoadingDatasetFromFile("/Users/apple/ClionProjects/GeneticAlgorithm/Datasets/ecu_1_100_dtf3_train.dat");
	wholeSet.maxValueNormalization();
	Dataset<double,double> optimizationSet;
	Dataset<double,double> trainingSetForOptimization;
	Dataset<double,double> testSetForOptimization;
	Dataset<double,double> validationSet;
	wholeSet.getSubsets(0.001, 0.0001, optimizationSet, validationSet);
	optimizationSet.getSubsets(0.9, 0.1, trainingSetForOptimization, testSetForOptimization);
	GeneticAlgorithm geneticAlgorithm(trainingSetForOptimization, testSetForOptimization);
	geneticAlgorithm.run();

	return 0;
}

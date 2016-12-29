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
	Dataset<double,double> trainingSet;
	Dataset<double,double> testSet;
	wholeSet.getSubsets(0.01,0.001,trainingSet,testSet);
	trainingSet.maxValueNormalization();
	testSet.setVectorOfMinValues(trainingSet.getVectorOfMinValues());
	testSet.setVectorOfMaxValues(trainingSet.getVectorOfMaxValues());
	testSet.setVectorOfMeanValues(trainingSet.getVectorOfMeanValues());
	testSet.setVectorOfStds(trainingSet.getVectorOfStds());
	testSet.maxValueNormalization();
	NeuralNet myNet({3,6,3,1},0.6,false);
	myNet.PartialFit(trainingSet,0.01);
	myNet.CheckAccuracy(testSet);
//	GeneticAlgorithm geneticAlgorithm(trainingSet,testSet);
//	geneticAlgorithm.run();

	return 0;
}

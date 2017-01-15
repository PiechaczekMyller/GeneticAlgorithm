#include <iostream>
#include "Neural_Net/NeuralNet.h"
#include "Dataset.h"
#include "LoadingDatasetFunctions.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"

const int BIAS_NEURON = 1;

using namespace std;
int main() {
	srand(time(0));

	Dataset<double,double> testSet;
	Dataset<double,double> trainingSet;
	Dataset<double,double> validationSet = LoadSingleDataset("/Users/apple/ClionProjects/GeneticAlgorithm/Datasets/validationSet.txt");
	JoinDatasets(trainingSet,testSet,1);
	GeneticAlgorithm geneticAlgorithm(trainingSet, testSet);
	Individual optimizedIndividual = geneticAlgorithm.run();
	NeuralNet myNet({3,6,3,1},0.6,0.001,0.00001,false);
	myNet.PartialFit(optimizedIndividual.getFeaturesVector(),optimizedIndividual.getLabelsVector(),false);
	fstream resultFile;
	Settings settings;
	resultFile.open(settings.fileForResults, std::ios::app);
	if(resultFile.good()){
		resultFile << myNet.CheckAccuracy(validationSet);
		resultFile.close();
	}

	return 0;
}

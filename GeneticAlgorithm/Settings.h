//
// Created by Szymek on 14.12.2016.
//

#ifndef GENETICALGORITHM_SETTINGS_H
#define GENETICALGORITHM_SETTINGS_H

#include <string>

struct Settings{
	int populationSize = 10;
	double mutationProbability = 0.01;
	double crossoverProbability=0.8;
	double randomPickProbability = 0.01;
	double weightForAccuracy=0.7;
	double weightForSize=0.3;
	double timeCondition = 0;
	double accuracyCondition = 0;
	double maxNoOfEpochs = 40;
	string selectionMethod = "RouletteWheel";
    string crossoverMethod = "crossoverMethod";
	vector<int> topology = {26,20,10,1};
	double learningRate = 0.8;
    double accuracy = 0.01;
    double tolerance = 0.00001;
	bool twoDescendants = true;
};
#endif //GENETICALGORITHM_SETTINGS_H

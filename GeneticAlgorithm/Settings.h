//
// Created by Szymek on 14.12.2016.
//

#ifndef GENETICALGORITHM_SETTINGS_H
#define GENETICALGORITHM_SETTINGS_H

#include <string>

struct Settings{
	int populationSize = 40;
	double mutationProbability = 0.01;
	double crossoverProbability=0.8;
	double randomPickProbability = 0.01;
	double weightForAccuracy=1.0;
	double weightForSize=0.0;
	double timeCondition = 0;
	double accuracyCondition = 0;
	double maxNoOfEpochs = 100;
	string selectionMethod = "RouletteWheel";
    string crossoverMethod = "crossoverMethod";
	vector<int> topology = {3,6,1};
	double learningRate = 0.8;
	bool twoDescendants = false;
};
#endif //GENETICALGORITHM_SETTINGS_H

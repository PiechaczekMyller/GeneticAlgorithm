//
// Created by Szymek on 14.12.2016.
//

#ifndef GENETICALGORITHM_SETTINGS_H
#define GENETICALGORITHM_SETTINGS_H

#include <string>

struct Settings{
	int populationSize = 5;
	double mutationProbability = 0.05;
	double crossoverProbability=0.9;
	double randomPickProbability = 0.01;
	double weightForAccuracy=0.75;
	double weightForSize=0.25;
	double timeCondition = 0;
	double accuracyCondition = 0;
	double maxNoOfEpochs = 40;
	string selectionMethod = "RouletteWheel";
    string crossoverMethod = "crossoverMethod";
	vector<int> topology = {3,6,3,1};
	double learningRate = 0.6;
	bool twoDescendants = true;
};
#endif //GENETICALGORITHM_SETTINGS_H

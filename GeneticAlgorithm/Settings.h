//
// Created by Szymek on 14.12.2016.
//

#ifndef GENETICALGORITHM_SETTINGS_H
#define GENETICALGORITHM_SETTINGS_H

#include <string>

struct Settings{
	int populationSize = 40;
	double mutationProbability = 0;
	double crossoverProbability=0.8;
	double randomPickProbability = 0.01;
	double weightForAccuracy=0.2;
	double weightForSize=0.8;
	double timeCondition = 0;
	double accuracyCondition = 0;
	double maxNoOfEpochs = 40;
	string selectionMethod = "RouletteWheel";
    string crossoverMethod = "crossoverMethod";
	vector<int> topology = {3,6,1};
	double learningRate = 0.8;
};
#endif //GENETICALGORITHM_SETTINGS_H

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
	double weightForAccuracy=0.8;
	double weightForSize=0.2;
	double timeCondition = 0;
	double accuracyCondition = 0;
	double maxNoOfEpochs = 40;
	string SelectionMethod = "RouletteWheel";
    string CrossoverMethod = "CrossoverMethod";
};
#endif //GENETICALGORITHM_SETTINGS_H

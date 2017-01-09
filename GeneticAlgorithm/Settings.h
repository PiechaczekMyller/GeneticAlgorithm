//
// Created by Szymek on 14.12.2016.
//

#ifndef GENETICALGORITHM_SETTINGS_H
#define GENETICALGORITHM_SETTINGS_H

#include <string>

struct Settings{
	//GA END CONDITIONS
	double timeCondition = 0;
	double accuracyCondition = 0;
	double maxNoOfEpochs = 40;

	//GA RUN SETTINGS
	int populationSize = 10;
	double mutationProbability = 0.01;
	double crossoverProbability=0.6;
	double randomPickProbability = 0.01;
	bool twoDescendants = false;

	//WEIGHTS FOR FITNESS SCORE
	double weightForAccuracy=0.8;
	double weightForSize=0.2;

	//METHODS TO USE
	string selectionMethod = "RouletteWheel";
	string crossoverMethod = "crossoverMethod";

	//SETTINGS FOR NEURAL NETWORK
	vector<int> topology = {3,6,3,1};
	double learningRate = 0.6;
	double accuracy = 0.01;
	double tolerance = 0.00001;
};
#endif //GENETICALGORITHM_SETTINGS_H

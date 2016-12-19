//
// Created by Szymek on 14.12.2016.
//

#ifndef GENETICALGORITHM_SETTINGS_H
#define GENETICALGORITHM_SETTINGS_H
struct Settings{
	int populationSize = 10;
	double mutationProbability;
	double crossoverProbability;
	double randomPickProbability;
	double weightForAccuracy=0.8;
	double weightForSize=0.2;
	double timeCondition;
	double accuracyCondition;
	double maxNoOfEpochs;

};
#endif //GENETICALGORITHM_SETTINGS_H

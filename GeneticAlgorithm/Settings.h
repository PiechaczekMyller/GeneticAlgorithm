//
// Created by Szymek on 14.12.2016.
//

#ifndef GENETICALGORITHM_SETTINGS_H
#define GENETICALGORITHM_SETTINGS_H
struct Settings{
	int populationSize;
	double mutationProbability;
	double crossoverProbability;
	double randomPickProbability;
	double weightForAccuracy;
	double weightForSize;
	double timeCondition;
	double accuracyCondition;

};
#endif //GENETICALGORITHM_SETTINGS_H

//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_H
#define GENETICALGORITHM_GENETICALGORITHM_H

#include <iostream>
#include "Population.h"
#include "../Dataset.h"
#include "Settings.h"
#include <algorithm>

class GeneticAlgorithm{
private:
	Population population;
	Dataset<double, double> trainingSet;
	Dataset<double, double> testSet;
public:
	Settings settings;

	GeneticAlgorithm(const Dataset<double, double> &trainingSet, const Dataset<double, double> &testSet) : trainingSet(
			trainingSet),
	                                                                                                       testSet(testSet){ };

	GeneticAlgorithm(const Dataset<double, double> &trainingSet, const Dataset<double, double> &testSet,
	                 const Settings &settings) : trainingSet(
			trainingSet), testSet(testSet), settings(settings){ }

	void run();

	void CheckSettings();

	virtual ~GeneticAlgorithm(){ }

	void printStats(int noOfEpochs, Individual &bestIndividual) const;
};


#endif //GENETICALGORITHM_GENETICALGORITHM_H

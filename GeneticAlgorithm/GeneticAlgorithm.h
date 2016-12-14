//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_H
#define GENETICALGORITHM_GENETICALGORITHM_H

#include <iostream>
#include "Population.h"
#include "../Dataset.h"
#include "Settings.h"

class GeneticAlgorithm{
private:
	Population population;
	Dataset trainingSet;
	Dataset testSet;
public:
	Settings settings;

	GeneticAlgorithm(const Dataset &trainingSet, const Dataset &testSet) : trainingSet(trainingSet),
	                                                                       testSet(testSet){ };

	GeneticAlgorithm(const Dataset &trainingSet, const Dataset &testSet, const Settings &settings) : trainingSet(
			trainingSet), testSet(testSet), settings(settings){ }

	virtual ~GeneticAlgorithm(){ }
};


#endif //GENETICALGORITHM_GENETICALGORITHM_H

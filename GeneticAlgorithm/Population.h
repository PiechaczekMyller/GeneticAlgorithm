//
// Created by Szymek on 13.11.2016.
//

#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include <iostream>
#include <vector>
#include <cmath>
#include "Indyvidual.h"
#include "../Dataset.h"

class Population{
private:
	std::vector<Indyvidual> vectorOfIndyviduals;
public:

	Population(){ }

	Population(const std::vector<Indyvidual> &vectorOfIndyviduals) : vectorOfIndyviduals(vectorOfIndyviduals){ }

	void createInitialPopulation(const int sizeOfPopulation, const Dataset<double, double> &trainingSet);

	virtual ~Population(){ };

	void addAClassExample(const Dataset<double, double> &trainingSet, vector<vector<double>> &randomFeaturesVector,
	                      vector<vector<double>> &labelsVector) const;

	void addBClassExample(const Dataset<double, double> &trainingSet, vector<vector<double>> &randomFeaturesVector,
	                      vector<vector<double>> &labelsVector) const;
};

#endif //GENETICALGORITHM_POPULATION_H


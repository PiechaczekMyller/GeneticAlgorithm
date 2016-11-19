//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_H
#define GENETICALGORITHM_GENETICALGORITHM_H

#include <iostream>
#include "Algorithm.h"
#include "Population.h"
template <typename featureType, typename labelType>
class GeneticAlgorithm : public Algorithm<featureType,labelType>{

public:
	int sizeOfPopulation = 100;
	int numberOfGenomes = 100;
	int sizeOfGenome = 100;
	double mutationCoefficient = 0.01;
	GeneticAlgorithm(const Dataset<featureType, labelType> &dataset) : Algorithm<featureType,labelType>(dataset){ }
	void run(){
		Population<featureType,labelType> population;
		population.CreateInitialPopulation(Algorithm<featureType,labelType>::dataset,sizeOfPopulation,numberOfGenomes,sizeOfGenome);
		std::cout<<"Initial population created";
	}
};


#endif //GENETICALGORITHM_GENETICALGORITHM_H

//
// Created by Szymek on 15.12.2016.
//

#include "GeneticAlgorithm.h"

void GeneticAlgorithm::run(){
	Population population;
	population.createInitialPopulation(settings.populationSize, trainingSet);
}

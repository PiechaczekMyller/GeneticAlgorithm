//
// Created by Szymek on 15.12.2016.
//

#include "GeneticAlgorithm.h"

void GeneticAlgorithm::run(){
	population.createInitialPopulation(settings.populationSize, trainingSet);
	bool endCondition=false;
	while(endCondition == false){
		population.checkFitnessScores(testSet,trainingSet.getLength());
		population.crossover(settings.crossoverProbability);
		endCondition = true;
	}
}

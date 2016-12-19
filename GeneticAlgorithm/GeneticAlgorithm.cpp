//
// Created by Szymek on 15.12.2016.
//

#include "GeneticAlgorithm.h"
#include "../Exceptions/WrongParameterRange.h"

void GeneticAlgorithm::CheckSettings() {
    if (settings.crossoverProbability > 1 || settings.crossoverProbability < 0 || settings.mutationProbability > 1 || settings.mutationProbability < 0 || settings.randomPickProbability > 1 || settings.randomPickProbability < 0)
        throw WrongParameterRange("Probability should have value from 0 to 1");
}


void GeneticAlgorithm::run(){
    try {
        CheckSettings();
    }
    catch (const WrongParameterRange &e)
    {
        cout << e.what() << endl;
    }
	Population population;
	population.createInitialPopulation(settings.populationSize, trainingSet);
	bool endCondition=false;
	while(!endCondition){
		population.checkFitnessScores(testSet,trainingSet.getLength());

		endCondition = true;
	}
    population.createInitialPopulation(10, trainingSet);
    population.Mutation(0.01, trainingSet);
}

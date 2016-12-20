//
// Created by Szymek on 15.12.2016.
//

#include "GeneticAlgorithm.h"
#include "../Exceptions/WrongParameterRange.h"
#include "../Exceptions/WrongMethod.h"

void GeneticAlgorithm::CheckSettings() {
    vector<string> possible_selection_methods;
    possible_selection_methods.push_back("RouletteWheel");
    vector<string> possible_crossover_methods;
    possible_crossover_methods.push_back("CrossoverMethod");
    if (settings.crossoverProbability > 1 || settings.crossoverProbability < 0 || settings.mutationProbability > 1 || settings.mutationProbability < 0 || settings.randomPickProbability > 1 || settings.randomPickProbability < 0)
        throw WrongParameterRange("Probability should have value from 0 to 1");
    if (find(possible_selection_methods.begin(), possible_selection_methods.end(), settings.SelectionMethod)==possible_selection_methods.end())
        throw WrongMethod(settings.SelectionMethod, possible_selection_methods);
    if (find(possible_crossover_methods.begin(), possible_crossover_methods.end(), settings.CrossoverMethod)==possible_crossover_methods.end())
        throw WrongMethod(settings.CrossoverMethod, possible_crossover_methods);
}

void GeneticAlgorithm::run(){
    try {
        CheckSettings();
    }
    catch (const WrongParameterRange &e)
    {
        cout << e.what() << endl;
    }
    catch (const WrongMethod &e)
    {
        e.what();
    }
	Population population;
	population.createInitialPopulation(settings.populationSize, trainingSet);
    int no_of_epochs = 0;
	while(no_of_epochs!=settings.maxNoOfEpochs){
		population.checkFitnessScores(testSet,trainingSet.getLength());
//		population.crossover(settings.crossoverProbability);
        no_of_epochs++;
	}
    population.Mutation(0.01, trainingSet);
}

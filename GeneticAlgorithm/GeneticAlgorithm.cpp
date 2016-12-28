//
// Created by Szymek on 15.12.2016.
//

#include "GeneticAlgorithm.h"
#include "../Exceptions/WrongParameterRange.h"
#include "../Exceptions/WrongMethod.h"

void GeneticAlgorithm::CheckSettings(){
	vector<string> possible_selection_methods;
	possible_selection_methods.push_back("RouletteWheel");
	vector<string> possible_crossover_methods;
	possible_crossover_methods.push_back("crossoverMethod");
	if(settings.crossoverProbability > 1 || settings.crossoverProbability < 0 || settings.mutationProbability > 1 ||
	   settings.mutationProbability < 0 || settings.randomPickProbability > 1 || settings.randomPickProbability < 0)
		throw WrongParameterRange("Probability should have value from 0 to 1");
	if(find(possible_selection_methods.begin(), possible_selection_methods.end(), settings.selectionMethod) ==
	   possible_selection_methods.end())
		throw WrongMethod(settings.selectionMethod, possible_selection_methods);
	if(find(possible_crossover_methods.begin(), possible_crossover_methods.end(), settings.crossoverMethod) ==
	   possible_crossover_methods.end())
		throw WrongMethod(settings.crossoverMethod, possible_crossover_methods);
}

void GeneticAlgorithm::run(){
	try{
		CheckSettings();
	}
	catch(const WrongParameterRange &e){
		cout << e.what() << endl;
	}
	catch(const WrongMethod &e){
		e.what();
	}
	population.createInitialPopulation(settings.populationSize, trainingSet);
	int noOfEpochs = 0;
	while(noOfEpochs != settings.maxNoOfEpochs){
		population.checkFitnessScores(testSet, trainingSet.getLength(), settings);
		population.setBestFitnessScore();
		cout << "Generation " << noOfEpochs << " best fitness score: " << population.getBestFitnessScore() << endl;
		population.SelectionRouletteWheel();
		population.crossover(settings.crossoverProbability);
		population.Mutation(settings.mutationProbability,trainingSet);
		population.resetBestFitnessScore();
		noOfEpochs++;
	}
}

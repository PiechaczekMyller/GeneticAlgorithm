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
	std::vector<double> vectorOfScores;
	Individual bestIndividualFromPopulation;
	Individual bestIndividual;
	while(noOfEpochs != settings.maxNoOfEpochs){
		population.checkFitnessScores(testSet, trainingSet.getVectorOfFeatures().size(), settings);
		population.sortByFitness();
		bestIndividualFromPopulation =population.getVectorOfIndividuals()[0];
		if(bestIndividualFromPopulation.getFitnessScore() >= bestIndividual.getFitnessScore()){
			if(bestIndividualFromPopulation.getFeaturesVector().size()<bestIndividual.getFeaturesVector().size()){
				bestIndividual=bestIndividualFromPopulation;
			}
		}
		population.setStats();
		printStats(noOfEpochs, bestIndividualFromPopulation);
		vectorOfScores.push_back(population.getBestFitnessScore());
		population.SelectionRouletteWheel();
		Population children(population);
		children.crossover(settings);
		children.compensate(trainingSet, settings);
		children.checkFitnessScores(testSet, trainingSet.getVectorOfFeatures().size(), settings);
		population.getVectorOfIndividuals().insert(population.getVectorOfIndividuals().begin(),
		                                           children.getVectorOfIndividuals().begin(),
		                                           children.getVectorOfIndividuals().end());
		population.Mutation(settings.mutationProbability, trainingSet);
		population.SurvivorSelection(settings.populationSize);
		population.resetBestFitnessScore();
		noOfEpochs++;
	}
	std::cout << *max_element(vectorOfScores.begin(), vectorOfScores.end());
}

void GeneticAlgorithm::printStats(int noOfEpochs, Individual &bestIndividual) const{
	cout << "Generation " << noOfEpochs << " best fitness score: " << population.getBestFitnessScore() << endl;
	cout << "Best individual: " << bestIndividual.getSerialNumber() << " accuracy: " << bestIndividual.getAccuracy() << " size: "<< bestIndividual.getFeaturesVector().size() << endl;
	cout << "Mean fitness score: " << population.getMeanFitnessScore() << " Worst fitness score: " << population.getWorstFitnessScore() << endl;
	cout << "Max length: " << population.getMaxLenght() << " Min length: " << population.getMinLength() << " Mean Length: " << population.getMeanLength() << endl;
}

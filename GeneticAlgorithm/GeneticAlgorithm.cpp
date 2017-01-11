//
// Created by Szymek on 15.12.2016.
//
#include <time.h>
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

Individual & GeneticAlgorithm::run(){
	try{
		CheckSettings();
	}
	catch(const WrongParameterRange &e){
		cout << e.what() << endl;
	}
	catch(const WrongMethod &e){
		e.what();
	}

	population.createInitialPopulation(settings.populationSize, trainingSet, settings);
	std::vector<double> vectorOfScores;
	Individual bestIndividualFromPopulation;
	Individual bestIndividual;
	timeAtBeginning = time(NULL);
	while(noOfEpochs != settings.maxNoOfEpochs){
		population.checkFitnessScores(testSet, trainingSet.getVectorOfFeatures().size(), settings);
		population.sortByFitness();
		bestIndividualFromPopulation = population.getVectorOfIndividuals()[0];
		if(bestIndividualFromPopulation.getFitnessScore() >= bestIndividual.getFitnessScore()){
			if(bestIndividualFromPopulation.getFeaturesVector().size() < bestIndividual.getFeaturesVector().size()){
				bestIndividual = bestIndividualFromPopulation;
			}
		}
		population.setStats();
		saveResults(settings.fileForResults);
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
	return bestIndividual;
}

void GeneticAlgorithm::printStats(int noOfEpochs, Individual &bestIndividual) const{
	cout << endl << "Generation " << noOfEpochs << " best fitness score: " << population.getBestFitnessScore() << endl;
	cout << "Best individual: " << bestIndividual.getSerialNumber() << " accuracy: " << bestIndividual.getAccuracy() <<
	" size: " << bestIndividual.getFeaturesVector().size() << endl;
	cout << "Mean fitness score: " << population.getMeanFitnessScore() << " Worst fitness score: " <<
	population.getWorstFitnessScore() << endl;
	cout << "Max length: " << population.getMaxLenght() << " Min length: " << population.getMinLength() <<
	" Mean Length: " << population.getMeanLength() << endl << endl;
}

void GeneticAlgorithm::saveResults(std::string filename){
	fstream resultFile;
	resultFile.open(filename, std::ios::app);
	if(resultFile.good()){
		resultFile.seekg(0, ios::end);
		if(resultFile.tellg() == 0){
			resultFile << "Generation number,"
					"Max fitness,Min fitness,Mean fitness,"
					"Max accuracy,Min accuracy,Mean accuracy,"
					"Max length,Min length,Mean length,"
					"Time\n";
		}
		else{
			resultFile << noOfEpochs << "," << population.getMaxFitnessScore() << "," <<
			population.getMinFitnessScore() << "," << population.getMeanFitnessScore()
			<< "," << population.getMaxAccuracy() << "," << population.getMinAccuracy() << "," <<
			population.getMeanAccuracy()
			<< "," << population.getMaxLenght() << "," << population.getMinLength() << "," << population.getMeanLength()
			<< "," << difftime(time(NULL), timeAtBeginning) << "\n";
		}
		resultFile.close();
	}
	else
		cout << "cannot open file" << endl;
}

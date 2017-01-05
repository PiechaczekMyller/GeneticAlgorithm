//
// Created by Szymek on 13.11.2016.
//

#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include "Individual.h"
#include "../Dataset.h"
#include "../Neural_Net/NeuralNet.h"
#include "Settings.h"

class Population{
private:
	std::vector<Individual> vectorOfIndividuals;
	double bestFitnessScore = 0;
public:

	Population(){ }

	Population(const std::vector<Individual> &vectorOfIndividuals) : vectorOfIndividuals(vectorOfIndividuals){ }

	Population(const Population &populationToSave);

	void setVectorOfIndividuals(vector<Individual> new_vector);

	std::vector<Individual> &getVectorOfIndividuals();

	void createInitialPopulation(const int sizeOfPopulation, const Dataset<double, double> &trainingSet);

	void addAClassExample(const Dataset<double, double> &trainingSet, vector<vector<double>> &randomFeaturesVector,
	                      vector<vector<double>> &labelsVector) const;

	void addBClassExample(const Dataset<double, double> &trainingSet, vector<vector<double>> &randomFeaturesVector,
	                      vector<vector<double>> &labelsVector) const;

	void checkFitnessScores(const Dataset<double, double> &testSet, long sizeOfTrainingSet, Settings settings);

	void crossover(Settings settings);

	void operator=(Population populationToSave);

	virtual ~Population(){ };


	void SelectionRouletteWheel();

	double CalculateSumOfFitnessScores();

	vector<double> CalculateWheelSegments(double scores_sum);

	void Mutation(double mutation_probability, Dataset<double, double> &training_set);


	void setBestFitnessScore();

	void resetBestFitnessScore();

	double getBestFitnessScore() const{
		return bestFitnessScore;
	}

	void compensate(Dataset<double, double> &training_set, Settings settings);

	void createRandomIndividual(const Dataset<double, double> &trainingSet);

	void sortByFitness();

	void SurvivorSelection(int populationSize);
};

#endif //GENETICALGORITHM_POPULATION_H


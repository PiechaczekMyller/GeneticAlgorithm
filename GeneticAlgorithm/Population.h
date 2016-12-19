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

class Population{
private:
	std::vector<Individual> vectorOfIndividuals;
public:

	Population(){ }

	Population(const std::vector<Individual> &vectorOfIndyviduals) : vectorOfIndividuals(vectorOfIndyviduals){ }

    void setVectorOfIndividuals(vector<Individual> new_vector);

    vector<Individual> getVectorOfIndividuals();

	void createInitialPopulation(const int sizeOfPopulation, const Dataset<double, double> &trainingSet);

	void addAClassExample(const Dataset<double, double> &trainingSet, vector<vector<double>> &randomFeaturesVector,
	                      vector<vector<double>> &labelsVector) const;

	void addBClassExample(const Dataset<double, double> &trainingSet, vector<vector<double>> &randomFeaturesVector,
	                      vector<vector<double>> &labelsVector) const;

	void checkFitnessScores(const Dataset<double, double> &testSet, long sizeOfTrainingSet);

	virtual ~Population(){ };

	void setTopologyForNeuralNet(vector<int> &topology) const;

	void SelectionRouletteWheel();

	double CalculateSumOfFitnessScores();

	vector<double> CalculateWheelSegments(double scores_sum);

    void Mutation(double mutation_probability, Dataset<double,double> &training_set);
};

#endif //GENETICALGORITHM_POPULATION_H


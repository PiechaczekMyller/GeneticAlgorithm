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
	double maxFitnessScore = 0;
	double meanFitnessScore = 0;
	double minFitnessScore = 2;
	long maxLenght;
	long minLength;
	double meanLength;
	double maxAccuracy = 0;
	double meanAccuracy = 0;
	double minAccuracy = 2;

public:

	Population(){ }

	Population(const std::vector<Individual> &vectorOfIndividuals) : vectorOfIndividuals(vectorOfIndividuals){ }

	Population(const Population &populationToSave);

	void setVectorOfIndividuals(vector<Individual> new_vector);

	std::vector<Individual> &getVectorOfIndividuals();

	void createInitialPopulation(const int sizeOfPopulation, const Dataset<double, double> &trainingSet,
		                             Settings settings);

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
		return maxFitnessScore;
	}

	void compensate(Dataset<double, double> &training_set, Settings settings);

	void createRandomIndividual(const Dataset<double, double> &trainingSet, Settings &settings);

	void sortByFitness();

	void SurvivorSelection(int populationSize);

	void setStats();

	void setWorstFitness();

	void setMeanFitness();

	void setMaxLength();

	void setMinLength();

	void setMeanLength();

	void setMaxAccuracy();

	void setMinAccuracy();

	void setMeanAccuracy();

	double getMeanFitnessScore() const{
		return meanFitnessScore;
	}

	double getWorstFitnessScore() const{
		return minFitnessScore;
	}

	long getMaxLenght() const{
		return maxLenght;
	}

	long getMinLength() const{
		return minLength;
	}

	double getMeanLength() const{
		return meanLength;
	}

	double getMaxFitnessScore() const{
		return maxFitnessScore;
	}

	double getMinFitnessScore() const{
		return minFitnessScore;
	}

	double getMaxAccuracy() const{
		return maxAccuracy;
	}

	double getMeanAccuracy() const{
		return meanAccuracy;
	}

	double getMinAccuracy() const{
		return minAccuracy;
	}
};

#endif //GENETICALGORITHM_POPULATION_H


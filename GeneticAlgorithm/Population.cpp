//
// Created by Szymek on 15.12.2016.
//

#include <vector>
#include "Population.h"


void Population::createInitialPopulation(const int sizeOfPopulation, const Dataset<double, double> &trainingSet){
	for(int loopControl = 0; loopControl < sizeOfPopulation; loopControl++){
		std::vector<std::vector<double>> randomFeaturesVector;
		std::vector<std::vector<double>> labelsVector;
		const long datasetLength = trainingSet.getLength();
		const long randomLength = (rand() % datasetLength) / 2;
		for(int loopControl2 = 0; loopControl2 < randomLength; loopControl2 = loopControl2 + 2){
			addAClassExample(trainingSet, randomFeaturesVector, labelsVector);
			addBClassExample(trainingSet, randomFeaturesVector, labelsVector);
		}
		Indyvidual newIndyvidual(randomFeaturesVector, labelsVector);
		vectorOfIndyviduals.push_back(newIndyvidual);
	}
	std::cout << "Initial population created";
}

void Population::addBClassExample(const Dataset<double, double> &trainingSet,
                                  vector<vector<double>> &randomFeaturesVector,
                                  vector<vector<double>> &labelsVector) const{
	long bClassIndex = trainingSet.getRandomBClassIndex();
	randomFeaturesVector.push_back(trainingSet.getVectorOfFeatures()[bClassIndex]);
	labelsVector.push_back(trainingSet.getVectorOfLabels()[bClassIndex]);
}

void Population::addAClassExample(const Dataset<double, double> &trainingSet,
                                  vector<vector<double>> &randomFeaturesVector,
                                  vector<vector<double>> &labelsVector) const{
	long aClassIndex = trainingSet.getRandomAClassIndex();
	randomFeaturesVector.push_back(trainingSet.getVectorOfFeatures()[aClassIndex]);
	labelsVector.push_back(trainingSet.getVectorOfLabels()[aClassIndex]);
}

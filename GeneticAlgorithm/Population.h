//
// Created by Szymek on 13.11.2016.
//

#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include <iostream>
#include "Indyvidual.h"
#include "../Dataset.h"
template <typename featureType, typename labelType>
class Population{
	std::vector<Indyvidual<featureType,labelType>> vectorOfIndyviduals;
	int generationNumber = 0;
public:
	Population(){ };

	const vector<Indyvidual<featureType, labelType>> &getVectorOfIndyviduals() const{
		return vectorOfIndyviduals;
	}

	void setVectorOfIndyviduals(const vector<Indyvidual<featureType, labelType>> &vectorOfIndyviduals){
		Population::vectorOfIndyviduals = vectorOfIndyviduals;
	}

	int getGenerationNumber() const{
		return generationNumber;
	}

	void setGenerationNumber(int generationNumber){
		Population::generationNumber = generationNumber;
	}

	void CreateInitialPopulation(Dataset<featureType,labelType> &dataset,int sizeOfPopulation, int sizeOfIndyvidual){
		srand(time(NULL));
		for(int loopControl = 0; loopControl < sizeOfPopulation; loopControl++){
			Indyvidual <featureType,labelType> indyvidual;
			indyvidual.CreateRandomIndyvidual(dataset,sizeOfIndyvidual);
			vectorOfIndyviduals.push_back(indyvidual);
		}
	};

	virtual ~Population(){}
};


#endif //GENETICALGORITHM_POPULATION_H

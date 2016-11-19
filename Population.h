//
// Created by Szymek on 13.11.2016.
//

#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include "Indyvidual.h"
#include "Dataset.h"
template <typename featureType, typename labelType>
class Population{
	std::vector<Indyvidual<featureType,labelType>> vectorOfIndyviduals;
	int generationNumber = 0;
public:
	Population(){ };

	void CreateInitialPopulation(Dataset<featureType,labelType> &dataset,int sizeOfPopulation, int numberOfgenomes, int sizeOfGenome){
		for(int loopControl = 0; loopControl < sizeOfPopulation; loopControl++){
			Indyvidual <featureType,labelType> indyvidual;
			indyvidual.CreateRandomIndyvidual(dataset,numberOfgenomes,sizeOfGenome);
			vectorOfIndyviduals.push_back(indyvidual);
		}
	};
};


#endif //GENETICALGORITHM_POPULATION_H

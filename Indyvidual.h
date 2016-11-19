//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_INDYVIDUAL_H
#define GENETICALGORITHM_INDYVIDUAL_H

#include <vector>
#include "Genome.h"
#include "Dataset.h"

template <typename featureType, typename labelType>
class Indyvidual{
std::vector<Genome<featureType,labelType>> vectorOfgenomes;
public:


	Indyvidual(){ }
	void CreateRandomIndyvidual(Dataset<featureType,labelType> &dataset,int numberOfGenomes,int sizeOfGenome){
		for(int loopControl = 0; loopControl < numberOfGenomes; loopControl++){
			Genome<featureType,labelType> genome;
			genome.CreateRandomGenome(sizeOfGenome,dataset);
			vectorOfgenomes.push_back(genome);

		}
	};
};



#endif //GENETICALGORITHM_INDYVIDUAL_H

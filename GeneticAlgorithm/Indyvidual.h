//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_INDYVIDUAL_H
#define GENETICALGORITHM_INDYVIDUAL_H

#include <vector>
#include "Gene.h"
#include "../Dataset.h"

template <typename featureType, typename labelType>
class Indyvidual{
	std::vector<Gene<featureType, labelType>> vectorOfgenes;
	bool isParent=0;
public:


	Indyvidual(){ }

	const vector<Gene<featureType, labelType>> &getVectorOfgenes() const{
		return vectorOfgenes;
	}

	void setVectorOfgenomes(const vector<Gene<featureType, labelType>> &vectorOfgenes){
		Indyvidual::vectorOfgenes = vectorOfgenes;
	}

	void CreateRandomIndyvidual(Dataset<featureType, labelType> &dataset, int sizeOfIndyvidual){
		for(int loopControl = 0; loopControl < sizeOfIndyvidual; loopControl=loopControl+2){
			Gene<featureType, labelType> gene;
			gene.createRandomAClassGene(dataset);
			vectorOfgenes.push_back(gene);
			gene.createRandomBClassGene(dataset);
			vectorOfgenes.push_back(gene);
		}
	};

};


#endif //GENETICALGORITHM_INDYVIDUAL_H

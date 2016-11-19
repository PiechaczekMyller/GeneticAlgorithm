//
// Created by Szymek on 14.11.2016.
//

#ifndef GENETICALGORITHM_GENOME_H
#define GENETICALGORITHM_GENOME_H

#include <vector>
#include "Gene.h"
#include "Dataset.h"


template <typename featureType, typename labelType>
class Genome{
private:
	std::vector<Gene<featureType, labelType>> vectorOfGenes;
public:

	Genome(){ };

	const std::vector<Gene<featureType, labelType>> &getGenome() const{
		return vectorOfGenes;
	}

	Genome(const std::vector<Gene<featureType, labelType>> &genome) : vectorOfGenes(genome){ }

	Genome(const Genome &indyvidual){
		vectorOfGenes = indyvidual.getGenome();
	}

	void CreateRandomGenome(int sizeOfGenome, Dataset<featureType,labelType> &dataset){
		for(int loopControl = 0; loopControl < sizeOfGenome; loopControl++){
			Gene<featureType, labelType> gene;
			gene.createRandomGene(dataset);
			vectorOfGenes.push_back(gene);
		}
	};

	virtual ~Genome(){ }
};

#endif //GENETICALGORITHM_GENOME_H
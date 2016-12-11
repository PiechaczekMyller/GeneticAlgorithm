//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_GENE_H
#define GENETICALGORITHM_GENE_H

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Dataset.h"

template <typename featureType, typename labelType>
class Gene{
private:
	std::vector<featureType> feature;
	std::vector<labelType> label;
public:

	Gene(){ }

	Gene(featureType feature, labelType label) : feature(feature), label(label){ }

	std::vector<featureType> getFeature() const{
		return feature;
	}

	void setFeature(std::vector<featureType> feature){
		Gene::feature = feature;
	}

	labelType getLabel() const{
		return label;
	}

	void setLabel(labelType label){
		Gene::label = label;
	}

	void createRandomGene(const Dataset<featureType, labelType> &dataset){
		const unsigned long sizeOfDataset = dataset.getVectorOfFeatures().size();
		unsigned long randomNumber = rand() % sizeOfDataset;
		feature = dataset.getVectorOfFeatures()[randomNumber];
		label = dataset.getVectorOfLabels()[randomNumber];
	}

	void createRandomAClassGene(Dataset<featureType, labelType> &dataset){
		long randomAClassIndex = dataset.getRandomAClassIndex();
		feature = dataset.getVectorOfFeatures()[randomAClassIndex];
		label = dataset.getVectorOfLabels()[randomAClassIndex];
	}
	void createRandomBClassGene(Dataset<featureType, labelType> &dataset){
		long randomBClassIndex = dataset.getRandomBClassIndex();
		feature = dataset.getVectorOfFeatures()[randomBClassIndex];
		label = dataset.getVectorOfLabels()[randomBClassIndex];
	};

	virtual ~Gene(){ }
};


#endif //GENETICALGORITHM_GENE_H
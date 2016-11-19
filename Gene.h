//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_GENE_H
#define GENETICALGORITHM_GENE_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Dataset.h"

template <typename featureType, typename labelType>
class Gene{
private:
	std::vector<featureType> feature;
	labelType label;
public:

	Gene(){ }

	Gene(featureType feature, labelType label) : feature(feature), label(label){ }

	featureType getFeature() const{
		return feature;
	}

	void setFeature(featureType feature){
		Gene::feature = feature;
	}

	labelType getLabel() const{
		return label;
	}

	void setLabel(labelType label){
		Gene::label = label;
	}

	void createRandomGene(const Dataset<featureType,labelType> &dataset){
		srand(time(NULL));
		const int sizeOfDataset = dataset.getVectorOfFeatures().size();
		int randomNumber = rand() % sizeOfDataset;
		feature = dataset.getVectorOfFeatures()[randomNumber];
		label = dataset.getVectorOfLabels()[randomNumber];
	}

	virtual ~Gene(){ }
};


#endif //GENETICALGORITHM_GENE_H
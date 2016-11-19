//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_ALGORITHM_H
#define GENETICALGORITHM_ALGORITHM_H

#include "Dataset.h"
template <typename featureType, typename labelType>
class Algorithm{
public:
	Dataset<featureType,labelType> dataset;

	Algorithm(){ }

	Algorithm(const Dataset<featureType, labelType> &dataset) : dataset(dataset){ }

	virtual ~Algorithm(){ }
};


#endif //GENETICALGORITHM_ALGORITHM_H

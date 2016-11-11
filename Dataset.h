//
// Created by Szymek on 09.11.2016.
//

#ifndef GENETICALGORITHM_DATASET_H
#define GENETICALGORITHM_DATASET_H

#include <vector>
#include "Exceptions/FeaturesLabesLenNotEqualExc.h"

template <typename FeaturesType, typename LabelsType>
class Dataset{
private:
	std::vector<std::vector<FeaturesType>> vectorOfFeatures;
	std::vector<LabelsType> vectorOfLabels;
public:
	Dataset(){ };

	Dataset(const std::vector<std::vector<FeaturesType>> &vectorOfFeaturesToLoad,
	        const std::vector<LabelsType> &vectorOfLabelsToLoad){
		if(vectorOfFeaturesToLoad.size() != vectorOfLabelsToLoad.size()){
			throw FeaturesLabesLenNotEqualExc();
		}
		else{
			vectorOfFeatures = vectorOfFeaturesToLoad;
			vectorOfLabels = vectorOfLabelsToLoad;
		}
	};

	const std::vector<std::vector<FeaturesType>> &getVectorOfFeatures() const{
		return vectorOfFeatures;
	};

	const std::vector<LabelsType> &getVectorOfLabels() const{
		return vectorOfLabels;
	};

	virtual ~Dataset(){ };

};


#endif //GENETICALGORITHM_DATASET_H

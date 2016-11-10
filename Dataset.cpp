//
// Created by Szymek on 09.11.2016.
//

#include "Dataset.h"
#include "Exceptions/FeaturesLabesLenNotEqualExc.h"

template <typename FeaturesType, typename LabelsType>
Dataset::Dataset(const std::vector<std::vector<FeaturesType>> &vectorOfFeaturesToLoad,
                 const std::vector<LabelsType> &vectorOfLabelsToLoad){
	if(vectorOfFeaturesToLoad.size() != vectorOfLabelsToLoad.size()){
		throw FeaturesLabesLenNotEqualExc();
	}
	else{
		vectorOfFeatures = vectorOfFeaturesToLoad;
		vectorOfLabels = vectorOfLabelsToLoad;
	}
}

template <typename FeaturesType, typename LabelsType>
Dataset<FeaturesType, LabelsType>::Dataset(){ }

template <typename FeaturesType, typename LabelsType>
const std::vector<std::vector<FeaturesType>> &Dataset::getVectorOfFeatures() const{
	return vectorOfFeatures;
}

template <typename FeaturesType, typename LabelsType>
const std::vector<LabelsType> &Dataset::getVectorOfLabels() const{
	return vectorOfLabels;
}

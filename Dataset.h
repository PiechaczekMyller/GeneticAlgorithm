//
// Created by Szymek on 09.11.2016.
//

#ifndef GENETICALGORITHM_DATASET_H
#define GENETICALGORITHM_DATASET_H

#include <vector>

template <typename FeaturesType, typename LabelsType>
class Dataset{
private:
	std::vector<std::vector<FeaturesType>> vectorOfFeatures;
	std::vector<LabelsType> vectorOfLabels;
public:
	Dataset();

	Dataset(const std::vector<std::vector<FeaturesType>> &vectorOfFeatures,
	        const std::vector<LabelsType> &vectorOfLabels);

	const std::vector<std::vector<FeaturesType>> &getVectorOfFeatures() const;

	const std::vector<LabelsType> &getVectorOfLabels() const;

	virtual ~Dataset(){ };

};


#endif //GENETICALGORITHM_DATASET_H

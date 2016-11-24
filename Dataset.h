//
// Created by Szymek on 09.11.2016.
//

#ifndef GENETICALGORITHM_DATASET_H
#define GENETICALGORITHM_DATASET_H

#include <vector>
#include <stdlib.h>
#include "Exceptions/FeaturesLabesLenNotEqualExc.h"

template <typename FeaturesType, typename LabelsType>
class Dataset{
private:
	std::vector<std::vector<FeaturesType>> vectorOfFeatures;
	std::vector<LabelsType> vectorOfLabels;
	std::vector<std::vector<long>> vectorOfIndexes;
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
			long index = 0;
			std::vector<long> aClassIndexes;
			std::vector<long> bClassIndexes;
			for(const auto &label:vectorOfLabels){
				if(label == 0){
					aClassIndexes.push_back(index);
				}
				if(label == 1){
					bClassIndexes.push_back(index);
				}
				index++;
			}
			vectorOfIndexes.push_back(aClassIndexes);
			vectorOfIndexes.push_back(bClassIndexes);
		}
	};

	Dataset(const std::vector<std::vector<FeaturesType>> &vectorOfFeaturesToLoad,
	        const std::vector<LabelsType> &vectorOfLabelsToLoad, int numberOfClasses){
		if(vectorOfFeaturesToLoad.size() != vectorOfLabelsToLoad.size()){
			throw FeaturesLabesLenNotEqualExc();
		}
		else{
			vectorOfFeatures = vectorOfFeaturesToLoad;
			vectorOfLabels = vectorOfLabelsToLoad;
			long index = 0;
			std::vector<long> aClass;
			for(auto &label:vectorOfLabels){
				if(label == 1){

				}
			}
		}
	};

	Dataset(const Dataset &dataset){
		vectorOfFeatures = dataset.getVectorOfFeatures();
		vectorOfLabels = dataset.getVectorOfLabels();
		vectorOfIndexes = dataset.getVectorOfIndexes();
	};

	const std::vector<std::vector<FeaturesType>> &getVectorOfFeatures() const{
		return vectorOfFeatures;
	};

	const std::vector<LabelsType> &getVectorOfLabels() const{
		return vectorOfLabels;
	};


	const std::vector<std::vector<long>> &getVectorOfIndexes() const{
		return vectorOfIndexes;
	};

	long &getRandomAClassIndex(){
		long randomNumber = rand() % vectorOfIndexes[0].size();
		return vectorOfIndexes[0][randomNumber];
	};

	long &getRandomBClassIndex(){
		long randomNumber = rand() % vectorOfIndexes[1].size();
		return vectorOfIndexes[1][randomNumber];
	};

	virtual ~Dataset(){ };

};


#endif //GENETICALGORITHM_DATASET_H

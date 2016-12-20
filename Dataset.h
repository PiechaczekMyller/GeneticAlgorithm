//
// Created by Szymek on 09.11.2016.
//

#ifndef GENETICALGORITHM_DATASET_H
#define GENETICALGORITHM_DATASET_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Exceptions/DifferentSizesOfVectors.h"
using namespace std;
template <typename FeaturesType, typename LabelsType>
class Dataset{
private:
	std::vector<std::vector<FeaturesType>> vectorOfFeatures;
	std::vector<std::vector<LabelsType>> vectorOfLabels;
	std::vector<std::vector<long>> vectorOfIndexes;
public:
	Dataset(){ };

	Dataset(const std::vector<std::vector<FeaturesType>> &vectorOfFeaturesToLoad,
	        const std::vector<std::vector<LabelsType>> &vectorOfLabelsToLoad){
		if(vectorOfFeaturesToLoad.size() != vectorOfLabelsToLoad.size()){
			throw DifferentSizesOfVectors("Dataset: Features and labels vectors are not equal in length");
		}
		else{
			vectorOfFeatures = vectorOfFeaturesToLoad;
			vectorOfLabels = vectorOfLabelsToLoad;
			long index = 0;
			std::vector<long> aClassIndexes;
			std::vector<long> bClassIndexes;
			for(const auto &label:vectorOfLabels){
				if(label[0] == 0){
					aClassIndexes.push_back(index);
				}
				if(label[0] == 1){
					bClassIndexes.push_back(index);
				}
				index++;
			}
			vectorOfIndexes.push_back(aClassIndexes);
			vectorOfIndexes.push_back(bClassIndexes);
		}
	};

	Dataset(const Dataset &dataset){
		vectorOfFeatures = dataset.getVectorOfFeatures();
		vectorOfLabels = dataset.getVectorOfLabels();
		vectorOfIndexes = dataset.getVectorOfIndexes();
	};

    void getSubsets(double percent_of_subset_for_training_set, double percent_of_subset_for_test_set, Dataset<FeaturesType, LabelsType> &training_set, Dataset<FeaturesType, LabelsType> &test_set)
    {
        typename vector<vector<FeaturesType>>::const_iterator first_features = vectorOfFeatures.begin();
        typename vector<vector<FeaturesType>>::const_iterator last_features = vectorOfFeatures.begin() + (vectorOfFeatures.size() * percent_of_subset_for_training_set);
        vector<vector<FeaturesType>> newFeatures(first_features, last_features);
        cout << newFeatures.size() << endl;
        typename vector<vector<LabelsType>>::const_iterator first_labels = vectorOfLabels.begin();
        typename vector<vector<LabelsType>>::const_iterator last_labels = vectorOfLabels.begin() + (vectorOfLabels.size() * percent_of_subset_for_training_set);
        vector<vector<LabelsType>> newLabels(first_labels, last_labels);
        cout << newLabels.size() << endl;
        training_set.vectorOfFeatures = newFeatures;
        training_set.vectorOfLabels = newLabels;
        typename vector<vector<FeaturesType>>::const_iterator first_features_test = vectorOfFeatures.begin() + (vectorOfFeatures.size() * percent_of_subset_for_training_set);
        typename vector<vector<FeaturesType>>::const_iterator last_features_test = vectorOfFeatures.begin() + (vectorOfFeatures.size() * percent_of_subset_for_training_set) + (vectorOfFeatures.size() * percent_of_subset_for_test_set);
        vector<vector<FeaturesType>> newFeatures_test(first_features_test, last_features_test);
        cout << newFeatures_test.size() << endl;
        typename vector<vector<LabelsType>>::const_iterator first_labels_test = vectorOfLabels.begin() + (vectorOfLabels.size() * percent_of_subset_for_training_set);
        typename vector<vector<LabelsType>>::const_iterator last_labels_test = vectorOfLabels.begin() + (vectorOfLabels.size() * percent_of_subset_for_training_set) + (vectorOfLabels.size() * percent_of_subset_for_test_set);
        vector<vector<LabelsType>>  newLabels_test(first_labels_test, last_labels_test);
        test_set.vectorOfFeatures = newFeatures_test;
        test_set.vectorOfFeatures = newLabels_test;
    };

	const std::vector<std::vector<FeaturesType>> &getVectorOfFeatures() const{
		return vectorOfFeatures;
	};

	const std::vector<std::vector<LabelsType>> &getVectorOfLabels() const{
		return vectorOfLabels;
	};


	const std::vector<std::vector<long>> &getVectorOfIndexes() const{
		return vectorOfIndexes;
	};

	const long &getRandomAClassIndex() const{
		long randomNumber = rand() % vectorOfIndexes[0].size();
		return vectorOfIndexes[0][randomNumber];
	};

	const long &getRandomBClassIndex() const{
		long randomNumber = rand() % vectorOfIndexes[1].size();
		return vectorOfIndexes[1][randomNumber];
	};

	const long &getLength() const{
		return vectorOfLabels.size();
	}

	virtual ~Dataset(){ };

};


#endif //GENETICALGORITHM_DATASET_H
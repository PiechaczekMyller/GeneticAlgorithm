//
// Created by Szymek on 09.11.2016.
//

#ifndef GENETICALGORITHM_DATASET_H
#define GENETICALGORITHM_DATASET_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <math.h>
#include "Exceptions/DifferentSizesOfVectors.h"

using namespace std;

template <typename FeaturesType, typename LabelsType>
class Dataset{
private:
	std::vector<std::vector<FeaturesType>> vectorOfFeatures;
	std::vector<std::vector<LabelsType>> vectorOfLabels;
	std::vector<std::vector<long>> vectorOfIndexes;
	std::vector<double> vectorOfMeanValues;
	std::vector<double> vectorOfMaxValues;
	std::vector<double> vectorOfMinValues;
	std::vector<double> vectorOfStds;
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
			setVectorOfIndexes();
		}
	}

	void setVectorOfIndexes(){
		long index = 0;
		vector<long> aClassIndexes;
		vector<long> bClassIndexes;
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
	};

	Dataset(const Dataset &dataset){
		vectorOfFeatures = dataset.getVectorOfFeatures();
		vectorOfLabels = dataset.getVectorOfLabels();
		vectorOfIndexes = dataset.getVectorOfIndexes();
	};

	void meanRangeValueNormalization(){
		setDataForNormalization();
		for(auto &example : this->vectorOfFeatures){
			int index = 0;
			for(auto &feature : example){
				double featureNorm =
						(feature - vectorOfMeanValues[index]) / (vectorOfMaxValues[index] - vectorOfMinValues[index]);
				feature = featureNorm;
				index++;
			}
		}
	}

	void maxValueNormalization(){
		setDataForNormalization();
		for(auto &example : this->vectorOfFeatures){
			int index = 0;
			for(auto &feature : example){
				double featureNorm = (feature / vectorOfMaxValues[index]);
				feature = featureNorm;
				index++;
			}
		}
	}

	void minValueNormalization(){
		setDataForNormalization();
		for(auto &example : this->vectorOfFeatures){
			int index = 0;
			for(auto &feature : example){
				double featureNorm = (feature / vectorOfMinValues[index]);
				feature = featureNorm;
				index++;
			}
		}
	}

	void meanDeviationNormalization(){
		setDataForNormalization();
		cout << vectorOfMeanValues[1];
		for(auto &example : this->vectorOfFeatures){
			int index = 0;
			for(auto &feature : example){
				double featureNorm = (feature - vectorOfMeanValues[index]) / vectorOfMeanValues[index];
				cout << vectorOfMeanValues[index];
				feature = featureNorm;
				index++;
			}
		}
	}

	void minValueDeviationNormalization(){
		setDataForNormalization();
		for(auto &example : this->vectorOfFeatures){
			int index = 0;
			for(auto &feature : example){
				double featureNorm = (feature - vectorOfMinValues[index]) / vectorOfMinValues[index];
				feature = featureNorm;
				index++;
			}
		}
	}

	void standardization(){
		setDataForNormalization();
		for(auto &example : this->vectorOfFeatures){
			int index = 0;
			for(auto &feature : example){
				double featureNorm = (feature - vectorOfMeanValues[index]) / vectorOfStds[index];
				feature = featureNorm;
				index++;
			}
		}
	}

	void setVectorOfMeanValues(){
		vector<long> vectorOfSums;
		for(auto &feature : getVectorOfFeatures()[0]){
			vectorOfSums.push_back(0);
		}
		for(auto &example : vectorOfFeatures){
			int index = 0;
			for(auto &feature : example){
				vectorOfSums[index] = vectorOfSums[index] + feature;
				index++;
			}
		}
		for(auto &sum : vectorOfSums){
			vectorOfMeanValues.push_back(sum / getLength());
		}
	};

	void setVectorOfMaxValues(){
		for(auto &feature : getVectorOfFeatures()[0]){
			vectorOfMaxValues.push_back(0);
		}
		for(auto &example : vectorOfFeatures){
			int index = 0;
			for(auto &feature : example){
				if(feature > vectorOfMaxValues[index]){
					vectorOfMaxValues[index] = feature;
				}
				index++;
			}
		}
	}

	void setVectorOfMinValues(){
		for(auto &feature : getVectorOfFeatures()[0]){
			vectorOfMinValues.push_back(feature);
		}
		for(auto &example : vectorOfFeatures){
			int index = 0;
			for(auto &feature : example){
				if(feature < vectorOfMinValues[index]){
					vectorOfMinValues[index] = feature;
				}
				index++;
			}
		}
	}

	void setVectorOfStds(){
		if(vectorOfMeanValues.empty()){
			setVectorOfMeanValues();
		}
		for(auto &feature : getVectorOfFeatures()[0]){
			vectorOfStds.push_back(feature);
		}
		int index = 0;
		vector<double> vectorOfSums;
		for(auto &feature : getVectorOfFeatures()[0]){
			vectorOfSums.push_back(0);
		}
		for(auto &example : vectorOfFeatures){
			index = 0;
			for(auto &feature : example){
				vectorOfSums[index] = vectorOfSums[index] + (feature - vectorOfMeanValues[index]);
				index++;
			}
		}
		index = 0;
		for(auto &std:vectorOfStds){
			double multiplier = 1.0 / this->getLength();
			std = sqrt((multiplier * vectorOfSums[index]));
			index++;
		}
	}

	void setDataForNormalization(){
		setVectorOfMinValues();
		setVectorOfMaxValues();
		setVectorOfMeanValues();
		setVectorOfStds();
	}

//    void getSubsets(double percent_of_subset_for_training_set, double percent_of_subset_for_test_set, Dataset<FeaturesType, LabelsType> &training_set, Dataset<FeaturesType, LabelsType> &test_set)
//    {
//        long loop_control = 0;
//        long a_class_index = 0;
//        long b_class_index = 0;
//        vector<vector<double>> random_features;
//        random_features.reserve(unsigned(this->vectorOfLabels.size() * percent_of_subset_for_training_set));
//        vector<vector<double>> random_labels;
//        random_labels.reserve(unsigned(this->vectorOfLabels.size() * percent_of_subset_for_training_set));
//        vector<long> chosen_indexes;
//        random_device rd;
//        mt19937 rng(rd());
//        uniform_int_distribution<long> a_class(this->vectorOfIndexes[0].front(), this->vectorOfIndexes[0].size());
//        uniform_int_distribution<long> b_class(this->vectorOfIndexes[1].front(), this->vectorOfIndexes[1].size());
//        while (loop_control < (this->vectorOfLabels.size() * percent_of_subset_for_training_set)/ 2)
//        {
//            a_class_index = this->vectorOfIndexes[0][a_class(rng)];
//            b_class_index = this->vectorOfIndexes[1][b_class(rng)];
//            if (find(chosen_indexes.begin(), chosen_indexes.end(), a_class_index) == chosen_indexes.end() && find(chosen_indexes.begin(), chosen_indexes.end(), b_class_index) == chosen_indexes.end()) {
//                random_features.push_back(this->getVectorOfFeatures()[a_class_index]);
//                random_labels.push_back(this->getVectorOfLabels()[a_class_index]);
//                random_features.push_back(this->getVectorOfFeatures()[b_class_index]);
//                random_labels.push_back(this->getVectorOfLabels()[b_class_index]);
//                chosen_indexes.push_back(a_class_index);
//                chosen_indexes.push_back(b_class_index);
//                loop_control++;
//            }
//        }
//        training_set.vectorOfFeatures = random_features;
//        training_set.vectorOfLabels = random_labels;
//	    training_set.setVectorOfIndexes();
//        random_features.clear();
//        random_labels.clear();
//        random_features.reserve(unsigned(this->getVectorOfLabels().size() * percent_of_subset_for_test_set));
//        random_labels.reserve(unsigned(this->getVectorOfLabels().size() * percent_of_subset_for_test_set));
//        loop_control = 0;
//        while (loop_control < (this->getVectorOfLabels().size() * percent_of_subset_for_test_set) / 2)
//        {
//            a_class_index = this->vectorOfIndexes[0][a_class(rng)];
//            b_class_index = this->vectorOfIndexes[1][b_class(rng)];
//            if (find(chosen_indexes.begin(), chosen_indexes.end(), a_class_index)== chosen_indexes.end() && find(chosen_indexes.begin(), chosen_indexes.end(), b_class_index)== chosen_indexes.end()) {
//                random_features.push_back(this->getVectorOfFeatures()[a_class_index]);
//                random_labels.push_back(this->getVectorOfLabels()[a_class_index]);
//                random_features.push_back(this->getVectorOfFeatures()[b_class_index]);
//                random_labels.push_back(this->getVectorOfLabels()[b_class_index]);
//                chosen_indexes.push_back(a_class_index);
//                chosen_indexes.push_back(b_class_index);
//                loop_control++;
//            }
//        }
//        test_set.vectorOfFeatures = random_features;
//        test_set.vectorOfLabels = random_labels;
//	    test_set.setVectorOfIndexes();
//        cout << "Subsets created" << endl;
//        cout << "Size of training set: " << training_set.vectorOfLabels.size() << endl;
//        cout << "Size of test set: " << test_set.vectorOfLabels.size() << endl;
//    };

    void getSubsets(double percent_of_subset_for_training_set, double percent_of_subset_for_test_set, Dataset<FeaturesType, LabelsType> &training_set, Dataset<FeaturesType, LabelsType> &test_set)
    {
        double training_set_size = this->vectorOfLabels.size() * percent_of_subset_for_training_set;
        double test_set_size = this->vectorOfLabels.size() * percent_of_subset_for_test_set;
        long index = 0;
        vector<vector<long>> indexes_copy = vectorOfIndexes;
        vector<vector<double>> random_features;
        random_features.reserve(unsigned(training_set_size));
        vector<vector<double>> random_labels;
        random_labels.reserve(unsigned(training_set_size));
        random_shuffle(indexes_copy[0].begin(), indexes_copy[0].end());
        random_shuffle(indexes_copy[1].begin(), indexes_copy[1].end());
        for (long loop_control = 0; loop_control < (training_set_size)/ 2; loop_control++) {
            random_features.push_back(this->vectorOfFeatures[indexes_copy[0][index]]); //add A class feature
            random_labels.push_back(this->vectorOfLabels[indexes_copy[0][index]]);
            random_features.push_back(this->vectorOfFeatures[indexes_copy[1][index]]); //add B class feature
            random_labels.push_back(this->vectorOfLabels[indexes_copy[1][index]]);
            index++;
        }
        training_set.vectorOfFeatures = random_features;
        training_set.vectorOfLabels = random_labels;
        training_set.setVectorOfIndexes();
        random_features.clear();
        random_labels.clear();
        random_features.reserve(unsigned(test_set_size));
        random_labels.reserve(unsigned(test_set_size));
        for (long loop_control = 0; loop_control < test_set_size / 2; loop_control++)
        {
            random_features.push_back(this->vectorOfFeatures[indexes_copy[0][index]]); //add A class feature
            random_labels.push_back(this->vectorOfLabels[indexes_copy[0][index]]);
            random_features.push_back(this->vectorOfFeatures[indexes_copy[1][index]]); //add B class feature
            random_labels.push_back(this->vectorOfLabels[indexes_copy[1][index]]);
            index++;
        }
        test_set.vectorOfFeatures = random_features;
        test_set.vectorOfLabels = random_labels;
        test_set.setVectorOfIndexes();
        cout << "Subsets created" << endl;
        cout << "Training set size: " << training_set.vectorOfLabels.size() << endl;
        cout << "Test set size: " << test_set.vectorOfLabels.size() << endl;
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

	const vector<double> &getVectorOfMeanValues() const{
		return vectorOfMeanValues;
	}

	void setVectorOfMeanValues(const vector<double> &vectorOfMeanValues){
		Dataset::vectorOfMeanValues = vectorOfMeanValues;
	}

	const vector<double> &getVectorOfMaxValues() const{
		return vectorOfMaxValues;
	}

	void setVectorOfMaxValues(const vector<double> &vectorOfMaxValues){
		Dataset::vectorOfMaxValues = vectorOfMaxValues;
	}

	const vector<double> &getVectorOfMinValues() const{
		return vectorOfMinValues;
	}

	void setVectorOfMinValues(const vector<double> &vectorOfMinValues){
		Dataset::vectorOfMinValues = vectorOfMinValues;
	}

	const vector<double> &getVectorOfStds() const{
		return vectorOfStds;
	}

	void setVectorOfStds(const vector<double> &vectorOfStds){
		Dataset::vectorOfStds = vectorOfStds;
	}
};


#endif //GENETICALGORITHM_DATASET_Hvoid Dataset::meanValueNormalization(double min, double max){


//
// Created by Szymek on 15.12.2016.
//
#include "Individual.h"
#include <iostream>
#include <algorithm>
#include <tuple>

void Individual::setScore(double newScore) // needed just for debugging
{
	fitnessScore = newScore;
}

void Individual::ChangeFeature(int index, vector<double> new_feature){
	featuresVector[index] = new_feature;
}

void Individual::ChangeLabel(int index, vector<double> new_label){
	labelsVector[index] = new_label;
}

double Individual::getFitnessScore(){
	return fitnessScore;
}

void Individual::setFitnessScore(double accuracy, double sizeOfTrainingSet, double weightForSize,
                                 double weightForAccuracy){
	double accuracyPart = weightForAccuracy * accuracy;
	double sizePart = weightForSize * (1.0 - (sizeOfIndividual / sizeOfTrainingSet));
	fitnessScore = accuracyPart + sizePart;
}

void crossoverIndividuals(double crossoverRatio, Individual &firstIndividual, Individual &secondIndividual){
	double randomNumber = (rand()%100)/100.0;
	if (randomNumber < crossoverRatio){
		std::vector<std::vector<double>> aClassFeatures;
		std::vector<std::vector<double>> bClassFeatures;
		long index=0;
		for(auto &label:firstIndividual.getLabelsVector()){
			if(label[0]==1){
				aClassFeatures.push_back(firstIndividual.getFeaturesVector()[index]);
			}
			if(label[0]==0){
				bClassFeatures.push_back(firstIndividual.getFeaturesVector()[index]);
			}
			index++;
		}
		index = 0;
		for(auto &label:secondIndividual.getLabelsVector()){
			if(label[0]==1){
				aClassFeatures.push_back(secondIndividual.getFeaturesVector()[index]);
			}
			if(label[0]==0){
				bClassFeatures.push_back(secondIndividual.getFeaturesVector()[index]);
			}
			index++;
		}
		random_shuffle(aClassFeatures.begin(),aClassFeatures.end());
		random_shuffle(bClassFeatures.begin(),bClassFeatures.end());

		firstIndividual.getFeaturesVector().clear();
		firstIndividual.getLabelsVector().clear();
		secondIndividual.getFeaturesVector().clear();
		secondIndividual.getLabelsVector().clear();

		std::vector<double> one;
		one.push_back(1.0);
		std::vector<double> zero;
		zero.push_back(0.0);

		index = 0;
		while(index < aClassFeatures.size()/2){
			firstIndividual.getFeaturesVector().push_back(aClassFeatures[index]);
			firstIndividual.getLabelsVector().push_back(one);
			firstIndividual.getFeaturesVector().push_back(bClassFeatures[index]);
			firstIndividual.getLabelsVector().push_back(zero);
			index++;
		}
		firstIndividual.setSizeOfIndividual();
		while(index < aClassFeatures.size()){
			secondIndividual.getFeaturesVector().push_back(aClassFeatures[index]);
			secondIndividual.getLabelsVector().push_back(one);
			secondIndividual.getFeaturesVector().push_back(bClassFeatures[index]);
			secondIndividual.getLabelsVector().push_back(zero);
			index++;
		}
		secondIndividual.setSizeOfIndividual();
	}
}

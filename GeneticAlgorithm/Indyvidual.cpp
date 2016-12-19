//
// Created by Szymek on 15.12.2016.
//
#include "Indyvidual.h"
#include <iostream>
void Indyvidual::setFitnessScore(double &accuracy, long sizeOfTrainingSet){
	double tempSizeOfTrainingSet = sizeOfTrainingSet;
	double tempSizeOfIndyvidual = sizeOfIndyvidual;
	fitnessScore=1-(tempSizeOfIndyvidual/tempSizeOfTrainingSet);
}

void crossoverIndividual(double crossoverRatio, Indyvidual &firstIndividual, Indyvidual &secondIndividual){
	double randomRatio = (rand() % 100)/100;
	if (randomRatio < crossoverRatio){
		std::vector<std::vector<double>> tempVectorOfFeatures;
		std::vector<std::vector<double>> tempVectorOfLabels;
		tempVectorOfFeatures = firstIndividual.getFeaturesVector();
		tempVectorOfFeatures.insert(tempVectorOfFeatures.end(),
		                            secondIndividual.getFeaturesVector().begin(),
		                            secondIndividual.getFeaturesVector().end());
		tempVectorOfLabels = firstIndividual.getLabelsVector();
		tempVectorOfLabels.insert(tempVectorOfLabels.end(),
		                          secondIndividual.getLabelsVector().begin(),
		                          secondIndividual.getLabelsVector().end());
		firstIndividual.getFeaturesVector().clear();
		firstIndividual.getLabelsVector().clear();
		long int numberOfAClassFeatures = 0;
		long int numberOfBClassFeatures = 0;
		for(auto &label: tempVectorOfLabels){
			if(label[0] == 1){
				numberOfAClassFeatures++;
			}
			if(label[0] == 0){
				numberOfBClassFeatures++;
			}
		}
		long int numberOfPickedExamples = 0;
		while(numberOfPickedExamples <= numberOfAClassFeatures / 2){
			long randomNumber = (rand() % tempVectorOfFeatures.size());
			if(tempVectorOfLabels[randomNumber][0] == 1){
				firstIndividual.getFeaturesVector().push_back(tempVectorOfFeatures[randomNumber]);
				firstIndividual.getLabelsVector().push_back(tempVectorOfLabels[randomNumber]);
				numberOfPickedExamples++;
			}
		}
		numberOfPickedExamples = 0;
		while(numberOfPickedExamples <= numberOfBClassFeatures / 2){
			long randomNumber = (rand() % tempVectorOfLabels.size());
			if(tempVectorOfLabels[randomNumber][0] == 0){
				firstIndividual.getFeaturesVector().push_back(tempVectorOfFeatures[randomNumber]);
				firstIndividual.getLabelsVector().push_back(tempVectorOfLabels[randomNumber]);
				numberOfPickedExamples++;
			}
			secondIndividual.getFeaturesVector() = tempVectorOfFeatures;
			secondIndividual.getLabelsVector() = tempVectorOfLabels;
		}
	}

}


//
// Created by Szymek on 15.12.2016.
//
#include "Individual.h"
#include <iostream>

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

void crossoverIndividual(double crossoverRatio, Individual &firstIndividual, Individual &secondIndividual){
	double randomRatio = (rand() % 100) / 100.0;
	if(randomRatio < crossoverRatio){
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
			firstIndividual.setSizeOfIndividual();
			secondIndividual.setSizeOfIndividual();
			secondIndividual.getFeaturesVector() = tempVectorOfFeatures;
			secondIndividual.getLabelsVector() = tempVectorOfLabels;
		}
	}

}

//
// Created by Szymek on 15.12.2016.
//
#include "Individual.h"
#include <iostream>
#include <cmath>


long Individual::count = 0;


void clearIndividuals(Individual &firstIndividual, Individual &secondIndividual);

void separateFeatures(Individual &individual, vector<vector<double>> &aClassFeatures,
                      vector<vector<double>> &bClassFeatures);

void createNewDescendant(Individual &individual, const vector<vector<double>> &aClassFeatures,
                         const vector<vector<double>> &bClassFeatures, long &indexA, long &indexB);

void createNewDescendant(vector<Individual> &vectorOfIndividuals, double randomNumber,
                         const vector<vector<double>> &aClassFeatures, const vector<vector<double>> &bClassFeatures,
                         const vector<double> &one, const vector<double> &zero, Individual &newIndividual,
                         long newIndividualSize);

void Individual::setScore(double newScore) // needed just for debugging
{
	fitnessScore = newScore;
}

long Individual::getSizeOfIndividual(){
	return sizeOfIndividual;
};

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
	double randomNumber = (rand() % 100) / 100.0;
	if(randomNumber < crossoverRatio){

		std::vector<std::vector<double>> aClassFeatures;
		std::vector<std::vector<double>> bClassFeatures;

		separateFeatures(firstIndividual, aClassFeatures, bClassFeatures);
		separateFeatures(secondIndividual, aClassFeatures, bClassFeatures);

		random_shuffle(aClassFeatures.begin(), aClassFeatures.end());
		random_shuffle(bClassFeatures.begin(), bClassFeatures.end());

		clearIndividuals(firstIndividual, secondIndividual);

		long indexA = 0;
		long indexB = 0;

		createNewDescendant(firstIndividual, aClassFeatures, bClassFeatures, indexA, indexB);
		createNewDescendant(secondIndividual,aClassFeatures,bClassFeatures,indexA,indexB);
	}
}

void createNewDescendant(Individual &individual, const vector<vector<double>> &aClassFeatures,
                         const vector<vector<double>> &bClassFeatures, long &indexA, long &indexB){
	vector<double> one;
	vector<double> zero;
	one.push_back(1.0);
	zero.push_back(0.0);

	while(indexA < aClassFeatures.size() / 2){
			individual.getFeaturesVector().push_back(aClassFeatures[indexA]);
			individual.getLabelsVector().push_back(one);
			indexA++;
		}
	while(indexB < bClassFeatures.size() / 2){
			individual.getFeaturesVector().push_back(bClassFeatures[indexB]);
			individual.getLabelsVector().push_back(zero);
			indexB++;
		}
	individual.setSizeOfIndividual();
	individual.setSerialNumber();
}

void clearIndividuals(Individual &firstIndividual, Individual &secondIndividual){
	firstIndividual.getFeaturesVector().clear();
	firstIndividual.getLabelsVector().clear();
	secondIndividual.getFeaturesVector().clear();
	secondIndividual.getLabelsVector().clear();
}

void separateFeatures(Individual &individual, vector<vector<double>> &aClassFeatures,
                      vector<vector<double>> &bClassFeatures){
	long index = 0;
	for(auto &label:individual.getLabelsVector()){
		if(label[0] == 1){
			aClassFeatures.push_back(individual.getFeaturesVector()[index]);
		}
		if(label[0] == 0){
			bClassFeatures.push_back(individual.getFeaturesVector()[index]);
		}
		index++;
	}
}

Individual::Individual(){
	serialNumber = ++count;
}

Individual::Individual(vector<vector<double>> &featuresVector, vector<vector<double>> &labelsVector)
		: featuresVector(featuresVector), labelsVector(labelsVector){
	sizeOfIndividual = labelsVector.size();
	serialNumber = ++count;
}

void Individual::setSerialNumber(){
	serialNumber = ++count;
}

void crossoverForManyIndividuals(Individual &firstIndividual, Individual &secondIndividual,
                                 vector<Individual> &vectorOfIndividuals, Settings &settings){
	double randomNumber = (rand() % 100) / 100.0;
	if(randomNumber < settings.crossoverProbability){
		std::vector<std::vector<double>> aClassFeatures;
		std::vector<std::vector<double>> bClassFeatures;

		separateFeatures(firstIndividual, aClassFeatures, bClassFeatures);
		separateFeatures(secondIndividual, aClassFeatures, bClassFeatures);

		random_shuffle(aClassFeatures.begin(), aClassFeatures.end());
		random_shuffle(bClassFeatures.begin(), bClassFeatures.end());

		clearIndividuals(firstIndividual, secondIndividual);

		std::vector<double> one;
		one.push_back(1.0);
		std::vector<double> zero;
		zero.push_back(0.0);
		Individual newIndividual;

		long newIndividualSize = aClassFeatures.size();
		for(int loopControl = 0; loopControl < settings.numberOfDescendants; loopControl++){
			createNewDescendant(vectorOfIndividuals, randomNumber, aClassFeatures, bClassFeatures, one, zero,
			                    newIndividual, newIndividualSize);
		}
	}
}

void createNewDescendant(vector<Individual> &vectorOfIndividuals, double randomNumber,
                         const vector<vector<double>> &aClassFeatures, const vector<vector<double>> &bClassFeatures,
                         const vector<double> &one, const vector<double> &zero, Individual &newIndividual,
                         long newIndividualSize){
	for(int loopControl2 = 0; loopControl2 < (newIndividualSize); loopControl2 = loopControl2 + 2){
				randomNumber = round(rand() % aClassFeatures.size());
				newIndividual.getFeaturesVector().push_back(aClassFeatures[randomNumber]);
				newIndividual.getLabelsVector().push_back(one);
				newIndividual.getFeaturesVector().push_back(bClassFeatures[randomNumber]);
				newIndividual.getLabelsVector().push_back(zero);
			}
	newIndividual.setSizeOfIndividual();
	newIndividual.setSerialNumber();
	vectorOfIndividuals.push_back(newIndividual);
	newIndividual.getFeaturesVector().clear();
	newIndividual.getLabelsVector().clear();
}

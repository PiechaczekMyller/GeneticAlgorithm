//
// Created by Szymek on 15.12.2016.
//
#include "Individual.h"
#include <iostream>

void Individual::setScore(double newScore) // needed just for debugging
{
	fitnessScore = newScore;
}

void Individual::ChangeFeature(int index, vector<double> new_feature)
{
	featuresVector[index] = new_feature;
}

void Individual::ChangeLabel(int index, vector<double> new_label)
{
	labelsVector[index] = new_label;
}

double Individual::getFitnessScore()
{
	return fitnessScore;
}

void Individual::setFitnessScore(double &accuracy, long sizeOfTrainingSet){
	double tempSizeOfTrainingSet = sizeOfTrainingSet;
	double tempSizeOfIndyvidual = sizeOfIndividual;
	fitnessScore=1-(tempSizeOfIndyvidual/tempSizeOfTrainingSet);
}

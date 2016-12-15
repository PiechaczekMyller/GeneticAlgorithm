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

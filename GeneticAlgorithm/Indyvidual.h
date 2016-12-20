//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_INDYVIDUAL_H
#define GENETICALGORITHM_INDYVIDUAL_H

#include <vector>

class Indyvidual{
private:
	std::vector<std::vector<double>> featuresVector;
	std::vector<std::vector<double>> labelsVector;
	double fitnessScore = 0;
	long sizeOfIndyvidual;
public:


	Indyvidual(){ }

	Indyvidual(const std::vector<std::vector<double>> &featuresVector,
	           const std::vector<std::vector<double>> &labelsVector)
			: featuresVector(featuresVector), labelsVector(labelsVector){
		sizeOfIndyvidual = labelsVector.size();
	};

	std::vector<std::vector<double>> &getFeaturesVector(){
		return featuresVector;
	}

	std::vector<std::vector<double>> &getLabelsVector(){
		return labelsVector;
	}

	void setFitnessScore(double &accuracy, long sizeOfTrainingSet);

	friend void crossoverIndividual(double crossoverRatio, Indyvidual &firstIndividual, Indyvidual &secondIndividual);

	virtual ~Indyvidual(){ };
};


#endif //GENETICALGORITHM_INDYVIDUAL_H


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
public:


	Indyvidual(){ }

	Indyvidual(const std::vector<std::vector<double>> &featuresVector,
	           const std::vector<std::vector<double>> &labelsVector)
			: featuresVector(featuresVector), labelsVector(labelsVector){ };

	virtual ~Indyvidual(){ };
};


#endif //GENETICALGORITHM_INDYVIDUAL_H

//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_INDYVIDUAL_H
#define GENETICALGORITHM_INDYVIDUAL_H

#include <vector>

class Indyvidual{
private:
	std::vector<vector<double>> featuresVector;
	std::vector<vector<double>> labelsVector;
	double fitnessScore = 0;
public:


	Indyvidual(){ }

	Indyvidual(const vector<vector<double>> &featuresVector, const vector<vector<double>> &labelsVector)
			: featuresVector(featuresVector), labelsVector(labelsVector){ };

	virtual ~Indyvidual(){ };
};


#endif //GENETICALGORITHM_INDYVIDUAL_H

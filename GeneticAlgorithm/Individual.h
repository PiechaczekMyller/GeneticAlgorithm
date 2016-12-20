//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <vector>
using namespace std;

class Individual{
private:
	std::vector<std::vector<double>> featuresVector;
	std::vector<std::vector<double>> labelsVector;
	double fitnessScore = 0;
	long sizeOfIndividual;
public:

	Individual(){ }

    void setScore(double newScore);

	Individual(const vector<vector<double>> &featuresVector,
	           const vector<vector<double>> &labelsVector)
			: featuresVector(featuresVector), labelsVector(labelsVector){
		sizeOfIndividual=labelsVector.size();
	};

	const vector<vector<double>> &getFeaturesVector() const{
		return featuresVector;
	}

	const vector<vector<double>> &getLabelsVector() const{
		return labelsVector;
	};

    double getFitnessScore();

	void setFitnessScore(double &accuracy, long sizeOfTrainingSet);

	friend void crossoverIndividual(double crossoverRatio, Individual &firstIndividual, Individual &secondIndividual);

	virtual ~Individual(){ };

    void ChangeFeature(int index, vector<double> new_feature);

    void ChangeLabel(int index, vector<double> new_label);
};


#endif //GENETICALGORITHM_INDIVIDUAL_H


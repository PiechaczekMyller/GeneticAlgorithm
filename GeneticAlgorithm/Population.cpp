//
// Created by Szymek on 15.12.2016.
//

#include "Population.h"

void Population::setVectorOfIndividuals(vector<Individual> new_vector)
{
    vectorOfIndividuals = new_vector;
}

vector<Individual> Population::getVectorOfIndividuals()
{
    return vectorOfIndividuals;
}

void Population::createInitialPopulation(const int sizeOfPopulation, const Dataset<double, double> &trainingSet){
	for(int loopControl = 0; loopControl < sizeOfPopulation; loopControl++){
		std::vector<std::vector<double>> randomFeaturesVector;
		std::vector<std::vector<double>> labelsVector;
		const long datasetLength = trainingSet.getVectorOfLabels().size();
		const long randomLength = (rand() % datasetLength) / 2;
		for(int loopControl2 = 0; loopControl2 < randomLength; loopControl2 = loopControl2 + 2){
			addAClassExample(trainingSet, randomFeaturesVector, labelsVector);
			addBClassExample(trainingSet, randomFeaturesVector, labelsVector);
		}
		Individual newIndyvidual(randomFeaturesVector, labelsVector);
		vectorOfIndividuals.push_back(newIndyvidual);
	}
	std::cout << "Initial population created";
}

void Population::addBClassExample(const Dataset<double, double> &trainingSet,
                                  vector<vector<double>> &randomFeaturesVector,
                                  vector<vector<double>> &labelsVector) const{
	long bClassIndex = trainingSet.getRandomBClassIndex();
	randomFeaturesVector.push_back(trainingSet.getVectorOfFeatures()[bClassIndex]);
	labelsVector.push_back(trainingSet.getVectorOfLabels()[bClassIndex]);
}

void Population::addAClassExample(const Dataset<double, double> &trainingSet,
                                  vector<vector<double>> &randomFeaturesVector,
                                  vector<vector<double>> &labelsVector) const{
	long aClassIndex = trainingSet.getRandomAClassIndex();
	randomFeaturesVector.push_back(trainingSet.getVectorOfFeatures()[aClassIndex]);
	labelsVector.push_back(trainingSet.getVectorOfLabels()[aClassIndex]);
}

void Population::checkFitnessScores(const Dataset<double, double> &testSet, long sizeOfTrainingSet){
	vector<int> topology;
	setTopologyForNeuralNet(topology);
	double accuracy;
	for(auto &indyvidual:vectorOfIndividuals){
		NeuralNet newNet(topology, 0.9, false);
		newNet.PartialFit(indyvidual.getFeaturesVector(),
		                  indyvidual.getLabelsVector(),
		                  0.01);
		accuracy = newNet.CheckAccuracy(testSet);
		indyvidual.setFitnessScore(accuracy,sizeOfTrainingSet);
	}
}

void Population::crossover(double crossoverRatio){
	std::vector<Indvidual> newVectorOfIndyviduals;
	Indyvidual firstIndividual;
	Indyvidual secondIndividual;
	long randomNumber = 0;
	while(!vectorOfIndyviduals.empty()){
		randomNumber = (rand() % vectorOfIndyviduals.size());
		firstIndividual = vectorOfIndyviduals[randomNumber];
		vectorOfIndyviduals.erase(vectorOfIndyviduals.begin() + randomNumber);
		randomNumber = (rand() % (vectorOfIndyviduals.size()));
		secondIndividual = vectorOfIndyviduals[randomNumber];
		vectorOfIndyviduals.erase(vectorOfIndyviduals.begin() + (randomNumber));
		crossoverIndividual(crossoverRatio, firstIndividual, secondIndividual);
		newVectorOfIndyviduals.push_back(firstIndividual);
		newVectorOfIndyviduals.push_back(secondIndividual);
	}
	vectorOfIndyviduals = newVectorOfIndyviduals;
}

void Population::setTopologyForNeuralNet(vector<int> &topology) const{
	topology.push_back(26);
	topology.push_back(50);
	topology.push_back(1);
}

double Population::CalculateSumOfFitnessScores()
{
	double scores_sum = 0;
	for(auto &individual : vectorOfIndividuals)
	{
		scores_sum = scores_sum + individual.getFitnessScore();
	}
	return scores_sum;
}

vector<double> Population::CalculateWheelSegments(double scores_sum)
{
	vector<double> wheel_segments;
	wheel_segments.push_back(0.0);
	double individual_wheel_portion = 0;
    double last_element = 0;
	for (auto &individual : vectorOfIndividuals)
	{
		individual_wheel_portion = (individual.getFitnessScore() / scores_sum) * 100;
		last_element = wheel_segments.back() + individual_wheel_portion;
        wheel_segments.push_back(last_element);
	}
	return wheel_segments;
}

void Population::SelectionRouletteWheel()
{
	vector<int>indexes_of_chosen_individuals;
	double scores_sum = CalculateSumOfFitnessScores();
	vector<double> wheel_segments = CalculateWheelSegments(scores_sum);
	int random_number = 0;
    vector<Individual> new_population;
    new_population.reserve(vectorOfIndividuals.size());
    random_device rd;
	for(int loopControl = 0; loopControl < vectorOfIndividuals.size(); loopControl++)
	{
		mt19937 rng(rd());
		uniform_int_distribution<int> uni(0, int(wheel_segments.back()));
		random_number = uni(rng);
		for (int wheel_segment = 1; wheel_segment < wheel_segments.size(); wheel_segment++)
		{
			if(random_number > wheel_segments[wheel_segment - 1] && random_number < wheel_segments[wheel_segment])
				indexes_of_chosen_individuals.push_back(wheel_segment);
		}
	}
    for (int index = 0; index < indexes_of_chosen_individuals.size(); index++)
    {
        Individual new_individual = vectorOfIndividuals[indexes_of_chosen_individuals[index] -  1];
        new_population.push_back(new_individual);
    }
    this->setVectorOfIndividuals(new_population);
}

void Population::Mutation(double mutation_probability, Dataset<double,double> &training_set) {
	double random_int = 0;
	double random_feature_and_label = 0;
    random_device rd;
	for(auto &individual : this->vectorOfIndividuals)
	{
		for (int index = 0; index < individual.getLabelsVector().size(); index++)
		{
			mt19937 mt(rd());
			uniform_int_distribution<int> uni(0, 100);
			random_int = uni(mt);
            cout << random_int << endl;
			if (random_int < (mutation_probability * 100))
			{
                mt19937 rng(rd());
				uniform_int_distribution<int> unif(0, int(training_set.getVectorOfLabels().size()));
				random_feature_and_label = unif(rng);
                cout << random_feature_and_label << endl;
				individual.ChangeFeature(index, training_set.getVectorOfFeatures()[random_feature_and_label]);
				individual.ChangeLabel(index, training_set.getVectorOfLabels()[random_feature_and_label]);
			}
		}
	}
}

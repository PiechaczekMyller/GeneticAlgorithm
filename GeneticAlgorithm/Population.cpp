//
// Created by Szymek on 15.12.2016.
//

#include "Population.h"
#include "Settings.h"

void Population::setVectorOfIndividuals(vector<Individual> new_vector){
	vectorOfIndividuals = new_vector;
}

vector<Individual> Population::getVectorOfIndividuals(){
	return vectorOfIndividuals;
}

void Population::createInitialPopulation(const int sizeOfPopulation, const Dataset<double, double> &trainingSet){
	for(int loopControl = 0; loopControl < sizeOfPopulation; loopControl++){
		createRandomIndividual(trainingSet);
	}
	std::cout << "Initial population created" << std::endl;
}

void Population::createRandomIndividual(const Dataset<double, double> &trainingSet){
	vector<vector<double>> randomFeaturesVector;
	vector<vector<double>> labelsVector;
	const long datasetLength = trainingSet.getVectorOfLabels().size();
	const long randomLength = (rand() % datasetLength) / 2;
	for(int loopControl2 = 0; loopControl2 < randomLength; loopControl2 = loopControl2 + 2){
			addAClassExample(trainingSet, randomFeaturesVector, labelsVector);
			addBClassExample(trainingSet, randomFeaturesVector, labelsVector);
		}
	Individual newIndividual(randomFeaturesVector, labelsVector);
	vectorOfIndividuals.push_back(newIndividual);
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

void Population::checkFitnessScores(const Dataset<double, double> &testSet, long sizeOfTrainingSet, Settings settings){
	double accuracy;
	int index = 0;
	for(auto &individual:vectorOfIndividuals){

		NeuralNet newNet(settings.topology, settings.learningRate, false);
		newNet.PartialFit(individual.getFeaturesVector(), individual.getLabelsVector(), 0.01, 0.00001,
		                  true);
		accuracy = newNet.CheckAccuracy(testSet);
		individual.setAccuracy(accuracy);
		individual.setFitnessScore(accuracy, sizeOfTrainingSet, settings.weightForSize, settings.weightForAccuracy);
		index++;

	}
}


void Population::crossover(double crossoverRatio){
	cout << "crossover now" << endl;
	std::vector<Individual> newVectorOfIndividuals;
	Individual firstIndividual;
	Individual secondIndividual;
	long randomNumber = 0;
	while(vectorOfIndividuals.size() > 1){
		randomNumber = (rand() % vectorOfIndividuals.size());
		firstIndividual = vectorOfIndividuals[randomNumber];
		vectorOfIndividuals.erase(vectorOfIndividuals.begin() + randomNumber);
		randomNumber = (rand() % (vectorOfIndividuals.size()));
		secondIndividual = vectorOfIndividuals[randomNumber];
		vectorOfIndividuals.erase(vectorOfIndividuals.begin() + (randomNumber));
		crossoverIndividuals(settings.crossoverProbability, firstIndividual, secondIndividual);
		newVectorOfIndividuals.push_back(firstIndividual);
		if (settings.twoDescendants)
			newVectorOfIndividuals.push_back(secondIndividual);
	}
	vectorOfIndividuals.insert(vectorOfIndividuals.end(), newVectorOfIndividuals.begin(), newVectorOfIndividuals.end());
}


double Population::CalculateSumOfFitnessScores(){
	double scores_sum = 0;
	for(auto &individual : vectorOfIndividuals){
		scores_sum = scores_sum + individual.getFitnessScore();
	}
	return scores_sum;
}

vector<double> Population::CalculateWheelSegments(double scores_sum){
	vector<double> wheel_segments;
	wheel_segments.push_back(0.0);
	double individual_wheel_portion = 0;
	double last_element = 0;
	for(auto &individual : vectorOfIndividuals){
		individual_wheel_portion = (individual.getFitnessScore() / scores_sum) * 100;
		last_element = wheel_segments.back() + individual_wheel_portion;
		wheel_segments.push_back(last_element);
	}
	return wheel_segments;
}

void Population::SelectionRouletteWheel(){
	cout << "selection now" << endl;
	vector<int> indexes_of_chosen_individuals;
	double scores_sum = CalculateSumOfFitnessScores();
	vector<double> wheel_segments = CalculateWheelSegments(scores_sum);
	int random_number = 0;
	vector<Individual> new_population;
	new_population.reserve(vectorOfIndividuals.size());
	random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, int(wheel_segments.back()));
	for(int loopControl = 0; loopControl < vectorOfIndividuals.size(); loopControl++){
		random_number = uni(rng);
		for(int wheel_segment = 1; wheel_segment < wheel_segments.size(); wheel_segment++){
			if(random_number > wheel_segments[wheel_segment - 1] && random_number < wheel_segments[wheel_segment])
				indexes_of_chosen_individuals.push_back(wheel_segment);
		}
	}
	for(int index = 0; index < indexes_of_chosen_individuals.size(); index++){
		Individual new_individual = vectorOfIndividuals[indexes_of_chosen_individuals[index] - 1];
		new_population.push_back(new_individual);
	}
	this->setVectorOfIndividuals(new_population);
}

void Population::Mutation(double mutation_probability, Dataset<double, double> &training_set){
	cout << "mutation now" << endl;
	double random_int = 0;
	double random_feature_and_label = 0;
	random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> uni(0, 100);
    mt19937 rng(rd());
    uniform_int_distribution<int> unif(0, int(training_set.getVectorOfLabels().size()));
	for(auto &individual : this->vectorOfIndividuals){
		for(int index = 0; index < individual.getLabelsVector().size(); index++){
			random_int = uni(mt);
			if(random_int < (mutation_probability * 100)){
				random_feature_and_label = unif(rng);
				individual.ChangeFeature(index, training_set.getVectorOfFeatures()[random_feature_and_label]);
				individual.ChangeLabel(index, training_set.getVectorOfLabels()[random_feature_and_label]);
			}
		}
	}
}

void Population::setBestFitnessScore(){
	for(auto &individual:vectorOfIndividuals){
		if(individual.getFitnessScore() > bestFitnessScore){
			bestFitnessScore = individual.getFitnessScore();

		}
	}
}

void Population::resetBestFitnessScore(){
	bestFitnessScore = 0;
}

void Population::compensate(Dataset<double, double> &training_set, Settings settings){
	long difference = settings.populationSize - this->getVectorOfIndividuals().size();
	if(difference > 0){
		while(difference > 0){
			this->createRandomIndividual(training_set);
			difference = -1;
		}
	}
}

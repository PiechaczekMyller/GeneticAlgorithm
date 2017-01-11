//
// Created by Szymek on 15.12.2016.
//

#include "Population.h"
#include "Settings.h"
#include <math.h>

void Population::setVectorOfIndividuals(vector<Individual> new_vector){
	vectorOfIndividuals = new_vector;
}

vector<Individual> &Population::getVectorOfIndividuals(){
	return vectorOfIndividuals;
}

void Population::createInitialPopulation(const int sizeOfPopulation, const Dataset<double, double> &trainingSet,
                                         Settings settings){
	for(int loopControl = 0; loopControl < sizeOfPopulation; loopControl++){
		createRandomIndividual(trainingSet, settings);
	}
	std::cout << "Initial population created" << std::endl;
}

void Population::createRandomIndividual(const Dataset<double, double> &trainingSet, Settings &settings){
	vector<vector<double>> randomFeaturesVector;
	vector<vector<double>> labelsVector;
	const long datasetLength = trainingSet.getVectorOfLabels().size();
	double individualSize=0;
	if(settings.individualSize == 0)
		individualSize = (rand() % datasetLength) / 2;
	else if(settings.individualSize > 1)
		individualSize = settings.individualSize;
	else if(settings.individualSize < 1){
		individualSize = round(settings.individualSize * datasetLength);
		}
	for(int loopControl2 = 0; loopControl2 < individualSize; loopControl2 = loopControl2 + 2){
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

		NeuralNet newNet(settings.topology, settings.learningRate, settings.accuracy, settings.tolerance, false);
		newNet.PartialFit(individual.getFeaturesVector(), individual.getLabelsVector(), false);
		accuracy = newNet.CheckAccuracy(testSet);
		individual.setAccuracy(accuracy);
		individual.setFitnessScore(accuracy, sizeOfTrainingSet, settings.weightForSize, settings.weightForAccuracy);
		index++;

	}
}


void Population::crossover(Settings settings){
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
		if(settings.twoDescendants){
			newVectorOfIndividuals.push_back(secondIndividual);
		}
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
	uniform_int_distribution<long> unif(0, int(training_set.getVectorOfLabels().size() - 1));
	for(auto &individual : this->vectorOfIndividuals){
		for(int index = 0; index < individual.getSizeOfIndividual(); index++){
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
	maxFitnessScore = 0;
	for(auto &individual:vectorOfIndividuals){
		if(individual.getFitnessScore() > maxFitnessScore){
			maxFitnessScore = individual.getFitnessScore();

		}
	}
}

void Population::resetBestFitnessScore(){
	maxFitnessScore = 0;
}

void Population::compensate(Dataset<double, double> &training_set, Settings settings){
	long difference = settings.populationSize - this->getVectorOfIndividuals().size();
	if(difference > 0){
		while(difference > 0){
			this->createRandomIndividual(training_set, settings);
			difference = -1;
		}
	}
}


void Population::sortByFitness(){
	std::sort(vectorOfIndividuals.begin(), vectorOfIndividuals.end(),
	          [ ](Individual &l, Individual &r){ return l.getFitnessScore() > r.getFitnessScore(); });
}

void Population::operator=(Population populationToSave){
	vectorOfIndividuals = populationToSave.vectorOfIndividuals;
	maxFitnessScore = populationToSave.maxFitnessScore;

}

Population::Population(const Population &populationToSave){
	vectorOfIndividuals = populationToSave.vectorOfIndividuals;
	maxFitnessScore = populationToSave.maxFitnessScore;
}

void Population::SurvivorSelection(int populationSize){
	vector<Individual> survivors;
	for(int i = 0; i < populationSize; i++){
		survivors.push_back(vectorOfIndividuals[i]);
	}
	vectorOfIndividuals = survivors;
}

void Population::setStats(){
	setBestFitnessScore();
	setMeanFitness();
	setWorstFitness();
	setMaxLength();
	setMinLength();
	setMeanLength();
	setMaxAccuracy();
	setMinAccuracy();
	setMeanAccuracy();
}

void Population::setWorstFitness(){
	minFitnessScore = 2;
	for(auto &individual:vectorOfIndividuals){
		if(individual.getFitnessScore() < minFitnessScore){
			minFitnessScore = individual.getFitnessScore();

		}
	}
}

void Population::setMeanFitness(){
	meanFitnessScore = 0;
	double sum = 0;
	for(auto &individual:vectorOfIndividuals){
		sum = sum + individual.getFitnessScore();
	}
	meanFitnessScore = (sum / vectorOfIndividuals.size());
}

void Population::setMaxLength(){
	maxLenght = 0;
	for(auto &individual:vectorOfIndividuals){
		if(individual.getFeaturesVector().size() > maxLenght){
			maxLenght = individual.getFeaturesVector().size();

		}
	}
}

void Population::setMinLength(){
	minLength = vectorOfIndividuals[0].getFeaturesVector().size();
	for(auto &individual:vectorOfIndividuals){
		if(individual.getFeaturesVector().size() < minLength){
			minLength = individual.getFeaturesVector().size();

		}
	}
}

void Population::setMeanLength(){
	meanLength = 0;
	double sum = 0;
	for(auto &individual:vectorOfIndividuals){
		sum = sum + individual.getFeaturesVector().size();
	}
	meanLength = (sum / vectorOfIndividuals.size());
}

void Population::setMaxAccuracy(){
	maxAccuracy = 0;
	for(auto &individual:vectorOfIndividuals){
		if(individual.getAccuracy() > maxAccuracy){
			maxAccuracy = individual.getAccuracy();

		}
	}
}

void Population::setMinAccuracy(){
	minAccuracy = 2;
	for(auto &individual:vectorOfIndividuals){
		if(individual.getAccuracy() < maxAccuracy){
			minAccuracy = individual.getAccuracy();
		}
	}
}

void Population::setMeanAccuracy(){
	meanAccuracy = 0;
	double sum = 0;
	for(auto &individual:vectorOfIndividuals){
		sum = sum + individual.getAccuracy();
	}
	meanAccuracy = (sum / vectorOfIndividuals.size());
}

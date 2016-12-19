cmake_minimum_required(VERSION 3.3.2)
project(GeneticAlgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Neural_Net/NeuralNet.cpp Neural_Net/NeuralNet.h Neural_Net/Neuron.cpp Neural_Net/Neuron.h Dataset.h LoadingDatasetFunctions.cpp LoadingDatasetFunctions.h GeneticAlgorithm/Population.h GeneticAlgorithm/Population.cpp GeneticAlgorithm/GeneticAlgorithm.h GeneticAlgorithm/GeneticAlgorithm.cpp GeneticAlgorithm/Individual.h GeneticAlgorithm/Individual.cpp GeneticAlgorithm/Settings.h Exceptions/DifferentSizesOfVectors.cpp Exceptions/DifferentSizesOfVectors.h Exceptions/WrongParameterRange.cpp Exceptions/WrongParameterRange.h)

add_executable(GeneticAlgorithm ${SOURCE_FILES})
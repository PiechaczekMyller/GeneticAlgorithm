cmake_minimum_required(VERSION 3.3.2)
project(GeneticAlgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Neural_Net/NeuralNet.cpp Neural_Net/NeuralNet.h Neural_Net/Connection.cpp Neural_Net/Connection.h Neural_Net/Neuron.cpp Neural_Net/Neuron.h Neural_Net/Layer.cpp Neural_Net/Layer.h Dataset.h Exceptions/FeaturesLabesLenNotEqualExc.cpp Exceptions/FeaturesLabesLenNotEqualExc.h LoadingDatasetFunctions.cpp LoadingDatasetFunctions.h GeneticAlgorithm/Population.h GeneticAlgorithm/Algorithm.h GeneticAlgorithm/GeneticAlgorithm.h GeneticAlgorithm/Gene.h GeneticAlgorithm/Indyvidual.h)

add_executable(GeneticAlgorithm ${SOURCE_FILES})
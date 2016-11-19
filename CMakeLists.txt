cmake_minimum_required(VERSION 3.3.2)
project(GeneticAlgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp NeuralNet.cpp NeuralNet.h Connection.cpp Connection.h Neuron.cpp Neuron.h Layer.cpp Layer.h Dataset.h Exceptions/FeaturesLabesLenNotEqualExc.cpp Exceptions/FeaturesLabesLenNotEqualExc.h LoadingDatasetFunctions.cpp LoadingDatasetFunctions.h Population.cpp Population.h Genome.cpp Genome.h Algorithm.cpp Algorithm.h GeneticAlgorithm.cpp GeneticAlgorithm.h Gene.cpp Gene.h Indyvidual.cpp Indyvidual.h)

add_executable(GeneticAlgorithm ${SOURCE_FILES})
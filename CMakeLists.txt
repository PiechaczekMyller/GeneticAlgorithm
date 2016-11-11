cmake_minimum_required(VERSION 3.3.2)
project(GeneticAlgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Net.cpp Net.h Connection.cpp Connection.h Neuron.cpp Neuron.h Layer.cpp Layer.h Dataset.h Exceptions/FeaturesLabesLenNotEqualExc.cpp Exceptions/FeaturesLabesLenNotEqualExc.h)
add_executable(GeneticAlgorithm ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.6)
project(GeneticAlgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp NeuralNet.cpp NeuralNet.h Connection.cpp Connection.h Neuron.cpp Neuron.h Layer.cpp Layer.h MathFunctions.h)
add_executable(GeneticAlgorithm ${SOURCE_FILES})
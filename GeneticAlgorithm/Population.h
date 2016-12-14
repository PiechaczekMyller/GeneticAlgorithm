//
// Created by Szymek on 13.11.2016.
//

#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include <iostream>
#include <vector>
#include "Indyvidual.h"

class Population{
private:
	std::vector<Indyvidual> vectorOfIndyviduals;
public:

	Population(){ }

	Population(const vector<Indyvidual> &vectorOfIndyviduals) : vectorOfIndyviduals(vectorOfIndyviduals){ }

	virtual ~Population(){ };
};

#endif //GENETICALGORITHM_POPULATION_H

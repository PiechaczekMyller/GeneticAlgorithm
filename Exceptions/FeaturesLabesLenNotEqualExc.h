//
// Created by Szymek on 09.11.2016.
//

#ifndef GENETICALGORITHM_FEATURESLABESLENNOTEQUALEXC_H
#define GENETICALGORITHM_FEATURESLABESLENNOTEQUALEXC_H


#include <exception>
#include <stdexcept>

class FeaturesLabesLenNotEqualExc:public std::logic_error{
public:
	FeaturesLabesLenNotEqualExc(): std::logic_error("Features and labels vectors are not equal in length"){};
	virtual const char *what() const noexcept override;
};


#endif //GENETICALGORITHM_FEATURESLABESLENNOTEQUALEXC_H

//
// Created by user on 2016-12-18.
//

#ifndef GENETICALGORITHM_WRONGPARAMETERRANGE_H
#define GENETICALGORITHM_WRONGPARAMETERRANGE_H

#include <iostream>
#include <exception>
#include <string>
using namespace std;
class WrongParameterRange : public exception{
private:
    string Reason;
public:
    WrongParameterRange(const char* why):Reason(why) {}
    const char* what() const throw();
};


#endif //GENETICALGORITHM_WRONGPARAMETERRANGE_H

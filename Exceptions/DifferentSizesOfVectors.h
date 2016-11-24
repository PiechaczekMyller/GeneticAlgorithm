//
// Created by user on 2016-11-24.
//

#ifndef GENETICALGORITHM_DIFFERENTSIZESOFVECTORS_H
#define GENETICALGORITHM_DIFFERENTSIZESOFVECTORS_H
#include <exception>
#include <string>
using namespace std;
class DifferentSizesOfVectors : public exception{
    string Reason;
public:
    DifferentSizesOfVectors(const char* why):Reason(why) {}
    const char* what() const throw();
};


#endif //GENETICALGORITHM_DIFFERENTSIZESOFVECTORS_H

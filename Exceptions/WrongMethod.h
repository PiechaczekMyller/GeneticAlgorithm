//
// Created by user on 2016-12-20.
//

#ifndef GENETICALGORITHM_WRONGMETHOD_H
#define GENETICALGORITHM_WRONGMETHOD_H

#include <iostream>
#include <exception>
#include <string>
#include <vector>
using namespace std;
class WrongMethod : public exception {
private:
    string invalid_method;
    vector<string> possible_methods;
public:
    WrongMethod(string invalid_method, vector<string> possible_methods): invalid_method(invalid_method), possible_methods(possible_methods) {}
    const char* what() const throw();
};


#endif //GENETICALGORITHM_WRONGMETHOD_H

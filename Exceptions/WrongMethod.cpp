//
// Created by user on 2016-12-20.
//

#include "WrongMethod.h"

const char* WrongMethod::what() const throw(){
    cout << "Method " << invalid_method << " does not exist" << endl;
    cout << "Possible methods: " << endl;
    for (auto &method : possible_methods)
    {
        cout << method << endl;
    }
    return "";
}
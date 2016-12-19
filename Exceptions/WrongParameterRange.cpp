//
// Created by user on 2016-12-18.
//

#include "WrongParameterRange.h"

const char* WrongParameterRange::what() const throw(){
    return Reason.c_str();
}

//
// Created by Szymek on 09.11.2016.
//

#include "FeaturesLabesLenNotEqualExc.h"

const char *FeaturesLabesLenNotEqualExc::what() const noexcept{
	return std::logic_error::what();
}

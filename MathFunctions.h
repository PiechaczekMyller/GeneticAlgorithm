#ifndef GENETICALGORITHM_MATHFUNCTIONS_H
#define GENETICALGORITHM_MATHFUNCTIONS_H
#include <cmath>
const double BETA = 1;

double ActivationFunction(double NeuronOutput)
{
	return 1 / (1 + exp(-BETA * NeuronOutput));
}

double CalculateDerivative(double Input)
{
	return	Input * (1 - Input);
}
#endif //GENETICALGORITHM_MATHFUNCTIONS_H

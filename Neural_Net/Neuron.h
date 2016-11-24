//
// Created by myychal on 2016-11-06.
//

#ifndef NEURALNETGA_NEURON_H
#define NEURALNETGA_NEURON_H
#include <iostream>
#include <cmath>

class Neuron {
private:
    double Input;
    double Output;
    double Squared_Error;
public:
    Neuron();

    double get_Input() const;

    void set_Input(double m_Input);

    double get_Output() const;

    void set_Output(double m_Output);

    double get_Squared_Error() const;

    void set_Squared_Error(double m_SquaredError);

    virtual ~Neuron();

    void AddToInput(double Value);

    double ActivationFunction();
};


#endif //NEURALNETGA_NEURON_H

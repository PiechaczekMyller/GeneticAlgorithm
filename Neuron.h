//
// Created by myychal on 2016-11-06.
//

#ifndef NEURALNETGA_NEURON_H
#define NEURALNETGA_NEURON_H
#include <iostream>

class Neuron {
private:
    double m_Input;
    double m_Output;
    double m_SquaredError;
public:
    Neuron();

    double getM_Input() const;

    void setM_Input(double m_Input);

    double getM_Output() const;

    void setM_Output(double m_Output);

    double getM_SquaredError() const;

    void setM_SquaredError(double m_SquaredError);

    virtual ~Neuron();

    void AddValue(double Value);
};


#endif //NEURALNETGA_NEURON_H

//
// Created by user on 2016-11-06.
//
#include "Neuron.h"

Neuron::Neuron() {
    m_Input = 0;
    m_Output = 0;
    m_SquaredError = 0;
}

double Neuron::getM_Input() const {
    return m_Input;
}

void Neuron::setM_Input(double m_Input) {
    Neuron::m_Input = m_Input;
}

double Neuron::getM_Output() const {
    return m_Output;
}

void Neuron::setM_Output(double m_Output) {
    Neuron::m_Output = m_Output;
}

double Neuron::getM_SquaredError() const {
    return m_SquaredError;
}

void Neuron::setM_SquaredError(double m_SquaredError) {
    Neuron::m_SquaredError = m_SquaredError;
}

void Neuron::AddValue (double Value)
{
     this->setM_Input(this->getM_Input() + Value);
}
Neuron::~Neuron() {

}

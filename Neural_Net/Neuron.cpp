//
// Created by user on 2016-11-06.
//
#include "Neuron.h"
const double BETA = 1;

Neuron::Neuron() {
    Input = 0;
    Output = 0;
    Squared_Error = 0;
}

double Neuron::get_Input() const {
    return Input;
}

void Neuron::set_Input(double m_Input) {
    Neuron::Input = m_Input;
}

double Neuron::get_Output() const {
    return Output;
}

void Neuron::set_Output(double m_Output) {
    Neuron::Output = m_Output;
}

double Neuron::get_Squared_Error() const {
    return Squared_Error;
}

void Neuron::set_Squared_Error(double m_SquaredError) {
    Neuron::Squared_Error = m_SquaredError;
}

void Neuron::AddToInput(double newValue)
{
     Input = Input + newValue;
}

double Neuron::ActivationFunction(){
    double new_output = 1 / (1 + exp(-BETA * Input));
    Output = new_output;
}
Neuron::~Neuron() {

}

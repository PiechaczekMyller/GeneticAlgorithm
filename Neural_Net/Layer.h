//
// Created by myychal on 2016-11-06.
//

#ifndef NEURALNETGA_LAYER_H
#define NEURALNETGA_LAYER_H

#include <iostream>
#include <vector>
#include "Neuron.h"
using namespace std;

class Layer {
private:
    vector<Neuron> Neurons_Layer;
public:
    Layer(int);

    vector<Neuron> &get_Neurons_Layer();

    void set_Neurons_Layer(const vector<Neuron> &m_NeuronsLayer);

    virtual ~Layer();
};


#endif //NEURALNETGA_LAYER_H

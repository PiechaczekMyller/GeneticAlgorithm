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
    vector<Neuron> m_NeuronsLayer;
public:
    Layer(int);

    vector<Neuron> &getM_NeuronsLayer();

    void setM_NeuronsLayer(const vector<Neuron> &m_NeuronsLayer);

    virtual ~Layer();
};


#endif //NEURALNETGA_LAYER_H

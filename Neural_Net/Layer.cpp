//
// Created by user on 2016-11-06.
//

#include "Layer.h"

vector<Neuron> &Layer::get_Neurons_Layer() {
    return Neurons_Layer;
}

void Layer::set_Neurons_Layer(const vector<Neuron> &m_NeuronsLayer) {
    Layer::Neurons_Layer = m_NeuronsLayer;
}

Layer::Layer(int NumberOfNeurons) {
    vector<Neuron> temp_neurons_layer;
    for(int i = 0; i < NumberOfNeurons; i++)
    {
        Neuron myNeuron;
        temp_neurons_layer.push_back(myNeuron);
    }
    set_Neurons_Layer(temp_neurons_layer);
}

Layer::~Layer() {}

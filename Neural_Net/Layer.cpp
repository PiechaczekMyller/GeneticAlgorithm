//
// Created by user on 2016-11-06.
//

#include "Layer.h"

vector<Neuron> &Layer::getM_NeuronsLayer() {
    return m_NeuronsLayer;
}

void Layer::setM_NeuronsLayer(const vector<Neuron> &m_NeuronsLayer) {
    Layer::m_NeuronsLayer = m_NeuronsLayer;
}

Layer::Layer(int NumberOfNeurons) {
    vector<Neuron> TempNeuronsLayer;
    for(int i = 0; i < NumberOfNeurons; i++)
    {
        Neuron myNeuron;
        TempNeuronsLayer.push_back(myNeuron);
    }
    setM_NeuronsLayer(TempNeuronsLayer);
}

Layer::~Layer() {

}

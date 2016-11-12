//
// Created by myychal on 2016-11-06.
//

#ifndef NEURALNETGA_NET_H
#define NEURALNETGA_NET_H
#include <iostream>
#include <vector>
#include "Connection.h"
#include "Layer.h"
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

class NeuralNet {
private:
    vector<vector<Connection>> m_Connections;
    vector<Layer> m_Layers;
    vector<int> Topology;
public:
    NeuralNet(vector<int>);

    void CreateLayers();

    vector<vector<Connection>> &getM_Connections();

    vector<Layer> &getM_Layers();

    void setM_Connections(const vector<vector<Connection>> &m_ConnectionsVector);

    void setM_Layers(const vector<Layer> &m_LayersVector);

    void CreateConnections();

    virtual ~NeuralNet();

    void ProcessDataForward();

    void ChangeOutputsInInputLayer(vector<double> NewOutputs);

    void SetOutputOfBiasNeuron(double);
};


#endif //NEURALNETGA_NET_H

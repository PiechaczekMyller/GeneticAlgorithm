//
// Created by myychal on 2016-11-06.
//

#ifndef NEURALNETGA_NET_H
#define NEURALNETGA_NET_H
#include <iostream>
#include <vector>
#include <exception>
#include "Connection.h"
#include "Layer.h"
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

class NeuralNet {
private:
    vector<vector<Connection>> Connections;
    vector<Layer> Layers;
    vector<int> Topology;
public:
    NeuralNet(vector<int>);

    void CreateLayers();

    vector<vector<Connection>> &get_Connections();

    vector<Layer> &get_Layers();

    void set_Connections(const vector<vector<Connection>> &m_ConnectionsVector);

    void set_Layers(const vector<Layer> &m_LayersVector);

    void CreateConnections();

    virtual ~NeuralNet();

    void ProcessDataForward();

    void ChangeOutputsInInputLayer(vector<double> new_outputs);

    void SetOutputOfBiasNeuron(double);

    void BackPropagation();
};


#endif //NEURALNETGA_NET_H

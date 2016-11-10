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

    void CreateLayers(vector<int>);

    const vector<vector<Connection>> &getM_Connections() const;

    const vector<Layer> &getM_Layers() const;

    void setM_Connections(const vector<vector<Connection>> &m_ConnectionsVector);

    void setM_Layers(const vector<Layer> &m_LayersVector);

    void CreateConnections(vector<int> Topology);

    virtual ~NeuralNet();

    void ProcessDataForward();
};


#endif //NEURALNETGA_NET_H

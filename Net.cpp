//
// Created by user on 2016-11-06.
//

#include "Net.h"

Net::Net(vector<int> Topology) {
    CreateLayers(Topology);
    CreateConnections(Topology);
}
const vector<vector<Connection>> &Net::getM_Connections() const {
    return m_Connections;
}

const vector<Layer> &Net::getM_Layers() const {
    return m_Layers;
}

void Net::setM_Connections(const vector<vector<Connection>> &m_ConnectionsVector) {
    Net::m_Connections = m_ConnectionsVector;
}

void Net::setM_Layers(const vector<Layer> &m_LayersVector) {
    Net::m_Layers = m_LayersVector;
}

void Net::CreateLayers(vector<int> Topology) {
    vector<Layer> TempLayerVector;
    int LayersCounter = 0;
    Layer InputLayer(Topology[LayersCounter]);
    TempLayerVector.push_back(InputLayer);
    for (int i = 0; i < Topology.size() - 2; i++)
    {
        LayersCounter++;
        Layer HiddenLayer(Topology[LayersCounter]);
        TempLayerVector.push_back(HiddenLayer);
    }
    Layer OutputLayer(Topology[LayersCounter]);
    TempLayerVector.push_back(OutputLayer);
    this->setM_Layers(TempLayerVector);
}

void Net::CreateConnections(vector<int> Topology){
    vector<vector<Connection>> TempConnections;
    int min = -5;
    int max = 5;
    double RandomWeight = 0;
    for(int i = 0; i < Topology.size() - 1; i++)
    {
        vector<Connection> ConnectionsVector;
        for(int j = 0; j < Topology[i] * Topology[i + 1]; j++)
        {
            random_device rd;
            mt19937 rng(rd());
            uniform_int_distribution<int> uni(min, max);
            RandomWeight = uni(rng);
            RandomWeight = RandomWeight / 10;
            Connection myConnection(RandomWeight);
            ConnectionsVector.push_back(myConnection);
        }
        TempConnections.push_back(ConnectionsVector);
    }
    this->setM_Connections(TempConnections);
}

Net::~Net() {}


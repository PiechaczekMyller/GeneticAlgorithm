//
// Created by user on 2016-11-06.
//

#include "NeuralNet.h"
const int InputAndOutputLayers = 2;

NeuralNet::NeuralNet(vector<int> Topology) {
    this->Topology = Topology;
    CreateLayers(Topology);
    CreateConnections(Topology);
}

const vector<vector<Connection>> &NeuralNet::getM_Connections() const {
    return m_Connections;
}

const vector<Layer> &NeuralNet::getM_Layers() const {
    return m_Layers;
}

void NeuralNet::setM_Connections(const vector<vector<Connection>> &m_ConnectionsVector) {
    NeuralNet::m_Connections = m_ConnectionsVector;
}

void NeuralNet::setM_Layers(const vector<Layer> &m_LayersVector) {
    NeuralNet::m_Layers = m_LayersVector;
}

void NeuralNet::CreateLayers(vector<int> Topology) {
    vector<Layer> TempLayerVector;
    int LayersCounter = 0;
    Layer InputLayer(Topology[LayersCounter]);
    TempLayerVector.push_back(InputLayer);
    for (int i = 0; i < Topology.size() - InputAndOutputLayers; i++)
    {
        LayersCounter++;
        Layer HiddenLayer(Topology[LayersCounter]);
        TempLayerVector.push_back(HiddenLayer);
    }
    LayersCounter++;
    Layer OutputLayer(Topology[LayersCounter]);
    TempLayerVector.push_back(OutputLayer);
    this->setM_Layers(TempLayerVector);
}

void NeuralNet::CreateConnections(vector<int> Topology){
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

void NeuralNet::ProcessDataForward()
{
    double SingleInput = 0;
    int ConnectionsCounter = 0;
    for (int ProcessedLayer = 0; ProcessedLayer < this->getM_Connections().size(); ProcessedLayer++)
    {
        for(int RightLayerNeuron = 0; RightLayerNeuron < this->getM_Layers()[ProcessedLayer + 1].getM_NeuronsLayer().size(); RightLayerNeuron++)
        {
            for(int LeftLayerNeuron = 0; LeftLayerNeuron < this->getM_Layers()[ProcessedLayer].getM_NeuronsLayer().size(); LeftLayerNeuron++)
            {
                SingleInput = this->getM_Connections()[ProcessedLayer][ConnectionsCounter].getM_Weight() * this->getM_Layers()[ProcessedLayer].getM_NeuronsLayer()[LeftLayerNeuron].getM_Output();
            }
        }
    }
}
NeuralNet::~NeuralNet() {}


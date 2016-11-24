//
// Created by user on 2016-11-06.
//

#include "NeuralNet.h"
#include "MathFunctions.h"
const int InputAndOutputLayers = 2;
int BIAS_NEURON = 1;

NeuralNet::NeuralNet(vector<int> Topology) {
    this->Topology = Topology;
    CreateLayers();
    CreateConnections();
}

vector<vector<Connection>> &NeuralNet::getM_Connections() {
    return m_Connections;
}

vector<Layer> &NeuralNet::getM_Layers() {
    return m_Layers;
}

void NeuralNet::setM_Connections(const vector<vector<Connection>> &m_ConnectionsVector) {
    NeuralNet::m_Connections = m_ConnectionsVector;
}

void NeuralNet::setM_Layers(const vector<Layer> &m_LayersVector) {
    NeuralNet::m_Layers = m_LayersVector;
}

void NeuralNet::CreateLayers() {
    vector<Layer> TempLayerVector;
    int LayersCounter = 0;
    Layer InputLayer(Topology[LayersCounter]);
    TempLayerVector.push_back(InputLayer);
    for (int i = 0; i < Topology.size() - InputAndOutputLayers; i++)
    {
        LayersCounter++;
        Layer HiddenLayer(Topology[LayersCounter] + BIAS_NEURON);
        TempLayerVector.push_back(HiddenLayer);
    }
    LayersCounter++;
    Layer OutputLayer(Topology[LayersCounter]);
    TempLayerVector.push_back(OutputLayer);
    this->setM_Layers(TempLayerVector);
}

void NeuralNet::CreateConnections(){
    vector<vector<Connection>> TempConnections;
    int min = -5;
    int max = 5;
    double RandomWeight = 0;
    for(int Connections = 0; Connections < Topology.size() - 1; Connections++)
    {
        vector<Connection> ConnectionsVector;
        if (Connections == 0) //check if first layer
            BIAS_NEURON = 0;
        else
            BIAS_NEURON = 1;
        for(int j = 0; j < (Topology[Connections] + BIAS_NEURON) * Topology[Connections + 1]; j++)
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

void NeuralNet::SetOutputOfBiasNeuron(double Output)
{
    for (int HiddenLayer = 1; HiddenLayer <= Topology.size() - InputAndOutputLayers; HiddenLayer++)
    {
     this->getM_Layers()[HiddenLayer].getM_NeuronsLayer().back().setM_Output(Output);
    }
}

void NeuralNet::ProcessDataForward()
{
    double SingleInput = 0;
    int ConnectionsCounter = 0;
    double NewNeuronOutput = 0;
    for (int ProcessedLayer = 0; ProcessedLayer < this->getM_Connections().size(); ProcessedLayer++)
    {
        ConnectionsCounter = 0;
        if (ProcessedLayer == this->getM_Connections().size() - 1) //check if it is last layer
            BIAS_NEURON = 0;
        else
            BIAS_NEURON = 1;
        for(int RightLayerNeuron = 0; RightLayerNeuron < this->getM_Layers()[ProcessedLayer + 1].getM_NeuronsLayer().size() - BIAS_NEURON; RightLayerNeuron++)
        {
            for(int LeftLayerNeuron = 0; LeftLayerNeuron < this->getM_Layers()[ProcessedLayer].getM_NeuronsLayer().size(); LeftLayerNeuron++)
            {
                SingleInput = this->getM_Connections()[ProcessedLayer][ConnectionsCounter].getM_Weight() * this->getM_Layers()[ProcessedLayer].getM_NeuronsLayer()[LeftLayerNeuron].getM_Output();
                this->getM_Layers()[ProcessedLayer + 1].getM_NeuronsLayer()[RightLayerNeuron].AddToInput(SingleInput);
                ConnectionsCounter++;
            }
            NewNeuronOutput = ActivationFunction(this->getM_Layers()[ProcessedLayer + 1].getM_NeuronsLayer()[RightLayerNeuron].getM_Input());
            this->getM_Layers()[ProcessedLayer + 1].getM_NeuronsLayer()[RightLayerNeuron].setM_Output(NewNeuronOutput);
        }
    }
}

void NeuralNet::ChangeOutputsInInputLayer(vector<double> NewOutputs)
{
    for (int Neuron = 0; Neuron < Topology[0]; Neuron++)
    {
        this->getM_Layers()[0].getM_NeuronsLayer()[Neuron].setM_Output(NewOutputs[Neuron]);
    }
}
NeuralNet::~NeuralNet() {}


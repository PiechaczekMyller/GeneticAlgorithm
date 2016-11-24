//
// Created by user on 2016-11-06.
//

#include "NeuralNet.h"
#include "../Exceptions/DifferentSizesOfVectors.h"
const int InputAndOutputLayers = 2;
int BIAS_NEURON = 1;

NeuralNet::NeuralNet(vector<int> Topology) {
    this->Topology = Topology;
    CreateLayers();
    CreateConnections();
}

vector<vector<Connection>> &NeuralNet::get_Connections() {
    return Connections;
}

vector<Layer> &NeuralNet::get_Layers() {
    return Layers;
}

void NeuralNet::set_Connections(const vector<vector<Connection>> &m_ConnectionsVector) {
    NeuralNet::Connections = m_ConnectionsVector;
}

void NeuralNet::set_Layers(const vector<Layer> &m_LayersVector) {
    NeuralNet::Layers = m_LayersVector;
}

void NeuralNet::CreateLayers() {
    vector<Layer> temp_layer_vector;
    int layers_counter = 0;
    Layer InputLayer(Topology[layers_counter]);
    temp_layer_vector.push_back(InputLayer);
    for (int i = 0; i < Topology.size() - InputAndOutputLayers; i++)
    {
        layers_counter++;
        Layer HiddenLayer(Topology[layers_counter] + BIAS_NEURON);
        temp_layer_vector.push_back(HiddenLayer);
    }
    layers_counter++;
    Layer OutputLayer(Topology[layers_counter]);
    temp_layer_vector.push_back(OutputLayer);
    this->set_Layers(temp_layer_vector);
}

void NeuralNet::CreateConnections(){
    vector<vector<Connection>> TempConnections;
    int min = -5;
    int max = 5;
    double random_weight = 0;
    for(int connections = 0; connections < Topology.size() - 1; connections++)
    {
        vector<Connection> connections_vector;
        if (connections == 0) //check if it is the first layer
            BIAS_NEURON = 0;
        else
            BIAS_NEURON = 1;
        for(int j = 0; j < (Topology[connections] + BIAS_NEURON) * Topology[connections + 1]; j++)
        {
            random_device rd;
            mt19937 rng(rd());
            uniform_int_distribution<int> uni(min, max);
            random_weight = uni(rng);
            random_weight = random_weight / 10;
            Connection myConnection(random_weight);
            connections_vector.push_back(myConnection);
        }
        TempConnections.push_back(connections_vector);
    }
    this->set_Connections(TempConnections);
}

void NeuralNet::SetOutputOfBiasNeuron(double Output)
{
    for (int hidden_layer = 1; hidden_layer <= Topology.size() - InputAndOutputLayers; hidden_layer++)
    {
        this->get_Layers()[hidden_layer].get_Neurons_Layer().back().set_Output(Output);
    }
}

void NeuralNet::ProcessDataForward()
{
    double single_input = 0;
    int connections_counter = 0;
    for (int processed_layer = 0; processed_layer < this->get_Connections().size(); processed_layer++)
    {
        connections_counter = 0;
        if (processed_layer == this->get_Connections().size() - 1) //check if it is the last layer
            BIAS_NEURON = 0;
        else
            BIAS_NEURON = 1;
        for(int RightLayerNeuron = 0; RightLayerNeuron <
                this->get_Layers()[processed_layer + 1].get_Neurons_Layer().size() - BIAS_NEURON; RightLayerNeuron++)
        {
            for(int LeftLayerNeuron = 0; LeftLayerNeuron < this->get_Layers()[processed_layer].get_Neurons_Layer().size(); LeftLayerNeuron++)
            {
                single_input = this->get_Connections()[processed_layer][connections_counter].get_Weight() *
                        this->get_Layers()[processed_layer].get_Neurons_Layer()[LeftLayerNeuron].get_Output();
                this->get_Layers()[processed_layer + 1].get_Neurons_Layer()[RightLayerNeuron].AddToInput(single_input);
                connections_counter++;
            }
                this->get_Layers()[processed_layer + 1].get_Neurons_Layer()[RightLayerNeuron].ActivationFunction();
        }
    }
}

void NeuralNet::ChangeOutputsInInputLayer(vector<double> new_outputs)
{
    if (new_outputs.size() != Topology[0])
        throw DifferentSizesOfVectors("Neural Net: Input layer vector size and new_outputs vector size should be equal!");
    else {
        for (int neuron = 0; neuron < Topology[0]; neuron++) {
            this->get_Layers()[0].get_Neurons_Layer()[neuron].set_Output(new_outputs[neuron]);
        }
    }
}

void NeuralNet::BackPropagation() {

}

NeuralNet::~NeuralNet() {}


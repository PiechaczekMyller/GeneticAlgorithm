//
// Created by user on 2016-11-06.
//

#include "NeuralNet.h"
const int InputAndOutputLayers = 2;

NeuralNet::NeuralNet(vector<int> Topology, double learning_rate) {
    this->Topology = Topology;
    this->LearningRate = learning_rate;
    CreateLayers();
    CreateConnections();
}

vector<vector<double>> &NeuralNet::getConnections(){
    return Connections;
}

void NeuralNet::setConnections(const vector<vector<double>> &Connections) {
    NeuralNet::Connections = Connections;
}

vector<vector<Neuron>> &NeuralNet::getLayers() {
    return Layers;
}

void NeuralNet::setLayers(const vector<vector<Neuron>> &Layers) {
    NeuralNet::Layers = Layers;
}

vector<Neuron> CreateSingleLayer(int number_of_neurons)
{
    vector<Neuron> temp_neurons_layer;
    for(int i = 0; i < number_of_neurons; i++)
    {
        Neuron myNeuron;
        temp_neurons_layer.push_back(myNeuron);
    }
    return temp_neurons_layer;
}


void NeuralNet::CreateLayers() {
    vector<vector<Neuron>> temp_layers_vector;
    int layers_counter = 0;
    const int BIAS_NEURON = 1;
    vector<Neuron> InputLayer = CreateSingleLayer(Topology[layers_counter] + BIAS_NEURON);
    temp_layers_vector.push_back(InputLayer);
    for (int i = 0; i < Topology.size() - InputAndOutputLayers; i++)
    {
        layers_counter++;
        vector<Neuron> HiddenLayer = CreateSingleLayer(Topology[layers_counter] + BIAS_NEURON);
        temp_layers_vector.push_back(HiddenLayer);
    }
    layers_counter++;
    vector<Neuron> OutputLayer = CreateSingleLayer(Topology[layers_counter]);
    temp_layers_vector.push_back(OutputLayer);
    this->setLayers(temp_layers_vector);
}

void NeuralNet::CreateConnections(){
    vector<vector<double>> TempConnections;
    int min = -5;
    int max = 5;
    double random_weight = 0;
    const int BIAS_NEURON = 1;
    for(int connections = 0; connections < Topology.size() - 1; connections++)
    {
        vector<double> connections_vector;
        for(int j = 0; j < (Topology[connections] + BIAS_NEURON) * Topology[connections + 1]; j++)
        {
            random_device rd;
            mt19937 rng(rd());
            uniform_int_distribution<int> uni(min, max);
            random_weight = uni(rng);
            random_weight = random_weight / 10;
            connections_vector.push_back(random_weight);
        }
        TempConnections.push_back(connections_vector);
    }
    this->setConnections(TempConnections);
}

void NeuralNet::SetOutputOfBiasNeuron(double Output)
{
    for (int bias_layer = 0; bias_layer <= Topology.size() - 1; bias_layer++)
    {
        this->getLayers()[bias_layer].back().set_Output(Output);
    }
}

void NeuralNet::ResetInputs(){
    for (auto &layer : this->getLayers())
    {
        for (auto &neuron : layer)
        {
            neuron.set_Input(0);
        }
    }
}

void NeuralNet::ResetPropagatedError(){
    for (auto &layer : this->getLayers())
    {
        for (auto &neuron : layer)
        {
            neuron.set_Propagated_Error(0);
        }
    }
}

void NeuralNet::ProcessDataForward()
{
    double single_input = 0;
    int connections_counter = 0;
    int BIAS_NEURON = 1;
    for (int processed_layer = 0; processed_layer < this->getConnections().size(); processed_layer++)
    {
        connections_counter = 0;
        if (processed_layer == this->getConnections().size() - 1) //check if it is the last layer
            BIAS_NEURON = 0;
        else
            BIAS_NEURON = 1;
        for(int RightLayerNeuron = 0; RightLayerNeuron <
                this->getLayers()[processed_layer + 1].size() - BIAS_NEURON; RightLayerNeuron++)
        {
            for(int LeftLayerNeuron = 0; LeftLayerNeuron < this->getLayers()[processed_layer].size(); LeftLayerNeuron++)
            {
                single_input = this->getConnections()[processed_layer][connections_counter] *
                        this->getLayers()[processed_layer][LeftLayerNeuron].get_Output();
                this->getLayers()[processed_layer + 1][RightLayerNeuron].AddToInput(single_input);
                connections_counter++;
            }
                this->getLayers()[processed_layer + 1][RightLayerNeuron].ActivationFunction();
        }
    }
    this->ResetInputs();
}

void NeuralNet::ChangeOutputsInInputLayer(vector<double> new_outputs)
{
    if (new_outputs.size() != Topology[0])
        throw DifferentSizesOfVectors("Neural Net: Input layer vector size and new_outputs vector size should be equal!");
    else {
        for (int neuron = 0; neuron < Topology[0]; neuron++) {
            this->getLayers()[0][neuron].set_Output(new_outputs[neuron]);
        }
    }
}

void NeuralNet::BackPropagationForLastLayer(vector<double> desired_outputs)
{
    if (desired_outputs.size() != Topology.back())
        throw DifferentSizesOfVectors("Output layer vector size and desired outputs vector size are different, should be equal!");
    double error = 0;
    int desired_outputs_iterator = 0;
    for (auto &neuron : this->getLayers().back())
    {
        error = (desired_outputs[desired_outputs_iterator] - neuron.get_Output()) * neuron.Derivative();
        neuron.AddToPropagatedError(error);
        desired_outputs_iterator++;
    }
}

void NeuralNet::BackPropagationForHiddenLayers() {
    double epsilon = 0;
    const int BIAS_NEURON = 1;
    int connections_counter = 0;
    double error = 0;
    int connections_vector_counter = int(this->getConnections().size()) - 1;
    for (int current_layer = int(Topology.size()) - 2; current_layer > 0; current_layer--) //start from next to last layer
    {
        for (int current_layer_neuron = 0; current_layer_neuron < Topology[current_layer] + BIAS_NEURON; current_layer_neuron++)
        {
            connections_counter = current_layer_neuron;
            epsilon = 0;
            for (int right_layer_neuron = 0; right_layer_neuron < Topology[current_layer + 1]; right_layer_neuron++) // for every neuron in currently processed layer, collect error from next to current layer
            {
                epsilon = epsilon + this->getLayers()[current_layer + 1][right_layer_neuron].get_Propagated_Error() * this->getConnections()[connections_vector_counter][connections_counter];
                connections_counter = connections_counter + Topology[current_layer] + BIAS_NEURON; //because of the order the connections were initialized
            }
            error = epsilon * this->getLayers()[current_layer][current_layer_neuron].Derivative();
            this->getLayers()[current_layer][current_layer_neuron].AddToPropagatedError(error);
        }
        connections_vector_counter--;
    }
}

void NeuralNet::UpdateWeights(){
    const int BIAS_NEURON = 1;
    double new_weight = 0;
    int connections_counter = 0;
    int connections_vector_counter = int(this->getConnections().size()) - 1;
    for (int current_layer = int(this->getLayers().size() - 1); current_layer > 0; current_layer--) //start from last layer
    {
        connections_counter = 0;
        for (int current_layer_neuron = 0; current_layer_neuron < Topology[current_layer]; current_layer_neuron++)
        {
            for (int left_layer_neuron = 0; left_layer_neuron < Topology[current_layer - 1] + BIAS_NEURON; left_layer_neuron++)
            {
                new_weight = this->getConnections()[connections_vector_counter][connections_counter] + 2 * LearningRate * this->getLayers()[current_layer][current_layer_neuron].get_Propagated_Error() * this->getLayers()[current_layer - 1][left_layer_neuron].get_Output();
                this->getConnections()[connections_vector_counter][connections_counter] = new_weight;
                connections_counter++;
            }
        }
        connections_vector_counter--;
    }
    this->ResetPropagatedError();
}

double NeuralNet::CalculateSquaredError(vector<double> desired_outputs)
{
    if (desired_outputs.size() != Topology.back())
        throw DifferentSizesOfVectors("Output layer vector size and desired outputs vector size are different, should be equal!");
    double squared_error = 0;
    int desired_outputs_counter = 0;
    for (auto &neuron : this->getLayers().back())
    {
        squared_error = squared_error + pow((desired_outputs[desired_outputs_counter] - neuron.get_Output()),2);
        desired_outputs_counter++;
    }
    return squared_error;
}

void NeuralNet::Fit(vector<vector<double>> data_to_fit, vector<vector<double>> desired_outputs, double accuracy)
{
    double error = 100;
    double squared_error = 0;
    while (error > accuracy)
    {
        squared_error = 0;
        for (int i = 0; i < data_to_fit.size(); i++)
        {
            this->ChangeOutputsInInputLayer(data_to_fit[i]);
            this->ProcessDataForward();
            squared_error = squared_error + this->CalculateSquaredError(desired_outputs[i]);
            this->BackPropagationForLastLayer(desired_outputs[i]);
            this->BackPropagationForHiddenLayers();
        }
        this->UpdateWeights();
        cout << "squared error: " << squared_error << endl;
        error = squared_error;
    }
}

void NeuralNet::PartialFit(vector<vector<double>> data_to_fit, vector<vector<double>> desired_outputs, double accuracy)
{
    double error = 100;
    vector<int> indexes;
    double squared_error = 0;
    for (int i = 0; i < data_to_fit.size(); i++)
    {
        indexes.push_back(i);
    }
    random_shuffle(indexes.begin(), indexes.end());
    while (error > accuracy)
    {
        squared_error = 0;
        random_shuffle(indexes.begin(), indexes.end());
        for (int i = 0; i < indexes.size(); i++) {
            this->ChangeOutputsInInputLayer(data_to_fit[indexes[i]]);
            this->ProcessDataForward();
            squared_error = squared_error + this->CalculateSquaredError(desired_outputs[indexes[i]]);
            this->BackPropagationForLastLayer(desired_outputs[indexes[i]]);
            this->BackPropagationForHiddenLayers();
            this->UpdateWeights();
        }
        cout << "squared error: " << squared_error << endl;
        error = squared_error;
    }
}

void NeuralNet::Predict(vector<double> data_to_predict)
{
    this->ChangeOutputsInInputLayer(data_to_predict);
    this->ProcessDataForward();
    int index = 0;
    for (auto &neuron : this->getLayers().back())
    {
        cout << "Predicted data:" << endl;
        cout << "Output " << index << ": " << neuron.get_Output() << endl;
        index++;
    }
}

NeuralNet::~NeuralNet() {}


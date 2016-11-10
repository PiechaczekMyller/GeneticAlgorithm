#include <iostream>
#include "NeuralNet.h"
const int BIAS_NEURON = 1;
using namespace std;
int main() {
    vector<int> Topology;
    Topology.push_back(256);
    Topology.push_back(50 + BIAS_NEURON);
    Topology.push_back(30 + BIAS_NEURON);
    Topology.push_back(2);
    NeuralNet myNet(Topology);
    return 0;
}
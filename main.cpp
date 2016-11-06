#include <iostream>
#include "Net.h"
#include "Layer.h"
#include "Neuron.h"
#include "Connection.h"
#include <ctime>

using namespace std;
int main() {
    vector<int> Topology;
    Topology.push_back(1);
    Topology.push_back(3);
    Topology.push_back(2);
    Topology.push_back(1);
    Topology.push_back(2);
    Net myNet(Topology);
    return 0;
}
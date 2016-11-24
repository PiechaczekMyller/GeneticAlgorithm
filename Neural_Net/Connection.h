//
// Created by myychal on 2016-11-06.
//

#ifndef NEURALNETGA_CONNECTION_H
#define NEURALNETGA_CONNECTION_H
#include <iostream>

class Connection {
private:
    double Weight;
    double Delta_Weight;
public:
    Connection(double m_Weight);

    double get_Weight() const;

    void set_Weight(double m_Weight);

    double get_Delta_Weight() const;

    void set_Delta_Weight(double m_DeltaWeight);

    virtual ~Connection();
};


#endif //NEURALNETGA_CONNECTION_H

//
// Created by myychal on 2016-11-06.
//

#ifndef NEURALNETGA_CONNECTION_H
#define NEURALNETGA_CONNECTION_H
#include <iostream>

class Connection {
private:
    double Weight;
public:
    Connection(double m_Weight);

    double get_Weight() const;

    void set_Weight(double m_Weight);

    virtual ~Connection();
};


#endif //NEURALNETGA_CONNECTION_H

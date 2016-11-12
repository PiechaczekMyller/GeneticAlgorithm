//
// Created by myychal on 2016-11-06.
//

#ifndef NEURALNETGA_CONNECTION_H
#define NEURALNETGA_CONNECTION_H
#include <iostream>

class Connection {
private:
    double m_Weight;
    double m_DeltaWeight;
public:
    Connection(double m_Weight);

    double getM_Weight() const;

    void setM_Weight(double m_Weight);

    double getM_DeltaWeight() const;

    void setM_DeltaWeight(double m_DeltaWeight);

    virtual ~Connection();
};


#endif //NEURALNETGA_CONNECTION_H

//
// Created by user on 2016-11-06.
//

#include "Connection.h"
Connection::Connection(double m_Weight) : m_Weight(m_Weight), m_DeltaWeight(0) {}

double Connection::getM_Weight() const {
    return m_Weight;
}

void Connection::setM_Weight(double m_Weight) {
    Connection::m_Weight = m_Weight;
}

double Connection::getM_DeltaWeight() const {
    return m_DeltaWeight;
}

void Connection::setM_DeltaWeight(double m_DeltaWeight) {
    Connection::m_DeltaWeight = m_DeltaWeight;
}

Connection::~Connection() {

}

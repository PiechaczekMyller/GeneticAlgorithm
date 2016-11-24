//
// Created by user on 2016-11-06.
//

#include "Connection.h"
Connection::Connection(double m_Weight) : Weight(m_Weight), Delta_Weight(0) {}

double Connection::get_Weight() const {
    return Weight;
}

void Connection::set_Weight(double m_Weight) {
    Connection::Weight = m_Weight;
}

double Connection::get_Delta_Weight() const {
    return Delta_Weight;
}

void Connection::set_Delta_Weight(double m_DeltaWeight) {
    Connection::Delta_Weight = m_DeltaWeight;
}

Connection::~Connection() {

}

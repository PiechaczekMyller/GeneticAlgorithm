//
// Created by user on 2016-11-06.
//

#include "Connection.h"
Connection::Connection(double m_Weight) : Weight(m_Weight){}

double Connection::get_Weight() const {
    return Weight;
}

void Connection::set_Weight(double m_Weight) {
    Connection::Weight = m_Weight;
}

Connection::~Connection() {

}

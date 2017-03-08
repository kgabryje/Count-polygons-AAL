//
// Created by kamil on 27.11.16.
//

#include "Point.h"

Point::Point(float x, float y) : _x(x), _y(y) {}

bool Point::operator==(const Point& rhs) const {
    return this->_x == rhs._x && this->_y == rhs._y;
}

bool Point::operator<(const Point& rhs) const {
    return (this->_x < rhs._x) || (this->_x == rhs._x && this->_y < rhs._y);
}

float Point::get_x() const {
    return _x;
}

float Point::get_y() const {
    return _y;
}

int Point::get_id() {
    return _id;
}

void Point::set_id(int id) {
    this->_id = id;
}

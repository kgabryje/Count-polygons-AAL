//
// Created by kamil on 27.11.16.
//

#include "Segment.h"
#include <climits>
#include <algorithm>

unsigned int Segment::intersection_counter = 0;

bool Segment::operator==(const Segment& rhs) const {
    return (this->_p1 == rhs._p1 && this->_p2 == rhs._p2) || (this->_p2 == rhs._p1 && this->_p1 == rhs._p2);
}

double max(double x, double y) {
    if (x > y)
        return x;
    else
        return y;
}

double min(double x, double y) {
    if (x < y)
        return x;
    else
        return y;
}

Segment::Segment(const Point &p1, const Point &p2) : _p1(p1), _p2(p2) {
    if (_p1.get_x() - p2.get_x() != 0) {
        _slope = (_p1.get_y() - _p2.get_y()) / (_p1.get_x() - p2.get_x());
        _bias = _p1.get_y() - _slope * _p1.get_x();
    }
    else _slope = INT_MAX;
}

std::vector<Point>& Segment::get_intersections() {
    return intersections;
}

void Segment::find_intersection(Segment& s) {
    double x,y;
    if (this->_slope == s._slope)
        return;
    else if (this->_slope == INT_MAX) {
        x = this->_p1.get_x();
        y = s._slope * x + s._bias;
    }
    else if (s._slope == INT_MAX) {
        x = s._p1.get_x();
        y = this->_slope * x + this->_bias;
    }
    else {
        x = (s._bias - this->_bias) / (this->_slope - s._slope);
        y = _slope * x + _bias;
    }
    Point p = Point(x,y);
    if (on_segment(p, s)) {
        auto it = std::find(intersections.begin(), intersections.end(),p);
        auto it2 = std::find(s.intersections.begin(), s.intersections.end(),p);
        if (it == intersections.end() && it2 == s.intersections.end())
            p.set_id(intersection_counter++);
        else if (it != intersections.end())
            p.set_id(it->get_id());
        else
            p.set_id(it2->get_id());
        intersections.push_back(p);
        s.intersections.push_back(p);
    }
}

bool Segment::on_segment(const Point& p, const Segment& s) {
    return !(p.get_x() > min(max(s._p1.get_x(), s._p2.get_x()), max(this->_p1.get_x(), this->_p2.get_x()))
           || p.get_y() > min(max(s._p1.get_y(), s._p2.get_y()), max(this->_p1.get_y(), this->_p2.get_y()))
           || p.get_x() < max(min(this->_p1.get_x(), this->_p2.get_x()), min(s._p1.get_x(), s._p2.get_x()))
           || p.get_y() < max(min(this->_p1.get_y(), this->_p2.get_y()), min(s._p1.get_y(), s._p2.get_y())));
}

unsigned int Segment::get_intersection_counter() {
    return intersection_counter;
}

const Point &Segment::get_p1() const {
    return _p1;
}

const Point &Segment::get_p2() const {
    return _p2;
}

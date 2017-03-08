//
// Created by kamil on 27.11.16.
//

#pragma once

#include <vector>
#include <set>
#include "Point.h"

class Segment
{
private:
    bool on_segment(const Point& p, const Segment& s);
    std::vector<Point> intersections;
    Point _p1;
    Point _p2;
    double _slope;
    double _bias;
    static unsigned int intersection_counter;
public:
    Segment(const Point &p1, const Point &p2);
    std::vector<Point>& get_intersections();
    void find_intersection(Segment& s);
    static unsigned int get_intersection_counter();
    bool operator==(const Segment& rhs) const;
    const Point &get_p1() const;
    const Point &get_p2() const;
};
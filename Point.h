//
// Created by kamil on 27.11.16.
//

#pragma once

#include <cstdlib>

class Point
{
private:
    float _x;
    float _y;
    int _id = 0;
public:
    Point(float x, float y);
    float get_x() const;
    float get_y() const;
    int get_id();
    void set_id(int id);
    bool operator==(const Point& rhs) const;
    bool operator<(const Point& rhs) const;
};
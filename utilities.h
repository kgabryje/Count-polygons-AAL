//
// Created by kamil on 18.01.17.
//

#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include "Point.h"
#include "Segment.h"

struct {
    bool operator()(Point a, Point b) {
        return a.get_x() < b.get_x();
    }
} sort_points;

struct {
    bool operator()(Segment s1, Segment s2) {
        Point p1 = s1.get_p1() < s1.get_p2() ? s1.get_p1() : s1.get_p2();
        Point p2 = s2.get_p1() < s2.get_p2() ? s2.get_p1() : s2.get_p2();
        return p1 < p2;
    }
} sort_segments;

void find_all_intersections(std::vector<Segment>& segments) {
    std::sort(segments.begin(),segments.end(),sort_segments);
    segments.erase(std::unique(segments.begin(),segments.end()), segments.end());

    for (int i = 0; i < segments.size() - 1; i++)
        for (int j = i + 1; j < segments.size(); j++) {
            segments[i].find_intersection(segments[j]);
        }
    for (auto i = segments.begin(); i != segments.end(); i++) {
        std::sort(i->get_intersections().begin(), i->get_intersections().end(), sort_points);
    }
}

void generate_random_segments(size_t number_of_segments, std::string file) {
    std::ofstream outfile;
    outfile.open(file);
    if (outfile.is_open()) {
        for (int i = 0; i < number_of_segments; i++) {
            for (int j = 0; j < 4; j++) {
                outfile << rand()%1000 << " ";
            }
            outfile << std::endl;
        }
        outfile.close();
    }
    else
        std::cerr << "Can't open segments data file." << std::endl;
}

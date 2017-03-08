//
// Created by kamil on 08.03.17.
//

#pragma once

#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "VectorHash.h"
#include "Point.h"
#include "Segment.h"

class Graph {
public:
    int V = 0;
    int E = 0;
    std::vector<std::set<int>> adj;
    CyclesSet cycles;
    std::ofstream outfile;
    std::vector<int> path;
    std::vector<bool> marked;

    virtual void addEdge(int v, int w, int& counter);
    virtual void addEdge(Point v, Point w);
    virtual void generate_graph(int V, int E);
    virtual void generate_graph(std::vector<Segment>& segments);

    virtual ~Graph();
    Graph(std::vector<Segment>& segments, std::string filename);
    Graph(int V, int E, std::string filename);
};




//
// Created by kamil on 27.11.16.
//

#pragma once


#include <vector>
#include <set>
#include <map>
#include <chrono>
#include <fstream>
#include "Point.h"
#include "Segment.h"
#include "VectorHash.h"
#include "Graph.h"

class Graph_DFS : public Graph
{
private:
    void DFS(int v, int parent);
    std::vector<int> normalize(std::vector<int> path);
    std::vector<int> invert(std::vector<int> path);

    bool is_new(std::vector<int>& path);
    static void run_repetition(Graph_DFS& g, std::map<long long int,double>& stats);

public:
    Graph_DFS(std::vector<Segment>& segments, std::string filename);
    Graph_DFS(int V, int E, std::string filename);
    void find_cycles();
    static void get_statistics(int v, int e, int repetitions, std::string filename);
};



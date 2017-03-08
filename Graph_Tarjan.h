//
// Created by kamil on 08.01.17.
//

#pragma once

#include <vector>
#include <set>
#include <stack>
#include <map>
#include <fstream>
#include <chrono>
#include "Segment.h"
#include "VectorHash.h"
#include "Graph.h"

class Graph_Tarjan : public Graph {
private:
    bool g = false;
    std::stack<int> marked_stack;

    void tarjan(int start_node, int current_node, bool f);
    std::vector<int> invert(std::vector<int> path);
    bool is_new(std::vector<int>& path);

    static void run_repetition(Graph_Tarjan& g, std::map<int,double>& stats);

public:
    Graph_Tarjan(std::vector<Segment>& segments, std::string filename);
    Graph_Tarjan(int V, int E, std::string filename);
    void find_cycles();
    static void get_statistics(int v, int e, int repetitions, std::string filename);
};

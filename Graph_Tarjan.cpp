//
// Created by kamil on 08.01.17.
//
#include <iostream>
#include <algorithm>
#include "Graph_Tarjan.h"

//Graph_Tarjan::~Graph_Tarjan() {}

Graph_Tarjan::Graph_Tarjan(std::vector<Segment>& segments, std::string filename) : Graph(segments, filename) {}
Graph_Tarjan::Graph_Tarjan(int V, int E, std::string filename) : Graph(V,E,filename) {}

void Graph_Tarjan::tarjan(int start_node, int current_node, bool f) {
    path.push_back(current_node);
    marked_stack.push(current_node);
    marked[current_node] = true;

    for (auto& v : adj[current_node]) {
        if (v < start_node) {
            adj[current_node].erase(v);
        }
        else if (v == start_node) {
            if ((path.size() > 2)) {
                std::vector<int> inv = invert(path);
                if (is_new(path) && is_new(inv)) {
                    cycles.insert(path);
                    f = true;
//                    for (auto& i : path) {
//                        outfile << i << " ";
//                    }
//                    outfile << std::endl;
                }
            }
        }
        else if (!marked[v]) {
            f = f || g;
            tarjan(start_node,v,true);
        }
    }

    if (f) {
        int u = marked_stack.top();
        marked_stack.pop();
        while (u != current_node) {
            marked[u] = false;
            u = marked_stack.top();
            marked_stack.pop();
        }
        marked[u] = false;
    }
    path.pop_back();
    g = true;
}

void Graph_Tarjan::find_cycles() {
    path.reserve(V);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for (int i = 0; i < this->V; i++) {
            tarjan(i,i,false);
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    outfile << "No. vertices: " << this->V << std::endl;
    outfile << "No. edges: " << this->E << std::endl;
    outfile << "Polygons found: " << cycles.size() << std::endl;
    outfile << "Elapsed time: " << elapsed_seconds.count() << std::endl;
}

void Graph_Tarjan::get_statistics(int v, int e, int repetitions, std::string filename) {
    std::map<int,double> stats;
    double q, t_median, T_median;

    for (int i = 0; i < repetitions; i++) {
        Graph_Tarjan g(v,e,filename);
        g.path.reserve(v);
        run_repetition(g, stats);
    }

    std::map<int,double>::iterator it = stats.begin();
    for (int i = 0; i < stats.size()/2; i++, it++);
    if (!(stats.size()%2)) {
        t_median = (it->second + (--it)->second)/2;
        T_median = (it->first + (++it)->first)/2 * (v + e);
    }
    else {
        t_median = it->second;
        T_median = it->first * (v + e);
    }

    std::cout << "STATS FOR PREDICTED COMPLEXITY O(C*(V+E))" << std::endl;
    std::cout.width(15);
    std::cout << std::left << "n = C*(V+E)";
    std::cout.width(15);
    std::cout << std::left << "t(n)";
    std::cout.width(15);
    std::cout << std::left << "q(n)" << std::endl;
    for (auto& i : stats) {
        q = i.second / (i.first*(v+e)) * T_median / t_median;
        std::cout.width(15);
        std::cout << std::left << i.first*(v+e);
        std::cout.width(15);
        std::cout << std::left << i.second;
        std::cout.width(15);
        std::cout << std::left << q << std::endl;
    }
}

void Graph_Tarjan::run_repetition(Graph_Tarjan &g, std::map<int,double>& stats) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for (int i = 0; i < g.V; i++) {
        g.tarjan(i, i, false);
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    stats.insert(std::make_pair<int,double>(g.cycles.size(),elapsed_seconds.count()));
}

std::vector<int> Graph_Tarjan::invert(std::vector<int> path) {
    std::reverse(path.begin()+1,path.end());
    return path;
}

bool Graph_Tarjan::is_new(std::vector<int>& path) {
    return cycles.find(path) == cycles.end();
}
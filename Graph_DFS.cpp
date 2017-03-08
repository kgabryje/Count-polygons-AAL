//
// Created by kamil on 04.12.16.
//
#include <iostream>
#include <algorithm>
#include "Graph_DFS.h"


Graph_DFS::Graph_DFS(std::vector<Segment>& segments, std::string filename) : Graph(segments, filename) {}
Graph_DFS::Graph_DFS(int V, int E, std::string filename) : Graph(V, E, filename) {}

void Graph_DFS::DFS(int v, int parent) {
    marked[v] = true;
    if (parent != -1)
        path.push_back(parent);
    std::vector<int>::iterator it = std::find(path.begin(),path.end(),v);
    if (it != path.end()) {
        std::vector<int> ancestors(it, path.end());
        std::vector<int> p = normalize(ancestors);
        std::vector<int> inv = invert(p);
        if (is_new(p) && is_new(inv)) {
            cycles.insert(p);
//            for (auto& i : p) {
//                outfile << i << " ";
//            }
//            outfile << std::endl;
        }
    }
    else
        for (auto& i : adj[v])
            if (i != parent)
                DFS(i, v);
    path.pop_back();
}

void Graph_DFS::find_cycles() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    for (int i = 0; i < V; i++) {
        if (!marked[i])
            DFS(i, -1);
            path.clear();
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    outfile << "No. vertices: " << this->V << std::endl;
    outfile << "No. edges: " << this->E << std::endl;
    outfile << "Polygons found: " << cycles.size() << std::endl;
    outfile << "Elapsed time: " << elapsed_seconds.count() << std::endl;
}

std::vector<int> Graph_DFS::normalize(std::vector<int> path) {
    std::vector<int>::iterator x = std::min_element(path.begin(),path.end());
    std::vector<int> temp;
    temp.reserve(path.size());
    temp.insert(temp.end(),x,path.end());
    temp.insert(temp.end(),path.begin(),x);
    return temp;
}

std::vector<int> Graph_DFS::invert(std::vector<int> path) {
    std::reverse(path.begin()+1,path.end());
    return path;
}

bool Graph_DFS::is_new(std::vector<int>& path) {
    return cycles.find(path) == cycles.end();
}

void Graph_DFS::get_statistics(int v, int e, int repetitions, std::string filename) {
    std::map<long long,double> stats;
    double q, t_median, T_median;

    for (int i = 0; i < repetitions; i++) {
        Graph_DFS g(v,e,filename);
        run_repetition(g, stats);
    }
    std::map<long long,double>::iterator it = stats.begin();
    for (int i = 0; i < stats.size()/2; i++, it++);
    if (!(stats.size()%2)) {
        t_median = (it->second + (--it)->second)/2;
        T_median = (it->first + (++it)->first)/2 * (v + e);
    }
    else {
        t_median = it->second;
        T_median = it->first * (v + e);
    }

    std::cout << "STATS FOR PREDICTED COMPLEXITY O(L*(V+E))" << std::endl;
    std::cout.width(15);
    std::cout << std::left << "n = L*(V+E)";
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

void Graph_DFS::run_repetition(Graph_DFS& g, std::map<long long,double>& stats) {
    long long path_length_sum = 0;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for (int i = 0; i < g.V; i++) {
        if (!g.marked[i]) {
            g.DFS(i, -1);
            g.path.clear();
        }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    for (auto& i : g.cycles) {
        path_length_sum += i.size();
    }
    stats.insert(std::make_pair(path_length_sum,elapsed_seconds.count()));
}
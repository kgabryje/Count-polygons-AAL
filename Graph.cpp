//
// Created by kamil on 08.03.17.
//

#include "Graph.h"

Graph::~Graph() {}

Graph::Graph(int V, int E, std::string filename) {
    outfile.open(filename);
    generate_graph(V,E);
}

Graph::Graph(std::vector<Segment> &segments, std::string filename) {
    outfile.open(filename);
    generate_graph(segments);
}

void Graph::addEdge(int v, int w, int& counter) {
    if (adj[v].insert(w).second) {
        adj[w].insert(v);
        counter++;
        outfile << "adding edge: " << w << "-" << v << std::endl;
    }
}

void Graph::addEdge(Point v, Point w) {
    if (adj[v.get_id()].insert(w.get_id()).second && adj[w.get_id()].insert(v.get_id()).second) {
        outfile << "adding edge: " << w.get_id() << "-" << v.get_id() << " (" << w.get_x() << "," << w.get_y() << " - "
                << v.get_x() << "," << v.get_y() << ")" << std::endl;
        this->E++;
    }
}

void Graph::generate_graph(std::vector<Segment> &segments) {
    std::vector<Point> temp_vec;
    this->V = Segment::get_intersection_counter();
    adj.resize(V);
    path.reserve(V);
    marked.resize(V);

    for (auto i = segments.begin(); i != segments.end(); i++) {
        for (int j = 0; j < (int) (i->get_intersections().size()) - 1; j++) {
            temp_vec = i->get_intersections();
            if (temp_vec[j].get_id() != temp_vec[j + 1].get_id()) {
                addEdge(temp_vec[j], temp_vec[j + 1]);
            }
        }
    }
}

void Graph::generate_graph(int V, int E) {
    int counter = 0;
    int v,w;
    this->V = V;
    this->E = E;
    if (E > V*(V-1)/2) {
        std::cerr << "Can't generate a graph with given number of vertices and edges." << std::endl;
        exit(1);
    }
    adj.resize(V);
    path.reserve(V);
    marked.reserve(V);

    while (counter < E) {
        v = rand() % V;
        w = rand() % V;
        if (v != w)
            addEdge(v,w,counter);
    }
}
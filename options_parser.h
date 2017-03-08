//
// Created by kamil on 18.01.17.
//

#pragma once

#include <getopt.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include "Segment.h"
#include "utilities.h"
#include "Graph_DFS.h"
#include "Graph_Tarjan.h"


int optparser(int argc, char **argv, option* long_options, std::string& input_file, std::string& output_file,
              int& vertices, int& edges, int& quantity, int& repetitions, std::string& algorithm) {

    bool f_break;
    int opt_result;
    int opt_index;

    f_break = false;
    optind++;

    while (!f_break) {
        opt_result = getopt_long(argc, argv, "v:e:i:o:q:s:a:r:", long_options, &opt_index);
        switch (opt_result) {
            case 'a':
                algorithm = optarg;
                break;

            case 'v':
                vertices = atoi(optarg);
                break;

            case 'e':
                edges = atoi(optarg);
                break;

            case 'q':
                quantity = atoi(optarg);
                break;

            case 'r':
                repetitions = atoi(optarg);
                break;

            case 'i':
                input_file = optarg;
                break;

            case 'o':
                output_file = optarg;
                break;

            case ':':
            case '?':
                break;

            case -1:
            default:
                f_break = true;
                break;
        }
    }
}

int cmdparser(int argc, char** argv) {
    option random_graph_options[] = {
            {"vertices",		required_argument,	nullptr, 'v'},
            {"edges",	        required_argument,	nullptr, 'e'},
            {"algorithm",	    required_argument,	nullptr, 'a'},
            {"output-file",	    required_argument,	nullptr, 'o'},
    };

    option import_segments_options[] = {
            {"input-file",	    required_argument,	nullptr, 'i'},
            {"output-file",	    required_argument,	nullptr, 'o'},
            {"algorithm",	    required_argument,	nullptr, 'a'}
    };

    option random_segments_options[] = {
            {"quantity",	    required_argument,	nullptr, 'q'},
            {"output-file",		required_argument,	nullptr, 'o'},
            {"segments-file",	required_argument,	nullptr, 'i'},
            {"algorithm",	    required_argument,	nullptr, 'a'}
    };

    option get_statistics_options[] = {
            {"vertices",		required_argument,	nullptr, 'v'},
            {"edges",	        required_argument,	nullptr, 'e'},
            {"algorithm",	    required_argument,	nullptr, 'a'},
            {"output-file",	    required_argument,	nullptr, 'o'},
            {"repetitions",	    required_argument,	nullptr, 'r'}
    };

    std::string command = argv[1];
    int v,e,quantity,repetitions;
    double x1, y1, x2, y2;
    std::string in,out,algorithm;

    if (command == "random_graph") {
        optparser(argc,argv,random_graph_options,in,out,v,e,quantity,repetitions,algorithm);
        if (algorithm == "tarjan") {
            Graph_Tarjan g(v,e,out);
            g.find_cycles();
        }
        else if (algorithm == "dfs") {
            Graph_DFS g(v,e,out);
            g.find_cycles();
        }
        else {
            std::cerr << "Wrong algorithm name!" << std::endl << "Please use tarjan or dfs" << std::endl;
            exit(1);
        }
    }
    else if (command == "import_segments") {
        optparser(argc,argv,import_segments_options,in,out,v,e,quantity,repetitions,algorithm);
        std::ifstream points(in);
        if (!points.good()) {
            std::cerr << "Can't open input file" << std::endl;
            exit(1);
        }
        std::vector<Segment> segments;
        while (points >> x1 >> y1 >> x2 >> y2) {
            segments.push_back(Segment(Point(x1, y1), Point(x2, y2)));
        }
        find_all_intersections(segments);
        if (algorithm == "tarjan") {
            Graph_Tarjan g(segments,out);
            g.find_cycles();
        }
        else if (algorithm == "dfs") {
            Graph_DFS g(segments,out);
            g.find_cycles();
        }
        else {
            std::cerr << "Wrong algorithm name!" << std::endl << "Please use tarjan or dfs" << std::endl;
            exit(1);
        }
    }
    else if (command == "random_segments") {
        optparser(argc,argv,random_segments_options,in,out,v,e,quantity,repetitions,algorithm);
        generate_random_segments(quantity, in);
        std::ifstream points(in);
        if (!points.good()) {
            std::cerr << "Can't open input file" << std::endl;
            exit(1);
        }
        std::vector<Segment> segments;
        while (points >> x1 >> y1 >> x2 >> y2) {
            segments.push_back(Segment(Point(x1, y1), Point(x2, y2)));
        }
        find_all_intersections(segments);
        if (algorithm == "tarjan") {
            Graph_Tarjan g(segments,out);
            g.find_cycles();
        }
        else if (algorithm == "dfs") {
            Graph_DFS g(segments,out);
            g.find_cycles();
        }
        else {
            std::cerr << "Wrong algorithm name!" << std::endl << "Please use tarjan or dfs" << std::endl;
            exit(1);
        }
    }
    else if (command == "get_statistics") {
        optparser(argc,argv,get_statistics_options,in,out,v,e,quantity,repetitions,algorithm);
        if (algorithm == "tarjan") {
            Graph_Tarjan::get_statistics(v,e,repetitions,out);
        }
        else if (algorithm == "dfs") {
            Graph_DFS::get_statistics(v,e,repetitions,out);
        }
        else {
            std::cerr << "Wrong algorithm name!" << std::endl << "Please use tarjan or dfs" << std::endl;
            exit(1);
        }
    }
}
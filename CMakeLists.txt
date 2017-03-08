cmake_minimum_required(VERSION 3.6)
project(AAL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11")

set(SOURCE_FILES main.cpp Segment.h Point.h Point.cpp Segment.cpp Graph_Tarjan.cpp Graph_Tarjan.h Graph_DFS.cpp Graph_DFS.h VectorHash.h options_parser.h utilities.h Graph.cpp Graph.h)
add_executable(AAL ${SOURCE_FILES})
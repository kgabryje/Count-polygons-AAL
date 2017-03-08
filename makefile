FLAGS = -O2 --std=c++11

all: AAL

main.o: main.cpp
	g++ -c $(FLAGS) main.cpp
Point.o: Point.cpp
	g++ -c $(FLAGS) Point.cpp
Segment.o: Segment.cpp
	g++ -c $(FLAGS) Segment.cpp
Graph_Tarjan.o: Graph_Tarjan.cpp
	g++ -c $(FLAGS) Graph_Tarjan.cpp
Graph_DFS.o: Graph_DFS.cpp
	g++ -c $(FLAGS) Graph_DFS.cpp
AAL: main.o Point.o Segment.o Graph_Tarjan.o Graph_DFS.o
	g++ -o AAL main.o Point.o Segment.o Graph_Tarjan.o Graph_DFS.o
clean:
	rm *.o
clean_all:
	rm AAL
	rm *.o

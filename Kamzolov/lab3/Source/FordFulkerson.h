#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <climits>
#include <sstream>


struct Edge {
    int capacity, flow;
    bool onStart;
    bool used = false;
};

inline bool operator==(const Edge& lhs, const Edge& rhs) {
    return (lhs.capacity == rhs.capacity && lhs.flow == rhs.flow && lhs.onStart == rhs.onStart);
}

class FordFulkerson {
public:
    std::map<char, std::vector<std::pair<char, Edge>>> graph;
    char start, finish;
    int size;
    std::map<char, bool> visited;
    std::map<char, char> parent;
    int maxFlow = 0;

    FordFulkerson(
        std::map<char,
        std::vector<std::pair<char, Edge>>> graph,
        char start,
        char finish,
        int size
    ) : graph(graph), start(start), finish(finish), size(size) {}

    void printAnswer();
    int search(char curVertex);
    void fordFulkersonAlgo();

};

bool flowComparator(std::pair<char, Edge> first, std::pair<char, Edge> second);

bool charComparator(std::pair<char, Edge> first, std::pair<char, Edge> second);


void readGraph(
    std::map<char, std::vector<std::pair<char, Edge>>>& graph,
    int& size,
    char& start,
    char& finish,
    std::istream& in
);

#endif

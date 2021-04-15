#pragma once

#include "graph.hpp"
#include <vector>
#include <set>

template <typename T>
inline std::vector<T> GreedyAlgorithm(const Graph<T>& graph, char start, char end) {
    std::vector<T> path = {start};
    std::set<T> visited = {start};
    char current_vertex = start;

    while (current_vertex != end) {
        auto neighbours = graph.GetNeighbours(current_vertex,
                                              [&visited](T c) { return visited.find(c) == visited.end(); });
        if (neighbours.empty()) {
            visited.insert(current_vertex);
            path.pop_back();
            current_vertex = path.back();
            continue;
        }

        T local_minimum = neighbours.front();

        while (!neighbours.empty()) {
            T neighbour = neighbours.front();
            if (graph.GetEdgeWeight(current_vertex, neighbour) < graph.GetEdgeWeight(current_vertex, local_minimum))
                local_minimum = neighbour;

            neighbours.pop_front();
        }

        current_vertex = local_minimum;
        path.push_back(current_vertex);
    }

    return path;
}
#pragma once

#include "graph.hpp"
#include <queue>
#include <algorithm>
#include <string>
#include <vector>


template <typename T>
struct Vertex {
    T name;
    float priority;

    bool operator<(const Vertex& v) const {
        return priority != v.priority ? priority > v.priority : name < v.name;
    }
};

template <typename T>
float Heuristics(T v, T u) {
    return static_cast<float>(std::abs(u - v));
}

template <typename T>
static std::vector<T> FindPath(T start, T end, const std::vector<T>& ancestors)
{
    std::vector<T> path;

    T current = end;
    while (current != start) {
        path.push_back(current);
        current = ancestors[Graph<T>::OffsetValue(current)];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}


template <typename T>
std::vector<T> AStarAlgorithm(const Graph<T>& graph, T start, T end) {
    std::vector<float> weights(graph.Size(), -1);
    std::vector<bool> visited(graph.Size());
    std::vector<T> ancestors(graph.Size());

    std::priority_queue<Vertex<T>> to_visit;
    to_visit.push({start, 0});
    weights[Graph<T>::OffsetValue(start)] = 0;

    while (!to_visit.empty()) {
        auto current_vertex = to_visit.top();
        to_visit.pop();

        if (visited[current_vertex.name])
            continue;
        if  (current_vertex.name == end)
            break;


        auto neighbours = graph.GetNeighbours(current_vertex.name);
        while (!neighbours.empty()) {
            auto neighbour = neighbours.front();
            neighbours.pop_front();

            auto offseted_value = Graph<T>::OffsetValue(neighbour);
            auto cost = static_cast<float>(weights[Graph<T>::OffsetValue(current_vertex.name)])
                        + graph.GetEdgeWeight(current_vertex.name, neighbour);

            if (weights[offseted_value] == -1 || cost < weights[offseted_value]) {
                weights[offseted_value] = cost;
                to_visit.push({neighbour, cost + Heuristics(neighbour, end)});
                ancestors[offseted_value] = current_vertex.name;
            }
        }

        visited[Graph<T>::OffsetValue(current_vertex.name)] = true;
    }

    return FindPath(start, end, ancestors);
}
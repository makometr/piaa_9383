#pragma once

#include "graph.hpp"
#include <vector>
#include <set>
#include <limits>
#include <cassert>
#include <iostream>

struct WebPath {
    std::vector<char> path;
    float minimal_edge;

    size_t Size() const { return  path.size(); }
    char operator[](size_t index) const {
        return path[index];
    }
};

static inline WebPath FindPath(const Graph& graph,
                              char from,
                              char to,
                              std::set<char>& visited) {
    WebPath web_path{std::vector<char>{from}, std::numeric_limits<float>::max()};

    if (from == to)
        return web_path;

    visited.insert(from);
    auto neighbours = graph.GetNeighbours(from, [&visited](char c) { return visited.find(c) == visited.end(); });
    std::sort(neighbours.begin(), neighbours.end(), [from](char n1, char n2) { return abs(from - n1) < abs(from - n1); });

    bool found = false;
    for (char neighbour : neighbours) {
        auto another_path = FindPath(graph, neighbour, to, visited);

        if (another_path.Size() > 0) {
            web_path.path.insert(web_path.path.end(), another_path.path.begin(), another_path.path.end());
            web_path.minimal_edge = std::min(graph.GetEdgeWeight(from, neighbour), another_path.minimal_edge);
            found = true;
            break;
        }
    }

    if (!found) {
        web_path.path.clear();
    }

    visited.erase(from);
    return web_path;
}

static inline WebPath FindPath(const Graph& graph,
                           char from,
                           char to) {
    std::set<char> visited;
    return FindPath(graph, from, to, visited);
}


inline std::pair<Graph, int> FordFalkerson(Graph& graph, char source, char drain) {
    Graph flow_graph(26);
    flow_graph.SetOffset(graph.GetOffset());
    float flow = 0;

    WebPath path = FindPath(graph, source, drain);
    while (path.Size() != 0) {
        flow += path.minimal_edge;

        for (int i = 0; i < path.Size() - 1; ++i) {
            assert(graph.GetEdgeWeight(path[i], path[i+1]) > 0);
            graph.ChangeWeight(path[i], path[i+1], std::max(graph.GetEdgeWeight(path[i], path[i+1]), 0.0f) - path.minimal_edge);
            graph.ChangeWeight(path[i+1], path[i], std::max(graph.GetEdgeWeight(path[i+1], path[i]), 0.0f) + path.minimal_edge);
            flow_graph.ChangeWeight(path[i], path[i+1], std::max(flow_graph.GetEdgeWeight(path[i], path[i+1]), 0.0f) + path.minimal_edge);
        }

        path = FindPath(graph, source, drain);
    }

    return {flow_graph, flow};
}
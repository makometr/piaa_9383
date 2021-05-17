#pragma once

#include "graph.hpp"
#include <vector>
#include <set>
#include <limits>
#include <cassert>

struct WebPath {
    std::vector<char> path;
    float minimal_edge;

    size_t Size() const { return  path.size(); }
    char operator[](size_t index) const {
        return path[index];
    }
};

static char FindMinimalEdge(const Graph& graph, char from, const std::deque<char>& neighbours,
                            const std::set<char>& visited_neighbours) {
    char max_neighbour = from;
    float minimal_edge = std::numeric_limits<float>::max();
    for (char neighbour : neighbours) {
        if (visited_neighbours.find(neighbour) == visited_neighbours.end() &&
                    minimal_edge > graph.GetEdgeWeight(from, neighbour)) {
            max_neighbour = neighbour;
            minimal_edge = graph.GetEdgeWeight(from, neighbour);
        }
    }
    return max_neighbour;
}

static inline WebPath FindPath(const Graph& graph,
                              char from,
                              char to,
                              std::set<char>& visited) {
    WebPath web_path{std::vector<char>{from}, std::numeric_limits<float>::max()};

    if (from == to)
        return web_path;

    visited.insert(from);

    auto neighbours = graph.GetNeighbours(from, [&visited](char v) { return visited.find(v) == visited.end(); });
    std::reverse(neighbours.begin(), neighbours.end());
    std::set<char> visited_neighbours;
    char max_neighbour = FindMinimalEdge(graph, from, neighbours, visited_neighbours);
    bool found = false;

    while (!found && max_neighbour != from) {
        visited_neighbours.insert(max_neighbour);
        auto another_path = FindPath(graph, max_neighbour, to, visited);

        if (another_path.Size() > 0) {
            web_path.path.insert(web_path.path.end(), another_path.path.begin(), another_path.path.end());
            web_path.minimal_edge = std::min(graph.GetEdgeWeight(from, max_neighbour), another_path.minimal_edge);
            found = true;
        }

        if (!found)
            max_neighbour = FindMinimalEdge(graph, from, neighbours, visited_neighbours);
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
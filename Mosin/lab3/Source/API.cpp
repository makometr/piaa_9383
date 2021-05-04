#include "API.h"

bool input(int& count, char& start, char& end, std::map<char, std::map<char, int>>& graph, std::istream& stream){
    stream >> count >> start >> end;

    char node1, node2;
    int weight = 0;
    for (int i = 0; i < count; ++i) {
        stream >> node1 >> node2 >> weight;
        //Some check for return false
        graph[node1][node2] = weight;
    }

    return true;
}

std::pair<std::vector<char>, int> path(std::map<char, std::map<char, int>>& rGraph, char s, char t) {
    std::pair<std::vector<char>, int> path_flow;

    std::map<char, std::map<char, int>> transposedGraph = transposition(rGraph);

    std::queue<char> queue_from_start;
    queue_from_start.push(s);

    std::vector<char> visited_from_start;
    visited_from_start.push_back(s);

    std::queue<char> queue_from_end;
    queue_from_end.push(t);

    std::vector<char> visited_from_end;
    visited_from_end.push_back(t);

    char node;
    std::map<char, std::pair<char, int>> graph1, graph2;
    while (!queue_from_start.empty() && !queue_from_end.empty()) {
        node = queue_from_start.front();
        queue_from_start.pop();
        if (std::find(visited_from_end.begin(), visited_from_end.end(), node) != visited_from_end.end()) {
            return restore(graph1, graph2, s, t, node);
        }

        for (auto it : rGraph[node]) {
            if (std::find(visited_from_start.begin(), visited_from_start.end(), it.first) == visited_from_start.end() && it.second > 0) {
                queue_from_start.push(it.first);
                visited_from_start.push_back(it.first);
                graph1[it.first] = std::make_pair(node, it.second);
            }
        }

        node = queue_from_end.front();
        queue_from_end.pop();
        if (std::find(visited_from_start.begin(), visited_from_start.end(), node) != visited_from_start.end()) {
            return restore(graph1, graph2, s, t, node);
        }

        for (auto it : transposedGraph[node]) {
            if (std::find(visited_from_end.begin(), visited_from_end.end(), it.first) == visited_from_end.end() && it.second > 0) {
                queue_from_end.push(it.first);
                visited_from_end.push_back(it.first);
                graph2[it.first] = std::make_pair(node, it.second);
            }
        }
    }

    return path_flow;
}

std::map<char, std::map<char, int>> transposition(std::map<char, std::map<char, int>>& graph) {
    std::map<char, std::map<char, int>> transposedGraph;
    for (auto it : graph) {
        for (auto vertex : it.second) {
            transposedGraph[vertex.first][it.first] = vertex.second;
        }
    }
    return transposedGraph;
}

std::pair<std::vector<char>, int> restore(std::map<char, std::pair<char, int>>& graph1, std::map<char, std::pair<char, int>>& graph2, char s, char t, char node) {
    std::vector<char> path;
    int flow = __INT_MAX__;

    path.push_back(node);

    char vertex = node;
    while (vertex != s) {
        path.push_back(graph1[vertex].first);
        flow = std::min(flow, graph1[vertex].second);
        vertex = graph1[vertex].first;
    }
    std::reverse(path.begin(), path.end());

    vertex = node;
    while (vertex != t) {
        path.push_back(graph2[vertex].first);
        flow = std::min(flow, graph2[vertex].second);
        vertex = graph2[vertex].first;
    }

    return std::make_pair(path, flow);
}

std::pair<int, std::map<char, std::map<char, int>>> FordFulkerson(std::map<char, std::map<char, int>>& graph, char s, char t) {
    std::map<char, std::map<char, int>> rGraph = graph;

    int flow = 0;
    for(std::pair<std::vector<char>, int> path_flow = path(rGraph, s, t); !path_flow.first.empty(); path_flow = path(rGraph, s, t)) {
        for (int i = 0; i < path_flow.first.size() - 1; ++i) {
            rGraph[path_flow.first[i]][path_flow.first[i + 1]] -= path_flow.second;
            rGraph[path_flow.first[i + 1]][path_flow.first[i]] += path_flow.second;
        }

        flow += path_flow.second;
    }

    return std::make_pair(flow, rGraph);
}
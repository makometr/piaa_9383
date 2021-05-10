#include <iostream>
#include <fstream>
#include <algorithm>
#include "graph.hpp"
#include "ford_falkerson.hpp"

int main() {
    std::ifstream in("input.txt");

    Graph graph(26);
    auto comparator = [](const auto& p1, const auto& p2) {
        return std::tie(p1.first, p1.second) < std::tie(p2.first, p2.second);
    };
    std::set<std::pair<char, char>, decltype(comparator)> to_check(comparator);

    int n;
    char source, drain;
    in >> n >> source >> drain;

    if (std::isdigit(source))
        graph.SetOffset(48);

    for (int i = 0; i < n; ++i) {
        char u, v;
        float weight;

        in >> u >> v >> weight;

        graph.AddEdge(u, v, weight);
        to_check.insert({u, v});
    }


    auto flow_info = FordFalkerson(graph, source, drain);

    std::cout << flow_info.second << std::endl;
    for (const auto &edge : to_check) {
        float weight = flow_info.first.GetEdgeWeight(edge.first, edge.second);
        if (weight != -1)
            std::cout << edge.first << " " << edge.second << " " << weight << std::endl;
        else
            std::cout << edge.first << " " << edge.second << " " << 0 << std::endl;
    }

    return 0;
}
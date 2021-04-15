#include <iostream>
#include "graph.hpp"
#include "search_algorithms.h"


int main() {
    Graph<char> graph(26);

    char start, end;
    std::cin >> start >> end;

    while (true) {
        char u; std::cin >> u;
        if (std::cin.eof())
            break;

        char v;       std::cin >> v;
        float weight; std::cin >> weight;

        graph.AddEdge(u, v, weight);
    }

    auto path = AStarAlgorithm(graph, start, end);
    std::cout << std::string{path.begin(), path.end()} << std::endl;

    return 0;
}

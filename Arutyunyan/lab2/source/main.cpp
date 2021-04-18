#include <iostream>
#include "graph.hpp"
#include "search_algorithms.h"

bool CheckOkayHeuristics() {
    float prev = 0;
    for (int i = 'a'; i <= 'z'; ++i) {
        for (int j = i + 1; j <= 'z'; ++j) {
            float new_value = Heuristics(i, j);
            if (new_value < prev) {
                return false;
            }
            prev = new_value;
        }
    }

    return true;
}

int main() {
    if (!CheckOkayHeuristics()) {
        std::cout << "Heuristics is not okay!" << std::endl;
        return 1;
    }

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

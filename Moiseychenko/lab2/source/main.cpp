#include "graph.h"

int main() {
    char start, finish;
    std::cin >> start >> finish;
    std::vector<Node*> graph;
    std::vector<Node*> vecToDelete;
    readGraph(graph, start, finish, std::cin);
    std::cout << "greedy: " << greedy(graph, finish) << '\n';
    std::cout << "Astar: " << Astar(graph, finish) << '\n';
    freeMemory(graph);
}
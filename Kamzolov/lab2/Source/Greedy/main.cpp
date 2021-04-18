#include "greedy.h"

int main() {
    char start, finish;
    std::cin >> start >> finish;

    std::vector<Node*> graph;
    std::vector<Node*> vecToDelete;

    initGraph(graph, start, std::cin);

    vecToDelete = graph;

    std::cout << "Path: "<< algo(graph, finish) << '\n';
    freeMemory(vecToDelete);
}

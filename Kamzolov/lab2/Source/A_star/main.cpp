#include "a_star.h"

int main() {
    char start, finish;
    std::cin >> start >> finish;

    std::vector<Node*> graph;
    std::vector<Node*> vecToDelete;

    initGraph(graph, start, finish, std::cin);

    vecToDelete = graph;

    std::cout << "Path: "<< algo(graph, finish) << '\n';

    freeMemory(vecToDelete);
}

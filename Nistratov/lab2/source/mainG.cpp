#include "greedy.h"

int main() {
    char start, end;
    std::cin >> start >> end;

    std::vector<Graph> graph;
    std::vector<char> corr_path;
    Graph cur_path;
    char first_point, second_point;
    float weight;

    while (std::cin >> first_point) {
        std::cin >> second_point >> weight;
        Graph cur_path(first_point, second_point, weight);
        graph.push_back(cur_path);
    }


    Greedy(graph, start, end, corr_path);

    std::cout << getAnswer(corr_path) << std::endl;
    return 0;
}
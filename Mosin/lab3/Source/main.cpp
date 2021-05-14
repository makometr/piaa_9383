#include "API.h"

int main(int argc, char *argv[]) {
    int count;
    char start, end;
    std::map<char, std::map<char, int>> graph;

    if (input(count, start, end, graph, std::cin)) {
        std::pair<int, std::map<char, std::map<char, int>>> path_flow = FordFulkerson(graph, start, end);
        std::cout << path_flow.first << std::endl;
        for (auto i : graph) {
            for (auto j : graph[i.first]) {
                std::cout << i.first << " " << j.first << " ";
                if (graph[i.first][j.first] - path_flow.second[i.first][j.first] > 0) {
                    std::cout << graph[i.first][j.first] - path_flow.second[i.first][j.first] << std::endl;
                }
                else {
                    std::cout << 0 << std::endl;
                }
            }
        }
    }

    return 0;
}
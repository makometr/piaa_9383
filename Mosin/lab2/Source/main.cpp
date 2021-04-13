#include "API.h"

int main(int argc, char *argv[]) {
    std::cout << "INPUT:" << std::endl;
    char start, end;
    std::map<char, std::vector<std::pair<char, float>>> graph;
    if (input(graph, start, end, std::cin)) {
        std::string convert(argv[1]);
        if (convert == "Greed") {
            for (auto it = graph.begin(); it != graph.end(); ++it) {
                std::sort(it->second.begin(), it->second.end(), [](std::pair<char, float> &a, std::pair<char, float> &b) -> bool {return a.second < b.second;});
            }
            std::cout << Greed::way(graph, start, end) << std::endl;
        }
        else if (convert == "Star"){
            for (auto it = graph.begin(); it != graph.end(); ++it) {
                std::sort(it->second.begin(), it->second.end(), [end](std::pair<char, float> &a, std::pair<char, float> &b) -> bool {return Star::heuristic(a.first, end) < Star::heuristic(b.first, end);});
            }
            std::cout << Star::way(graph, start, end) << std::endl;
        }
    }

    return 0;
}
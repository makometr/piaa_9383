#include "FordFulkerson.h"

int main() {
    std::map<char, std::vector<std::pair<char, Edge>>> graph;
    char start, finish;
    int size;

    readGraph(graph, size, start, finish, std::cin);
    std::map<char, std::vector<std::pair<char, Edge>>> indicator = {};
    if(graph == indicator) {
        std::cout << "Wrong input!\n";
    }
    FordFulkerson algosRun = FordFulkerson(graph, start, finish, size);
    algosRun.fordFulkersonAlgo();
    algosRun.printAnswer();
}

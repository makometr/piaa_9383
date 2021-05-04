#include <iostream>

#include "graph.hpp"

#include <sstream>

int main() {

    int edges_amount;
    char source_node, sink_node;

    std::cin >> edges_amount >> source_node >> sink_node;

    Graph graph(source_node, sink_node, edges_amount);
    bool has_read = graph.read_edges(std::cin);
    if(!has_read) {
        std::cout << "can't read\n";
        return 0;
    }
    
    std::cout << graph.ford_fulkerson() << '\n';

    std::cout << graph.print_res_graph();

    return 0;
}
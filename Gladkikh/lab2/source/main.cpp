#include "graph.hpp"

int main() {

    char start_vertex, end_vertex;
    std::cin >> start_vertex >> end_vertex;

    Graph graph(start_vertex, end_vertex);
    if(!graph.read_edges(std::cin)) return 0;
    std::cout << graph.print_vector_to_string() << "\n";
    std::cout << "A Star Path: " << graph.find_path_a_star() << '\n';
    //std::cout << "Greedy Path: " << graph.find_path_greedy() << '\n';

    return 0;
}

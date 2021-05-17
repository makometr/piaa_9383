#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../source/graph.hpp"
#include "../source/ford_falkerson.hpp"

#include <cstdlib>
#include <sstream>
#include <iostream>

TEST_CASE("Adding edges tests") {
    Graph graph(26);

    REQUIRE(graph.GetEdgeWeight('a', 'b') == -1);
    REQUIRE(graph.GetEdgeWeight('c', 't') == -1);
    REQUIRE(graph.GetEdgeWeight('q', 'n') == -1);

    graph.AddEdge('a', 'b', 1023);
    graph.AddEdge('b', 'q', 2);

    REQUIRE(graph.GetEdgeWeight('a', 'b') == 1023);
    REQUIRE(graph.GetEdgeWeight('b', 'q') == 2);
    REQUIRE(graph.GetEdgeWeight('a', 'q') == -1);
    REQUIRE(graph.GetEdgeWeight('a', 'a') == -1);

    graph.AddEdge('b', 'a', 123);
    graph.AddEdge('q', 'b', 22222);

    REQUIRE(graph.GetEdgeWeight('a', 'b') == 1023);
    REQUIRE(graph.GetEdgeWeight('b', 'a') == 123);
    REQUIRE(graph.GetEdgeWeight('b', 'q') == 2);
    REQUIRE(graph.GetEdgeWeight('q', 'b') == 22222);
}


TEST_CASE("Getting neighbours tests") {
    Graph graph(26);

    auto neighbours_empty = graph.GetNeighbours('a');
    REQUIRE(neighbours_empty.size() == 0);

    graph.AddEdge('a', 'b', 123);
    graph.AddEdge('a', 'c', 444);
    auto neighbours_small = graph.GetNeighbours('a');
    REQUIRE((neighbours_small.size() == 2 && neighbours_small[0] == 'b' && neighbours_small[1] == 'c'));

    graph.AddEdge('a', 'n', 1000);
    auto neighbours_with_predicate = graph.GetNeighbours('a', [&graph](char c) { return graph.GetEdgeWeight('a', c) > 999; });
    REQUIRE((neighbours_with_predicate.size() == 1 && neighbours_with_predicate[0] == 'n'));
}

TEST_CASE("First input test") {
    Graph graph(26);

    graph.AddEdge('a', 'b', 7);
    graph.AddEdge('a', 'c', 6);
    graph.AddEdge('b', 'd', 6);
    graph.AddEdge('c', 'f', 9);
    graph.AddEdge('d', 'e', 3);
    graph.AddEdge('d', 'f', 4);
    graph.AddEdge('e', 'c', 2);

    std::ostringstream correct;
    correct << "12\n"
                "a b 6\n"
                "a c 6\n"
                "b d 6\n"
                "c f 8\n"
                "d e 2\n"
                "d f 4\n"
                "e c 2\n";


    auto flow_info = FordFalkerson(graph, 'a', 'f');
    std::ostringstream output;
    output << flow_info.second << "\n";

    std::vector<std::pair<char, char>> to_check = {{'a', 'b'}, {'a', 'c'}, {'b', 'd'}, {'c', 'f'}, {'d', 'e'}, {'d', 'f'}, {'e', 'c'}};
    for (const auto &edge : to_check) {
        float weight = flow_info.first.GetEdgeWeight(edge.first, edge.second);
        if (weight != -1)
            output << edge.first << " " << edge.second << " " << weight << "\n";
        else
            output << edge.first << " " << edge.second << " " << 0 << "\n";
    }

    REQUIRE((correct.str() == output.str()));
}
#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../source/graph.hpp"

#include <cstdlib>

TEST_CASE("Adding edges tests") {
    Graph<int> graph(100);

    std::vector<std::tuple<int, int, int>> edges(50);
    for (int i = 0; i < edges.size(); ++i) {
        int v = rand() % 100, u = rand() % 100;

        if (!graph.HasEdge(v, u)) {
            edges[i] = {v, u, rand() % 1000};
            graph.AddEdge(std::get<0>(edges[i]), std::get<1>(edges[i]), std::get<2>(edges[i]));
        }
    }

    for (const auto& edge : edges) {
        REQUIRE((graph.HasEdge(std::get<0>(edge), std::get<1>(edge)) && 
                graph.GetEdgeWeight(std::get<0>(edge), std::get<1>(edge)) == std::get<2>(edge)));
    }
}


TEST_CASE("Getting neighbours tests") {
    Graph<int> graph(100);

    std::map<int, std::vector<int>> neighbours;
    for (int v = 0; v < 10; ++v) {
        int neighbour = 10 + rand() % 90;
        
        if (!graph.HasEdge(v, neighbour)) {
            neighbours[v].push_back(neighbour);
            graph.AddEdge(v, neighbour, rand() % 500);
        }
    }

    for (int v = 0; v < 10; ++v) {
        auto neighbours_graph = graph.GetNeighbours(v);
        REQUIRE(neighbours[v] == std::vector<int>{neighbours_graph.begin(), neighbours_graph.end()});
    }

    // Все веса у нас удовлетворяют условию 0 <= weight < 500
    for (int v = 0; v < 10; ++v) {
        auto neighbours_graph = graph.GetNeighbours(v, [&graph, v](int c) { return graph.GetEdgeWeight(v, c) >= 500; });
        REQUIRE(neighbours_graph.size() == 0);
    }

    for (int v = 0; v < 10; ++v) {
        auto neighbours_graph = graph.GetNeighbours(v, [](int c) { return false; });
        REQUIRE(neighbours_graph.size() == 0);
    }

    for (int v = 0; v < 10; ++v) {
        int counter = 0;
        auto neighbours_graph = graph.GetNeighbours(
                                        v, [&counter](int c) {
                                            return counter++ < 1 ? true : false;
                                        }
        );
        
        if (neighbours[v].size() >= 1)
            REQUIRE(neighbours_graph.size() == 1);
        else
            REQUIRE(neighbours_graph.size() == 0);
    }
}
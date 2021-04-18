#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "API.h"

TEST_CASE("Input syntax") {
    char start, end;
    std::map<char, std::vector<std::pair<char, float>>> graph;

    SECTION("Check start and finish input syntax") {
        std::istringstream stream("a 3");
        REQUIRE(input(graph, start, end, stream) == false);
        graph.clear();
    }

    SECTION("Check vertices and weight input syntax") {
        std::istringstream stream("a e\n a 2 b");
        REQUIRE(input(graph, start, end, stream) == false);
        graph.clear();
    }

    SECTION("Check for a start vertex") {
        std::istringstream stream("a c\n b c 1");
        REQUIRE(input(graph, start, end, stream) == false);
        graph.clear();
    }

    SECTION("Check for a finish vertex") {
        std::istringstream stream("a c\n a b 1");
        REQUIRE(input(graph, start, end, stream) == false);
        graph.clear();
    }

    SECTION("Valid input syntax") {
        std::istringstream stream("a e\n a b 1\nb e 1");
        REQUIRE(input(graph, start, end, stream) == true);
        graph.clear();
    }
}

TEST_CASE("algorithm") {
    /*
    a d
    a b 1
    a c 2
    b d 3
    c d 1
    */
    std::map<char, std::vector<std::pair<char, float>>> graph = {{'a',{{'b', 1},{'c', 2}}},{'b',{{'d',3}}},{'c',{{'d',1}}}};
    SECTION("Greed") {
        REQUIRE(Greed::way(graph, 'a', 'd') == "abd");
    }

    SECTION("Star") {
        REQUIRE(Star::way(graph, 'a', 'd') == "acd");
    }
}
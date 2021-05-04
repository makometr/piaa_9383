#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "API.h"

TEST_CASE("algorithm") {
    /*
    7
    a
    f
    a b 7
    a c 6
    b d 6
    c f 9
    d e 3
    d f 4
    e c 2
    */
    int count;
    char start, end;
    std::map<char, std::map<char, int>> graph;
    std::istringstream stream("7\na\nf\na b 7\na c 6\nb d 6\nc f 9\nd e 3\nd f 4\ne c 2\n");
    input(count, start, end, graph, stream);
    SECTION("Find path and minimal flow") {
        std::vector<char> test_path = {'a', 'c', 'f'};
        REQUIRE(path(graph, start, end).first == test_path);
        REQUIRE(path(graph, start, end).second == 6);
    }
    SECTION("FordFulkerson") {
        REQUIRE(FordFulkerson(graph, start, end).first == 12);
    }
}
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "API.h"

TEST_CASE("FordFulkerson algorithm") {
    int count;
    char start, end;
    std::map<char, std::map<char, int>> graph;
    std::stringstream stream;
    SECTION("Path found and flow calculated") {
        stream << "7\na\nf\na b 7\na c 6\nb d 6\nc f 9\nd e 3\nd f 4\ne c 2\n";
        input(count, start, end, graph, stream);
        REQUIRE(FordFulkerson(graph, start, end).first == 12);
    }
    SECTION("Path found but flow is zero") {
        stream << "7\na\nf\na b 7\na c 6\nb d 6\nc f 0\nd e 3\nd f 0\ne c 2\n";
        input(count, start, end, graph, stream);
        REQUIRE(FordFulkerson(graph, start, end).first == 0);
    }
    SECTION("Path not found") {
        stream << "7\na\nf\na b 7\na c 6\nb d 6\nc d 9\nd e 3\nd b 4\ne c 2\n";
        input(count, start, end, graph, stream);
        REQUIRE(FordFulkerson(graph, start, end).first == 0);
    }
    SECTION("Numbers only") {
        stream << "7\n1\n6\n1 2 7\n1 3 6\n2 4 6\n3 6 9\n4 5 3\n4 6 4\n5 3 2\n";
        input(count, start, end, graph, stream);
        REQUIRE(FordFulkerson(graph, start, end).first == 12);
    }
}
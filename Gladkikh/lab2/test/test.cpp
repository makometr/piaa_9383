#define CATCH_CONFIG_MAIN

#include "../../catch.hpp"
#include "../source/graph.hpp"

#include <sstream>

TEST_CASE("Graph Constructor and Read Input Test", "[internal Graph Test]" ) {

    char from_vertex = 'a';
    char to_vertex = 'e';

    std::stringstream input_test;
    input_test << "a b 3.0\nb c 1.0\nc d 1.0\na d 5.0\nd e 1.0";

    Graph graph(from_vertex, to_vertex, input_test);

    std::string res = graph.print_vector_to_string();
    REQUIRE(res == "a = [ b d ]; b = [ c ]; c = [ d ]; d = [ e ]; e = [ ]; ");


    std::stringstream input_test2;
    input_test2 << "a b 3.0\nb c 1.0\nc d -1.0\na d 5.0\nd e 1.0";

    Graph graph2(from_vertex, to_vertex, input_test2);

    REQUIRE(graph2.check_input_error() == true);


    std::stringstream input_test3;
    input_test3 << "; b 3.0\nb c 1.0\nc d 1.0\na d 5.0\nd e 1.0";

    Graph graph3(from_vertex, to_vertex, input_test3);

    REQUIRE(graph3.check_input_error() == true);

    std::stringstream input_test4;
    input_test4 << "";

    Graph graph4(from_vertex, to_vertex, input_test4);

    REQUIRE(graph4.check_input_error() == true);

}

TEST_CASE("Find Path Greedy Test", "[internal Graph Test]" ) {

    char from_vertex = 'a';
    char to_vertex = 'e';

    std::stringstream input_test;
    input_test << "a b 3.0\nb c 1.0\nc d 1.0\na d 5.0\nd e 1.0";

    Graph graph(from_vertex, to_vertex, input_test);

    std::string res = graph.find_path_greedy();
    REQUIRE(res == "abcde");


    std::stringstream input_test2;
    input_test2 << "a b 3.0\nb c 1.0";

    Graph graph2(from_vertex, to_vertex, input_test2);

    res = graph2.find_path_greedy();
    REQUIRE(res == "no path");
}

TEST_CASE("Heuristic Test", "[internal Graph Test]" ) {
    char from_vertex = 'a';
    char to_vertex = 'e';

    std::stringstream input_test;
    input_test << "a b 3.0\nb c 1.0\nc d 1.0\na d 5.0\nd e 1.0";

    Graph graph(from_vertex, to_vertex, input_test);

    REQUIRE(graph.heuristics('a', 'e') == 4);

    REQUIRE(graph.heuristics('b', 'c') == 1);
}

TEST_CASE("Find Path A* Test", "[internal Graph Test]" ) {
    char from_vertex = 'a';
    char to_vertex = 'e';

    std::stringstream input_test;
    input_test << "a b 3.0\nb c 1.0\nc d 1.0\na d 5.0\nd e 1.0";

    Graph graph(from_vertex, to_vertex, input_test);

    std::string res = graph.find_path_a_star();
    REQUIRE(res == "ade");

    std::stringstream input_test2;
    input_test2 << "a b 3.0\nb c 1.0\nc d 1.0\na d 5.0\nd e 1.0\na e 1.0";

    Graph graph2(from_vertex, to_vertex, input_test2);

    res = graph2.find_path_a_star();
    REQUIRE(res == "ae");


    std::stringstream input_test3;
    input_test3 << "a b 3.0\nb c 1.0";

    Graph graph3(from_vertex, to_vertex, input_test3);

    res = graph3.find_path_a_star();
    REQUIRE(res == "no path");
}

#define CATCH_CONFIG_MAIN

#include "../../catch.hpp"
#include "../source/graph.hpp"

#include <sstream>

TEST_CASE("Graph Constructor and Read Input Test", "[internal Graph Test]" ) {

    std::stringstream input_test;
    int edge_amount = 3;
    char source_symbol = 'a';
    char sink_symbol = 'c';
    input_test << "a b 3\nb c 2\na c 5";

    Graph graph(source_symbol, sink_symbol, edge_amount);
    graph.read_edges(input_test);

    std::string res = graph.to_string();
    REQUIRE(res == "a: b(3/0) c(5/0) \nb: a(0/3) c(2/0) \nc: b(0/2) a(0/5) \n");


    std::stringstream input_test_2;
    input_test_2 << "a b 3\nb c 2\na c -5";

    Graph graph_2(source_symbol, sink_symbol, edge_amount);

    REQUIRE(graph_2.read_edges(input_test_2) == false);

    std::stringstream input_test_3;
    char source_symbol_3 = '1';
    char sink_symbol_3 = '3';
    input_test_3 << "1 2 3\n2 3 2\n1 3 5";

    Graph graph_3(source_symbol_3, sink_symbol_3, edge_amount);
    graph_3.read_edges(input_test_3);

    res = graph_3.to_string();
    REQUIRE(res == "1: 2(3/0) 3(5/0) \n2: 1(0/3) 3(2/0) \n3: 2(0/2) 1(0/5) \n");

}


TEST_CASE("Comparator and Find Path Test", "[internal Graph Test]" ) {

    Neighbour first_neighbour = {'a', {}};
    Neighbour second_neighbour = {'c', {}};

    REQUIRE(neighbour_cmp(first_neighbour, second_neighbour) == false);

    auto join_path = [](std::vector<char> path) -> std::string {
        std::string out;
        for(const auto& el: path) {
            out += el;
        }
        return out;
    };

    std::stringstream input_test;
    int edge_amount = 7;
    char source_symbol = 'a';
    char sink_symbol = 'f';
    input_test << "a b 7\na c 6\nb d 6\nc f 9\nd e 3\nd f 4\ne c 2";

    Graph graph(source_symbol, sink_symbol, edge_amount);
    graph.read_edges(input_test);

    std::vector<char> path1 = graph.test_find_path(source_symbol, sink_symbol);
    
    REQUIRE(join_path(path1) == "fdba");


    std::stringstream input_test_2;
    int edge_amount_2 = 5;
    char source_symbol_2 = '1';
    char sink_symbol_2 = '4';
    input_test_2 << "1 2 20\n1 3 1\n2 3 20\n2 4 1\n3 4 20";

    Graph graph2(source_symbol_2, sink_symbol_2, edge_amount_2);
    graph2.read_edges(input_test_2);

    std::vector<char> path2 = graph2.test_find_path(source_symbol_2, sink_symbol_2);
    
    REQUIRE(join_path(path2) == "4321");
}

TEST_CASE("Max Flow and Res Graph Test", "[internal Graph Test]" ) {

    std::stringstream input_test;
    int edge_amount = 7;
    char source_symbol = 'a';
    char sink_symbol = 'f';
    input_test << "a b 7\na c 6\nb d 6\nc f 9\nd e 3\nd f 4\ne c 2";

    Graph graph(source_symbol, sink_symbol, edge_amount);
    graph.read_edges(input_test);

    int max_flow = graph.ford_fulkerson();
    
    REQUIRE(max_flow == 12);
    REQUIRE(graph.print_res_graph() == "a b 6\na c 6\nb d 6\nc f 8\nd e 2\nd f 4\ne c 2\n");


    std::stringstream input_test_2;
    int edge_amount_2 = 5;
    char source_symbol_2 = '1';
    char sink_symbol_2 = '4';
    input_test_2 << "1 2 20\n1 3 1\n2 3 20\n2 4 1\n3 4 20";

    Graph graph_2(source_symbol_2, sink_symbol_2, edge_amount_2);
    graph_2.read_edges(input_test_2);

    int max_flow_2 = graph_2.ford_fulkerson();
    
    REQUIRE(max_flow_2 == 21);
    REQUIRE(graph_2.print_res_graph() == "1 2 20\n1 3 1\n2 3 19\n2 4 1\n3 4 20\n");
}

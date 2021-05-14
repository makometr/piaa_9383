#define CATCH_CONFIG_MAIN

#include "../Source/FordFulkerson.h"
#include "catch.hpp"
#include "sstream"


TEST_CASE("Read Graph", "[Read Test]" ) {
    std::istringstream in("7 \na\nf\na b 7\na c 6\nb d 6\nc f 9\nd e 3\n d f 4\ne c 2\n");
    std::map<char, std::vector<std::pair<char, Edge>>> graph;
    int size;
    char start, finish;


    std::map<char, std::vector<std::pair<char, Edge>>> graphPredict {
        { 'a', { std::make_pair<char, Edge>('b', { 7, 0, true } ),
                 std::make_pair<char, Edge>('c', { 6, 0, true } ) } },
        { 'b', { std::make_pair<char, Edge>('a', { 0, 7, false } ),
                 std::make_pair<char, Edge>('d', { 6, 0, true } ) } },
        { 'c', { std::make_pair<char, Edge>('a', { 0, 6, false } ),
                 std::make_pair<char, Edge>('f', { 9, 0, true } ),
                 std::make_pair<char, Edge>('e', { 0, 2, false } ) } },
        { 'd', { std::make_pair<char, Edge>('b', { 0, 6, false } ),
                 std::make_pair<char, Edge>('e', { 3, 0, true } ),
                 std::make_pair<char, Edge>('f', { 4, 0, true } ) } },
        { 'e', { std::make_pair<char, Edge>('d', { 0, 3, false } ),
                 std::make_pair<char, Edge>('c', { 2, 0, true } ) } },
        { 'f', { std::make_pair<char, Edge>('c', { 0, 9, false } ),
                 std::make_pair<char, Edge>('d', { 0, 4, false } ) } },
    };
    int sizePredict = 7;
    char startPredict = 'a';
    char finishPredict = 'f';

    readGraph(graph, size, start, finish, in);
    REQUIRE(graph['a'] == graphPredict['a']);
    REQUIRE(graph['b'] == graphPredict['b']);
    REQUIRE(graph['c'] == graphPredict['c']);
    REQUIRE(graph['d'] == graphPredict['d']);
    REQUIRE(graph['e'] == graphPredict['e']);
    REQUIRE(graph['f'] == graphPredict['f']);
    REQUIRE(size == sizePredict);
    REQUIRE(start == startPredict);
    REQUIRE(finish == finishPredict);

    std::istringstream in2("0\na\nb");
    graph = {};
    graphPredict = {};
    sizePredict = 0;
    startPredict = 'a';
    finishPredict = 'b';

    readGraph(graph, size, start, finish,  in2);
    REQUIRE(graph == graphPredict);
    REQUIRE(size == sizePredict);
    REQUIRE(start == startPredict);
    REQUIRE(finish == finishPredict);

    std::istringstream in3("7 \na\nf\na b -7\na c 6\nb d 6\nc f 9\nd e 3\n d f 4\ne c 2\n");
    graphPredict = {};
    graph = {};
    readGraph(graph, size, start, finish,  in3);
    REQUIRE(graph == graphPredict);
}

TEST_CASE("Search way", "[Search Test]") {
    std::istringstream in("7 \na\nf\na b 7\na c 6\nb d 6\nc f 9\nd e 3\n d f 4\ne c 2\n");
    std::map<char, std::vector<std::pair<char, Edge>>> graph;
    int size;
    char start, finish;
    readGraph(graph, size, start, finish,  in);

    FordFulkerson testAlgo = FordFulkerson(graph, start, finish, size);
    REQUIRE(testAlgo.search(start) == true);

    std::istringstream in2("1 \na\nb\na b 7");
    graph = {};
    readGraph(graph, size, start, finish,  in2);

    testAlgo = FordFulkerson(graph, start, finish, size);
    REQUIRE(testAlgo.search(start) == true);

    std::istringstream in3("1 \na\nb\na с 7");
    graph = {};
    readGraph(graph, size, start, finish,  in3);

    testAlgo = FordFulkerson(graph, start, finish, size);
    REQUIRE(testAlgo.search(start) == false);
}

TEST_CASE("Test main algorithm", "[Test Algo]") {
    std::istringstream in("7 \na\nf\na b 7\na c 6\nb d 6\nc f 9\nd e 3\n d f 4\ne c 2\n");
    std::map<char, std::vector<std::pair<char, Edge>>> graph;
    int size;
    char start, finish;
    readGraph(graph, size, start, finish,  in);

    FordFulkerson testAlgo = FordFulkerson(graph, start, finish, size);
    testAlgo.fordFulkersonAlgo();

    REQUIRE(testAlgo.maxFlow == 12);

    std::istringstream in2("4 \n a \n d \n a b 3 \n a c 3 \n c d 3 \n b d 3\n");
    graph = {};
    readGraph(graph, size, start, finish,  in2);

    testAlgo = FordFulkerson(graph, start, finish, size);
    testAlgo.fordFulkersonAlgo();

    REQUIRE(testAlgo.maxFlow == 6);
}

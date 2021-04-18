#define CATCH_CONFIG_MAIN

#include "../Source/A_star/a_star.h"
#include "catch.hpp"
#include "sstream"

TEST_CASE("Right input", "[Read Test]" ) {
    std::istringstream in("a b 1.0\nb c 1.0\nc a 1.0\na d 8.0");
    std::vector<Node*> test;

    char start = 'a';
    char finish = 'd';
    initGraph(test, start, finish, in);

    std::string answer = "vertex: a, neighbours: [b, d,  ]; \n"
                          "vertex: b, neighbours: [c,  ]; \n"
                          "vertex: c, neighbours: [a,  ]; \n"
                          "vertex: d, neighbours: [ ]; \n";
    REQUIRE(vecToString(test) == answer);


    start = 'a';
    finish = 'f';
    test.clear();
    //every line new unique char
    std::istringstream in2("a c 1.0\na b 1.0\nc d 2.0\nb e 2.0\nd f 3.0\ne f 3.0");
    initGraph(test, start, finish, in2);

    REQUIRE(test.size() == 6);

    start = 'a';
    finish = 'f';
    test.clear();
    //only three unique chars in 6 lines
    std::istringstream in3("a b 1.0\nb a 1.0\na c 1.0\nc a 1.0\nc b 1.0\nb c 1.0");
    initGraph(test, start, finish, in3);

    REQUIRE(test.size() == 3);
}

TEST_CASE("Wrong input", "[Read Test]") {
    //not include the line with edgeLength <= 0
    std::istringstream in("a b 1.0\nb c -1.0\nc a 1.0\na d 8.0");
    std::vector<Node*> test;

    char start = 'a';
    char finish = 'd';
    initGraph(test, start, finish, in);

    std::string answer = "vertex: a, neighbours: [b, d,  ]; \n"
                          "vertex: b, neighbours: [ ]; \n"
                          "vertex: c, neighbours: [a,  ]; \n"
                          "vertex: d, neighbours: [ ]; \n";
    REQUIRE(vecToString(test) == answer);

    start = 'a';
    finish = 'f';
    test.clear();
    //not include the line with symbol that do not belong english letters range(;)
    std::istringstream in2(". c 1.0\n. b 1.0\nc d 2.0\nb e 2.0\nd f 3.0\ne f 3.0");
    initGraph(test, start, finish, in2);

    REQUIRE(test.size() == 5);

    start = 'a';
    finish = 'f';
    test.clear();
    std::istringstream in3("");
    initGraph(test, start, finish, in3);

    REQUIRE(!test.size());
}

TEST_CASE("Check heuristic function", "[Heuristic Test]" ) {

    char start = 'a';
    char finish = 'b';
    REQUIRE(heuristic(start, finish) == 1);

    start = 'a';
    finish = 'z';
    REQUIRE(heuristic(start, finish) == 25);
}

TEST_CASE("If can find", "[customFind Test]") {
    std::istringstream in("a b 1.0\nb c 1.0\nc a 1.0\na d 8.0");
    std::vector<Node*> test;

    char start = 'a';
    char finish = 'd';
    initGraph(test, start, finish, in);
    char find = 'b';
    REQUIRE(customFind(test, find) == 1);

    start = 'a';
    finish = 'f';
    test.clear();
    std::istringstream in2("a c 1.0\na b 1.0\nc d 2.0\nb e 2.0\nd f 3.0\ne f 3.0");
    find = 'f';
    initGraph(test, start, finish, in2);

    REQUIRE(customFind(test, find) == 5);

    find = 'z';
    REQUIRE(customFind(test, find) == -1);
}

TEST_CASE("Find path A-star", "[Algorithm Test]" ) {

    std::istringstream in("a b 1.0\nb c 1.0\nc a 1.0\na d 8.0");
    std::vector<Node*> test;

    char start = 'a';
    char finish = 'd';
    initGraph(test, start, finish, in);

    std::string answer = "ad";
    REQUIRE(algo(test, finish) == answer);


    start = 'a';
    finish = 'f';
    test.clear();
    std::istringstream in2("a c 1.0\na b 1.0\nc d 2.0\nb e 2.0\nd f 3.0\ne f 3.0");
    initGraph(test, start, finish, in2);

    REQUIRE(algo(test, finish).size() == 4);

    start = 'a';
    finish = 'f';
    test.clear();
    std::istringstream in3("a c 1.0\na b 1.0\nc d 2.0\nb e 2.0\n. f 3.0\n. f 3.0");
    initGraph(test, start, finish, in3);

    REQUIRE(algo(test, finish) == "No path.");
}

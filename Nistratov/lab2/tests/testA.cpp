#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../source/graph.h"
#include <sstream>
    
TEST_CASE("A* test for different values" ) {
    std::stringstream ss;
    char v1, v2;
    float weight, h1, h2;
    SECTION("Значение стоимости пути одинаковые") {
        Graph *graph = new Graph('a', 'e');
        ss << "a b 3.0 4.0 3.0 \n \
           b c 1.0 3.0 2.0 \n \
           c d 1.0 2.0 1.0 \n \
           a d 5.0 4.0 1.0 \n \
           d e 1.0 1.0 0.0 \n";
        while (ss >> v1 >> v2 >> weight >> h1 >> h2)
        {
            graph->inputNode(v1, v2, abs(weight));
            graph->getNodeByName(v1)->heuristic = h1;
            graph->getNodeByName(v2)->heuristic = h2;
        }
        graph->AStar();
        REQUIRE(graph->getAnswer() == "ade");
    }
    SECTION("Путь abcde меньше ade") {
        Graph *graph = new Graph('a', 'e');
        ss << "a b 3.0 4.0 3.0 \n \
           b c 1.0 3.0 2.0 \n \
           c d 1.0 2.0 1.0 \n \
           a d 6.0 4.0 1.0 \n \
           d e 1.0 1.0 0.0 \n";
        while (ss >> v1 >> v2 >> weight >> h1 >> h2)
        {
            graph->inputNode(v1, v2, abs(weight));
            graph->getNodeByName(v1)->heuristic = h1;
            graph->getNodeByName(v2)->heuristic = h2;
        }
        graph->AStar();
        REQUIRE(graph->getAnswer() == "abcde");
    }
    SECTION("Значения эвристики пустые") {
        Graph *graph = new Graph('a', 'e');
        ss << "a b 3.0 0.0 0.0 \n \
           b c 1.0 0.0 0.0 \n \
           c d 1.0 0.0 0.0 \n \
           a d 5.0 0.0 0.0 \n \
           d e 1.0 0.0 0.0 \n";
        while (ss >> v1 >> v2 >> weight >> h1 >> h2)
        {
            graph->inputNode(v1, v2, abs(weight));
            graph->getNodeByName(v1)->heuristic = h1;
            graph->getNodeByName(v2)->heuristic = h2;
        }
        graph->AStar();
        REQUIRE(graph->getAnswer() == "ade");
    }
    SECTION("Начало графа не с 1 точки") {
    Graph *graph = new Graph('c', 'e');
    ss << "a b 3.0 4.0 3.0 \n \
        b c 1.0 3.0 2.0 \n \
        c d 1.0 2.0 1.0 \n \
        a d 5.0 4.0 1.0 \n \
        d e 1.0 1.0 0.0 \n";
    while (ss >> v1 >> v2 >> weight >> h1 >> h2)
    {
        graph->inputNode(v1, v2, abs(weight));
        graph->getNodeByName(v1)->heuristic = h1;
        graph->getNodeByName(v2)->heuristic = h2;
    }
    graph->AStar();
    REQUIRE(graph->getAnswer() == "cde");
    }         
    SECTION("Отрицательные значения веса") {
        Graph *graph = new Graph('a', 'e');
        ss << "a b -3.0 4.0 3.0 \n \
           b c -1.0 3.0 2.0 \n \
           c d -1.0 2.0 1.0 \n \
           a d -5.0 4.0 1.0 \n \
           d e -1.0 1.0 0.0 \n";
        while (ss >> v1 >> v2 >> weight >> h1 >> h2)
        {
            graph->inputNode(v1, v2, abs(weight));
            graph->getNodeByName(v1)->heuristic = h1;
            graph->getNodeByName(v2)->heuristic = h2;
        }
        graph->AStar();
        REQUIRE(graph->getAnswer() == "ade");
    } 
    SECTION("Отрицательные значения эвристики") {
        Graph *graph = new Graph('a', 'e');
        ss << "a b 3.0 -4.0 -3.0 \n \
           b c 1.0 -3.0 -2.0 \n \
           c d 1.0 2.0 1.0 \n \
           a d 5.0 4.0 -1.0 \n \
           d e 1.0 -1.0 0.0 \n";
        while (ss >> v1 >> v2 >> weight >> h1 >> h2)
        {
            graph->inputNode(v1, v2, abs(weight));
            graph->getNodeByName(v1)->heuristic = h1;
            graph->getNodeByName(v2)->heuristic = h2;
        }
        graph->AStar();
        REQUIRE(graph->getAnswer() == "ade");
    }
    SECTION("Пусть задан сразу") {
        Graph *graph = new Graph('a', 'b');
        ss << "a b 3.0 4.0 3.0 \n";
        while (ss >> v1 >> v2 >> weight >> h1 >> h2)
        {
            graph->inputNode(v1, v2, abs(weight));
            graph->getNodeByName(v1)->heuristic = h1;
            graph->getNodeByName(v2)->heuristic = h2;
        }
        graph->AStar();
        REQUIRE(graph->getAnswer() == "ab");
    }    

}
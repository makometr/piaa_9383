#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../source/greedy.h"

TEST_CASE("A* test for different values" ) {
    std::stringstream ss;
    std::vector<Graph> graph;
    std::vector<char> corr_path;
    char first_point, second_point;
    float weight;
    SECTION("Первый наименьший") {
            ss << "a b  3.0\n \
            b c 1.0  \n \
            c d 1.0  \n \
            a d 5.0  \n \
            d e 1.0  \n";
        while (ss >> first_point) {
            ss >> second_point >> weight;
            Graph cur_path(first_point, second_point, weight);
            graph.push_back(cur_path);
        }

        Greedy(graph, 'a', 'e', corr_path);
        REQUIRE(getAnswer(corr_path) == "abcde");
    }  
    SECTION("Первый наименьший №2") {
        ss << "a b  3.0\n \
           b c 1.0  \n \
           c d 1.0  \n \
           a d 2.0  \n \
           d e 1.0  \n";
        while (ss >> first_point) {
            ss >> second_point >> weight;
            Graph cur_path(first_point, second_point, weight);
            graph.push_back(cur_path);
        }

        Greedy(graph, 'a', 'e', corr_path);
        REQUIRE(getAnswer(corr_path) == "ade");
    }
    SECTION("Одинаковые стоимости") {
        ss << "a b  1.0\n \
           b c 1.0  \n \
           c d 1.0  \n \
           a d 1.0  \n \
           d e 1.0  \n";
        while (ss >> first_point) {
            ss >> second_point >> weight;
            Graph cur_path(first_point, second_point, weight);
            graph.push_back(cur_path);
        }

        Greedy(graph, 'a', 'e', corr_path);
        REQUIRE(getAnswer(corr_path) == "abcde");
    }    
    SECTION("Начало не с первого элемента") {
        ss << "a b  3.0\n \
           b c 1.0  \n \
           c d 1.0  \n \
           a d 2.0  \n \
           d e 1.0  \n";
        while (ss >> first_point) {
            ss >> second_point >> weight;
            Graph cur_path(first_point, second_point, weight);
            graph.push_back(cur_path);
        }

        Greedy(graph, 'c', 'e', corr_path);
        REQUIRE(getAnswer(corr_path) == "cde");
    }
    SECTION("Путь задан сразу") {
        ss << "a b  3.0\n ";
        while (ss >> first_point) {
            ss >> second_point >> weight;
            Graph cur_path(first_point, second_point, weight);
            graph.push_back(cur_path);
        }

        Greedy(graph, 'a', 'b', corr_path);
        REQUIRE(getAnswer(corr_path) == "ab");
    }      
}
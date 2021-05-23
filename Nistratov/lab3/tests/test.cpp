#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <sstream>

#include "../source/ford_falk.h"

TEST_CASE("Поиск пути по наибольшей остаточной пропускной способности" ) {
    std::stringstream ss;
    FFsolver ff;
    SECTION("Путь существует") {
        ss << "3 a e a b 2 b e 3 a c 1";
        ff.setInput(ss);
        REQUIRE(ff.findPath(ff.edges) == true);
    }
    SECTION("Путь существует, наибольшая остаточная пропускная способность приводит в тупик") {
        ss << "3 a e a b 2 b e 3 a c 7";
        ff.setInput(ss);
        REQUIRE(ff.findPath(ff.edges) == true);
    }
    SECTION("Путь не существует") {
        ss << "3 a e a b 2 b с 3 a c 1";
        ff.setInput(ss);
        REQUIRE(ff.findPath(ff.edges) == false);
    }
    SECTION("Путь существует, но все пути посещены") {
        ss << "3 a e a b 2 b e 3 a c 1";
        ff.visited.push_back('e');
        ff.visited.push_back('b');
        ff.setInput(ss);
        REQUIRE(ff.findPath(ff.edges) == false);
    }                      
}  

TEST_CASE("Алгоритм Форда-Фалкерсона"){
    std::stringstream ss;
    FFsolver ff;
    SECTION("Граф соеденен"){
        ss << "7 a f a b 7 a c 6 b d 6 c f 9 d e 3 d f 4 e c 2";
        ff.setInput(ss);
        auto a = ff.FordFulkerson();
        ss << "7 a f a b 6 a c 6 b d 6 c f 8 d e 2 d f 4 e c 2";
        ff.setInput(ss);
        REQUIRE(a.first == 12);
        REQUIRE(a.second == ff.edges);
    }
    SECTION("Граф задан числами"){
        ss << "7 1 7 1 2 7 1 3 6 2 4 6 3 7 9 4 5 3 4 7 4 5 3 2";
        ff.setInput(ss);
        auto a = ff.FordFulkerson();
        ss << "7 1 7 1 2 6 1 3 6 2 4 6 3 7 8 4 5 2 4 7 4 5 3 2";
        ff.setInput(ss);
        REQUIRE(a.first == 12);
        REQUIRE(a.second == ff.edges);
    }
    SECTION("Ноды в цикле"){
        ss << "3 a d a b 2 b c 3 c d 2";
        ff.setInput(ss);
        auto a = ff.FordFulkerson();
        ss << "3 a d a b 2 b c 2 c d 2";
        ff.setInput(ss);
        REQUIRE(a.first == 2);
        REQUIRE(a.second == ff.edges);
    }
}
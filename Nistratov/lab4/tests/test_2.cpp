#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/lab4_2.hpp"

TEST_CASE("Префикс-функция") {
    SECTION("Каждый символ новый преффикс") {
        std::string T = "abcdefg";
        std::vector<int> checker = {0, 0, 0, 0, 0, 0, 0};
        auto answer = prefix_function(T);
        REQUIRE(answer == checker);
    }
    SECTION("Каждый символ суфикс первого символа") {
        std::string T = "aaaaaaaa";
        std::vector<int> checker = {0, 1, 2, 3, 4, 5, 6, 7};
        auto answer = prefix_function(T);
        REQUIRE(answer == checker);
    } 
    SECTION("Преффикс ada") {
        std::string T = "adabadaada";
        std::vector<int> checker = {0, 0, 1, 0, 1, 2, 3, 1, 2, 3};
        auto answer = prefix_function(T);
        REQUIRE(answer == checker);
    }
    SECTION("Преффикс ab") {
        std::string T = "abab";
        std::vector<int> checker = {0, 0, 1, 2};
        auto answer = prefix_function(T);
        REQUIRE(answer == checker);
    }                  
}  

TEST_CASE("Алгоритм Кнута-Морриса-Пратта для подсчета сдвигов"){
    SECTION("Отсутсвует строка") {
        std::string T = "abcd";
        std::string P = "efgp";
        std::vector<int> checker = {-1};
        auto answer = KMP(P, T);
        REQUIRE(!answer.size());
    }
    SECTION("Необходим 1 сдвиг") {
        std::string T = "bcdefa";
        std::string P = "abcdef";
        std::vector<int> checker = {1};
        auto answer = KMP(P, T);
        REQUIRE(answer == checker);
    }
    SECTION("Вхождение строки несколько раз") {
        std::string T = "defabc";
        std::string P = "abcdef";
        std::vector<int> checker = {3};
        auto answer = KMP(P, T);
        REQUIRE(answer == checker);
    }
} 
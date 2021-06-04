#define CATCH_CONFIG_MAIN
#include "catch.hpp" 
#include "../source/lb5_2.h"


TEST_CASE("Тест для функции Partitioning") {

    SECTION("1 случай") {
        std::vector<std::pair<std::string, int>> check;
        check.push_back({ "A", 0 });
        check.push_back({ "A", 3 });
        const std::string& p = "A$$A$";
        const char& joker = '$';
        std::vector<std::pair<std::string, int>> patterns;
        Partitioning(p, joker, patterns);
        CHECK(patterns == check);
    }

    SECTION("2 случай") {
        std::vector<std::pair<std::string, int>> check;
        check.push_back({ "A", 0 });
        check.push_back({ "A", 1 });
        check.push_back({ "A", 2 });
        check.push_back({ "A", 3 });
        check.push_back({ "A", 4 });
        const std::string& p = "AAAAA";
        const char& joker = '$';
        std::vector<std::pair<std::string, int>> patterns;
        Partitioning(p, joker, patterns);
        CHECK(patterns == check);
    }

    SECTION("3 случай") {
        std::vector<std::pair<std::string, int>> check;
        const std::string& p = "$$$$$";
        const char& joker = '$';
        std::vector<std::pair<std::string, int>> patterns;
        Partitioning(p, joker, patterns);
        CHECK(patterns == check);
    }
}


TEST_CASE("Тест для функции LongestChain") {

    SECTION("1 случай") {
        std::pair<int, int> check = { 1, 0 };
        std::pair<int, int> longest = { 0, 0 };
        const std::string& p = "A$$A$";
        const char& joker = '$';
        std::vector<std::pair<std::string, int>> patterns;
        Partitioning(p, joker, patterns);
        Bor* bor = CreateBor(patterns);
        Links(bor);
        int depth = 0;
        longest = LongestChain(bor, bor, depth);
        CHECK(longest == check);
    }

    SECTION("2 случай") {
        std::pair<int, int> check = { 5, 0 };
        std::pair<int, int> longest = { 0, 0 };
        const std::string& p = "AAAAA";
        const char& joker = '$';
        std::vector<std::pair<std::string, int>> patterns;
        Partitioning(p, joker, patterns);
        Bor* bor = CreateBor(patterns);
        Links(bor);
        int depth = 0;
        longest = LongestChain(bor, bor, depth);
        CHECK(longest == check);
    }

    SECTION("3 случай") {
        std::pair<int, int> check = { 1, 0 };
        std::pair<int, int> longest = { 0, 0 };
        const std::string& p = "$$$$$";
        const char& joker = '$';
        std::vector<std::pair<std::string, int>> patterns;
        Partitioning(p, joker, patterns);
        Bor* bor = CreateBor(patterns);
        Links(bor);
        int depth = 0;
        longest = LongestChain(bor, bor, depth);
        CHECK(longest == check);
    }
}


TEST_CASE("Тест для функции AhoCorasick") {

    SECTION("1 случай") {
        std::string T = "ACTANCA";
        std::string P = "A$$A$";
        char joker = '$';
        std::vector<std::pair<std::string, int>> patterns;
        std::vector<std::pair<int, int>> result;
        std::vector<std::pair<int, int>> check;
        check.push_back({ 1, 0 });
        Partitioning(P, joker, patterns);
        AhoCorasick(T, patterns, result, P.length());
        CHECK(result == check);
    }

    SECTION("2 случай") {
        std::string T = "ACTANCA";
        std::string P = "AAA";
        char joker = '$';
        std::vector<std::pair<std::string, int>> patterns;
        std::vector<std::pair<int, int>> result;
        std::vector<std::pair<int, int>> check;
        Partitioning(P, joker, patterns);
        AhoCorasick(T, patterns, result, P.length());
        CHECK(result == check);
    }

    SECTION("3 случай") {
        std::string T = "ACTANCA";
        std::string P = "$$$";
        char joker = '$';
        std::vector<std::pair<std::string, int>> patterns;
        std::vector<std::pair<int, int>> result;
        std::vector<std::pair<int, int>> check;
        check.push_back({ 1, 0 });
        check.push_back({ 2, 0 });
        check.push_back({ 3, 0 });
        check.push_back({ 4, 0 });
        check.push_back({ 5, 0 });
        Partitioning(P, joker, patterns);
        AhoCorasick(T, patterns, result, P.length());
        CHECK(result == check);
    }
}

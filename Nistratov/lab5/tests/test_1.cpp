#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/lab5_1.hpp"

bool compare_res(std::vector<std::pair<int, int>> res, std::vector<std::pair<int, int>> ans){
    if (res.size() != ans.size()) return false;
    if (res.empty() && ans.empty()) return true;
    for (size_t i = 0; i < res.size(); i++){
        if (res[i].first != ans[i].first || res[i].second != ans[i].second) return false;
    }
    return true;
}

/*bool compare_res(std::vector<int> res, std::vector<int> ans){
    if (res.size() != ans.size()) return false;
    for (size_t i = 0; i < res.size(); i++){
        if (res[i] != ans[i]) return false;
    }
    return true;
}*/

TEST_CASE("Ахо-Корасик") {
    SECTION("Шаблоны не пересекаются") {
        std::vector<std::pair<int, int>> ans = {{1, 2}, {2, 1}, {4, 3}};
        AhoCorasick ak("NTAG");
        ak.addPattern("TA", 1);
        ak.addPattern("N", 2);
        ak.addPattern("G", 3);
        ak.createSuffixLinks();
        auto res = ak.find_ak();
        REQUIRE(compare_res(res, ans));
    }
    SECTION("Шаблоны пересекаются") {
        std::vector<std::pair<int, int>> ans = {{2, 3}};
        AhoCorasick ak("NTAG");
        ak.addPattern("TAGT", 1);
        ak.addPattern("TAG", 2);
        ak.addPattern("T", 3);
        ak.createSuffixLinks();
        auto res = ak.find_ak();
        REQUIRE(compare_res(res, ans));
    }
    SECTION("Строка из одного символа с 1 шаблном") {
        std::vector<std::pair<int, int>> ans = {{1, 1}, {2, 1}, {3, 1}, {4, 1}};
        AhoCorasick ak("AAAA");
        ak.addPattern("A", 1);
        ak.createSuffixLinks();
        auto res = ak.find_ak();
        REQUIRE(compare_res(res, ans));
    }
    SECTION("Шаблоны отсутсвуют в строке") {
        std::vector<std::pair<int, int>> ans;
        AhoCorasick ak("AAAA");
        ak.addPattern("C", 1);
        ak.addPattern("T", 2);
        ak.addPattern("G", 3);
        ak.createSuffixLinks();
        auto res = ak.find_ak();
        REQUIRE(compare_res(res, ans));
    }         
}

TEST_CASE("Ахо-Корасик, задача с Джокером") {
    SECTION("Отсутствующий шаблон, поиск по тексту \"NTAG\"") {  
    }  
}
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/lab5_2.hpp"


bool compare_res(std::vector<int> res, std::vector<int> ans){
    if (res.size() != ans.size()) return false;
    for (size_t i = 0; i < res.size(); i++){
        if (res[i] != ans[i]) return false;
    }
    return true;
}

TEST_CASE("Ахо-Корасик, задача с Джокером") {
    SECTION("Шаблон совпадает с 1 символа") {
        std::vector<int> ans = {1};
        AhoCorasick ak("ACTANCA", "A$$A$");
        ak.split_by_joker('$');
        ak.createSuffixLinks();
        auto res = ak.find_ak();
        REQUIRE(compare_res(res, ans));
    }
    SECTION("Шаблон совпадает со 2 символа") {
        std::vector<int> ans = {2};
        AhoCorasick ak("ACTANCA", "C$A$");
        ak.split_by_joker('$');
        ak.createSuffixLinks();
        auto res = ak.find_ak();
        REQUIRE(compare_res(res, ans));
    }
    SECTION("Символ Джокера отличный от $") {
        std::vector<int> ans = {1}; 
        AhoCorasick ak("ACTANCA", "A44A4");
        ak.split_by_joker('4');
        ak.createSuffixLinks();
        auto res = ak.find_ak();
        REQUIRE(compare_res(res, ans));
    }
    SECTION("Известен 1 символ шаблона") {
        std::vector<int> ans = {2};
        AhoCorasick ak("ACTANCA", "C$$$");
        ak.split_by_joker('$');
        ak.createSuffixLinks();
        auto res = ak.find_ak();
        REQUIRE(compare_res(res, ans));
    }     
    SECTION("Шаблон встречается 2 раза") {
        std::vector<int> ans = {1, 3};
        AhoCorasick ak("ACAD", "A$");
        ak.split_by_joker('$');
        ak.createSuffixLinks();
        auto res = ak.find_ak();
        REQUIRE(compare_res(res, ans));
    }      
}
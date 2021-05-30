#define CATCH_CONFIG_MAIN

#include "../../catch.hpp"
#include "../source/kmp.hpp"

#include <sstream>

TEST_CASE("Read Function Test", "[internal KMP Test]" ) {
    std::string str1, str2;
    std::stringstream input_test;
    input_test << "abc\nabcd";

    bool read_result = read_strings(str1, str2, input_test);

    REQUIRE(read_result == true);
    REQUIRE(str1 == "abc");
    REQUIRE(str2 == "abcd");

    str1.clear();
    str2.clear();
    std::stringstream input_test2;
    input_test2 << "def\n";

    read_result = read_strings(str1, str2, input_test2);

    REQUIRE(read_result == false);
}

TEST_CASE("Prefix Function Test", "[internal KMP Test]" ) {
    std::string str = "efefeftef";

    std::vector<int> res = prefix_function(str);
    std::vector<int> correct_ans {0, 0, 1, 2, 3, 4, 0, 1, 2};

    REQUIRE(res == correct_ans);

    str.clear();
    res = prefix_function(str);

    REQUIRE(res.size() == 0);
}

TEST_CASE("Knuth–Morris–Pratt Algorithm Test", "[internal KMP Test]" ) {
    std::string patt, temp;

    patt = "ab";
    temp = "ababacdab";

    std::vector<int> res = kmp(patt, temp, false);
    std::vector<int> correct_ans {0, 2, 7};

    REQUIRE(res == correct_ans);

    patt = "";
    temp = "abcdef";
    
    res = kmp(patt, temp, false);
    correct_ans = {-1};

    REQUIRE(res == correct_ans);

    patt = "abc";
    temp = "";
    
    res = kmp(patt, temp, false);
    correct_ans = {-1};

    REQUIRE(res == correct_ans);
}

TEST_CASE("Check Cycle Function Test", "[internal KMP Test]" ) {
    std::string patt, temp;

    patt = "abaa";
    temp = "baaa";

    int res = check_cycle(patt, temp);

    REQUIRE(res == 1);

    patt = "defabc";
    temp = "abcdef";

    res = check_cycle(patt, temp);

    REQUIRE(res == 3);

    patt = "abaaddd";
    temp = "baaa";

    res = check_cycle(patt, temp);

    REQUIRE(res == -1);

    patt = "abaa";
    temp = "b";

    res = check_cycle(patt, temp);

    REQUIRE(res == -1);

    patt = "";
    temp = "abcdef";
    
    res = check_cycle(patt, temp);

    REQUIRE(res == -1);

    patt = "abc";
    temp = "";
    
    res = check_cycle(patt, temp);

    REQUIRE(res == -1);
}
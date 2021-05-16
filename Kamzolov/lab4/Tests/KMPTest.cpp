#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Source/KMP/KMP.h"
#include "sstream"

TEST_CASE("Read Strings", "[Read Test]") {
    std::string s1, s2;

    std::istringstream in("\n");
    readStrings(s1, s2, in);
    REQUIRE(s1.size() == 0);
    REQUIRE(s2.size() == 0);

    std::istringstream in2("abbbc\nasdasdasd");
    readStrings(s1, s2, in2);

    REQUIRE(s1 == "abbbc");
    REQUIRE(s2 == "asdasdasd");

    std::string temp1, temp2;
    for (int i = 0; i < 1000; i++)
    {
        temp1 += (char)(std::rand() % 10 + 20);
        temp2 += (char)(std::rand() % 10 + 20);
    }

    std::istringstream in3(temp1 + "\n" + temp2);
    readStrings(s1, s2, in3);

    REQUIRE(s1.size() == 1000);
    REQUIRE(s2.size() == 1000);
}

TEST_CASE("Prefix function", "[Prefix Test]") {
    std::string s = "efefeftef";
    std::vector<int> test1 = {0, 0, 1, 2, 3, 4, 0, 1, 2};
    REQUIRE(prefixFunc(s) == test1);

    s = "abbaabbab";
    std::vector<int> test2 = {0, 0, 0, 1, 1, 2, 3, 4, 2};
    REQUIRE(prefixFunc(s) == test2);

    
    int count = rand() % 100;
    
    std::vector<int> test3;
    s = "";

    for(int i = 0; i < count; i++) {
        s += 'a';
        test3.push_back(i);
    }

    REQUIRE(test3 == prefixFunc(s));
}

TEST_CASE("Knuth - Morris - Pratt algorithm", "[KMP Test]") {
    std::string s1, s2;

    s1 = "defabcdefabc";
    s2 = "abcdef";

    std::vector<int> test1 = KMP(s2, s1);
    REQUIRE(test1.size() == 1);
    REQUIRE(test1[0] == 3);

    s1 = "ababab";
    s2 = "ab";
    std::vector<int> test2 = KMP(s2, s1);
    REQUIRE(test2.size() == 3);
    REQUIRE(test2[0] == 0);
    REQUIRE(test2[1] == 2);
    REQUIRE(test2[2] == 4);

    s1 = "aaaaaaaa";
    s2 = "a";
    std::vector<int> test3 = KMP(s2, s1);
    REQUIRE(test3.size() == s1.size());
    for(size_t i = 0; i < s1.size(); i++){
        REQUIRE(test3[i] == (int)i);
    }

    s1 = "";
    s2 = "";
    for(int i = 0; i < 10; i++) {
        s1 += rand() % 10; 
    }
    for(int i = 0; i < 9; i++) {
        s2 += s1[i+1];
    }
    s2 += s1[0];
    s1 = s1 + s1;
    std::vector<int> test4 = KMP(s2, s1);
    REQUIRE(test4.size() == 1);
    REQUIRE(test4[0] == 1);
}
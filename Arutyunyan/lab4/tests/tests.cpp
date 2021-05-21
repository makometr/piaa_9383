#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../source/stringwrapper.hpp"
#include "../source/knutmorrispratt.hpp"


TEST_CASE("String concatenating tests") {
    std::string left1 = "lol try to con";
    std::string right1 = "catenate this";
    std::string correct1 = left1 + right1;

    ConcatenatedStringsWrapper wrapper1{left1, right1};

    REQUIRE((correct1 == wrapper1.MakeString()));


    std::string left2 = "lol try to con";
    std::string right2 = "cat";
    std::string another2 = "enate ";
    std::string another3 = "this";

    ConcatenatedStringsWrapper wrapper2{left2, right2, another2, another3};

    REQUIRE((correct1 == wrapper2.MakeString()));
}


TEST_CASE("Knut-Morris-Pratt test") {
    std::string t1 = "abab";
    std::string p1 = "ab";

    std::string t2 = "abclollolfind";
    std::string p2 = "lol";

    std::string t3 = "don't find it!";
    std::string p3 = "okay";

    REQUIRE((KnutMorrisPratt(t1, p1) == std::vector<int>{0, 2}));
    REQUIRE((KnutMorrisPratt(t2, p2) == std::vector<int>{3, 6}));
    REQUIRE((KnutMorrisPratt(t3, p3) == std::vector<int>{-1}));
}


TEST_CASE("Cycle shift test") {
    std::string t1 = "abcdef";
    std::string p1 = "defabc";

    std::string t2 = "ikiehaliben";
    std::string p2 = "ehalibeniki";

    std::string t3 = "no no no no";
    std::string p3 = "okay";

    REQUIRE((CycleShiftDetect(t1, p1) == 3));
    REQUIRE((CycleShiftDetect(t2, p2) == 8));
    REQUIRE((CycleShiftDetect(t3, p3) == -1));
}
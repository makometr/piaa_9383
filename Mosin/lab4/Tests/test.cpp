#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "API.h"

TEST_CASE("Test prefix function") {
    std::vector<int> indices;
    SECTION("default values") {
        indices = {0, 0, 1, 2, 0, 1, 2, 3};
        REQUIRE(prefix_function("ababbaba") == indices);

        indices = {0, 0, 1, 2, 3, 4};
        REQUIRE(prefix_function("ababab") == indices);

        indices = {0};
        REQUIRE(prefix_function("a") == indices);
    }
    SECTION("empty value") {
        indices = {-1};
        REQUIRE(prefix_function("") == indices);
    }
    SECTION("garbage input") {
        indices = {0, 0, 0, 0, 0, 0};
        REQUIRE(prefix_function("\naaa\b\t") == indices);
        REQUIRE(prefix_function("\'\"\\A@*") == indices);
    }
}

TEST_CASE("Test KMP algorithm") {
    std::vector<int> indices;
    SECTION("default values") {
        indices = {0, 2, 7, 10};
        REQUIRE(KMP("ab", "ababaaaabaab") == indices);

        indices = {1};
        REQUIRE(KMP("a", "sas") == indices);

        REQUIRE(KMP("a", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb").empty() == true);
    }
    SECTION("first arg is greater than second") {
        REQUIRE(KMP("ababa","a").empty() == true);
    }
    SECTION("empty values") {
        REQUIRE(KMP("", "a").empty() == true);
        REQUIRE(KMP("a", "").empty() == true);
        REQUIRE(KMP("", "").empty() == true);
    }
    SECTION("garbage input") {
        REQUIRE(KMP("aas#11f1__\n\\\'", "aaaaaaaasaaaaaaabababbbsbs\n\t").empty() == true);

        indices = {1};
        REQUIRE(KMP("as", "\nas") == indices);

        indices = {12};
        REQUIRE(KMP("as", "\n\t____\n\b\t\a\a\nas\n@@@@a@sa\ns") == indices);
    }
}
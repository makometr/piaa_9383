#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "API.h"

extern int* mutation[N+N];
extern int* answer[N+N];
extern int table[N*N];
extern bool rectangle;

TEST_CASE("Restore branch solution function") {
    int M = 3;
    int square[3] = {0,0,0};
    int count = 0;
    SECTION("return false - stop squaring") {
        square[2] = 1;
        fill(square, M, M);
        copy(mutation[count++], square, true);
        REQUIRE(restore(square, M, M, count) == false);
    }
    SECTION("return true - restart squaring with less square at upper left corner") {
        square[2] = 2;
        fill(square, M, M);
        copy(mutation[count++], square, true);
        REQUIRE(restore(square, M, M, count) == true);
    }
}

TEST_CASE("Search new coordinates to insert square") {
    int M = 3;
    int square[3] = {0,0,0};
    SECTION("return false - no there to insert") {
        square[2] = 3;
        fill(square, M, M);
        REQUIRE(update(square, M, M) == false);
        clean(square, M, M);
    }
    SECTION("return true - coordinates was found") {
        square[2] = 2;
        fill(square, M, M);
        REQUIRE(update(square, M, M) == true);
        clean(square, M, M);
    }
}
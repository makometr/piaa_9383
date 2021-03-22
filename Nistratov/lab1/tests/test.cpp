#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include "../source/square.h"

extern int stack[20][3];
extern int answer[20][3];
extern int rectMap[400];
extern bool type; // 0 - Square, 1 - Rectangle
extern int width, height, solve;

TEST_CASE("sd")
{
    width = height = 7;
    int square[3] = {0, 0, 2};

    placeSquare(square);
    REQUIRE(isEmptySquares(square) == true);
    
    square[0] = 0;
    square[1] = 0;
    square[2] = 6;

    placeSquare(square);
    REQUIRE(isEmptySquares(square) == true);

    square[0] = 6;
    square[1] = 0;
    square[2] = 1;

    placeSquare(square);
    REQUIRE(isEmptySquares(square) == true);

    square[0] = 0;
    square[1] = 0;
    square[2] = 7;

    placeSquare(square);
    REQUIRE(isEmptySquares(square) == false);
}
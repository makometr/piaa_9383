#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include "../source/square.h"

TEST_CASE("find square width in matrix")
{
    Square test1;
    test1.squareset(7, 7, false);
    SECTION("width of a square == 1"){
        int square[3] = {0, 0, 6};
        int w = 1;
        test1.placeSquare(square);
        test1.findSquare(6, 6, w);
        REQUIRE(w == 1);
        test1.removeSquare(square);
    }
    SECTION("empty map, widht of a square == 6"){
        int w = 1;
        test1.findSquare(0, 0, w);
        REQUIRE(w == 6);
    }
}

TEST_CASE("add new element to stack")
{
    Square test2;
    test2.squareset(20, 20, false);
    int count = 0;
    int square[3] = {0, 0, 1};
    SECTION("add first element to stack"){
        REQUIRE(test2.push_back(square, count) == true);
    }
    SECTION("add last element to stack"){
    for (int i = 0; i < 19; i++){
        test2.push_back(square, count);
    }        
        REQUIRE(test2.push_back(square, count) == true);
    }
    SECTION("reach limit"){
    for (int i = 0; i < 20; i++){
        test2.push_back(square, count);
    }        
        REQUIRE(test2.push_back(square, count) == false);
    }
}

TEST_CASE("remove last elemnt in stack, until found side > 1")
{
    Square test3;
    test3.squareset(5, 5, false);
    int square[3] = {0, 0, 0};
    int count = 0;
    SECTION("No element in stack"){
        square[2] = 1;
    for (int i = 0; i < 5; i++){
        square[0] = i;
        test3.placeSquare(square); 
        test3.push_back(square, count);
    }
    REQUIRE(test3.pop_back(square, count) == false);
    }
    SECTION("Found element > 1"){
        square[2] = 2;
        test3.placeSquare(square);
        test3.push_back(square, count);
        REQUIRE(test3.pop_back(square, count) == true);
    }
}

TEST_CASE("check if there's empty space for square")
{
    Square test4;
    test4.squareset(7, 7, false);
    int square[3] = {0, 0, 0};

    SECTION("Empty matrix"){
        REQUIRE(test4.isEmptySquares(square) == true);
    }
    SECTION("Empty square on x = 7, y = 7"){
        square[2] = 6;
        test4.placeSquare(square);
        REQUIRE(test4.isEmptySquares(square) == true);
    }
    SECTION("Matrix is filled"){
        square[2] = 7;
        test4.placeSquare(square);
        REQUIRE(test4.isEmptySquares(square) == false);
    }
}
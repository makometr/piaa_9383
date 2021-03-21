#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../source/field.h"
#include "../source/backtracking.hpp"

TEST_CASE("UnputLastSquare tests") {
    Field field(10);

    field.PutSquare({1, 2, 3});
    for (int i = 1; i < 4; ++i) {
        for (int j = 2; j < 5; ++j) {
            REQUIRE(field[j-1][i-1] == 3);
        }
    }
    field.UnputLastSquare();
    for (int i = 1; i < 4; ++i) {
        for (int j = 2; j < 5; ++j) {
            REQUIRE(field[j-1][i-1] == 0);
        }
    }

    field.UnputLastSquare();
    for (int i = 1; i <= field.N(); ++i) {
        for (int j = 1; j <= field.N(); ++j) {
            REQUIRE(field[j-1][i-1] == 0);
        }
    }
}


TEST_CASE("PutSquares borders tests") {
    Field field(5);

    REQUIRE(field.PutSquare({1, 1, 100}) == false);
    REQUIRE(field.PutSquare({5, 5, 2})   == false);

    REQUIRE(field.PutSquare({1, 1, 1})   == true);
    field.UnputLastSquare();
    REQUIRE(field.PutSquare({3, 3, 1})   == true);
    field.UnputLastSquare();
    REQUIRE(field.PutSquare({1, 1, 5})   == true);
    field.UnputLastSquare();
}


TEST_CASE("CheckIntersection tests") {
    Field field(5);
    field.PutSquare({1, 1, 3});

    REQUIRE(field.CheckIntersection({2, 2, 1}) == true);
    REQUIRE(field.CheckIntersection({4, 4, 1}) == false);

    field.PutSquare({1, 3, 2});

    REQUIRE(field.CheckIntersection({1, 3, 2}) == true);
    REQUIRE(field.CheckIntersection({5, 5, 1}) == false);
}

TEST_CASE("Answers tests") {
    Field current_field1(10);
    Field min_field1(10);
    for (int x = 1; x <= 10; ++x) {
        for (int y = 1; y <= 10; ++y) {
            min_field1.PutSquare({x, y, 1});
        }
    }

    Backtracking(1, 1, min_field1, current_field1);
    REQUIRE(min_field1.Area() == 0);
    REQUIRE(min_field1.SquaresAmount() == 4);


    Field current_field2(15);
    Field min_field2(15);
    for (int x = 1; x <= 15; ++x) {
        for (int y = 1; y <= 15; ++y) {
            min_field2.PutSquare({x, y, 1});
        }
    }

    Backtracking(1, 1, min_field2, current_field2);
    REQUIRE(min_field2.Area() == 0);
    REQUIRE(min_field2.SquaresAmount() == 6);


    Field current_field3(19);
    Field min_field3(19);
    for (int x = 1; x <= 19; ++x) {
        for (int y = 1; y <= 19; ++y) {
            min_field3.PutSquare({x, y, 1});
        }
    }

    Backtracking(1, 1, min_field3, current_field3);
    REQUIRE(min_field3.Area() == 0);
    REQUIRE(min_field3.SquaresAmount() == 13);
}
#define CATCH_CONFIG_MAIN

#include "../../catch.hpp"
#include "../source/Field.h"

std::vector<std::vector<int>> answer;

TEST_CASE("Field Constructor Test", "[internal Field Test]" ) {
    Field field1(2);
    Field field2(5);
    Field field3(10);

    answer = {
        {0, 0},
        {0, 0}
    };

    REQUIRE(field1.get_arr() == answer);

    answer = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    REQUIRE(field2.get_arr() == answer);

    answer = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    REQUIRE(field3.get_arr() == answer);
}

TEST_CASE("PlaceSquare() and set_cur_square_size() test", "[internal Field Test]" ) {
    Field field(5);

    field.set_cur_square_size(2);
    field.PlaceSquare(-1, 0);

    answer = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    REQUIRE(field.get_arr() == answer);

    field.PlaceSquare(4, 20);

    REQUIRE(field.get_arr() == answer);

    field.set_cur_square_size(20);
    field.PlaceSquare(0, 0);

    REQUIRE(field.get_arr() == answer);

    field.set_cur_square_size(2);
    field.PlaceSquare(0, 0);

    answer = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    REQUIRE(field.get_arr() == answer);

    field.set_cur_square_size(1);
    field.PlaceSquare(2, 0);

    answer = {
        {1, 1, 2, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    REQUIRE(field.get_arr() == answer);

    field.set_cur_square_size(3);
    field.PlaceSquare(2, 1);

    answer = {
        {1, 1, 2, 0, 0},
        {1, 1, 3, 3, 3},
        {0, 0, 3, 3, 3},
        {0, 0, 3, 3, 3},
        {0, 0, 0, 0, 0}
    };

    REQUIRE(field.get_arr() == answer);
}

TEST_CASE("DeleteSquare() Test", "[internal Field Test]" ) {
    Field field(5);
    field.set_cur_square_size(2);
    field.PlaceSquare(0, 0);

    field.set_cur_square_size(3);
    field.PlaceSquare(2, 0);

    field.set_cur_square_size(2);
    field.PlaceSquare(0, 2);

    field.PlaceSquare(2, 3);

    answer = {
        {1, 1, 2, 2, 2},
        {1, 1, 2, 2, 2},
        {3, 3, 2, 2, 2},
        {3, 3, 4, 4, 0},
        {0, 0, 4, 4, 0}
    };

    REQUIRE(field.get_arr() == answer);


    field.DeleteSquare();

    answer = {
        {1, 1, 2, 2, 2},
        {1, 1, 2, 2, 2},
        {3, 3, 2, 2, 2},
        {3, 3, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    REQUIRE(field.get_arr() == answer);
}


TEST_CASE("Backtrace() Test", "[internal Field Test]" ) {
    Field field(5);
    field.set_cur_square_size(2);
    field.PlaceSquare(0, 0);

    field.set_cur_square_size(2);
    field.PlaceSquare(2, 0);

    field.set_cur_square_size(2);
    field.PlaceSquare(0, 2);

    field.set_cur_square_size(3);
    field.PlaceSquare(2, 2);

    answer = {
        {1, 1, 2, 2, 0},
        {1, 1, 2, 2, 0},
        {3, 3, 4, 4, 4},
        {3, 3, 4, 4, 4},
        {0, 0, 4, 4, 4}
    };

    REQUIRE(field.get_arr() == answer);


    field.Backtrace();

    answer = {
        {1, 1, 2, 2, 0},
        {1, 1, 2, 2, 0},
        {3, 3, 4, 4, 0},
        {3, 3, 4, 4, 0},
        {0, 0, 0, 0, 0}
    };

    REQUIRE(field.get_arr() == answer);

    field.Backtrace();

    answer = {
        {1, 1, 2, 2, 0},
        {1, 1, 2, 2, 0},
        {3, 3, 4, 0, 0},
        {3, 3, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    REQUIRE(field.get_arr() == answer);

    field.set_cur_square_size(2);
    field.PlaceSquare(3, 3);

    answer = {
        {1, 1, 2, 2, 0},
        {1, 1, 2, 2, 0},
        {3, 3, 4, 0, 0},
        {3, 3, 0, 5, 5},
        {0, 0, 0, 5, 5}
    };

    REQUIRE(field.get_arr() == answer);

    field.Backtrace();

    answer = {
        {1, 1, 2, 2, 0},
        {1, 1, 2, 2, 0},
        {3, 3, 4, 0, 0},
        {3, 3, 0, 5, 0},
        {0, 0, 0, 0, 0}
    };

    REQUIRE(field.get_arr() == answer);
}

TEST_CASE("Fill() Test", "[internal Field Test]" ) {
    Field field(5);

    field.Fill(25);

    answer = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 2},
        {0, 0, 1, 1, 3},
        {0, 0, 4, 5, 6}
    };

    REQUIRE(field.get_arr() == answer);

    Field field1(10);

    field1.set_cur_square_size(1);
    field1.Fill(50);

    answer = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 2, 2, 2, 2},
        {0, 0, 0, 0, 0, 3, 2, 2, 2, 2},
        {0, 0, 0, 0, 0, 4, 2, 2, 2, 2},
        {0, 0, 0, 0, 0, 5, 2, 2, 2, 2},
        {0, 0, 0, 0, 0, 6, 7, 8, 9, 10}
    };

    REQUIRE(field1.get_arr() == answer);


    Field field2(10);

    field2.set_cur_square_size(3);
    field2.Fill(4);

    answer = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 2, 2},
        {0, 0, 0, 0, 0, 1, 1, 1, 2, 2},
        {0, 0, 0, 0, 0, 1, 1, 1, 3, 3},
        {0, 0, 0, 0, 0, 4, 4, 0, 3, 3},
        {0, 0, 0, 0, 0, 4, 4, 0, 0, 0}
    };

    REQUIRE(field2.get_arr() == answer);

}

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Source/Table.hpp"





TEST_CASE( "Squares are placed when appropriate", "[placing]" ) {
    Table table = Table(10);
    std::vector<std::vector<int>> testTable = {
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
    table.setCurrentSquare(5);
    table.setTempX(0);
    table.setTempY(0);
    table.newSquare();

    REQUIRE(table.getTable() == testTable);

    table.clearSquare(0, 0, 5);


    testTable = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 1, 1, 0, 2, 2, 0, 0 },
                {0, 0, 0, 1, 1, 0, 2, 2, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

    table.setTempX(3);
    table.setTempY(2);
    table.setCurrentSquare(2);
    table.newSquare();

    table.setTempX(6);
    table.newSquare();

    REQUIRE(table.getTable() == testTable);

    table.clearSquare(3, 2, 2);
    table.clearSquare(6, 2, 2);

    testTable = {{1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 2, 2, 2, 2, 2 },
                {0, 0, 0, 0, 0, 2, 2, 2, 2, 2 },
                {0, 0, 0, 0, 0, 2, 2, 2, 2, 2 },
                {0, 0, 0, 0, 0, 2, 2, 2, 2, 2 },
                {0, 0, 0, 0, 0, 2, 2, 2, 2, 2 }};

    table.setCurrentSquare(5);
    table.setTempX(0);
    table.setTempY(0);
    table.newSquare();

    table.setTempX(5);
    table.setTempY(5);
    table.newSquare();

    REQUIRE(table.getTable() == testTable);

    table.clearSquare(0, 0, 5);
    table.clearSquare(5, 5, 5);
}

TEST_CASE( "Squares are not placed when they are not appropriate", "[not placing]" ) {
    Table table = Table(10);
    std::vector<std::vector<int>> testTable = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
    table.setCurrentSquare(5);
    table.setTempX(6);
    table.setTempY(6);
    table.newSquare();

    REQUIRE(table.getTable() == testTable);


    testTable = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
                {0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

    table.setTempX(3);
    table.setTempY(2);
    table.setCurrentSquare(2);
    table.newSquare();

    table.newSquare();

    REQUIRE(table.getTable() == testTable);

    table.clearSquare(3, 2, 2);

    testTable = {{1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

    table.setCurrentSquare(5);
    table.setTempX(0);
    table.setTempY(0);
    table.newSquare();

    table.setTempX(4);
    table.setTempY(4);
    table.newSquare();

    REQUIRE(table.getTable() == testTable);
    table.clearSquare(0, 0, 5);
}

TEST_CASE( "Squares are cleared when it is possible ", "[clearing]" ) {
    Table table = Table(10);
    std::vector<std::vector<int>> testTable = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

    table.setCurrentSquare(10);
    table.setTempX(0);
    table.setTempY(0);
    table.newSquare();
    table.clearSquare(0, 0, 10);

    REQUIRE(table.getTable() == testTable);



    testTable = {{1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
                {1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

    table.setCurrentSquare(5);
    table.setTempX(0);
    table.setTempY(0);
    table.newSquare();

    table.clearSquare(3, 3, 2);

    REQUIRE(table.getTable() == testTable);

    table.setCurrentSquare(2);
    table.setTempX(3);
    table.setTempY(3);
    table.newSquare();
    table.clearSquare(0, 0, 5);

}

TEST_CASE( "Squares are not cleared when it is not possible ", "[no clearing]" ) {
    Table table = Table(10);
    std::vector<std::vector<int>> testTable = {
                {0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
    table.setCurrentSquare(5);
    table.setTempX(0);
    table.setTempY(0);
    table.newSquare();
    table.clearSquare(-1, 0, 2);
    REQUIRE(table.getTable() != testTable);

    testTable = {{1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
    REQUIRE(table.getTable() == testTable);
    table.clearSquare(0, 0, 5);
}




TEST_CASE( "Start alignment works right ", "[start alignment]" ) {
    Table table3 = Table(3);
    std::vector<std::vector<int>> testTable = {
                {1, 1, 3},
                {1, 1 , 0},
                {2, 0, 0}};
    table3.startAlignment();
    REQUIRE(table3.getTable() == testTable);

    table3.clearSquare(2, 0, 1);
    table3.clearSquare(0, 2, 1);
    table3.clearSquare(0, 0, 2);

    testTable = {{1, 1, 1, 3, 3},
                {1, 1, 1, 3, 3},
                {1, 1, 1, 0, 0},
                {2, 2, 0, 0, 0},
                {2, 2, 0, 0, 0}};
    Table table5 = Table(5);
    table5.startAlignment();
    REQUIRE(table5.getTable() == testTable);
    table5.clearSquare(3, 0, 2);
    table5.clearSquare(0, 3, 2);
    table5.clearSquare(0, 0, 3);

}

TEST_CASE( "Backtracking works right ", "[alignment]" ) {
    Table table3 = Table(3);
    std::vector<std::vector<int>> testTable = {
                {1, 1, 3},
                {1, 1, 0},
                {2, 0, 0}};

    table3.startAlignment();

    table3.setCurrentSquare(1);
    table3.setTempX(1);
    table3.setTempY(2);
    table3.newSquare();

    table3.setTempX(2);
    table3.setTempY(2);
    table3.newSquare();

    table3.backTracking();

    REQUIRE(table3.getTable() == testTable);

    table3.setCurrentSquare(0);
    table3.isFullAlignment();
    table3.backTracking();
    REQUIRE(table3.getTable() == testTable);

    Table table5 = Table(5);
    testTable = {{1, 1, 1, 3, 3},
                {1, 1, 1, 3, 3},
                {1, 1, 1, 0, 0},
                {2, 2, 0, 0, 0},
                {2, 2, 0, 0, 0}};

    table5.startAlignment();
    table5.setCurrentSquare(2);
    table5.setTempX(3);
    table5.setTempY(2);
    table5.newSquare();
    table5.backTracking();

    REQUIRE(table5.getTable() == testTable);
}

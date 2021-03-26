#include "includeCatch.hpp"
#include "../Source/header.hpp"


bool operator==(const Square& square1,const Square& square2)
{
    return square1.size==square2.size && square1.x==square2.x && square1.y==square2.y;
}

TEST_CASE("Test for function createTableNxN","[Creating a Table]")
{
    Table table1 = createTableNxN(5);
    Table table2 = {{0,0,0,0,0},
                    {0,0,0,0,0},
                    {0,0,0,0,0},
                    {0,0,0,0,0},
                    {0,0,0,0,0}};
    REQUIRE(table1==table2);
}

TEST_CASE("Test for function addSquare","[Adding a square]")
{
    Table testTable1_1 = {
        {1,1,1,0,0,0},
        {1,1,1,0,0,0},
        {1,1,1,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    };
    Solution solution1_1;
    solution1_1.push(Square(0,0,3));
    Solution solution1_2;
    Table testTable1_2 = createTableNxN(6);
    addSquare(Square(0,0,3),testTable1_2,solution1_2);
    REQUIRE(solution1_2==solution1_1);//добавление в пустую столешницу
    REQUIRE(testTable1_2==testTable1_1);

    Table testTable2_1 ={
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    Solution solution2_1;
    solution2_1.push(Square(0,0,3));
    solution2_1.push(Square(0,3,2));
    Table testTable2_2 = {
        {1,1,1,0,0},
        {1,1,1,0,0},
        {1,1,1,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    Solution solution2_2;
    solution2_2.push(Square(0,0,3));
    addSquare(Square(0,3,2),testTable2_2,solution2_2);
    REQUIRE(solution2_1==solution2_2);//добавление не в пустую столешницу
    REQUIRE(testTable2_2==testTable2_1);

    Table testTable3_1 ={
        {1,1,1,1,0},
        {1,1,1,1,0},
        {1,1,1,1,0},
        {1,1,1,1,0},
        {0,0,0,0,0}
    };
    Table testTable3_2 = createTableNxN(5);
    Solution solution3_1;
    solution3_1.push(Square(0,0,4));
    Solution solution3_2;
    addSquare(Square(0,0,4),testTable3_2,solution3_2);
    REQUIRE(solution3_1==solution3_2);//добавление квадрата максимального размера
    REQUIRE(testTable3_1==testTable3_1);
}


TEST_CASE("Test for function delSquare","[deleting a square]")
{
    Table testTable1 = {{0,0,0},
                       {0,0,0},
                       {0,0,0},};
    Table testTable2 = createTableNxN(3);
    Solution solution2;
    addSquare(Square(0,0,2),testTable2,solution2);
    delSquare(testTable2,solution2);//удаляем единственный квадрат
    REQUIRE(testTable1==testTable2);
    REQUIRE(solution2.size()==0);

    Table testTable3 = createTableNxN(3);
    Solution solution3;
    addSquare(Square(0,0,2),testTable3,solution3);
    
    Table testTable4 = createTableNxN(3);
    Solution solution4;
    addSquare(Square(0,0,2),testTable4,solution4);
    addSquare(Square(0,2,1),testTable4,solution4);
    delSquare(testTable4,solution4);//удаляем не единственный квадрат
    REQUIRE(testTable4==testTable3);
    REQUIRE(solution4==solution3);

}


TEST_CASE("Test for function checkPlaceForSquare","[Checking the location]")
{
    Table testTable = createTableNxN(7);
    REQUIRE(checkPlaceForSquare(Coordinate(0,1),3,testTable)==true);//граница сверху
    REQUIRE(checkPlaceForSquare(Coordinate(1,5),2,testTable)==true);//граница справа
    REQUIRE(checkPlaceForSquare(Coordinate(5,1),2,testTable)==true);//граница снизу
    REQUIRE(checkPlaceForSquare(Coordinate(1,0),3,testTable)==true);//граница слева
    REQUIRE(checkPlaceForSquare(Coordinate(2,1),6,testTable)==false);//не входит в столешницу снизу
    REQUIRE(checkPlaceForSquare(Coordinate(1,2),6,testTable)==false);//не входит в столешницу справа

    Solution solution;
    addSquare(Square(1,1,3),testTable,solution);
    REQUIRE(checkPlaceForSquare(Coordinate(0,0),3,testTable)==false);//место занято другим квадратом
    REQUIRE(checkPlaceForSquare(Coordinate(4,1),2,testTable)==true);//граничит с квадратом
}


TEST_CASE("Test for function nextCoordinate","[finding coordinate]")
{
    Table table = createTableNxN(7);
    Solution solution = initialFill(table);
    auto coord = nextCoordinate(table);
    REQUIRE(coord.value()==Coordinate(3,4));

    addSquare(Square(3,4,2),table,solution);
    coord = nextCoordinate(table);
    REQUIRE(coord.value()==Coordinate(3,6));

    table = {{1,1,1},{1,1,1},{1,1,1}};
    coord = nextCoordinate(table);
    REQUIRE(coord == std::nullopt);
}


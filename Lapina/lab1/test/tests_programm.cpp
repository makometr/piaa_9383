#define CATCH_CONFIG_MAIN
#include "catch.hpp" 
#include "../source/lb1.hpp"

TEST_CASE("Тест для функции isCan") {
  int n = 8;
  Map map = Map(n);
  for (int i = 0; i < n; i++)
  map[i] = vector<int>(n, 0);

  SECTION("Выход за пределы") {
    REQUIRE(isCan(n, map, Square(5, 4, 15)) == false); 
    REQUIRE(isCan(n, map, Square(-100, 100, 2)) == false); 
    REQUIRE(isCan(n, map, Square(3, 50, 4)) == false); 
    REQUIRE(isCan(n, map, Square(20, 20, 5)) == false); 
    REQUIRE(isCan(n, map, Square(3, -9, 3)) == false);  
    REQUIRE(isCan(n, map, Square(200, 7, 10)) == false); 
    REQUIRE(isCan(n, map, Square(100, -200, 20)) == false); 
  }

  SECTION("Пересечения") {
    Square square(3, 3, 4);
    New_Square(map, square);
    REQUIRE(isCan(n, map, Square(2, 3, 3)) == false); 
    REQUIRE(isCan(n, map, Square(3, 3, 3)) == false); 
  }

  SECTION("Корректная работа") {
    Square square(0, 0, 3);
    New_Square(map, square);
    REQUIRE(isCan(n, map, Square(3, 3, 3)) == true); 
    REQUIRE(isCan(n, map, Square(0, 3, 2)) == true); 
    REQUIRE(isCan(n, map, Square(5, 5, 1)) == true); 
  }

}

TEST_CASE("Тест для функции New_Square") {
  int n = 12;
  Map map = Map(n);
  for (int i = 0; i < n; i++)
    map[i] = vector<int>(n, 0);

  SECTION("Средний случай") {      
    Square square(3, 4, 3);
    New_Square(map, square);
    for (int i = square.x; i < square.x + square.width; i++)
      for (int j = square.y; j < square.y + square.width; j++)
        CHECK(map[i][j] != 0);   
  }

  SECTION("Нижний правый угол") {
    Square square(8, 8, 4);
    New_Square(map, square);
    for (int i = square.x; i < square.x + square.width; ++i)
      for (int j = square.y; j < square.y + square.width; ++j)
        CHECK(map[i][j] != 0);
  }

  SECTION("Нижний левый угол") {
    Square square(7, 0, 5);
    New_Square(map, square);
    for (int i = square.x; i < square.x + square.width; ++i)
      for (int j = square.y; j < square.y + square.width; ++j)
        CHECK(map[i][j] != 0);
  }
  SECTION("Верхний левый угол") {
    Square square(0, 0, 7);
    New_Square(map, square);
    for (int i = square.x; i < square.x + square.width; i++)
      for (int j = square.y; j < square.y + square.width; j++)
        CHECK(map[i][j] != 0);
  }

  SECTION("Верхний правый угол") {
    Square square(0, 7, 5);
    New_Square(map, square);
    for (int i = square.x; i < square.x + square.width; i++)
      for (int j = square.y; j < square.y + square.width; j++)
        CHECK(map[i][j] != 0);
  }
}

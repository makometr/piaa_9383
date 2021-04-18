#define CATCH_CONFIG_MAIN
#include "catch.hpp" 
#include "../source/lb1.hpp"

TEST_CASE("Тест для функции isCan") {
  int n = 8;
  Matrix matrix = Matrix(n);
  for (int i = 0; i < n; i++)
  matrix[i] = std::vector<int>(n, 0);

  SECTION("Выход за пределы") {
    REQUIRE(isCan_Add_Square(n, matrix, Square(5, 4, 15)) == false); 
    REQUIRE(isCan_Add_Square(n, matrix, Square(-100, 100, 2)) == false); 
    REQUIRE(isCan_Add_Square(n, matrix, Square(3, 50, 4)) == false); 
    REQUIRE(isCan_Add_Square(n, matrix, Square(20, 20, 5)) == false); 
    REQUIRE(isCan_Add_Square(n, matrix, Square(3, -9, 3)) == false);  
    REQUIRE(isCan_Add_Square(n, matrix, Square(200, 7, 10)) == false); 
    REQUIRE(isCan_Add_Square(n, matrix, Square(100, -200, 20)) == false); 
  }

  SECTION("Пересечения") {
    Square square(3, 3, 4);
    New_Square(matrix, square);
    REQUIRE(isCan_Add_Square(n, matrix, Square(2, 3, 3)) == false); 
    REQUIRE(isCan_Add_Square(n, matrix, Square(3, 3, 3)) == false); 
  }

  SECTION("Корректная работа") {
    Square square(0, 0, 3);
    New_Square(matrix, square);
    REQUIRE(isCan_Add_Square(n, matrix, Square(3, 3, 3)) == true); 
    REQUIRE(isCan_Add_Square(n, matrix, Square(0, 3, 2)) == true); 
    REQUIRE(isCan_Add_Square(n, matrix, Square(5, 5, 1)) == true); 
  }

}

TEST_CASE("Тест для функции New_Square") {
  int n = 12;
  Matrix matrix = Matrix(n);
  for (int i = 0; i < n; i++)
    matrix[i] = std::vector<int>(n, 0);

  SECTION("Средний случай") {      
    Square square(3, 4, 3);
    New_Square(matrix, square);
    for (int i = square.x; i < square.x + square.width; i++)
      for (int j = square.y; j < square.y + square.width; j++)
        CHECK(matrix[i][j] != 0);   
  }

  SECTION("Нижний правый угол") {
    Square square(8, 8, 4);
    New_Square(matrix, square);
    for (int i = square.x; i < square.x + square.width; ++i)
      for (int j = square.y; j < square.y + square.width; ++j)
        CHECK(matrix[i][j] != 0);
  }

  SECTION("Нижний левый угол") {
    Square square(7, 0, 5);
    New_Square(matrix, square);
    for (int i = square.x; i < square.x + square.width; ++i)
      for (int j = square.y; j < square.y + square.width; ++j)
        CHECK(matrix[i][j] != 0);
  }
  SECTION("Верхний левый угол") {
    Square square(0, 0, 7);
    New_Square(matrix, square);
    for (int i = square.x; i < square.x + square.width; i++)
      for (int j = square.y; j < square.y + square.width; j++)
        CHECK(matrix[i][j] != 0);
  }

  SECTION("Верхний правый угол") {
    Square square(0, 7, 5);
    New_Square(matrix, square);
    for (int i = square.x; i < square.x + square.width; i++)
      for (int j = square.y; j < square.y + square.width; j++)
        CHECK(matrix[i][j] != 0);
  }
}

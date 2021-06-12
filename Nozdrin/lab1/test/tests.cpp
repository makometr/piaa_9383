#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/Squaring.h"

TEST_CASE( "Base case is correct", "[base case]" ) {
  Squaring squaring(10);
  squaring.baseCase1();

  std::vector<std::vector<int>> testSquare = {
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  3},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  4},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  5},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  6},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  7},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  8},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  9},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  10},
      {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
  };
  REQUIRE(squaring.getCurrentSquaring() == testSquare);
}

TEST_CASE( "Backtrack is correct", "[backtrack]" ) {
  Squaring squaring(10);
  squaring.baseCase1();

  squaring.backtrack();
  std::vector<std::vector<int>> testSquare = {
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };
  REQUIRE(squaring.getCurrentSquaring() == testSquare);

  squaring.backtrack();
  testSquare = {
      {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };
  REQUIRE(squaring.getCurrentSquaring() == testSquare);

  squaring.backtrack();
  squaring.backtrack();
  testSquare = {
      {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  REQUIRE(squaring.getCurrentSquaring() == testSquare);
}

TEST_CASE( "Pop is correct", "[pop]" ) {
  Squaring squaring(10);
  squaring.baseCase1();
  squaring.pop();

  std::vector<std::vector<int>> testSquare = {
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  3},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  4},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  5},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  6},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  7},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  8},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  9},
      {1,  1,  1,  1,  1,  1,  1,  1,  1,  10},
      {11, 12, 13, 14, 15, 16, 17, 18, 19, 0},
  };
  REQUIRE(squaring.getCurrentSquaring() == testSquare);

  squaring.pop();
  testSquare = {
      {1,  1,  1,  1,  1,  1,  1,  1,  1, 2},
      {1,  1,  1,  1,  1,  1,  1,  1,  1, 3},
      {1,  1,  1,  1,  1,  1,  1,  1,  1, 4},
      {1,  1,  1,  1,  1,  1,  1,  1,  1, 5},
      {1,  1,  1,  1,  1,  1,  1,  1,  1, 6},
      {1,  1,  1,  1,  1,  1,  1,  1,  1, 7},
      {1,  1,  1,  1,  1,  1,  1,  1,  1, 8},
      {1,  1,  1,  1,  1,  1,  1,  1,  1, 9},
      {1,  1,  1,  1,  1,  1,  1,  1,  1, 10},
      {11, 12, 13, 14, 15, 16, 17, 18, 0, 0},
  };
  REQUIRE(squaring.getCurrentSquaring() == testSquare);
}

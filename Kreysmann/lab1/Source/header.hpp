#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <optional>
#include <chrono>
#include <fstream>

struct Square;
using integer = unsigned int;
using Table = std::vector<std::vector<integer>>;
using Coordinate = std::pair<integer,integer>;
using Solution = std::stack<Square>;
using Pair = std::pair<integer, Coordinate>;
using StackBacktrack = std::stack<Pair>;

struct Square
{
    integer size;
    integer x, y;
    Square(integer y,integer x, integer size);
};

bool checkPlaceForSquare(const Coordinate& coord,integer size,const Table& table);
void addSquare(const Square& square, Table& table, Solution& solution);
void delSquare(Table& table, Solution& solution);
std::optional<Coordinate> nextCoordinate(const Table& table);
Solution evenFillTable(Table& table);
Solution multipleOfThreeFillTable(Table& table);
Solution multipleOfFiveFillTable(Table& table);
Solution initialFill(Table& table);
void backTracking(Table& table, Solution& tempSolution, Solution& bestSolution);
Table createTableNxN(integer N);
bool isBadSolution(const Solution &tempSolution,const Solution &bestSolution, integer minSize);

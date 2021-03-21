#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
#include <optional>
#include <chrono>

struct Square;
using Table = std::vector<std::vector<unsigned short>>;
using Coordinate = std::pair<unsigned short, unsigned short>;
using Solution = std::stack<Square>;
using Pair = std::pair<unsigned short, Coordinate>;
using StackBacktrack = std::stack<Pair>;

struct Square
{
    size_t size;
    int x, y;
};

Square createSquare(const int y, const int x, const size_t size);
bool checkPlaceForSquare(const Coordinate coord, const size_t size, const Table table);
void addSquare(const Square& square, Table& table, Solution& solution);
void dellSquare(Table& table, Solution& solution);
std::optional<Coordinate> nextCoordinate(const Table& table);
Solution evenFillTable(Table& table);
Solution multipleOfThreeFillTable(Table& table);
Solution multipleOfFiveFillTable(Table& table);
Solution initialFill(Table& table);
void Process(Table& table, Solution& tempSolution, Solution& bestSolution);
Table createTableNxN(const unsigned short N);
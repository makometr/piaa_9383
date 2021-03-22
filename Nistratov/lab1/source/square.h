#pragma once

#include <iostream>
#include <vector>

void backtracking(int square[3], int& count, int& min);
void findSquare(const int x, const int y, int& w);
void removeSquare(const int square[3]);
void placeSquare(const int square[3]);
void updateAnswer(const int square_size);
void printAnswer(const int size);
bool pop_back(int square[3], int& count);
void push_back(int* square, int& count);
bool isEmptySquares(int* square);
//FOR TEST ONLY
void setMap(std::vector<std::vector<int>> square, int n, int m);
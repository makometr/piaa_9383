#pragma once
#include <iostream>
#include <algorithm>

class Square
{
public:
    Square();
    ~Square() { };
    void backtracking(int square[3], int& count, int& min);
    void findSquare(const int x, const int y, int& w);
    void removeSquare(const int square[3]);
    void placeSquare(const int square[3]);
    void updateAnswer(const int square_size);
    void printAnswer(const int size);
    bool pop_back(int square[3], int& count);
    bool push_back(int* square, int& count);
    bool isEmptySquares(int* square);
    void squareset(int n, int m, bool t);

    int width, height, solve;
    bool type; // false - Square, true - Rectangle
private:
    int stack[20][3];
    int answer[20][3];
    int rectMap[400];
};
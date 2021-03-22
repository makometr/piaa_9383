#include "backtracking.h"
#include "square.h"


void backtracking(int square[3], int& count, int& min, int& solve, Square sq)
{
    if (count >= min && !sq.pop_back(square, count)) {
        return;
    }
    sq.placeSquare(square);
    sq.push_back(square, count);
    if (!sq.getEmptySquare(square) && count <= min) {
        if (count < min) {
            min = count;
            solve = 1;
        }
        else {
            solve++;
        }
        sq.updateAnswer(min);
    }
    backtracking(square, count, min, solve, sq);
}
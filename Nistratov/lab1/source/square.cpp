#include "square.h"

Square::Square()
{
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 3; j++) {
            stack[i][j] = 0;
            answer[i][j] = 0;
        }
    }
    for (int i = 0; i < 400; i++) {
        rectMap[i] = 0;
    }
    width = 0;
    height = 0;
    type = false;
    solve = 0;
}

void Square::backtracking(int square[3], int& count, int& min)
{
    if (count >= min && !pop_back(square, count)) {
        return;
    }
    placeSquare(square);
    push_back(square, count);
    if (!isEmptySquares(square) && count <= min) {
        if (count < min) {
            min = count;
            solve = 1;
        }
        else {
            solve++;
        }
        updateAnswer(min);
    }
    backtracking(square, count, min);
}

void Square::findSquare(const int x, const int y, int& w)
{
    if (w <= std::min(width, height) - 1) {
        if (x + w > width || y + w > height) {
            w--;
            return;
        }
        if (type) {
            for (int* i = &rectMap[x + y * width]; i != &rectMap[x + y * width + w]; ++i) {
                for (int j = 0; j < w; ++j) {
                    if (*(i + j * width)) {
                        w--;
                        return;
                    }
                }
            }
        }
        else if (rectMap[x + y * width + w - 1] || rectMap[x + y * width + (w - 1) * width] || rectMap[x + y * width + w - 1 + (w - 1) * width]) {
            w--;
            return;
        }
        w++;
        findSquare(x, y, w);
        return;
    }
    else {
        w--;
        return;
    }
}

void Square::removeSquare(const int square[3])
{
    for (int* i = &rectMap[square[0] + square[1] * width]; i != &rectMap[square[0] + square[1] * width + square[2]]; ++i) {
        for (int j = 0; j < square[2]; ++j) {
            *(i + j * width) = 0;
        }
    }
}

void Square::placeSquare(const int square[3])
{
    for (int* i = &rectMap[square[0] + square[1] * width]; i != &rectMap[square[0] + square[1] * width + square[2]]; ++i) {
        for (int j = 0; j < square[2]; ++j) {
            *(i + j * width) = square[2];
        }
    }
}

void Square::updateAnswer(const int square_size)
{
    for (size_t i = 0; i < square_size; ++i) {
        answer[i][0] = stack[i][0];
        answer[i][1] = stack[i][1];
        answer[i][2] = stack[i][2];
    }
}

void Square::printAnswer(const int size)
{
    for (int i = 0; i < size; ++i) {
        std::cout << answer[i][0] + 1 << " " << answer[i][1] + 1 << " " << answer[i][2] << std::endl;
    }
}

bool Square::pop_back(int square[3], int& count)
{
    while (count) {
        count--;
        square[0] = stack[count][0];
        square[1] = stack[count][1];
        square[2] = stack[count][2];
        removeSquare(square);
        if (!count && square[2] < 2) {
            return false;
        }
        if (square[2] > 1) {
            square[2]--;
            return true;
        }
    }
    return false;
}

bool Square::push_back(int* square, int& count)
{
    if (count < 20) {
        stack[count][0] = square[0];
        stack[count][1] = square[1];
        stack[count][2] = square[2];
        count++;
        return true;
    }
    else {
        return false;
    }
}

bool Square::isEmptySquares(int* square)
{
    int index = square[0] + square[1] * width;
    while (index < height * width) {
        if (!rectMap[index]) {
            square[0] = index % width;
            square[1] = index / width;
            square[2] = 1;
            findSquare(square[0], square[1], square[2]);
            return true;
        }
        index += rectMap[index];
    }
    return false;
}

void Square::squareset(int n, int m, bool t)
{
	width = n;
	height = m;
    type = t;
}

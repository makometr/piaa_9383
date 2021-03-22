#include "square.h"

int stack[20][3];
int answer[20][3];
int rectMap[400];
bool type; // 0 - Square, 1 - Rectangle
int width, height, solve;

// Recursive backtracking 
void backtracking(int square[3], int& count, int& min)
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

// Find max sided square to fit map
void findSquare(const int x, const int y, int& w)
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
    }
    else{
        w--;
        return;
    }
}

// Remove square from map 
void removeSquare(const int square[3])
{
    for (int* i = &rectMap[square[0] + square[1] * width]; i != &rectMap[square[0] + square[1] * width + square[2]]; ++i) {
        for (int j = 0; j < square[2]; ++j) {
            *(i + j * width) = 0;
        }
    }    
}

// Place square on map
void placeSquare(const int square[3])
{
    for (int* i = &rectMap[square[0] + square[1] * width]; i != &rectMap[square[0] + square[1] * width + square[2]]; ++i) {
        for (int j = 0; j < square[2]; ++j) {
            *(i + j * width) = square[2];
        }
    }
}

// Write answer for new best solution
void updateAnswer(const int square_size)
{
    for (size_t i = 0; i < square_size; ++i) {
        answer[i][0] = stack[i][0];
        answer[i][1] = stack[i][1];
        answer[i][2] = stack[i][2];
    }    
}

// Print best solution
void printAnswer(const int size)
{
    for (int i = 0; i < size; ++i) {
        std::cout << answer[i][0] + 1 << " " << answer[i][1] + 1 << " " << answer[i][2] << std::endl;
    }    
}

// Remove last element from stack
bool pop_back(int square[3], int& count)
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

// Add new element to stack
void push_back(int* square, int& count)
{
    stack[count][0] = square[0];
    stack[count][1] = square[1];
    stack[count][2] = square[2];
    count++;    
}

// Jump on map by square sides to find empty spot
bool isEmptySquares(int* square)
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

// set map #FOR TEST ONLY!
void setMap(std::vector<std::vector<int>> square, int n, int m)
{
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            rectMap[j + i * width] = square[i][j];
        }
    }
}
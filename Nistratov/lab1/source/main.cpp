#include <iostream>
#include "square.h"


extern int stack[20][3];
extern int answer[20][3];
extern int rectMap[400];
extern bool type; // 0 - Square, 1 - Rectangle
extern int width, height, solve;

void input();

int main()
{
    input();
    int square[3] = { 0, 0, std::min(width, height) - 1 };
    int min = width * height;
    int count = 0;

    if (!type)
        min = 17;

    backtracking(square, count, min);
    std::cout << min << std::endl;
    printAnswer(min);
    std::cout << "Number of solutions: " << solve << std::endl;
    return 0;
}

void input()
{
    std::cout << "Input sides of Rectangle (1 < N,M < 21)" << std::endl;
    std::cin >> width >> height;
    if (width < 2 || width > 20 || height < 2 || height > 20){
        std::cout << "Out of sides border (1 < N,M < 21)" << std::endl;
        std::exit(1);
    }
    if (width < height) {
        std::swap(width, height);
    }

    if (width == height) {
        type = false;
    }
    else {
        type = true;
    }
}
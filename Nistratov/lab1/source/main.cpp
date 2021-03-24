#include <iostream>
#include "square.h"

int main()
{
    Square sq;
    int width, height;
    bool type;
    std::cout << "Input sides of Rectangle (1 < N,M < 21)" << std::endl;
    std::cin >> width >> height;
    if (width < 2 || width > 20 || height < 2 || height > 20) {
        std::cout << "Out of sides border (1 < N,M < 21)" << std::endl;
        return -1;
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
    sq.squareset(width, height, type);
    int square[3] = { 0, 0, std::min(sq.width, sq.height) - 1 };
    int min = sq.width * sq.height;
    int count = 0;
    if (!sq.type)
        min = 17;

    sq.backtracking(square, count, min);
    std::cout << min << std::endl;
    sq.printAnswer(min);
    std::cout << "Number of solutions: " << sq.solve << std::endl;
    return 0;
}

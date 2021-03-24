#include <iostream>
#include "field.h"


void Backtracking(int x, int y, Field& currentField, Field& minField) {
    int n = currentField.GetN();
    while (x <= n && y <= n && currentField[y - 1][x - 1]) {
        x++;
        if (x == n + 1) {
            x = 1;
            y++;
        }
    }
    if (y == n + 1)
        return;

    Square square(x, y, n - 1);
    for (int size = n - 1; size >= 1; size--) {
        square = { x, y, size };
        if (x + size > n + 1 || y + size > n + 1 || currentField.CheckIntersection(square))
            continue;

        currentField.AddSquare(square);

        if (currentField.GetArea() == 0 && currentField.SquaresAmount() < minField.SquaresAmount()) {
            minField = currentField;
        }
        else if (currentField.SquaresAmount() >= minField.SquaresAmount()) {
            currentField.RemoveLastSquare();
            break;
        }
        else {
            Backtracking(x + 1, y, currentField, minField);
        }

        currentField.RemoveLastSquare();
    }
}


int main() {
    int n;
    std::cin >> n;

    Field minField(n);
    Field currentField(n);

    Square square(1, 1, 1);
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= n; ++y) {
            square = { x, y, 1 };
            minField.AddSquare(square);
        }
    }

    std::cout << "Enter the necessary squares:" << std::endl;
    for (int i = 0; i < n * n; ++i) {
        int x;
        std::cin >> x;
        if (x == -1)
            break;
        int y, width;
        std::cin >> y >> width;

        square = { x, y, width };
        currentField.AddSquare(square);
    }

    Backtracking(1, 1, currentField, minField);

    std::cout << minField.SquaresAmount() << std::endl;
    minField.PrintSquares();
    std::cout << '\n';
    minField.PrintField();

    return 0;
}

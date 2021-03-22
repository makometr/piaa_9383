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

    if (n % 2 == 0) {
        Square square(1, 1, n / 2);
        minField.AddSquare(square);
        square = { n / 2 + 1, 1, n / 2 };
        minField.AddSquare(square);
        square = { 1, n / 2 + 1, n / 2 };
        minField.AddSquare(square);
        square = { n / 2 + 1, n / 2 + 1, n / 2 };
        minField.AddSquare(square);
    }
    else if (n % 3 == 0) {
        Square square(1, 1, 2 * n / 3);
        minField.AddSquare(square);
        square = { 1 + 2 * n / 3, 1, n / 3 };
        minField.AddSquare(square);
        square = { 1, 2 * n / 3 + 1, n / 3 };
        minField.AddSquare(square);
        square = { 2 * n / 3 + 1, n / 3 + 1, n / 3 };
        minField.AddSquare(square);
        square = { n / 3 + 1, 2 * n / 3 + 1, n / 3 };
        minField.AddSquare(square);
        square = { 2 * n / 3 + 1, 2 * n / 3 + 1, n / 3 };
        minField.AddSquare(square);
    }
    else if (n % 5 == 0) {
        Square square(1, 1, 3 * n / 5);
        minField.AddSquare(square);
        square = { 3 * n / 5 + 1, 1, 2 * n / 5 };
        minField.AddSquare(square);
        square = { 1, 3 * n / 5 + 1, 2 * n / 5 };
        minField.AddSquare(square);
        square = { 3 * n / 5 + 1, 3 * n / 5 + 1, 2 * n / 5 };
        minField.AddSquare(square);
        square = { 2 * n / 5 + 1, 3 * n / 5 + 1, n / 5 };
        minField.AddSquare(square);
        square = { 2 * n / 5 + 1, 4 * n / 5 + 1, n / 5 };
        minField.AddSquare(square);
        square = { 3 * n / 5 + 1, 2 * n / 5 + 1, n / 5 };
        minField.AddSquare(square);
        square = { 4 * n / 5 + 1, 2 * n / 5 + 1, n / 5 };
        minField.AddSquare(square);
    }
    else {
        Square square(1, 1, (n + 1) / 2);
        currentField.AddSquare(square);
        square = { (n + 3) / 2, 1, n / 2 };
        currentField.AddSquare(square);
        square = { 1, (n + 3) / 2, n / 2 };
        currentField.AddSquare(square);

        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= n; ++y) {
                square = { x, y, 1 };
                minField.AddSquare(square);
            }
        }

        Backtracking(1, 1, currentField, minField);
    }

    std::cout << minField.SquaresAmount() << std::endl;
    minField.PrintSquares();

    return 0;
}

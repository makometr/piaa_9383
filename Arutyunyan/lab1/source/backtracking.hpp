#pragma once

#include "field.h"

inline void Backtracking(int x, int y, Field& min_field, Field& current_field) {
    auto N = current_field.N();

    while (x <= N && y <= N && current_field[y-1][x-1]) {
        ++x;
        if (x == N + 1) {
            x = 1;
            ++y;
        }
    }

    if (y == N + 1)
        return;

    for (int width = N - 1; width >= 1; --width) {
        if (x + width > N + 1 || y + width > N + 1 || current_field.CheckIntersection({x, y, width}))
            continue;

        current_field.PutSquare({x, y, width});

        if (current_field.Area() == 0 && current_field.SquaresAmount() < min_field.SquaresAmount()) {
            min_field = current_field;
        }
        else if (current_field.SquaresAmount() >= min_field.SquaresAmount()) {
            current_field.UnputLastSquare();
            break;
        }
        else {
            Backtracking(x + 1, y, min_field, current_field);
        }

        current_field.UnputLastSquare();
    }
}
#include <iostream>
#include "field.h"
#include "backtracking.hpp"


int main() {
    int N; std::cin >> N;

    Field min_field(N);
    Field current_field(N);

    if (N % 2 == 0) {
        min_field.PutSquare({1, 1, N / 2});
        min_field.PutSquare({N/2 + 1, 1, N / 2});
        min_field.PutSquare({1, N/2 + 1, N / 2});
        min_field.PutSquare({N/2 + 1, N/2 + 1, N / 2});
    }
    else if (N % 3 == 0) {
        min_field.PutSquare({1, 1, 2*N/3});
        min_field.PutSquare({1 + 2*N/3, 1, N/3});
        min_field.PutSquare({1, 2*N/3 + 1, N/3});
        min_field.PutSquare({2*N/3 + 1, N/3 + 1, N/3});
        min_field.PutSquare({N/3 + 1, 2*N/3 + 1, N/3});
        min_field.PutSquare({2*N/3 + 1, 2*N/3 + 1, N/3});
    }
    else if (N % 5 == 0) {
        min_field.PutSquare({1, 1, 3*N/5});
        min_field.PutSquare({3*N/5 + 1, 1, 2*N/5});
        min_field.PutSquare({1, 3*N/5 + 1, 2*N/5});
        min_field.PutSquare({3*N/5 + 1, 3*N/5 + 1, 2*N/5});
        min_field.PutSquare({2*N/5 + 1, 3*N/5 + 1, N/5});
        min_field.PutSquare({2*N/5 + 1, 4*N/5 + 1, N/5});
        min_field.PutSquare({3*N/5 + 1, 2*N/5 + 1, N/5});
        min_field.PutSquare({4*N/5 + 1, 2*N/5 + 1, N/5});
    }
    else {
        current_field.PutSquare({1, 1, (N+1)/2});
        current_field.PutSquare({(N+3)/2, 1, N/2});
        current_field.PutSquare({1, (N+3)/2, N/2});


        for (int x = 1; x <= N; ++x) {
            for (int y = 1; y <= N; ++y) {
                min_field.PutSquare({x, y, 1});
            }
        }

        Backtracking(1, 1, min_field, current_field);
    }

    std::cout << min_field.SquaresAmount() << std::endl;
    min_field.PrintSquares();

    return 0;
}

#include <iostream>

#include <vector>
#include <stack>
#include <chrono>
#include <cmath>

#include "Field.h"
#include "Square.h"


int main() {

    int n;
    std::cout << "Enter n: ";
    std::cin >> n;


    if(n % 2 == 0) {
        std::cout << 4 << "\n";

        std::cout << 1 << " " << 1 << " " << n / 2 << "\n";
        std::cout << 1 + n / 2 << " " << 1 << " " << n / 2 << "\n";
        std::cout << 1 << " " << 1 + n / 2 << " " << n / 2 << "\n";
        std::cout << 1 + n / 2 << " " << 1 + n / 2 << " " << n / 2 << "\n";
        return 0;
    }
    else if(n % 3 == 0) {
        std::cout << 6 << "\n";

        std::cout << 1 << " " << 1 << " " << 2 * n / 3 << "\n";

        std::cout << 1 + 2 * n / 3 << " " << 1 << " " << n / 3 << "\n";
        std::cout << 1 << " " << 1 + 2 * n / 3 << " " << n / 3 << "\n";
        std::cout << 1 + 2 * n / 3 << " " << 1 + n / 3 << " " << n / 3 << "\n";
        std::cout << 1 + n / 3 << " " << 1 + 2 * n / 3 << " " << n / 3 << "\n";
        std::cout << 1 + 2 * n / 3 << " " << 1 + 2 * n / 3 << " " << n / 3 << "\n";
        return 0;
    }
    else if(n % 5 == 0) {
        std::cout << 8 << "\n";
        std::cout << 1 << " " << 1 << " " << 3 * n / 5 << "\n";
        std::cout << 1 + 3 * n / 5 << " " << 1 << " " << 2 * n / 5 << "\n";
        std::cout << 1 << " " << 1 + 3 * n / 5 << " " << 2 * n / 5 << "\n";
        std::cout << 1 + 3 * n / 5 << " " << 1 + 3 * n / 5 << " " << 2 * n / 5 << "\n";
        std::cout << 1 + 2 * n / 5 << " " << 1 + 3 * n / 5 << " " << n / 5 << "\n";
        std::cout << 1 + 2 * n / 5 << " " << 1 + 4 * n / 5 << " " << n / 5 << "\n";
        std::cout << 1 + 3 * n / 5 << " " << 1 + 2 * n / 5 << " " << n / 5 << "\n";
        std::cout << 1 + 4 * n / 5 << " " << 1 + 2 * n / 5 << " " << n / 5 << "\n";
        return 0;
    }

    Field field(n);
    Field min_field(n);

    field.set_cur_square_size(std::ceil(double(n) / 2));
    field.PlaceSquare(0, 0);

    field.set_cur_square_size(n / 2);
    field.PlaceSquare(std::ceil(double(n) / 2), 0);

    field.PlaceSquare(0, std::ceil(double(n) / 2));

    auto start = std::chrono::steady_clock::now();


    int min_amount = n * n;

    long long int operations_amount = 0;

    while(field.get_running()) {
        bool filled_succesfully = field.Fill(min_amount);

        operations_amount += field.get_operations_amount();

        if (filled_succesfully && field.get_squares_amount() < min_amount) {
            min_field = field;
            min_amount = field.get_squares_amount();
        }

        field.Backtrace();

    }

    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Elapsed Time: " << elapsed_seconds.count() << "s\n";
    std::cout << "Operaions: " << operations_amount << "\n";
    min_field.Print();
    min_field.PrintStack();
    return 0;
}

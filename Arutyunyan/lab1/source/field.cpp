#include "field.h"

Field::Field(std::size_t n) 
   : n(n), current_area(n * n)
{
    field.resize(n, std::vector<int>(n, false));
    putted_squares.reserve(n*n);
}

const std::vector<int>& Field::operator[](int index) const {
    return field[index];
}

bool Field::PutSquare(const Square& square) {
    if (square.x + square.width > n + 1 || square.y + square.width > n + 1)
        return false;

    for (int i = square.x; i < square.x + square.width; ++i) {
        for (int j = square.y; j < square.y + square.width; ++j) {
            field[j-1][i-1] = square.width;
        }
    }

    putted_squares.push_back(square);
    current_area -= square.width * square.width;
    return true;
}

void Field::UnputLastSquare() {
    if (putted_squares.empty())
        return;

    auto square = putted_squares.back();

    for (int i = square.x; i < square.x + square.width; ++i) {
        for (int j = square.y; j < square.y + square.width; ++j) {
            field[j-1][i-1] = 0;
        }
    }

    current_area += square.width * square.width;
    putted_squares.pop_back();
}

bool Field::CheckIntersection(const Square& square) {
    for (int i = square.x; i < square.x + square.width; ++i) {
        for (int j = square.y; j < square.y + square.width; ++j) {
            if (field[j-1][i-1])
                return true;
        }
    }

    return false;
}

std::size_t Field::SquaresAmount() const {
    return putted_squares.size();
}

std::size_t Field::N() const {
	return n;
}

int Field::Area() const {
    return current_area;
}

void Field::PrintSquares() const {
    for (const auto& square : putted_squares) {
        std::cout << square.x << " " << square.y << " " << square.width << std::endl;
    }
}
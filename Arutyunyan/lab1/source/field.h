#pragma once

#include <vector>
#include <iostream>


struct Square {
    int x, y;
    int width;
};


class Field {
public:
    explicit Field(std::size_t n);
    Field(const Field& other_field) = default;

    bool PutSquare(const Square& square);
    void UnputLastSquare();
    bool CheckIntersection(const Square& square);

    const std::vector<int>& operator[](int index) const;

    std::size_t SquaresAmount() const;
    std::size_t N() const;
    int Area() const;
    void PrintSquares() const;

private:
    int current_area;
    std::size_t n;
    std::vector<std::vector<int>> field;
    std::vector<Square> putted_squares;
};

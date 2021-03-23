#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <stack>
#include <iostream>

#include "Square.h"

class Field {

public:

    Field(int size);

    void Print();

    void PrintStack();

    void PlaceSquare(int x, int y);
    void DeleteSquare();

    bool Fill(int min_amount);

    void Backtrace();

    bool get_running() { return running_; }

    const std::vector<std::vector<int>> get_matrix() { return matrix_; }

    int get_squares_amount() { return squares_amount_; }

    long long int get_operations_amount() { return operations_amount_; }

    void set_cur_square_size(int value) { if(value > 0) cur_square_size_ = value; }

private:
    int size_;
    int default_square_size_;
    std::vector<std::vector<int>> matrix_;
    std::stack<Square> square_stack_;

    int squares_amount_ = 0;
    int cur_square_size_ = 0;
    long long int operations_amount_ = 0;

    bool running_ = true;

    void Init();

    bool CheckEnoughPlace(int start_x, int start_y);

};

#endif

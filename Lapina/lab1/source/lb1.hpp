#include <bits/stdc++.h>

struct Square {   //структура для хранения квадратов
    Square(int x, int y, int width){
        this->x = x;    //координата по х
        this->y = y;    //координата по у
        this->width = width;    //ширина квадрата
    }
    int x = 0;
    int y = 0;
    int width = 0;
};

using List_of_squares = std::vector<Square>;
using Matrix = std::vector<std::vector<int>>;
using Point = std::pair<int, int>;

struct For_backtracking {
    For_backtracking(Matrix matrix, int count, List_of_squares list_of_square){
        this->matrix = matrix;
        this->count = count;
        this->list_of_square = list_of_square;
    }
    Matrix matrix;
    int count;
    List_of_squares list_of_square;
};

void New_Square(Matrix& matrix, Square square);
void Print_Answer(const int result, List_of_squares result_squares);
bool isCan_Add_Square(int n, Matrix matrix, Square square);
void Backtracking(int n, Matrix matrix, int count_ready_squares, int& result, List_of_squares& result_squares);

void Divisible_2(int n, int&result, List_of_squares& result_squares); //для чисел, кратных 2
void Divisible_3(int n, int&result, List_of_squares& result_squares); //для чисел, кратных 3

void Simple_Number(int n, Matrix& matrix, int&result, List_of_squares& resultSquares); //для простых чисел

void Time_Information(clock_t start_time, clock_t end_time); //для вычисления времени
 

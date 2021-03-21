#include <bits/stdc++.h>

using namespace std;

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

using List_of_squares = vector<Square>;
using Map = vector<vector<int>>;
using Point = pair<int, int>;

struct For_backtracking {
    For_backtracking(Map map, int count, List_of_squares list_of_square){
        this->map = map;
        this->count = count;
        this->list_of_square = list_of_square;
    }
    Map map;
    int count;
    List_of_squares list_of_square;
};

void New_Square(Map& map, Square square);
void Print(int& result, List_of_squares& result_squares);
bool isCan(int n, Map map, Square square);
void Backtracking(int n, Map map, int count_ready_squares, int& result, List_of_squares& result_squares);

void Divisible_2(int n, int&result, List_of_squares& result_squares); //для чисел, кратных 2
void Divisible_3(int n, int&result, List_of_squares& result_squares); //для чисел, кратных 3

void Simple_Number(int n, Map& map, int&result, List_of_squares& resultSquares); //для простых чисел

void Time_Information(clock_t start_time, clock_t end_time); //для вычисления времени
 

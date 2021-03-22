#include <iostream>
#include <vector>
using namespace std;

int countOperation = 0;  //переменная для подсчета количества операций

struct Square //квадрат
{
    int x, y, size;
};

struct TableTop  //столешница
{
    int N;
    TableTop(int N) : N(N), filled(N, 0) {}
    std::vector<int> filled;   //степень заполненности каждого столбца построчно
    std::vector<Square> current, minSquares;  //то, с чем работаем сейчас; минимальный 
    int minAmount = 0;  //минимальное количество квадратов

    int getTopColNumber()  //получение координаты левого верхнего столбца
    {
        int minRow = N;
        int minCol = -1;
        for (int i = 0; i < N; i++) 
        {
            if (filled[i] < minRow) 
            {
                minCol = i;
                minRow = filled[i];
            }
        }
        return minCol;
    }
    
    int spaceBelow(int col)   //сколько места есть ниже
    {
        return N - filled[col];
    }
    
    int spaceRight(int col)   //сколько места есть справа
    {
        int endCol = col + 1;
        int row = filled[col];
        for ( ; endCol < N; endCol++) 
        {
            if (filled[endCol] > row)
                break;
        }
        return endCol - col;
    }
    
    void insertSquare(int topLeftCol, int size)   //вставка квадрата
    {
        countOperation++;
        current.push_back({topLeftCol, filled[topLeftCol], size});
        for (int i = 0; i < size; i++) 
        {
            filled[topLeftCol + i] += size;
        }
    }
    
    void deleteSquare(int topLeftCol, int size)  //удаление квадрата
    {
        for (int i = 0; i < size; i++) 
        {
            filled[topLeftCol + i] -= size;
        }
        current.pop_back();
    }
    
    void saveMinSquares()   //сохранение полученных минимальных значений
    {
        if (current.size() < minAmount) 
        {
            minAmount = current.size();
            minSquares = current;
        }
    }
};

void printSquaresData(const std::vector<Square> &current)  //печать данных по квадратам на экран
{
    cout << "Min number of squares: " << current.size() << '\n';
    for (auto square : current) 
    {
        cout << "x coord: " << square.x << "; y coord: " << square.y << "; size: " << square.size << '\n';
    }
}

void backtracking(TableTop &table);

decltype(TableTop::current) analysisN(int N)  //в зависимости от входных данных выбираем ход действий
{
    TableTop table(N);
    table.minAmount = (N + 3) + 1; // +1 to record squares
    if (N % 2 != 0 && N % 3 != 0 && N % 5 != 0) 
    {
        int size = N/2 + 1;
        table.insertSquare(0, size);
        table.insertSquare(size, size - 1);
        table.insertSquare(0, size - 1);
        backtracking(table);
    }
    else 
    {
        if (N % 2 == 0) table.minAmount = 4 + 1; // +1 to record squares
        else if (N % 3 == 0) table.minAmount = 6 + 1; // +1 to record squares
        else if (N % 5 == 0) table.minAmount = 8 + 1; // +1 to record squares
        backtracking(table);
    }
    return table.minSquares;
}

void backtracking(TableTop &table)   //основаная фукция осуществляющая рекурсивную вставку
{
    int toppestCol = table.getTopColNumber();
    if (toppestCol == -1) 
    {
        table.saveMinSquares();
        return;
    }

    if (table.current.size() >= table.minAmount - 1)
    {
        return;
    }

    int maxSize = std::min(table.spaceBelow(toppestCol), table.spaceRight(toppestCol));
    maxSize = std::min(maxSize, table.N - 1);

    for (int size = maxSize; size >= 1; size--) 
    {
        table.insertSquare(toppestCol, size);
        backtracking(table);
        table.deleteSquare(toppestCol, size);
    }
}

int main() 
{
    int N;
    cout << "Size of table top: ";
    cin >> N;
    auto current = analysisN(N);
    printSquaresData(current);
    cout << "Number of operations: " << countOperation << '\n';
    return 0;
}
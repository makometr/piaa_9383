
#include <bitset>
#include <iostream>
#include <list>
#include <vector>
#include <stack>


struct Square {
    int x = 0;
    int y = 0;
    int side = 0;
    Square(int x, int y, int side): x(x), y(y), side(side) {}
};

class Table {
    std::vector <std::vector<int>> table;
    std::vector <std::vector<int>> bestTable;

    int tempY = 0;
    int tempX = 0;
    int width;
    int squaresCounter = 0;
    int minSquares = 0;

    int currentSquare;

    std::stack<Square> squares;

    bool allowToClear(int x, int y, int side);

public:
    const std::vector <std::vector<int>> getTable() { return table; }
    int getsquaresCounter() { return squaresCounter; }
    void setTempX(int tempX) { this->tempX = tempX; }
    void setTempY(int tempY) { this->tempY = tempY; }
    void setCurrentSquare(int tempSquare) { currentSquare = tempSquare; }
    void calculations();
    void printAnswer(int pow = 1);
    void startAlignment();
    void print();
    bool isFullAlignment();
    bool newSquare();
    void clearSquare(int x, int y, int side);
    bool backTracking();

    std::stack<Square> bestCase;
    void running();
    Table(int width);
};

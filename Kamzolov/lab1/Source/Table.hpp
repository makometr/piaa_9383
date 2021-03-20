
#include <bitset>
#include <iostream>
#include <list>
#include <vector>
#include <stack>

using namespace std;

struct Square {
    int x = 0;
    int y = 0;
    int side = 0;
    Square(int x, int y, int side): x(x), y(y), side(side) {}
};

class Table {
    vector <vector<int>> table;
    vector <vector<int>> bestTable;

    int tempY;
    int tempX;
    int width;
    int squaresCounter;
    int minSquares;

    int currentSquare;

    stack<Square> squares;

public:
    const vector <vector<int>> getTable() { return table; }
    int getsquaresCounter() { return squaresCounter; }
    void setTempX(int tempX) { this->tempX = tempX; }
    void setTempY(int tempY) { this->tempY = tempY; }
    void setCurrentSquare(int tempSquare) { currentSquare = tempSquare; }
    void calculations();
    void printAnswer(int pow = 1);
    void startAlignment();
    void print();
    bool alignment();
    bool newSquare();
    void clearSquare(int x, int y, int side);
    bool backTracking();

    stack<Square> bestCase;
    void running();
    Table(int width);
};

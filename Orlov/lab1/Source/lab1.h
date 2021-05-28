#include <iostream>
#include <vector>
#include <cmath>

struct Square
{
    int sizeSquare;
    int x;
    int y;
};


struct Field
{
public:

    int Width, Height;
    int counter = 0;

    std::vector <std::vector <bool>> table;
    std::vector <Square> Squares;
    std::vector <Square> bestSquares;

    Field(int w, int h);

    void printField();

    bool isFree(int x, int y);
    bool isFull();

    bool checkOptimality();
    bool checkMinimality();

    void setFree(int x, int y);
    void setBusy(int x, int y);

    void buildSquare(int x, int y, int sizeS);
    void destroyLastSquare();

    int findMaxSizeOfSquare(int x, int y, int maxSize);

    Square findNextFreeCell();


    void backtracking();

};


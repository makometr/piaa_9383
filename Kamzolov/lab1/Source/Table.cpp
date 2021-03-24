#include "Table.hpp"


Table::Table(int width) {
    this->width = width;
    table.resize(width);
    for (int i = 0; i < width; i++) {
        table[i].resize(width);
        for(int j = 0; j < width; j++) {
            table[i][j] = 0;
        }
    }
}

void Table::calculations() {
    startAlignment();
    int min = width * width;
    minSquares = min;
    do {
        if(isFullAlignment()) {
            if(squaresCounter < min) {
                bestCase = squares;
                bestTable = table;
                min = squaresCounter;
                minSquares = min;
            }
        }
        if(!backTracking())
            break;
    }while(true);
}

void Table::running() {
    if (width % 2 == 0) {
        std::cout << "Count of squares: " <<  4 << std::endl;
        std::cout << "x: " << 1 << " y: " << 1 << " side: " << width / 2 << '\n';
        std::cout << "x: " << width / 2 + 1
                  << " y: " << 1
                  << " side: " << width / 2
                  << '\n';
        std::cout << "x: " << 1
                  << " y: " << width / 2 + 1
                  << " side: " << width / 2
                  << '\n';
        std::cout << "x: " << width / 2 + 1
                  << " y: " << width / 2 + 1
                  << " side: " << width / 2
                  << '\n';
        return;
    }

    if (width % 3 == 0) {
        int tempW = width;
        width = 3;
        calculations();
        printAnswer(tempW / width);
        return;
    }

    if (width % 5 == 0) {
        int tempW = width;
        width = 5;
        calculations();
        printAnswer(tempW / width);
        return;
    }

    calculations();
    printAnswer();

}

void Table::printAnswer(int pow) {
    std::cout << "Count of squares: "<< minSquares << std::endl;
    for(int i = 0; i < minSquares; i++) {
        Square temp = bestCase.top();
        bestCase.pop();
        std::cout << "x: " <<temp.x * pow + 1
            << " y: " << temp.y * pow + 1
            << " side: "<< temp.side * pow
            << std::endl;
    }
}

void Table::startAlignment() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < width; j++) {
            if(i < width/2 + 1 && j < width/2 + 1) {
                table[i][j] = 1;
            }
            else if(j < width/2) {
                table[i][j] = 2;
            }
            else if(i < width/2) {
                table[i][j] = 3;
            }
        }
    }
    squaresCounter = 3;
    squares.push(Square(0, 0, width/2 + 1));
    squares.push(Square(width/2 + 1, 0, width/2));
    squares.push(Square(0, width/2 + 1, width/2));
    tempX = width/2;
    tempY = width/2;
}

void Table::print() {
    for (int i = 0; i < width; i++) {
        for(int j = 0; j < width; j++) {
            std::cout << bestTable[i][j];
        }
        std::cout << std::endl;
    }
}
bool Table::isFullAlignment() {
    if(currentSquare == 0)
        currentSquare = width / 2;
    for(int i = width/2; i < width; i++) {
        for(int j = width/2; j < width; j++) {
            if(table[i][j] == 0) {
                tempY = i;
                tempX = j;
                if(squaresCounter >= minSquares) {
                    return false;
                }
                while(true) {
                    if (newSquare())
                    {
                        currentSquare = width / 2;
                        break;
                    }
                    else currentSquare--;
                }

            }
        }
    }
    return true;
}

bool Table::newSquare() {
    if(tempX + currentSquare > width
    || tempY + currentSquare > width) return false;
    for (int i = tempY; i < tempY + currentSquare; i++) {
        for (int j = tempX; j < tempX + currentSquare; j++) {
            if(table[i][j]) return false;
        }
    }
    squaresCounter++;
    for (int i = tempY; i < tempY + currentSquare; i++) {
        for (int j = tempX; j < tempX + currentSquare; j++) {
            table[i][j] = squaresCounter;
        }
    }

    squares.push(Square(tempX, tempY, currentSquare));
    return true;
}

bool Table::allowToClear(int x, int y, int side) {
    if (x < 0 || x + side > width) return false;
    if (y < 0 || y + side > width) return false;
    if (squares.empty()) return false;
    return true;
}

void Table::clearSquare(int x, int y, int side) {
    if(!allowToClear(x, y, side))
        return;
    for(int i = y; i < y + side; i++) {
        for(int j = x; j < x + side; j++) {
            table[i][j] = 0;
        }
    }
    squares.pop();
    squaresCounter--;
}

bool Table::backTracking() {
    Square temp = squares.top();
    while(squares.size() > 3 && temp.side == 1) {
        clearSquare(squares.top().x, squares.top().y, squares.top().side);
        temp = squares.top();
    }

    if(squares.size() == 3){
        return false;
    }
    clearSquare(squares.top().x, squares.top().y, squares.top().side);
    currentSquare = temp.side - 1;
    return true;
}

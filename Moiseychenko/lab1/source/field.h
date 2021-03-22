#pragma once

#include <iostream>
#include <vector>

struct Square {
	int x, y;
	int size;
	Square(int x, int y, int size) : x(x), y(y), size(size) {}
};

class Field {
private:
	int freeArea;
	int n;
	std::vector<std::vector<int>> field;
	std::vector<Square> squares;

public:
	Field(int n);

	std::vector<int>& operator[](int index);

	int SquaresAmount();
	int GetN();
	int GetArea();
	void PrintSquares();
	void PrintField();

	void AddSquare(Square& square);
	bool CheckIntersection(Square& square);
	void RemoveLastSquare();
};
